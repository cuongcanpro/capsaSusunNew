#ifndef GUIMerge_H
#define GUIMerge_H

#include "../../Engine/GUI/BaseGUI.h"

#include "GroupCenter.h"
#include "GroupNewNumber.h"
using namespace ax::ui;
class GUIMerge : public BaseGUI
{
private:
	GroupCenter* groupCenter;
	
public:
    GameImage* border;
	Text* labelScore;
	Text* labelHighscore;
	Text* labelScoreSum, *labelHighscoreSum;
	Text* tutorialLabel;
	Text* labelAddScore;
	BaseButton* btnBack, *btnSound, *btnPause, *btnPlay, *btnTop, *btnDownload;
	int score, highscore;
	GroupNewNumber* groupNewNumber;
	float widthCenter, heightCenter;
	Scale9Sprite* bgScore, *bgBest;
	Sprite* bgCenter;

	void initGUI();
	void onBackKey();
	void onButtonRelease(int buttonId, Touch* event);
	void hideGUI();
    void showGUI(Node* parent = NULL, bool hasFog = true);
	void showEffect();
	void moveEffect(Node* node, float dx, float dy, float delay = 0);
	void update();

	void onTouchEnded(Touch *pTouch, Event *pEvent);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch*touch, Event* event);

	void addScore(int _score);
	void updateScoreSum();
	void endGame();
	void newGame();
	void showNewNumber(int number, Vec2 pos, float scale);
	void resumeGame();

    public:
        static std::string className;
};
#endif
