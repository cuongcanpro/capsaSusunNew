#include "FlyNumber.h"
#include <cmath>  
#include <string>

FlyNumber::FlyNumber(void)
{
	iconWingLeft = Sprite::create("GuiGame/pop/iconWingLeft.png");
	addChild(iconWingLeft);
	iconWingLeft->setAnchorPoint(Vec2(0.95, 0.3));
	iconWingLeft->setPosition(Vec2(-40, 30));

	iconWingRight = Sprite::create("GuiGame/pop/iconWingRight.png");
	addChild(iconWingRight);
	iconWingRight->setAnchorPoint(Vec2(0.05, 0.3));
	iconWingRight->setPosition(Vec2(40, 30));

	iconNumber = new PopObjectNumber();
	addChild(iconNumber);
	iconNumber->setNumber(1);
	iconNumber->setNewNumber();

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

FlyNumber::~FlyNumber(void)
{
}

void FlyNumber::setNumber(int number)
{
	iconNumber->setNumber(number);
}

void FlyNumber::effectFly(Vec2 pos)
{
	iconWingLeft->stopAllActions();
	iconWingLeft->setRotation(30);
	iconWingLeft->runAction(
		RepeatForever::create(
			Sequence::create(
				RotateTo::create(0.2, -30),
				RotateTo::create(0.2, 30),
				NULL
			)
		)
	);

	iconWingRight->stopAllActions();
	iconWingRight->setRotation(-30);
	iconWingRight->runAction(
		RepeatForever::create(
			Sequence::create(
				RotateTo::create(0.2, 30),
				RotateTo::create(0.2, -30),
				NULL
			)
		)
	);

	setVisible(true);
	setOpacity(0);
	Size size     = Director::getInstance()->getRenderView()->getVisibleSize();
	setPosition(pos);
	ccBezierConfig config1;
	config1.controlPoint_1 = Vec2(size.width * (0.1 + AXRANDOM_0_1() * 0.8), size.height * 0.2 + pos.y);
	config1.endPosition = Vec2(size.width * (0.1 + AXRANDOM_0_1() * 0.8), size.height * 0.4 + pos.y);

	ccBezierConfig config2;
	config2.controlPoint_1 = Vec2(size.width * (0.1 + AXRANDOM_0_1() * 0.8), size.height * 0.6 + pos.y);
	config2.endPosition = Vec2(size.width * (0.1 + AXRANDOM_0_1() * 0.8), size.height * 0.8 + pos.y);
	runAction(FadeIn::create(0.5));
	runAction(
		Sequence::create(
			EaseSineIn::create(BezierTo::create(1.5, config1)),
			EaseSineOut::create(BezierTo::create(1.5, config2)),
			FadeOut::create(0.5),
			Hide::create(),
			NULL
		)
	);
}

