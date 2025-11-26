#include "StorageUtil.h"
#include "axmol.h"

using namespace ax;
StorageUtil::StorageUtil()
{

}

StorageUtil::~StorageUtil()
{

}

std::string StorageUtil::getString(std::string key, std::string defValue /*= ""*/)
{
	std::string val = std::string(UserDefault::getInstance()->getStringForKey(key.c_str(), defValue));
	return val;
}

int StorageUtil::getInt(std::string key, int defValue /*= 0*/)
{
	return UserDefault::getInstance()->getIntegerForKey(key.c_str(), defValue);
}

bool StorageUtil::getBool(std::string key, bool defValue /*= false*/)
{
	return UserDefault::getInstance()->getBoolForKey(key.c_str(), defValue);

}

void StorageUtil::setInt(std::string key, int value)
{
	UserDefault::getInstance()->setIntegerForKey(key.c_str(), value);
	UserDefault::getInstance()->flush();
}

void StorageUtil::setString(std::string key, std::string value)
{
	UserDefault::getInstance()->setStringForKey(key.c_str(), value);
	UserDefault::getInstance()->flush();
}

void StorageUtil::setBool(std::string key, bool value)
{
	UserDefault::getInstance()->setBoolForKey(key.c_str(), value);
	UserDefault::getInstance()->flush();
}

void StorageUtil::clear() 
{
	//std::string path = UserDefault::getInstance()->getXMLFilePath();
	//ax::log("UserDefault %s", path.c_str());
}
