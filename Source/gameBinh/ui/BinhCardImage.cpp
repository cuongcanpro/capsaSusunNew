#include "BinhCardImage.h"
#include "core/utils/StringUtility.h"

BinhCardImage::BinhCardImage(void)
{
}


BinhCardImage::~BinhCardImage(void)
{
}

BinhCardImage::BinhCardImage( int id )
{
	this->id = id;
	string s = getResource();
	initWithFile(s.c_str());
}


void BinhCardImage::setIdCard(int id)
{
	this->id = id;
	string s = getResource();
	setTexture(s.c_str());
}

string BinhCardImage::getResource()
{
	if(id > 52)
		return "";

	std::string s;
	if (id == 52)
		s = "table/Cards/labai_52.png";
	else
	{
		s = "table/Cards/labai_%id.png";
		s = StringUtility::replaceAll(s, "%id", id);
	}	
	return s;
}

void BinhCardImage::setDark( bool isDark )
{
	if(isDark)
	{
		Color3B color = {120, 120, 120};
		setColor(color);
	}
	else
	{
		Color3B color = {255, 255, 255};
		setColor(color);
	}
}

float BinhCardImage::getCardWidth()
{
	return getContentSize().width * getScaleX();
}

float BinhCardImage::getCardHeight()
{
	return getContentSize().height * getScaleY();
}


void BinhCardImage::setPosDefaultY(float pos)
{
	posDefaultY = pos;
}

void BinhCardImage::setPosDefaultX(float pos)
{
	posDefaultX = pos;
}

void BinhCardImage::setDefaultPos()
{
	stopAllActions();
	setPosition(Vec2(posDefaultX, posDefaultY));
}

void BinhCardImage::saveDefaultPos()
{
	setPosDefaultX(getPositionX());
	setPosDefaultY(getPositionY());
}

void BinhCardImage::saveScale()
{
	rootScale = getScale();
}

void BinhCardImage::saveZOrder()
{
	rootZOrder = getLocalZOrder();
}

int BinhCardImage::getRootZOrder()
{
	return rootZOrder;
}

void BinhCardImage::saveInfoCard()
{
	saveDefaultPos();
	saveScale();
	saveZOrder();
}

void BinhCardImage::showCard()
{
	saveIdCard = id;
	setIdCard(52);
	runAction(Sequence::create(
		ScaleTo::create(0.2, 0, getScaleY()),
		CallFuncN::create(AX_CALLBACK_1(BinhCardImage::callbackShowCard, this)),
		NULL
	));
}

void BinhCardImage::callbackShowCard(Node* pSender)
{
	setIdCard(saveIdCard);
	runAction(ScaleTo::create(0.2, rootScale));
}

ax::Vec2 BinhCardImage::getDefaultPos()
{
	return Vec2(posDefaultX, posDefaultY);
}

void BinhCardImage::moveToDefault(float time, float delayTime)
{
	stopAllActions();
	runAction(Sequence::create(
		DelayTime::create(delayTime),
		EaseSineIn::create(MoveTo::create(time, getDefaultPos())),
		CallFuncN::create(AX_CALLBACK_1(BinhCardImage::callbackMoveCard, this)),
		NULL
	));
	runAction(ScaleTo::create(time, rootScale));
}

void BinhCardImage::callbackMoveCard(Node* pSender)
{
	setLocalZOrder(rootZOrder);
}
