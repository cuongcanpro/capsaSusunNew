#include "Way.h"


Way::Way(void)
{
	point = -1;
	previousPoint = new PointGame();
}


Way::~Way(void)
{
}
void Way::reset()
{
	point = -1;
	specialBrick = false;
}

