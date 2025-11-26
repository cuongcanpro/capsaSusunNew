#pragma once
#ifndef Smoke_h__
#define Smoke_h__
#include "../../Engine/GUI/GameImage.h"
#include "string"
using namespace std;

class Smoke : public GameImage
{
public:
	Smoke(void);
	~Smoke(void);

	Smoke(const char *nameImg, bool frame = false);
	string nameImage;
	void update();
	void setImage(const char* nameImg);
	void start();
	float countTime;
	float frameTime;
	int currentFrame;

	bool isAct;
};
#endif // Smoke_h__

