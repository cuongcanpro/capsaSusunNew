#pragma once
#ifndef BallMove_h__
#define BallMove_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ui;

class BallMove : public Node
{
public:
    enum StateBall
    {
        MOVE,
        STOP
    };

	BallMove(void);
	~BallMove(void);

	GameImage* ball;

	StateBall state;

	Text* label;
	void act1(float delta);
	bool checkHit();
	void checkMakeNew();
	void setText(int num);
	void setRealWidth(float wIDTH_BALL);
};
#endif // BallMove_h__

