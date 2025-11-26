#ifndef UserInfo_h__
#define UserInfo_h__

#include <string>

class UserInfo {
public:
	std::string avatar;
	std::string displayName;
	std::string zName;
	std::string name;

	long long bean;
	long long coin;
	long long diamond;

	int levelScore;
	int winCount;
	int lostCount;
	int playCount;
	int star;
	long long uID;
	std::string openID;
	int maxEatPot;
	int preferredBet;
	int amountFriend;
	long long maxWinGold;
	long long exp;
	int level;
public:
	UserInfo();
	~UserInfo();

public:

	std::string getDisplayName(int nLength = -1);
	std::string getUserName();
	std::string getOpenID();
	long long getUserID();
	std::string getAvatar();
	long long getGold();
	long long getBean();

	long long getCoin();
	void setCoin(long long coin);

	long long getDiamond();
	int getLevel();
	int getWinCount();
	int getLoseCount();
	int getPlayCount();
	float getWinRate();
	int getMaxEatPot();
	int getPreferredBet();
	int getAmountFriend();
	long long getMaxWinGold();

	int getLevelScore();
	long long getEXP();
	void setLevel(int level);
	void setLevelScore(long long levelScore);
	
	
};

#endif // UserInfo_h__
