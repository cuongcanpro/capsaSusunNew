#pragma once
#ifndef BinhHelpGUI_h__
#define BinhHelpGUI_h__
#include "core/gui/BaseLayer.h"


using namespace std;
using namespace ax::extension;

class BinhHelpGUI : public BaseLayer
{
public:
	CREATE_FUNC(BinhHelpGUI);
	BinhHelpGUI(void);
	~BinhHelpGUI(void);
	bool init();
public:
	ImageView *bg;
	ImageView* iconHand;
	void initGUI();
	void backKeyPress();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	static std::string className;
};
#endif // BinhHelpGUI_h__

