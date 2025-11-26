#include "TalaInGameMgr.h"
#include "data/TalaGamePackets.h"
#include "logic/TalaGameLogic.h"
#include "data/TalaGameConstant.h"
#include "ui/TalaScene.h"
#include <Game/Utility/JNIUtils.h>
TalaInGameMgr::TalaInGameMgr()
{

}

TalaInGameMgr::~TalaInGameMgr()
{

}

void TalaInGameMgr::init() {

	
}

bool TalaInGameMgr::isInBoard() {
	Node* scene = sceneMgr->getMainLayer();
	TalaScene* board = dynamic_cast<TalaScene*>(scene);
	if (board)
		return true;
	return false;
}

int TalaInGameMgr::getChairFromId(int id) {
	return 0;
}

void TalaInGameMgr::openBoardScene(bool isSolo)
{
    JNIUtils::showAds(0);
	CmdReceivedJoinRoomSuccess joinRoom;
	joinRoom.chair = 0;
	joinRoom.roomBet = 1;
	joinRoom.roomOwner = 0;
	joinRoom.roomIndex = 1;
	joinRoom.roomId = 1;
	joinRoom.isModeSolo = false;

	vector<char>playerStatus;
	for (int i = 0; i < NUM_PLAYER; i++) {
		//playerStatus.push_back(i == 0 ? PlayerStatus::PLAYER_PLAY : PlayerStatus::PLAYER_NONE);
		if (i % 1 == 0 || isSolo == false)
			playerStatus.push_back(TalaPlayerInfo::STATUS_PLAYING);
		else 
			playerStatus.push_back(TalaPlayerInfo::STATUS_NONE);
	}

	//int length = pk->getShort();
	for (int i = 0; i < NUM_PLAYER; i++) {
		TalaPlayerInfo p;
		p.status = playerStatus[i];
		p.chair = i;
		p.serverChair = -1;
		p.gold = AXRANDOM_0_1() * 15000 + 30000;
		p.displayName = "Player " + to_string((int)(AXRANDOM_0_1() * 100));
		if (i == 0) {
			p.gold = gameMgr->goldTala;
			p.displayName = "You";
			p.winCount = gameMgr->winCountTala;
			int level = p.getLevel();
			int currentIdAvatar = level;
			if (currentIdAvatar > 19)
				currentIdAvatar = 19;
			//JNIUtils::sendEvent(("level_" + to_string(level)).c_str(), to_string(winCount).c_str());
			p.idAvatar = UserDefault::getInstance()->getIntegerForKey("idAvatarTala", currentIdAvatar);
			p.lostCount = gameMgr->lostCountTala;
		}
        else
        {
            p.winCount = floor(gameMgr->winCountTala * (1.2 - AXRANDOM_0_1() * 0.8));
            if (p.winCount < 0)
                p.winCount = 0;
        }

		joinRoom.playerInfos.push_back(p);
		//joinRoom.playerInfos[i] = TalaPlayerInfo(i);
		//joinRoom.playerInfos[i].status = (playerStatus[i]);
	}

	//joinRoom.roomOwnerId = 1;
	//joinRoom.isLock = false;



	TalaGameLogic::getInstance()->onReceiveJoinRoomSuccess(joinRoom);
	//	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->openScene(BoardScene::className);
	//	gui->joinRoomSuccess();
}


// singleton mgr
TalaInGameMgr* TalaInGameMgr::getInstance()
{
	if (!_instance)
	{
		_instance = new TalaInGameMgr();
	}
	return _instance;
}

TalaInGameMgr* TalaInGameMgr::_instance = nullptr;


void TalaInGameMgr::sendViewInfo()
{

}

void TalaInGameMgr::sendStart()
{

}

void TalaInGameMgr::sendAuthenConnect()
{

}


void TalaInGameMgr::sendQuit()
{

}


void TalaInGameMgr::sendCheatCard(vector <int> arrayCard)
{

}

string TalaInGameMgr::SOUND_ENTER_ROOM = "sounds/board/enter_room.mp3";
string TalaInGameMgr::SOUND_LEAVE_ROOM = "sounds/board/leave_room.mp3";
string TalaInGameMgr::SOUND_REG_QUIT = "sounds/board/reg_quit.mp3";
string TalaInGameMgr::SOUND_CANCEL_QUIT = "sounds/board/cancel_quit.mp3";
string TalaInGameMgr::SOUND_START_MATCH = "sounds/board/start_match.mp3";
string TalaInGameMgr::SOUND_TIMER = "sounds/board/timer.mp3";
string TalaInGameMgr::SOUND_DRAW_CARD = "sounds/board/draw_card.mp3";
string TalaInGameMgr::SOUND_EAT_CARD = "sounds/board/eat_card.mp3";
string TalaInGameMgr::SOUND_THROW_CARD = "sounds/board/throw_card.mp3";
string TalaInGameMgr::SOUND_ARRANGE_CARD = "sounds/board/arrange_card.mp3";
string TalaInGameMgr::SOUND_SELECT_CARD = "sounds/board/select_card.mp3";
string TalaInGameMgr::SOUND_HINT_SUIT = "sounds/board/hint_suit.mp3";
string TalaInGameMgr::SOUND_SHOW_SUIT = "sounds/board/show_suit.mp3";
string TalaInGameMgr::SOUND_SEND_CARD = "sounds/board/send_card.mp3";
string TalaInGameMgr::SOUND_RANK_WIN = "sounds/board/rank_win.mp3";
string TalaInGameMgr::SOUND_RANK_LOSE = "sounds/board/rank_lose.mp3";
string TalaInGameMgr::SOUND_RANK_U = "sounds/board/rank_u.mp3";
string TalaInGameMgr::SOUND_RANK_MOM = "sounds/board/rank_mom.mp3";
string TalaInGameMgr::SOUND_CHANGE_TURN = "sounds/board/player_bing.mp3";


vector<string> TalaInGameMgr::VOICE_DRAW_CARD = {
	"sounds/board/voice_draw_card1.mp3",
	"sounds/board/voice_draw_card2.mp3",
	"sounds/board/voice_draw_card3.mp3",
	"sounds/board/voice_draw_card4.mp3",
	"sounds/board/voice_draw_card5.mp3",
	"sounds/board/voice_draw_card6.mp3",
	"sounds/board/voice_draw_card7.mp3"
};
vector<string> TalaInGameMgr::VOICE_DRAW_LAST = {
	"sounds/board/voice_draw_last1.mp3",
	"sounds/board/voice_draw_last2.mp3",
	"sounds/board/voice_draw_last3.mp3",
	"sounds/board/voice_draw_last4.mp3",
	"sounds/board/voice_draw_last5.mp3"
};
vector<string> TalaInGameMgr::VOICE_EAT_CARD = {
	"sounds/board/voice_eat_card1.mp3",
	"sounds/board/voice_eat_card2.mp3",
	"sounds/board/voice_eat_card3.mp3",
	"sounds/board/voice_eat_card4.mp3",
	"sounds/board/voice_eat_card5.mp3",
	"sounds/board/voice_eat_card6.mp3",
	"sounds/board/voice_eat_card7.mp3",
	"sounds/board/voice_eat_card8.mp3",
	"sounds/board/voice_eat_card9.mp3"
};
vector<string> TalaInGameMgr::VOICE_EAT_LAST = {
	"sounds/board/voice_eat_last1.mp3",
	"sounds/board/voice_eat_last2.mp3",
	"sounds/board/voice_eat_last3.mp3",
	"sounds/board/voice_eat_last4.mp3",
	"sounds/board/voice_eat_last5.mp3"
};
vector<string> TalaInGameMgr::VOICE_THROW_CARD = {
	"sounds/board/voice_throw_card1.mp3",
	"sounds/board/voice_throw_card2.mp3",
	"sounds/board/voice_throw_card3.mp3",
	"sounds/board/voice_throw_card4.mp3",
	"sounds/board/voice_throw_card5.mp3",
	"sounds/board/voice_throw_card6.mp3"
};
vector<string> TalaInGameMgr::VOICE_THROW_LAST = {
	"sounds/board/voice_throw_last1.mp3",
	"sounds/board/voice_throw_last2.mp3",
	"sounds/board/voice_throw_last3.mp3",
	"sounds/board/voice_throw_last4.mp3"
};
vector<string> TalaInGameMgr::VOICE_ENTER_ROOM = {
	"sounds/board/voice_enter_room1.mp3",
	"sounds/board/voice_enter_room2.mp3",
	"sounds/board/voice_enter_room3.mp3",
	"sounds/board/voice_enter_room4.mp3",
	"sounds/board/voice_enter_room5.mp3",
	"sounds/board/voice_enter_room6.mp3"
};
vector<string> TalaInGameMgr::VOICE_LEAVE_ROOM = {
	"sounds/board/voice_leave_room1.mp3",
	"sounds/board/voice_leave_room2.mp3",
	"sounds/board/voice_leave_room3.mp3",
	"sounds/board/voice_leave_room4.mp3",
	"sounds/board/voice_leave_room5.mp3",
	"sounds/board/voice_leave_room6.mp3"
};
vector<string> TalaInGameMgr::VOICE_RANK_WIN = {
	"sounds/board/voice_rank_win1.mp3",
	"sounds/board/voice_rank_win2.mp3",
	"sounds/board/voice_rank_win3.mp3",
	"sounds/board/voice_rank_win4.mp3",
	"sounds/board/voice_rank_win5.mp3",
	"sounds/board/voice_rank_win6.mp3",
	"sounds/board/voice_rank_win7.mp3"
};
vector<string> TalaInGameMgr::VOICE_RANK_LOSE = {
	"sounds/board/voice_rank_lose1.mp3",
	"sounds/board/voice_rank_lose2.mp3",
	"sounds/board/voice_rank_lose3.mp3",
	"sounds/board/voice_rank_lose4.mp3",
	"sounds/board/voice_rank_lose5.mp3",
	"sounds/board/voice_rank_lose6.mp3"
};
vector<string> TalaInGameMgr::VOICE_TIMER = {
	"sounds/board/voice_timer1.mp3",
	"sounds/board/voice_timer2.mp3",
	"sounds/board/voice_timer3.mp3",
	"sounds/board/voice_timer4.mp3",
	"sounds/board/voice_timer5.mp3"
};
vector<string> TalaInGameMgr::VOICE_U = {
	"sounds/board/voice_u1.mp3",
	"sounds/board/voice_u2.mp3",
	"sounds/board/voice_u3.mp3",
	"sounds/board/voice_u4.mp3",
	"sounds/board/voice_u5.mp3"
};
vector<string> TalaInGameMgr::VOICE_UTRON = {
	"sounds/board/voice_utron1.mp3",
	"sounds/board/voice_utron2.mp3",
	"sounds/board/voice_utron3.mp3",
	"sounds/board/voice_utron4.mp3",
	"sounds/board/voice_utron5.mp3"
};


void TalaInGameMgr::sendStartGame()
{
	
}

void TalaInGameMgr::sendQuitGame()
{

}

void TalaInGameMgr::sendThrowCard(char id)
{
	
}

void TalaInGameMgr::sendGetCard(char chair)
{
	
}

void TalaInGameMgr::sendShowPhom(char chair, vector<char> cards)
{
	
}

void TalaInGameMgr::sendSendCard(char senderChair, char senderCard, char targetChair, char targetCard)
{
	
}

void TalaInGameMgr::sendViewGame()
{
	
}

void TalaInGameMgr::sendConnectRoom()
{
	
}

void TalaInGameMgr::sendCheatCard(vector<char> cards)
{
	
}

void TalaInGameMgr::sendAddBot()
{
	
}

void TalaInGameMgr::sendRemoveBot(char chair)
{
	
}
