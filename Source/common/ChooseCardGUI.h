#pragma once
#ifndef ChooseCardGUI_h__
#define ChooseCardGUI_h__
#include "core/gui/BaseLayer.h"


using namespace std;
using namespace ax::extension;

class ChooseCardGUI : public BaseLayer
{
public:
	CREATE_FUNC(ChooseCardGUI);
	ChooseCardGUI(void);
	~ChooseCardGUI(void);
	bool init();
public:
	ImageView *bg;
	ImageView* iconSelect;
	Button* btnCard0, *btnCard1;
	void initGUI();
	void backKeyPress();
	void onEnterFinish();
	void selectCard(int select);
	void onButtonRelease(ax::ui::Button* button, int id);
	
	static std::string className;
};
#endif // ChooseCardGUI_h__

