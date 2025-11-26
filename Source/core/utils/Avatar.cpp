#include "Avatar.h"



Avatar::Avatar()
{

}

Avatar::~Avatar()
{

}

Avatar* Avatar::create(std::string defaultImg, std::string url /*= ""*/)
{
	Avatar* avatar = new Avatar();
	avatar->init(defaultImg, url);
	avatar->autorelease();
	return avatar;
}

bool Avatar::init(std::string defaultImg, std::string url /*= ""*/)
{
	setCascadeOpacityEnabled(true);

	defaultAvatar = ax::Sprite::create(defaultImg);
	defaultAvatar->setCascadeOpacityEnabled(true);
	addChild(defaultAvatar);

	///avatar = fr::AsyncSprite::create(defaultAvatar->getContentSize(), std::bind(&Avatar::onFinishLoad, this, std::placeholders::_1));
//	addChild(avatar);

	updateAvatar(url);
	return true;
}

void Avatar::updateAvatar(std::string url)
{
	/*if (url.empty())
	{
		return;
	}
	defaultAvatar->setVisible(true);
	avatar->setVisible(false);

	avatar->updatePath(url, getStorePath(url));*/
}

void Avatar::onFinishLoad(bool result)
{
	if (result)
	{
		defaultAvatar->setVisible(false);
	//	avatar->setVisible(true);
	}
	else
	{
		defaultAvatar->setVisible(true);
		//avatar->setVisible(false);
	}
}

std::string Avatar::getStorePath(std::string url)
{
    return "";
	//return StringUtils::format("%s/%s",FileUtils::getInstance()->getWritablePath().c_str(), url.c_str());
}

