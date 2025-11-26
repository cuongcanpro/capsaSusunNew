#pragma once
#ifndef StickMan_h__
#define StickMan_h__
#include "../../Engine/GUI/GameImage.h"
#include "string"
using namespace std;

class StickMan : public GameImage
{
public:
	StickMan(void);
	~StickMan(void);

	StickMan(const char *nameImg, bool frame = false);
    enum StickManState
    {
        RUN,
        NORMAL,
        KICK
    };
	string nameImage;
	void update();
	void setState(StickManState _state, float _frameTime = 0.03f);
	void setImage(const char* nameImg);

	float countTime;
	float frameTime;
	int currentFrame;

	StickManState state;

	bool isAct;
	float distance;
	float speed;
};
#endif // StickMan_h__

