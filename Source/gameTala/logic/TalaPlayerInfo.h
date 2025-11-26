#ifndef TalaPlayerInfo_h__
#define TalaPlayerInfo_h__

#include <string>
#include <vector>
#include "axmol.h"
using namespace std;

class TalaPlayerInfo
{
public:
	enum PlayerStatus {
		STATUS_NONE = 0,
		STATUS_PLAYING = 1,
		STATUS_VIEWING = 4
	};
	enum PlayerState {
		STATE_NONE = -1,
		STATE_BOCBAI = 1,
		STATE_DANHBAI = 2,
		STATE_HABAI = 3,
		STATE_GUIBAI = 4
	};

public:
	//general info
	long long uID;
	long long gold;
	string avatar;
	string displayName;
	int level;
	long long exp;
	int winCount;
	int lostCount;
	char vip;
	string ip;

	//game info
	char status;
	char chair;
	char serverChair;
	char state;
	vector<char> handOnCards;
	vector<char> selectedCards;
	vector<char> eatenCards;
	vector<char> throwCards;
	vector<vector<char>> listPhom;
	bool isEnd;
	bool isMom;
	char rank;
	int idAvatar;
    int score;
	
public:
	TalaPlayerInfo(char chair);
	TalaPlayerInfo();
	~TalaPlayerInfo();

public:
	bool isBot();
	void setAvatar(int idAvatar);
	void setGold(double gold);
	void setWinCount(int winCount);
	void setLostCount(int lostCount);
	std::string getAvatarLevel();
	float getPercentLevel();
	int getLevel();
	void renewUser();
};
#endif // TalaPlayerInfo_h__
