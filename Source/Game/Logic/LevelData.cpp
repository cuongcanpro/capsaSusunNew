#include "LevelData.h"


LevelData::LevelData(int score, int time, int numEat, int numRandom, int size)
{
	this->score = score;
	this->time = time;
	this->numEat = numEat;
	this->numRandom = numRandom;
	this->size = size;
}


LevelData::~LevelData(void)
{
}
