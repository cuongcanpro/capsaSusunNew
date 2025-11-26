#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "Number.h"
#include "GroupNumber.h"
#include "Engine/GUI/ImageEffect.h"

#include "Engine/GUI/Paper.h"
#include "Game/Logic/PointGame.h"

using namespace std;
using namespace ax::extension;
using namespace ax::ui;

#define MAX_ROW_TWENTY 9
#define MAX_COLUMN_TWENTY 7
#define NUMBER_DESTROY 8

enum GameStateTwenty{
	PLAY_TWENTY, END_TWENTY, PAUSE_TWENTY, MOVE_TWENTY, TUTORIAL_TWENTY, NEXT_NUMBER_TWENTY
};

class GUITwenty : public BaseGUI
{
public:
	GUITwenty(void);
	~GUITwenty(void);
public:
	void initGUI();
private:
	

public:
	GameStateTwenty state;
	void callBackSplash();
	void update();
	void callbackCompleteEndGame();
	void playParticle(float posX, float posY, Color3B color, int id);
	void onTouchEnded( Touch *pTouch, Event *pEvent );
	bool onTouchBegan( Touch *pTouch, Event *pEvent );
	void onTouchMoved(Touch*touch, Event* event);
	int count;
	int countMove;
	int countGame;
	int countSuccess;
	int countReverse;
	void updateScore();
	Node* layer;

	Text* labelScore;
	Text* labelHighscore;
	Text* labelScoreSum, *labelHighscoreSum;
	Text* tutorialLabel;
	Text* labelAddScore;
	BaseButton* btnBack, *btnSound, *btnPause, *btnPlay, *btnTop;
	int score;

	void onButtonRelease(int buttonID, Touch* touch);
	void endGame();
	void onPause();
	void newGame();
	void onBackKey();
	void doFall();
	PointGame* convertPoint(float x, float y);
	PointGame* checkNotMove(Point center, int id);
	void checkEat(Number* number);
	void doEat(Number* number);
	bool setPosNumber(Number* number, float posX, float posY);
	void setPos(Number* number, float posX, float posY);
	vector<Number*> getListTouch(Number* number);
	void checkListFall();
	void checkListFall1();
	int getFirstVisible();
	bool checkCanMove(PointGame* newpoint, PointGame* oldPoint);
	void genRow();
	void checkGenRow();
	void checkFall(Number* number, PointGame* oldPoint);
	void makelistFall(PointGame* oldPoint);
	void doTutorial();
	void updateScoreSum();
	void newGame(int maxNumber, int row, int data[8][7], int saveScore);
	void tutorial1();
	void tutorial2();
	void tutorial3();
	void tutorial4();
	void tutorial5();
	void tutorial6();
	void tutorial7();
	float countTime, maxTime, timeProgress;
	float radius, rootX, rootY;
	GameImage* bar;
	int level;

	GameImage* bg;
	GameImage* bgDark1;
	GameImage* complete;
	GameImage* next;
	GameImage* gameover;
	GameImage* tryAgain;
    ProgressTimer* progress;

	Number* arrayNumber[MAX_ROW_TWENTY][MAX_COLUMN_TWENTY];
	PointGame* currentTouch;
	int idCurrentNumber;
	vector<Number*> currentNumber;

	int currentRow;

	float moveY;

	//ProgressTimer progress;
	int maxNumber;
	float timeAds;

	ax::LayerColor* layerColor;
	Sprite* imgNewBest;
	bool isNewBest;
	void checkIsNewBest(int add);
	void showEffectLabel(string s);
    GameImage* border;
	GroupNumber* effectNumber;
	GroupNumber* curNumber;

	vector <ImageEffect*> arrayImageEffect;
	void effectImage(Number* ball);

	void callbackEffectEndGame();
	void callbackEffectEndGame1();
	void initAds();
	bool isInitAds;
	//vector <StarFly*> arrayStarEffect;
	void effectStar(Number* ball);
	GameImage* bgProgress;
	GameImage* bgDark2;
	float widthBoard;
	float currentTime;
	void updateBg();
	void updateSizeNumber();
	void showNextNumber();

	vector <Sprite*> arraySmoke;
	Sprite* getSmoke();

	Paper* paperLeft;
	Paper* paperRight;
	GroupNumber* newNumber;
	GroupNumber* deleteNumber;
	void showNewNumber(Number* number);
	vector<int> arrayLevel;
	void playSoundMove();
	void showDeleteNumber();
	BaseButton* btnOk;
	void hideNewNumber();
	Sprite* iconX;
	//StarFly* starFly;
	void showAdsFull();
	void showGui();

    public:
        static std::string className;
};

