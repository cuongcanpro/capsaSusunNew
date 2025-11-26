#include "Card.h"
#include "../data/TalaGameConstant.h"

Card::Card(int id)
{
	this->id = (id >= 0 && id < NUM_TYPE * NUM_SHAPE) ? id : -1;
	eaten = false;
}

Card::~Card()
{
}

char Card::getId()
{
	return id;
}

bool Card::isValid()
{
	return id != -1;
}

char Card::getType()
{
	return id / NUM_SHAPE;
}

char Card::getShape()
{
	return id % NUM_SHAPE;
}

bool Card::isEaten()
{
	return eaten;
}

void Card::setEaten(bool eaten)
{
	this->eaten = eaten;
}
