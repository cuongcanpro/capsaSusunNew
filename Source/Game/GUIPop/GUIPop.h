#ifndef GUIPop_H
#define GUIPop_H

#include "../../Engine/GUI/BaseGUI.h"

#include "PopGroupNewNumber.h"
#include "BoardPop.h"
#include "FlyNumber.h"
using namespace ax::ui;
class GUIPop : public BaseGUI
{
private:
	BoardPop* groupCenter;
	
public:
    Text* labelScore;
    Text* labelHighscore;
	BaseButton* btnBack, *btnSound, *btnPause, *btnPlay, *btnTop, *btnMusic, *btnVibrate, *btnResume, *btnBomb, *btnNewGame;
    PopObjectNumber* bestNumber;
    PopObjectNumber* currentNumber;
    PopGroupNewNumber* groupNewNumber;
	int score, highscore;
	float widthCenter, heightCenter;
	Scale9Sprite* bgScore, *bgBest;
	Sprite* bgCenter;
	float deltaScore;
	float targetScore;
	float currentScore;
	float scaleResume;
	float manaPoint;
	float deltaMana;
	float targetMana;
	int numBomb;
	Sprite* iconBomb;
	Sprite* iconBombEffect;
	Text* lbBomb;
	
	GameImage* bgProgress;
	ProgressTimer* progress;
    Sprite* iconHand;
    FlyNumber* flyNumber;
    BoardType type;

	void initGUI();
	void onBackKey();
	void onButtonRelease(int buttonId, Touch* event);
	void hideGUI();
	void showGUI(BoardType type);
	void showEffect();
	void moveEffect(Node* node, float dx, float dy, float delay = 0);
	void moveEffectSineOut(Node* node, float dx, float dy, float delay = 0);
	void update();
    void checkShowTouch();

	void onTouchEnded(Touch *pTouch, Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch*touch, Event* event);

	void addScore(int _score);
	void addMana(int mana);
    void updateMaxNum();
    void updateBestNum();
	void updateScoreSum();
	void updateBomb();
	void useBomb();
	void endGame();
	void newGame();
	void showNewNumber(int number, Vec2 pos, float scale);
    void showFlyNumber(int number, Vec2 pos, float scale);
	void initAds();
	void updatePosCenter();
    void addBomb(int _bomb);

	Sprite* imgNewBest;
	bool isNewBest;
	void showNewBest();
	void showEffectLabel(string s);

    public:
        static std::string className;
};
#endif
