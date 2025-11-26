#include "WayPika.h"


WayPika::WayPika()
{
	pointSameRow = -1;
    pointSameColumn = -1;
	previousPointRow = new PointGame();
	previousPointColumn = new PointGame();
}


WayPika::~WayPika()
{
}

void WayPika::reset()
{
	pointSameRow = -1;
    pointSameColumn = -1;
	specialBrick = false;
	sameRow = false;
	sameColumn = false;
	countBreak = -1;
}
