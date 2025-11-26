#pragma once
#ifndef GUIPika_h__
#define GUIPika_h__

#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "Game/Logic/PointGame.h"
#include "BlockItem.h"
#include "BoardDataPika.h"
#include "spine/spine-cocos2dx.h"

#include "EffekseerForCocos2d-x.h"
using namespace ax::ui;
using namespace std;
using namespace ax::extension;
enum GameStatePika{
    PLAY_PIKA,
    END_PIKA,
    PAUSE_PIKA,
    TOUCH_PIKA,
    EFFECT_PIKA
};

enum GameMode {
	NORMAL_MODE, EXTEND_MODE, CHALLENGE_MODE
};

enum GameType
{
	NORMAL_PIKA, DOWN_PIKA, UP_PIKA, LEFT_PIKA, RIGHT_PIKA, CENTER_PIKA
};

class GUIPika : public BaseGUI
{
public:
	GUIPika(void);
	~GUIPika(void);
public:
	void initGUI();
private:
	

public:
    GameStatePika state;
	void callBackSplash();
	void onButtonRelease(int buttonID, Touch* touch);
	void onBackKey(void);
	
	void act();
	void makeNewLevel();
	void resetGame();
	void newGame();
	void showParticle(BlockItem* number);
	void showParticleFire(float posX, float posY, int id);
	void finishEat();
	void newData();
	void doCenter(int row);
	GameStatePika gameState;
	int score, countGame;
	GameImage* bgProgress;
	ProgressTimer* progress;
	Text* labelScore, *labelHighscore;
    Text *labelLife, *labelLevel;
	BaseButton* btnBack, *btnSound, *btnPause, *btnHelp, *btnSearch;
	BlockItem* arrayNumber[BOARD_ROW_PIKA][BOARD_COLUMN_PIKA];
	int level;
	GameMode gameMode;
	float rootProgress;
	PointGame* currentTouch;
	int idCurrentNumber;
	vector<BlockItem*> currentNumber;
	int timeGame;
	float currentTime;
	int currentRow;

	float moveY;

	//ProgressTimer progress;
	int maxNumber;
	GameType gameType;
	float timeAds;

	BoardDataPika* boardData;
	GameImage* arrayLine[4];
	PointGame* touchPoint1;
	PointGame* touchPoint2;
	vector<BlockItem*> arrayEffectN;
	vector<BlockItem*> getListTouch(BlockItem* number);
	void startMode();
	void startTime(float time, float currentTime = 0);
	void setSelect(bool isSelect);
	float pad;
	int countLife;
	void endGame();
	void callbackEndGame();
	GameImage* bgDark;
	BaseButton* btnPlay;
	bool onTouchBegan( Touch *pTouch, Event *pEvent );
	PointGame* convertPoint(float x, float y);
	PointGame* checkNotMove(PointGame* center, int id);
	void updateScore();
	void onPause();
	void callbackEffect();
	int getFirstVisible();
	float saveTime;
	float widthProgress;
	bool checkCanMove(PointGame* newpoint, PointGame* oldPoint);
	void showGui(GameMode mode);

	float targetScore;
	float deltaScore;
	void checkNewLevel();
	void effectStar(Vec2 posStart, Vec2 posEnd, float time);
	void callbackEffectStar(Node* sender);
	GameImage* background;
	Scale9Sprite *bgScore;
	bool arrayPlayTime[10];
	void saveData();
	void genLevel();
	void genRowColumnTime();
	void genData();
	void startGameAfterGen();
	void resumeGame();

	float deltaBonus;
	float targetBonus;
	GameImage* bgProgressBonus;
	ProgressTimer* progressBonus;
	float timeBonus;
	GameImage* iconGift, *iconBomb;
	GameImage* imgEffectBomb;
	void callbackBomb();
    void callbackBonus();
	Text* labelEffectStar;
	GameImage* iconHeart;
	Node* groupBonus;
    efk::EffectEmitter* effBomb;

    public:
        static std::string className;
};
#endif // GUIPika_h__

