#include "CellBomb.h"
#include "../Utility/GameUtility.h"
#include "../GUIManager.h"


CellBomb::CellBomb(void)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = Scale9Sprite::createWithSpriteFrameName("bgNumber2.png");
	addChild(bg);
	bg->setContentSize(Size(80, 80));
	bg->setColor(Color3B(50, 50, 50));

	//loadTexture("btnSound.png");
	/*lbNum = Text::create("0", "fonts/tahomabd.ttf", 30);
	lbNum->enableOutline(ccc4(20, 100, 20, 255), 2);
	lbNum->setColor(Color3B(0, 255, 0));
	addChild(lbNum);*/

	lbNum = Sprite::createWithSpriteFrameName("num_1.png");
	this->addChild(lbNum);

	iconBomb = Sprite::createWithSpriteFrameName("iconBomb.png");
	addChild(iconBomb);
	
	bgMask = Scale9Sprite::createWithSpriteFrameName("bgMaskCell.png");
//	bgMask->setColor(Color3B(200, 200, 200));
	addChild(bgMask);
	bgMask->setContentSize(bg->getContentSize());

	icon = Sprite::createWithSpriteFrameName("iconFlag.png");
	addChild(icon);
	icon->setAnchorPoint(Vec2(0.5, 0));
	icon->setPosition(Vec2(0, -iconBomb->getContentSize().height * 0.5));

	iconWrong = Sprite::createWithSpriteFrameName("iconX.png");
	addChild(iconWrong);
}

CellBomb::~CellBomb(void)
{

}

void CellBomb::setState(CellDataState state, int num, float delayTime)
{
	iconWrong->setVisible(false);
	lbNum->setVisible(false);
	icon->setVisible(false);
	iconBomb->setVisible(false);
	//bgMask->setVisible(false);
	CellDataState oldState = cellState;
	switch (state)
	{
	case CELL_BOMB_REAL_OPEN:
		bg->setColor(Color3B(255, 0, 0));
		iconBomb->setVisible(true);
		bgMask->setVisible(false);
		break;
	case CELL_BOMB_REAL_CLOSE:
		bg->setColor(Color3B(150, 150, 150));
		iconBomb->setVisible(true);
		iconBomb->setScale(0);
		iconBomb->runAction(
			Sequence::create(
				DelayTime::create(delayTime),
				EaseBounceOut::create(ScaleTo::create(0.5, 1)),
				NULL
			)
		);
		hideMask(delayTime);
		break;
	case CELL_NOT_OPEN:
		bg->setColor(Color3B(75, 75, 75));
		showMask(delayTime);
		if (oldState == CELL_BOMB_GUESS) {
			icon->setVisible(true);
			icon->runAction(Sequence::create(
				EaseBackIn::create(ScaleTo::create(0.5, 1, 0)),
				Hide::create(),
				NULL
			));
		}
		break;
	case CELL_BOMB_GUESS:
		bg->setColor(Color3B(150, 150, 150));
		icon->setVisible(true);
		icon->setScale(1, 0);
		icon->runAction(
			EaseBackOut::create(ScaleTo::create(0.5, 1))
		);
		hideMask(delayTime);
		break;
	case CELL_OPEN:
		bg->setColor(Color3B(75, 75, 75));
		icon->setVisible(false);
		if (num > 0) {
			lbNum->setVisible(true);
			lbNum->setSpriteFrame("num_" + to_string(num) + ".png");
		}
		hideMask(delayTime);
		break;
	default:
		break;
	}
	cellState = state;
}

void CellBomb::showIconWrong()
{
	iconWrong->setVisible(true);
	iconWrong->setScale(5);
	iconWrong->runAction(EaseBounceOut::create(ScaleTo::create(0.5, 1)));
}

void CellBomb::hideMask(float delay)
{
	bgMask->runAction(Sequence::create(
		DelayTime::create(delay),
		Spawn::create(
			ScaleTo::create(0.2, 0),
			FadeOut::create(0.2),
			NULL
		),
		Hide::create(),
		NULL
	));
}

void CellBomb::showMask(float delay)
{
	bgMask->setVisible(true);
	bgMask->runAction(Sequence::create(
		DelayTime::create(delay),
		Spawn::create(
			ScaleTo::create(0.2, 1),
			FadeIn::create(0.2),
			NULL
		),
		NULL
	));
}

void CellBomb::effectVibrate()
{
	if (numVibrate >= 8)
		return;
	Vec2 pos = Vec2(4 - AXRANDOM_0_1() * 8, 4 - AXRANDOM_0_1() * 8);
	if (numVibrate == 7)
		pos = Vec2(0, 0);
	if (cellState == CELL_BOMB_GUESS) {
		pos.y = pos.y - icon->getContentSize().height * 0.5;
	}
	runAction(
		Sequence::create(
			DelayTime::create(0.05),
			CallFunc::create(AX_CALLBACK_0(CellBomb::effectVibrate, this)),
			NULL
		)
	);
	if (iconBomb->isVisible()) {
		iconBomb->runAction(MoveTo::create(0.05, pos));
	}
	if (icon->isVisible()) {
		icon->runAction(MoveTo::create(0.05, pos));
	}
	if (lbNum->isVisible()) {
		lbNum->runAction(MoveTo::create(0.05, pos));
	}
	numVibrate++;
}

void CellBomb::effectNoti()
{
	bgMask->stopAllActions();
	bgMask->runAction(
		Repeat::create(
		Sequence::create(
			ScaleTo::create(0.1, 0.8),
			ScaleTo::create(0.1, 1.0),
			NULL
		), 2)
	);
}

void CellBomb::effectNewGame(float delay)
{
	bgMask->stopAllActions();
	bgMask->setVisible(true);
	bgMask->setOpacity(0);
	bgMask->setScale(0);
	bgMask->runAction(
		Sequence::create(
			DelayTime::create(delay),
			Spawn::create(
				ScaleTo::create(0.2, 1),
				FadeIn::create(0.2),
				NULL
			),
			nullptr
		)
	);
}
