#include "TalaGameLogic.h"
#include "core/gui/SceneMgr.h"
#include "gameTala/ui/TalaScene.h"
#include "../TalaInGameMgr.h"
#include "TalaGameRule.h"
#include "core/utils/TalaGameSound.h"
#include "Game/Utility/JNIUtils.h"
#include "common/UserInfoGUI.h"
#include <algorithm>
#include <random> // std::mt19937, std::random_device
TalaGameLogic::TalaGameLogic()
{
	board = nullptr;
	for (int i = 0; i < NUM_PLAYER; i++)
		players.push_back(new TalaPlayerInfo(i));
}

TalaGameLogic::~TalaGameLogic()
{
	for (int i = 0; i < NUM_PLAYER; i++)
		delete players[i];
}

TalaGameLogic* TalaGameLogic::_instance = nullptr;
TalaGameLogic* TalaGameLogic::getInstance()
{
	if (!_instance)
		_instance = new TalaGameLogic();
	return _instance;
}


void TalaGameLogic::onEnterBoard()
{
    doJoinRoom();
	if (board) {
		board->updateAction();
		//effect vip
	}
}

void TalaGameLogic::onExitBoard()
{
	board = nullptr;
}

void TalaGameLogic::onSelectCard(char cardId)
{
	if (gameState == PLAYING && players[0]->status == TalaPlayerInfo::STATUS_PLAYING) {
		if (players[0]->handOnCards.size() <= 0) return;
		if (find(players[0]->handOnCards.begin(), players[0]->handOnCards.end(), cardId) == players[0]->handOnCards.end()) return;
		auto it = find(players[0]->selectedCards.begin(), players[0]->selectedCards.end(), cardId);
		if (it == players[0]->selectedCards.end()) {
			TalaGameSound::playEffect(TalaInGameMgr::SOUND_SELECT_CARD);
			if (players[0]->state != TalaPlayerInfo::STATE_GUIBAI && players[0]->state != TalaPlayerInfo::STATE_HABAI)
				players[0]->selectedCards.clear();
			players[0]->selectedCards.push_back(cardId);
		}
		else
			players[0]->selectedCards.erase(it);
		if (board) board->updateHandOnCards(0.05);
	}
}

void TalaGameLogic::onArrangeCard()
{
	if (gameState == PLAYING && players[0]->status == TalaPlayerInfo::STATUS_PLAYING) {
		TalaGameSound::playEffect(TalaInGameMgr::SOUND_ARRANGE_CARD);
		if (players[0]->handOnCards.size() <= 0) return;
		players[0]->handOnCards = TalaGameRule::arrangeCard(players[0]->handOnCards, players[0]->eatenCards);
		players[0]->selectedCards.clear();

		if (board) board->effectArrangeCard();
	}
}

void TalaGameLogic::onThrowCard()
{
	if (gameState != PLAYING || players[0]->status != TalaPlayerInfo::STATUS_PLAYING || players[0]->state != TalaPlayerInfo::STATE_DANHBAI) return;

	auto cards = talaGameLogic->players[0]->selectedCards;
	if (cards.size() == 0) {
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_THROW_SELECT_LEAST_1"));
		return;
	}
	if (cards.size() > 1) {
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_THROW_SELECT_ONLY_1"));
		return;
	}
	auto cardId = cards[0];
	if (TalaGameRule::kiemtraVutQuan(talaGameLogic->players[0]->handOnCards, talaGameLogic->players[0]->eatenCards, cardId)) {
		setPlayerState(0, TalaPlayerInfo::STATE_NONE, -1);
		//talaInGameMgr->sendThrowCard(cardId);
		CmdReceivedThrowCard cmd;
		cmd.cardId = cardId;
		cmd.chair = 0;
		onReceiveThrowCard(cmd);
	}
	else ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_THROW_INVALID"));
}

void TalaGameLogic::onShowSuits()
{
	if (gameState != PLAYING || players[0]->status != TalaPlayerInfo::STATUS_PLAYING || players[0]->state != TalaPlayerInfo::STATE_HABAI) return;

	auto allSol = TalaGameRule::kiemtraHaBai(players[0]->handOnCards, players[0]->selectedCards, players[0]->eatenCards);
	if (allSol.size() > 0) {
		//talaInGameMgr->sendShowPhom(talaGameLogic->myChair, players[0]->selectedCards);
		setPlayerState(0, TalaPlayerInfo::STATE_NONE, -1);
		CmdReceivedShowPhom cmd;
		cmd.chair = currentTurn;
		cmd.cards = players[0]->selectedCards;
		onReceiveShowPhom(cmd);
	}
	else ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_SHOWPHOM_INVALID"));
}

void TalaGameLogic::onSendCard()
{
	if (gameState != PLAYING || players[currentTurn]->status != TalaPlayerInfo::STATUS_PLAYING || players[currentTurn]->state != TalaPlayerInfo::STATE_GUIBAI) return;

	auto &cards = talaGameLogic->players[currentTurn]->selectedCards;
	if (cards.size() == 0) {
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_SEND_SELECT_LEAST_1"));
		return;
	}
	for (int i = 0; i < players.size(); i++) {
		for (int j = 0; j < players[i]->listPhom.size(); j++) {
			auto suit = players[i]->listPhom[j];
			for (int k = 0; k < cards.size(); k++) {
				auto cardId = cards[k];
				auto it = find(cards.begin(), cards.end(), cardId);
				if (it == cards.end()) continue;
				if (TalaGameRule::kiemtraGuiBai(suit, cardId)) {
					auto suitId = TalaGameRule::getSuitId(suit);
					//talaInGameMgr->sendSendCard(players[0]->serverChair, cardId, players[i]->serverChair, suitId);
					cards.erase(it);
					CmdReceivedSendCard cmd;
					cmd.senderCardId = cardId;
					cmd.senderChair = players[currentTurn]->serverChair;
					cmd.targetChair = players[i]->serverChair;
					cmd.targetCardId = suitId;
					onReceiveSendCard(cmd);
					k--;
				}
			}
		}
	}
	idU = autoCheckU(false);
	if (idU >= 0) {
		autoNotifyU();
	}
	else {
        if (canSendCard()) {
            hintSendCard();
            autoState = AUTO_SEND_CARD;
            if (currentTurn == 0)
            {
                if (board)
                {
                    board->effectHintSendCard();
                    board->updateHandOnCards();
                }
                timeAuto = 2.0;
            }
            else
            {
                timeAuto = 0.5;
            }
        }
        else
        {
            autoChangeNewTurn();
        }
	}
}

void TalaGameLogic::onTouchLastThrowCard(char chair)
{
	if (gameState != PLAYING || players[0]->status != TalaPlayerInfo::STATUS_PLAYING || players[0]->state != TalaPlayerInfo::STATE_BOCBAI) return;

	if (chair == getLastEnemyChair() && canGetLastCard()) {
		//talaInGameMgr->sendGetCard(clientChairToServerChair(chair));
		setPlayerState(0, TalaPlayerInfo::STATE_NONE);
		autoGetCard();
	}
}

void TalaGameLogic::onTouchSuit(char chair, int suitIndex)
{
	if (gameState != PLAYING || players[0]->status != TalaPlayerInfo::STATUS_PLAYING || players[0]->state != TalaPlayerInfo::STATE_GUIBAI) return;

	if (suitIndex < 0 || suitIndex >= players[chair]->listPhom.size()) return;
	auto suit = players[chair]->listPhom[suitIndex];

	if (players[0]->selectedCards.empty()) {
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_SEND_SELECT_LEAST_1"));
		return;
	}
	bool validSuit = false;
	for (auto cardId : players[0]->handOnCards) {
		auto it = find(players[0]->selectedCards.begin(), players[0]->selectedCards.end(), cardId);
		if (it == players[0]->selectedCards.end()) continue;
		if (TalaGameRule::kiemtraGuiBai(suit, cardId)) {
			auto suitId = TalaGameRule::getSuitId(suit);
		//	talaInGameMgr->sendSendCard(players[0]->serverChair, cardId, players[chair]->serverChair, suitId);
			players[0]->selectedCards.erase(it);
			CmdReceivedSendCard cmd;
			cmd.senderCardId = cardId;
			cmd.senderChair = players[currentTurn]->serverChair;
			cmd.targetChair = players[chair]->serverChair;
			cmd.targetCardId = suitId;
			onReceiveSendCard(cmd);
			validSuit = true;
		}
	}
	if (!validSuit)
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("BOARD_SEND_SUIT_INVALID"));
	if (players[0]->selectedCards.size() == 0) {
		idU = autoCheckU(false);
		if (idU >= 0) {
			autoNotifyU();
		}
		else {
			autoChangeNewTurn();
		}
	}
}

void TalaGameLogic::onDrawCard()
{
	if (gameState != PLAYING || players[0]->status != TalaPlayerInfo::STATUS_PLAYING || players[0]->state != TalaPlayerInfo::STATE_BOCBAI) return;

	talaInGameMgr->sendGetCard(-1);
	setPlayerState(0, TalaPlayerInfo::STATE_NONE);
}

void TalaGameLogic::onStart()
{
	if (gameState != WAITING || players[0]->status != TalaPlayerInfo::STATUS_PLAYING) return;

	if (talaGameLogic->isOwner())
		talaInGameMgr->sendStartGame();
}

void TalaGameLogic::onBeginMoveCard()
{
	//unselect all cards
	players[0]->selectedCards.clear();
	if (board) board->updateHandOnCards(0, false);
}

void TalaGameLogic::onEndMoveCard(char oldIdx, char newIdx)
{
	//rearrange cards
	players[0]->selectedCards.clear();
	if (oldIdx < 0 || oldIdx >= players[0]->handOnCards.size()) return;
	if (newIdx < 0 || newIdx > players[0]->handOnCards.size()) newIdx = oldIdx;
	if (oldIdx != newIdx) {
		auto cardId = players[0]->handOnCards[oldIdx];
		players[0]->handOnCards.erase(players[0]->handOnCards.begin() + oldIdx);
		players[0]->handOnCards.insert(players[0]->handOnCards.begin() + ((oldIdx < newIdx) ? (newIdx - 1) : newIdx), cardId);
	}
	if (board) board->effectMoveCard(oldIdx, newIdx);
}

void TalaGameLogic::onSelectPlayer(char chair)
{
	if (chair == 0) {
		BaseLayer* layer = sceneMgr->openGUI(UserInfoGUI::className, UserInfoGUI::ZODER, UserInfoGUI::TAG);
		UserInfoGUI *gui = dynamic_cast<UserInfoGUI*> (layer);
		gui->showInfo(TypeGame::TA_LA);
	}
}

void TalaGameLogic::onAddBot()
{
}

void TalaGameLogic::onRemoveBot(char chair)
{
}

void TalaGameLogic::onReceiveJoinRoomSuccess(const CmdReceivedJoinRoomSuccess &pk)
{
	TalaScene *gui = (TalaScene *)SceneMgr::getInstance()->openScene(TalaScene::className);
	board = gui;
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_ENTER_ROOM);
    joinRoom = pk;
}

void TalaGameLogic::doJoinRoom() {
    CmdReceivedJoinRoomSuccess pk = joinRoom;
    clearRoomInfo();
    setRoomInfo(pk.roomIndex, pk.roomBet, pk.isModeSolo);
    setMyChair(pk.chair);
    setRoomOwner(pk.roomOwner);
    setRateBigBet(pk.rateBigBet);
    setRegQuit(false);
    setQuitReason(REASON_NONE);
    setGameState(NONE);

    if (myChair >= 0)
    {
        setGameState(WAITING);
        for (int i = 0; i < pk.playerInfos.size(); i++)
        {
            auto chair = serverChairToClientChair(i);
            setPlayerStatus(chair, pk.playerInfos[i].status);
            if (players[chair]->status != TalaPlayerInfo::STATUS_NONE)
            {
                players[chair]->serverChair = i;
                setPlayerInfo(chair, pk.playerInfos[i]);
                setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);
            }
        }
    }
    else
    {
        tempPlayerInfos = pk.playerInfos;
        talaInGameMgr->sendViewGame();

       // sceneMgr->addLoading(LocalizedString::to("BOARD_LOADING"));
    }
    idU       = -1;
    idWin     = 0;
    countGame = 0;
    idFirstShowPhom.clear();
    timeAuto  = 1;
    autoState = AUTO_START_STATE;
}

void TalaGameLogic::onReceiveUserJoinRoom(const CmdReceivedUserJoinRoom &pk)
{
	auto chair = serverChairToClientChair(pk.chair);
	setPlayerStatus(chair, pk.playerInfo.status);
	if (players[chair]->status != TalaPlayerInfo::STATUS_NONE) {
		players[chair]->serverChair = pk.chair;
		setPlayerInfo(chair, pk.playerInfo);
		setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);
	}
}

void TalaGameLogic::onReceiveQuitRoom(const CmdReceivedQuitRoom &pk)
{
	auto chair = serverChairToClientChair(pk.chair);
	setPlayerStatus(chair, TalaPlayerInfo::STATUS_NONE);
}

void TalaGameLogic::onReceiveQuitReason(const CmdReceivedQuitReason &pk)
{
	if (pk.chair == myChair) setQuitReason(pk.reason);
}

void TalaGameLogic::onReceiveQuitSuccess(const CmdReceivedQuitSuccess &pk)
{
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_LEAVE_ROOM);
	if (quitReason != REASON_NONE)
		ToastFloat::makeToast(ToastFloat::LONG, LocalizedString::to("BOARD_KICK_" + to_string(quitReason)));
}

void TalaGameLogic::onReceiveQuitResult(const CmdReceivedQuitResult &pk)
{
	setRegQuit(pk.result == 0);
	TalaGameSound::playEffect(regQuit ? TalaInGameMgr::SOUND_REG_QUIT : TalaInGameMgr::SOUND_CANCEL_QUIT);
}

void TalaGameLogic::onReceiveUpdateOwner(const CmdReceivedUpdateOwner & pk)
{
	setRoomOwner(pk.chair);
}

void TalaGameLogic::onReceiveAutoStart(const CmdReceivedAutoStart & pk)
{
	setRoomOwner(pk.chairStart);

	if (board) board->updateStart(pk.autoType == AUTO_COUNTDOWN, pk.time);
}

void TalaGameLogic::onReceiveNotifyStart(const CmdReceivedNotifyStart & pk)
{
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_START_MATCH);

	setGameState(PLAYING);
	setNDeckCard(pk.nDeckCard);
	for (int i = 0; i > pk.isPlaying.size(); i++)
		if (pk.isPlaying[i]) {
			auto chair = serverChairToClientChair(i);
			setPlayerStatus(chair, TalaPlayerInfo::STATUS_PLAYING);
			setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);
		}

	if (board) board->effectDealCards(serverChairToClientChair(pk.firstTurn) == 0);
	countGame++;
    JNIUtils::sendEvent("start_game_tala", "");
}

void TalaGameLogic::onReceiveUpdateCards(const CmdReceivedUpdateCards & pk)
{
	idU = -1;
	idFirstShowPhom.clear();
	players[0]->handOnCards = TalaGameRule::arrangeCard(pk.cards, players[0]->eatenCards);
	//if (board) board->effectShowCards();

	idU = autoCheckU(true);
	if (idU >= 0) {
		autoState = AUTO_NOTIFY_U;
		talaGameLogic->timeAuto = TIME_NOTIFY_U;
	}
	else {
		autoState = AUTO_CHANGE_TURN_FIRST;
		talaGameLogic->timeAuto = TIME_CHANGE_TURN_FIRST;
	}
}

void TalaGameLogic::onReceiveThrowCard(const CmdReceivedThrowCard & pk)
{
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_THROW_CARD);
	char chair = serverChairToClientChair(pk.chair);
	setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);

	players[chair]->throwCards.push_back(pk.cardId);
	for (int i = 0; i < players[chair]->handOnCards.size(); i++) {
		if (pk.cardId == players[chair]->handOnCards[i]) {
			players[chair]->handOnCards.erase(players[chair]->handOnCards.begin() + i);
			break;
		}
	}
	if (chair == 0) players[chair]->selectedCards.clear();
	bool notifyShowPhom = false;
	//if (chair != getLastEnemyChair()) {
		if (players[chair]->throwCards.size() == 4) {		//throw 4th card, and not last card of match
			for (int i = 0; i < 4; i++) {
				if (i != chair && players[i]->status == TalaPlayerInfo::STATUS_PLAYING) {
					if (players[i]->throwCards.size() < 4) {
						break;
					}
				}
			}
			notifyShowPhom = true;
		}
		else if (players[chair]->throwCards.size() == 3) {	//throw last 3rd card
			bool check = true;
			for (int i = 0; i < 4; i++) {
				if (i != chair && players[i]->status == TalaPlayerInfo::STATUS_PLAYING) {
					if (players[i]->throwCards.size() < 3) {
						check = false;
						break;
					}
				}
			}
		}
		else {
		}
	//}

	if (board) board->effectThrowCard(chair, pk.cardId);
	if (notifyShowPhom) {
		// thong bao ha phom
		CmdReceivedNotifyShowPhom cmd;
		cmd.turnTime = 20;
		cmd.chair = chair;
		cmd.allCards = players[chair]->handOnCards;
		players[chair]->selectedCards = TalaGameRule::tuDongHaBai(players[chair]->handOnCards, players[chair]->eatenCards);
		if (players[chair]->selectedCards.size() > 0)
		{
			cmd.isMom = false;
			players[chair]->isMom = false;
		}
		else
		{
			cmd.isMom = true;
			if (players[chair]->listPhom.size() == 0)
				players[chair]->isMom = true;
		}
		notifyShowPhom = true;
		onReceiveNotifyShowPhom(cmd);
	}
	else {

		autoChangeNewTurn();
	}
}

void TalaGameLogic::onReceiveReceiveCard(const CmdReceivedReceiveCard & pk)
{
	char srcChair = serverChairToClientChair(pk.srcChair);
	char desChair = serverChairToClientChair(pk.desChair);
	char throwChair = serverChairToClientChair(pk.throwChair);
	setNDeckCard(pk.nDeckCard);
	setPlayerState(desChair, TalaPlayerInfo::STATE_DANHBAI);

	if (desChair == 0) players[desChair]->selectedCards.clear();
	if (pk.srcChair < 0) {	//get card from deck
		TalaGameSound::playEffect(TalaInGameMgr::SOUND_DRAW_CARD);

		if (pk.cardId < NUM_CARD)
			players[desChair]->handOnCards.push_back(pk.cardId);
	}
	else {
		TalaGameSound::playEffect(TalaInGameMgr::SOUND_EAT_CARD);

		for (int i = 0; i < players[srcChair]->throwCards.size(); i++) {
			if (players[srcChair]->throwCards[i] == pk.cardId) {
				players[srcChair]->throwCards.erase(players[srcChair]->throwCards.begin() + i);
				players[desChair]->eatenCards.push_back(pk.cardId);
				//if (desChair == 0) {
					players[desChair]->handOnCards.push_back(pk.cardId);
					players[desChair]->handOnCards = TalaGameRule::arrangeCard(players[desChair]->handOnCards, players[desChair]->eatenCards);
				//}
				break;
			}
		}
	}
	if (pk.throwChair >= 0) {
		if (players[throwChair]->throwCards.size() > 0) {
			players[srcChair]->throwCards.push_back(players[throwChair]->throwCards[players[throwChair]->throwCards.size() - 1]);
			players[throwChair]->throwCards.erase(players[throwChair]->throwCards.begin() + players[throwChair]->throwCards.size() - 1);
		}
	}

	if (board) {
		if (desChair == 0) {
			board->effectEatableCard(getLastEnemyChair(), false);
		}
		if (pk.srcChair < 0) {
			board->effectReceiveCardFromDeck(desChair, pk.cardId);
			board->effectDarkThrowCards(getLastEnemyChair(desChair));
		}
		else {
			board->effectReceiveCardFromOther(srcChair, desChair);
			if (pk.anChot) {
				board->effectRank(desChair, AN_CHOT);
				if (desChair == 0)
					board->effectMyRank(AN_CHOT);
			}
			players[srcChair]->setGold(players[srcChair]->gold - pk.nMoney);
			players[desChair]->setGold(players[desChair]->gold - pk.nMoney);
			board->effectMoney(srcChair, -pk.nMoney);
			board->effectMoney(desChair, pk.nMoney);

			if (rateBigBet > 0) board->effectBigBet(desChair);
		}
		if (pk.throwChair >= 0) board->effectMoveThrowCard(throwChair, srcChair);
	}
}

void TalaGameLogic::onReceiveChangeTurn(const CmdReceivedChangeTurn & pk)
{
	char chair = serverChairToClientChair(pk.chair);
	for (int i = 0; i < players.size(); i++)
		setPlayerState(i, TalaPlayerInfo::STATE_NONE, -1);
	setPlayerState(chair, pk.canGetCard ? TalaPlayerInfo::STATE_BOCBAI : TalaPlayerInfo::STATE_DANHBAI, pk.time);
	players[chair]->isMom = false;
	if (board) {
		if (chair == 0) {
			if (pk.canGetCard) {
				if (canGetLastCard()) {
					board->effectEatableCard(getLastEnemyChair(), true);
				}
				autoState = AUTO_GET_CARD;
			}
			else {
				autoState = AUTO_THROW_CARD;
			}
			timeAuto = pk.time;
			TalaGameSound::playEffect(TalaInGameMgr::SOUND_CHANGE_TURN);
		}
		else {
			if (pk.canGetCard) {
				autoState = AUTO_GET_CARD;
			}
			else {
				autoState = AUTO_THROW_CARD;
			}
			genTimeAuto();
		}
	}
	currentTurn = pk.chair;
}

void TalaGameLogic::onReceiveNotifyShowPhom(const CmdReceivedNotifyShowPhom & pk)
{
	char chair = serverChairToClientChair(pk.chair);
	setPlayerState(chair, pk.isMom ? TalaPlayerInfo::STATE_NONE : TalaPlayerInfo::STATE_HABAI, pk.isMom ? -1 : pk.turnTime);
	if (idFirstShowPhom.size() == 4)
		idFirstShowPhom.erase(idFirstShowPhom.begin());
	idFirstShowPhom.push_back(chair);
	players[chair]->selectedCards = TalaGameRule::tuDongHaBai(players[chair]->handOnCards, players[chair]->eatenCards);
	if (chair == 0) {
		if (players[chair]->selectedCards.size() > 0)
			TalaGameSound::playEffect(TalaInGameMgr::SOUND_HINT_SUIT);
		board->updateHandOnCards(0.05);
	}
	else {
		if (pk.allCards.size() > 0) players[chair]->handOnCards = pk.allCards;
	}

	if (pk.isMom) {
		if (players[chair]->listPhom.size() == 0) {
            if (chair == 0)
			    TalaGameSound::playEffect(TalaInGameMgr::SOUND_RANK_MOM);
			board->effectRank(chair, RANK_MOM);
			autoChangeNewTurn();
		}
		else {
			if (canSendCard()) {
				CmdReceivedNotifySendCard cmd;
				cmd.chair = currentTurn;
				cmd.turnTime = 20;
				onReceiveNotifySendCard(cmd);
			}
			else {
				autoChangeNewTurn();
			}
		}
	}
	else {
		autoState = AUTO_SHOW_PHOM;
		if (chair == 0)
			timeAuto = pk.turnTime;
		else
			genTimeAuto();
	}
}

void TalaGameLogic::onReceiveShowPhom(const CmdReceivedShowPhom & pk)
{
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_SHOW_SUIT);
	char chair = serverChairToClientChair(pk.chair);
	setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);

	auto allSol = TalaGameRule::kiemtraHaBai(pk.cards, pk.cards, players[chair]->eatenCards);
	if (allSol.size() > 0) {
		for (int i = 0; i < allSol.size(); i++)
			players[chair]->listPhom.push_back(allSol[i]);
		for (int i = 0; i < players[chair]->handOnCards.size(); i++) {
			if (find(pk.cards.begin(), pk.cards.end(), players[chair]->handOnCards[i]) != pk.cards.end()) {
				players[chair]->handOnCards.erase(players[chair]->handOnCards.begin() + i);
				i--;
			}
		}
		players[chair]->eatenCards.clear();
		if (chair == 0) players[0]->selectedCards.clear();
	}

	if (board) board->effectShowPhom(chair, false);

	// chuyen sang turn gui bai
	if (canSendCard()) {
		CmdReceivedNotifySendCard cmd;
		cmd.chair = currentTurn;
		cmd.turnTime = 20;
		onReceiveNotifySendCard(cmd);
	}
	else {
		// chuyen sang turn nguoi khac
		autoChangeNewTurn();
	}
}

void TalaGameLogic::onReceiveNotifyU(const CmdReceivedNotifyU & pk)
{
	setGameState(ENDING);
	for (int i = 0; i < players.size(); i++)
		setPlayerState(i, TalaPlayerInfo::STATE_NONE, -1);
	if (pk.chair == 0)
		JNIUtils::sendEvent("notify_myU", "1");
	else
		JNIUtils::sendEvent("notify_otherU", "1");
	auto chair = serverChairToClientChair(pk.chair);
	players[0]->selectedCards.clear();
	if (chair == 0) TalaGameSound::playEffect(TalaInGameMgr::SOUND_RANK_U);
	else TalaGameSound::playEffect(TalaInGameMgr::SOUND_RANK_LOSE);

	if (players[chair]->listPhom.size() == 0 && TalaGameRule::kiemtraUKhan(pk.allCards)) {	//u khan
		if (chair != 0) players[chair]->handOnCards = pk.allCards;
		if (board) {
			for (int i = 0; i < players.size(); i++) {
				if (players[i]->status != TalaPlayerInfo::STATUS_PLAYING) continue;
				board->effectRank(i, i == chair ? U_KHAN : RANK_BET);
			}
			board->effectMyRank(chair == 0 ? U_KHAN : RANK_BET);
			if (chair != 0) board->effectShowCardsOther(chair, false);
			else board->effectJackpot();
		}
		JNIUtils::sendEvent("u_khan", "1");
	}
	else {
        if (pk.allCards.size() > 0)
            players[chair]->handOnCards = pk.allCards;
		auto showCards = TalaGameRule::tuDongHaBai(players[chair]->handOnCards, players[chair]->eatenCards);
		auto allSol = TalaGameRule::kiemtraHaBai(players[chair]->handOnCards, showCards, players[chair]->eatenCards);
		if (allSol.size() > 0) {
			for (int i = 0; i < allSol.size(); i++)
				players[chair]->listPhom.push_back(allSol[i]);

            for (int i = 0; i < players[chair]->handOnCards.size(); i++) {
                if (find(showCards.begin(), showCards.end(), players[chair]->handOnCards[i]) != showCards.end()) {
                    players[chair]->handOnCards.erase(players[chair]->handOnCards.begin() + i);
                    i--;
                }
            }
			players[chair]->eatenCards.clear();
		}

		if (board) {
			board->effectShowPhom(chair, true);

			char rank;
			if (allSol.size() > 0)
				rank = pk.isUTron ? U_TRON : U_NORMAL;
			else rank = U_NORMAL;
			for (int i = 0; i < players.size(); i++)
				if (players[i]->status == TalaPlayerInfo::STATUS_PLAYING) {
					board->effectRank(i, i == chair ? rank : RANK_BET);
					if (i == 0) board->effectMyRank(chair == 0 ? rank : RANK_BET);
				}
			if (rank == U_NORMAL)
				JNIUtils::sendEvent("u_normal", "1");
			else if (rank == U_TRON)
				JNIUtils::sendEvent("u_tron", "1");
		}
	}

	if (board) board->effectDarkAllCards();

	for (int i = 0; i < pk.playerMoneys.size(); i++) {
		if (pk.playerMoneys[i] != 0) {
			auto chair = serverChairToClientChair(i);
			if (board) {
				players[chair]->setGold(players[chair]->gold + pk.playerMoneys[i]);
				board->effectMoney(chair, pk.playerMoneys[i]);
				if (pk.playerMoneys[i] > 0 && rateBigBet > 0) board->effectBigBet(chair);
				if (i == pk.chairDen) board->effectDenTien(chair);
			}
		}
	}

	autoState = AUTO_END_GAME;
	timeAuto = TIME_RESULT;
}

void TalaGameLogic::onReceiveNotifySendCard(const CmdReceivedNotifySendCard & pk)
{
	auto chair = serverChairToClientChair(pk.chair);
	currentTurn = chair;
	setPlayerState(chair, TalaPlayerInfo::STATE_GUIBAI, pk.turnTime);
	hintSendCard();
	autoState = AUTO_SEND_CARD;
	if (chair == 0) {
		if (board) {
			board->effectHintSendCard();
			board->updateHandOnCards();
		}
		timeAuto = pk.turnTime;
	}
	else {
		genTimeAuto();
	}
}

void TalaGameLogic::onReceiveSendCard(const CmdReceivedSendCard & pk)
{
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_SEND_CARD);
	auto srcChair = serverChairToClientChair(pk.senderChair);
	auto desChair = serverChairToClientChair(pk.targetChair);

	for (int i = 0; i < players[desChair]->listPhom.size(); i++) {
		auto &suit = players[desChair]->listPhom[i];
		if (find(suit.begin(), suit.end(), pk.targetCardId) != suit.end()) {
			suit = TalaGameRule::addCardToSuit(suit, pk.senderCardId);
			for (int j = 0; j < players[srcChair]->handOnCards.size(); j++)
				if (players[srcChair]->handOnCards[j] == pk.senderCardId)
					players[srcChair]->handOnCards.erase(players[srcChair]->handOnCards.begin() + j);
			if (srcChair == 0) hintSendCard();
			if (board) board->effectSendCard(srcChair, desChair, pk.senderCardId);
			break;
		}
	}
}

void TalaGameLogic::onReceiveTaiLuot(const CmdReceivedTaiLuot & pk)
{
	auto chair = serverChairToClientChair(pk.chair);
	if (board) board->effectMoreTurn(chair);
}

void TalaGameLogic::onReceiveNewMatch(const CmdReceivedNewMatch & pk)
{
	setGameState(WAITING);
	setMyChair(pk.chair);

	for (int i = 0; i < pk.playerInfos.size(); i++) {
		auto chair = serverChairToClientChair(i);
		setPlayerStatus(chair, pk.playerInfos[i].status);
		if (players[chair]->status != TalaPlayerInfo::STATUS_NONE) {
			players[chair]->serverChair = i;
			setPlayerInfo(chair, pk.playerInfos[i]);
			setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);
		}
	}
}

void TalaGameLogic::onReceiveContinueMatch(const CmdReceivedContinueMatch & pk)
{

}

void TalaGameLogic::onReceiveEndMatch(const CmdReceivedEndMatch & pk)
{
	setRateBigBet(0);

	clearAllCards();
	if (board) board->clearEffectRank();
	autoState = AUTO_START_STATE;
	timeAuto = TIME_END_GAME;
	if (countGame % 3 == 0)
            if (gameMgr->useAds)
                JNIUtils::showAdsFull();
}

void TalaGameLogic::onReceiveViewGameInfo(const CmdReceivedViewGameInfo & pk)
{
	sceneMgr->clearLoading();
	setGameState(PLAYING);
	setNDeckCard(pk.nDeckCard);
	auto state = pk.playerAction;
	auto time = pk.turnTime;
	if (state != TalaPlayerInfo::STATE_BOCBAI && state != TalaPlayerInfo::STATE_DANHBAI && state != TalaPlayerInfo::STATE_HABAI && state != TalaPlayerInfo::STATE_GUIBAI) {
		state = TalaPlayerInfo::STATE_NONE;
		time = -1;
	}
	setPlayerState(serverChairToClientChair(pk.currentChair), state, time > 0 ? time : -1);

	for (int i = 0; i < pk.playerCards.size(); i++) {
		if (pk.hasPlayer[i]) {
			auto chair = serverChairToClientChair(i);
			if (chair == 0) continue;
			auto player = players[chair];
			auto playerCard = pk.playerCards[i];

			player->handOnCards.clear();
			player->selectedCards.clear();

			//set throw cards
			player->throwCards.clear();
			for (int j = 0; j < playerCard.throwCards.size(); j++)
				player->throwCards.push_back(playerCard.throwCards[j]);

			//set eaten cards
			player->eatenCards.clear();
			for (int j = 0; j < playerCard.handOnCards.size(); j++)
				if (playerCard.isEatens[j])
					player->eatenCards.push_back(playerCard.handOnCards[j]);

			//set list phom
			player->listPhom.clear();
			if (playerCard.isShowCard) {
				for (int j = 0; j < playerCard.listPhom.size(); j++) {
					player->listPhom.push_back(vector<char>());
					auto phom = playerCard.listPhom[j];
					for (int k = 0; k < phom.size(); k++)
						player->listPhom[j].push_back(phom[k]);
				}
			}
		}
	}

	if (board) board->updateAllCards();
}

void TalaGameLogic::onReceiveGameResult(const CmdReceivedGameResult & pk)
{
	setGameState(ENDING);
	for (int i = 0; i < players.size(); i++)
		setPlayerState(i, TalaPlayerInfo::STATE_NONE, -1);

	players[0]->selectedCards.clear();
	if (board) board->effectDarkAllCards();

	//effect rank and money
	auto ranks = pk.rank;
	for (int i = 0; i < ranks.size(); i++) {
		auto chair = serverChairToClientChair(i);
		if (players[chair]->status != TalaPlayerInfo::STATUS_PLAYING) continue;
		if (ranks[i] == (getNumPlaying() - 1)) ranks[i] = RANK_BET;
		if (board) {
            board->effectRank(chair, pk.isMom[i] ? RANK_MOM : ranks[i], 4);
			if (chair == 0) {
				auto myRank = pk.isMom[i] && ranks[i] != 0 ? RANK_MOM : ranks[i];
                board->effectMyRank(myRank, 4);
            }
            float time = 3 - 1 * ranks[i];
            players[chair]->score = pk.arrayScore[i];
            board->effectShowCardsOther(chair, true, time);
			players[chair]->setGold(players[chair]->gold + pk.moneyGet[i]);
			board->effectMoney(chair, pk.moneyGet[i], 4);

			if (pk.moneyGet[i] > 0 && rateBigBet > 0) board->effectBigBet(chair);
		}
	}

	autoState = AUTO_END_GAME;
	timeAuto = TIME_RESULT;
}

void TalaGameLogic::onReceiveUserTakeChair(const CmdReceivedUserTakeChair & pk)
{
	if (pk.error == 0 && tempPlayerInfos.size() > 0) {
		setMyChair(pk.chair);
		for (int i = 0; i < tempPlayerInfos.size(); i++) {
			auto chair = serverChairToClientChair(i);
			if (tempPlayerInfos[i].status != TalaPlayerInfo::STATUS_NONE
				&& tempPlayerInfos[i].status != TalaPlayerInfo::STATUS_PLAYING
				&& tempPlayerInfos[i].status != TalaPlayerInfo::STATUS_VIEWING)
				tempPlayerInfos[i].status = TalaPlayerInfo::STATUS_PLAYING;
			setPlayerStatus(chair, chair == 0 ? TalaPlayerInfo::STATUS_VIEWING : tempPlayerInfos[i].status);
			if (players[chair]->status != TalaPlayerInfo::STATUS_NONE) {
				players[chair]->serverChair = i;
				setPlayerInfo(chair, tempPlayerInfos[i]);
				setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);
			}
		}
	}
}

void TalaGameLogic::onReceiveUserView(const CmdReceivedUserView & pk)
{
	auto chair = serverChairToClientChair(pk.chair);
	setPlayerStatus(chair, TalaPlayerInfo::STATUS_VIEWING);

	players[chair]->serverChair = pk.chair;
	setPlayerInfo(chair, pk.playerInfo);
	setPlayerState(chair, TalaPlayerInfo::STATE_NONE, -1);
}

void TalaGameLogic::onReceiveRateBigBet(const CmdReceivedRateBigBet & pk)
{
	setRateBigBet(pk.rateBigBet, true);
}

char TalaGameLogic::serverChairToClientChair(char serverChair)
{
	auto chair = serverChair - myChair;
	if (isModeSolo) {
		if (abs(chair) == 2) chair = 3;
		else if ((myChair == 0 && chair == 1) || (myChair == 1 && chair == -1)) chair = 2;
	}
	if (chair < 0) chair += 4;
	else if (chair >= NUM_PLAYER) chair -= 4;
	return chair;
}

char TalaGameLogic::clientChairToServerChair(char clientChair)
{
	return players[clientChair]->serverChair;
}

char TalaGameLogic::getLastEnemyChair(char chair)
{
	for (int i = 1; i < players.size(); i++)
		if (players[(chair + i) % players.size()]->status == TalaPlayerInfo::STATUS_PLAYING)
			return (chair + i) % players.size();
	return -1;
}

bool TalaGameLogic::isOwner()
{
	return myChair == roomOwner;
}

bool TalaGameLogic::isWaiting()
{
	return gameState == WAITING;
}

bool TalaGameLogic::isPlaying()
{
	return gameState == PLAYING;
}

bool TalaGameLogic::isEnding()
{
	return gameState == ENDING;
}

char TalaGameLogic::getRoomOwner()
{
	if (myChair < 0) return -1;
	if (roomOwner < 0) return -1;
	return serverChairToClientChair(roomOwner);
}

int TalaGameLogic::getNumPlaying()
{
	int count = 0;
	for (int i = 0; i < players.size(); i++)
		if (players[i]->status == TalaPlayerInfo::STATUS_PLAYING) count++;
	return count;
}

bool TalaGameLogic::getIPCount(char chair)
{
	if (players[chair]->status == TalaPlayerInfo::STATUS_NONE) return false;
	for (int i = 0; i < players.size(); i++)
		if (i != chair && players[i]->status != TalaPlayerInfo::STATUS_NONE && players[chair]->ip == players[i]->ip)
			return true;
	return false;
}

bool TalaGameLogic::canGetLastCard()
{
	auto lastChair = getLastEnemyChair();
	if (lastChair < 0) return false;

	if (players[lastChair]->throwCards.size() > 0) {
		auto cardId = players[lastChair]->throwCards[players[lastChair]->throwCards.size() - 1];
		if (TalaGameRule::kiemtraAnQuan(players[0]->handOnCards, players[0]->eatenCards, cardId))
			return true;
	}
	return false;
}

bool TalaGameLogic::otherCanGetLastCard(char chair)
{
	auto lastChair = getLastEnemyChair(chair);
	if (lastChair < 0) return false;

	if (players[lastChair]->throwCards.size() > 0) {
		auto cardId = players[lastChair]->throwCards[players[lastChair]->throwCards.size() - 1];
		if (TalaGameRule::kiemtraAnQuan(players[chair]->handOnCards, players[chair]->eatenCards, cardId))
			return true;
	}
	return false;
}

void TalaGameLogic::hintSendCard()
{
	players[currentTurn]->selectedCards.clear();
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->status != TalaPlayerInfo::STATUS_PLAYING) continue;
		if (board && currentTurn == 0) board->effectHintSuit(i);
		auto suits = players[i]->listPhom;
		for (int j = 0; j < suits.size(); j++) {
			for (int k = 0; k < players[currentTurn]->handOnCards.size(); k++) {
				if (TalaGameRule::kiemtraGuiBai(suits[j], players[currentTurn]->handOnCards[k])) {
					players[currentTurn]->selectedCards.push_back(players[currentTurn]->handOnCards[k]);
					if (board && currentTurn == 0) board->effectHintSuit(i, j);
				}
			}
		}
	}
}

bool TalaGameLogic::canSendCard()
{
	players[currentTurn]->selectedCards.clear();
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->status != TalaPlayerInfo::STATUS_PLAYING) continue;
		auto suits = players[i]->listPhom;
		for (int j = 0; j < suits.size(); j++) {
			for (int k = 0; k < players[currentTurn]->handOnCards.size(); k++) {
				if (TalaGameRule::kiemtraGuiBai(suits[j], players[currentTurn]->handOnCards[k])) {
					return true;
				}
			}
		}
	}
	return false;
}

void TalaGameLogic::autoChangeNewTurn()
{
	int i;
	for (i = 0; i < NUM_PLAYER; i++) {
		if (players[i]->throwCards.size() < 4)
			break;
	}
	if (i >= NUM_PLAYER) {
		autoShowResult();
		return;
	}
	CmdReceivedChangeTurn cmd1;
	talaGameLogic->currentTurn--;
	if (talaGameLogic->currentTurn < 0)
		talaGameLogic->currentTurn = NUM_PLAYER - 1;
	cmd1.chair = talaGameLogic->currentTurn;
	cmd1.canGetCard = true;
	cmd1.time = 20;
	talaGameLogic->onReceiveChangeTurn(cmd1);
}

int TalaGameLogic::getThrowChair(char srcChair)
{
	int lastEnemy = getLastEnemyChair(srcChair);
	if (players[srcChair]->throwCards.size() - 1 < players[lastEnemy]->throwCards.size()) {
		AXLOGD("Need change card ");
		// can phai dao quan Card
		for (int i = 3; i > 0; i--) {
			int throwChair = srcChair + i;
			throwChair = throwChair % 4;
			if (players[srcChair]->throwCards.size() - 1 < players[throwChair]->throwCards.size()) {
				return throwChair;
			}
		}
	}
	return -1;
}

void TalaGameLogic::autoGenCard()
{

	CmdReceivedNotifyStart cmdStart;
	for (int i = 0; i < NUM_PLAYER; i++)
		cmdStart.isPlaying.push_back(i);
	cmdStart.firstTurn = idWin;
	cmdStart.nDeckCard = 15;
	onReceiveNotifyStart(cmdStart);
	CmdReceivedUpdateCards cmdCard;
	arrayCard.clear();
	for (int i = 0; i < 52; i++) {
		arrayCard.push_back(i);
	}
	int num = idWin == 0 ? 10 : 9;
	for (int i = 0; i < num; i++) {
		int index = floor(AXRANDOM_0_1() * arrayCard.size());
		cmdCard.cards.push_back(char(arrayCard[index]));
		arrayCard.erase(arrayCard.begin() + index);
	}
	//cmdCard.cards.clear();
	char arr0[10] = { 44, 45, 46, 16, 17, 18, 32, 33, 34, 35 }; //u tron
	//char arr0[10] = { 0, 1, 10, 12, 17, 22, 24, 37, 41, 45 };
//    char arr0[10] = {4, 8, 12, 21, 22, 23, 47, 46, 9, 30};  // u tron
//        char arr0[10] = {1, 2, 3, 21, 28, 10, 35, 36, 40, 30};  // u tron
        char arr3[9] = {3, 4, 5, 6, 10, 11, 15, 33, 49};
	for (int i = 0; i < 10; i++) {
		//cmdCard.cards.push_back(arr0[i]);
	}
	for (int i = 0; i < 3; i++) {
		vector<char> arr;
		num = idWin == (i + 1) ? 10 : 9;
		for (int j = 0; j < num; j++) {
			int index = floor(AXRANDOM_0_1() * arrayCard.size());
			arr.push_back(char(arrayCard[index]));
			arrayCard.erase(arrayCard.begin() + index);
		}
		players[i + 1]->handOnCards = arr;
	}
      // players[3]->handOnCards.clear();
        for (int i = 0; i < 9; i++)
        {
          //  players[3]->handOnCards.push_back(arr0[i]);
        }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arrayCard.begin(), arrayCard.end(), g);
	onReceiveUpdateCards(cmdCard);
}


void TalaGameLogic::autoGetCard()
{
	// Lay bai va chuyen sang turn danh bai
	if (otherCanGetLastCard(currentTurn)) {
		//board->effectEatableCard(getLastEnemyChair(), true);
		CmdReceivedReceiveCard cmd;
		cmd.srcChair = getLastEnemyChair(currentTurn);
		cmd.desChair = currentTurn;
		cmd.throwChair = getThrowChair(cmd.srcChair);
		cmd.cardId = players[cmd.srcChair]->throwCards[players[cmd.srcChair]->throwCards.size() - 1];
		bool isChot = players[cmd.srcChair]->throwCards.size() == 4;

		cmd.anChot = isChot;
		cmd.nEaten = players[cmd.desChair]->eatenCards.size() + 1;
		cmd.nMoney = cmd.nEaten * 1000 * (isChot ? 3 : 1);
		cmd.nDeckCard = arrayCard.size();
		cmd.money = 1;
		onReceiveReceiveCard(cmd);

		idU = autoCheckU(false);
		if (idU >= 0) {
			autoNotifyU();
		}
		else {
			CmdReceivedChangeTurn cmd1;
			cmd1.chair = this->currentTurn;
			cmd1.canGetCard = false;
			cmd1.time = 20;
			this->onReceiveChangeTurn(cmd1);
		}

	}
	else {
		autoGetFromDeck();
	}
}

void TalaGameLogic::autoGetFromDeck()
{
	CmdReceivedReceiveCard cmd;
	cmd.srcChair = -1;
	cmd.desChair = currentTurn;
	cmd.throwChair = -1;
	cmd.cardId = char(this->arrayCard[this->arrayCard.size() - 1]);
	arrayCard.pop_back();
	cmd.anChot = false;
	cmd.nEaten = 0;
	cmd.nMoney = 0;
	cmd.nDeckCard = arrayCard.size();
	cmd.money = 0;
	onReceiveReceiveCard(cmd);

	idU = autoCheckU(false);
	if (idU >= 0) {
		autoNotifyU();
	}
	else {
		CmdReceivedChangeTurn cmd1;
		cmd1.chair = this->currentTurn;
		cmd1.canGetCard = false;
		cmd1.time = 20;
		this->onReceiveChangeTurn(cmd1);
	}
}

void TalaGameLogic::autoThrowCard()
{
	// danh bai va chuyen sang turn nguoi khac

	vector<char> selectedCards = TalaGameRule::tuDongHaBai(players[currentTurn]->handOnCards, players[currentTurn]->eatenCards);
	vector<char> arrayRandom;
	for (int i = 0; i < players[currentTurn]->handOnCards.size(); i++) {
		int j = 0;
		for (j = 0; j < selectedCards.size(); j++) {
			if (selectedCards[j] == players[currentTurn]->handOnCards[i])
				break;
		}
		if (j >= selectedCards.size())
			arrayRandom.push_back(players[currentTurn]->handOnCards[i]);
	}

	splitAutoThrowCard1(arrayRandom);
}

void TalaGameLogic::splitAutoThrowCard1(vector<char> arrayRandom) {
	if (arrayRandom.size() == 0) {
		splitAutoThrowCard3(52);
	}
	else if (arrayRandom.size() == 1) {
		splitAutoThrowCard3(arrayRandom[0]);
	}
	else {
		splitAutoThrowCard2(arrayRandom);
	}
}

void TalaGameLogic::splitAutoThrowCard2(vector<char> arrayRandom) {
	sort(arrayRandom.begin(), arrayRandom.end());
	int index = arrayRandom.size() - 1;
	for (int i = arrayRandom.size() - 1; i >= 0; i--) {
        bool canThrow = true;
        for (int i1 = 0; i1 < players.size(); i1++)
        {
            auto suits = players[i1]->listPhom;
            for (int j1 = 0; j1 < suits.size(); j1++)
            {
                if (TalaGameRule::kiemtraGuiBai(suits[j1], arrayRandom[i]))
                {
                    // neu quan card nay co the gui thi no khong thoa man
                    canThrow = false;
                    break;
                }
            }
            if (canThrow == false)
            {
                break;
            }
        }
        if (canThrow == false)
            continue;
        if (arrayCard.size() < 4)
        {
            index = i;
            break;
        }
        index          = i;
		bool canSelect = true;
		for (int j = 0; j < arrayRandom.size(); j++) {
			if (j != i) {
				int n1 = arrayRandom[i] / 4;
				int s1 = arrayRandom[i] % 4;
				int n2 = arrayRandom[j] / 4;
				int s2 = arrayRandom[j] % 4;
				if (n1 == n2) {
					canSelect = false;
					break;
				}
				if (s1 == s2) {
					if (abs(n1 - n2) <= 2)
					{
						canSelect = false;
						break;
					}
				}
			}
		}
		if (canSelect) {
			index = i;
			break;
		}
	}
	splitAutoThrowCard3(arrayRandom[index]);
}

void TalaGameLogic::splitAutoThrowCard3(char card) {


	CmdReceivedThrowCard cmd;
	int index = 0;
    // Lay ra quan Card dau tien khong nam trong mang quan da an de lam quan mac dinh
	for (int i = 0; i < players[currentTurn]->handOnCards.size(); i++) {
		int j = 0;
		for (j = 0; j < players[currentTurn]->eatenCards.size(); j++) {
			if (players[currentTurn]->eatenCards[j] == players[currentTurn]->handOnCards[i])
				break;
		}
		if (j >= players[currentTurn]->eatenCards.size()) {
			index = i;
			break;
		}
	}
	// Lay vi tri quan Card duoc truyen vao
	for (int i = 0; i < players[currentTurn]->handOnCards.size(); i++) {
		if (card == players[currentTurn]->handOnCards[i]) {
			index = i;
			break;
		}
	}
	cmd.cardId = players[currentTurn]->handOnCards[index];
	players[currentTurn]->handOnCards.erase(players[currentTurn]->handOnCards.begin() + index);
	cmd.chair = currentTurn;
	this->onReceiveThrowCard(cmd);
}

void TalaGameLogic::autoShowPhom()
{
	CmdReceivedShowPhom cmd;
	cmd.chair = currentTurn;
	cmd.cards = players[currentTurn]->selectedCards;
	onReceiveShowPhom(cmd);
}

void TalaGameLogic::autoShowResult()
{
	vector<int> score;
	vector<int> scoreHa;
	vector<int> scoreSort;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (players[i]->isMom) {
			score.push_back(1000);
		}
		else {
			score.push_back(0);
			for (int j = 0; j < players[i]->handOnCards.size(); j++) {
				score[i] = score[i] + floor(players[i]->handOnCards[j] / 4 + 1);
			}
		}
		for (int j = 0; j < NUM_PLAYER; j++) {
			if (i == idFirstShowPhom.at(j)) {
				scoreHa.push_back(j);
				break;
			}
		}
		scoreSort.push_back(i);
	}
	for (int i = 0; i < NUM_PLAYER - 1; i++) {
		for (int j = i + 1; j < NUM_PLAYER; j++) {
			int index1 = scoreSort[i];
			int index2 = scoreSort[j];
			bool isSwap = true;
			if (score[index1] > score[index2]) {
				isSwap = true;
			}
			else if (score[index1] == score[index2]) {
				if (scoreHa[index1] > scoreHa[index2]) {
					isSwap = true;
				}
				else {
					isSwap = false;
				}
			}
			else {
				isSwap = false;
			}
			if (isSwap) {
				int temp = scoreSort[i];
				scoreSort[i] = scoreSort[j];
				scoreSort[j] = temp;
			}
		}
	}
	CmdReceivedGameResult cmd;
	cmd.hasJackpot = false;
	int indexWin = 0;
	int sumMoney = 0;
	bool allMom = true;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (players[i]->isMom == false)
		{
			allMom = false;
			break;
		}
	}
	for (int i = 0; i < NUM_PLAYER; i++) {
		int money = 0;
		cmd.isMom.push_back(players[i]->isMom);
		int rank = -1;
		for (int j = 0; j < scoreSort.size(); j++) {
			if (i == scoreSort[j]) {
				if (j == 0) {
					rank = RANK_NHAT;
					indexWin = i;
				}
				else {
					if (players[i]->isMom) {
						rank = RANK_MOM;
					}
					else {
						rank = j;
					}
				}
				break;
			}
		}
		if (rank == RANK_MOM) {
			money = -6;
		}
		else if (rank == RANK_NHAT) {
			money = 0;
		}
		else {
			money = -rank;

		}
		sumMoney = sumMoney + abs(money);
		cmd.rank.push_back(rank);
		cmd.moneyGet.push_back(money * 1000);
        cmd.arrayScore.push_back(score[i]);
	}
	cmd.moneyGet[indexWin] = sumMoney * 1000;
	onReceiveGameResult(cmd);
	if (indexWin == 0) {
		players[0]->setWinCount(players[0]->winCount + 1);
	}
	else {
		players[0]->setWinCount(players[0]->lostCount + 1);
	}
	idWin = indexWin;
	if (indexWin == myChair) {
		JNIUtils::sendEvent("my_win", "1");
	}
	else {
		JNIUtils::sendEvent("other_win", "1");
	}
}

void TalaGameLogic::genTimeAuto()
{
	float addTime = (10 - players[0]->winCount) / 10.0f;
    if (addTime < 0)
        addTime = 0;
    addTime  = 0;
    timeAuto = TIME_CHANGE_TURN + AXRANDOM_0_1() * 1 + addTime;
}


int TalaGameLogic::autoCheckU(bool checkUKhan)
{
	if (checkUKhan) {
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (players[i]->listPhom.size() == 0 && TalaGameRule::kiemtraUKhan(players[i]->handOnCards)) {	//u khan
				typeU = U_KHAN;
				return i;
			}
		}
	}
	for (int i = 0; i < NUM_PLAYER; i++) {
		vector<char> showCards = TalaGameRule::tuDongHaBai(players[i]->handOnCards, players[i]->eatenCards);
		if (showCards.size() == 10) {
			typeU = U_TRON;
			return i;
		}
	}
	for (int i = 0; i < NUM_PLAYER; i++) {
		vector<char> showCards = TalaGameRule::tuDongHaBai(players[i]->handOnCards, players[i]->eatenCards);
		if (showCards.size() >= 9) {
			if (showCards.size() == 9)
				typeU = U_NORMAL;
			return i;
		}
	}
	return -1;
}

void TalaGameLogic::autoNotifyU()
{
	CmdReceivedNotifyU cmd;

	cmd.allCards = players[idU]->handOnCards;
	cmd.chair = idU;
	cmd.chairDen = -1;
	cmd.eatCards = players[idU]->eatenCards;
	cmd.hasJackpot = false;
	cmd.isUTron = typeU == U_TRON;
	int money = typeU == U_TRON ? 12000 : 6000;
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (i == idU)
			cmd.playerMoneys.push_back(money * 3);
		else
			cmd.playerMoneys.push_back(-money);
	}
	if (idU == 0) {
		players[0]->setWinCount(players[0]->winCount + 1);
	}
	else {
		players[0]->setWinCount(players[0]->lostCount + 1);
	}
	onReceiveNotifyU(cmd);
	idWin = idU;
}

void TalaGameLogic::clearRoomInfo()
{
	roomIndex = -1;
	roomBet = 0;
	isModeSolo = false;
	roomOwner = -1;
	rateBigBet = 0;

	myChair = -1;
	nDeckCard = 0;
	regQuit = false;
	quitReason = REASON_NONE;
	gameState = NONE;

	for (int i = 0; i < players.size(); i++) {
		players[i]->handOnCards.clear();
		players[i]->eatenCards.clear();
		players[i]->throwCards.clear();
		players[i]->listPhom.clear();
		players[i]->status == TalaPlayerInfo::STATUS_NONE;
		players[i]->state == TalaPlayerInfo::STATE_NONE;
	}
	tempPlayerInfos.clear();

	if (board) board->clearRoomInfo();
}

void TalaGameLogic::clearAllCards()
{
	for (int i = 0; i < players.size(); i++) {
		players[i]->handOnCards.clear();
		players[i]->eatenCards.clear();
		players[i]->throwCards.clear();
		players[i]->listPhom.clear();
	}

	if (board) board->effectClearAllCards();
}

void TalaGameLogic::setRoomInfo(int roomIndex, long long roomBet, bool isModeSolo)
{
	this->roomIndex = roomIndex;
	this->roomBet = roomBet;
	this->isModeSolo = isModeSolo;

	if (board) board->updateRoomInfo();
}

void TalaGameLogic::setMyChair(char myChair)
{
	this->myChair = myChair;
}

void TalaGameLogic::setRoomOwner(char roomOwner)
{
	this->roomOwner = roomOwner;

	if (board) board->updateRoomOwner();
}

void TalaGameLogic::setRateBigBet(char rateBigBet, bool animate)
{
	this->rateBigBet = rateBigBet;

	if (board) board->updateBigBet(animate);
}

void TalaGameLogic::setRegQuit(bool regQuit)
{
	if (this->regQuit != regQuit) {
		this->regQuit = regQuit;
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to(this->regQuit ? "REG_QUIT" : "CANCEL_REG_QUIT"));
	}

	if (board) board->updateQuitReg();
}

void TalaGameLogic::setQuitReason(char reason)
{
	if (reason == -1) quitReason = REASON_ERROR;
	else if (reason != REASON_NONE && reason != REASON_GOLD && reason != REASON_READY && reason != REASON_EMPTY
		&& reason != REASON_ERROR && reason != REASON_NETWORK && reason != REASON_AFK)
		quitReason = REASON_READY;
	else quitReason = reason;
}

void TalaGameLogic::setGameState(GameState state)
{
	gameState = state;

	if (board) {
		for (int i = 0; i < players.size(); i++)
			board->updateGameInfo(i);
		if (gameState == PLAYING) board->updateStart(false);
		if (gameState == ENDING)
			if (!regQuit) talaInGameMgr->sendConnectRoom();
		board->updateWait();
		board->updateAction();
		board->updateBigBet();
		board->setTouchEnabled(gameState == PLAYING && players[0]->status == TalaPlayerInfo::STATUS_PLAYING && (players[0]->state == TalaPlayerInfo::STATE_BOCBAI || players[0]->state == TalaPlayerInfo::STATE_GUIBAI));
	}
}

void TalaGameLogic::setNDeckCard(char nDeckCard)
{
	this->nDeckCard = nDeckCard;

	if (board) board->updateDeckCard();
}

void TalaGameLogic::setPlayerStatus(char chair, char status)
{
	if (status != TalaPlayerInfo::STATUS_NONE && status != TalaPlayerInfo::STATUS_PLAYING && status != TalaPlayerInfo::STATUS_VIEWING)
		status = TalaPlayerInfo::STATUS_PLAYING;
	players[chair]->status = status;

	if (board) {
		board->updateGameInfo(chair);
		board->updateIP();
		board->updateWait();
		board->setTouchEnabled(gameState == PLAYING && players[0]->status == TalaPlayerInfo::STATUS_PLAYING && (players[0]->state == TalaPlayerInfo::STATE_BOCBAI || players[0]->state == TalaPlayerInfo::STATE_GUIBAI));
	}
}

void TalaGameLogic::setPlayerState(char chair, char state, char time)
{
	players[chair]->state = state;

	if (board) {
		board->updateGameInfo(chair);
		board->updateAction();
		if (time != 0) board->updateTimer(chair, time);
		board->setTouchEnabled(gameState == PLAYING && players[0]->status == TalaPlayerInfo::STATUS_PLAYING && (players[0]->state == TalaPlayerInfo::STATE_BOCBAI || players[0]->state == TalaPlayerInfo::STATE_GUIBAI));
	}
}

void TalaGameLogic::setPlayerInfo(char chair, TalaPlayerInfo info)
{
	auto player = players[chair];
	player->uID = info.uID;
	player->gold = info.gold;
	player->avatar = info.avatar;
	player->displayName = info.displayName;
	player->level = info.level;
	player->exp = info.exp;
	player->winCount = info.winCount;
	player->lostCount = info.lostCount;
	player->vip = info.vip;
	player->ip = info.ip;

	if (board) {
		board->updateUserInfo(chair);
		board->updateIP();
	}
}


void TalaGameLogic::onReward(int num)
{
	TalaScene *gui = (TalaScene *)SceneMgr::getInstance()->getMainLayer();
	if (num > 0) {
		autoState = REWARD_SUCCESS_STATE;
		timeAuto = 0.5;
	}
	else {
		autoState = REWARD_FAIL_STATE;
		timeAuto = 0.5;
	}
	AXLOGD("Num %i ", num);
	/*string reason = "";
	if (num > 0) {
		reason = LocalizedString::to("RECEIVE_NUM");
		reason = StringUtility::replaceAll(reason, "@gold",  "30.000");
		sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {
			arrayPlayer[0]->Gold(30000);
			TalaScene *gui = (TalaScene *)SceneMgr::getInstance()->getMainLayer();
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

bool TalaGameLogic::checkGetSupport()
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
			TalaGameLogic::getInstance()->players[0]->setGold(15000);
			TalaScene *gui = (TalaScene *)SceneMgr::getInstance()->getMainLayer();
            if (gui)
			    gui->updateUserInfo(0);
		});
		JNIUtils::sendEvent("get_support", "1");
		UserDefault::getInstance()->setStringForKey("daySupport", s1);
		UserDefault::getInstance()->flush();
		return true;
	}
	return false;
}


void TalaGameLogic::update(float delta)
{
	if (TalaGameLogic::getInstance()->timeAuto >= 0) {
		TalaGameLogic::getInstance()->timeAuto = TalaGameLogic::getInstance()->timeAuto - delta;
		if (TalaGameLogic::getInstance()->timeAuto <= 0) {
			switch (autoState)
			{
			case AUTO_START_STATE:
                autoStartState();
				break;
			case AUTO_CHANGE_TURN_FIRST: {
                autoChangeTurnFirstState();
				break;
			}
			case AUTO_GET_CARD: {
                autoGetCardState();
				break;
			}
			case AUTO_THROW_CARD: {
                autoThrowCardState();
				break;
			}
			case AUTO_SHOW_PHOM: {
                autoShowPhomState();
				break;
			}
			case AUTO_SEND_CARD: {
                autoSendCardState();
				break;
			}
			case AUTO_NOTIFY_U: {
                autoNotifyUState();
				break;
			}
			case AUTO_END_GAME: {
                autoEndGameState();
				break;
			}
			case REWARD_FAIL_STATE:
			{
                autoRewardFailState();
				break;
			}
			case REWARD_SUCCESS_STATE:
			{
                autoRewardSuccessState();
				break;
			}
		}
		}
	}
}

void TalaGameLogic::autoStartState() {
    if (board == nullptr)
        return;
    board->pStart->setVisible(true);
    board->btnStart->setVisible(true);
    board->btnStart->setTouchEnabled(true);
    for (int i = 1; i < NUM_PLAYER; i++)
    {
        if (talaGameLogic->players[i]->gold < 3000)
        {
            talaGameLogic->players[i]->renewUser();
            board->updateUserInfo(i);
            board->effectRenew(i);
        }
    }
}
void TalaGameLogic::autoChangeTurnFirstState() {
    CmdReceivedChangeTurn cmd;
    cmd.chair      = talaGameLogic->idWin;
    cmd.canGetCard = false;
    cmd.time       = 20;
    talaGameLogic->onReceiveChangeTurn(cmd);
}
void TalaGameLogic::autoGetCardState() {
    talaGameLogic->autoGetCard();
}
void TalaGameLogic::autoThrowCardState() {
    talaGameLogic->autoThrowCard();
}
void TalaGameLogic::autoShowPhomState() {
    talaGameLogic->autoShowPhom();
}
void TalaGameLogic::autoSendCardState() {
    talaGameLogic->onSendCard();
}
void TalaGameLogic::autoNotifyUState() {
    talaGameLogic->autoNotifyU();
}
void TalaGameLogic::autoEndGameState() {
    CmdReceivedEndMatch cmd;
    talaGameLogic->onReceiveEndMatch(cmd);
}
void TalaGameLogic::autoRewardFailState() {
    string reason = LocalizedString::to("NOT_FINISH_REWARD");
    sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {

    });
    JNIUtils::sendEvent("get_reward_fail", "1");
}
void TalaGameLogic::autoRewardSuccessState() {
    string reason = LocalizedString::to("RECEIVE_NUM");
    reason        = StringUtility::replaceAll(reason, "@gold", "30.000");
    sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {
        TalaGameLogic::getInstance()->players[0]->setGold(30000);
        TalaScene* gui = (TalaScene*)SceneMgr::getInstance()->getMainLayer();
        if (gui)
            gui->updateUserInfo(0);
    });
    JNIUtils::sendEvent("get_reward_success", "1");
}

/*****************************  Native Callback method  *****************************/
// can than, code native da bi xoa
