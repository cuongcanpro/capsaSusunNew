#pragma once
#ifndef GUIBlock_h__
#define GUIBlock_h__

#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "LogicBlock/BaseEntity.h"
#include "CellBlock.h"

#include "EffekseerForCocos2d-x.h"
#include "Engine/GUI/ParticleEffect.h"
using namespace std;
using namespace ax::ui;
enum GameStateBlock
{
	PLAY_BLOCK, EFFECT_BLOCK, NORMAL_GAME_BLOCK, TOUCH_BLOCK, SCORE_BLOCK, END_GAME_EFFECT_BLOCK, END_GAME_BLOCK
};
class GUIBlock : public BaseGUI
{
public:
	GUIBlock(void);
	~GUIBlock(void);
public:
	void initGUI();
private:


public:
	BaseButton* btnBack, *btnSound, *btnTop;
	void callBackSplash();
	void initMenu();
	void initBoard();
	void initBonus();
	void initBottom();
	void update(float delta);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch *touch, Event* event);
    virtual void showGUI();
	void newGame();
	void showParticle(float posX, float posY, int id);
	void eatAll();
	Text *labelScore;
	Text *labelHighscore;
	void callbackCheckScore();
	void endGame();
	float time;
	bool isExtraTime;
	int score;
	int countNoBonus;
	void onButtonRelease(int buttonID, Touch* touch);
	float startX, startY, sizeCell, widthBoard;
	CellBlock* arrayCell[8][8];
	GameImage* arrayBgCell[8][8];
	vector <CellBlock*> arrayNewCell;

	Scale9Sprite* bgBottom, *bgMenu, *bgCenter;
	BaseButton* bonusExchange;
	GameImage* bonusBomb, *bonusX3;
	GameImage* iconBomb;
	int numExchange, numBomb;
	Text* lbExchange, *lbBomb, *lbX3;
	float timeX3;
	//DBCCArmatureNode* effX3;
	vector <BaseEntity*> arrayEntity;
	BaseEntity* arrayNextEntity[3];
	BaseEntity* currentEntity;
	void updateBomb();
	void updateX3();
	void updateExchange();
	void updateCell(bool canGen = true);
	void checkWillScore();
	void normalData();
	int checkScore();
	void addScore(int add, Vec2 pos);
	void callbackShowParticle(Node* pSender, int row, int columnt, int id);
	void callbackEffectExtra();
	void callbackEffectBonus();
	void callbackTouchEnd();
	Point getPosCell(int x, int y);
	void genNextEntity(bool isEffect = false);
	void loadNextEntity(int arrayNext[3], bool isEffect = false);
	void startEndGame();
	void checkEndGame();
	bool isNewBest;
	int currentScore;
	int deltaScore;
	void effectScore();
	void updateScore();
	GameStateBlock gameState;
	BaseEntity* getEntity(int id);
	
	vector<Text*> arrayLabelEffect;
	Text* getLabelEffect();
	Point lastTouchEnd;
    GameImage* iconHand;
    void makeHelp1();
    void callbackHelp1();
    int countHelp;
    void makeHelp2();
    void makeHelp3();
	PointGame getPointInBoard(float posX, float posY);
	void showEffectLabel(string s);
	void saveGame();
	void checkIsNewBest(int add);
	void initAds();

	vector <Sprite*> arrayBlockEffect;
	Sprite* getBlockEffect();
    efk::EffectManager* manager;
    efk::EffectEmitter* bombEffect;
    efk::EffectEmitter* clearEffect;
    ParticleEffect* effectX3;
    void onBackKey();

public:
    static std::string className;
};
#endif // GUIBlock_h__

