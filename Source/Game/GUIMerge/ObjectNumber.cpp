#include "ObjectNumber.h"
#include <cmath>  
#include <string>
#include "Game/Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"


ObjectNumber::ObjectNumber(void)
{
	ball = Sprite::create("GuiGame/Merge/2.png");
	addChild(ball);
	setContentSize(ball->getContentSize());

	border = Sprite::create("GuiGame/Merge/level8.png");
	addChild(border);
	border->setScale(0.7);

	label = Text::create("SCORE", "fonts/tahomabd.ttf", 40);
	addChild(label);
	label->enableOutline(Color4B(115, 37, 31, 255), 2);

	//eff = DBFactory::getInstance()->buildArmatureNode("Oqua");
	//eff = DBFactory::getInstance()->buildArmatureNode("eff_button_daily_gift");
	//if (eff) {
	//	this->addChild(eff);
	//	eff->setVisible(false);
	//	//eff->setPositionY(-5);
	//	//eff->setScaleX(1.8);
	//	//eff->setScaleY(2.0);

	//	eff->setScaleX(0.7);
	//	eff->setScaleY(0.75);
	//}

	//eff1 = DBFactory::getInstance()->buildArmatureNode("Oqua");
	//if (eff1) {
	//	this->addChild(eff1);
	//	eff1->setVisible(false);
	//	eff1->setPositionY(-5);
	//	eff1->setScaleX(1.8);
	//	eff1->setScaleY(2.0);
	//}

	setNumber(0);
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}


void ObjectNumber::setRootPosition()
{
	rootX = getPositionX();
	rootY = getPositionY();
}

void ObjectNumber::resetPosition()
{
	setPositionX(rootX);
	setPositionY(rootY);
}

void ObjectNumber::setNumber(int number)
{
	setVisible(true);
	setAvailable(true);
	this->number = number;
	label->setString(GameUtility::toString(number).c_str());
	std::string s = "GuiGame/Merge/" + GameUtility::toString(number % 16) + ".png";
	//s = "GuiGame/2.png";
	ball->setTexture(s.c_str());
	//ball->setColor(GameUtility::getColorMerge(number));

	if (number >= 10) {
		border->setVisible(true);
		ball->setVisible(false);
		s = "GuiGame/Merge/level" + GameUtility::toString(number % 10 + 1) + ".png";
		border->setTexture(s);
		//label->enableOutline(Color4B(115, 37, 31, 255), 1);
		
	}
	else {
		border->setVisible(false);
		//label->disableEffect();
		ball->setVisible(true);
	}
}


void ObjectNumber::increaseNumber(int num)
{
	number = number + num;
	setNumber(number);
	playEffect();
	//JNIUtils::vibrate();
}


bool ObjectNumber::isEffect()
{
    return false;
	//return eff->isVisible();
}

void ObjectNumber::playEffect()
{
	//eff->setVisible(true);
	//eff->setOpacity(0);
	//eff->runAction(
	//	Sequence::create(
	//		DelayTime::create(0.1),
	//		FadeIn::create(0.1),
	//		NULL
	//	)
	//);

	////eff->gotoAndPlay("1", 0.1, -1, 1);
	//eff->gotoAndPlay("vienkhung", 0.1, 0.7, 1);
	//eff->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
	//	armature->setVisible(false);
	//});

	//eff1->setVisible(true);
	//eff1->setOpacity(0);
	//eff1->runAction(
	//	Sequence::create(
	//		DelayTime::create(0.1),
	//		FadeIn::create(0.1),
	//		NULL
	//	)
	//);
	//eff1->gotoAndPlay("1", 0.1, -1, 1);
	//eff1->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
	//	armature->setVisible(false);
	//});
}

void ObjectNumber::callback1()
{
	label->runAction(
		Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.4, 0)),
			CallFunc::create(AX_CALLBACK_0(ObjectNumber::callback2, this)),
			NULL
		)
	);
}

void ObjectNumber::callback2()
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

bool ObjectNumber::checkSame(int _number)
{
	return number == _number;
}

void ObjectNumber::moveDown(float time)
{
	stopAllActions();
	runAction(Sequence::create(
		MoveTo::create(time, Vec2(rootX, rootY)),
		CallFunc::create(AX_CALLBACK_0(ObjectNumber::callbackMoveDown, this)),
		NULL
	));
	runAction(
		Sequence::create(
			ScaleTo::create(time * 0.4, 1.2, 0.5),
			EaseBounceOut::create(ScaleTo::create(time * 2.0, 1, 1)),
			NULL
		)
	);
}

void ObjectNumber::callbackMoveDown()
{
	//setIsIdle(true);
}

void ObjectNumber::moveToEat(float time, Vec2 pos)
{
	stopAllActions();
	runAction(Sequence::create(
		MoveTo::create(time, pos),
		CallFunc::create(AX_CALLBACK_0(ObjectNumber::callbackMoveEat, this)),
		NULL
	));
	setAvailable(false);
}

void ObjectNumber::callbackMoveEat()
{
	setVisible(false);
}

ObjectNumber::~ObjectNumber(void)
{
}

void ObjectNumber::effectNewGame()
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

void ObjectNumber::effectEndGame()
{
	float pX = 5 * (0.5 - GameUtility::getRandom()) + rootX;
	float pY = 5 * (0.5 - GameUtility::getRandom()) + rootY;
	runAction(Sequence::create(
		MoveTo::create(0.02 + GameUtility::getRandom() * 0.08, Vec2(pX, pY)),
		CallFunc::create(AX_CALLBACK_0(ObjectNumber::effectEndGame, this)),
		NULL
	));

}
