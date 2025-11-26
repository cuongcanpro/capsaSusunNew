#include "guiSwing.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "../Utility/Toast.h"


#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_PLAY_ID 3

std::string GUISwing::className = "GUISwing";
GUISwing::GUISwing(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	setKeypadEnabled(true);
	time = 0;
	bar = NULL;
}


GUISwing::~GUISwing(void)
{
}

void GUISwing::initGUI(){

    callBackSplash();
    setKeypadEnabled(true);
}

void GUISwing::onBackKey()
{
	AXLOGD("KEY BACK CLICK ");
    if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
    {
        game->changeToLandscape();
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
        GUIManager::getInstance().isCallBackPress = true;
    }
}

void GUISwing::update()
{
	if(bar == NULL)
		return;
	
	
	if (gameState == GUISwing::GameState::PRESS)
	{
		stickMan->update();
		updateMove();
	}
	else if(gameState == GUISwing::GameState::SWING)
	{
		updateSwing();
	}
	else if(gameState == GUISwing::GameState::SWING_REVERSE)
	{
		updateReverse();
	}
		//time = time + game->deltaTime;
		//bar->setHeight(time / 0.008f * fixHeight);
	
		//GameSound::playScroll();
	for(int i = 0; i < arraySmoke.size(); i++)
		arraySmoke.at(i)->update();

}

void GUISwing::onButtonRelease(int buttonID, Touch* touch)
{
	GameSound::playClick();
	switch (buttonID)
	{
	case BTN_BACK_ID:
		{
			
			onBackKey();
		}
		
		break;
	case BTN_SOUND_ID:
		{
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("btnSoundOn.png");
			}
			else
			{
				btnSound->normalImage->setImage("btnSoundOff.png");
			}

			UserDefault::getInstance()->setBoolForKey("music", game->music);
			UserDefault::getInstance()->flush();
		}
		break;
	case BTN_PLAY_ID:
		{
			gameState = saveState;
			btnPlay->setVisible(false);
		}
		break;
	default:
		break;
	}
}

void GUISwing::callBackSplash()
{
	BaseGUI::initGUI();
	
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	countGame = 0;
	

	btnPlay = addButton(BTN_PLAY_ID, "swing/btnPlayBig.png");
	btnPlay->setPosition(size.width * 0.5f, size.height * 0.5f);
	btnPlay->setVisible(false);

	GameImage* bg = addImage("swing/background.png");
	bg->setWidth(size.width);
	bg->setHeight(size.height);
	bg->setPos(size.width * 0.5f, size.height * 0.5f);

    btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if(game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png");
	}

	bar = addImage("swing/bgDark.png");
	bar->setAnchorPointImage(Vec2(0.5f, 0));
	bar->setWidth(size.width * 0.01f);
	fixHeight = size.height * 0.005f;

	stickMan = new StickMan();
	this->addChild(stickMan);
	
	rootHeight = size.height * 0.5f;
	column1 = addImage("swing/bgDark.png");
	column1->_img->setAnchorPoint(Vec2(0.5f, 0));
	column1->setHeight(rootHeight);
	column1->setPos(0, 0);

	column2 = addImage("swing/bgDark.png");
	column2->_img->setAnchorPoint(Vec2(0.5f, 0));
	column2->setHeight(rootHeight);
	column2->setPos(0, 0);

	column3 = addImage("swing/bgDark.png");
	column3->_img->setAnchorPoint(Vec2(0.5f, 0));
	column3->setHeight(rootHeight);
	column3->setPos(0, 0);

	stickStand = addImage("swing/stickStand.png");
	stickStand->setVisible(false);
	stickStand->setPos(size.width * 0.5f, size.height * 0.5f);
	stickStand->setOpacity(150);
	
	//bar->setPos(200, 300);
	//bar->setHeight(200);
    lbState = Text::create("SCORE: 0", "fonts/tahomabd.ttf", 30);
    lbState->enableOutline(Color4B(10, 10, 10, 255), 2);
    addChild(lbState);
// labelScore->setColor(Color3B(50, 50, 50));
    lbState->setPositionX(size.width * 0.5f);
    lbState->setPositionY(size.height * 0.9f);

	Scale9Sprite* bgScore = Scale9Sprite::create("GuiGame/bgScoreNormal.png");
    addChild(bgScore);
    bgScore->setContentSize(Size(110, 50));
    bgScore->setPosition(Vec2(bgScore->getContentSize().width * 0.54, btnBack->getPositionY()));

    Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 14);
    bgScore->addChild(lbScore);
    lbScore->enableOutline(Color4B(3, 85, 188, 255), 1);
    lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.75));

    Scale9Sprite* bgBest = Scale9Sprite::create("GuiGame/bgScoreBest.png");
    addChild(bgBest);
    bgBest->setContentSize(bgScore->getContentSize());
    bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.05, bgScore->getPositionY());

    Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 14);
    bgBest->addChild(lbBest);
    lbBest->enableOutline(Color4B(175, 108, 3, 255), 1);
    lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.75));

    labelScore = Text::create("0", "fonts/tahomabd.ttf", 18);
    labelScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelScore->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelScore->enableOutline(Color4B(3, 85, 188, 255), 1);
    bgScore->addChild(labelScore);
    labelScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.3));

    highscore      = UserDefault::getInstance()->getIntegerForKey("highscoreSwing", 0);
    labelHighscore = Text::create(GameUtility::standardizeNumber(highscore), "fonts/tahomabd.ttf", 18);
    labelHighscore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelHighscore->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelHighscore->enableOutline(Color4B(175, 108, 3, 255), 1);
    bgBest->addChild(labelHighscore);
    labelHighscore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.3));
    
    iconHand = Sprite::create("GuiGame/iconHand.png");
    addChild(iconHand);
    iconHand->setPosition(size.width * 0.5, size.height * 0.8);

}

bool GUISwing::onTouchBegan( Touch *pTouch, Event *pEvent )
{
    if (pTouch->getLocation().y > Director::getInstance()->getRenderView()->getVisibleSize().height * 0.9f)
        return BaseGUI::onTouchBegan(pTouch, pEvent);
	else
	{
// 		gameState = PRESS;
// 		stickStand->setVisible(false);
// 		stickMan->setVisible(true);
// 		startMove();
        if (gameState == GUISwing::GameState::WAIT_MOVE)
            startMove();
		else if (gameState == GUISwing::GameState::PRESS)
			startSwing();
		return BaseGUI::onTouchBegan(pTouch, pEvent);
	}

}

void GUISwing::genNewGame()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	
	bar->setVisible(false);
	stickMan->setState(StickMan::StickManState::NORMAL);
	column1->cleanup();
	column2->cleanup();
	width1 = (0.25f + GameUtility::getRandom() * 0.1f) * size.width;
	width2 = (0.04f + GameUtility::getRandom() * 0.2f) * size.width;
	distance = (0.1f * size.width + GameUtility::getRandom() * (size.width * 0.9f - width1 - width2));
	height2 = rootHeight * (0.7f + GameUtility::getRandom() * 0.3f);
	float scale3 = height2 / column3->getHeight();
	float scale2 = rootHeight/ column2->getHeight();

	float sumWidth = column1->getRealWidth() + column2->getRealWidth();
	float pos1 = width1 - sumWidth;
	float pos2 = pos1 + column1->getRealWidth();
	float pos3 = width1 + distance;

	
	column1->setWidth(width1);
	column1->setPositionX(width1 * 0.5f);

	column2->setWidth(width2);
	column2->setPositionX(width1 + distance + width2 * 0.5f);
	column2->setScaleY(scale3);

	column3->setVisible(false);
	bar->setRotation(0);
	bar->setPositionX(width1 - bar->getRealWidth() * 0.5f);
	bar->setPositionY(rootHeight);
	bar->setHeight(fixHeight);
	bar->setRotation(-70);

	stickMan->setPos(width1 - stickMan->getWidth() * 0.5f, rootHeight + stickMan->getHeight() * 0.5f);
	stickMan->setVisible(false);
	stickStand->setVisible(true);
	stickStand->setPos(width1 - stickStand->getWidth() * 0.5f, rootHeight + stickStand->getHeight() * 0.5f);

    bar->setRotation(0);
    bar->setHeight(fixHeight);
    score = 0;
    updateScore();

	//runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(AX_CALLBACK_0(GUISwing::startMove, this)), NULL));
    gameState = GameState::WAIT_MOVE;
    lbState->setVisible(true);
    lbState->setString("Tap screen to move character!");
    showHand();
	//Toast::makeToast(2.0f, "Tap screen to make a swing!");
}

void GUISwing::showHand() {
    if (highscore > 2)
    {
        return;
    }
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    iconHand->setVisible(true);
    iconHand->stopAllActions();
    Vec2 pos = Vec2(size.width * 0.5, size.height * 0.8);
    iconHand->runAction(RepeatForever::create(
        Sequence::create(
            DelayTime::create(0.5),
            Spawn::create(FadeIn::create(0), MoveTo::create(0.0f, pos), ScaleTo::create(0.0, 1.0), NULL),
            Spawn::create(MoveTo::create(0.2f, Vec2(pos.x, pos.y - 20)), EaseBounceOut::create(ScaleTo::create(0.4, 0.8)), NULL),
            DelayTime::create(1.0),
            Spawn::create(FadeOut::create(0.5), NULL),
            DelayTime::create(1.0),
            NULL
        )
    ));
}

void GUISwing::onTouchEnded( Touch *pTouch, Event *pEvent )
{
	
	
// 	if(isPress)
// 	{
// 		float distance = column2->getPositionX() - column2->getRealWidth() * 0.5f - column1->getRealWidth();
// 		float distance1 = distance + column2->getRealWidth();
// 		AXLOGD("ToUCHE END %f %f %f ", distance, distance1, bar->getRealHeight());
// 		//bar->setHeight(500);
// 		if(bar->getRealHeight() >= distance && bar->getRealHeight() <= distance1)
// 			bar->runAction(Sequence::create(RotateBy::create(0.4f, 90), CallFunc::create(this, AX_CALLBACK_0(GUISwing::startRun)), NULL));
// 		else
// 		{
// 			bar->runAction(Sequence::create(RotateBy::create(0.4f, 90), CallFunc::create(this, AX_CALLBACK_0(GUISwing::startRunFail)), NULL));
// 		}
// 		stickMan->setState(KICK, 0.05f);
// 		time = 0;
// 		isPress = false;
// 		return;
// 	}
// 	
	BaseGUI::onTouchEnded(pTouch, pEvent);
}

void okEndFunction()
{
	//GUIManager::getInstance().guiSwing->bar->setRotation(0);
	//GUIManager::getInstance().guiSwing->bar->setHeight(GUIManager::getInstance().guiSwing->fixHeight);

	GUIManager::getInstance().guiSwing->genNewGame();
	GUIManager::getInstance().guiSwing->score = 0;
	GUIManager::getInstance().guiSwing->updateScore();
}

void cancelEndFunction()
{
	//GUIManager::getInstance().guiSwing->bar->setRotation(0);
	//GUIManager::getInstance().guiSwing->bar->setHeight(GUIManager::getInstance().guiSwing->fixHeight);

	GUIManager::getInstance().guiSwing->genNewGame();
	GUIManager::getInstance().guiSwing->score = 0;
	GUIManager::getInstance().guiSwing->updateScore();
	GUIManager::getInstance().guiSwing->cleanup();
	GUIManager::getInstance().guiSwing->startMove();
	GUIManager::getInstance().guiSwing->pause();
}

void GUISwing::endGame()
{
	//GameSound::playCrack();
    GUIManager::getInstance().guiResult->showGUI(score, highscore);
}

void GUISwing::startRun()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    gameState      = GUISwing::GameState::PRESS;
	float distance = column2->getPositionX() - column2->getRealWidth() * 0.5f - column1->getRealWidth();
    stickMan->setState(StickMan::StickManState::RUN, 0.03f / (distance / size.width / 0.2f));
	stickMan->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(distance, 0)), CallFunc::create(AX_CALLBACK_0(GUISwing::nextStep, this)), NULL));
    lbState->setVisible(true);
    
}

void GUISwing::nextStep()
{
    GameSound::playCorrect();
	bar->setVisible(false);
	stickMan->setState(StickMan::StickManState::NORMAL);
	column1->cleanup();
	column2->cleanup();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	width1 = (0.25f + GameUtility::getRandom() * 0.1f) * size.width;
	width2 = (0.04f + GameUtility::getRandom() * 0.2f) * size.width;
	distance = (0.1f * size.width + GameUtility::getRandom() * (size.width * 0.9f - width1 - width2));
	height2 = rootHeight * (0.7f + GameUtility::getRandom() * 0.3f);
	float scale3 = height2 / column3->getHeight();
	float scale2 = rootHeight/ column2->getHeight();

	float sumWidth = column1->getRealWidth() + column2->getRealWidth();
	float pos1 = width1 - sumWidth;
	float pos2;
	float pos3 = width1 + distance;

	if(pos1 > 0)
	{
		column1->setWidth(width1 - column2->getRealWidth());
		column1->runAction(MoveTo::create(0.3f, Vec2(column1->getRealWidth() * 0.5f, column1->getPositionY())));
		pos2 = column1->getRealWidth() + column2->getRealWidth() * 0.5f;
	}
	else
	{
		column1->runAction(MoveTo::create(0.3f, Vec2(pos1 + column1->getRealWidth() * 0.5f, column1->getPositionY())));
		pos2 = pos1 + column1->getRealWidth();
	}
	column2->runAction(MoveTo::create(0.3f, Vec2(pos2 + column2->getRealWidth() * 0.5f, column2->getPositionY())));
	column2->runAction(ScaleTo::create(0.3f, column2->getScaleX(), scale2));
	column3->setVisible(true);
	column3->setWidth(width2);
	column3->setPos(size.width + width2 * 0.5f, 0);
	column3->setScaleY(0);

	ScaleTo* scaleTo = ScaleTo::create(0.5f, column3->getScaleX(), scale3);
	//ActionInterval* move_ease_in = EaseBounceOut::create((ActionInterval*)(scaleTo->copy()->autorelease()));
    column3->runAction(EaseBounceOut::create(ScaleTo::create(0.5f, column3->getScaleX(), scale3)));
	column3->runAction(MoveTo::create(0.3f, Vec2(pos3 + width2 * 0.5f, 0)));

	isGen = true;
    gameState = GameState::WAIT_MOVE;
    lbState->setVisible(true);
    lbState->setString("Tap screen to move character!");
    showHand();
    // Toast::makeToast(2.0f, "Tap screen to make a swing!");
	//runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(AX_CALLBACK_0(GUISwing::startMove, this)), NULL));
	stickStand->runAction(MoveTo::create(0.3f, Vec2(width1 - stickStand->getWidth() * 0.5f, rootHeight + stickStand->getHeight() * 0.5f)));

	score = score + 1;
	updateScore();

	bar->setRotation(0);
	bar->setHeight(fixHeight);
	bar->setPositionX(width1 - bar->getRealWidth() * 0.5f);

}

void GUISwing::updateScore()
{
	labelScore->setString(("" + GameUtility::toString(score)).c_str());
	if(score > highscore)
	{
		highscore = score;
		labelHighscore->setString(("" + GameUtility::toString(highscore)).c_str());
        UserDefault::getInstance()->setIntegerForKey("highscoreSwing", score);
		UserDefault::getInstance()->flush();
	}
}

void GUISwing::startRunFail()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	stickMan->setState(StickMan::StickManState::RUN, 0.03f / (bar->getRealHeight() / size.width / 0.2f));
	stickMan->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(bar->getRealHeight(), 0)), CallFunc::create(AX_CALLBACK_0(GUISwing::startFall, this)), NULL));
}

void GUISwing::startFall()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    bar->runAction(Sequence::create(RotateBy::create(0.4f, 90),
                                    CallFunc::create(AX_CALLBACK_0(GUISwing::endGame, this)), NULL));
	stickMan->runAction(MoveBy::create(1.0f, Vec2(0, -size.height * 0.4f)));

	stickMan->setState(StickMan::StickManState::NORMAL);
	stickMan->runAction(RotateBy::create(0.4f, 360));
}


void GUISwing::startMove()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	column1->setWidth(width1);
	column2->setWidth(width2);
	column2->setHeight(height2);
	column3->setVisible(false);

	isGen = false;
	column1->setPos(width1 * 0.5f, 0);
	column2->setPos(width1 + distance + width2 * 0.5f, 0);

	stickMan->setPos(width1 - stickMan->getWidth() * 0.5f, rootHeight + stickMan->getHeight() * 0.5f);
	stickStand->setPos(width1 - stickStand->getWidth() * 0.5f, rootHeight + stickStand->getHeight() * 0.5f);

	stickStand->setVisible(false);
	stickMan->setVisible(true);
	//float distance = column2->getPositionX() - column2->getRealWidth() * 0.5f - column1->getRealWidth();
	column1->setWidth(size.width);
	column1->setPositionX(width1 - size.width * 0.5f);
        stickMan->setState(StickMan::StickManState::RUN);
	bar->setVisible(true);
        gameState = GUISwing::GameState::PRESS;
	
	//stickMan->runAction(Sequence::create(MoveBy::create(1.0f, Vec2(distance, 0)), CallFunc::create(this, AX_CALLBACK_0(GUISwing::nextStep)), NULL));
    lbState->setOpacity(0);
    lbState->runAction(Sequence::create(DelayTime::create(0.5), FadeIn::create(0.5), NULL));
    lbState->setString("Tap screen to make a swing!");
    showHand();
}

void GUISwing::updateMove()
{
    if (stickMan->state == StickMan::StickManState::RUN)
	{
		if(stickMan->getPositionX() - stickMan->getWidth() * 0.5f < 0)
		{
			stickMan->setPositionX(stickMan->getWidth() * 0.5f);
			column1->setPositionX(column1->getPositionX() + stickMan->speed);
			column2->setPositionX(column2->getPositionX() + stickMan->speed);
			for(int i = 0; i < arraySmoke.size(); i++)
			{
				if(arraySmoke.at(i)->isVisible())
				{
					arraySmoke.at(i)->setPositionX(arraySmoke.at(i)->getPositionX() + stickMan->speed);
				}
			}
		}
		if(column1->getPositionX() >= column1->getRealWidth() * 0.5f + stickMan->getWidth() * 0.5f)
		{
			//end game
			doEndGame(1);
			return;
		}
		bar->setVisible(true);

		float tagValue = stickMan->getHeight() * 0.33f / stickMan->distance;
		float tagAngle = atan(tagValue);
		float height = stickMan->distance / cos(tagAngle);
		tagAngle = tagAngle * 180/ 3.14;
		bar->setHeight(stickMan->distance + stickMan->getWidth() * 0.35f);
		bar->setRotation(tagAngle - 90);
		bar->setPositionX(column1->getRealWidth() * 0.5f + column1->getPositionX());
	}
	
}

void GUISwing::startSwing()
{
	//bar->runAction(RotateTo::create(1.0f, -270, -270));
    gameState = GUISwing::GameState::SWING;
	stickMan->setState(StickMan::StickManState::NORMAL);
	GameSound::playMove();
    lbState->setVisible(false);
    iconHand->setVisible(false);
}

void GUISwing::updateSwing()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	bar->setRotation(bar->getRotation() - 3);

	float dy = bar->getRealHeight() * sin((bar->getRotation() - 90) / 180 * 3.14);
	stickMan->setPositionY(rootHeight - dy);

	if(column1->getPositionX() + column1->getRealWidth() * 0.5f > width1)
	{
		float speed = size.width * 0.02f;
		column1->setPositionX(column1->getPositionX() - speed);
		column2->setPositionX(column2->getPositionX() - speed);
		bar->setPositionX(column1->getPositionX() + column1->getRealWidth() * 0.5f);
		
	}
	float posX = bar->getPositionX() - bar->getRealHeight() * cos(fabs((bar->getRotation() + 90) / 180 * 3.14f));
	stickMan->setPositionX(posX);

	if(bar->getRotation() < -290)
	{
		gameState = GUISwing::GameState::SWING_REVERSE;
	}
}

void GUISwing::updateReverse()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Point p1, p2;
	p1.x = stickMan->getPositionX();
	p1.y = stickMan->getPositionY() - stickMan->getHeight() * 0.5f;

	if(fabs(p1.y - height2) < size.width * 0.03f)
	{
		if(p1.x + stickMan->getWidth() * 0.1f > column2->getPositionX() - column2->getRealWidth() * 0.5f && p1.x - stickMan->getWidth() * 0.1f < column2->getPositionX() + column2->getRealWidth() * 0.5f)
		{
			gameState = GUISwing::GameState::FINISH;
			stickStand->setVisible(true);
			stickStand->setPos(stickMan->getPositionX(), height2 + stickStand->getHeight() * 0.5f);
			stickMan->setVisible(false);
                        runAction(Sequence::create(DelayTime::create(0.5f),
                                                   CallFunc::create(AX_CALLBACK_0(GUISwing::nextStep, this)),
                                                   NULL));
			bar->runAction(RotateTo::create(0.5f, -100, -100));
			GameSound::playLand();
			return;
		}
	}
	else
	{
		if(p1.y < rootHeight)
		{
			if(p1.x < column1->getPositionX() + column1->getRealWidth() * 0.5f)
			{
				// game over
				doEndGame();
				return;
			}
		}

		if(p1.y < height2)
		{
			if(p1.x > column2->getPositionX() - column2->getRealWidth() * 0.5f && p1.x < column2->getPositionX() + column2->getRealWidth() * 0.5f)
			{
				// game over
				doEndGame();
				return;
			}

		}
	}
	bar->setRotation(bar->getRotation() + 3);
	float dy = bar->getRealHeight() * sin((bar->getRotation() - 90) / 180 * 3.14);
	stickMan->setPositionY(rootHeight - dy);

	float posX = bar->getPositionX() - bar->getRealHeight() * cos(fabs((bar->getRotation() + 90) / 180 * 3.14f));
	stickMan->setPositionX(posX);
}

void GUISwing::doEndGame(int type)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    gameState = GUISwing::GameState::GAME_OVER;
	bar->runAction(RotateTo::create(0.5f, -90, -90));
	makeSmoke();
	stickMan->setState(StickMan::StickManState::NORMAL);
	if(type == 0)
	{
		stickMan->runAction(MoveTo::create(1.0f, Vec2(stickMan->getPositionX() + size.width * 0.2f, stickMan->getPositionY() - size.height * 0.3f)));
	}
	else
	{
		stickMan->runAction(MoveTo::create(1.0f, Vec2(stickMan->getPositionX(), stickMan->getPositionY() - size.height * 0.5f)));
	}
        stickMan->runAction(Sequence::create(RotateBy::create(1.0f, 360),
                                             CallFunc::create(AX_CALLBACK_0(GUISwing::endGame, this)), NULL));
	
	GameSound::playEnd();
}

void GUISwing::makeSmoke()
{
	Smoke* smoke = NULL;
	for(int i = 0; i < arraySmoke.size(); i++)
	{
		if(!arraySmoke.at(i)->isVisible())
		{
			smoke = arraySmoke.at(i);
		}
	}
	if(smoke == NULL)
	{
		smoke = new Smoke();
		addChild(smoke);
		arraySmoke.push_back(smoke);
	}

	smoke->setPos(stickMan->getPositionX(), stickMan->getPositionY() - stickMan->getHeight() * 0.45f);
	smoke->start();
    GameSound::playWalk();
	//GameSound::playFoot();
}

void GUISwing::pause()
{
	if(gameState != GUISwing::GameState::GAME_OVER)
	{
		saveState = gameState;
		gameState = GUISwing::GameState::PAUSE;
		btnPlay->setVisible(true);
	}
}

void GUISwing::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
    BaseGUI::showGUI(parent, hasFog);
    // Nếu có save tạm, tiếp tục; không thì ván mới
    genNewGame();
}
