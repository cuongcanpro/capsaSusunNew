#pragma once
#include "Game/Logic/PointGame.h"
class Way
{
public:
	Way(void);
	~Way(void);

	int point;
	bool specialBrick;
	PointGame* previousPoint;

	void reset();
};

