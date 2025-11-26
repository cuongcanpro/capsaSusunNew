#pragma once
#include "axmol.h"
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "extensions/axmol-ext.h"
#include "EffekseerForCocos2d-x.h"
#include <Game/Logic/BoardData.h>
#include "BallAnimationNew.h"
#include "ScoreGroup.h"

#include <Engine/GUI/Paper.h>
#include <Engine/GUI/ImageEffect.h>
#include "extensions/axmol-ext.h"
#include "GUI/ControlExtension/ControlExtensions.h"
#include "../GUIs/CommonResultGroup.h"

using namespace ax::ui;

class GUILine : public BaseGUI
{
public:
	GUILine(void);
	~GUILine(void);
	void initGUI();
    bool isDev;
    int countDev;
    float startX;
    float startY;
    float sizeCell;
    Sprite* bgBoard;

    BaseButton *btnBack, *btnSound, *btnUndo, *btnTrophy, *btnNewGame;
    BoardData* board;
    GameState gameState;
    LayerColor* layerDark;
    Sprite* imgNewBest;
    GameImage* ballMove;
    GameImage* bg;
    GameImage* background;
    GameImage* arrayNext[3];
    Sprite* arrayShadow[9][9];
    BallAnimationNew* arrayBall[9][9];
    Sprite* imgCombo;
    ui::Text* labelAddScore;
    int score;
    float currentScore;
    float deltaScore;
    int highscore;
    int oldScore;
    int arrayOldBall[9][9];  // dung de cap nhat trang thai cac qua bong sau khi
    // random hoac di chuyen
    int saveBall[9][9];              // luu lai mang gia tri truoc khi di chuyen
    vector<PointGame*> arrayChange;  // mang ghi cac bong thay doi
    int valueSaveBall;
    int positionSaveBall;
    MotionStreak* _streak;
    ScoreGroup *highscoreGroup, *scoreGroup;

    int currentRow;
    int currentColumn;
    int nextRow, nextColumn;
    float SPEED;
    bool canUndo;
    bool genNext;
    int typeBall;
    int saveValue2;
    GameImage* effect;
    vector<GameImage*> arrayEffectBall;
    bool isNewBest;
    Sprite* bgEffect;
    float widthBoard;
    GameImage* iconHand;
    CommonResultGroup* groupBest;
    void showHand(Vec2 posStart);
    

public:
    void initMenu();
    void initBoard();
    void initBall();
    void initLabel();
    void updateBoard();
	void callBackSplash();
    void effectOpen();
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void update(float delta) override;
    void showGui();
    void newGame();
    void genBall(int i, int j);
    void updateNextBall();
    void updateViewBall();

    void updateScore();
    void undo();
    void onFinish();
    void doMoveBall();
    void checkGenNextBall();
    void autoBiggerBall();
    void makeBiggerBall();
    void checkAfterMove();
    void checkAfterMove2();
    void checkEatPoint();
    void checkEndGame();
    void callbackEffectEndGame();
    void callbackEffectEndGame1();
    void addScore(int _score);
    void checkIsNewBest(int add);
    void showEffectLabel(string s);
    void showParticle(float posX, float posY, int id, float time);
    void savePreference();
    void onBackKey(void);
    void onButtonRelease(int buttonId, Touch* event);
    vector<ImageEffect*> arrayImageEffect;
    void effectImage(BallAnimationNew* ball);
    void effectCombo(int count);
    void renewGall();
    void callbackRenew();
    void showScaleBall(bool show);
    void updateContentBall();
    void hideSetting();
    void showSetting();
    void showNewGame();

    int numRemove;
    void changeToRemoveBall();
    void removeBall(int row, int column);
    Text* lbRemove;
    Sprite* arrayBomb[9][9];

public:
    static std::string className;
};

