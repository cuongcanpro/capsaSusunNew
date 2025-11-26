#include "BigLBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


BigLBrick::BigLBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(2, 0));
	data.push_back(new PointGame(2, 1));
	data.push_back(new PointGame(2, 2));
	data.push_back(new PointGame(1, 2));
	data.push_back(new PointGame(0, 2));
	idBlock = 1;
	initCell();
}


BigLBrick::~BigLBrick(void)
{
}

int BigLBrick::getWidth()
{
	return 3;
}

int BigLBrick::getHeight()
{
	return 3;
}

