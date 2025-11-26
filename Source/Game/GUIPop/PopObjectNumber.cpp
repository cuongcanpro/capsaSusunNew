#include "PopObjectNumber.h"
#include <cmath>  
#include <string>
#include "../Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"
#include "BoardDataPop.h"


PopObjectNumber::PopObjectNumber(void)
{
	ball = Sprite::createWithSpriteFrameName("bgNumber2.png");
	addChild(ball);
	//ball->setScaleX(100 / ball->getContentSize().width);
	//ball->setScaleY(100 / ball->getContentSize().height);
	setContentSize(ball->getContentSize());
	ball->setScale(1.01);


	label = Text::create("SCORE", "fonts/tahomabd.ttf", 50);
	addChild(label);
	label->enableOutline(Color4B(253, 226, 167, 255), 2);
	label->setVisible(false);

	bomb = Sprite::createWithSpriteFrameName("iconBomb.png");
	addChild(bomb);
	bomb->setOpacity(50);
	bomb->setScale(1.3);
	//bomb->setAnchorPoint(Vec2(0, 0));
	//bomb->setPosition(-ball->getContentSize().width * 0.5, -ball->getContentSize().height * 0.5);
	bomb->setVisible(false);

	group = new PopNumberGroup();
	addChild(group);
    group->setScale(1.0);
	//group->setVisible(false);

	setNumber(0);
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}


void PopObjectNumber::setRootPosition()
{
	rootX = getPositionX();
	rootY = getPositionY();
}

void PopObjectNumber::resetPosition()
{
	setPositionX(rootX);
	setPositionY(rootY);
}

void PopObjectNumber::setNumber(int number)
{
	setVisible(true);
	setAvailable(true);
	if (number == this->number)
		return;
	this->number = number;
	std::string s = "GuiGame/" + GameUtility::toString(number % 16) + ".png";
	s = "bgNumber2.png";
    if (number < 1000) {
        ball->setColor(GameUtility::getColorPop(number));
        ball->setSpriteFrame(s);
        group->setVisible(true);
        group->setMoney(number);
        group->setPosition(Vec2(-group->getContentSize().width * 0.5 * group->getScaleX(),
                                -group->getContentSize().height * 0.5 * group->getScaleY()));
        group->setVisible(false);
        label->setString(to_string(number));
        label->enableOutline(Color4B(GameUtility::getColorPopOutline(number)), 2);
        label->setVisible(true);
    }
    else
    {
        group->setVisible(false);
        ball->setColor(Color3B(255, 255, 255));
        ball->setSpriteFrame("x" + to_string(number - NUM_SPECIAL) + ".png");
    }
	//ball->setTexture("480_800/bgNumber2.png");
	//ball->setSpriteFrame(s);
	//ball->setSpriteFrame(s.c_str());
	
}

void PopObjectNumber::increaseNumber(int num)
{
	number = number + num;
	setNumber(number);
	playEffect();
	//JNIUtils::vibrate();
}

bool PopObjectNumber::isEffect()
{
    return false;
	//return eff->isVisible();
}

void PopObjectNumber::playEffect()
{
    float scale = getScale();
    runAction(
        Sequence::create(
            ScaleTo::create(0.2, scale * 1.5),
            EaseBounceOut::create(ScaleTo::create(0.5, scale)),
            NULL
        )
    );
}

void PopObjectNumber::callback1()
{
	label->runAction(
		Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.4, 0)),
			CallFunc::create(AX_CALLBACK_0(PopObjectNumber::callback2, this)),
			NULL
		)
	);
}

void PopObjectNumber::callback2()
{
	setNumber(number);
	label->runAction(
		Sequence::create(
			EaseBounceOut::create(ScaleTo::create(0.5, 1)),
			//CallFunc::create(this, callfunc_selector(Number::effectEndGame)),
			NULL
		)
	);
}

bool PopObjectNumber::checkSame(int _number)
{
	return number == _number;
}

void PopObjectNumber::moveDown(float time)
{
	stopAllActions();
	runAction(Sequence::create(
		MoveTo::create(time, Vec2(rootX, rootY)),
        CallFunc::create(AX_CALLBACK_0(PopObjectNumber::callbackMoveDown, this)),
		NULL
	));
	runAction(
		Sequence::create(
			DelayTime::create(time),
			ScaleTo::create(time * 0.4, 1.05, 0.9),
			EaseBounceOut::create(ScaleTo::create(time * 0.6, 1, 1)),
			NULL
		)
	);
}

void PopObjectNumber::callbackMoveDown()
{
	//setIsIdle(true);
}

void PopObjectNumber::moveToEat(float time, Vec2 pos)
{
	stopAllActions();
	runAction(Sequence::create(
		MoveTo::create(time, pos),
        CallFunc::create(AX_CALLBACK_0(PopObjectNumber::callbackMoveEat, this)),
		NULL
	));
	setAvailable(false);
}

void PopObjectNumber::callbackMoveEat()
{
	setVisible(false);
}

PopObjectNumber::~PopObjectNumber(void)
{
}

void PopObjectNumber::effectNewGame()
{
	float sX = ball->getScaleX();
	float sY = ball->getScaleY();
	setScale(0);
	float delay = GameUtility::getRandom() * 0.3;
	runAction(
		Sequence::create(
			DelayTime::create(delay),
			EaseExponentialOut::create(ScaleTo::create(0.5, 1, 1)),
			NULL
		)
	);
}

void PopObjectNumber::effectEndGame()
{
	float pX = 5 * (0.5 - GameUtility::getRandom()) + rootX;
	float pY = 5 * (0.5 - GameUtility::getRandom()) + rootY;
	runAction(Sequence::create(
		MoveTo::create(0.02 + GameUtility::getRandom() * 0.08, Vec2(pX, pY)),
        CallFunc::create(AX_CALLBACK_0(PopObjectNumber::effectEndGame, this)),
		NULL
	));

}

void PopObjectNumber::showBomb(bool show)
{
	bomb->setVisible(show);
	if (show) {
		bomb->setOpacity(0);
		bomb->runAction(FadeTo::create(0.3, 50));
	}
}

void PopObjectNumber::setNewNumber()
{
	label->setFontSize(80);
	label->setScale(0.5);

	Sprite* border = Sprite::create("GuiGame/pop/border.png");
	addChild(border);
	//border->setScale(0.75);
}
