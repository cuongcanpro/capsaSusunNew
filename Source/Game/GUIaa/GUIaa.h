#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "curl/curl.h"
#include "../GameClient.h"
#include "../Logic/BoardData.h"
#include "BallCircle.h"
#include "BallMove.h"

#include "EffekseerForCocos2d-x.h"
#include "../GUIs/Entity/BombEffect.h"

using namespace std;


class GUIaa : public BaseGUI
{
public:
	GUIaa(void);
	~GUIaa(void);
public:
	void initGUI();
private:
	

public:
    void onBackKey(void);
	

	BaseButton* btnBack, *btnSound;
	
	void onButtonRelease(int buttonID, Touch* touch);
	void callBackSplash();
	float time;
	GameState state;
	vector <BallCircle*> arrayBall;
    void onTouchEnded(Touch* pTouch, Event* pEvent);
	bool isUpdate;

	float countTime, maxTime;
	float radius, rootX, rootY;
    GameImage* bar;

	BallMove* arrayBallMove[4];
	GameImage* bg;

	GameImage* complete;
	GameImage* next;
	GameImage* gameover;
	GameImage* tryAgain;
	Text* labelLevel;
	int level;
	int countGame;
    int score;
    int highscore;
    Text* labelScore;
    Text* labelHighscore;

	void act(float delta);
	void makeNew();
	void finishGame();
	void reArrangeBall();
	void newGame();
	void endGame();
    void callbackEndGame();
	GameImage* barEnd;
	void callbackCompleteEndGame();
    efk::EffectEmitter* effectBreakBall;
    void showGUI(Node* parent /* = NULL */, bool hasFog /* = true */);

public:
    static std::string className;
};

