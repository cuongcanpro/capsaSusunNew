#include "CellBlock.h"
#include "../Utility/GameUtility.h"
#include "../../Engine/GlobalVar.h"
#include "Game/GUIManager.h"


CellBlock::CellBlock(void): Node()
{
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
	isVibrate = false;
	idBonus = CellBonus::NONE;
	bg = ImageView::create();
	bg->loadTexture("GuiGame/gameBlockPuzzel/cell_0.png");
	addChild(bg);
	setContentSize(bg->getContentSize());

	iconBonus = ImageView::create();
	iconBonus->loadTexture("GuiGame/gameBlockPuzzel/iconX3.png");
	//iconBonus->setPosition(Vec2(getWidth() * 0.5, getHeight() * 0.5));
	iconBonus->setVisible(false);
	addChild(iconBonus);

	GameImage* bgNum = new GameImage("gameBlockPuzzel/bgNumber.png");
	bgNum->setOpacity(100);
	iconBonus->addChild(bgNum);
	bgNum->setPosition(Vec2(iconBonus->getContentSize().width * 0.2, iconBonus->getContentSize().height * 0.25));

	lbNum = Text::create("BEST", "fonts/tahomabd.ttf", 20);
	iconBonus->addChild(lbNum);
	lbNum->enableOutline(Color4B(115, 37, 31, 255), 1);
	lbNum->setPosition(Vec2(iconBonus->getContentSize().width * 0.2, iconBonus->getContentSize().height * 0.25));
}

CellBlock::~CellBlock(void)
{
}

void CellBlock::doVibrate(bool vibrate)
{
	if (vibrate) {
		if (isVibrate)
			return;
		isVibrate = true;
		runAction(Sequence::create(
			DelayTime::create(GameUtility::getRandom() * 0.3),
			CallFunc::create(AX_CALLBACK_0(CellBlock::callbackVibrate, this)),
			NULL
		));
	}
	else {
		isVibrate = false;
		setRotation(0);
		stopAllActions();
	}
}

void CellBlock::callbackVibrate()
{
	runAction(RepeatForever::create(
		Sequence::create(
			RotateTo::create(0.05, 10),
			RotateTo::create(0.1, -10),
			RotateTo::create(0.05, 0),
			NULL
		)
	));
}

void CellBlock::setBg(int id)
{
	bg->loadTexture(GameUtility::getTextureCell(id));
}

void CellBlock::setBonus(CellBonus idBonus, int num)
{
	this->idBonus = idBonus;
	switch (idBonus)
	{
	case NONE:
		if (iconBonus->isVisible()) {
			iconBonus->runAction(Sequence::create(
				EaseBackIn::create(ScaleTo::create(0.5, 0)),
				Hide::create(),
				NULL
			));
		}
		return;
		break;
	case X2:
		iconBonus->loadTexture("GuiGame/gameBlockPuzzel/iconX3.png");
		break;
	case BOMB:
		iconBonus->loadTexture("GuiGame/gameBlockPuzzel/iconBomb.png");
		break;
	case EXCHANGE:
		iconBonus->loadTexture("GuiGame/gameBlockPuzzel/iconExchange.png");
		break;
	case EXTRA:
		iconBonus->loadTexture("GuiGame/gameBlockPuzzel/iconExtra.png");
		break;
	default:
		break;
	}
	if (num > 0) {
		this->num = num;
		lbNum->setString(GameUtility::toString(num));
	}
	iconBonus->setVisible(true);
	iconBonus->setScale(0);
	iconBonus->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
}

void CellBlock::decreaseBonus()
{
	if (idBonus != NONE) {
		this->num--;
		lbNum->setString(GameUtility::toString(num));
	}
	if (this->num <= 0) {
		this->setBonus(CellBonus::NONE);
	}
}

void CellBlock::setWidth(float widthValue)
{
	float scale = widthValue / getContentSize().width;
	this->setScaleX(scale);
}

void CellBlock::setHeight(float heightValue)
{
	float scale = heightValue / getContentSize().height;
	this->setScaleY(scale);
}

float CellBlock::getWidth()
{
	return getContentSize().width;
}

float CellBlock::getHeight()
{
	return getContentSize().height;
}

float CellBlock::getRealWidth()
{
	return getWidth() * getScaleX();
}

float CellBlock::getRealHeight()
{
	return getHeight() * getScaleY();
}

void CellBlock::endGame(float time)
{
	runAction(Sequence::create(
		DelayTime::create(time),
		CallFunc::create(AX_CALLBACK_0(CellBlock::callbackEndGame, this)),
		NULL
	));
}

void CellBlock::callbackEndGame()
{
	((Scale9Sprite*)bg->getVirtualRenderer())->setState(Scale9Sprite::State::GRAY);
}

void CellBlock::newGame()
{
	stopAllActions();
	setRotation(0);
	setColor(Color3B(255, 255, 255));
	((Scale9Sprite*)bg->getVirtualRenderer())->setState(Scale9Sprite::State::NORMAL);
	setBonus(CellBonus::NONE);
}

void CellBlock::doVibrateNTime(int n)
{
	runAction(Repeat::create(
		Sequence::create(
			RotateTo::create(0.05, 10),
			RotateTo::create(0.1, -10),
			RotateTo::create(0.05, 0),
			NULL
		)
	, n));
}
