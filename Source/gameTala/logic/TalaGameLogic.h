#ifndef TalaGameLogic_h__
#define TalaGameLogic_h__
#include "gameTala/logic/TalaPlayerInfo.h"
#include "gameTala/data/TalaGameConstant.h"
#include "gameTala/data/TalaGamePackets.h"
#include "gameTala/ui/TalaScene.h"
#include "axmol.h"
#define talaGameLogic TalaGameLogic::getInstance()

class TalaGameLogic
{
public:
	enum AutoState {
		AUTO_START_STATE,
		AUTO_NOTIFY_U,
		AUTO_CHANGE_TURN_FIRST,
		AUTO_CHANGE_TURN_NORMAL_1,
		AUTO_GET_CARD,
		AUTO_THROW_CARD,
		AUTO_SHOW_PHOM,
		AUTO_SEND_CARD,
		AUTO_SHOW_RESULT,
		AUTO_END_GAME,
		CHECK_SUDDEN_WIN_STATE,
		AUTO_PLAY_CARD,
		AUTO_PASS,
		SUMMARY_STATE,
		END_GAME_STATE,
		WAIT_NEXT_GAME_STATE,
		REWARD_FAIL_STATE,
		REWARD_SUCCESS_STATE
	};
	enum GameState {
		NONE = -1,		//init
		WAITING = 0,	//wait for new game (after new match, before start match)
		PLAYING = 1,	//game in progress (after start match, before end match)
		ENDING = 2		//game in result (after end match, before new match
	};
	enum QuitReason {
		REASON_NONE = -100,
		REASON_GOLD = 0,
		REASON_READY = 1,
		REASON_EMPTY = 2,
		REASON_ERROR = 3,
		REASON_NETWORK = 4,
		REASON_AFK = 10
	};
	enum AutoStart {
		AUTO_NONE = 0,
		AUTO_CLICK = 1,
		AUTO_COUNTDOWN = 2
	};
	enum Rank {
		RANK_NHAT = 0,
		RANK_NHI = 1,
		RANK_BA = 2,
		RANK_BET = 3, 
		U_KHAN = 4,
		U_TRON = 5,
		U_NORMAL = 6,
		AN_CHOT = 7,
		RANK_MOM = -1
	};

	enum Time {
		TIME_CHANGE_TURN = 2,
		TIME_CHANGE_TURN_FIRST = 2,
		TIME_NOTIFY_U = 2,
		TIME_RESULT = 9,
		TIME_END_GAME = 2
	};

public:
	TalaGameLogic();
	~TalaGameLogic();
	static TalaGameLogic* _instance;
	static TalaGameLogic* getInstance();

public:
	//room config
	int roomIndex;
	long long roomBet;
	bool isModeSolo;
	char roomOwner;
	char rateBigBet;

	//game info
	char myChair;		//my chair index on serer, used as pivot to convert server chair to client chair
	char nDeckCard;
	bool regQuit;
	int quitReason;
	GameState gameState;

	vector<TalaPlayerInfo*> players;
	vector<TalaPlayerInfo> tempPlayerInfos;	//save data to load after take chair for view user
	float timeAuto;
	TalaScene *board;
	char currentTurn;
	vector<char> arrayCard;
	bool canGetCard;
	int idU;
	vector<int> idFirstShowPhom;
	int idWin;
	int typeU;
	AutoState autoState;
    CmdReceivedJoinRoomSuccess joinRoom;

    public:	//LISTENERS
	void onReceiveJoinRoomSuccess(const CmdReceivedJoinRoomSuccess &pk);
    void doJoinRoom();
	void onReceiveUserJoinRoom(const CmdReceivedUserJoinRoom &pk);
	void onReceiveQuitRoom(const CmdReceivedQuitRoom &pk);
	void onReceiveQuitReason(const CmdReceivedQuitReason &pk);
	void onReceiveQuitSuccess(const CmdReceivedQuitSuccess &pk);
	void onReceiveQuitResult(const CmdReceivedQuitResult &pk);
	void onReceiveUpdateOwner(const CmdReceivedUpdateOwner &pk);
	void onReceiveAutoStart(const CmdReceivedAutoStart &pk);
	void onReceiveNotifyStart(const CmdReceivedNotifyStart &pk);
	void onReceiveUpdateCards(const CmdReceivedUpdateCards &pk);
	void onReceiveThrowCard(const CmdReceivedThrowCard &pk);
	void onReceiveReceiveCard(const CmdReceivedReceiveCard &pk);
	void onReceiveChangeTurn(const CmdReceivedChangeTurn &pk);
	void onReceiveNotifyShowPhom(const CmdReceivedNotifyShowPhom &pk);
	void onReceiveShowPhom(const CmdReceivedShowPhom &pk);
	void onReceiveNotifyU(const CmdReceivedNotifyU &pk);
	void onReceiveNotifySendCard(const CmdReceivedNotifySendCard &pk);
	void onReceiveSendCard(const CmdReceivedSendCard &pk);
	void onReceiveTaiLuot(const CmdReceivedTaiLuot &pk);
	void onReceiveNewMatch(const CmdReceivedNewMatch &pk);
	void onReceiveContinueMatch(const CmdReceivedContinueMatch &pk);
	void onReceiveEndMatch(const CmdReceivedEndMatch &pk);
	void onReceiveViewGameInfo(const CmdReceivedViewGameInfo &pk);
	void onReceiveGameResult(const CmdReceivedGameResult &pk);
	void onReceiveUserTakeChair(const CmdReceivedUserTakeChair &pk);
	void onReceiveUserView(const CmdReceivedUserView &pk);
	void onReceiveRateBigBet(const CmdReceivedRateBigBet &pk);

	void onEnterBoard();
	void onExitBoard();
	void onSelectCard(char cardId);
	void onArrangeCard();
	void onThrowCard();
	void onShowSuits();
	void onSendCard();
	void onTouchLastThrowCard(char chair);
	void onTouchSuit(char chair, int suitIndex);
	void onDrawCard();
	void onStart();
	void onBeginMoveCard();
	void onEndMoveCard(char oldIdx, char newIdx);
	void onSelectPlayer(char chair);
	void onAddBot();
	void onRemoveBot(char chair);

public:	//GET - CHECK - CONVERT
	char serverChairToClientChair(char serverChair);	//convert server chair to client chair
	char clientChairToServerChair(char clientChair);	//convert client chair to server chair
	char getLastEnemyChair(char chair = 0);	//get client chair of last enemy
	bool isOwner();				//check if me the owner
	bool isWaiting();			//check if game in wating phase
	bool isPlaying();			//check if game in playing phase
	bool isEnding();			//check if game in ending phase
	char getRoomOwner();		//get client chair of owner
	int getNumPlaying();		//get num of playing players
	bool getIPCount(char chair);

public:	
	bool canGetLastCard();
	bool otherCanGetLastCard(char chair);
	void hintSendCard();
	bool canSendCard();
	void autoChangeNewTurn();
	int getThrowChair(char srcChair);
	void autoGenCard();
	void autoGetCard();
	void autoGetFromDeck();
	void autoThrowCard();
	void splitAutoThrowCard1(vector<char> arrayRandom);
	void splitAutoThrowCard2(vector<char> arrayRandom);
	void splitAutoThrowCard3(char card);
	void autoShowPhom();
	void autoShowResult();
	void genTimeAuto();
	int autoCheckU(bool checkUKhan);
	void autoNotifyU();

public:	//SET
	void clearRoomInfo();
	void clearAllCards();
	void setRoomInfo(int roomIndex, long long roomBet, bool isModeSolo);
	void setMyChair(char myChair);
	void setRoomOwner(char roomOwner);
	void setRateBigBet(char rateBigBet, bool animate = false);
	void setRegQuit(bool regQuit);
	void setQuitReason(char reason);
	void setGameState(GameState state);
	void setNDeckCard(char nDeckCard);

	void setPlayerStatus(char chair, char status);
	void setPlayerState(char chair, char state, char time=0);
	void setPlayerInfo(char chair, TalaPlayerInfo info);

	void onReward(int num);
	bool checkGetSupport();
	int countGame;
	void update(float delta);

    void autoStartState();
    void autoChangeTurnFirstState();
    void autoGetCardState();
    void autoThrowCardState();
    void autoShowPhomState();
    void autoSendCardState();
    void autoNotifyUState();
    void autoEndGameState();
    void autoRewardFailState();
    void autoRewardSuccessState();
};

#endif // TalaGameLogic_h__
