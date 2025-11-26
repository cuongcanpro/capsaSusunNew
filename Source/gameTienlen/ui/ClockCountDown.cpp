#include "ClockCountDown.h"
#include "string"
#include <ctime>
#include <chrono>
#include "app/Constant.h"
using namespace std::chrono;
#define NUMBER_RES "table/start_"

using namespace std;

ClockCountDown::ClockCountDown(void)
{
	//	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	lbTime = Text::create("10", FONT_BOLD, 30);
	lbTime->setTextColor(Color4B(247, 161, 12, 255));
	lbTime->enableOutline(Color4B(10, 10, 10, 255), 1);
	addChild(lbTime);
	lbTime->setLocalZOrder(11);

	arrayImage[0] = Sprite::create(getResource(0));
	addChild(arrayImage[0]);
	arrayImage[0]->setPositionX(-arrayImage[0]->getContentSize().width * 0.48);
	arrayImage[0]->setPositionY(-2);

	arrayImage[1] = Sprite::create(getResource(0));
	addChild(arrayImage[1]);
	arrayImage[1]->setPositionX(arrayImage[1]->getContentSize().width * 0.48);
	arrayImage[1]->setPositionY(-2);

	//arrayImage[0]->setPosition(size.width / 2, size.height / 2);
	//arrayImage[1]->setPosition(size.width / 2, size.height / 2);

	setVisible(true);
	pause = false;
	pad = arrayImage[0]->getContentSize().width * 0.5f;
	setContentSize(Size(arrayImage[0]->getContentSize().width * 2.2f, arrayImage[0]->getContentSize().height));
	playTime = false;
	schedule(AX_SCHEDULE_SELECTOR(ClockCountDown::update), 1);
	callback = nullptr;
}

ClockCountDown::~ClockCountDown(void)
{
}

void ClockCountDown::onEnterFinish()
{
    schedule(AX_SCHEDULE_SELECTOR(ClockCountDown::update), 1);
}

void ClockCountDown::setPlayTime(bool play)
{
	playTime = play;
}


void ClockCountDown::setCallback(const ClockListener& _callback)
{
	callback = _callback;
}

void ClockCountDown::callbackTimeOut()
{
	if (callback) {
		callback();
	}
}

std::string ClockCountDown::getResource(int number)
{
	std::string content = "bosonew/";
	content = content + std::to_string(number);
	content = content + ".png";
	return content;
}

void ClockCountDown::update(float delta)
{
	if (!isVisible())
		return;
	if (!pause) {
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		int remainTime = round((targetTime - ms.count()) / 1000);
		if (remainTime >= 0) {
			convertTime(remainTime);
			if (remainTime < 20) {
			//	TienlenGameSound::playSoundCountDown();
			}
		}
		else {
			callbackTimeOut();
			setPause(true);
		}
	}
}

void ClockCountDown::setPause(bool value)
{
	setVisible(!value);
	pause = value;
}

void ClockCountDown::setTime(int time)
{
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	AXLOGD("SET TIME %i ", time);
	targetTime = time * 1000 + ms.count();
	schedule(AX_SCHEDULE_SELECTOR(ClockCountDown::update), 1);
	convertTime(time);
	setPause(false);
}

void ClockCountDown::convertTime(int convertTime)
{
	if (convertTime < 0)
		convertTime = 0;
	if (convertTime >= 100) {
		convertTime = 99;
	}
	lbTime->setString(to_string(convertTime));
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	int time = convertTime;
	int number = 0;
	int count = 0;
	while (time > 0)
	{
		number = time % 10;
		std::string content = getResource(number);
		arrayImage[count]->setTexture(content.c_str());
		time = time / 10;
		count++;
		if (count == 2) {
			break;
		}
	}

	if (count == 2)
	{
		arrayImage[1]->setVisible(true);
		arrayImage[1]->setPositionX(-arrayImage[1]->getContentSize().width * 0.5);
		arrayImage[0]->setPositionX(arrayImage[0]->getContentSize().width * 0.5);
	}
	else
	{
		arrayImage[1]->setVisible(false);
		arrayImage[0]->setPosition(0, 0);
	}
	arrayImage[0]->setVisible(false);
	arrayImage[1]->setVisible(false);
}

ClockGame::ClockGame() : ClockCountDown()
{
	Sprite* bgClock = Sprite::create("Game/bgClock.png");
	addChild(bgClock);
	//	bgClock->setPosition(bgClock->getContentSize().width * 0.5, bgClock->getContentSize().height * 0.5);
	arrayImage[0]->setLocalZOrder(1);
	arrayImage[1]->setLocalZOrder(1);
	setContentSize(bgClock->getContentSize());
	arrayImage[0]->setScale(0.8);
	arrayImage[1]->setScale(0.8);
}

ClockGame::~ClockGame()
{
	//setScale(0.8);
}

std::string ClockGame::getResource(int number)
{
	std::string content = "Game/start_";
	content = "bosonew/";
	content = content + std::to_string(number);
	content = content + ".png";
	return content;
}
