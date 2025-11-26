#ifndef BinhPlayerInfo_h__
#define BinhPlayerInfo_h__
#include <string>
#include "gamePlay/MaubinhPlayerCard.h"
#include "TypeGameData.h"
#include "UserInfo.h"
#include "core/gui/SceneMgr.h"
#include "app/GameMgr.h"
#include "common/NewLevelGUI.h"
#include "axmol.h"
using namespace std;

enum BinhPlayerStatus {
	BINH_PLAYER_VIEWING = 5,
	BINH_PLAYER_NONE = 0,
	BINH_PLAYER_PLAY = 2
};
class BinhGameLogic;

class BinhPlayerInfo
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
	int level;
	bool isCompareBai;
	bool isMauBinh;
	bool isBinhLung;
	bool isArranging;
	bool waitBaoBinh;
	int idAvatar;
	
	SapBaiType sapType;
	MaubinhPlayerCard* playerCard;
public:
	
	BinhPlayerInfo(long long uID, long long gold, string avatar, string displayName, int exp, int winCount, int lostCount, int status, char chair, char vip);
	BinhPlayerInfo(char chair);
	~BinhPlayerInfo();
	vector <int> arrayCard;
	int NumCard() const { return numCard; }
	void NumCard(int val) { numCard = val; }
	int Level() const { return level; }
	void Level(int val) { level = val; }
	bool IsCompareBai() const { return isCompareBai; }
	void IsCompareBai(bool val) { isCompareBai = val; }
	MaubinhPlayerCard* PlayerCard() const { return playerCard; }
	void PlayerCard(MaubinhPlayerCard* val) { playerCard = val; }
	bool IsMauBinh() const { return isMauBinh; }
	void IsMauBinh(bool val) { isMauBinh = val; }
	bool IsBinhLung() const { return isBinhLung; }
	void IsBinhLung(bool val) { isBinhLung = val; }
	SapBaiType SapType() const { return sapType; }
	void SapType(SapBaiType val) { sapType = val; }
	bool IsArranging() const { return isArranging; }
	void IsArranging(bool val) { isArranging = val; }
	bool WaitBaoBinh() const { return waitBaoBinh; }
	void WaitBaoBinh(bool val) { waitBaoBinh = val; }
	int IdAvatar() const { return idAvatar; }
	void IdAvatar(int val) { 
		idAvatar = val; 
		UserDefault::getInstance()->setIntegerForKey("idAvatarBinh", idAvatar);
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
			UserDefault::getInstance()->setIntegerForKey("myGoldBinh", gold);
			UserDefault::getInstance()->flush();
			gameMgr->goldBinh = gold;
		}
	}
	std::string Avatar() const { return avatar; }
	void Avatar(std::string val) { avatar = val; }
	std::string DisplayName() const { return displayName; }
	void DisplayName(std::string val) { displayName = val; }
	int Exp() const { return exp; }
	void Exp(int val) { exp = val; }
	int WinCount() const {
		return winCount; 
	}
	void WinCount(int val) {
		int oldLevel = getLevel();
		winCount = val; 
		if (chair == 0) {
			UserDefault::getInstance()->setIntegerForKey("winCountBinh", winCount);
			UserDefault::getInstance()->flush();
			int newLevel = getLevel();
			if (oldLevel != newLevel) {
				BaseLayer* layer = sceneMgr->openGUI(NewLevelGUI::className, NewLevelGUI::ZODER, NewLevelGUI::TAG);
				NewLevelGUI *gui = dynamic_cast<NewLevelGUI*> (layer);
				gui->showInfo(TypeGame::BINH);
			}
			gameMgr->winCountBinh = winCount;
		}
	}
	int LostCount() const { return lostCount; }
	void LostCount(int val) {
		lostCount = val;
		if (chair == 0) {
			UserDefault::getInstance()->setIntegerForKey("lostCountBinh", lostCount);
			UserDefault::getInstance()->flush();
			gameMgr->lostCountBinh = lostCount;
		}
	}
	int Status() const { return status; }
	void Status(int val) { status = val; }
	char Chair() const { return chair; }
	void Chair(char val) { chair = val; }
	char Vip() const { return vip; }
	void Vip(char val) { vip = val; }

	void newGame();
	void resetState();
	bool isPlaying();
	bool isViewing();
	void setArrayCard(vector<char> arrayId);
	void setArrayCard(vector <int> arrayId);
	void setArrayCardInClient(vector <int> arrayId);

	bool haveCard(char id);
	void setEndCard(vector<char> arrayId);
	void sortCard(bool isSortNormal);
	void printPlayerCard();
	void checkMauBinh(bool isMauBinh);
	void checkBinhLung();
	int getNumAt();
	UserInfo* getUserInfo(); // lay ra thong tin hien thi tren GUI Profile
	void renewUser();
	std::string getAvatarLevel();
	float getPercentLevel();
	int getLevel();

};
#endif // PlayerInfo_h__
