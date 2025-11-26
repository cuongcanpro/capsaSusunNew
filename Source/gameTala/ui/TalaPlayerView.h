#ifndef TalaPlayerView_h__
#define TalaPlayerView_h__

#include "core/gui/SceneMgr.h"
#include "core/gui/BaseLayer.h"
#include "TalaCardView.h"
#include "TalaResultGroup.h"
#include <ui/UILoadingBar.h>

using namespace ax::ui;

class TalaScene;
class TalaPlayerView : public BaseLayer {
public:
	static TalaPlayerView* create(TalaScene* gameScene, Layout* panel, int index);
	TalaPlayerView();
	~TalaPlayerView();
	bool init(TalaScene* gameScene, Layout* panel, int index);
	void initGUI();
	void onEnter();

public:
	TalaScene* gameScene;
	int index;
    ImageView* bgScore;
    Text *lbScore;
	ImageView *avatar;
	Text *name, *gold;
	Sprite *nen;
	ProgressTimer *timer;
	Layout *panel_eat, *panel_haphom, *panel_throw, *panel_card;
	Node *state;
	TalaResultGroup* resultGroup;
	Layout *cardPanel;
	ImageView *card;
	TalaCardView *moveCard;
	bool touchEnabled;
	bool isTouchMoved;
	int touchId;
	int touchIndex;

	ax::Vector<TalaCardView*> handOnCards;
	ax::Vector<TalaCardView*> eatenCards;
	ax::Vector<TalaCardView*> throwCards;
	vector<ax::Vector<TalaCardView*>> listPhom;
	Text* lbLevel;
	LoadingBar* progress;
	ImageView* borderAvatar;

public:
	bool onTouchBegan(Touch *touch, ax::Event *event);
	void onTouchMoved(Touch *touch, ax::Event *event);
	void onTouchEnded(Touch *touch, ax::Event *event);

public:
	void clearInfo();
	void updateUserInfo();
	void updateGameInfo();
	void effectTime(char time);
	void effectDarkAllCards();
	void clearAllCards();
	void updateLevel();
	void setVisible(bool visible);
	void setTouchEnabled(bool enabled);
    bool isTouchEnabled();
	Vec2 getAvatarPosition();
	bool isTouchLastThrowCard(Vec2 touchPos);
	char getTouchSuitIndex(Vec2 touchPos);
	void showEffectRank(int rank, float delayTime = 0);
    void showScore(int score);
    void effectRenew();

    public:
	void updateHandOnCards(float duration = 0.25, bool resetTouch = true);
	void updateThrowCards(float duration = 0.25);
	void updateEatenCards(float duration = 0.25);
	void updatePhomCards(float duration = 0.25);
    void updatePhomCardsU(float duration = 1.0);
};

#endif //TalaPlayerView_h__
