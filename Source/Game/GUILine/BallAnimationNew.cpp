#include "BallAnimationNew.h"
#include "Game/Utility/GameUtility.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include <Game/Utility/GameSound.h>

BallAnimationNew::BallAnimationNew(void):GameImage()
{
}

BallAnimationNew::BallAnimationNew( const char *nameImg, bool frame ): GameImage(nameImg, frame)
{
	std::string s(nameImg);
	nameImage = s;
	countTime = 0;
	frameTime = 0.1f;
	currentFrame = 0;
}


BallAnimationNew::~BallAnimationNew(void)
{
}

void BallAnimationNew::update()
{
	if(true)
		return;
}

void BallAnimationNew::setState( BallState _state )
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	float dy = getWidth() * rootScaleX * 0.2;
    if (state == _state)
        return;
	BallState save = state;
	state = _state;
	currentFrame = 0;
    setLocalZOrder(0);
    float time = 0.3;
    float rateShadow = 1.3;
    float sizeBall       = GUIManager::getInstance().guiLine->sizeCell;
    float sizeShadow = rateShadow * sizeBall;
    float scaleShadow    = sizeShadow / shadow->getContentSize().width;
    shadow->stopAllActions();
    shadow->setVisible(false);
	switch (state)
	{
        case BallState::JUMP:
        {
            shadow->setVisible(true);
            setLocalZOrder(3);
            runAction(
                Sequence::create(
            		Spawn::create(
            			ScaleTo::create(time, 1.3 * rootScaleX, 1.34 * rootScaleY),
            			EaseSineOut::create(MoveTo::create(0.2, Vec2(rootX, rootY + dy))),
            			NULL
            		),
            		Repeat::create(
            			Sequence::create(
            				Spawn::create(
            					ScaleTo::create(time * 2, rootScaleX * 1.0, rootScaleY * 0.8),
            					EaseSineOut::create(MoveTo::create(0.4, Vec2(rootX, rootY - dy * 0.1))),
            					NULL
            				),
                            CallFunc::create(AX_CALLBACK_0(BallAnimationNew::callbackJump, this)),
            				Spawn::create(
            					ScaleTo::create(time * 2, 1.3 * rootScaleX, 1.34 * rootScaleY),
            					EaseSineOut::create(MoveTo::create(0.1, Vec2(rootX, rootY + dy))),
            					NULL
            				),
            				NULL
            			), -1
            		),
            		NULL
            	)
            );
            shadow->runAction(
                Sequence::create(
            	    ScaleTo::create(time, scaleShadow * 1.2),
                    Repeat::create(
            	        Sequence::create(
            			    ScaleTo::create(time * 2, scaleShadow),
            		        ScaleTo::create(time * 2, 1.2 * scaleShadow),
            		        NULL
            	        ), -1
                    ),
                    NULL
                )
            );
             /*runAction(
            	Sequence::create(
            		Spawn::create(
            			ScaleTo::create(0.2, 1.2 * rootScaleX, 0.8 * rootScaleY),
            			EaseSineOut::create(MoveTo::create(0.2, Vec2(rootX, rootY + dy))),
            			NULL
            		),
            		Repeat::create(
            			Sequence::create(
            				Spawn::create(
            					ScaleTo::create(0.4, rootScaleX, rootScaleY),
            					EaseSineIn::create(MoveTo::create(0.4, Vec2(rootX, rootY - dy))),
            					NULL
            				),
            				Spawn::create(
            					ScaleTo::create(0.1, 1.2 * rootScaleX, 0.8 * rootScaleY),
            					EaseSineIn::create(MoveTo::create(0.1, Vec2(rootX, rootY - dy * 0.6))),
            					NULL
            				),
            				Spawn::create(
            					ScaleTo::create(0.3, rootScaleX * 1.1, rootScaleY * 0.9),
            					EaseSineOut::create(MoveTo::create(0.3, Vec2(rootX, rootY + dy))),
            					NULL
            				),
            				NULL
            			), -1
            		),
            		NULL
            	)
            );*/
           
            break;
        }
	case BallState::NORMAL:
		if (save != BallState::BIGGER) {
			cleanup();
			setScaleX(rootScaleX);
			setScaleY(rootScaleY);
		}
		setPos(rootX, rootY);
        shadow->setScale(scaleShadow);
		break;
	case BallState::DISAPPEAR:
		setVisible(false);
		break;
	case BallState::SMALL:
		cleanup();
		setPos(rootX, rootY);
		setScale(0);
		runAction(ScaleTo::create(0.3, rootScaleX * 0.4, rootScaleY * 0.4));
        shadow->setScale(scaleShadow * 0.4);
		break;
	case BallState::BIGGER: {
		cleanup();
        float delayTime = GameUtility::getRandom() * 0.3;
		runAction(Sequence::create(DelayTime::create(delayTime), EaseBackOut::create(ScaleTo::create(0.5f, rootScaleX, rootScaleY)), NULL));
        shadow->runAction(
            Sequence::create(
                DelayTime::create(delayTime),
                ScaleTo::create(0.5f, scaleShadow),
                NULL
            )
        );
		//runAction(EaseBackOut::create(ScaleTo::create(0.15f, rootScaleX, rootScaleY)));
		break;
    }
	default:
		break;
	}
}

void BallAnimationNew::setImage( const char* nameImg )
{
	string s(nameImg);
	nameImage = s;
	GameImage::setImage(nameImg, false);
	int value = 255 * game->brightBall;
	getImg()->setColor(Color3B(value, value, value));
    //getImg()->setAnchorPoint(Vec2(0.5, 0));
    //getImg()->setPosition(Vec2(0, -getImg()->getContentSize().height * 0.5));
}

void BallAnimationNew::setIdBall(int idBall)
{
   // if (this->idBall == idBall)
     //   return;
	this->idBall = idBall;
	
	if (idBall > 0 && idBall < 15) {
		int id = (idBall - 1) % 7;
		string s = GameUtility::getResourceBall(id + 1);
		setImage(s.c_str());
		setVisible(true);
		if (idBall > 7) {
			setState(BallState::SMALL);
		}
		else {
			setState(BallState::NORMAL);
		}
	}
	else if (idBall >= 100) {
		string s = GameUtility::getResourceBall(idBall);
		setImage(s.c_str());
		setVisible(true);
		stopAllActions();
		//float scale = GUIManager::getInstance().guiChallenge.sizeCell / getWidth();
        float scale = 1;
        setPosition(rootX, rootY);
		setScale(scale);
	}
	else {
        cleanup();
		setVisible(false);
        shadow->setVisible(false);
	}
}

void BallAnimationNew::setPos( float x, float y )
{
	GameImage::setPos(x, y);
	rootX = x;
	rootY = y;
}


void BallAnimationNew::setNumber(int _id) {
	setColor(GameUtility::getColorLine(_id));
}

void BallAnimationNew::animationNewGame()
{
	stopAllActions();
	float saveScale = getScaleX();
	setScale(0);
	float targetX = rootScaleX;
	float targetY = rootScaleY;
    float timeDelay = GameUtility::getRandom() * 0.5;
	if (state == BallState::SMALL) {
		targetX = targetX * 0.4;
		targetY = targetY * 0.4;
	}
    else
    {
        float scale = getWidth() * saveScale * 1.3 / shadow->getContentSize().width;
        this->shadow->runAction(Sequence::create(DelayTime::create(timeDelay), ScaleTo::create(0.7, scale), NULL));
    }
	if (this->idBall < 100)
		runAction(Sequence::create(DelayTime::create(timeDelay), EaseBounceOut::create(ScaleTo::create(0.7, targetX, targetY)), NULL));
	else
		runAction(Sequence::create(DelayTime::create(timeDelay), EaseBounceOut::create(ScaleTo::create(0.7, saveScale, saveScale)), NULL));
}

void BallAnimationNew::animationNewGame2(float delay, Vec2 pos) {
    setPosition(pos);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = pos;
    bezier.controlPoint_2 = Vec2(GameUtility::getRandom() * 700, GameUtility::getRandom() * 1200);
    bezier.endPosition    = Vec2(rootX, rootY);
    runAction(
        Sequence::create(
            DelayTime::create(delay),
            EaseSineOut::create(BezierTo::create(0.5, bezier)),
            NULL
        )
    );
}

void BallAnimationNew::effectEndGame(float delay)
{
	runAction(Sequence::create(
		DelayTime::create(delay),
		MoveBy::create(0.2, Vec2(0, 20)),
		EaseBounceOut::create(MoveBy::create(0.5, Vec2(0, -20))),
		NULL
	));
}

void BallAnimationNew::doBreak()
{
	stopAllActions();
	float scale = getScaleX();
	runAction(Sequence::create(
		DelayTime::create(0.3),
		Repeat::create(Sequence::create(ScaleTo::create(0.06, scale * 1.1), ScaleTo::create(0.06, scale), NULL), 4),
		Hide::create(), 
		NULL));
}



void BallAnimationNew::effectVibrate()
{
	if (state == BallState::JUMP)
		return;
	if (state == BallState::BIGGER || state == BallState::NORMAL) {
		stopAllActions();
		setScale(rootScaleX);
	}
	numVibrate = 0;
	doVibrate();
}

void BallAnimationNew::doVibrate()
{
	if (numVibrate > 3) {
		stopAllActions();
		setPosition(rootX, rootY);
		return;
	}
	numVibrate++;
	float pX = rootX + 5 * (0.5 - GameUtility::getRandom());
	float pY = rootY + 5 * (0.5 - GameUtility::getRandom());
	runAction(Sequence::create(
		MoveTo::create(0.01 + GameUtility::getRandom() * 0.004, Vec2(pX, pY)),
                                   CallFunc::create(AX_CALLBACK_0(BallAnimationNew::doVibrate, this)),
		NULL
	));
}

void BallAnimationNew::callbackJump() {
    GameSound::playJump();
}
