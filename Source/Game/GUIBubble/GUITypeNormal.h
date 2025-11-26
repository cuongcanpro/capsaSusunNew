#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;


class GUITypeNormal : public BaseGUI
{
public:
	GUITypeNormal(void);
	~GUITypeNormal(void);
	void initGUI();
	BaseButton* btnBack, *btnSound, *btnSetting;
	BaseButton* btnExtend,  *btnNormal;
	void onButtonRelease(int buttonID, Touch* touch);
    void callBackSplash();
	void onBackKey();
	void initAds();
	void showGUI(Node* parent /* = NULL */, bool hasFog /* = true */);
	void updateButton();

	vector<BaseButton*> arrayButton;
};

