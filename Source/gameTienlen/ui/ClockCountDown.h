#ifndef _ClockCountDown_h__
#define _ClockCountDown_h__

#include "axmol.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ax::ui;
typedef std::function<void()> ClockListener;
class ClockCountDown : public Node
{
public:
	ClockCountDown(void);
	~ClockCountDown(void);
	void onEnterFinish();
	void update(float delta);
	void setPause(bool value);
	void setTime(int time);
	void convertTime(int time);
	void setPlayTime(bool play);
	void setCallback(const ClockListener& _callback);
	virtual void callbackTimeOut();
	virtual std::string getResource(int number);
	ClockListener callback;
protected:
	Sprite *arrayImage[2];
	int standardTime;
	double targetTime;
	bool pause;
	float pad;
	bool playTime;
	Text* lbTime;
};

class ClockGame : public ClockCountDown
{
public:
	ClockGame();
	~ClockGame();
	std::string getResource(int number);
private:
};
#endif

