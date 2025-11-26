#include "LSortBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


LSortBrick::LSortBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(0, 1));
	data.push_back(new PointGame(1, 1));
	idBlock = 6;
	initCell();
}


LSortBrick::~LSortBrick(void)
{
}

int LSortBrick::getWidth()
{
	return 2;
}

int LSortBrick::getHeight()
{
	return 2;
}
