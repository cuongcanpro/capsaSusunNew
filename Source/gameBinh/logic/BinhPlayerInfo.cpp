#include "BinhPlayerInfo.h"
#include "BinhGameLogic.h"
#include "Game/Utility/JNIUtils.h"

BinhPlayerInfo::BinhPlayerInfo(long long uID, long long gold, string avatar, string displayName, int exp, int winCount, int lostCount, int status, char chair, char vip)
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
	PlayerCard(new MaubinhPlayerCard());
}

BinhPlayerInfo::BinhPlayerInfo(char chair)
{
	this->avatar = "Common/defaultavatar.png";
    this->status = BinhPlayerStatus::BINH_PLAYER_PLAY;
    this->vip = 0;
	this->gold = AXRANDOM_0_1() * 15000 + 15000;
	this->displayName = "Player " + to_string((int)(AXRANDOM_0_1() * 100));
    idAvatar          = -1;
	if (chair == 0) {
		this->gold = gameMgr->goldBinh;
		this->displayName = "You";
		this->winCount = gameMgr->winCountBinh;
		int level = getLevel();
		int currentIdAvatar = level;
		if (currentIdAvatar > 19)
			currentIdAvatar = 19;
		JNIUtils::sendEvent(("level_" + to_string(level)).c_str(), to_string(winCount).c_str());
		this->idAvatar = UserDefault::getInstance()->getIntegerForKey("idAvatarBinh", currentIdAvatar);

		this->lostCount = gameMgr->lostCountBinh;
	}
    else
    {
        winCount = floor(gameMgr->winCountBinh * (1.2 - AXRANDOM_0_1() * 0.8));
        winCount = winCount < 0 ? 0 : winCount;
    }
	
	Chair(chair);
	PlayerCard(new MaubinhPlayerCard());
}

void BinhPlayerInfo::newGame()
{
	WaitBaoBinh(false);
	NumCard(13);
	arrayCard.clear();
	if (status == BinhPlayerStatus::BINH_PLAYER_VIEWING)
		status = BinhPlayerStatus::BINH_PLAYER_PLAY;
	resetState();
}

void BinhPlayerInfo::resetState()
{
	IsArranging(true);
	IsBinhLung(false);
	IsMauBinh(false);
	IsCompareBai(false);
}

bool BinhPlayerInfo::isPlaying()
{
	if (status != BinhPlayerStatus::BINH_PLAYER_NONE && status != BinhPlayerStatus::BINH_PLAYER_VIEWING) {
		return true;
	}
	return false;
}

bool BinhPlayerInfo::isViewing()
{
	return status == BinhPlayerStatus::BINH_PLAYER_VIEWING;
}

void BinhPlayerInfo::setArrayCard(vector<char> arrayId)
{
	arrayCard.clear();
	for (int i = 0; i < arrayId.size(); i++) {
		arrayCard.push_back(arrayId[i]);
	}
	PlayerCard()->Clear();
	PlayerCard()->setArrayCard(arrayCard);
	PlayerCard()->SapXepTruocSoBai();
}

void BinhPlayerInfo::setArrayCard(vector <int> arrayId)
{
	vector <int> arrayCard1;
	arrayCard = arrayId;
	PlayerCard()->Clear();
	PlayerCard()->setArrayCard(arrayId);
	PlayerCard()->SapXepTruocSoBai();
	
}

// set card cua User qua viec xep bai duoi Client, ko phai tu Server
void BinhPlayerInfo::setArrayCardInClient(vector <int> arrayId)
{
	vector <int> arrayCard1;
	for (int i = 0; i < arrayId.size(); i++) {
		arrayCard1.push_back(arrayId[NUM_CARD - 1 - i]);
	}
	setArrayCard(arrayCard1);
}

bool BinhPlayerInfo::haveCard(char id)
{
	for (int i = 0; i < arrayCard.size(); i++) {
		if (arrayCard.at(i) == id)
			return true;
	}
	return false;
}

// goi end card se den sau goi suddenWin, sau khi nhan duoc End card, xet bo bai tao nen suddenWin
void BinhPlayerInfo::setEndCard(vector<char> arrayId)
{
	setArrayCard(arrayId);
}

void BinhPlayerInfo::sortCard(bool isSortNormal)
{
	
}

void BinhPlayerInfo::printPlayerCard()
{
	
}

void BinhPlayerInfo::checkMauBinh(bool isMauBinh)
{
	int cardKind = PlayerCard()->GetPlayerCardsKind(BinhGameLogic::getInstance()->isTinhAt());
	if (isMauBinh) {
		if (BinhGameLogic::getInstance()->isMauBinh(cardKind)) {
			IsMauBinh(true);
			IsCompareBai(true);
		}
		else {
			IsMauBinh(false);
		}
	}
	else {
		if (cardKind == EM_BINHLUNG) {
			IsBinhLung(true);
			IsCompareBai(true);
		}
		else {
			IsBinhLung(false);
			IsCompareBai(false);
		}
	}
}

void BinhPlayerInfo::checkBinhLung()
{
	int cardKind = PlayerCard()->GetPlayerCardsKind(BinhGameLogic::getInstance()->isTinhAt());
	if (cardKind == EM_BINHLUNG) {
		IsBinhLung(true);
	}
}

int BinhPlayerInfo::getNumAt()
{
	int count = 0;
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i] >= 48) {
			count++;
		}
	}
	return count;
}

UserInfo* BinhPlayerInfo::getUserInfo()
{
	UserInfo* info = new UserInfo();
	info->zName = displayName;
	info->avatar = avatar;
	info->displayName = displayName;
	info->bean = gold;
	info->levelScore = exp;
	info->exp = exp;
	info->winCount = winCount;
	info->lostCount = lostCount;
	info->uID = uID;
	info->level = level;
	return info;
}

void BinhPlayerInfo::renewUser()
{
	displayName = "guest" + std::to_string(floor(AXRANDOM_0_1() * 1000));
	gold = floor(AXRANDOM_0_1() * 15000 + 15000);
    winCount    = floor(gameMgr->winCountBinh * (1.2 - AXRANDOM_0_1() * 0.8));
    winCount    = winCount < 0 ? 0 : winCount;
}

std::string BinhPlayerInfo::getAvatarLevel()
{
	int level = getLevel();
	if (level > 19)
		level = 19;
	//idAvatar = 16;
    if (idAvatar >= 0)
	    return "avatar/level" + std::to_string(idAvatar) + ".png";
    else
        return "avatar/level" + std::to_string(level) + ".png";
}

float BinhPlayerInfo::getPercentLevel()
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

int BinhPlayerInfo::getLevel()
{
	/*if (true)
		return WinCount();*/
	int level = WinCount() / 5;
	level = (int)log2(level);
	if (level < 0)
		level = 0;
	return level;
}

