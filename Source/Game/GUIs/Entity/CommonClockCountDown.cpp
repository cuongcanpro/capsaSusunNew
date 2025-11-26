#include "CommonClockCountDown.h"
#include "string"
#include <ctime>
#include <chrono>
#include "Game/Utility/GameUtility.h"
#include "Game/Utility/GameSound.h"
using namespace std::chrono;

CommonClockCountDown::CommonClockCountDown(void)
{
	bgClock = Sprite::create("GuiGame/clock.png");
	addChild(bgClock);

	setVisible(true);
	pause = false;
	playTime = false;
//	schedule(schedule_selector(CommonClockCountDown::update), 1);
	callback = nullptr;

	lbTime = Text::create("0", "fonts/tahomabd.ttf", 25);
    lbTime->setColor(Color3B(240, 129, 130));
	lbTime->setAnchorPoint(Vec2(0.5, 0.5));
	lbTime->enableOutline(Color4B(20, 20, 20, 255), 1);
	lbTime->setTextHorizontalAlignment(TextHAlignment::CENTER);
    bgClock->addChild(lbTime);
	lbTime->setPosition(Vec2(bgClock->getContentSize().width * 0.5, bgClock->getContentSize().height * 0.45));
	//lbTime->setPosition(Vec2(bgProgress->getRealWidth() * 0.4, 0));

    
}

CommonClockCountDown::~CommonClockCountDown(void)
{
}

void CommonClockCountDown::onEnterFinish()
{
    this->schedule(
        [this](float dt) {
        // Add your task logic here
        this->update(dt);
    },
        1.0f, "one_time_task_key");
}

void CommonClockCountDown::setPlayTime(bool play)
{
	playTime = play;
}

Size CommonClockCountDown::getContentSize()
{
    return bgClock->getContentSize();
}


void CommonClockCountDown::setCallback(const ClockListener& _callback)
{
	callback = _callback;
}

void CommonClockCountDown::callbackTimeOut()
{
	if (callback) {
		callback();
	}
}

bool CommonClockCountDown::isPause()
{
    return pause;
}

void CommonClockCountDown::update(float delta)
{
	if (!isVisible())
		return;
	if(!pause) {
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		int remainTime = round((targetTime - ms.count()) / 1000);
		if(remainTime >= 0) {
			convertTime(remainTime);
			if(remainTime < 10) {
				//GameSound::playSoundCountDown();
				if (!arrayCountDown[remainTime]) {
					GameSound::playCountDown();
					arrayCountDown[remainTime] = true;
                    bgClock->runAction(
                        Spawn::create(
                            Sequence::create(
                                MoveTo::create(0.2, Vec2(0, 50)),
                                EaseBounceOut::create(MoveTo::create(0.5, Vec2(0, 0))),
                                NULL
                            ),
                            Sequence::create(
                                ScaleTo::create(0.2, 1, 1.2),
                                ScaleTo::create(0.2, 1, 0.6),
                                EaseBounceOut::create(ScaleTo::create(0.5, 1, 1)),
                                NULL
                            ),
                            NULL
                        )
                    );
				}
			}
		}
		else {
			callbackTimeOut();
			setPause(true);
		}
	}
}

void CommonClockCountDown::setPause(bool value)
{
	setVisible(!value);
	pause = value;
}

void CommonClockCountDown::setTime(int time)
{
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	AXLOGD("SET TIME %i ", time);
	targetTime = time * 1000 + ms.count();
	//schedule(schedule_selector(CommonClockCountDown::update),1);
	convertTime(time);
	setPause(false);
	for (int i = 0; i < 10; i++) {
		arrayCountDown[i] = false;
	}
}

float CommonClockCountDown::getTime()
{
	if (pause)
		return -1;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	float remainTime = round((targetTime - ms.count()) / 1000.0f);
	return remainTime;
}

void CommonClockCountDown::convertTime(int convertTime)
{
	if (convertTime < 0)
		convertTime = 0;
	lbTime->setString(GameUtility::toString(convertTime));
	lbTime->runAction(Sequence::create(
		ScaleTo::create(0.2, 1.2),
		EaseBounceOut::create(ScaleTo::create(0.5, 1.0)),
		NULL
	));
}
