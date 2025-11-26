#include "BallCircle.h"
#include "Game/Data/GlobalData.h"
#include "math.h"
#include "aaConfig.h"


BallCircle::BallCircle(void)
{
	ball = new GameImage("circle.png");
	ball->setWidth(AA_WIDTH_BALL);
	ball->setHeight(AA_WIDTH_BALL);
	ball->getImg()->setAnchorPoint(Vec2(0, 0));
    ball->getImg()->setColor(Color3B(222, 196, 143));

	bar = new GameImage("bgWhite.jpg");
    bar->getImg()->setAnchorPoint(Vec2(0.5f, 1));
	bar->setWidth(AA_WIDTH_BALL * 0.03f);
	bar->setHeight(AA_RADIUS);
	bar->setPosition(AA_ROOT_X, AA_ROOT_Y);
    bar->getImg()->setColor(Color3B(222, 196, 143));

	countTime = 0;
}


BallCircle::~BallCircle(void)
{
}

void BallCircle::act(float delta) {

	countTime = countTime + delta;

    double angle = countTime / AA_TIME_WHEEL * 2 * 3.14;
    angle        = angle - 3.14 * 0.5f;

    float posX = (float)(cos(angle) * AA_RADIUS + AA_ROOT_X);

    float posY = (float)(sin(angle) * AA_RADIUS + AA_ROOT_Y);

    float degree = countTime / AA_TIME_WHEEL * 360;

    bar->setRotation(-degree);
    //	bar->setPosition(posX, posY);

    posX = (float)(cos(angle) * (AA_RADIUS - AA_WIDTH_BALL * 0.5f) + AA_ROOT_X);

    posY = (float)(sin(angle) * (AA_RADIUS - AA_WIDTH_BALL * 0.5f) + AA_ROOT_Y);

    ball->setPosition(posX - AA_WIDTH_BALL * 0.5f, posY - AA_WIDTH_BALL * 0.5f);
}

void BallCircle::finishGame()
{
	ball->runAction(MoveTo::create(0.5f, Vec2(AA_ROOT_X - ball->getRealWidth() * 0.5f, AA_ROOT_Y - ball->getRealWidth() * 0.5f)));
	bar->runAction(ScaleTo::create(0.5f, 1, 0));
}

void BallCircle::setPosition(float f, float g) {
	// TODO Auto-generated method stub
	ball->setPosition(f - ball->getRealWidth() * 0.5f, g - AA_RADIUS);
	bar->setPosition(f, g);
}
