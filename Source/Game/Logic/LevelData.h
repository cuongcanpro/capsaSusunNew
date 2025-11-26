#pragma once
class LevelData
{
public:
	LevelData(int score, int time, int numEat, int numRandom, int size);
	~LevelData(void);
	int score;
	int time;
	int numEat;
	int numRandom;
	int size;
};

