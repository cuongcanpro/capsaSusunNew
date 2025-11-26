#include "BallMove.h"
#include "Game/GUIManager.h"
#include "math.h"
#include "Game/Utility/GameUtility.h"
#include "aaConfig.h"
#include "BallCircle.h"


BallMove::BallMove(void)
{
	ball = new GameImage("circle.png");
	setAnchorPoint(Vec2(0, 0));
	ball->setWidth(AA_WIDTH_BALL);
	ball->setHeight(AA_WIDTH_BALL);
	ball->getImg()->setAnchorPoint(Vec2(0, 0));
    ball->getImg()->setColor(Color3B(222, 196, 143));
	this->addChild(ball);

	label = Text::create("10", "fonts/tahomabd.ttf", 12);
	this->addChild(label);
	label->setColor(Color3B(0,0,0));
	label->setPosition(Vec2(ball->getRealWidth() * 0.5f, ball->getRealHeight() * 0.5f));

	state = StateBall::MOVE;
	//setContentSize(CCSizeMake(ball->getRealWidth(), ball->getRealHeight()));
}


BallMove::~BallMove(void)
{
}

void BallMove::act1(float delta) {
	if (state == MOVE && GUIManager::getInstance().guiAa->state != GameState::END_GAME) {
		setPositionY(getPositionY() + AA_SPEED_BALL);
		if(!checkHit()){
			checkMakeNew();
		}
	}
}

bool BallMove::checkHit() {
	vector<BallCircle*> arrayBall = GUIManager::getInstance().guiAa->arrayBall;
	for (int i = 0; i < arrayBall.size(); i++) {
		double distance = (arrayBall.at(i)->ball->getPositionX() - getPositionX())
			* (arrayBall.at(i)->ball->getPositionX() - getPositionX());
		distance = distance + (arrayBall.at(i)->ball->getPositionY() - getPositionY())
			* (arrayBall.at(i)->ball->getPositionY() - getPositionY());
		distance = sqrt(distance);
		if (distance <= AA_WIDTH_BALL) {
			// va cham va game over
			GUIManager::getInstance().guiAa->endGame();
			return true;
		}
	}

	return false;
}

void BallMove::checkMakeNew() {
    Size size   = Director::getInstance()->getRenderView()->getVisibleSize();
    double distance = (AA_ROOT_X - getPositionX()) * (AA_ROOT_X - getPositionX());
    distance        = distance + (AA_ROOT_Y - getPositionY()) * (AA_ROOT_Y - getPositionY());
    distance        = sqrt(distance);
    if (distance < AA_RADIUS)
    {
        // tao qua bong moi
        setPositionY(AA_ROOT_Y - AA_RADIUS);
        if (!checkHit())
            GUIManager::getInstance().guiAa->makeNew();
    }
}

void BallMove::setText(int num)
{
	label->setString(GameUtility::toString(num).c_str());
//	label->setPositionX(ball->getRealWidth() * 0.5f);
}

void BallMove::setRealWidth(float AA_WIDTH_BALL) {
	// TODO Auto-generated method stub
	setScale(AA_WIDTH_BALL / AA_ROOT_WIDTH_BALL);
	
}
