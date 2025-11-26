#ifndef BinhGamePackets_h__
#define BinhGamePackets_h__
#include <string>
#include <vector>
#include "GameConstant.h"
#include "../logic/BinhPlayerInfo.h"


struct BinhMsgJoinRoomSuccess {
	char uChair;
	char roomBet;
	char roomOwner;
	int roomIndex;
	int roomId;
	char roomType;
	char* playerStatus;
	char betType;
	BinhPlayerInfo* playerList[NUM_PLAYER];
	char* vip;
	bool cuoclon;
	char zoneId;
	bool isLock;
	bool isSoloMode;
	int roomOwnerId;
};



#endif // BinhGamePackets_h__
