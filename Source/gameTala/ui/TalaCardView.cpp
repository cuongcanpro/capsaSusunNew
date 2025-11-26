#include "TalaCardView.h"
#include "gameTala/data/TalaGameConstant.h"
#include "app/GameMgr.h"

TalaCardView * TalaCardView::create(int id)
{
	auto card = new TalaCardView();
	card->init(id);
	card->autorelease();
	return card;
}

TalaCardView::TalaCardView()
{
}

TalaCardView::~TalaCardView()
{
}

bool TalaCardView::init(int id)
{
	if (gameMgr->typeCard == 0)
		Sprite::initWithFile("cards/labai_52.png");
	else
		Sprite::initWithFile("cards/labai1_52.png");
	setID(id);
	setUp(false);
	setDark(false);

	arrow = Sprite::create("GameTala/arrow.png");
	arrow->setVisible(false);
	addChild(arrow);

	eatable = Sprite::create();
	eatable->setPosition(getContentSize().width / 2, getContentSize().height / 2 - 5);
	eatable->setVisible(false);
	eatable->setScale(1.35);
	addChild(eatable);

	eaten = Sprite::create();
	eaten->setPosition(getContentSize().width / 2, getContentSize().height / 2);
	eaten->setVisible(false);
	addChild(eaten);

	return true;
}

void TalaCardView::onEnter()
{
	Sprite::onEnter();

	auto anim = Animation::create();
	for (int i = 0; i < 3; i++)
		anim->addSpriteFrameWithFile("GameTala/animation/eatable/eat_" + to_string(i) + ".png");
	anim->setDelayPerUnit(0.1);
	eatable->runAction(RepeatForever::create(Animate::create(anim)));

	anim = Animation::create();
	for (int i = 0; i < 4; i++)
		anim->addSpriteFrameWithFile("GameTala/animation/eaten/eaten_" + to_string(i) + ".png");
	anim->setDelayPerUnit(0.1);
	eaten->runAction(RepeatForever::create(Animate::create(anim)));

	arrow->stopAllActions();
	arrow->setPosition(getContentSize().width / 2, getContentSize().height + 15);
	arrow->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(0.2, { 0, 15 }),
		MoveBy::create(0.2, { 0, -15 }),
		nullptr
	)));
}

string TalaCardView::getCardResource(int id)
{
	if (id < 0 || id > NUM_CARD) return "";
	int convertId = id < 4 ? id + 48 : id - 4;
	if (id != NUM_CARD) {
		if (gameMgr->typeCard <= 0)
			return "cards/labai_" + to_string(convertId) + ".png";
		else
			return "cards/labai1_" + to_string(convertId) + ".png";
	}
	else { 
		if (gameMgr->typeCard <= 0)
			return "cards/labai_52.png"; 
		else
			return "cards/labai1_52.png";
	}
}

void TalaCardView::setID(int id)
{
	this->id = id;
	//this->setTexture(TextureCache::getInstance()->addImage(getCardResource(id)));
    this->setTexture(getCardResource(id));
}

void TalaCardView::setUp(bool up, bool animate)
{
	isUp = up;
	auto newY = isUp ? START_Y + OFFSET_Y : START_Y;
	stopActionByTag(UP_ACTION_TAG);
	if (animate) {
		auto action = MoveTo::create(0.05, { this->getPositionX(), newY });
		action->setTag(UP_ACTION_TAG);
		runAction(action);
	}
	else setPositionY(newY);
}

void TalaCardView::setDark(bool dark, bool animate)
{
	isDark = dark;
	auto newColor = isDark ? Color3B(100, 100, 100) : Color3B::WHITE;
	stopActionByTag(DARK_ACTION_TAG);
	if (animate) {
		auto action = TintTo::create(0.05, newColor);
		action->setTag(DARK_ACTION_TAG);
		runAction(action);
	}
	else setColor(newColor);
}

void TalaCardView::showArrow(bool show)
{
	arrow->setVisible(show);
	arrow->stopAllActions();
	if (show) {
		arrow->setPosition(getContentSize().width / 2, getContentSize().height + 15);
		arrow->runAction(RepeatForever::create(Sequence::create(
			MoveBy::create(0.2, { 0, 15 }),
			MoveBy::create(0.2, { 0, -15 }),
			nullptr
		)));
	}
}

void TalaCardView::showEatable(bool show)
{
	eatable->setVisible(show);
}

void TalaCardView::showEaten(bool show)
{
	eaten->setVisible(show);
}

void TalaCardView::effectClear()
{
	showEatable(false);
	showEaten(false);
	showArrow(false);
	/*

	vx = CCRANDOM_MINUS1_1() * 1000;
	vy = 400 + CCRANDOM_0_1() * 400;
	a = -4000 * getScale();
	turnSpeed = (720 + CCRANDOM_0_1() * 360) * (CCRANDOM_0_1() < 0.5 ? 1 : -1);
	scheduleUpdate();

	stopAllActions();*/
	setDark(true, true);
	runAction(Sequence::create(
		Spawn::create(
			FadeOut::create(1),
			ScaleTo::create(1, TalaCardView::SMALL_SCALE),
			nullptr
		),
		RemoveSelf::create(),
		nullptr
	));
}

void TalaCardView::update(float dt) 
{
	setPositionX(getPositionX() + vx * dt);
	setPositionY(getPositionY() + (vy = vy + a * dt) * dt);
	auto size = getContentSize();
	if (getPositionY() < 0 && getPositionY() * getPositionY() > (size.width * size.width + size.height * size.height) / 4) {
		unscheduleUpdate();
		removeFromParent();
		return;
	}
	setRotation(getRotation() + turnSpeed * dt);
}

bool TalaCardView::containTouchPoint(Point point)
{
	Size size = this->getContentSize();
	auto localPoint = this->convertToNodeSpace(point);
	return localPoint.x >= 0 && localPoint.x < size.width && localPoint.y >= 0 && localPoint.y < size.height;
}

Point TalaCardView::calculateAnchorPoint(Point point)
{
	Size size = this->getContentSize();
	auto localPoint = this->convertToNodeSpace(point);
	if (localPoint.x >= 0 && localPoint.x < size.width && localPoint.y >= 0 && localPoint.y < size.height)
		return { localPoint.x / size.width, localPoint.y / size.height };
	else return { -1, -1 };
}

Point TalaCardView::calculateNewPositionWithNewAnchor(Point anchor)
{
	float x = this->getPositionX() + (-this->getAnchorPoint().x + anchor.x)* this->getContentSize().width;
	float y = this->getPositionY() + (-this->getAnchorPoint().y + anchor.y)* this->getContentSize().height;

	return { x, y };
}

float TalaCardView::SMALL_SCALE = 0.66;
float TalaCardView::START_Y = 0;
const float TalaCardView::OFFSET_Y = 15;
const int TalaCardView::UP_ACTION_TAG = 100;
const int TalaCardView::DARK_ACTION_TAG = 200;
