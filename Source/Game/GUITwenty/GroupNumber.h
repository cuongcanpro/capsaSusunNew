#ifndef _GroupNumber_h__
#define _GroupNumber_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ui;
class GroupNumber : public Node
{
public:

	GroupNumber(void);
	~GroupNumber(void);
	GameImage* ball;
	Text* label;
	int number;
	void setNumber(int number);
	void increaseNumber();
	void callback1();
	void callback2();
};
#endif
