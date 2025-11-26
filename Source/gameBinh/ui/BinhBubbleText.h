#pragma once
#ifndef BinhBubbleText_h__
#define BinhBubbleText_h__
#include "axmol.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ax::ui;
class BinhBubbleText : public Node
{
public:
	BinhBubbleText();
	~BinhBubbleText();
	Scale9Sprite* bg;
	Text* text;
	void setText(const char* s);
};
#endif // BinhBubbleText_h__

