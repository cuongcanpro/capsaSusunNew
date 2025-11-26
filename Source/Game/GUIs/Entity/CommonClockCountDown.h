#ifndef _CommonClockCountDown_h__
#define _CommonClockCountDown_h__

#include "axmol.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ax::ui;
typedef std::function<void()> ClockListener;
class CommonClockCountDown : public Node
{
public:
	CommonClockCountDown(void);
	~CommonClockCountDown(void);
	void onEnterFinish();
	void update(float delta);
	void setPause(bool value);
	void setTime(int time);
	float getTime();
	void convertTime(int time);
	void setPlayTime(bool play);
    Size getContentSize();
	void setCallback(const ClockListener& _callback);
	virtual void callbackTimeOut();
	ClockListener callback;
    bool isPause();

protected:
	Text* lbTime;
    Sprite* bgClock;
	int standardTime;
	double targetTime;
	bool pause;
	float pad;
	bool playTime;
	bool arrayCountDown[10];
};

#endif

