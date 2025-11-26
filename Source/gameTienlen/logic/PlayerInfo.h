#ifndef PlayerInfo_h__
#define PlayerInfo_h__
#include <string>
#include "gameTienlen/logic/gamePlay/TienlenGamePlayer.h"
#include "gameTienlen/logic/gamePlay/TienlenPlayerCard.h"
#include "core/gui/SceneMgr.h"
#include "app/GameMgr.h"
#include "common/NewLevelGUI.h"
using namespace std;
enum PlayerStatus {
	PLAYER_VIEWING = 4,
	PLAYER_NONE = 0,
	PLAYER_PLAY = 1
};

class PlayerInfo
{
private:
	long long uID;
	long long gold;
	string avatar;
	string displayName;
	int exp;
	int winCount;
	int lostCount;
	int status;
	char chair;
	char vip;
	int numCard;
	TienlenGamePlayer* game;
	TienlenPlayerCard* playerCard;
	TienlenGroupCard* groupCard;
	char typeSuddenWin;
	bool canThrowCard;
	char rank;
	int level;
	int idAvatar;
	
public:
	PlayerInfo(long long uID, long long gold, string avatar, string displayName, int exp, int winCount, int lostCount, int status, char chair, char vip);
	PlayerInfo(char chair);
	~PlayerInfo();
	vector <int> arrayCard;
	int NumCard() const { return numCard; }
	void NumCard(int val) { numCard = val; }
	
	TienlenGamePlayer* Game() const { return game; }
	void Game(TienlenGamePlayer* val) { game = val; }
	bool CanThrowCard() const { return canThrowCard; }
	void CanThrowCard(bool val) { canThrowCard = val; }
	char Rank() const { return rank; }
	void Rank(char val) { rank = val; }
	TienlenPlayerCard* PlayerCard() const { return playerCard; }
	void PlayerCard(TienlenPlayerCard* val) { playerCard = val; }
	int Level() const { return level; }
	void Level(int val) { level = val; }
	int IdAvatar() const { return idAvatar; }
	void IdAvatar(int val) {
		idAvatar = val;
		gameMgr->idAvatar = idAvatar;
		UserDefault::getInstance()->setIntegerForKey("idAvatar", idAvatar);
		UserDefault::getInstance()->flush();
	}
public:
	long long ID() const { return uID; }
	void ID(long long val) { uID = val; }
	long long Gold() const { return gold; }
	void Gold(long long val) {
		gold = val;
		if (gold < 0) {
			gold = 0;
		}
		if (chair == 0) {
			UserDefault::getInstance()->setIntegerForKey("myGold", gold);
			UserDefault::getInstance()->flush();
			gameMgr->gold = gold;
		}
	}
	std::string Avatar() const { return avatar; }
	void Avatar(std::string val) { avatar = val; }
	std::string DisplayName() const { return displayName; }
	void DisplayName(std::string val) { displayName = val; }
	int Exp() const { return exp; }
	void Exp(int val) { exp = val; }
	int WinCount() const { return winCount; }
	void WinCount(int val) {
		int oldLevel = getLevel();
		winCount = val;
		if (chair == 0) {
			UserDefault::getInstance()->setIntegerForKey("winCount", winCount);
			UserDefault::getInstance()->flush();
			int newLevel = getLevel();
			if (oldLevel != newLevel) {
				BaseLayer* layer = sceneMgr->openGUI(NewLevelGUI::className, NewLevelGUI::ZODER, NewLevelGUI::TAG);
				NewLevelGUI *gui = dynamic_cast<NewLevelGUI*> (layer);
				gui->showInfo(TypeGame::TIEN_LEN);
			}
			gameMgr->winCount = winCount;
		}
	}
	int LostCount() const { return lostCount; }
	void LostCount(int val) {
		lostCount = val;
		if (chair == 0) {
			UserDefault::getInstance()->setIntegerForKey("lostCount", lostCount);
			UserDefault::getInstance()->flush();
		}
		gameMgr->lostCount = lostCount;
	}
	int Status() const { return status; }
	void Status(int val) { status = val; }
	char Chair() const { return chair; }
	void Chair(char val) { chair = val; }
	char Vip() const { return vip; }
	void Vip(char val) { vip = val; }

	void newGame();
	bool isPlaying();
	bool isViewing();
	void setArrayCard(vector<char> arrayId);
	void setArrayCard(vector <int> arrayId);
	bool haveCard(char id);
	void removeCard(char id);
	void setSuddenWin(char typeSuddenWin);
	void setSuddenWinCard();
	void setEndCard(vector<char> arrayId);
	bool isSuddenWin();
	bool checkCanPlayWithoutTurn(TienlenGroupCard* lastCard);
	bool checkCanThrowCard(TienlenGroupCard* lastCard, vector <int>& arraySelect);
	void sortCard(bool isSortNormal);
	vector<int> checkAutoCard(TienlenGroupCard* lastCard, TienlenGroupCard* groupCard);
	bool canPlay(TienlenGroupCard* lastCard);
	void printPlayerCard();
	void renewUser();
	std::string getAvatarLevel();
	float getPercentLevel();
	int getLevel();
	vector<char> getAutoPlayCard(TienlenGroupCard* lastCard, int minCard, int maxCard, int nextCard);

	bool isPass;
};
#endif // PlayerInfo_h__
