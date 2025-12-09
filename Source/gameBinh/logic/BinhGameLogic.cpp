#include "BinhGameLogic.h"
#include "core/gui/SceneMgr.h"
#include "gameBinh/ui/BinhBoardScene.h"
#include "../BinhInGameMgr.h"
#include "../ui/BinhTruyenThong.h"
#include <chrono>
#include "core/utils/TienlenGameSound.h"
#include "gamePlay/MaubinhGameRule.h"
#include "Game/Utility/JNIUtils.h"
using namespace std::chrono;
BinhGameLogic::BinhGameLogic()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i] = new BinhPlayerInfo(i);
	}
	myChair = 0;
	jackpotNumber = 1000;
    timeAuto = -1;
	countGame = 0;
}

BinhGameLogic::~BinhGameLogic()
{

}
BinhGameLogic* BinhGameLogic::_instance;
BinhGameLogic* BinhGameLogic::getInstance()
{
	if (!_instance)
	{
		_instance = new BinhGameLogic();
	}
	return _instance;
}


void BinhGameLogic::joinRoomSuccess(BinhMsgJoinRoomSuccess msg)
{
	newGame();
	isKick = false;
	myChair = msg.uChair;
	roomBet = msg.roomBet;
	roomOwner = msg.roomOwner;
	roomIndex = msg.roomIndex;
	roomId = msg.roomId;
	roomType = msg.roomType;
	cuoclon = msg.cuoclon;
	goldBet = 1000;
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i] = msg.playerList[i];
	}
	if (msg.playerList[msg.uChair]->Status() == BinhPlayerStatus::BINH_PLAYER_VIEWING) {
		binhInGameMgr->sendViewInfo();
		gameState = BinhGameState::BINH_GAME_PLAYING;
		isViewing = true;
	}
	else {
		gameState = BinhGameState::BINH_GAME_WAITING;
		isViewing = false;
	}
	BinhBoardScene *gui = (BinhBoardScene *) SceneMgr::getInstance()->openScene(BinhBoardScene::className);
	//gui->joinRoomSuccess();
	AXLOGD("MY CHAIR %i %i", myChair, roomOwner);
}

void BinhGameLogic::setViewInfo(char gameState, int gameTime, vector<bool> isPlayings, vector<bool> playerStates)
{
	
}

void BinhGameLogic::autoStart(int time, bool isAutoStart)
{
	AXLOGD("Type auto start %s ", isAutoStart ? " true " : " false ");
	if (isAutoStart) {
		// Dem Countdown
	}
	else {
		// Dung Countdown
	}
	if (gameState == BinhGameState::BINH_GAME_WAITING) {
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->autoStart(time, isAutoStart);
	}
}

void BinhGameLogic::newUserJoinRoom(BinhPlayerInfo* info)
{
	arrayPlayer[info->Chair()] = info;
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->newUserJoinRoom(getChair(info->Chair()), info);
}

void BinhGameLogic::userLeaveRoom(char chair)
{
	if (chair == -1)
		return;
	if (chair == myChair)
		return;
	arrayPlayer[chair]->Status(BinhPlayerStatus::BINH_PLAYER_NONE);
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->userLeave(getChair(chair));
}

void BinhGameLogic::updateRoomOwner(char chair)
{
	roomOwner = chair;
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->updateRoomOwner();
}

void BinhGameLogic::notifyStart(vector<char> cardIds, int gameCount, int time)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->newGame();
	}
	this->gameCount = gameCount;
	this->gameTime = time;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	targetTime = time * 1000 + ms.count();
	// dao nguoc lai mang card de hien thi cho dung duoi client
	//std::reverse(cardIds.begin(), cardIds.end());
	arrayPlayer[myChair]->setArrayCard(cardIds);
	gameState = BinhGameState::BINH_GAME_DEAL_CARD;
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->notifyStart();
	countGame++;
}

void BinhGameLogic::ready(char chair)
{
	arrayPlayer[chair]->IsArranging(false);
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->ready(getChair(chair));
	if (chair == myChair) {
		if (gameMgr->useGuiAt) {
			BinhTinhAt* guiBinh = dynamic_cast<BinhTinhAt*> (sceneMgr->getGUI(BinhTinhAt::TAG));
			if (guiBinh != nullptr)
				guiBinh->removeFromParent();
		}
		else {
			BinhTruyenThong* guiBinh = dynamic_cast<BinhTruyenThong*> (sceneMgr->getGUI(BinhTruyenThong::TAG));
			if (guiBinh != nullptr)
				guiBinh->removeFromParent();
		}
	}
}

void BinhGameLogic::unReady(char chair)
{
	arrayPlayer[chair]->IsArranging(true);
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->unReady(getChair(chair));
}

void BinhGameLogic::endCard(char chair, vector<char> arrayId)
{
	// dao nguoc lai mang card de hien thi cho dung duoi client
	//std::reverse(arrayId.begin(), arrayId.end());
	arrayPlayer[chair]->setEndCard(arrayId);
	arrayPlayer[chair]->checkBinhLung();

	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->endCard(getChair(chair));

	if (chair == myChair) {
		if (isTinhAt()) {
			BinhTinhAt* guiBinh = dynamic_cast<BinhTinhAt*> (sceneMgr->getGUI(BinhTinhAt::TAG));
			if (guiBinh != nullptr)
				guiBinh->removeFromParent();
		}
	}
	gameState = BinhGameState::BINH_GAME_COMPARE;
}

void BinhGameLogic::chiIndex(char chi)
{
	currentChi = chi;
	if (gameState != BinhGameState::BINH_GAME_COMPARE)
		return;
	AXLOGD("CHI INDEX %i ", chi);
	if (chi < CHI_1)
		return;
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->chiIndex(chi);
	if (chi == CHI_1) {
		BinhTruyenThong* guiBinh = dynamic_cast<BinhTruyenThong*> (sceneMgr->getGUI(BinhTruyenThong::TAG));
		if (guiBinh != nullptr)
			guiBinh->removeFromParent();
	}
	
}

void BinhGameLogic::compareChi(char chi, vector<double> arrayMoney, vector<int> arrayResult)
{
	if (gameState != BinhGameState::BINH_GAME_COMPARE)
		return;
	// mang result la ket qua so chi cua minh so tung vi tri doi thu: 1 thang, -1 thua
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	arrayResult[myChair] = 0;
	if (!isViewing) {
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (i != myChair) {
				arrayResult[myChair] = arrayResult[myChair] + getNumEatChi(chi, arrayPlayer[myChair]->PlayerCard()) * arrayResult[i];
				if (arrayResult[i] < 0) {
					arrayLose[i] = arrayLose[i] + 1;
				}
				else if (arrayResult[i] > 0) {
					arrayWin[i] = arrayWin[i] + 1;
				}
			}
		}
	}
	gui->compareChi(chi, arrayMoney, arrayResult);
}

void BinhGameLogic::summary(vector<double> arrayMoney)
{
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->summary(arrayMoney);
	binhInGameMgr->sendAuthenConnect();
}

void BinhGameLogic::sapBai(vector<double> arrayMoney, vector <char> arraySapBai)
{
	for (int i = 0; i < arraySapBai.size(); i++) {
		AXLOGD("SAP BAI ******* %i %f", arraySapBai[i], arrayMoney[i]);
	}
	/**
	 *  xu li Sap bai rat phuc tap, chia lam 2 truong hop
	 * TH1: minh nam trong case Sap Bai: truong Sap bai cua minh != -1, nguoi nao bat sap minh thi = 0, bi minh bat Sap thi la 1
	 * TH2: minh khong nam trong Sap Bai, chi quan sat: nguoi bi bat Sap la 0, nguoi chi di bat sap nguoi khac la 1
	 */
	if (arraySapBai[myChair] == -1) {
		arrayPlayer[myChair]->SapType(SapBaiType::NOT_SAP);
	}
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (i != myChair) {
			if (arraySapBai[myChair] == -1) {
				// minh chi quan sat nguoi khac bat sap
				if (arraySapBai[i] == 0) { // bi bat sap
					arrayPlayer[i]->SapType(SapBaiType::BI_SAP);
				}
				else if (arraySapBai[i] == 1) { // chi di bat sap nguoi khac
					arrayPlayer[i]->SapType(SapBaiType::BAT_SAP);
				}
				else {
					arrayPlayer[i]->SapType(SapBaiType::NOT_SAP);
				}
			}
			else {
				// minh tham gia vao qua trinh bat sap
				if (arraySapBai[i] == 0) { // bat sap minh
					arrayPlayer[i]->SapType(SapBaiType::BAT_SAP);
					arrayPlayer[myChair]->SapType(SapBaiType::BI_SAP);
				}
				else if (arraySapBai[i] == 1) { // minh bat sap ho
					arrayPlayer[i]->SapType(SapBaiType::BI_SAP);
					if (arrayPlayer[myChair]->SapType() != SapBaiType::BI_SAP) {
						// neu minh da bi bat Sap thi chi the hien la minh bi bat Sap, neu khong thi moi la bat Sap nguoi khac
						arrayPlayer[myChair]->SapType(SapBaiType::BAT_SAP);
					}
				}
				else {
					arrayPlayer[i]->SapType(SapBaiType::NOT_SAP);
				}
			}
		}
	}
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->sapBai(arrayMoney);
}

void BinhGameLogic::soBai(bool isMauBinh, vector<double> arrayMoney)
{
	if (gameState != BinhGameState::BINH_GAME_COMPARE)
		return;
	arrayMoneyMauBinh = arrayMoney;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->isPlaying()) {
			arrayPlayer[i]->checkMauBinh(isMauBinh);
		}
	}
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->soBai(isMauBinh, arrayMoney);
}

void BinhGameLogic::sapLang(char chair, vector<double> arrayMoney)
{
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->soBai(getChair(chair), arrayMoney);
}

void BinhGameLogic::binhAt(vector<double> arrayMoney)
{
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->binhAt(arrayMoney);
}

void BinhGameLogic::endGame()
{
	newGame();
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->newGame();
}

void BinhGameLogic::jackpot(double money, int userId)
{
	if (userId == arrayPlayer[myChair]->ID()) {
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->jackpot(money);
	}
}

void BinhGameLogic::updateJackpot(double jackpotNumber)
{
	AXLOGD("UPDATE JACKPOT %d", jackpotNumber);
	this->jackpotNumber = jackpotNumber;
	if (isInBoard()) {
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->updateJackpot();
	}
}

void BinhGameLogic::regQuit(char chair, bool status)
{
	AXLOGD("REG QUIT %s ", status ? "true" : "false");
	if (!isInBoard()) {
		return;
	}
	if (chair == myChair) {
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->regQuit(status);
	}
}

void BinhGameLogic::kickFromRoom(char chair, char reason)
{
	AXLOGD("KICK ROOM %i %i ", chair, reason);
	arrayPlayer[chair]->Status(BinhPlayerStatus::BINH_PLAYER_NONE);
	if (isInBoard()) {
		if (chair == myChair)
			isKick = true;
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->kickFromRoom(getChair(chair), reason);
	}
}

void BinhGameLogic::quitRoomSuccess()
{
	AXLOGD("QUIT ROOM %s ", isKick ? "TRUE " : " false");
	if (isKick)
		return;
}

/**
 * Convert chair Tu Server thanh duoi Client
 */
char BinhGameLogic::getChair(char chair)
{
	return (chair + 4 - this->myChair) % 4;
}

char BinhGameLogic::getChairInServer(char chair)
{
	return (chair + this->myChair) % 4;
}

BinhPlayerInfo* BinhGameLogic::getInfo(char chairInClient) 
{
	char chair = getChairInServer(chairInClient);
	return arrayPlayer[chair];
}

void BinhGameLogic::newGame()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->newGame();
		arrayMoneySummary[i] = 0;
		arrayWin[i] = 0;
		arrayLose[i] = 0;
	}
	gameState = BinhGameState::BINH_GAME_WAITING;
}

char BinhGameLogic::convertRank(char rank)
{

	return rank;
}

string BinhGameLogic::getResourceRank(char rank)
{
	string resource;
	return resource;
}

int BinhGameLogic::getNumPlaying()
{
	int count = 0;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->isPlaying()) {
			count++;
		}
	}
	return count;
}

bool BinhGameLogic::isShowBtnStart()
{
	if (myChair == roomOwner) {
		return true;
	}
	return false;
}

bool BinhGameLogic::isInBoard()
{
	BinhBoardScene* board = dynamic_cast<BinhBoardScene*>(sceneMgr->getMainLayer());
	if (board != nullptr) {
		return true;
	}
	return false;
}

int BinhGameLogic::getChairFromId(int id)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->ID() == id) {
			return i;
		}
	}
	return -1;
}

UserInfo* BinhGameLogic::getUserInfo(char chairClient)
{
	return arrayPlayer[getChairInServer(chairClient)]->getUserInfo();
}

char BinhGameLogic::getPlayerCardKind(vector <int> id, bool isTinhAt)
{
	MaubinhPlayerCard playerCard;
	playerCard.setArrayCard(id);
	playerCard.SapXepTruocSoBai();
	return playerCard.GetPlayerCardsKind(isTinhAt);
}

int BinhGameLogic::getZOrderCard(int index)
{
	int row = index / NUM_CARD_BIG_CHI;
	int zOrder = (2 - row) * NUM_CARD_BIG_CHI + index % NUM_CARD_BIG_CHI;
	return zOrder;
}

int BinhGameLogic::getCardIndex(int index, int chi)
{
	return index + chi * NUM_CARD_BIG_CHI;
}

void BinhGameLogic::setMyCard(vector<int> arrayId, vector<Vec2> arrayPos, vector<float> arraySize)
{
	arrayPlayer[myChair]->setArrayCardInClient(arrayId);
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	gui->updateMyCard(arrayId, arrayPos, arraySize);
}

std::string BinhGameLogic::getResourceResult(bool isWin)
{
    string res = BinhGameLogic::getInstance()->getRes();
	if (isWin) {
        return "table/" + res + "win.png ";
	}
	else {
        return "table/" + res + "lose.png ";
	}
}

int BinhGameLogic::getNumEatChi(char chi, MaubinhPlayerCard* playerCard)
{
	int groupKind;
	if (chi == CHI_1) {
		groupKind = playerCard->ChiCuoi->GetGroupKind();
	}
	else if (chi == CHI_2){
		groupKind = playerCard->ChiGiua->GetGroupKind();
	}else
	{
		groupKind = playerCard->ChiDau->GetGroupKind();
	}

	switch (groupKind) {
	case EG_THUNGPHASANHTHUONG:
	{
		if (chi == CHI_1)
			return 10;
		else
			return 20;
		break;
	}
	case EG_THUNGPHASANH:
	{
		if (chi == CHI_1)
			return 10;
		else
			return 20;
		break;
	}
	case EG_TUQUI:
	{
		// trong Binh tinh at, neu tu quy at thi duoc tinh an chi kieu khac
		if (chi == CHI_1) {
			if (playerCard->ChiCuoi->GetMaxNumber() == 14 && roomType == GameType::TINH_AT)
				return 20;
			else
				return 8;
		}
		else
		{
			if (playerCard->ChiCuoi->GetMaxNumber() == 14 && roomType == GameType::TINH_AT)
				return 40;
			else
				return 16;
		}
		break;
	}
	case EG_CULU:
		if (chi == CHI_1)
			return 1;
		else
			return 4;
		break;
	case EG_THUNG:
	case EG_SANH:
	case EG_THU:
	case EG_DOI:
	case EG_MAUTHAU:
		return 1;
		break;
	break;
	case EG_SAMCO:
	{
		if (chi == CHI_3)
			return 6;
		else
			return 1;
		break;
	}
	default:
		return 0;
		break;
	}
}

bool BinhGameLogic::isTinhAt()
{
	return roomType == GameType::TINH_AT;
}

bool BinhGameLogic::isMauBinh(int cardKind)
{
	if (cardKind == EM_LUCPHEBON || cardKind == EM_SANHRONG || cardKind == EM_3SANH
		|| cardKind == EM_3THUNG || cardKind == EM_MUOI_BA || cardKind == EM_MUOI_HAI) {
		return true;
	}
	return false;
}

std::string BinhGameLogic::getResourceEffectChi(char chi, double Money, MaubinhPlayerCard* playerCard, bool &isEffectParticle, bool isSound)
{
	isSound = false;
	int groupKind;
	string resource = "";
	if (chi == CHI_1) {
		groupKind = playerCard->ChiCuoi->GetGroupKind();
	}
	else if (chi == CHI_2) {
		groupKind = playerCard->ChiGiua->GetGroupKind();
	}
	else {
		groupKind = playerCard->ChiDau->GetGroupKind();
	}

	switch (groupKind) {
	case EG_THUNGPHASANHTHUONG:
	{
		isEffectParticle = true;
		if (chi == CHI_1)
			resource = "table/thungPhaSanh.png";
		else
			resource = "table/thungPhaSanhChi2.png";

		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thungphasanh();
			}
			else {
				TienlenGameSound::playSoundxepbai_thungphasanh();
			}
		}
	}

	break;
	case EG_THUNGPHASANH:
	{
		isEffectParticle = true;
		if (chi == CHI_1)
			resource = "table/thungPhaSanh.png";
		else
			resource = "table/thungPhaSanhChi2.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thungphasanh();
			}
			else {
				TienlenGameSound::playSoundxepbai_thungphasanh();
			}
		}
	}
	break;
	case EG_TUQUI:
	{
		isEffectParticle = true;
		if (chi == CHI_1)
			resource = "table/tuQuy.png";
		else
			resource = "table/tuQuyChi2.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_tuquy();
			}
			else
			{
				TienlenGameSound::playSoundxepbai_tuquy();
			}
		}
	}

	break;
	case EG_CULU:
	{
		if (chi == CHI_2)
			isEffectParticle = true;
		if (chi == CHI_1)
			resource = "table/cuLu.png";
		else
			resource = "table/cuLuChi2.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_culu();
			}
			else {
				TienlenGameSound::playSoundxepbai_culu();
			}
		}
	}

	break;
	case EG_THUNG:
		resource = "table/thung.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thung();
			}
			else {
				TienlenGameSound::playSoundxepbai_thung();
			}
		}
		break;
	case EG_SANH:
		resource = "table/sanh.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_sanh();
			}
			else {
				TienlenGameSound::playSoundxepbai_sanh();
			}
		}
		break;
	case EG_SAMCO:
	{
		if (chi == CHI_3)
			isEffectParticle = true;
		if (chi == CHI_3)
			resource = "table/xamChiCuoi.png";
		else
			resource = "table/xamChi.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_samchicuoi();
			}
			else {
				TienlenGameSound::playSoundxepbai_samchi();
			}
		}
	}

	break;
	case EG_THU:
		resource = "table/thu.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thu();
			}
			else {
				TienlenGameSound::playSoundxepbai_thu();
			}
		}
		break;
	case EG_DOI:
		resource = "table/doi.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_doi();
			}
			else {
				TienlenGameSound::playSoundxepbai_doi();
			}
		}
		break;
	case EG_MAUTHAU:
		resource = "table/mauThau.png";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_mauthau();
			}
			else {
				TienlenGameSound::playSoundxepbai_mauthau();
			}
		}
		break;

	default:

		break;
	}
	return resource;
}


std::string BinhGameLogic::getResourceEffectChiCompare(char chi, double Money, MaubinhPlayerCard* playerCard, bool &isEffectParticle, bool isSound)
{
	
	int groupKind;
    string res      = BinhGameLogic::getInstance()->getRes();
	string resource = "Board/table/" + res + "effectChi/";
	if (chi == CHI_1) {
		groupKind = playerCard->ChiCuoi->GetGroupKind();
	}
	else if (chi == CHI_2) {
		groupKind = playerCard->ChiGiua->GetGroupKind();
	}
	else {
		groupKind = playerCard->ChiDau->GetGroupKind();
	}

	switch (groupKind) {
	case EG_THUNGPHASANHTHUONG:
	{
		isEffectParticle = true;
		if (chi == CHI_1)
			resource = resource + "thungphasanh";
		else
			resource = resource + "thungphasanhchi2";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thungphasanh();
			}
			else {
				TienlenGameSound::playSoundxepbai_thungphasanh();
			}
		}
	}
	break;
	case EG_THUNGPHASANH:
	{
		isEffectParticle = true;
		if (chi == CHI_1)
			resource = resource + "thungphasanh";
		else
			resource = resource + "thungphasanhchi2";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thungphasanh();
			}
			else {
				TienlenGameSound::playSoundxepbai_thungphasanh();
			}
		}
	}
	break;
	case EG_TUQUI:
	{
		isEffectParticle = true;
		if (chi == CHI_1)
			resource = resource + "tuquy";
		else
			resource = resource + "tuquychi2";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_tuquy();
			}
			else
			{
				TienlenGameSound::playSoundxepbai_tuquy();
			}
		}
	}

	break;
	case EG_CULU:
	{
		if (chi == CHI_2)
			isEffectParticle = true;
		if (chi == CHI_1)
			resource = resource + "culu";
		else
			resource = resource + "culuchi2";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_culu();
			}
			else {
				TienlenGameSound::playSoundxepbai_culu();
			}
		}
	}

	break;
	case EG_THUNG:
		resource = resource + "thung";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thung();
			}
			else {
				TienlenGameSound::playSoundxepbai_thung();
			}
		}
		break;
	case EG_SANH:
		resource = resource + "sanh";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_sanh();
			}
			else {
				TienlenGameSound::playSoundxepbai_sanh();
			}
		}
		break;
	case EG_SAMCO:
	{
		if (chi == CHI_3)
			isEffectParticle = true;
		if (chi == CHI_3)
			resource = resource + "xamchicuoi";
		else
			resource = resource + "xam";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_samchicuoi();
			}
			else {
				TienlenGameSound::playSoundxepbai_samchi();
			}
		}
	}

	break;
	case EG_THU:
		resource = resource + "thu";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_thu();
			}
			else {
				TienlenGameSound::playSoundxepbai_thu();
			}
		}
		break;
	case EG_DOI:
		resource = resource + "doi";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_doi();
			}
			else {
				TienlenGameSound::playSoundxepbai_doi();
			}
		}
		break;
	case EG_MAUTHAU:
		resource = resource + "mauthau";
		if (isSound) {
			if (Money > 0) {
				TienlenGameSound::playSoundthang_mauthau();
			}
			else {
				TienlenGameSound::playSoundxepbai_mauthau();
			}
		}
		break;

	default:

		break;
	}
	if (Money > 0)
		resource = resource + "_thang.png";
	else
		resource = resource + "_thua.png";
	return resource;
}

int BinhGameLogic::getNumCompareBai()
{
	int count = 0;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->IsCompareBai())
			count++;
	}
	return count;
}

int BinhGameLogic::getNumMauBinh()
{
	int count = 0;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->IsMauBinh())
			count++;
	}
	return count;
}


int BinhGameLogic::getEffectMaubinh(char chair)
{
	if (chair < 0) {
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (arrayPlayer[i]->IsMauBinh()) {
				chair = i;
			}
		}
	}
	else {
		chair = getChairInServer(chair);
	}
	MaubinhPlayerCard* playerCard = arrayPlayer[chair]->PlayerCard();
	int cardKind;
	if (isTinhAt())
		cardKind = playerCard->GetPlayerCardsKindBao(false, true);
	else
		cardKind = playerCard->GetPlayerCardsKind();
	string resource = "";
	switch (cardKind)
	{
	case EM_LUCPHEBON:
		if (chair != myChair)
			TienlenGameSound::playSoundbaobinh_lucphebon();
		else
			TienlenGameSound::playSoundmaubinh_lucphebon();
		break;
	case EM_SANHRONG:
		if (chair != myChair)
			TienlenGameSound::playSoundbaobinh_sanhrong();
		else
			TienlenGameSound::playSoundmaubinh_sanhrong();
		break;
	case EM_3SANH:
		if (chair != myChair)
			TienlenGameSound::playSoundbaobinh_3caisanh();
		else
			TienlenGameSound::playSoundmaubinh_3caisanh();
		break;
	case EM_3THUNG:
		if (chair != myChair)
			TienlenGameSound::playSoundbaobinh_3caithung();
		else
			TienlenGameSound::playSoundmaubinh_3caithung();
		break;
	case EM_MUOI_BA:
		if (chair != myChair)
			TienlenGameSound::playSoundbaobinh_13caydongmau();
		break;
	case EM_MUOI_HAI:
		//animation = "2";
		if (chair != myChair)
			TienlenGameSound::playSoundbaobinh_12caydongmau();
		break;
	default:
		break;
	}
	return cardKind;
}

//
//std::string BinhGameLogic::getEffectMaubinh(string &animation, char chair)
//{
//	if (chair < 0) {
//		for (int i = 0; i < NUM_PLAYER; i++) {
//			if (arrayPlayer[i]->IsMauBinh()) {
//				chair = i;
//			}
//		}
//	}
//	else {
//		chair = getChairInServer(chair);
//	}
//	MaubinhPlayerCard* playerCard = arrayPlayer[chair]->PlayerCard();
//	int cardKind;
//	if (isTinhAt())
//		cardKind = playerCard->GetPlayerCardsKindBao(false, true);
//	else
//		cardKind = playerCard->GetPlayerCardsKind();
//	string resource = "";
//	animation = "1";
//	switch (cardKind)
//	{
//	case EM_LUCPHEBON:
//		resource = "Text_bobai";
//		animation = "Six_Pair_Play";
//		if (chair != myChair)
//			TienlenGameSound::playSoundbaobinh_lucphebon();
//		else
//			TienlenGameSound::playSoundmaubinh_lucphebon();
//		break;
//	case EM_SANHRONG:
//		resource = "Text_bobai";
//		animation = "Dragon_Play";
//		if (chair != myChair)
//			TienlenGameSound::playSoundbaobinh_sanhrong();
//		else
//			TienlenGameSound::playSoundmaubinh_sanhrong();
//		break;
//	case EM_3SANH:
//		resource = "Text_bobai";
//		animation = "Three_Straight_Play";
//		if (chair != myChair)
//			TienlenGameSound::playSoundbaobinh_3caisanh();
//		else
//			TienlenGameSound::playSoundmaubinh_3caisanh();
//		break;
//	case EM_3THUNG:
//		resource = "Text_bobai";
//		animation = "Three_Flush_Play";
//		if (chair != myChair)
//			TienlenGameSound::playSoundbaobinh_3caithung();
//		else
//			TienlenGameSound::playSoundmaubinh_3caithung();
//		break;
//	case EM_MUOI_BA:
//		resource = "Text_bobai";
//		animation = "13Kartu_Samawarna_Play";
//		if (chair != myChair)
//			TienlenGameSound::playSoundbaobinh_13caydongmau();
//		break;
//	case EM_MUOI_HAI:
//		resource = "Text_bobai";
//		animation = "12Kartu_Samawarna_Play";
//		//animation = "2";
//		if (chair != myChair)
//			TienlenGameSound::playSoundbaobinh_12caydongmau();
//		break;
//	default:
//		break;
//	}
//	return resource;
//}

void BinhGameLogic::sortArrayId(int* arrayArrange, int count, SortCard stateSort)
{
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (stateSort == SortCard::NUMBER) {
				if (arrayArrange[i] > arrayArrange[j]) {
					int temp = arrayArrange[j];
					arrayArrange[j] = arrayArrange[i];
					arrayArrange[i] = temp;
				}
			}
			else {
				int remaneti = arrayArrange[i] % 4;
				int remanetj = arrayArrange[j] % 4;

				remaneti = convert(remaneti);
				remanetj = convert(remanetj);

				if (remaneti > remanetj || (remaneti == remanetj && arrayArrange[i] > arrayArrange[j])) {
					int temp = arrayArrange[j];
					arrayArrange[j] = arrayArrange[i];
					arrayArrange[i] = temp;
				}
			}
		}
	}
}

int BinhGameLogic::convert(int id)
{
	switch (id)
	{
	case 0:
		return 0;
	case 1:
		return 2;
	case 2:
		return 1;
	case 3:
		return 3;
	default:
		break;
	}
}

std::vector <int> BinhGameLogic::getArrayCardBao()
{
	MaubinhPlayerCard* playerCard = arrayPlayer[myChair]->PlayerCard();
	int *arrayCard = playerCard->ArrangePlayerCardsBao();
	vector <int> arrayId;
	for (int i = 0; i < NUM_CARD; i++) {
		arrayId.push_back(arrayCard[i]);
	}
	return arrayId;
}

void BinhGameLogic::showDarkCard(MaubinhPlayerCard playerCard, int cardKind, bool mauBinh, BinhCardButton* arrayCard [])
{
	int i, j;
	MaubinhGroupCardLogic* gc = nullptr;
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setDark(true);
	}
	if (cardKind == EM_BINHLUNG) {
		for (int i = 0; i < NUM_CARD; i++) {
			arrayCard[i]->setDark(false);
		}
		return;
	}
	if (mauBinh) {
		return;
	}

	if (!mauBinh) {
		if (playerCard.ChiDau->GetGroupKind() != EG_SAMCO) {
			switch (playerCard.ChiDau->GetGroupKind()) {
			case EG_MAUTHAU:
				gc = playerCard.ChiDau->getMaxCard();
				break;
			case EG_THU:
				gc = playerCard.ChiDau->get2DoiKhacNhau();
				break;
			case EG_DOI:
				gc = playerCard.ChiDau->getPair();
				break;
			}
			if (gc != nullptr) {
				for (i = 0; i < NUM_CARD_SMALL_CHI; i++) {
					int stt = NUM_CARD_BIG_CHI * 2 + i;
					for (j = 0; j < gc->Cards.size(); j++) {
						if (gc->Cards[j]->ID == arrayCard[stt]->id) {
							break;
						}
					}
					if (j == gc->Cards.size()) {
						arrayCard[stt]->setDark(false);
					}
				}
			}
		}
		showDark2BigChi(playerCard.ChiGiua, CHI_GIUA, arrayCard);
		showDark2BigChi(playerCard.ChiCuoi, CHI_CUOI, arrayCard);
	}
}

void BinhGameLogic::showDark2BigChi(MaubinhGroupCardLogic* gc1, int chi, BinhCardButton* arrayCard[])
{
	int i, j;
	MaubinhGroupCardLogic* gc = nullptr;
	if (gc1->GetGroupKind() != EG_THUNGPHASANH && gc1->GetGroupKind() != EG_THUNG && gc1->GetGroupKind() != EG_SANH && gc1->GetGroupKind() != EG_CULU) {
		switch (gc1->GetGroupKind()) {
		case EG_MAUTHAU:
			gc = gc1->getMaxCard();
			break;
		case EG_THU:
			gc = gc1->get2DoiKhacNhau();
			break;
		case EG_DOI:
			gc = gc1->getPair();
			break;
		case EG_SAMCO:
			gc = gc1->getXamChi();
			break;
		case EG_TUQUI:
			gc = gc1->getFour();
			break;
		}
		if (gc != nullptr) {
			for (i = 0; i < NUM_CARD_BIG_CHI; i++) {
				int stt = NUM_CARD_BIG_CHI * (NUM_CHI - chi - 1) + i;
				for (j = 0; j < gc->Cards.size(); j++) {
					if (gc->Cards[j]->ID == arrayCard[stt]->id) {
						break;
					}
				}
				if (j == gc->Cards.size()) {

					arrayCard[stt]->setDark(false);
				}

			}
		}
	}
}

float BinhGameLogic::getPercentTime()
{
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	float timeRemain = targetTime - ms.count();
	return timeRemain / gameTime / 1000 * 100;
}

double BinhGameLogic::getRemainTime()
{
	std::time_t result = std::time(nullptr);
	double timeR = (targetTime - result * 1000) / 1000;
	AXLOGD("Remain time %f", timeR);
	return timeR;
}

// kiem tra xem toan bo nguoi choi da So Bai hay chua, neu du roi thi co the lat het bai cua ho ra
bool BinhGameLogic::isShowAll()
{
	AXLOGD("COMPARE BAI %i %i", getNumCompareBai(), getNumPlaying());
	if (arrayPlayer[0]->IsCompareBai())
		return true;
	if (getNumCompareBai() >= getNumPlaying() - 1) {
		return true;
	}
	return false;
}

BinhPlayerInfo * BinhGameLogic::getPlayerByUId(long long uId)
{
	for (auto playerInfo : arrayPlayer) {
		if (playerInfo && playerInfo->ID() == uId) return playerInfo;
	}
	return nullptr;
}

/**
 * Xem Bo bai cua nguoi choi co phai la mau binh khi xep xong hay khong
 */
int BinhGameLogic::getCardKindReady()
{
	BinhPlayerInfo* info = arrayPlayer[myChair];
	if (isTinhAt()) {
		if (arrayPlayer[myChair]->WaitBaoBinh()) {
			return info->PlayerCard()->GetPlayerCardsKindBao(false, true);
		}
		else {
			if (info->PlayerCard()->GetPlayerCardsKind() == EM_BINHLUNG)
				return EM_BINHLUNG;
			else
				return EM_NORMAL;
		}
	}
	else {
		return info->PlayerCard()->GetPlayerCardsKind();
	}
}

std::string BinhGameLogic::getResourceBinh(int typeMaubinh)
{
    if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
    {
        switch (typeMaubinh)
        {
        case EM_LUCPHEBON:
            return "table/textEnglish/sixPair.png";
            break;
        case EM_SANHRONG:
            return "table/textEnglish/dragon.png";
            break;
        case EM_3SANH:
            return "table/textEnglish/threeStraight.png";
            break;
        case EM_3THUNG:
            return "table/textEnglish/threeFlush.png";
            break;
        case EM_MUOI_HAI:
            return "table/12cay.png";
            break;
        case EM_MUOI_BA:
            return "table/13cay.png";
            break;
        default:
            return "";
            break;
        }
    }
    else
    {
        switch (typeMaubinh)
        {
        case EM_LUCPHEBON:
            return "CommonEffect/sauDoi.png";
            break;
        case EM_SANHRONG:
            return "CommonEffect/sanhRong.png";
            break;
        case EM_3SANH:
            return "CommonEffect/baSanh.png";
            break;
        case EM_3THUNG:
            return "CommonEffect/baThung.png";
            break;
        case EM_MUOI_HAI:
            return "table/12cay.png";
            break;
        case EM_MUOI_BA:
            return "table/13cay.png";
            break;
        default:
            return "";
            break;
        }
    }
}


int BinhGameLogic::compareChiWithPlayer(int chi, int chairClient)
{
	BinhPlayerInfo* info = getInfo(chairClient);
	BinhPlayerInfo* myInfo = getInfo(myChair);
	int result;
	if (chi == CHI_1) {
		result = MaubinhGameRule::SoSanhChi(myInfo->PlayerCard()->ChiCuoi, info->PlayerCard()->ChiCuoi, false);
	}
	else if (chi == CHI_2) {
		result = MaubinhGameRule::SoSanhChi(myInfo->PlayerCard()->ChiGiua, info->PlayerCard()->ChiGiua, false);
	}
	else
		result = MaubinhGameRule::SoSanhChi(myInfo->PlayerCard()->ChiDau, info->PlayerCard()->ChiDau, false);
	int numChi;
	if (result > 0) {
		numChi = getNumEatChi(chi, myInfo->PlayerCard());
		return numChi * result;
	}
	else if (result < 0) {
		numChi = getNumEatChi(chi, info->PlayerCard());
		return numChi * result;
	}
	else {
		return 0;
	}
}

void BinhGameLogic::autoCompareChi(int chi)
{
	vector<double> arrayMoney;
	vector<int> arrayResult;
	int money = 0;
	for (int i = 1; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = arrayPlayer[i];
		if (info->IsCompareBai() == false) {
			int compare = this->compareChiWithPlayer(chi, i);
			arrayMoney.push_back(-compare * goldBet);
			arrayResult.push_back(compare);
			arrayMoneySummary[i] = arrayMoneySummary[i] + arrayMoney.at(i - 1);
			money = -arrayMoney.at(i - 1) + money;
		}
		else {
			arrayMoney.push_back(0);
			arrayResult.push_back(0);
		}
	}
	arrayMoneySummary[0] = arrayMoneySummary[0] + money;
	arrayMoney.insert(arrayMoney.begin(), money);
	arrayResult.insert(arrayResult.begin(), 0);
	compareChi(chi, arrayMoney, arrayResult);
}

int BinhGameLogic::getNumEatBinh(int groupKind)
{
	if (this->isMauBinh(groupKind)) {
		if (groupKind == EM_SANHRONG) {
			return 64;
		}
		else {
			return 32;
		}
	}
	return 0;
}

bool BinhGameLogic::autoCheckMauBinh()
{
	vector <double> arrayMoney;
	int count = 0;
	bool isBinh = false;
	int rateEat = 0;
	bool arrayBinh[NUM_PLAYER] = { false, false, false, false };

	arrayPlayer[0]->PlayerCard()->SapXepTruocSoBai();
	int groupKind = arrayPlayer[0]->PlayerCard()->GetPlayerCardsKind(false);
	rateEat = this->getNumEatBinh(groupKind);
	if (rateEat > 0) {
		isBinh = true;
	}
	
	double money = 0;
	arrayMoney.push_back(0);
	for (int i = 1; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->PlayerCard()->SapXepTruocSoBai();
		int groupKind = arrayPlayer[i]->PlayerCard()->GetPlayerCardsKind(false);
		int rate = this->getNumEatBinh(groupKind);
		double eatMoney = (rateEat - rate) * goldBet;
		money = money + eatMoney;
		arrayMoney.push_back(-eatMoney);
		arrayMoneySummary[i] = arrayMoneySummary[i] - eatMoney;
		if (rate > 0) {
			isBinh = true;
		}
	}
	arrayMoney.at(0) = money;
	arrayMoneySummary[0] = arrayMoneySummary[0] + money;
	if (isBinh) {
		soBai(true, arrayMoney);
	}
	return isBinh;
}

bool BinhGameLogic::autoCheckBinhLung()
{
	vector <double> arrayMoney;
	int count = 0;
	bool arrayBinhLung[NUM_PLAYER] = { false, false, false, false };
	bool isMyBinhLung = false;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (arrayPlayer[i]->IsCompareBai() == false) {
			arrayPlayer[i]->PlayerCard()->SapXepTruocSoBai();
			int groupKind = arrayPlayer[i]->PlayerCard()->GetPlayerCardsKind(false);
			if (groupKind == EM_BINHLUNG) {
				arrayBinhLung[i] = true;
				count++;
				if (i == 0) {
					isMyBinhLung = true;
				}
			}
		}
	}
	
	double money = 0;
	arrayMoney.push_back(0);
	for (int i = 1; i < NUM_PLAYER; i++) {
		if (arrayBinhLung[i]) {
			if (isMyBinhLung) {

			}
			else {
				arrayMoney.push_back(-6 * goldBet);
				arrayMoneySummary[i] = arrayMoneySummary[i] - 6 * goldBet;
				money = money + 6 * goldBet;
			}
		}
		else {
			if (isMyBinhLung) {
				arrayMoney.push_back(6 * goldBet);
				arrayMoneySummary[i] = arrayMoneySummary[i] + 6 * goldBet;
				money = money - 6 * goldBet;
			}
			else {
				arrayMoney.push_back(0);
			}
		}
	}
	arrayMoney.at(0) = money;
	arrayMoneySummary[0] = arrayMoneySummary[0] + money;
	if (count > 0) {
		soBai(false, arrayMoney);
	}
	return count > 0;
}

bool BinhGameLogic::autoCheckBiSap()
{
	vector<double> arrayMoney;
	vector<char> arraySap;
	bool isJoin = false;
	for (int i = 1; i < NUM_PLAYER; i++) {
		if (arrayLose[i] == 3) {
			isJoin = true;
			break;
		}
	}
	if (isJoin) {
		arraySap.push_back(1);
		double money = 0;
		arrayMoney.push_back(0);
		for (int i = 1; i < NUM_PLAYER; i++) {
			if (arrayLose[i] == 3) {
				// bat sap minh
				money = money - arrayMoneySummary[i];
				arrayMoney.push_back(arrayMoneySummary[i]);
				arraySap.push_back(0);
				arrayMoneySummary[i] = arrayMoneySummary[i] * 2;
			}
			else {
				arrayMoney.push_back(0);
				arraySap.push_back(-1);
			}
		}
		arrayMoney[0] = money;
		arrayMoneySummary[0] = arrayMoneySummary[0] + money;
		sapBai(arrayMoney, arraySap);
		return true;
	}
	return false;
}


bool BinhGameLogic::autoCheckBatSap()
{
	vector<double> arrayMoney;
	vector<char> arraySap;
	bool isJoin = false;
	for (int i = 1; i < NUM_PLAYER; i++) {
		if (arrayWin[i] == 3) {
			isJoin = true;
			break;
		}
	}

	if (isJoin) {
		arrayPlayer[myChair]->SapType(SapBaiType::BAT_SAP);
		arraySap.push_back(1);
		double money = 0;
		arrayMoney.push_back(0);
		for (int i = 1; i < NUM_PLAYER; i++) {
			if (arrayWin[i] == 3) {
				// minh bat sap
				money = money - arrayMoneySummary[i];
				arrayMoney.push_back(arrayMoneySummary[i]);
				arraySap.push_back(1);
				arrayMoneySummary[i] = arrayMoneySummary[i] * 2;
			}
			else {
				arrayMoney.push_back(0);
				arraySap.push_back(-1);
			}
		}
		arrayMoney[0] = money;
		arrayMoneySummary[0] = arrayMoneySummary[0] + money;
		sapBai(arrayMoney, arraySap);
		return true;
	}
	return false;
}


void BinhGameLogic::onReward(int num)
{
	BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
	if (num > 0) {
		gui->autoState = BinhBoardScene::AutoState::REWARD_SUCCESS_STATE;
		timeAuto = 0.5;
	}
	else {
		gui->autoState = BinhBoardScene::AutoState::REWARD_FAIL_STATE;
		timeAuto = 0.5;
	}
	AXLOGD("Num %i ", num);
	/*string reason = "";
	if (num > 0) {
		reason = LocalizedString::to("RECEIVE_NUM");
		reason = StringUtility::replaceAll(reason, "@gold",  "30.000");
		sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {
			arrayPlayer[0]->Gold(30000);
			BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
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

bool BinhGameLogic::checkGetSupport()
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
			BinhGameLogic::getInstance()->arrayPlayer[0]->Gold(15000);
			BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
			gui->updateUserMoney(0);
            gameMgr->showReceiveGold();
		});
		JNIUtils::sendEvent("get_support", "1");
		UserDefault::getInstance()->setStringForKey("daySupport", s1);
		UserDefault::getInstance()->flush();
		return true;
	}
	return false;
}

string BinhGameLogic::getRes()
{
    if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
        return "textEnglish/";
    return "";
}
