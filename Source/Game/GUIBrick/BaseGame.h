#pragma once
#ifndef BaseGame_h__
#define BaseGame_h__
#include "Engine/GlobalVar.h"
#include "../GameClient.h"
class BaseGame
{
public:
	BaseGame(void);
	~BaseGame(void);
	void actEnd();
	void changeEnd();
	void endGame();
	virtual void newGame();
	virtual void show();
	virtual void changeData();
	virtual void update();
	

	float countTime;
	int countEnd;
	float countTimeEnd;
	float frameEnd;
	int dataEnd[NUM_HEIGHT][NUM_WIDTH];
	int countTop, countBottom, countRight, countLeft;
	float width, height;

	int stateEnd;
	int index;
	bool isEnd;
	bool music;
	bool isSplash;
	bool isLevel;

	virtual void onButtonLeft();
	virtual void onButtonRight();
	virtual void onButtonUp();
	virtual void onButtonDown();
	virtual void onButtonRotate();

};
#endif // BaseGame_h__

