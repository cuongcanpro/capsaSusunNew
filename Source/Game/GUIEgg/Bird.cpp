#include "Bird.h"
#include "math.h"
#include "Game/Utility/GameUtility.h"
#include "Game/GUIManager.h"
#include "Game/Logic/Constant.h"

Bird::Bird(void)
{
    GameImage("Egg/fly_1.png");
    countTime    = 0;
    frameTime    = 0.04f;
    currentFrame = 0;
    setImage("Egg/fly_1.png");
    // act(0);
}

Bird::~Bird(void) {}

void Bird::setDegree(double degree)
{
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();

    if (degree > 0)
    {
        setScaleX(1);
        setPositionX(START_X);
    }
    else
    {
        setScaleX(-1);
        setPositionX(size.width - START_X - fabs(getRealWidth()) * 0.5f);
    }
    this->degree = degree;

    double radian = degree / 180 * 3.14;

    float dis          = 3.285;
    float arrayRate[7] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};
    if (countAppear < 7)
    {
        SPEED_BIRD = dis * arrayRate[countAppear];
    }
    else
    {
        SPEED_BIRD = dis * (arrayRate[6] + (countAppear - 6) * 0.03);
    }

    vx = (float)(SPEED_BIRD * sin(radian));
    vy = (float)(SPEED_BIRD * cos(radian));
}

void Bird::updatePosition(float delta)
{
    float rateSpeed = delta * 60;
    countTime       = countTime + delta;
    if (countTime >= frameTime)
    {
        countTime = 0;
        currentFrame++;
        if (currentFrame > 15)
        {
            currentFrame = 0;
        }
    }
    if (currentFrame < 0)
        currentFrame = 0;
    setImage(("Egg/fly_" + GameUtility::toString(currentFrame + 1) + ".png").c_str());

    setPositionX(getPositionX() + vx * rateSpeed);
    setPositionY(getPositionY() + vy * rateSpeed);
}

void Bird::checkVisible()
{
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    if (getPositionY() > size.height)
    {
        setVisible(false);
        if (GUIManager::getInstance().guiGame->genBall->isVisible())
        {
            // them bong moi
            countAppear = 0;
            GUIManager::getInstance().guiGame->addNewBall();
        }
    }
    else
    {
        if (getPositionX() <= START_X || getPositionX() >= size.width - START_X - fabs(getRealWidth()) * 0.5f)
        {
            // dao chieu bay cua chim
            setDegree(-degree);
        }
    }
}

void Bird::act(float delta)
{
    if (isVisible())
    {
        this->updatePosition(delta);
        this->checkVisible();
    }
}

void Bird::newGame()
{
    setVisible(false);
    countAppear = 0;
}
