#include "GroupNewNumber.h"
#include <cmath>  
#include <string>
#include "Game/Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"
#include "Game/Utility/GameSound.h"
#include "Game/GUIManager.h"


GroupNewNumber::GroupNewNumber(void)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	layerColor = LayerColor::create(Color4B(0, 0, 0, 200), size.width, size.height);
	addChild(layerColor);
	layerColor->setContentSize(size);
	layerColor->setVisible(true);
	layerColor->setOpacity(0);

	/*starFly = new StarFly(size.width, size.height * 0.6);
	addChild(starFly);
	starFly->setPosition(0, size.height * 0.3);*/

	paperLeft = new Paper(size.width * 0.5, 300, 1, 1);
	addChild(paperLeft);
	paperLeft->setPosition(0, size.height * 0.45);
	//paperLeft->startEffect();
	paperLeft->setLocalZOrder(4);

	paperRight = new Paper(size.width * 0.5, 300, -1, 1);
	addChild(paperRight);
	paperRight->setPosition(size.width, size.height * 0.45);
	//paperRight->startEffect();
	paperRight->setLocalZOrder(4);

	Vec2 pos = Vec2(size.width * 0.5, size.height * 0.65);
	/*eff = DBFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setPosition(pos);
	}

	eff1 = DBFactory::getInstance()->buildArmatureNode("cast_skill_vua_le_hoi");
	if (eff1) {
		this->addChild(eff1);
		eff1->setPosition(pos.x, pos.y + 50);
	}*/

	newNumber = new ObjectNumber();
	addChild(newNumber);
	newNumber->setVisible(true);

	btnOk = Button::create("GuiGame/btnOk.png", "GuiGame/btnOk.png", "GuiGame/btnOk.png");
	addChild(btnOk);
	btnOk->setPosition(Vec2(size.width * 0.5, size.height * 0.35));
	btnOk->addClickEventListener([this](Object* sender)
	{
		btnOk->runAction(ScaleTo::create(0.5, 0));
		newNumber->runAction(Spawn::create(
			EaseBackIn::create(ScaleTo::create(0.4, 0)),
			FadeOut::create(0.5),
			NULL
		));

		layerColor->runAction(
			FadeOut::create(0.5)
		);

		this->runAction(
			Sequence::create(
				DelayTime::create(0.5),
				Hide::create(),
				NULL
			)
		);
		GUIManager::getInstance().guiMerge->resumeGame();
	});

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

GroupNewNumber::~GroupNewNumber(void)
{

}

void GroupNewNumber::showNewNumber(int number, Vec2 pos, float scale)
{
	if (isVisible())
		return;
	setOpacity(255);
	setVisible(true);
	GameSound::playLevelUp();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	layerColor->setVisible(true);
	layerColor->setOpacity(0);
	layerColor->stopAllActions();
	layerColor->runAction(Sequence::create(
		EaseIn::create(FadeTo::create(0.5, 200), 2),
		DelayTime::create(1.8),
		NULL
	));

	/*if (eff) {
		eff->setVisible(true);
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->setVisible(false);
		});
	}

	if (eff1) {
		eff1->setVisible(true);
		eff1->gotoAndPlay("run", 0.5, -1, 1);
		eff1->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->setVisible(false);
		});
	}*/

	newNumber->setVisible(true);
	newNumber->setNumber(number);
	newNumber->setPosition(pos);
	newNumber->setScale(scale);
	newNumber->setOpacity(255);
	newNumber->runAction(
		Sequence::create(
			Spawn::create(
				EaseOut::create(ScaleTo::create(0.4, 2), 2),
				EaseOut::create(MoveTo::create(0.4, Vec2(size.width * 0.5, size.height * 0.65)), 2),
				NULL
			),
            Spawn::create(RotateTo::create(0.4, Vec3(0, -20, 0)), MoveBy::create(0.4, Vec2(-5, 0)), NULL),
            Spawn::create(RotateTo::create(0.4, Vec3(10, 20, 0)), MoveBy::create(0.4, Vec2(10, 0)), NULL),
            Spawn::create(RotateTo::create(0.4, Vec3(0, 0, 0)), MoveBy::create(0.4, Vec2(-5, 0)), NULL),
			NULL
		)
	);
	paperRight->startEffect();
	paperLeft->startEffect();

	btnOk->setVisible(true);
	btnOk->setScale(1);
	btnOk->setOpacity(0);
	btnOk->runAction(
		Sequence::create(
			DelayTime::create(3.5),
			CallFunc::create(AX_CALLBACK_0(GroupNewNumber::callbackShowNew, this)),
			FadeIn::create(0.5),
			NULL
		)
	);

	//starFly->setVisible(true);
//	starFly->startEffect();
}

void GroupNewNumber::callbackShowNew()
{
	//if (newNumber->getNumber() % 2 == 0)
		//JNIUtils::showAdsFull();
}
