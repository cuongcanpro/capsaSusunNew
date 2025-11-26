#pragma once
#ifndef BallAnimation_h__
#define BallAnimation_h__
#include "Engine/GUI/GameImage.h"
#include "string"
#include "Game/GameClient.h"

class BallAnimation : public GameImage
{
public:
	BallAnimation(void);
	~BallAnimation(void);

	BallAnimation(const char *nameImg, bool frame = false);
	std::string nameImage;
	void update();
	void setState(BallState _state);
	void setImage(const char* nameImg);

	float countTime;
	float frameTime;
	int currentFrame;

	BallState state;

	bool isAct;
	void effectEndGame(float delay);
	void callbackEnd();
};
#endif // BallAnimation_h__

