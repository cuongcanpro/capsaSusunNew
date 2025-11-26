#pragma once
#ifndef BallCircle_h__
#define BallCircle_h__
#include "Engine/GUI/GameImage.h"

class BallCircle
{
public:
	BallCircle(void);
	~BallCircle(void);

	float countTime;
    GameImage* ball;
    GameImage* bar;
	void act(float delta);
	void finishGame();
	void setPosition(float x, float y);
};
#endif // BallCircle_h__

