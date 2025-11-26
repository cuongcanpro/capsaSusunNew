#ifndef GamePackets_h__
#define GamePackets_h__
#include <string>
#include <vector>
#include "GameConstant.h"
#include "../logic/PlayerInfo.h"

enum CMD_GAME {

	JOIN_ROOM = 3003,
	NEW_USER_JOIN = 3004,
	JOIN_ROOM_SUCCESS = 3005,
	JOIN_ROOM_FAIL = 3007,
	LEAVE_ROOM = 3008,
	LEAVE_ROOM_SUCCESS = 3009,
	NOTIFY_KICK_FROM_ROOM = 3010,
	UPDATE_OWNER_ROOM = 3011,
	AUTO_START = 3012,
	START_GAME = 3013,
	NOTIFY_START = 3014,
	NOTIFY_GAME_END = 3015,
	NOTIFY_GAME_RESULT = 3016,
	CHANGE_TURN = 3018,
	SUDDEN_WIN = 3019,
	UPDATE_MY_CARD = 3020,
	SEND_PLAY_CARD = 3021,
	PLAYER_CARD = 3021,
	PASS_TURN = 3022,
	FINE_MONEY = 3024,
	REG_QUIT = 3026,
	RECEIVE_END_CARDS = 3028,
	GET_RANK = 3029,
	NOT_REG_QUIT = 3030,
	SEND_DETERMINE_IN_TABLE = 3031,
	NOTIFY_USER_GET_JACKPOT = 3056,
	VIEW_GAME = 3059,
	NOTIFY_VIEW_INFO = 3060,
	UPDATE_INFO_GAME = 3061,
	AUTHEN_CONNECT = 3400,
	RECEIVE_JACKPOT = 2007,
	BIG_BET = 3300
};


struct MsgJoinRoomSuccess {
	char uChair;
	char roomBet;
	char roomOwner;
	int roomIndex;
	int roomId;
	char roomType;
	char* playerStatus;
	char betType;
	PlayerInfo* playerList[NUM_PLAYER];
	char* vip;
	bool cuoclon;
	char zoneId;
	bool isLock;
	bool isSoloMode;
};


struct MsgUpdateInfoGame {
	char uChair;
	char roomBet;
	char roomOwner;
	int roomIndex;
	int roomId;
	char roomType;
	vector <int> playerStatus;
	char betId;
	PlayerInfo* playerList[NUM_PLAYER];
	char* vip;
	bool cuoclon;
	char zoneId;
	bool isLock;
	vector <int> cards;
	vector <int> ranks;
	vector <int> lastCard;
	vector <int> myCard;
	vector <bool> players;
	int gameState;
	int turnId;
	int turnTime;
	char rate;
	bool isSoloMode;
};
#endif // LobbyPackets_h__
