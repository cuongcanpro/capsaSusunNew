#include "InGameMgr.h"
#include "data/GamePackets.h"
#include "logic/GameLogic.h"
#include "data/GameConstant.h"
#include "ui/BoardScene.h"
#include <Game/Utility/JNIUtils.h>
InGameMgr::InGameMgr()
{

}

InGameMgr::~InGameMgr()
{

}

void InGameMgr::init() {

	
}

bool InGameMgr::isInBoard() {
	Node* scene = sceneMgr->getMainLayer();
	BoardScene* board = dynamic_cast<BoardScene*>(scene);
	if (board)
		return true;
	return false;
}

int InGameMgr::getChairFromId(int id) {
	return 0;
}

void InGameMgr::openBoardScene(bool isSolo)
{
    JNIUtils::showAdsBanner(0);
	MsgJoinRoomSuccess joinRoom;
	joinRoom.uChair = 0;
	joinRoom.roomBet = 1;
	joinRoom.roomOwner = 0;
	joinRoom.roomIndex = 1;
	joinRoom.roomId = 1;
	joinRoom.roomType = 0;

	vector<char>playerStatus;
	for (int i = 0; i < NUM_PLAYER; i++) {
		//playerStatus.push_back(i == 0 ? PlayerStatus::PLAYER_PLAY : PlayerStatus::PLAYER_NONE);
		if (i % 2 == 0 || isSolo == false)
			playerStatus.push_back(PlayerStatus::PLAYER_PLAY);
		else 
			playerStatus.push_back(PlayerStatus::PLAYER_NONE);
	}

	//int length = pk->getShort();
	for (int i = 0; i < NUM_PLAYER; i++) {
		joinRoom.playerList[i] = new PlayerInfo(i);
		joinRoom.playerList[i]->Status(playerStatus[i]);
	}

	//joinRoom.roomOwnerId = 1;
	joinRoom.isLock = false;

	GameLogic::getInstance()->joinRoomSuccess(joinRoom);
	//	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->openScene(BoardScene::className);
	//	gui->joinRoomSuccess();
}


// singleton mgr
InGameMgr* InGameMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new InGameMgr();
	}
	return _instance;
}

InGameMgr* InGameMgr::_instance = nullptr;


void InGameMgr::sendViewInfo()
{

}

void InGameMgr::sendStart()
{

}

void InGameMgr::sendAuthenConnect()
{

}


void InGameMgr::sendQuit()
{

}


void InGameMgr::sendCheatCard(vector <int> arrayCard)
{

}
