#include "PlayerInfo.h"
#include "GamePlay/TienlenRule.h"
#include "GamePlay/TienlenGameLogic.h"
#include "GameLogic.h"

PlayerInfo::PlayerInfo(long long uID, long long gold, string avatar, string displayName, int exp, int winCount, int lostCount, int status, char chair, char vip)
{
	this->uID = uID;
	this->gold = gold;
	this->avatar = avatar;
	this->displayName = displayName;
	this->winCount = winCount;
	this->lostCount = lostCount;
	this->status = status;
	this->chair = chair;
	this->vip = vip;

	Game(new TienlenGamePlayer());
	PlayerCard(new TienlenPlayerCard());
	groupCard = new TienlenGroupCard();
	isPass = false;
}

PlayerInfo::PlayerInfo(char chair)
{
	Chair(chair);
	Game(new TienlenGamePlayer());
	PlayerCard(new TienlenPlayerCard());
	groupCard = new TienlenGroupCard();
	isPass = false;

	this->gold = AXRANDOM_0_1() * 15000 + 15000;
	this->displayName = "Player " + to_string((int)(AXRANDOM_0_1() * 100));
        idAvatar          = -1;
	if (chair == 0) {
		this->gold = gameMgr->gold;
		this->displayName = "You";
		this->winCount = gameMgr->winCount;
		int level = getLevel();
		int currentIdAvatar = level;
		if (currentIdAvatar > 19)
			currentIdAvatar = 19;
		//JNIUtils::sendEvent(("level_" + to_string(level)).c_str(), to_string(winCount).c_str());
		this->idAvatar = UserDefault::getInstance()->getIntegerForKey("idAvatar", currentIdAvatar);
		this->lostCount = gameMgr->lostCount;
	}
    else
    {
        winCount = floor(gameMgr->winCount * (1.2 - AXRANDOM_0_1() * 0.8));
        winCount = winCount < 0 ? 0 : winCount;
    }
}

void PlayerInfo::newGame()
{
	isPass = false;
	typeSuddenWin = -1;
	NumCard(13);
	Game(new TienlenGamePlayer());
	arrayCard.clear();
	if (status == PlayerStatus::PLAYER_VIEWING)
		status = PlayerStatus::PLAYER_PLAY;
}

bool PlayerInfo::isPlaying()
{
	if (status != PlayerStatus::PLAYER_NONE && status != PlayerStatus::PLAYER_VIEWING) {
		return true;
	}
	return false;
}

bool PlayerInfo::isViewing()
{
	return status == PlayerStatus::PLAYER_VIEWING;
}

void PlayerInfo::setArrayCard(vector<char> arrayId)
{
	arrayCard.clear();
	for (int i = 0; i < arrayId.size(); i++) {
		arrayCard.push_back(arrayId[i]);
	}
	PlayerCard()->SetCard(arrayCard);
	NumCard(arrayCard.size());
}

void PlayerInfo::setArrayCard(vector <int> arrayId)
{
	arrayCard.clear();
	for (int i = 0; i < arrayId.size(); i++) {
		arrayCard.push_back(arrayId[i]);
	}
	PlayerCard()->SetCard(arrayCard);
}

bool PlayerInfo::haveCard(char id)
{
	for (int i = 0; i < arrayCard.size(); i++) {
		if (arrayCard.at(i) == id)
			return true;
	}
	return false;
}

void PlayerInfo::removeCard(char id)
{
	for (int i = 0; i < arrayCard.size(); i++) {
		if (arrayCard.at(i) == id) {
			arrayCard.erase(arrayCard.begin() + i);
			break;
		}
	}
	PlayerCard()->SetCard(arrayCard);
	
	printPlayerCard();
}

void PlayerInfo::setSuddenWin(char typeSuddenWin)
{
	this->typeSuddenWin = typeSuddenWin;
}

void PlayerInfo::setSuddenWinCard()
{
	groupCard->setCard(arrayCard);
	groupCard->Sort(true);
	switch (typeSuddenWin) {
		case ST_STRAIGHT:
			Game()->CheckStraight(groupCard);
			break;
		case ST_FOUR_2:
			Game()->CheckFour2(groupCard);
			break;
		case ST_FOUR_3:
			Game()->CheckFour3(groupCard);
			break;
		case ST_SIXPAIR:
			Game()->CheckSixPair(groupCard);
			break;
		case ST_BIGGER:
			Game()->CheckBigger(groupCard);
			break;
		case ST_SUPER:
			Game()->CheckSuper(groupCard);
			break;
		case ST_ULTRA:
			Game()->CheckUltra(groupCard);
			break;
		default:
			break;
	}
}

// goi end card se den sau goi suddenWin, sau khi nhan duoc End card, xet bo bai tao nen suddenWin
void PlayerInfo::setEndCard(vector<char> arrayId)
{
	setArrayCard(arrayId);
	if (typeSuddenWin >= 0) {
		setSuddenWinCard();
	}
	else {
		// tim nhung quan card bi thoi
		groupCard->setCard(arrayCard);
		Game()->KiemTraBaiThoi(groupCard);
	}
}

bool PlayerInfo::isSuddenWin()
{
	return typeSuddenWin >= 0;
}

bool PlayerInfo::checkCanPlayWithoutTurn(TienlenGroupCard* lastCard)
{
	if (PlayerCard()->CanPlay(lastCard)) {
		if (PlayerCard()->Has4DoiThong() || PlayerCard()->HasUltra()) {
			return true;
		}
	}
	return false;
}

bool PlayerInfo::checkCanThrowCard(TienlenGroupCard* lastCard, vector <int>& arraySelect)
{
	if (GameLogic::getInstance()->lastThrowId == chair)
		return false;
	TienlenGroupCard* groupSelect = new TienlenGroupCard();
	groupSelect->setCard(arraySelect);
	string s = "";
	for (int i = 0; i < arraySelect.size(); i++) {
		s = s + " " + to_string(arraySelect.at(i));
	}

	//AXLOGD("checkCanThrowCard");
	//printPlayerCard();

	int result = TienlenRule::CheckValidCard(lastCard, groupSelect, PlayerCard());
	if (result == E_NO_ERROR) {
		// kiem tra xem danh van dau tien, phai danh 3 bich
		if (GameLogic::getInstance()->isFirstPlayInSection()) {
			if (!PlayerCard()->Has3Spade()) {
				CanThrowCard(true);
			}
			else {
				int i;
				for (i = 0; i < arraySelect.size(); i++) {
					if (arraySelect.at(i) == 0)
						break;
				}
				if (i == arraySelect.size()) {
					CanThrowCard(false);
				}
				else {
					CanThrowCard(true);
				}
			}
		}
		else {
			CanThrowCard(true);
		}
	}
	else {
		CanThrowCard(false);
	}
	return CanThrowCard();
}

void PlayerInfo::sortCard(bool isSortNormal)
{
	if (isSortNormal) {
		TienlenGameLogic::ScanGroupCardNormal(PlayerCard());
	}
	else {
		TienlenGameLogic::ScanGroupCardAuto(PlayerCard());
	}
	arrayCard = PlayerCard()->getListIdCard();
}

vector<int> PlayerInfo::checkAutoCard(TienlenGroupCard* lastCard, TienlenGroupCard *groupCard)
{
	// khi chay qua ham AutoCard, mang card cua nguoi choi bi thay doi nen tao them PlayerCard moi
	TienlenPlayerCard* pCard = new TienlenPlayerCard();
	pCard->SetCard(PlayerCard()->getListIdCard());
	TienlenGroupCard* takeCard = NULL;
	if (lastCard->GetNumOfCards() == 0) {
		if (groupCard->GetNumOfCards() <= 3) {
			takeCard = PlayerCard()->FirstTurnPlay(lastCard, groupCard, pCard);
		}
	}
	else if (groupCard->GetNumOfCards() == 1) {
		takeCard = PlayerCard()->OnTurnPlay(lastCard, groupCard, pCard);
	}
	delete pCard;
	if (takeCard == NULL)
		return vector <int> ();
	vector<int> result = takeCard->getListId();
	//delete takeCard;
	return takeCard->getListId();
}

bool PlayerInfo::canPlay(TienlenGroupCard* lastCard)
{
	return PlayerCard()->CanPlay(lastCard);
}

void PlayerInfo::printPlayerCard()
{
	vector<int> arr = PlayerCard()->getListIdCard();
	string s = "";
	for (int i = 0; i < arr.size(); i++) {
		s = s + " " + to_string(arr.at(i));
	}
}

void PlayerInfo::renewUser()
{
    displayName = "guest" + std::to_string(floor(AXRANDOM_0_1() * 1000));
    gold        = floor(AXRANDOM_0_1() * 15000 + 15000);
    winCount    = floor(gameMgr->winCount * (1.2 - AXRANDOM_0_1() * 0.8));
    winCount    = winCount < 0 ? 0 : winCount;
}

std::string PlayerInfo::getAvatarLevel()
{
    int level = getLevel();
    if (level > 19)
        level = 19;
    // idAvatar = 16;

    if (idAvatar >= 0)
        return "avatar/level" + std::to_string(idAvatar) + ".png";
    else
        return "avatar/level" + std::to_string(level) + ".png";
}

float PlayerInfo::getPercentLevel()
{
	//if (true)
	//	return 0;
	int level = getLevel();
	int current = pow(2, level) * 5;
	if (level == 0) {
		current = 0;
	}
	int target = pow(2, level + 1) * 5;
	return (WinCount() - current) * 1.0f / (target - current) * 100;
}

int PlayerInfo::getLevel()
{
	/*if (true)
		return WinCount();*/
	int level = WinCount() / 5;
	level = (int)log2(level);
	if (level < 0)
		level = 0;
	
	return level;
}

std::vector<char> PlayerInfo::getAutoPlayCard(TienlenGroupCard* lastCard, int minCard, int maxNumCard, int nextCard)
{
	vector<char> arr;
	vector<int> arr1;
	if (lastCard->GetNumOfCards() == 0) {
		arr1 = PlayerCard()->getAutoPlayCard(minCard, maxNumCard, nextCard);
	}
	else {
		arr1 = PlayerCard()->getAutoResponseCard(lastCard, minCard, nextCard);
	}
	for (int i = 0; i < arr1.size(); i++) {
		arr.push_back(arr1[i]);
	}
	return arr;
}

