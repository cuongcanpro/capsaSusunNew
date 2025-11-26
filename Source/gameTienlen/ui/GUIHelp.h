#pragma once
#ifndef GUIHelp_h__
#define GUIHelp_h__
#include "core/gui/BaseLayer.h"


using namespace std;
using namespace ax::extension;

class GUIHelp : public BaseLayer
{
public:
	CREATE_FUNC(GUIHelp);
	GUIHelp(void);
	~GUIHelp(void);
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
#endif // GUIHelp_h__

