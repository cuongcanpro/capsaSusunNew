#include "BubbleText.h"


BubbleText::BubbleText()
{
	bg = ui::Scale9Sprite::create("GuiGame/bubble/bgDialog.png");
	this->addChild(bg);
// 	
// 	bg = CCSprite::create("480_800/bubble/bgDark.png");
// 	this->addChild(bg);

//	CCScale9Sprite *bgLogin = CCScale9Sprite::create("480_800/bgClockGame.png");
	//bgLogin->setContentSize(ccp(size.width * 0.96f, heightInput * 5));

	text = ui::Text::create("20", "fonts/tahomabd.ttf", 40);
	//text->setAnchorPoint(ccp(0.5f, 0.75f));
	this->addChild(text);
	setCascadeOpacityEnabled(true);
}


BubbleText::~BubbleText()
{

}

void BubbleText::setText(const char* s)
{
	text->setPosition(Vec2(0, 0));
	text->setString(s);
	float scale = (text->getContentSize().width + 20) / bg->getContentSize().width;
	bg->setScaleX(scale);
	scale = (text->getContentSize().height + 10) / bg->getContentSize().height;
	bg->setScaleY(scale);
	setContentSize(Size(bg->getContentSize().width * bg->getScaleX(), bg->getContentSize().height * bg->getScaleY()));
}

