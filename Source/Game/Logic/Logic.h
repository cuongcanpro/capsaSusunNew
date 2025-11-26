#pragma once
#ifndef Logic_h__
#define Logic_h__

#include "axmol.h";
using namespace ax;
class Logic
{
public:
	Logic(void);
	~Logic(void);

	static float getDistance2Point(float x1, float y1, float x2, float y2);
	static float getDistance(float x0, float y0, float x1, float y1, float x2, float y2); 
	static bool inDistance(float x0, float x1, float x2, float d);
	static bool detectHit(float x0, float y0, float d0, float x1, float y1, float x2, float y2, float d1);
	static bool detectHitCircle(float x0, float y0, float d0, float x1, float y1, float d1);
	static bool validCoordinate(int row, int column);
	static Color4B getColorColumn(int column);
};
#endif // Logic_h__

