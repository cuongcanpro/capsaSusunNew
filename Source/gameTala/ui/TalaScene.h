#ifndef TalaScene_h__
#define TalaScene_h__
#include "core/gui/BaseLayer.h"
#include "../data/TalaGameConstant.h"
#include "TalaResultGroup.h"
#include "TalaPlayerView.h"

class TalaPlayerView;
class TalaScene:
public BaseLayer{
public:
	CREATE_FUNC(TalaScene);
	TalaScene();
	~TalaScene();
	bool init();


public:
	void initGUI();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	void onExit();
	void backKeyPress();
	void loadBtnSound();
public:
	Text *roomBet;
	Button *btnDanh, *btnHaBai, *btnGuiBai, *btnGroup, *btnStart, *btnXepBai, *btnSound;
	ImageView *actionArrow, *drawArrow;
	Text *nDeck;
	Layout *pAction;
	ImageView *deckCard;

	Layout *pStart;
	TalaResultGroup* resultGroup;
	Layout *pEffect, *pClearCards;
	vector<Sprite*> effectCards;

	vector<TalaPlayerView*> players;

public:	//methods to update room info
	void clearRoomInfo();			//clear when first join room, reconnect, new match
	void updateRoomInfo();			//update when room info (bet, index, type) change
	void updateRoomOwner();			//update when room owner change
	void updateQuitReg();			//update when quit reg change
	void updateJackpot();

public: //method to update common game info
	void updateDeckCard();								//update when change nDeckCard
	void updateAction();								//update when change state
	void updateStart(bool countdown, char time = 0);	//update when receive notify start and auto start
	void updateWait();									//update when user join or leave room
	void updateBigBet(bool animate = false);			//update when bigbet change

	void updateUserInfo(char chair);			//update when user info change
	void updateGameInfo(char chair);			//update when user status or state change
	void updateIP();							//update when user status change
	void updateTimer(char chair, char time);	//update when user has new turn time

    void effectRenew(char chair);
	void effectMoreTurn(char chair);							//effect when user receive another turn
	void effectRank(char chair, char rank, float time = -1);	//effect when game result
	void effectMyRank(char rank, float time = 0);								//effect my rank when result
	void effectMoney(char chair, long long money, float delayTime = 0);				//effect when an chot || game result
	void effectDenTien(char chair);								//effect when den tien
	void effectAnChot();										//effect when a me an chot
	void effectJackpot();
	void effectBigBet(char chair);
	void clearEffectRank();

public:	//method to update cards
	void effectDealCards(bool isFirstTurn);							//when notify start
	void effectShowCards();											//when update cards
	void effectThrowCard(char chair, char cardId);					//when throw cards
	void effectReceiveCardFromDeck(char chair, char cardId);		//when receive cards form deck
	void effectReceiveCardFromOther(char srcChair, char desChair);	//when receive card from other
	void effectMoveThrowCard(char srcChair, char desChair);			//when a card change player
	void effectShowPhom(char chair, bool isU);								//when player ha bai
	void effectSendCard(char srcChair, char desChair, char cardId);	//when player send card
	void effectArrangeCard();										//when player arrange card
	void effectHintSendCard();										//when hint cards can be sent
	void effectShowCardsOther(char chair, bool dark = true, float delayTime = 0);
	void effectMoveCard(char oldIdx, char newIdx);
	void updateHandOnCards(float duration = 0.25, bool resetTouch = true);

	void effectEatableCard(char chair, bool show);
	void effectDarkThrowCards(char chair);
	void effectHintSuit(char chair, char suitIndex = -1);
	void effectDarkAllCards();
	void effectClearAllCards();
	void updateAllCards();
	void update(float delta);
	void updateAvatar();

public:

	bool touchEnabled;
	bool isTouchMoved;
	int touchId;
	bool onTouchBegan(Touch *touch, ax::Event *event);
	void onTouchMoved(Touch *touch, ax::Event *event);
	void onTouchEnded(Touch *touch, ax::Event *event);
	void setTouchEnabled(bool enabled);

private:
	void switchParent(Node* child, Node* oldParent, Node* newParent);

public:
	static const std::string className;
	enum BtnCode {
		BTN_QUIT = 0,
		BTN_XEPBAI = 1,
		BTN_DANH = 2,
		BTN_HABAI = 3,
		BTN_GUIBAI = 4,
		BTN_START = 5,
		BTN_CHEAT = 6,
		BTN_GROUP = 7,
		BTN_JACKPOT = 8,
		BTN_EMO = 9,
		BTN_CHAT = 10,
		BTN_ADD_BOT = 11,
		BTN_SOUND = 12
	};
};

#endif // TalaScene_h__
