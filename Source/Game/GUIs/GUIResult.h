#ifndef GUIResult_H
#define GUIResult_H

#include "Engine/GUI/BaseGUI.h"

#include "EffekseerForCocos2d-x.h"

#include "Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;
using namespace ax::ui;
class GUIResult : public BaseGUI
{
public:
    GUIResult(void);
    ~GUIResult(void);

public:
private:
	Scale9Sprite* bg;
	Text* lbScore, *lbScore1;
	Text* lbBestScore, *lbBestScore1;
	Scale9Sprite *bgBest;
	Scale9Sprite *bgScore;
	BaseButton* btnPlay;
    BaseButton* btnContinue;
	GameImage* title;
	Sprite* iconBest;
    bool isTime;
	//DBCCArmatureNode* eff;
	//DBCCArmatureNode* effBest;
	int score;
	float currentScore;
	int highscore;
	float currentBest;
	float deltaScore;
	float deltaBest;
    efk::EffectEmitter* effFirework;

    public:
	void initGUI();
	void onButtonRelease(int buttonId, Touch* event);
	void hideGUI();
	void showGUI(int score, int highscore, bool isTime = false);
	void moveEffect(Node* node, int rate, float delay = 0);
	void updateResult(float dt);

    public:
        static std::string className;
};
#endif
