#include "TalaPlayerInfo.h"
#include "TalaGameLogic.h"
#include "TalaGameRule.h"
#include "app/GameMgr.h"
#include "core/gui/SceneMgr.h"
#include "common/NewLevelGUI.h"

TalaPlayerInfo::TalaPlayerInfo(char chair)
{
	this->chair = chair;
	serverChair = -1;
	status = 0;
    idAvatar    = -1;
    winCount    = 0;
}

TalaPlayerInfo::TalaPlayerInfo()
{
}

TalaPlayerInfo::~TalaPlayerInfo()
{
}

bool TalaPlayerInfo::isBot() {
	return displayName.length() >= 4 && displayName.substr(0, 4) == "bot_"
		&& uID >= 1000000000;
}

void TalaPlayerInfo::setAvatar(int _idAvatar)
{
	idAvatar = _idAvatar;
	gameMgr->idAvatarTala = _idAvatar;
	UserDefault::getInstance()->setIntegerForKey("idAvatarTala", _idAvatar);
	UserDefault::getInstance()->flush();
}

void TalaPlayerInfo::setGold(double _gold)
{
	gold = _gold;
	if (gold < 0) {
		gold = 0;
	}
	if (chair == 0) {
		UserDefault::getInstance()->setIntegerForKey("myGoldTala", gold);
		UserDefault::getInstance()->flush();
		gameMgr->goldTala = gold;
	}
}

void TalaPlayerInfo::setWinCount(int _winCount)
{
	int oldLevel = getLevel();
	winCount = _winCount;
	if (chair == 0) {
		UserDefault::getInstance()->setIntegerForKey("winCountTala", winCount);
		UserDefault::getInstance()->flush();
		int newLevel = getLevel();
		if (oldLevel != newLevel) {
			BaseLayer* layer = sceneMgr->openGUI(NewLevelGUI::className, NewLevelGUI::ZODER, NewLevelGUI::TAG);
			NewLevelGUI *gui = dynamic_cast<NewLevelGUI*> (layer);
			gui->showInfo(TypeGame::TA_LA);
		}
		gameMgr->winCountTala = winCount;
	}
}

void TalaPlayerInfo::setLostCount(int _lostCount)
{
	lostCount = _lostCount;
	if (chair == 0) {
		UserDefault::getInstance()->setIntegerForKey("lostCountTala", lostCount);
		UserDefault::getInstance()->flush();
	}
	gameMgr->lostCountTala = lostCount;
}

std::string TalaPlayerInfo::getAvatarLevel()
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

float TalaPlayerInfo::getPercentLevel()
{
	//if (true)
	//	return 0;
	int level = getLevel();
	int current = pow(2, level) * 5;
	if (level == 0) {
		current = 0;
	}
	int target = pow(2, level + 1) * 5;
	return (winCount - current) * 1.0f / (target - current) * 100;
}

int TalaPlayerInfo::getLevel()
{
	/*if (true)
		return WinCount();*/
	int level = winCount / 5;
	level = (int)log2(level);
	if (level < 0)
		level = 0; 
	return level;
}
void TalaPlayerInfo::renewUser()
{
	displayName = "guest" + std::to_string(floor(AXRANDOM_0_1() * 1000));
    gold        = floor(AXRANDOM_0_1() * 15000 + 30000);
    winCount    = floor(gameMgr->winCountTala * (1.2 - AXRANDOM_0_1() * 0.8));
}
