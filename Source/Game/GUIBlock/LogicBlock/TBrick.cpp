#include "TBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


TBrick::TBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(1, 0));
	data.push_back(new PointGame(2, 0));
	data.push_back(new PointGame(1, 1));
	idBlock = 9;
	initCell();
}


TBrick::~TBrick(void)
{
}

int TBrick::getWidth()
{
	return 3;
}

int TBrick::getHeight()
{
	return 2;
}


