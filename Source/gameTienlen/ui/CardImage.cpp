#include "CardImage.h"
#include "core/utils/StringUtility.h"
#include "app/GameMgr.h"

CardImage::CardImage(void)
{
}


CardImage::~CardImage(void)
{
}

CardImage::CardImage( int id )
{
	this->id = id;
	string s = getResource();
	initWithFile(s.c_str());
}


void CardImage::setIdCard(int id)
{
	this->id = id;
	string s = getResource();
	setTexture(s.c_str());
}

string CardImage::getResource()
{
	if(id > 52)
		return "";

	std::string s;
	if (id == 52)
	{
		s = "cards/labai_52.png";
			return "cards/labai_52.png";
		
	}
	else
	{
		int convertId;
		if (id < 48)
			convertId = id + 4;
		else if (id >= 48) {
			convertId = id - 48;
		}
		s = "cards/labai_%id.png";
			s = "cards/labai_%id.png";
		
		s = StringUtility::replaceAll(s, "%id", convertId);
	}	
	return s;
}

void CardImage::setDark( bool isDark )
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

float CardImage::getRealWidth()
{
	return getContentSize().width * getScale();
}

float CardImage::getRealHeight()
{
	return getContentSize().height * getScale();
}
