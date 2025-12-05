#ifndef BinhTruyenThong_h__
#define BinhTruyenThong_h__
#include "core/gui/BaseLayer.h"
#include "BinhPlayerUI.h"
#include "../data/GameConstant.h"
#include "BinhCardButton.h"
#include "../logic/gamePlay/MaubinhPlayerCard.h"
#include "gameTienlen/ui/ClockCountDown.h"
#include "core/gui/Sparkle.h"

class BinhCardButton;

class BinhTruyenThong:
public BaseLayer{
public:
	CREATE_FUNC(BinhTruyenThong);
	BinhTruyenThong();
	~BinhTruyenThong();
	
	Node* groupCard;
	Node* bgDark;
	Button* btnSwap;
	Button* btnComplete;
	Button* btnHard;
	BinhCardButton* arrayCard[NUM_CARD];
public:
	bool init();
	void initGUI();
	void onEnterFinish();
	void showEffect(Vec2 arrayPos[], float widthCard, bool effectGUI);
	void callbackShow(Node* pSender);
	void onButtonRelease(ax::ui::Button* button, int id);
	void sendReady(TypeSend type);
	void touchEvent(Object *pSender, Widget::TouchEventType type);
	void onTouchBeganCard(BinhCardButton* card);
	void onTouchMoveCard(BinhCardButton* card, Vec2 point);
	void onTouchEndCard(BinhCardButton* card, Vec2 point);
	void onTouchCancelCard(BinhCardButton* card, Vec2 point);
	int getCardFromPoint(Vec2 point, int indexNotSelect);
	void swapCard(BinhCardButton* card1, BinhCardButton* card2);
	void callbackSwapCard(Node* pSender);
	void highlightCard(bool sound);
	void checkBoBai(MaubinhPlayerCard playerCard, int cardKind, bool &maubinh, bool &isEffect);
	void playSoundChi(MaubinhPlayerCard playerCard);
	void checkTypeChi(MaubinhPlayerCard playerCard);
	void showTypeChi(int chi, int type, bool binh);

    void effect3Chi();
	void effectChi(int chi);
	void effectBoBai(string resource);
	void effectParticle();
	void setDarkAllCard(bool isDark);
	void setGameTime(int time);
	vector<int> getArrayId();

	int touchCard;
	int moveCard;
	int chiGoal; // chi ma minh dang muon xep
	Sprite* effectImage;
	ImageView* arrayBorder[NUM_CHI];
	ImageView* bgTypeChi[NUM_CHI];
	Text* typeChi[NUM_CHI];
	ClockGame* clockGame;
    Sparkle* arrayEffectChi[NUM_CHI];
public:
	// name
	static const std::string className;
	static const int TAG;
};


#endif // BinhTruyenThong_h__
