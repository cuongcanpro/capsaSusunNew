#pragma once
#include "Game/Logic/PointGame.h"
#ifndef WayPika_h__
#define WayPika_h__

class WayPika
{
public:
	WayPika();
	~WayPika();

	int pointSameRow;
    int pointSameColumn;
	bool specialBrick;
	PointGame* previousPointRow;
	PointGame* previousPointColumn;
	bool sameRow;
	bool sameColumn;
	int countBreak;

	void reset();
};
#endif // WayPika_h__

