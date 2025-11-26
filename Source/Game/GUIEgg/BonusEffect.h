#pragma once
#ifndef BonusEffect_h__
#define BonusEffect_h__
#include "Engine/GUI/GameImage.h"
class BonusEffect : public GameImage
{
public:
	BonusEffect(void);
	~BonusEffect(void);
	float rootX, rootY;
	float countTime, maxTime;
	float radius;

	float countTimeBonus;
	float maxTimeBonus;

	float countTimeAppear;
	int idBonus;

	void act(float delta);
	void setIdBonus(int _id);
	int getMul();
	void setImage(const char* url);
};
#endif // BonusEffect_h__

