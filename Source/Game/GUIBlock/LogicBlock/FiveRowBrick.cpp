#include "FiveRowBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


FiveRowBrick::FiveRowBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(1, 0));
	data.push_back(new PointGame(2, 0));
	data.push_back(new PointGame(3, 0));
	data.push_back(new PointGame(4, 0));
	idBlock = 3;
	initCell();
}


FiveRowBrick::~FiveRowBrick(void)
{
}

int FiveRowBrick::getWidth()
{
	return 5;
}

int FiveRowBrick::getHeight()
{
	return 1;
}

