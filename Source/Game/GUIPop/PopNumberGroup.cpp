#include "PopNumberGroup.h"
#include <cmath>  
#include <string>
#include <Game/Utility/GameUtility.h>
using namespace ax;
using namespace ax::ui;
PopNumberGroup::PopNumberGroup(void)
{
}

PopNumberGroup::PopNumberGroup(long money)
{
	
}

void PopNumberGroup::setMoney(double money)
{
	removeAllChildren();
	float width  = 0;
	float pad;
	float height = 0;
	float centerHeight = 0;
	std::string resource = "";
	if (money < 0) {
		resource = "bosothua/tru.png";
	}
	else {
		resource = "bosothang/cong.png";
	}
	//Sprite* signal = Sprite::create(resource.c_str());
	//this->addChild(signal);

	pad = 2;
	//width = width + signal->getContentSize().width;

	std::string moneyString = GameUtility::toString(money);

	const char * arrayChar = moneyString.c_str();
	int size = strlen(moneyString.c_str());
	int i;

	for (i = 0; i < size; i++)
	{

		if (arrayChar[i] != ',' && arrayChar[i] != '.')
		{
			std::string content = "number_";
			content.append(arrayChar, i, 1);
			content.append(".png");
			Sprite* image = Sprite::createWithSpriteFrameName(content.c_str());
			this->addChild(image);
			image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height / 2);
			width = width + image->getContentSize().width + pad;
			height = image->getContentSize().height;
		}
		else
		{
			if (money < 0) {
				resource = "bosothua/dot.png";
			}
			else {
				resource = "bosothang/dot.png";
			}
			Sprite *image = Sprite::create(resource.c_str());
			this->addChild(image);
			image->setPosition(width + pad + image->getContentSize().width / 2, image->getContentSize().height * 0.6f);
			width = width + image->getContentSize().height + pad;
		}
	}
	
	setContentSize(Size(width, height));
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

PopNumberGroup::~PopNumberGroup(void)
{
}
