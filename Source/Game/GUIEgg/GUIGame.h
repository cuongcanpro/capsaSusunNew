#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

#include "Arrow.h"
#include "Ball.h"
#include "RowBall.h"
#include "Bird.h"
#include "BonusEffect.h"
#include "Game/Logic/PointGame.h"
#include "BonusEffect.h"
#include "GroupScore.h"
#include "Engine/GUI/ImageEffect.h"

#include "EffekseerForCocos2d-x.h"
#include "../GUIs/Entity/BombEffect.h"

using namespace std;
using namespace ui;

#define SPLASH_LAYER 0
#define LEVEL_LAYER 1
#define RACE_LAYER 2
#define TETRIS_LAYER 3
#define GUN_LAYER 4
#define FULL_LAYER 5
#define EMPTY_LAYER 6
#define SNAKE_LAYER 7
#define HIT_LAYER 8
#define JUMP_LAYER 9
#define SAME_LAYER 10

enum GameTypeEgg
{
	ENDLESS, STOMP, TIME, FAKE
};

class GUIGame : public BaseGUI
{
public:
	GUIGame(void);
	~GUIGame(void);
public:
	void initGUI();
private:
	

public:
	void onBackKey(void);
	
	Arrow *arrow;

	void update();
	void onButtonRelease(int buttonID, Touch* touch);
	void callBackSplash();
	
	GameState gameState;

	void newGame();
	

	bool isUpdate;

	vector<RowBall*> arrayRow;
	vector<Ball*> arrayEatBall;
	vector<Ball*> arrayEffectBall;
	vector<GroupScore*> arrayGroupScore;
	Ball* getBall(int idRow, int idColumn);
	
	void resetCheckConnect();
	Ball* genBall;

	float countTime;
	int level;
	Ball* moveBall;
	Ball* nextBall;
	GameImage* cannon1;
	GameImage* bgRow;
	float speedX, speedY, speed;
	GameImage* rope;
	int oldRow, oldColumn;
	Node* groupBall;

	float countTimeVisible;
	int countVisible;
	bool delay;

	GameState state;
	Bird* ani;
	bool increaseSpeed;

	ProgressTimer* progress;
	GameImage* bgProgress;

	float countTimeVibrate;
	int countGenBonus;

	float oldX, oldY;
	bool nextBonus;
	int currentMul;

	Text* labelScore;
    Text* labelHighscore;
    Text* labelRow;

	int score;
	BonusEffect* bonusEffect;

	bool isMoving;
	int numRowScore;
	int countRowScore;
	GameTypeEgg gameType;
	GameImage* bar;
	float distanceY;
	float countDistance;
	bool isNewhigh;
	GameImage* rightWall;
	GameImage* upWall;
	GameImage* leftWall;

    BaseButton* btnTop;
	BaseButton* btnSound;
	BaseButton* btnPause;
	BaseButton* btnBack;
	GameImage* fakeBall;
    vector<BombEffect*> arrayBomb;

	void act(float deltaTime);

	bool onTouchBegan( Touch *pTouch, Event *pEvent );
	void onTouchMoved(Touch*touch, Event* event);
	void onTouchEnded( Touch *pTouch, Event *pEvent );
	void moveArrow(int screenX, int screenY);
	float getTag(int screenX, int screenY);
	void delayReturn();
	void updateArrayBall();
	PointGame* getPoint(float x, float y);
	 void getNearBall(float x, float y);
	 bool checkNearBall(float x, float y, int row, int column,
		 int dRow, int dColumn);
	 void addMoveBall(int row, int column);
	 double getDistance(Ball* ball, float x, float y);
	 bool checkEndGame();
	 void endGame();
	 void makeGenBall();
	 void showParticle(float px, float py, int id);
     void showBomb(float px, float py, float delayTime);
	 void makeBonus();
	 void updateScore();
	 void initGame();
	 void updateTime();
	 string convertTime(float countTime);
	 void onPause();
	 GroupScore* getGroupScore();

	 void callbackRemove(Node* pSender);
	 void callbackNextBall();
	 void callbackProgress();
	 void callbackEndGame();
	 void makeEffectScore();
     void showGui(GameTypeEgg gameType);
	 void showGui(int level);
    efk::EffectEmitter* effectBreakBall;
	/* DBCCArmatureNode* effectShootBall = NULL;
	 DBCCArmatureNode* effectBreakBall = NULL;
	 DBCCArmatureNode* effectLight = NULL;
	 DBCCArmatureNode* effectShoot = NULL;
	 DBCCArmatureNode* effectWin = NULL;*/
	 void initDragonbone();

	 void dropBall(int id, float posX, float posY);
	 Ball* getEffectBall();

	 vector <ImageEffect*> arrayImageEffect;
	 void effectImage(int id);
	 void addNewBall();

     public:
         static std::string className;
};

