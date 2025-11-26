#ifndef BubbleText_h__
#define BubbleText_h__

#include "Engine/GUI/GameImage.h"
#include "extensions/axmol-ext.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ax::extension;
class BubbleText : public Node
{
public:
	BubbleText();
	~BubbleText();
	ui::Scale9Sprite* bg;
	ui::Text* text;
	void setText(const char* s);

};
#endif // BubbleText_h__

