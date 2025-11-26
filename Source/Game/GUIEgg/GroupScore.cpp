#include "GroupScore.h"
#include <cmath>  
#include "Engine/Utility/Utility.h"
#include "Engine/Utility/CStringUtils.h"
#include <string>
#include "Game/Utility/GameUtility.h"


GroupScore::GroupScore(void)
{
	setCascadeOpacityEnabled(true);
	setCascadeColorEnabled(true);
}


GroupScore::~GroupScore(void)
{
}

void GroupScore::createNormalScore( int numBall, int numDrop, int mul )
{
	string s1 = GameUtility::toString((numBall + numDrop) * 10);
	const char * arrayChar = s1.c_str();
	int size = strlen(s1.c_str());
	int i;
	float width  = 0;
	float pad = 0;
	float height = 0;
	float centerHeight = 0;

	for(i = 0; i<size; i++)
	{
			Sprite* image = Sprite::create(("GuiGame/Egg/num_" + GameUtility::toString(arrayChar[i] - '0') + ".png").c_str());
			this->addChild(image);
			image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
			width = width + image->getContentSize().width + pad;
			height  = image->getContentSize().height;
	}
	setContentSize(Size(width, height));
	if(mul <= 1)
		return ;

	Sprite* image = Sprite::create("GuiGame/Egg/signalMul.png");
	this->addChild(image);
	image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
	width = width + image->getContentSize().width + pad;
	height  = image->getContentSize().height;

	s1 = GameUtility::toString(mul);
	arrayChar = s1.c_str();
	size = strlen(s1.c_str());
	for(i = 0; i<size; i++)
	{
		Sprite* image = Sprite::create(("GuiGame/Egg/num_" + GameUtility::toString(arrayChar[i] - '0') + ".png").c_str());
		this->addChild(image);
		image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
		width = width + image->getContentSize().width + pad;
		height  = image->getContentSize().height;
	}
	setContentSize(Size(width, height));

}

void GroupScore::createBonusScore( int bonus )
{
	cleanup();
	removeAllChildren();
	string s1 = GameUtility::toString(bonus);
	const char * arrayChar = s1.c_str();
	int size = strlen(s1.c_str());
	int i;
	float width  = 0;
	float pad = 0;
	float height = 0;
	float centerHeight = 0;

	for(i = 0; i<size; i++)
	{
		Sprite* image = Sprite::create(("GuiGame/Egg/num_" + GameUtility::toString(arrayChar[i] - '0') + ".png").c_str());
		this->addChild(image);
		image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
		width = width + image->getContentSize().width + pad;
		height  = image->getContentSize().height;
	}
	setContentSize(Size(width, height));
}

void GroupScore::createNormalBonusScore( int numBall, int numDrop, int mul, int bonus )
{
	cleanup();
	removeAllChildren();
	string s1 = GameUtility::toString((numBall + numDrop) * 10);
	const char * arrayChar = s1.c_str();
	int size = strlen(s1.c_str());
	int i;
	float width  = 0;
	float pad = 0;
	float height = 0;
	float centerHeight = 0;

	for(i = 0; i<size; i++)
	{
		Sprite* image = Sprite::create(("GuiGame/Egg/num_" + GameUtility::toString(arrayChar[i] - '0') + ".png").c_str());
		this->addChild(image);
		image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
		width = width + image->getContentSize().width + pad;
		height  = image->getContentSize().height;
	}
	if(mul > 1)
	{
		Sprite* image = Sprite::create("GuiGame/Egg/signalMul.png");
		this->addChild(image);
		image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
		width = width + image->getContentSize().width + pad;
		height  = image->getContentSize().height;

		s1 = GameUtility::toString(mul);
		arrayChar = s1.c_str();
		size = strlen(s1.c_str());
		for(i = 0; i<size; i++)
		{
			image = Sprite::create(("GuiGame/Egg/num_" + GameUtility::toString(arrayChar[i] - '0') + ".png").c_str());
			this->addChild(image);
			image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
			width = width + image->getContentSize().width + pad;
			height  = image->getContentSize().height;
		}
	}

	if(bonus > 0)
	{

		Sprite* image = Sprite::create("GuiGame/Egg/signalPlus.png");
		this->addChild(image);
		image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
		width = width + image->getContentSize().width + pad;
		height  = image->getContentSize().height;

		s1 = GameUtility::toString(bonus);
		arrayChar = s1.c_str();
		size = strlen(s1.c_str());
		for(i = 0; i<size; i++)
		{
			image = Sprite::create(("GuiGame/Egg/num_" + GameUtility::toString(arrayChar[i] - '0') + ".png").c_str());
			this->addChild(image);
			image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
			width = width + image->getContentSize().width + pad;
			height  = image->getContentSize().height;
		}
	}

	setContentSize(Size(width, height));
}

int GroupScore::getNormalBonusScore( int numBall, int numDrop, int mul, int bonus )
{
	int result = 0;
	if(numDrop <= 1)
		numDrop = 1;
	return (numBall + numDrop)* 10 * mul + bonus;
}
