#include "ImageEffect.h"

ImageEffect::ImageEffect()
{
}

ImageEffect::~ImageEffect()
{
}

ImageEffect * ImageEffect::create()
{
	ImageEffect* coin = new ImageEffect();
	coin->initAnim();
	//coin->autorelease();
	return coin;
}

void ImageEffect::initAnim() {
	//loadTexture("common/coinFake.png");
	initWithFile("GuiGame/balls/lineBall_0_0.png");
	amoutLoop = 0;
	//setScale(ImageEffect::SCALE_CHIP_RATE);
	setVisible(false);
}

void ImageEffect::initState() {
	setVisible(true);
}

void ImageEffect::initCoin(int type, int amoutLoopRun, float posX, float posY) {
	isCollided = false; //kiem tra da cham dat 1 lan chua
	//opacity = 0;
	amoutLoop = amoutLoopRun;
	float valueRan;
	if (type == ImageEffect::TYPE_FLOW) {
		speedX = 2 * AXRANDOM_0_1() * ImageEffect::RATE_SPEED_X - ImageEffect::RATE_SPEED_X;
		//speedY = AXRANDOM_0_1() * ImageEffect::RATE_SPEED_Y + ImageEffect::DEFAULT_SPEED_Y;
                auto def = AXRANDOM_0_1() * 800 + 800;
		speedY = sqrt(def * def - speedX * speedX);
		speedR = 2 * AXRANDOM_0_1() * ImageEffect::RATE_SPEED_R - ImageEffect::RATE_SPEED_R;
		valueRan = AXRANDOM_0_1() * (ImageEffect::MAX_SCALE - ImageEffect::MIN_SCALE) + ImageEffect::MIN_SCALE;
		//this->setScale(valueRan, valueRan);
	//	setRotation(AXRANDOM_0_1() * 360);
		this->setPosition(posX, posY);
	}
	else if (type == ImageEffect::TYPE_RAIN) {
		speedX = 0;
            speedY   = AXRANDOM_0_1() * ImageEffect::RATE_SPEED_X;
                speedR   = 2 * AXRANDOM_0_1() * ImageEffect::RATE_SPEED_R - ImageEffect::RATE_SPEED_R;
            valueRan   = AXRANDOM_0_1() * (ImageEffect::MAX_SCALE - ImageEffect::MIN_SCALE) + ImageEffect::MIN_SCALE;
		this->setScale(valueRan, valueRan);
		setRotation(AXRANDOM_0_1() * 360);
		auto parent = getParent();
		this->setPosition(Vec2(AXRANDOM_0_1() * parent->getContentSize().width, parent->getContentSize().height + getContentSize().height + AXRANDOM_0_1() * ImageEffect::RATE_Position_Y));
	}
	//this->setVisible(false);
}

void ImageEffect::start() {
	setVisible(true);
}

void ImageEffect::stop() {
	setVisible(false);
	stopAllActions();
}

void ImageEffect::repeat() {
	if (amoutLoop <= 0) {
		stop();
	}
	else {
		amoutLoop -= 1;
		isCollided = false;
		speedX = 0;
		speedY = AXRANDOM_0_1() * ImageEffect::RATE_SPEED_X;
		speedR = 2 * AXRANDOM_0_1() * ImageEffect::RATE_SPEED_R - ImageEffect::RATE_SPEED_R;
		//valueRan = AXRANDOM_0_1() * (ImageEffect::MAX_SCALE - ImageEffect::MIN_SCALE) + ImageEffect::MIN_SCALE;
		//this->setScale(valueRan, valueRan);
		setRotation(AXRANDOM_0_1() * 360);
		auto parent = getParent();
		this->setPosition(Vec2(AXRANDOM_0_1() * parent->getContentSize().width, parent->getContentSize().height + getContentSize().height + AXRANDOM_0_1() * ImageEffect::RATE_Position_Y));
	}
}

void ImageEffect::updateCoin(float dt) {
	auto opa = opacity;
	opa += 1500 * dt;
	if (opa > 255) opacity = 255;
	else opacity = opa;
	setPositionX(getPositionX() + speedX * dt);
	setPositionY(getPositionY() + speedY * dt);
	speedY -= ImageEffect::GRAVITY * dt;
	setRotation(getRotation() + speedR);
	//cham dat thi cho nhay len 1 lan roi roi tiep
	if (getPositionY() < getContentSize().height / 2 && !isCollided) {
		isCollided = true;
		speedY = -speedY * (AXRANDOM_0_1() * ImageEffect::RATE_JUMP_BACK);
		speedX = 0;
	}
	else if (getPositionY() + (getContentSize().height * getScale()) < 0 && isCollided) {
		repeat();
	}
}

const float ImageEffect::SCALE_CHIP_RATE = 0.35f;
const int ImageEffect::NUM_SPRITE_ANIMATION_COIN = 5;
const std::string ImageEffect::NAME_ANIMATION_COIN = "gold";
const float ImageEffect::TIME_ANIMATION_COIN = 0.3f;
const float ImageEffect::TYPE_FLOW = 0;
const float ImageEffect::TYPE_RAIN = 0;

const float ImageEffect::RATE_SPEED_Y = 600;
const float ImageEffect::DEFAULT_SPEED_Y = 850;
const float ImageEffect::RATE_SPEED_X = 350;
const float ImageEffect::RATE_SPEED_R = 10;
const float ImageEffect::RATE_Position_X = 100;
const float ImageEffect::RATE_Position_Y = 1000;
const float ImageEffect::MIN_SCALE = 0.32f;
const float ImageEffect::MAX_SCALE = 0.42f;
const float ImageEffect::RATE_JUMP_BACK = 0.5f;
const float ImageEffect::GRAVITY = 2300;
const float ImageEffect::POSI = 90;
const float ImageEffect::NUM_COIN_EACH_TIME = 100;
const float ImageEffect::NUM_COIN_RATE_RAIN = 100;
const float ImageEffect::TIME_OUT_COIN = 0.05f;
const float ImageEffect::DELAY_PLAY_SOUND = 0.3f;
