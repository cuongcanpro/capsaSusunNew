#include "GameLogic.h"
#include "core/gui/SceneMgr.h"
#include "gameTienlen/ui/BoardScene.h"
#include "../InGameMgr.h"
#include "gamePlay/TienlenRule.h"
#include "Game/Utility/JNIUtils.h"

#define TIME_NORMAL 10
#define TIME_POSTURE 60
#define TIME_PRE_END_GAME 2

GameLogic::GameLogic()
{
	lastCard = new TienlenGroupCard();
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i] = new PlayerInfo(i);
	}
	lastThrowId = -1;
	turnId = 0;
	lastWinId = 0;
	countGame = 0;
	isPosture = false;
	// level 0
	int array0_0[11] = { 1,6,7,8,10,38,39,41,40,47,51 };
	
	for (int i = 0; i < 11; i++) {
		arrayCard0[0].push_back(array0_0[i]);
	}
	int array2_0[3] = { 12,49,50 };
	//int array2_0[13] = { 2,13,5,9,21,19,24,30,33,43,38,46,49 };
	for (int i = 0; i < 3; i++) {
		arrayCard2[0].push_back(array2_0[i]);
	}

	// level 1
	int array0_1[13] = { 5,7,10,8,15,28,30,34,32,40,41,44,50 };
	for (int i = 0; i < 13; i++) {
		arrayCard0[1].push_back(array0_1[i]);
	}
	int array2_1[3] = { 46,47,14 };
	for (int i = 0; i < 3; i++) {
		arrayCard2[1].push_back(array2_1[i]);
	}

	// level 2
	int array0_2[7] = { 3,5,8,14,17,49,50 };
	for (int i = 0; i < 7; i++) {
		arrayCard0[2].push_back(array0_2[i]);
	}
	int array2_2[8] = { 15,16,20,24,28,47,48,51 };
	for (int i = 0; i < 8; i++) {
		arrayCard2[2].push_back(array2_2[i]);
	}

	// level 3
	int array0_3[12] = { 2,6,10,14,19,22,26,30,34,39,41,42 };
	for (int i = 0; i < 12; i++) {
		arrayCard0[3].push_back(array0_3[i]);
	}
	int array2_3[12] = { 3,7,11,15,18,23,27,31,35,38,43,40 };
	for (int i = 0; i < 12; i++) {
		arrayCard2[3].push_back(array2_3[i]);
	}

	// level 4
	int array0_4[13] = { 1,3,7,11,15,19,23,27,31,35,39,46,47 };
	for (int i = 0; i < 13; i++) {
		arrayCard0[4].push_back(array0_4[i]);
	}
	int array2_4[13] = { 13,12,17,16,21,20,34,38,44,45,49,48,50 };
	for (int i = 0; i < 13; i++) {
		arrayCard2[4].push_back(array2_4[i]);
	}

	// level 5
	int array0_5[8] = { 20,21,25,31,34,39,46,47 };
	for (int i = 0; i < 8; i++) {
		arrayCard0[5].push_back(array0_5[i]);
	}
	int array2_5[7] = { 35,38,44,45,49,50,51 };
	for (int i = 0; i < 7; i++) {
		arrayCard2[5].push_back(array2_5[i]);
	}

	// level 6
	int array0_6[10] = { 11,9,35,34,18,16,41,42,47,51 };
	for (int i = 0; i < 10; i++) {
		arrayCard0[6].push_back(array0_6[i]);
	}
	int array2_6[3] = { 27,48,49 };
	for (int i = 0; i < 3; i++) {
		arrayCard2[6].push_back(array2_6[i]);
	}

	// level 7
	int array0_7[6] = { 48,51,35,45,3,2 };
	for (int i = 0; i < 6; i++) {
		arrayCard0[7].push_back(array0_7[i]);
	}
	int array2_7[7] = { 47,44,39,24,25,26,27 };
	for (int i = 0; i < 7; i++) {
		arrayCard2[7].push_back(array2_7[i]);
	}

	// level 8
	int array0_8[8] = { 17,21,25,28,32,36,49,50 };
	for (int i = 0; i < 8; i++) {
		arrayCard0[8].push_back(array0_8[i]);
	}
	int array2_8[9] = { 18,22,26,31,35,39,48,51,47 };
	for (int i = 0; i < 9; i++) {
		arrayCard2[8].push_back(array2_8[i]);
	}

	// level 9
	int array0_9[11] = { 4,5,10,12,19,21,27,29,34,42,43 };
	for (int i = 0; i < 11; i++) {
		arrayCard0[9].push_back(array0_9[i]);
	}
	int array2_9[13] = { 9,14,13,18,17,20, 25, 30,33,41,40,47,45 };
	for (int i = 0; i < 13; i++) {
		arrayCard2[9].push_back(array2_9[i]);
	}

	// level 10
	int array0_10[10] = { 10,11,25,24,39,37,44,47,48,51 };
	for (int i = 0; i < 10; i++) {
		arrayCard0[10].push_back(array0_10[i]);
	}
	int array2_10[4] = { 45,46,49,50 };
	for (int i = 0; i < 4; i++) {
		arrayCard2[10].push_back(array2_10[i]);
	}

	// level 11
	int array0_11[12] = { 2,1,0,13,12,14,21,27,28,34,45,46 };
	for (int i = 0; i < 12; i++) {
		arrayCard0[11].push_back(array0_11[i]);
	}
	int array2_11[11] = { 8,9,10,11,20,26,29,35,41,44,47 };
	for (int i = 0; i < 11; i++) {
		arrayCard2[11].push_back(array2_11[i]);
	}

	// level 12
	int array0_12[10] = { 1,6,8,9,10,11,15,18,49,50 };
	for (int i = 0; i < 10; i++) {
		arrayCard0[12].push_back(array0_12[i]);
	}
	int array2_12[8] = { 13,17,22,27,24,31,48,51 };
	for (int i = 0; i < 8; i++) {
		arrayCard2[12].push_back(array2_12[i]);
	}
}

GameLogic::~GameLogic()
{

}
GameLogic* GameLogic::_instance;
GameLogic* GameLogic::getInstance()
{
	if (!_instance)
	{
		_instance = new GameLogic();
	}
	return _instance;
}

void GameLogic::joinRoomSuccess(MsgJoinRoomSuccess msg)
{
	isFirstPlay = true;
	newGame();
	isKick = false;
	myChair = msg.uChair;
	roomBet = msg.roomBet;
	roomOwner = msg.roomOwner;
	roomIndex = msg.roomIndex;
	roomId = msg.roomId;
	roomType = msg.roomType;
	cuoclon = msg.cuoclon;
	isSoloMode = msg.isSoloMode;
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i] = msg.playerList[i];
	}
	if (msg.playerList[msg.uChair]->Status() == PlayerStatus::PLAYER_VIEWING) {
		inGameMgr->sendViewInfo();
		gameState = GameState::GAME_PLAYING;
	}
	else {
		gameState = GameState::GAME_WAITING;
	}
	
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->openScene(BoardScene::className);
	//gui->joinRoomSuccess();
	
	AXLOGD("MY CHAIR %i ", myChair);
}

void GameLogic::updateInfoGame(MsgUpdateInfoGame msg)
{
	newGame();
	isKick = false;
	myChair = msg.uChair;
	roomBet = msg.roomBet;
	roomOwner = msg.roomOwner;
	roomIndex = msg.roomIndex;
	roomId = msg.roomId;
	roomBet = msg.betId;
	roomType = msg.roomType;
	rate = msg.rate;
	isSoloMode = msg.isSoloMode;
	//cuoclon = msg.cuoclon;
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i] = msg.playerList[i];
		arrayPlayer[i]->NumCard(msg.cards[i]);
		if (i == myChair) {
			arrayPlayer[i]->setArrayCard(msg.myCard);
		}
	}
	turnId = msg.turnId;
	turnTime = msg.turnTime;
	gameState = GameState::GAME_PLAYING;
	lastCard->RemoveAllCards();
	lastCard->addCardWithIDs(msg.lastCard);
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->openScene(BoardScene::className);
	//gui->updateInfoGame();
	gui->joinRoomSuccess();
	gui->updateBigBet();
	gui->callbackEndDealCard();
	vector <int> arrayId = GameLogic::getInstance()->lastCard->getListId();
	gui->playCard(lastCard->getListId(), -1, lastCard->getTypeGroupCard());
	gui->changeTurn(false, getChair(turnId), turnTime);
}

void GameLogic::setViewInfo(vector <int> numCards, vector <int> rank)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->NumCard(numCards[i]);
		if (arrayPlayer[i]->isPlaying() && rank[i] > 0) {
			// set Rank cho nguoi nay, khong con mode choi truyen thong nen doan nay bo
		}
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->setViewInfo();
	}
}

void GameLogic::autoStart(int time, char type)
{
	AXLOGD("Type auto start %i ", type);
	if (type == 2) {
		// Dem Countdown
	}
	else {
		// Dung Countdown
	}
	if (gameState == GameState::GAME_WAITING) {
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->autoStart(time, type);
	}
}

void GameLogic::newUserJoinRoom(PlayerInfo* info)
{
	arrayPlayer[info->Chair()] = info;
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->newUserJoinRoom(getChair(info->Chair()), info);
}

void GameLogic::userLeaveRoom(char chair)
{
	if (chair == -1)
		return;
	if (chair == myChair)
		return;
	arrayPlayer[chair]->Status(PlayerStatus::PLAYER_NONE);
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->userLeave(getChair(chair));
}

void GameLogic::updateRoomOwner(char chair)
{
	roomOwner = chair;
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->updateRoomOwner();
}

void GameLogic::notifyStart(int gameCount)
{
	this->gameCount = gameCount;
	//isFirstPlay = true;
	gameState = GameState::GAME_DEAL_CARD;
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->notifyStart();
	countGame++;
}

void GameLogic::updateMyCard(vector<char> cardIds)
{
	arrayPlayer[myChair]->setArrayCard(cardIds);
	AXLOGD("UPDATE MY CARD");
	arrayPlayer[myChair]->printPlayerCard();
	if (gameState == GameState::GAME_DEAL_CARD)
		return;
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->updateMyCard();
}

void GameLogic::changeTurn(char playerTurn, char turnTime, bool isNewTurn)
{
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	if (gui->autoState != END_GAME_STATE && gui->autoState != PRE_END_GAME_STATE) {
		if (playerTurn != 0) {
			gui->autoState = AUTO_PLAY_CARD;
			timeAuto = 1;
		}
		else {
			timeAuto = TIME_NORMAL;
			if (isPosture) {
				timeAuto = TIME_POSTURE;
			}
			gui->autoState = AUTO_PASS;
		}
	}
	else {
		return;
	}
	if (isNewTurn) {
		if (punishMoney > 0)
			fineMoney(punishMoney, lastThrowId, punishChair);
		punishMoney = 0;
		lastCard->RemoveAllCards();
		lastThrowId = -1;
		CanPlayVsLastCard(true);
		for (int i = 0; i < NUM_PLAYER; i++) {
			arrayPlayer[i]->isPass = false;
		}
	}
	else {
		if (playerTurn == myChair)
			CanPlayVsLastCard(arrayPlayer[myChair]->canPlay(lastCard));
	}
	
	this->isNewTurn = isNewTurn;
	turnId = playerTurn;
	
	gui->changeTurn(isNewTurn, getChair(playerTurn), turnTime);
	AXLOGD("CHANGE TURN ");
	arrayPlayer[myChair]->printPlayerCard();
	
}

void GameLogic::passTurn(char playerId)
{
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->pass(getChair(playerId));
	AXLOGD("PASS TURN ");
	arrayPlayer[playerId]->isPass = true;
	if (playerId == 0) {
		
	}
}

void GameLogic::playCard(char playerId, vector<char> cards)
{
	AXLOGD("PLAY CARD *** Start ");
	arrayPlayer[myChair]->printPlayerCard();
	CanPlayWithoutTurn(false);
	isFirstPlay = false;
	
	// tru tien neu lay bo dac biet chat 2 hoac bo dac biet
	int groupKind1 = lastCard->GetGroupKind();
	int punish = TienlenRule::getThoi(lastCard);
	if (punish > 0) {
		//fineMoney(punish * 1000, playerId, lastTurnPlay);
		punishMoney = punish * 1000;
		punishChair = lastTurnPlay;
	}
	else {
		punishMoney = 0;
	}

	vector <int> arrayId;
	lastCard->RemoveAllCards();
	for (int i = 0; i < cards.size(); i++) {
		//if (playerId == myChair) {
			arrayPlayer[playerId]->removeCard(cards[i]);
		//}
		arrayId.push_back(cards[i]);
	}
	lastCard->addCardWithIDs(arrayId);
	int groupKind = lastCard->GetGroupKind();
	if (lastCard->GetNumber() == 15) {
		punishMoney = 0;
	}
	
	lastThrowId = playerId;
	lastTurnPlay = playerId;
	if (playerId != myChair) {
		if (lastCard->canWithoutTurn()) {
			// kiem tra xem minh co duoc auto danh khong
			PlayerInfo* info = arrayPlayer[myChair];
			CanPlayWithoutTurn(info->checkCanPlayWithoutTurn(lastCard));
			
		}
		arrayPlayer[playerId]->NumCard(arrayPlayer[playerId]->NumCard() - arrayId.size());
	}
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->playCard(arrayId, getChair(playerId), lastCard->getTypeGroupCard(), arrayPlayer[playerId]->PlayerCard()->getListIdCard().size() == 0);
	//AXLOGD("PLAY CARD **** END ");
	//arrayPlayer[myChair]->printPlayerCard();

	if (arrayPlayer[playerId]->PlayerCard()->getListIdCard().size() == 0) {
		gui->autoState = PRE_END_GAME_STATE;
		timeAuto = TIME_PRE_END_GAME;
	}
}

void GameLogic::caculateEndGame() {
	int playerId = lastThrowId;
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->setSuddenWin(-1);
		if (i != playerId && arrayPlayer[i]->isPlaying()) {
			endCard(i, arrayPlayer[i]->PlayerCard()->getListIdCardByChar());
		}
	}

	// end Game
	vector<double> moneys;
	vector<char> ranks;
	vector<bool> isCong;

	int countMoney = 0;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->isPlaying()) {
			if (i != playerId) {
				int numLose = this->arrayPlayer[i]->PlayerCard()->getThoi();
				numLose = numLose + 3;
				if (arrayPlayer[i]->PlayerCard()->getListIdCard().size() == NUM_CARD) {
					numLose = numLose * 2;
					isCong.push_back(true);
					//ranks.push_back(6);
					ranks.push_back(RANK_CONG);
				}
				else {
					isCong.push_back(false);
					//ranks.push_back(4);
					ranks.push_back(RANK_BET);
				}
				countMoney = countMoney + numLose;
				moneys.push_back(-numLose * 1000);

			}
			else {
				//ranks.push_back(1);
				ranks.push_back(RANK_NHAT);
				moneys.push_back(0);
				isCong.push_back(false);
			}
		}
		else {
			ranks.push_back(-1);
			moneys.push_back(0);
			isCong.push_back(false);
		}
	}

	//moneys.insert(moneys.begin(), playerId, countMoney * 1000);
	moneys[playerId] = countMoney * 1000;
	lastWinId = playerId;
	notifyGameResult(moneys, ranks, isCong);
}

// goi suddenWin se den truoc goi end Card
void GameLogic::suddenWin(char chair, char type)
{
	typeSuddenWin = type;
	chairSuddenWin = chair;
	arrayPlayer[chair]->setSuddenWin(type);
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->suddenWin();
}

void GameLogic::endCard(char chair, vector<char> arrayId)
{
	arrayPlayer[chair]->setEndCard(arrayId);
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->endCard(getChair(chair));
}

void GameLogic::notifyGameResult(vector<double> moneys, vector<char> ranks, vector<bool> isCong)
{
	inGameMgr->sendAuthenConnect();
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (isPosture)
			moneys[i] = 0;
		arrayPlayer[i]->Gold(arrayPlayer[i]->Gold() + moneys[i]);
	}
	if (isPosture == false) {
		if (moneys[0] > 0) {
			arrayPlayer[0]->WinCount(arrayPlayer[0]->WinCount() + 1);
		}
		else {
			arrayPlayer[0]->LostCount(arrayPlayer[0]->LostCount() + 1);
		}
	}
	
	gui->notifyGameResult(moneys, ranks, isCong);
	gui->autoState = END_GAME_STATE;
	timeAuto = 6;
}

void GameLogic::fineMoney(double money, char getChair, char loseChair)
{
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	//if (getChair == 0) {
		arrayPlayer[getChair]->Gold(arrayPlayer[getChair]->Gold() + money);
	//}
	//if (loseChair == 0) {
		arrayPlayer[loseChair]->Gold(arrayPlayer[loseChair]->Gold() - money);
	//}
	gui->fineMoney(money, this->getChair(getChair), this->getChair(loseChair));
}

void GameLogic::endGame()
{
	gameMgr->checkCanPlayEffect();
	if (isPosture) {
		if (lastWinId == 0) {
			//if (countGame > AXRANDOM_0_1() * 2 + 2) {
				if (gameMgr->useAds)
					    JNIUtils::showAdsFull();
				countGame = 0;
			//}
			// Show thong bao hoan thanh Level
			string s;
			if (currentPosture >= 12) {
				s = s + LocalizedString::to("THANK_YOU");
			}
			else {
				s = LocalizedString::to("FINISH_LEVEL");
				s = StringUtility::replaceAll(s, "@level", to_string(currentPosture + 1));
				s = s + LocalizedString::to("NEXT_LEVEL");
				// tang level hien tai
				currentPosture++;
				if (currentPosture > gameMgr->currentPosture) {
					gameMgr->currentPosture = currentPosture;
					UserDefault::getInstance()->setIntegerForKey("currentPosture", gameMgr->currentPosture);
					UserDefault::getInstance()->flush();
				}
			}
			sceneMgr->showOkDialogWithAction(s, [this](int btnId) {

			});
			startPosture(currentPosture);
		}
		else {
			if (countGame > AXRANDOM_0_1() * 2 + 2) {
				if (gameMgr->useAds)
					    JNIUtils::showAdsFull();
				countGame = 0;
			}
			// show thong bao that bai
			string s = LocalizedString::to("LOSE_LEVEL");
			sceneMgr->showOkDialogWithAction(s, [this](int btnId) {

			});
			countLose++;
			if (countLose >= 3) {
				canShowCard = true;
			}
		}
	}
	else {
		if (countGame > AXRANDOM_0_1() * 3 + 2) {
                    if (gameMgr->useAds)
                        JNIUtils::showAdsFull();
			countGame = 0;
		}
	}
	newGame();
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->newGame();

}

void GameLogic::jackpot(double money, int userId)
{
	if (userId == arrayPlayer[myChair]->ID()) {
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->jackpot(money);
	}
}

void GameLogic::updateJackpot(double jackpotNumber)
{
	AXLOGD("UPDATE JACKPOT %d", jackpotNumber);
	this->jackpotNumber = jackpotNumber;
	if (isInBoard()) {
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->updateJackpot();
	}
}

void GameLogic::determineInGame()
{
	if (!isInBoard())
		return;
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->determineInGame();
	inGameMgr->sendAuthenConnect();
}

void GameLogic::regQuit(char chair, bool status)
{
	AXLOGD("REG QUIT %s ", status ? "true" : "false");
	if (!isInBoard()) {
		return;
	}
	//if (chair == myChair) {
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->regQuit(status);
	//}
}

void GameLogic::kickFromRoom(char chair, char reason)
{
	AXLOGD("KICK ROOM %i %i ", chair, reason);
	arrayPlayer[chair]->Status(PlayerStatus::PLAYER_NONE);
	if (isInBoard()) {
		if (chair == myChair)
			isKick = true;
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->kickFromRoom(getChair(chair), reason);
	}
}

void GameLogic::quitRoomSuccess()
{
	AXLOGD("QUIT ROOM %s ", isKick ? "TRUE " : " false");
	if (isKick)
		return;
}

void GameLogic::bigBet(char rateBigBet)
{
	rate = rateBigBet;
	if (isInBoard()) {
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->updateBigBet();
	}
}

/**
 * Convert chair Tu Server thanh duoi Client
 */
char GameLogic::getChair(char chair)
{
	return (chair + 4 - this->myChair) % 4;
}

char GameLogic::getChairInServer(char chair)
{
	return (chair + this->myChair) % 4;
}

PlayerInfo* GameLogic::getInfo(char chairInClient) 
{
	return arrayPlayer[getChairInServer(chairInClient)];
}

void GameLogic::newGame()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->newGame();
	}
	chairSuddenWin = -1;
	lastThrowId = -1;
	rate = 0;
	punishMoney = 0;
	gameState = GameState::GAME_WAITING;
	CanPlayVsLastCard(true);
	CanPlayWithoutTurn(false);
	lastCard->RemoveAllCards();
}

char GameLogic::convertRank(char rank)
{
	if (rank == getNumPlaying()) {
		rank = NUM_PLAYER;
	}
	else if (rank == 0) {
		return RANK_TOI_TRANG;
	}
	return rank;
}

string GameLogic::getResourceRank(char rank)
{
	string resource;
	switch (rank)
	{
	case GameRank::RANK_BA:
		resource = "ba";
		break;
	case GameRank::RANK_BET:
		resource = "Bon";
		break;
	case GameRank::RANK_NHI:
		resource = "Nhi";
		break;
	case GameRank::RANK_NHAT:
		resource = "Nhat";
		break;
	case GameRank::RANK_CONG:
		resource = "Cong";
		break;
	case GameRank::RANK_TOI_TRANG:
		resource = "Toitrang_1";
		break;
	default:
		resource = "ba";
		break;
	}
	AXLOGD("RESOURCE RANK %s ", resource.c_str());
	return resource;
}

int GameLogic::getNumPlaying()
{
	int count = 0;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->isPlaying()) {
			count++;
		}
	}
	return count;
}

bool GameLogic::isSuddenWin()
{
	return chairSuddenWin >= 0;
}

vector<int> GameLogic::getSuddenWinCard()
{
	return arrayPlayer[chairSuddenWin]->Game()->WinCards;
}

/**
 * Kiem tra xem co phai lan danh dau tien ke tu khi ban choi duoc tao ra khong
 */
bool GameLogic::isFirstPlayInSection()
{
	return gameCount == 0 && isFirstPlay;
}

bool GameLogic::isShowBtnStart()
{
	if (myChair == roomOwner) {
		return true;
	}
	return false;
}

void GameLogic::checkAutoCard()
{
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	vector <int> arrayId = gui->getArrayCardSelect();
	TienlenGroupCard* groupCard = new TienlenGroupCard();
	groupCard->setCard(arrayId);
	vector<int> arrayAuto = arrayPlayer[myChair]->checkAutoCard(lastCard, groupCard);
	gui->autoCard(arrayAuto);
	delete groupCard;
}

bool GameLogic::canPlay()
{
	CanPlayVsLastCard(arrayPlayer[myChair]->canPlay(lastCard));
	return CanPlayVsLastCard();
}

bool GameLogic::checkCanThrowCard(vector <int> arraySelect)
{
	if (!isMyTurn() && !CanPlayWithoutTurn())
		return false;
	//AXLOGD("checkCanThrowCard");
	//arrayPlayer[myChair]->printPlayerCard();
	return arrayPlayer[myChair]->checkCanThrowCard(lastCard, arraySelect);
}

bool GameLogic::checkEffectPlayCard(char type)
{
	bool isEffect = false;
	switch (type) {
	case TOI_TRANG:
	case EG_BA_CON_HAI:
	case EG_DOI_HAI: {
		isEffect = true;
		break;
	}
	case EG_SUPER:
	case EG_ULTRA:
	case EG_BIGGER:
	case EG_TU_QUY: {
		isEffect = true;
		break;
	}
	default:
		break;
	}
	return isEffect;
}

std::string GameLogic::getResourcePlayCard(char type)
{
	string sEffect;
	switch (type) {
	case EG_BA_CON_HAI:
		sEffect = "3con2";
		break;
	case EG_DOI_HAI:
		sEffect = "doi2";
		break;
	case EG_SUPER:
		sEffect = "4doithong";
		break;
	case EG_ULTRA:
		sEffect = "5doithong";
		break;
	case EG_BIGGER:
		sEffect = "3doithong";
		break;
	case EG_TU_QUY:
		sEffect = "tuquy";
		break;
	case TOI_TRANG:
		sEffect = "toitrang";
		break;
	default:
		sEffect = "3con2";
		break;
	}
	return sEffect;
}

bool GameLogic::isInBoard()
{
	BoardScene* board = dynamic_cast<BoardScene*>(sceneMgr->getMainLayer());
	if (board != nullptr) {
		return true;
	}
	return false;
}

int GameLogic::getChairFromId(int id)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->ID() == id) {
			return i;
		}
	}
	return -1;
}

bool GameLogic::isMyTurn()
{
	return myChair == turnId;
}

bool GameLogic::checkWrong3Space()
{
	PlayerInfo* info = arrayPlayer[myChair];
	if (isFirstPlayInSection() && info->PlayerCard()->Has3Spade())
		return true;
	return false;
}

PlayerInfo * GameLogic::getPlayerByUId(long long uId)
{
	for (auto playerInfo : arrayPlayer) {
		if (playerInfo && playerInfo->ID() == uId) return playerInfo;
	}
	return nullptr;
}

void GameLogic::genStartGame()
{
	//GameLogic::getInstance()->arrayPlayer[0]->setArrayCard(arrayId);
	vector <char> arrayAutoCard[NUM_PLAYER];
	vector<char> arrayId;
	for (int i = 0; i < 52; i++) {
		arrayId.push_back(i);
	}
	vector<char> cardIds;
	string s = "";
	for (int i = 0; i < NUM_PLAYER; i++)
		arrayAutoCard[i].clear();
	for (int i = 0; i < 52; i++) {
		int value = AXRANDOM_0_1() * arrayId.size() * 0.999f;
		arrayAutoCard[i % 4].push_back(arrayId[value]);
		s = s + ", " + to_string(arrayId[value]);
		arrayId.erase(arrayId.begin() + value);
		
	}

	//arrayAutoCard[0].clear();
	//arrayAutoCard[2].clear();

    int arr3[13] = {1, 5, 10, 13, 18, 20, 24, 29, 33, 39, 42, 46, 49};
	//int arr3[13] = { 37, 36, 38, 39, 5, 4, 47, 28, 4, 8, 9, 30, 31 };
	//int arr3[13] = { 0, 1, 2, 4, 30, 11, 15, 17, 21, 25, 50, 51, 49 };
	//int arr3[13] = { 0, 1, 2, 4, 5, 9, 11, 31, 30, 34, 35, 41, 42};  // luc phe bon
	//int arr3[13] = { 0, 8, 12, 20, 24, 1, 9, 25, 29, 37, 2, 10, 14 }; // 3 cai thung
	//int arr3[13] = { 0, 4, 8, 12, 16, 1, 5, 9, 13, 17, 22, 11, 14 }; // 3 cai thung
	//int arr3[11] = { 0,7,6,10,9,39,38,41,40,47,51 };
	for (int j = 0; j < 13; j++) {
		//arrayAutoCard[0].push_back(arr3[j]);
	}
        for (int j = 0; j < 13; j++)
        {
            //arrayAutoCard[2].push_back(arr3[j]);
        }
	

	if (isPosture) {
		arrayAutoCard[0].clear();
		arrayAutoCard[2].clear();
		//arrayAutoCard[0].clear();

		//int arr3[13] = { 37, 33, 21, 13, 5, 48, 44, 28, 4, 0, 43, 26, 23 };
		//int arr3[13] = { 0, 1, 2, 4, 5, 8, 13, 17, 21, 30, 31, 26, 23 };
		int arr3[13] = { 0, 1, 4, 5, 9, 11, 31, 30, 34, 35, 41, 42, 50 };  // luc phe bon
		//int arr3[13] = { 0, 8, 12, 20, 24, 1, 9, 25, 29, 37, 2, 10, 14 }; // 3 cai thung
		//int arr3[13] = { 0, 4, 8, 12, 16, 1, 5, 9, 13, 17, 22, 11, 14 }; // 3 cai thung
		//int arr3[11] = { 0,7,6,10,9,39,38,41,40,47,51 };
		for (int j = 0; j < arrayCard0[currentPosture].size(); j++) {
			arrayAutoCard[0].push_back(arrayCard0[currentPosture][j]);
		}
		int arr2[3] = { 12,50,49 };
		for (int j = 0; j < arrayCard2[currentPosture].size(); j++) {
			arrayAutoCard[2].push_back(arrayCard2[currentPosture][j]);
		}
	}

	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->setArrayCard(arrayAutoCard[i]);
		arrayPlayer[i]->sortCard(true);
	}
	
	BoardScene* board = dynamic_cast<BoardScene*>(sceneMgr->getMainLayer());
	board->autoState = AUTO_START_STATE;
	//board->arrayPlayer[0]->endDealCard();
	if (isFirstPlay) {
		int min = 52;
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (arrayPlayer[i]->isPlaying()) {
				vector<int>cards = arrayPlayer[i]->PlayerCard()->getListIdCard();
				for (int j = 0; j < cards.size(); j++) {
					if (cards.at(j) < min) {
						lastWinId = i;
						min = cards.at(j);
						break;
					}
				}
			}
		}
		isFirstPlay = false;
	}
	else {
		if (isPosture)
			lastWinId = 0;
	}
	notifyStart(1);
}

void GameLogic::autoPlay()
{
	//turnId = 0;
	vector<char> arr = arrayPlayer[turnId]->getAutoPlayCard(lastCard, getMinNumCard(), getMaxNumCard(), getNextNumCard());
	if (arr.size() > 0)
		playCard(turnId, arr);
	else {
		// bo luot
		passTurn(turnId);
	}
	while (true) {
		turnId--;
		if (turnId < 0)
			turnId = 3;
		if (this->arrayPlayer[turnId]->isPlaying() && arrayPlayer[turnId]->isPass == false) {
			int time = TIME_NORMAL;
			if (isPosture)
				time = TIME_POSTURE;
			changeTurn(turnId, time, lastTurnPlay == turnId);
			break;
		}
	}
}

void GameLogic::myPlay(vector<char> ids)
{
	if (ids.size() > 0)
		playCard(turnId, ids);
	else {
		// bo luot
		passTurn(turnId);
	}
	while (true) {
		turnId--;
		if (turnId < 0)
			turnId = 3;
		if (this->arrayPlayer[turnId]->isPlaying() && arrayPlayer[turnId]->isPass == false) {
			int time = TIME_NORMAL;
			if (isPosture)
				time = TIME_POSTURE;
			changeTurn(turnId, time, lastTurnPlay == turnId);
			break;
		}
	}
}

int GameLogic::getMinNumCard()
{
	int min = 13;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (this->arrayPlayer[i]->isPlaying()) {
			if (min > this->arrayPlayer[i]->PlayerCard()->getListIdCard().size()) {
				min = this->arrayPlayer[i]->PlayerCard()->getListIdCard().size();
			}
		}
	}
	return min;
}

int GameLogic::getMaxNumCard()
{
	int max = 0;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (this->arrayPlayer[i]->isPlaying()) {
			if (max < this->arrayPlayer[i]->PlayerCard()->getListIdCard().size()) {
				max = this->arrayPlayer[i]->PlayerCard()->getListIdCard().size();
			}
		}
	}
	return max;
}

int GameLogic::getNextNumCard()
{
	int turnIdTemp = turnId;
	while (true) {
		turnIdTemp--;
		if (turnIdTemp < 0)
			turnIdTemp = 3;
		if (arrayPlayer[turnIdTemp]->isPlaying() && arrayPlayer[turnIdTemp]->isPass == false) {
			break;
		}
	}
	return this->arrayPlayer[turnIdTemp]->PlayerCard()->getListIdCard().size();
}

void GameLogic::checkAutoSuddenWin()
{
	int chairWin = -1;
	for (int i = 0; i < NUM_PLAYER; i++) {
		int convertId = (lastWinId + i) % NUM_PLAYER;
		if (arrayPlayer[convertId]->isPlaying()) {
			int typeSuddenWin = arrayPlayer[convertId]->PlayerCard()->getSuddenWin();
			if (typeSuddenWin != ST_NONE) {
				suddenWin(convertId, typeSuddenWin);
				chairWin = convertId;
				break;
			}
		}
	}

	if (chairWin >= 0) {
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (arrayPlayer[i]->isPlaying()) {
				endCard(i, arrayPlayer[i]->PlayerCard()->getListIdCardByChar());
			}
		}

		// end Game
		vector<double> moneys;
		vector<char> ranks;
		vector<bool> isCong;

		int countMoney = 0;
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (this->arrayPlayer[i]->isPlaying()) {
				if (i != chairWin) {
					int numLose = this->arrayPlayer[i]->PlayerCard()->getThoi();
					numLose = numLose + 3;
					if (arrayPlayer[i]->PlayerCard()->getListIdCard().size() == NUM_CARD) {
						numLose = numLose * 2;
						isCong.push_back(true);
						//ranks.push_back(6);
						ranks.push_back(RANK_CONG);
					}
					else {
						isCong.push_back(false);
						//ranks.push_back(4);
						ranks.push_back(RANK_BET);
					}
					countMoney = countMoney + numLose;
					moneys.push_back(-numLose * 1000);

				}
				else {
					ranks.push_back(RANK_TOI_TRANG);
					//ranks.push_back(5);
					moneys.push_back(0);
					isCong.push_back(false);
				}
			}
			else {
				ranks.push_back(-1);
				moneys.push_back(0);
				isCong.push_back(false);
			}

		}
		//moneys.insert(moneys.begin(), chairWin, countMoney * 1000);
		moneys[chairWin] = countMoney * 1000;
		notifyGameResult(moneys, ranks, isCong);
		lastWinId = chairWin;
	}
	else {
		int time = TIME_NORMAL;
		if (isPosture)
			time = TIME_POSTURE;
		changeTurn(lastWinId, time, true);
	}
}


void GameLogic::onReward(int num)
{
	BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
	if (num > 0) {
		gui->autoState = REWARD_SUCCESS_STATE;
		timeAuto = 0.5;
	}
	else {
		gui->autoState = REWARD_FAIL_STATE;
		timeAuto = 0.5;
	}
	AXLOGD("Num %i ", num);
	/*string reason = "";
	if (num > 0) {
		reason = LocalizedString::to("RECEIVE_NUM");
		reason = StringUtility::replaceAll(reason, "@gold",  "30.000");
		sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {
			arrayPlayer[0]->Gold(30000);
			BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
			gui->updateUserMoney(0);
		});
		JNIUtils::sendEvent("get_reward_success", "1");
	}
	else {
		reason = LocalizedString::to("NOT_FINISH_REWARD");
		sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {

		});
		JNIUtils::sendEvent("get_reward_fail", "1");
	}*/
}

bool GameLogic::checkGetSupport()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	string s1 = to_string(ltm->tm_year) + " " + to_string(ltm->tm_yday);
	string day = string(UserDefault::getInstance()->getStringForKey("daySupport", ""));

	if (s1.compare(day) != 0) {
		AXLOGD("CHUA NHAN SUPPORT");
		string message = LocalizedString::to("SUPPORT_GOLD");
		message = StringUtility::replaceAll(message, "@gold", "15.000");
		sceneMgr->showOkDialogWithAction(message, [this](int btnId) {
			GameLogic::getInstance()->arrayPlayer[0]->Gold(15000);
			BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
			gui->updateUserMoney(0);
		});
		JNIUtils::sendEvent("get_support", "1");
		UserDefault::getInstance()->setStringForKey("daySupport", s1);
		UserDefault::getInstance()->flush();
		return true;
	}
	return false;
}

void GameLogic::startPosture(int level)
{
	countLose = 0;
	isPosture = true;
	canShowCard = false;
	currentPosture = level;
}

void GameLogic::endPosture()
{
	isPosture = false;
	canShowCard = false;
}

void GameLogic::update(float delta)
{

}
