#ifndef BinhTinhAt_h__
#define BinhTinhAt_h__
#include "core/gui/BaseLayer.h"
#include "gameTienlen/ui/ClockCountDown.h"
#include "../data/GameConstant.h"
#include "../logic/gamePlay/MaubinhPlayerCard.h"
#include "BinhCardButton.h"
#include "../logic/TypeGameData.h"
#include "BinhBubbleText.h"
enum SortCard {
	NUMBER = 0,
	KIND = 1
};
//#include "../logic/GameLogic.h"
class BinhCardButton;
enum TypeSend;

class BinhTinhAt:
public BaseLayer{
public:
	CREATE_FUNC(BinhTinhAt);
	BinhTinhAt();
	~BinhTinhAt();
	
	Node* panelCenter;
	Node* groupCard;
	Node* bgDark;
	Layout* panelSort;
	Button* btnSwap;

	Sprite* arrayBgCard[NUM_CARD];
	BinhCardButton* arrayCardBottom[NUM_CARD];
	BinhCardButton* arrayCard[NUM_CARD];
	Sprite* effectImage;

	Button* btnBao;
	Button* btnComplete;
	Button* btnCancel;
	Button* btnArrange;
	Button* btnNormal;
	Sprite* iconHand;

	float scaleBottomToCenter;
	float scaleCenterToBottom;

	Vec2 lastTouchPoint;
	int touchCard;
	int moveCard;
	int chiGoal; // chi ma minh dang muon xep
	bool isLung;
	int dataBai[10];
	int dataBinh[10];
	bool showBinh; // the hien xem group thong tin bo bai se show thong tin chi hay thong tin binh cua bo bai
	bool isSort;
	SortCard stateSort;
	bool sendAuto;
	bool effectGUI;
	ClockGame* clockGame;
	BinhBubbleText* bubbleText;
public:
	bool init();
	void initGUI();
	void initBottomCard();
	void initCenterCard();
	void initButton();
	void initOneButton(Button* btn, string resource);

	void onEnterFinish();
	void showEffect(Vec2 arrayPos[], float widthCard, bool effectGUI);
	void callbackShow(Node* pSender);
	void onButtonRelease(ax::ui::Button* button, int id);
	void touchEvent(Object *pSender, Widget::TouchEventType type);
	void onTouchBeganCard(BinhCardButton* card);
	void onTouchMoveCard(BinhCardButton* card, Vec2 point);
	void onTouchEndCard(BinhCardButton* card, Vec2 point);
	void showCardToCenter(BinhCardButton* card);
	void hideCardToBottom(BinhCardButton* card);
	void onTouchCancelCard(BinhCardButton* card, Vec2 point);
	int getCardFromPoint(Vec2 point, int indexNotSelect);
	void swapCard(BinhCardButton* card1, BinhCardButton* card2);
	void callbackSwapCard(Node* pSender);
	void highlightCard(bool sound);
	void checkBoBai(MaubinhPlayerCard playerCard, int cardKind, bool &maubinh, bool &isEffect);
	void playSoundChi(MaubinhPlayerCard playerCard);
	void showEffectChi(MaubinhPlayerCard playerCard);
	void showDarkCard(MaubinhPlayerCard playerCard, int cardKind, bool mauBinh);
	void showDark2BigChi(MaubinhGroupCardLogic* gc1, int chi);
	void showGroupTypeCard();
	void onTouchSort(Object *pSender, Widget::TouchEventType type);
	void sortCard();
	void callbackSortCard(Node* pSender);
	int findIndexCardToShow();
	int findIndexCardToHide();
	bool checkEnoughCard();
	bool checkHaveCard();
	void sendReady(vector <int> arrayId, TypeSend type);

	void effectBoBai(string resource);
	void effectParticle();
	void setDarkAllCard(bool isDark);
	vector<int> getArrayId();
	void update(float dt);
	void setGameTime(int time);
	void showHelp();
public:
	// name
	static const std::string className;
	static const int TAG;
};


#endif // BinhTinhAt_h__
