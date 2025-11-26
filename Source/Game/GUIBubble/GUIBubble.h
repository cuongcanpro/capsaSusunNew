#pragma once
#include "Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

#include "Bubble.h"
#include "BoardDataBubble.h"
#include "BubbleText.h"

//#include "Engine/Effect/ParticleEffect.h"
using namespace std;
using namespace ax::ui;

enum GameStateBubble
{
	PLAY_BUBBLE, NORMAL_GAME_BUBBLE, GAME_OVER_BUBBLE, TOUCH_BUBBLE, MOVE_BUBBLE
};
class GUIBubble : public BaseGUI
{
public:
	GUIBubble(void);
	~GUIBubble(void);
public:
	void initGUI();
	void onBackKey(void);
	

	BaseButton* btnBack, *btnSound, *btnUndo, *btnAchievement;
	
	void update();
	void onButtonRelease(int buttonID, Touch* touch);
	void callBackSplash();
	Bubble *ballMove;
	GameImage *bg;
    Sprite* bgShadow;
	Bubble *arrayNext[MAX_NEXT];
	Bubble* arrayBall[MAX_ROW][MAX_COLUMN];
	GameImage *arrayBgBall[MAX_ROW][MAX_COLUMN];
	Text* labelScore, *labelHighscore;
	BubbleText* bubbleText;
	vector<Text*> arrayLabelEffect;
    vector<Text*> arrayLabelEffectSmall;
	Sprite* iconHand;
	int score;
	
	int oldScore;
	int saveNumRand;
	int saveNext[MAX_NEXT];
	bool canTouch;
	BoardDataBubble* board;
	int arrayOldBall[MAX_ROW][MAX_COLUMN]; // dung de cap nhat trang thai cac qua bong sau khi
	// random hoac di chuyen
	int saveBall[MAX_ROW][MAX_COLUMN]; // luu lai mang gia tri truoc khi di chuyen
	vector<PointGame*> arrayChange; // mang ghi cac bong thay doi
	int valueSaveBall;
	int positionSaveBall;
	int stateTutorial;

	int currentRow;
	int currentColumn;
	int nextRow, nextColumn;
	float SPEED;
	bool canUndo;
	bool genNext;

	int deltaScore;
	int currentScore;

	float startX, startY, pad, sizeCell;
	float time;
	GameStateBubble gameState;
	void effectScore();
	void newGame();
	void updateScore(int score);
	void updateNextBall();
	void updateViewBall();
	void doMoveBall();
	void checkGenNextBall();
	void makeBiggerBall();
	void genBall(int i, int j);
	void checkEatPoint();
	void updateHighScore();
	void undo();
	void onFinish();
	void showParticle(float posX, float posY, int id);
	bool isUpdate;
	void act();
    void showGui();
    void showGuiWithMode(int typeMode);
    void newTimer();
    void callbackTimer();
	void setLevel(int level);
    int typeMode;
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void autoBiggerBall();
	void updateSizeBall();
	void callbackFinishMove();
	void callbackDelayBigger(void* data);
	void visibleBgBall(int row, int column);
	void callbackVisibleEatPoint(Node* pSender);
	void callbackLabelEffect(Node* pSender);
	void callbackEatPoint();
	void callbackAutoScore();
	void showTutorial();
	void setPosIconHand(int x, int y);
    void initAds();
	int countVibrate;
	void vibrate();
	Text* getLabelEffect();
    Text* getLabelEffectSmall();
	Scale9Sprite *bgScore, *bgBest;

	BaseButton* btnBall, *btnColor;
	void updateBoardColor();
	GameImage* background;
    void moveEffect(Node* node, float dx, float dy, float delay = 0);
    void moveEffectSineOut(Node* node, float dx, float dy, float delay = 0);
    float cellW, cellH;
    bool checkInHexagon(float centerX, float centerY, Vec2 pos);
    bool isPointInHexagon(Vec2 point, vector<Vec2> hexagonVertices);

public:
    static std::string className;
};

