#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;

class GUILoadingGame : public BaseGUI
{
public:
	GUILoadingGame(void);
	~GUILoadingGame(void);
	void initGUI();
	void callBackSplash();
	void callbackCompleteEndGame();
    int currentGame;
    void showGame(int game);
    public:
        static std::string className;
};

