#pragma once
#include "axmol.h"
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "extensions/axmol-ext.h"
#include "EffekseerForCocos2d-x.h"
class GUILoading : public BaseGUI
{
public:
	GUILoading(void);
	~GUILoading(void);
public:
	void initGUI();
    vector<Sprite*> arrayBall;
    GameImage* background;
    efk::EffectManager* manager = nullptr;
	void callBackSplash();
	void callbackCompleteEndGame();
    void callbackCompleteEndGame1();
    void callbackTest();
    void update(float delta) override;

public:
    static std::string className;
};

