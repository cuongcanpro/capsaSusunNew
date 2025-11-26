#ifndef _FlyNumber_h__
#define _FlyNumber_h__
#include "axmol.h"
#include "PopObjectNumber.h"
using namespace ax;
using namespace ax::ui;
class FlyNumber : public Node
{
public:

	FlyNumber(void);
	~FlyNumber(void);
    PopObjectNumber* iconNumber;
	Sprite* iconWingLeft;
	Sprite* iconWingRight;
	
	void setNumber(int number);
	void effectFly(Vec2 pos);
};
#endif
