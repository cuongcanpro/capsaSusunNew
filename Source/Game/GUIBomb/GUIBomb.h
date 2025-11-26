#ifndef GUIBomb_H
#define GUIBomb_H

#include "../../Engine/GUI/BaseGUI.h"

#include "BoardDataBomb.h"
#include "CellBomb.h"
#include "EffekseerForCocos2d-x.h"
#include "GroupBombHelp.h"
#include "Game/GUIs/Entity/BombEffect.h"
using namespace efk;
using namespace std;
using namespace ax::ui;
enum ChangeTouch {
	TOUCH_ADD,
	TOUCH_REMOVE,
	TOUCH_CHANGE
};
enum BombGameState {
	BOMB_GAME_WAIT_FIRST_TOUCH,
	BOMB_GAME_PLAY,
	BOMB_GAME_END
};

enum VibrateType
{
	VIBRATE_JUMP,
	VIBRATE_EAT,
	VIBRATE_DIE
};

enum TypeBoard
{
    BOARD_NORMAL,
    BOARD_EXTEND
};
class GUIBomb : public BaseGUI
{
protected:
	Scale9Sprite* bg, *bgMenu, *bgAds, *bgNewGame;
	BaseButton* btnSound, *btnPlay, *btnBack, *btnNewGame, *btnTop, *btnMode;
    GameImage* border;
	
	CellBomb* arrayCell[BOARD_ROW_BOMB][BOARD_COLUMN_BOMB];
	Node* groupCell;
	float timeTouch;
	float cellSize;
	bool isMoving;
	int countTouch;
	Vec2 pointViewGlobal;
	Vec2 pointViewLocal;
	float lastDistance;
	Vec2 arrTouchPoint[2];
	vector<Touch> arrTouch;
	float lastMoveX, lastMoveY;
	bool isContinueMove;
	Sprite* iconDot;
	BombGameState gameState;
	int currentRow, currentColumn;
	int numVibrate;
	Vec2 saveGroupCellPos;
	efk::EffectManager* manager;
	efk::EffectEmitter* emitter;
	efk::EffectEmitter* hitEffect;
	int countOpen;
	int maxSoundOpen;
	float startX, startY;
	Text* lbBomb;
	Text* lbTimeGame;
	Text* lbTimeBest;
	Text* lbLevel;
	Text* lbEndGame;
	float timeGame;
	float heightView;
	Vec2 posCenter;
	GroupBombHelp* groupHelp;
	Sprite* iconBomb;
    TypeBoard typeBoard;

public:
	BoardDataBomb* boardData;
public:
	void initGUI();
	void onButtonRelease(int buttonId, Touch* event);
	void onBackKey();
	void hideGUI();
	virtual void showGUI();
	void moveEffect(Node* node, int rate, float delay = 0);
	void loadSound();
    virtual void startGame();
    virtual void newGame();
	void callbackNewGame();
	void update(float delta);
	void endGame();
	void showDialogEndGame();
	void showDialogWinGame();
	void showDialogLoseGame();
	void onTouchEnded(Touch *pTouch, Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch*touch, Event* event);
	void onTouchesBegan(const std::vector<Touch *>& touches, Event *event);
	void changeListTouch(Touch* touch, ChangeTouch change);
	bool isTouchMove(Touch* touch);
	void checkBound();
	void effectVibrate();
    void effectVibrateSmall();
	void startSoundOpen(int count);
	void playSoundOpen();
	void scaleToFitScreen(float delayTime);
	virtual void saveData();
	
	Vec2 getPosCell(int row, int column);
	bool isPlaying();
	void initAds();
    vector<BombEffect*> arrayBomb;
    void showBomb(float px, float py, float delayTime);
    void showEndGame();
    void effectEndGame(PointGame p);
    void callbackShowAds();
    virtual Size getSizeGroupCell();
    virtual void loadSaveGame();
    virtual void clearData();
    virtual void saveHighscore();

public:
    static std::string className;
};
#endif
