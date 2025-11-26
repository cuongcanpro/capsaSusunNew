#include "UserInfo.h"
#include <string>

UserInfo::UserInfo()
{

}

UserInfo::~UserInfo()
{

}


std::string UserInfo::getDisplayName(int nLength)
{
	if (nLength < 0) return displayName;
	if (nLength > displayName.length()) {
		return displayName.substr(0, nLength - 2) + "...";
	}
	return displayName;
}

std::string UserInfo::getUserName()
{
	return zName;
}

std::string UserInfo::getOpenID()
{
	return openID;
}

long long UserInfo::getUserID()
{
	return uID;
}

std::string UserInfo::getAvatar()
{
	return avatar;
}

long long UserInfo::getGold()
{
	return bean;
}

long long UserInfo::getBean()
{
	return bean;
}

long long UserInfo::getCoin()
{
	return coin;
}

void UserInfo::setCoin(long long value) {
	coin = value;
}

long long UserInfo::getDiamond()
{
	return diamond;
}

int UserInfo::getLevel()
{
	return level;
}

int UserInfo::getWinCount()
{
	return winCount;
}

int UserInfo::getLoseCount()
{
	return lostCount;
}

int UserInfo::getPlayCount() {
	return playCount;
}

float UserInfo::getWinRate() {
	if (playCount == 0) return 0;
	return winCount * 100 / playCount;
}

int UserInfo::getMaxEatPot() {
	return maxEatPot;
}

int UserInfo::getPreferredBet() {
	return preferredBet;
}

int UserInfo::getAmountFriend() {
	return amountFriend;
}

long long UserInfo::getMaxWinGold() {
	return maxWinGold;
}

int UserInfo::getLevelScore() {
	return levelScore;
}

long long UserInfo::getEXP() {
	return exp;
}

void UserInfo::setLevel(int level)
{
	this->level = level;
}

void UserInfo::setLevelScore(long long levelScore)
{
	this->levelScore = levelScore;
}
