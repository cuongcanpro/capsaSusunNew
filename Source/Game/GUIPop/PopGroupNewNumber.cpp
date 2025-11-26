#include "PopGroupNewNumber.h"
#include <cmath>  
#include <string>
#include "../Utility/GameUtility.h"
#include "Game/Utility/JNIUtils.h"
#include "Game/Utility/GameSound.h"
#include "Game/GUIManager.h"
#include "../../Engine/GlobalVar.h"

PopGroupNewNumber::PopGroupNewNumber(void)
{
    Size size  = Director::getInstance()->getRenderView()->getVisibleSize();
	layerColor = LayerColor::create(Color4B(0, 0, 0, 200), size.width, size.height);
	addChild(layerColor);
	layerColor->setContentSize(size);
	layerColor->setVisible(true);
	layerColor->setOpacity(0);

	imgCongrat = Sprite::create("GuiGame/iconCongrat.png");
	addChild(imgCongrat);
	imgCongrat->setPosition(0, size.height * 0.8);

	//starFly = new StarFly(size.width, size.height * 0.6);
	//addChild(starFly);
	//starFly->setPosition(0, size.height * 0.3);

	paperLeft = new Paper(size.width * 0.5, 450, 1, 1);
	addChild(paperLeft);
	paperLeft->setPosition(0, size.height * 0.45);
	//paperLeft->startEffect();
	paperLeft->setLocalZOrder(4);

	paperRight = new Paper(size.width * 0.5, 450, -1, 1);
	addChild(paperRight);
	paperRight->setPosition(size.width, size.height * 0.45);
	//paperRight->startEffect();
	paperRight->setLocalZOrder(4);


	newNumber = new PopObjectNumber();
	addChild(newNumber);
	newNumber->setVisible(true);
	newNumber->setNewNumber();

	lbCongrat = Text::create("You have just unlocked number 10", "fonts/tahomabd.ttf", 25);
	lbCongrat->enableOutline(Color4B(50, 10, 0, 255), 2);
	addChild(lbCongrat, 10);
	lbCongrat->setPosition(Vec2(size.width * 0.5, size.height * 0.3));

	btnOk = Button::create("GuiGame/btnOk.png", "GuiGame/btnOk.png", "GuiGame/btnOk.png");
	addChild(btnOk);
	btnOk->setPosition(Vec2(size.width * 0.5, lbCongrat->getPositionY() - btnOk->getContentSize().height * 1.2));
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
		lbCongrat->runAction(FadeOut::create(0.5));
		imgCongrat->runAction(FadeOut::create(0.5));
        GUIManager::getInstance().guiPop->addBomb(2);
		GUIManager::getInstance().guiPop->updatePosCenter();
	});

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);

    auto effect = efk::Effect::create("TestEffect/firework.efk", 20.0f);
    if (effect != nullptr)
    {
        effFirework = efk::EffectEmitter::create(game->manager);
        effFirework->setEffect(effect);
        effFirework->setPlayOnEnter(false);
        effFirework->setRemoveOnStop(false);

        effFirework->setRotation3D(ax::Vec3(0, 90, 0));
        effFirework->setPosition(Vec2(size.width * 0.5, size.height * 0.2));

        // emitter->setScale(13);
        this->addChild(effFirework, 2);
    }
}

PopGroupNewNumber::~PopGroupNewNumber(void)
{

}

void PopGroupNewNumber::showNewNumber(int number, Vec2 pos, float scale)
{
	if (isVisible())
		return;
        Size size     = Director::getInstance()->getRenderView()->getVisibleSize();
	float centerY = size.height * 0.6;
	lbCongrat->setString("You have just unlocked number " + to_string(number));
	lbCongrat->setOpacity(0);
	lbCongrat->setPosition(Vec2(size.width * 0.5, centerY - newNumber->getContentSize().height * 0.5 * 2 - lbCongrat->getContentSize().height * 2));
	lbCongrat->runAction(
		Sequence::create(
			DelayTime::create(2.0),
			FadeIn::create(0.5),
			NULL
		)
	);
	setOpacity(255);
	setVisible(true);
	GameSound::playNewNumber();
    GameSound::playFirework();
	
	layerColor->setVisible(true);
	layerColor->setOpacity(0);
	layerColor->stopAllActions();
	layerColor->runAction(Sequence::create(
		EaseIn::create(FadeTo::create(0.5, 200), 2),
		DelayTime::create(1.8),
		NULL
	));


	imgCongrat->setOpacity(0);
	imgCongrat->setPosition(size.width * 0.5, size.height + 200);
	imgCongrat->runAction(
		Sequence::create(
			DelayTime::create(2.0),
			Spawn::create(
				EaseBackOut::create(MoveTo::create(0.5, Vec2(size.width * 0.5, size.height * 0.6 + newNumber->getContentSize().height * 0.5 * 2 + imgCongrat->getContentSize().height * 0.7))),
				FadeIn::create(0.5),
				NULL
			),
			NULL
		)
	);

	newNumber->setVisible(true);
	newNumber->setNumber(number);
	newNumber->setPosition(pos);
	newNumber->setScale(scale);
	newNumber->setOpacity(255);
	newNumber->runAction(
		Sequence::create(
			Spawn::create(
				EaseOut::create(ScaleTo::create(0.4, 2), 2),
				EaseOut::create(MoveTo::create(0.4, Vec2(size.width * 0.5, size.height * 0.6)), 2),
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
	btnOk->setPositionY(lbCongrat->getPositionY() - btnOk->getContentSize().height * 1.5);
	btnOk->setScale(1);
	btnOk->setOpacity(0);
	btnOk->runAction(
		Sequence::create(
			DelayTime::create(3.5),
            CallFunc::create(AX_CALLBACK_0(PopGroupNewNumber::callbackShowNew, this)),
			FadeIn::create(0.5),
			NULL
		)
	);
    effFirework->setVisible(true);
    effFirework->play(1);
        //	starFly->setVisible(true);
	//starFly->startEffect();
}

void PopGroupNewNumber::callbackShowNew()
{
    if (newNumber->getNumber() % 2 == 0)
        game->showAdsFull();
}
