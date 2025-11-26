#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "Tetris/TetrisLayer.h"
#include "Engine/GUI/GameImage.h"
using namespace std;

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
class GUIBrick : public BaseGUI
{
public:
	GUIBrick(void);
	~GUIBrick(void);
public:
	void initGUI();
private:
	

public:

	//virtual bool onTouchBegan( CCTouch*touch, CCEvent* event );

	float startX, startY, sizeCell;
	int typeLayer;

	GameImage* arrayEmpty[NUM_HEIGHT][NUM_WIDTH];
	GameImage* arrayCell[NUM_HEIGHT][NUM_WIDTH];

	GameImage* arrayEmptyNext[4][4];
	GameImage* arrayCellNext[4][4];

	BaseButton* btnOff, *btnMenu, *btnPause, *btnSound;
	BaseButton* btnDown, *btnLeft, *btnRight, *btnUp, *btnRotate;
	Text* labelOff, *labelMenu, *labelPause, *labelSound;
    Text *labelLeft, *labelRight, *labelUp, *labelDown, *labelRotate;
    Text *labelScore, *labelHighscore, *labelLevel, *labelSpeed;
	GameImage* imagePause, *imageMusic, *imageLevel, *imageScore, *imageHighScore, *imageSpeed;

	void update();

	void updateLevel();
	void updateSpeed();
	void updateHighscore();
	void updateScore();
	void updateLabelGame();
	void updateLabelLevel();
	void updateInfoGame();
	void onButtonRelease(int buttonID, Touch* touch);

	TetrisLayer *tetrisLayer;
	BaseGame* currentLayer;

	void showTetrisLayer();

	bool checkRotate();
	bool checkLeft();
	bool checkRight();
	bool checkUp();
	bool checkDown();

	void callBackSplash();
    bool isInit;
    void initAds();
	bool run;

public:
    static std::string className;
};

