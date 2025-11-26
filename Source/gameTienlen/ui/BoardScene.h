#ifndef BoardScene_h__
#define BoardScene_h__
#include "core/gui/BaseLayer.h"
#include "PlayerUI.h"
#include "ClockCountDown.h"
#include "CardImage.h"
#include "../data/GameConstant.h"
#include "Effekseer/Effekseer.h"
#include "CardEffect.h"
#include "CardEndGroup.h"

using namespace efk;

enum AutoState {
	AUTO_START_STATE,
	CHECK_SUDDEN_WIN_STATE,
	AUTO_PLAY_CARD,
	AUTO_PASS,
	SUMMARY_STATE,
	PRE_END_GAME_STATE,
	END_GAME_STATE,
	WAIT_NEXT_GAME_STATE,
	REWARD_FAIL_STATE,
	REWARD_SUCCESS_STATE
};

class BoardScene:
public BaseLayer{
public:
	CREATE_FUNC(BoardScene);
	BoardScene();
	~BoardScene();
	bool init();
	
public:
	void initGUI();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	
public:
	// name
	static const std::string className;
private:
	ImageView *bgBoard, *groupCard;
	Text *labelRoom, *labelBet, *labelRate, *lbJackpot;
	Button *btnMore, *btnHelp, *btnSound, *btnBack, *btnStart, *btnQuitSelect, *btnLanguage, *btnTop, *btnGame;
	
	//SelfUI *myPlayer;

	Node* pEffect, *pGroup, *pLight, *pCard, *pJackpot, *pCardTop, *pEffectTop, *pEffectAll;
	ClockCountDown *clockCountDown;
	ResultGroup* resultGroup;
	vector <CardEffect*> arrayCardEffect;
	vector <CardImage*> arrayCardOnBoard;
	vector <CardEffect*> arrayCardEffectTop;

private:
	bool showMore;
	float timeWaitOther;
	char typeGroup;
public:
	void initPlayer();

public:
	void onEnter();
	void update(float delta);
	// function in Game
	void newGame();
    void newGame1();
    void newGame2();
    void newGame3();
    void newGame4();
	void joinRoomSuccess();
	void setViewInfo();
	void updateRoomOwner();
	void updateWaitOther();
	void newUserJoinRoom(char chair, PlayerInfo* info);
	void userLeave(char chair);
	void autoStart(int time, char type);
	void notifyStart();
	void dealStartGame();
	void callbackDealCard(int num, int indexPlayer, float delayTime);
	void callbackDealCard1(Node* sender, int num, int indexPlayer);
	void callbackEndDealCard();
	void updateMyCard();
	void changeTurn(bool isNewTurn, char playerTurn, int turnTime);
	void endTurnCard();
	void playCard(vector<int> arrayId, char chair, char typeGroup, bool isEnd = false);
    void callbackVibrate(Node* sender, int miliseconds);
	void playEffectCard(Node* sender, char typeGroup, Vec2 pos);
	void pass(char chair);
	void suddenWin();
	void endCard(char chair);
	void fineMoney(double money, char getChair, char loseChair);
	void notifyGameResult(vector<double> moneys, vector<char> ranks, vector<bool> isCongs);
	void jackpot(double gold);
	void callbackToiTrang(Node* sender);
	void callbackJackpot(Node* sender);
	void updateJackpot();
	void determineInGame();
	void regQuit(bool status);
	void kickFromRoom(char chair, char reason);
	void updateBigBet();
	void effectBigBet(Vec2 posEnd);
	void chatEmoticon(char chair, char id, char type);
	void chatMessage(char chair, string message);
	void updateUserMoney(char chair);
public:
	PlayerUI *arrayPlayer[NUM_PLAYER];
	// utils function
	CardEffect* getCardEffect(bool isTop);
	vector <int> getArrayCardSelect();
	void autoCard(vector <int> arrayId);
	void checkCanThrowCard();
	void onTouchBoard();
	void showMoreButton();

	// call from other modules 
	Node* getNodeEffect(char chair);
	void setInfoCountDown();
	void onReceiveChatEmotion(int index, int fromUserId);
	void onReceiveChatMessage(std::string msg, char chair);
	void updateAvatarFrame(char chairInServer);
	ax::Point getPositionAvatar(char chairInServer);

	void updateMyInfo();
	ui::Text *getMyGoldLabel();
	Node *getMyAvatar();

	Vec2 getPosFromPlayer(int id);
	std::vector<Vec2> getPlayerPosExcepted(int id);
	AutoState autoState;
	void loadBtnSound();
	void loadBtnLanguage();
	void backKeyPress();

	efk::EffectManager* manager;
	efk::EffectEmitter* emitter;
	efk::EffectEmitter* lightExplore;
	CardEndGroup* cardEndGroup;

	void moveCardToiTrang(vector<int> arrayId, int indexPlayer);
    void moveCardToiTrang1(int numCard, int indexPlayer);
};


#endif // BoardScene_h__
