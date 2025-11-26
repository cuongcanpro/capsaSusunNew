#ifndef BinhGameLogic_h__
#define BinhGameLogic_h__
#include "BinhPlayerInfo.h"
#include "../data/GameConstant.h"
#include "../data/GamePackets.h"
#include "../ui/BinhCardButton.h"
#include "../data/GamePackets.h"
#include "axmol.h"

class BinhGameLogic 
{
public:
	BinhGameLogic();
	~BinhGameLogic();
	static BinhGameLogic* _instance;
	static BinhGameLogic* getInstance();

	
	bool IsVewing() const { return isViewing; }
	void IsVewing(bool val) { isViewing = val; }
	BinhGameState getGameState() const { return gameState; }
	void setGameState(BinhGameState val) { gameState = val; }
	

public:
	BinhPlayerInfo* arrayPlayer[NUM_PLAYER];
	char myChair;
	char betType;
	char roomBet;
	char roomOwner;
	double goldBet;
	int roomIndex;
	int roomId;
	char roomType;
	bool cuoclon;
	char zoneId;
	int roomOwnerId;
	int gameCount;
	bool isKick;
	double jackpotNumber;
	double gameTime;
	double targetTime;
	int countGame;
	int currentChi;
private:
	bool isViewing;
	BinhGameState gameState;
public:
	void joinRoomSuccess(BinhMsgJoinRoomSuccess msg);
	void setViewInfo(char gameState, int gameTime, vector<bool> isPlayings, vector<bool> playerStates);
	void autoStart(int time, bool isAutoStart);
	void newUserJoinRoom(BinhPlayerInfo* info);
	void userLeaveRoom(char chair);
	void updateRoomOwner(char chair);
	void notifyStart(vector<char> arrayCard, int gameCount, int time);
	void ready(char chair);
	void unReady(char chair);
	void endCard(char chair, vector<char> arrayId);
	void chiIndex(char chi);
	void compareChi(char chi, vector<double> arrayMoney, vector<int> arrayResult);
	void summary(vector<double> arrayMoney);
	void sapBai(vector<double> arrayMoney, vector <char> arraySapBai);
	void soBai(bool isMauBinh, vector<double> arrayMoney);
	void sapLang(char chair, vector<double> arrayMoney);
	void binhAt(vector<double> arrayMoney);
	void endGame();
	void jackpot(double money, int userId);
	void updateJackpot(double jackpotNumber);
	void regQuit(char chair, bool status);
	void kickFromRoom(char chair, char reason);
	void quitRoomSuccess();
public:
	char getChair(char chair);
	char getChairInServer(char chair);
	BinhPlayerInfo* getInfo(char chairInClient);
	void newGame();
	char convertRank(char rank);
	string getResourceRank(char rank);
	int getNumPlaying();
	bool isShowBtnStart();
	bool isInBoard();
	int getChairFromId(int id);
	UserInfo* getUserInfo(char chairClient);
	char getPlayerCardKind(vector <int> id, bool isTinhAt);
	int getZOrderCard(int index);
	int getCardIndex(int index, int chi);
	void setMyCard(vector<int> arrayId, vector<Vec2> arrayPos, vector<float> arraySize);
	string getResourceResult(bool isWin);
	int getNumEatChi(char chi, MaubinhPlayerCard* playerCard);
	bool isTinhAt();
	bool isMauBinh(int cardKind);
	string getResourceEffectChi(char chi, double Money, MaubinhPlayerCard* playerCard, bool &isEffectParticle, bool isSound);
	string getResourceEffectChiCompare(char chi, double Money, MaubinhPlayerCard* playerCard, bool &isEffectParticle, bool isSound);
	int getNumCompareBai();
	int getNumMauBinh();
	//string getEffectMaubinh(string &animation, char chair = -1);
	int getEffectMaubinh(char chair = -1);
	void sortArrayId(int* arrayArrange, int count, SortCard stateSort);
	int convert(int id);
	vector <int> getArrayCardBao();
	void showDarkCard(MaubinhPlayerCard playerCard, int cardKind, bool mauBinh, BinhCardButton* arrayCard []);
	void showDark2BigChi(MaubinhGroupCardLogic* gc1, int chi, BinhCardButton* arrayCard []);
	float getPercentTime();
	double getRemainTime();
	bool isShowAll();
	BinhPlayerInfo* getPlayerByUId(long long uId);
	int getCardKindReady();
	string getResourceBinh(int typeMaubinh);

	int compareChiWithPlayer(int chi, int chairClient);
	bool isOffline;
	float timeAuto;
	double arrayMoneySummary[4];
	int arrayLose[4];
	int arrayWin[4];

	vector <double> arrayMoneyMauBinh;
	void autoCompareChi(int chi);
	int getNumEatBinh(int kind);
	bool autoCheckMauBinh();
	bool autoCheckBinhLung();
	bool autoCheckBiSap();
	bool autoCheckBatSap();
	void onReward(int num);
	bool checkGetSupport();
    string getRes();
};
#endif // GameLogic_h__

