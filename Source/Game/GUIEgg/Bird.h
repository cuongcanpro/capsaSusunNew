#pragma once
#ifndef Bird_h__
#define Bird_h__
#include "Engine/GUI/GameImage.h"

class Bird : public GameImage
{
public:
	Bird(void);
	~Bird(void);

	float vx, vy;
	double degree;

	int countAppear;
	void setDegree(double degree);
	void act(float delta);
	void updatePosition(float delta);
	void checkVisible();
	void newGame();

	float countTime;
	int currentFrame;
	float frameTime;
};
#endif // Bird_h__

