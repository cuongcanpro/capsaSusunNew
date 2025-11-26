#pragma once
#ifndef GUIChoose_h__
#define GUIChoose_h__
#include "../../Engine/GUI/BaseGUI.h"


using namespace ax;
using namespace ui;
class GUIChoose : public BaseGUI
{
public:
	GUIChoose(void);
	~GUIChoose(void);

	Text* labelEndless, *labelStomp, *labelTime, *labelLine, *labelTwenty, *labelMerge;
    BaseButton* btnMinesweeper;
	BaseButton* btnEndless;
	BaseButton* btnStomp;
	BaseButton* btnTime;
	BaseButton* btnBack;
	BaseButton* btnSound;
	BaseButton* btnLines;
	BaseButton* btnTwenty;
	BaseButton* btnMerge;
    BaseButton* btnVibrate;
	void onBackKey(void);
	void callBackSplash();
	void initGUI();
    void showGUI(Node* parent = NULL, bool hasFog = true);
	void onButtonRelease(int buttonID, Touch* touch);
    void loadVibrate();
};
#endif // GUIChoose_h__

