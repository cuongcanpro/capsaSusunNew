#include "BinhBubbleText.h"


BinhBubbleText::BinhBubbleText()
{
	bg = Scale9Sprite::create("Board/table/bgBubble.png");
	this->addChild(bg);

	text = Text::create("10000", "fonts/tahomabd.ttf", 15);
	text->setTextHorizontalAlignment(TextHAlignment::CENTER);
	text->setTextAreaSize(Size(200, 0));
	//text->ignoreContentAdaptWithSize(true);
	//text->setContentSize(Size(200, 0));
	this->addChild(text);
	setCascadeOpacityEnabled(true);
}


BinhBubbleText::~BinhBubbleText()
{

}

void BinhBubbleText::setText(const char* s)
{
	text->setString(s);
	bg->setContentSize(Size(text->getContentSize().width + 20, text->getContentSize().height + 20));
	setContentSize(Size(bg->getContentSize().width, bg->getContentSize().height));
}

