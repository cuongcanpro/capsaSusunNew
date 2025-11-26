#ifndef GameLogic_h__
#define GameLogic_h__
#include "gameTienlen/logic/PlayerInfo.h"
#include "gameTienlen/data/GameConstant.h"
#include "gameTienlen/data/GamePackets.h"
#include "axmol.h"
enum class GameState {
	GAME_WAITING,
	GAME_PLAYING,
	EFFECT_END_GAME,
	GAME_DEAL_CARD
};

class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	static GameLogic* _instance;
	static GameLogic* getInstance();

	
	bool IsVewing() const { return isViewing; }
	void IsVewing(bool val) { isViewing = val; }
	GameState getGameState() const { return gameState; }
	void setGameState(GameState val) { gameState = val; }
	
	bool CanPlayWithoutTurn() const { return canPlayWithoutTurn; }
	void CanPlayWithoutTurn(bool val) { canPlayWithoutTurn = val; }


public:
	PlayerInfo* arrayPlayer[NUM_PLAYER];
	char myChair;
	char betType;
	char roomBet;
	char roomOwner;
	int roomIndex;
	int roomId;
	char roomType;
	bool cuoclon;
	char zoneId;
	int roomOwnerId;
	bool isSoloMode;
	int gameCount;
	bool isFirstPlay;
	char chairSuddenWin;

	char rate;
	char turnId;
	char turnTime;
	char lastThrowId;
	bool isPosture;
	bool canShowCard;
	int countLose;

	TienlenGroupCard* lastCard;
	
	bool isKick;
	double jackpotNumber;
	bool isNewTurn;
	bool CanPlayVsLastCard() const { return canPlayVsLastCard; }
	void CanPlayVsLastCard(bool val) { canPlayVsLastCard = val; }
	float timeAuto;

private:
	bool isViewing;
	GameState gameState;
	bool canPlayWithoutTurn;
	bool canPlayVsLastCard; // bien luu lai lieu nguoi choi co the do duoc bo bai cuoi cung danh ra hay khong de han che tinh toan
public:
	void joinRoomSuccess(MsgJoinRoomSuccess msg);
	void updateInfoGame(MsgUpdateInfoGame msg);
	void setViewInfo(vector <int> numCards, vector <int> rank);
	void autoStart(int time, char type);
	void newUserJoinRoom(PlayerInfo* info);
	void userLeaveRoom(char chair);
	void updateRoomOwner(char chair);
	void notifyStart(int gameCount);
	void updateMyCard(vector<char> cardIds);
	void changeTurn(char playerTurn, char turnTime, bool isNewTurn);
	void passTurn(char playerId);
	void playCard(char playerId, vector<char> cards);
	void caculateEndGame();
	void suddenWin(char chair, char type);
	void endCard(char chair, vector<char> arrayId);
	void notifyGameResult(vector<double> moneys, vector<char> ranks, vector<bool> isCongs);
	void fineMoney(double money, char getChair, char loseChair);
	void endGame();
	void jackpot(double money, int userId);
	void updateJackpot(double jackpotNumber);
	void determineInGame();
	void regQuit(char chair, bool status);
	void kickFromRoom(char chair, char reason);
	void quitRoomSuccess();
	void bigBet(char rateBigBet);
public:
	char getChair(char chair);
	char getChairInServer(char chair);
	PlayerInfo* getInfo(char chairInClient);
	void newGame();
	char convertRank(char rank);
	string getResourceRank(char rank);
	int getNumPlaying();
	bool isSuddenWin();
	vector <int> getSuddenWinCard();
	bool isFirstPlayInSection();
	bool isShowBtnStart();
	void checkAutoCard();
	bool canPlay();
	bool checkCanThrowCard(vector <int> arraySelect);
	bool checkEffectPlayCard(char type);
	string getResourcePlayCard(char type);
	bool isInBoard();
	int getChairFromId(int id);
	bool isMyTurn();
	bool checkWrong3Space();
	PlayerInfo* getPlayerByUId(long long uId);

	void genStartGame();
	void autoPlay();
	int lastTurnPlay;
	void myPlay(vector<char> ids);
	int getMinNumCard();
	int getMaxNumCard();
	int getNextNumCard();
	void checkAutoSuddenWin();
	int lastWinId;
	int punishMoney;
	int punishChair;
	void onReward(int num);
	bool checkGetSupport();
	int countGame;
	int typeSuddenWin;
	int currentPosture;
	vector<int> arrayCard0[13];
	vector<int> arrayCard2[13];
	void startPosture(int level);
	void endPosture();
	void update(float delta);
};
#endif // GameLogic_h__

