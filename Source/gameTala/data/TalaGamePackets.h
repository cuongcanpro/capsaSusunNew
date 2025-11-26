#ifndef TalaGamePackets_h__
#define TalaGamePackets_h__

#include <string>
#include <vector>
#include <map>
#include "TalaGameConstant.h"
#include "../logic/TalaPlayerInfo.h"
#include "axmol.h"
using namespace std;


struct CmdReceivedJoinRoomSuccess {
	char chair;
	long long roomBet;
	char roomOwner;
	int roomIndex;
	int roomId;
	int roomOwnerId;
	char rateBigBet;
	bool isModeSolo;
	vector<TalaPlayerInfo> playerInfos;

};

struct CmdReceivedUserJoinRoom {
	char chair;
	TalaPlayerInfo playerInfo;

};

struct CmdReceivedQuitResult {
	char result;

};

struct CmdReceivedUserView {
	char chair;
	TalaPlayerInfo playerInfo;

};

struct CmdReceivedUserTakeChair {
	char error;
	char chair;

};

struct CmdReceivedViewGameInfo {
	vector<bool> hasPlayer;
	char nDeckCard;
	char currentChair;
	char turnTime;
	int playerAction;

	struct PlayerCard {
		bool isShowCard;
		vector<int> handOnCards;
		vector<int> isEatens;
		vector<int> throwCards;
		vector<vector<int>> listPhom;
	};
	vector<PlayerCard> playerCards;

};

struct CmdReceivedAutoStart {
	bool isAutoStart;
	char time;
	char autoType;
	char chairStart;

};

struct CmdReceivedNotifyStart {
	vector<bool> isPlaying;
	char firstTurn;
	char nDeckCard;

};

struct CmdReceivedUpdateCards {
	vector<char> cards;	//card ids

};

struct CmdReceivedChangeTurn {
	bool canGetCard;
	char chair;
	char time;

};

struct CmdReceivedReceiveCard {
	char srcChair;
	char desChair;
	char throwChair;
	char cardId;
	bool anChot;
	char nEaten;
	long long nMoney;
	char nDeckCard;
	long long money;

};

struct CmdReceivedThrowCard {
	char chair;
	char cardId;

};

struct CmdReceivedNotifySendCard {
	char chair;
	char turnTime;

};

struct CmdReceivedSendCard {
	char senderChair;
	char senderCardId;
	char targetChair;
	char targetCardId;

};

struct CmdReceivedNotifyShowPhom {
	char turnTime;
	char chair;
	vector<char> allCards;
	vector<bool> eatCards;
	bool isMom;

};

struct CmdReceivedShowPhom {
	char chair;
	vector<char> cards;

};

struct CmdReceivedTaiLuot {
	char chair;

};

struct CmdReceivedNotifyU {
	char chair;
	vector<char> allCards;
	vector<char> eatCards;
	vector<double> playerMoneys;
	vector<double> dMoneys;

	char chairDen;
	bool isUTron;
	bool hasJackpot;

};

struct CmdReceivedGameResult {
	vector<double> moneyGet;
	vector<char> rank;
	vector<double> money;
	vector<bool> isMom;
    vector<int> arrayScore;
	bool hasJackpot;

};

struct CmdReceivedUpdateOwner {
	char chair;

};

struct CmdReceivedNewMatch {
	int roomId;
	char chair;
	vector<TalaPlayerInfo> playerInfos;
	vector<bool> willView;

};

struct CmdReceivedContinueMatch {
	char chair;
	long long roomBet;
	char roomOwner;
	int roomOwnerId;
	int roomIndex;
	int roomId;
	bool isBigBet;
	char rateBigBet;
	char turnTime;
	char currentChair;
	char nDeckCard;
	int playerAction;
	bool isModeSolo;
	vector<TalaPlayerInfo> playerInfos;
	
	struct PlayerCard {
		bool isShowCard;
		vector<int> handOnCards;
		vector<int> isEatens;
		vector<int> throwCards;
		vector<vector<int>> listPhom;
	};
	vector<PlayerCard> playerCards;

};

struct CmdReceivedEndMatch {
};

struct CmdReceivedQuitRoom {
	char chair;
	char takenChair;

};

struct CmdReceivedQuitReason {
	char chair;
	char reason;

};

struct CmdReceivedQuitSuccess {
};

struct CmdReceivedRateBigBet {
	char rateBigBet;

};

struct CmdReceivedUpdateJackpot {
	long long jackpot;

};

#endif // LobbyPackets_h__

