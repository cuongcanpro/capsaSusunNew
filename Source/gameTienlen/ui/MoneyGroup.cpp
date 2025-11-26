#include "MoneyGroup.h"
#include <cmath>  
#include <string>
#include "core/utils/StringUtility.h"
using namespace ax;
using namespace ax::ui;
MoneyGroup::MoneyGroup(void)
{
}

MoneyGroup::MoneyGroup(long money)
{
	
}

void MoneyGroup::setMoney(double money)
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
	Sprite* signal = Sprite::create(resource.c_str());
	this->addChild(signal);

	pad = signal->getContentSize().width * 0.1f;
	width = width + signal->getContentSize().width;

	std::string moneyString = StringUtility::pointNumber(abs(money));

	const char * arrayChar = moneyString.c_str();
	int size = strlen(moneyString.c_str());
	int i;

	for (i = 0; i < size; i++)
	{

		if (arrayChar[i] != ',' && arrayChar[i] != '.')
		{
			std::string content = "poker/tru_";
			if (money < 0) {
				content = "bosothua/so";
			}
			else {
				content = "bosothang/so";
			}
			content.append(arrayChar, i, 1);
			content.append(".png");
			Sprite* image = Sprite::create(content.c_str());
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
	signal->setPosition(signal->getContentSize().width / 2, height / 2);
	
	setContentSize(Size(width, height));
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

MoneyGroup::~MoneyGroup(void)
{
}
