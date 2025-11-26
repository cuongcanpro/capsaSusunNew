#include "BinhInGameMgr.h"
#include "data/GamePackets.h"
#include "logic/BinhGameLogic.h"
#include "data/GameConstant.h"
#include "ui/BinhBoardScene.h"
#include <Game/Utility/JNIUtils.h>
BinhInGameMgr::BinhInGameMgr()
{

}

BinhInGameMgr::~BinhInGameMgr()
{

}

void BinhInGameMgr::init() {

	
	//Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
}

void BinhInGameMgr::update(float deltaTime)
{
}

bool BinhInGameMgr::isInBoard() {
	return false;
}

int BinhInGameMgr::getChairFromId(int id) {
	return 0;
}


void BinhInGameMgr::openBoardScene()
{
    JNIUtils::showAdsBanner(0);
	BinhMsgJoinRoomSuccess joinRoom;
	joinRoom.uChair = 0;
	joinRoom.roomBet = 1;
	joinRoom.roomOwner = 0;
	joinRoom.roomIndex = 1;
	joinRoom.roomId = 1;
	joinRoom.roomType = 0;
	
	vector<char>playerStatus;
	for (int i = 0; i < NUM_PLAYER; i++) {
		playerStatus.push_back(i == 0 ? BinhPlayerStatus::BINH_PLAYER_PLAY : BinhPlayerStatus::BINH_PLAYER_NONE);
	}

	//int length = pk->getShort();
	for (int i = 0; i < NUM_PLAYER; i++) {
		joinRoom.playerList[i] = new BinhPlayerInfo(i);
		joinRoom.playerList[i]->Status(playerStatus[i]);
	}

	joinRoom.roomOwnerId = 1;
	joinRoom.isLock = false;
	
	BinhGameLogic::getInstance()->joinRoomSuccess(joinRoom);
//	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->openScene(BoardScene::className);
//	gui->joinRoomSuccess();
}

void BinhInGameMgr::sendViewInfo()
{
	
}

void BinhInGameMgr::sendStart()
{
	
}

void BinhInGameMgr::sendAuthenConnect()
{
	
}


void BinhInGameMgr::sendQuit()
{
	
}

void BinhInGameMgr::sendConfirmInGame()
{
	
}

void BinhInGameMgr::sendCheatCard(vector <int> arrayCard)
{
	
}

void BinhInGameMgr::sendReady(vector<int> arrayId, TypeSend type)
{
	
}

void BinhInGameMgr::sendUnReady()
{
	
}

void BinhInGameMgr::sendBaoBinh()
{
	
}

void BinhInGameMgr::sendAddBot()
{
	
}

// singleton mgr
BinhInGameMgr* BinhInGameMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new BinhInGameMgr();
	}
	return _instance;
}

BinhInGameMgr* BinhInGameMgr::_instance = nullptr;

