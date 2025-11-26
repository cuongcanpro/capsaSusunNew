#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "curl/curl.h"
#include "../GameClient.h"

#include "../Logic/BoardData.h"
#include "StickMan.h"
#include "Smoke.h"

using namespace std;
using namespace ax::ui;
class GUISwing : public BaseGUI
{
public:
	GUISwing(void);
	~GUISwing(void);

    enum GameState
    {
        PLAY,
        NORMAL_GAME,
        GAME_OVER,
        WAIT_MOVE,
        PRESS,
        SWING,
        SWING_REVERSE,
        FINISH,
        PAUSE
    };

    public:
	void initGUI();
private:
	

public:
	void onBackKey(void);
	

	BaseButton* btnBack, *btnSound, *btnPlay;
	
	void update();
	void onButtonRelease(int buttonID, Touch* touch);
	void callBackSplash();
	StickMan *stickMan;
	GameState gameState;
	GameImage *column1, *column2, *column3, *bar;
    GameImage* stickStand;
	Text* labelScore;
    Text* labelHighscore;
    Text* lbState;
    Sprite* iconHand;
    int highscore;
	int score;
	float fixHeight;
	bool onTouchBegan(Touch *pTouch, Event *pEvent );
	bool isPress;
	float time;
	void genNewGame();
    void showHand();
	void onTouchEnded(Touch *pTouch, Event *pEvent );
	void updateScore();

	void endGame();
	void startRun();
	void startRunFail();
	void startFall();
	void nextStep();
	bool isGen;
	float rootHeight;
	float width1;
	float width2;
	float height2;
	float distance;
	int countGame;
	vector <Smoke*> arraySmoke;
	GameState saveState;

	void startMove();
	void updateMove();
	void startSwing();
	void updateSwing();
	void updateReverse();
	void doEndGame(int type = 0);
	void makeSmoke();
	void pause();
    void showGUI(Node* parent /* = NULL */, bool hasFog /* = true */);

    public:
        static std::string className;
};

