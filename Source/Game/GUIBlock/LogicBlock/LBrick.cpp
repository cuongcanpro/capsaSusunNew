#include "LBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


LBrick::LBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(1, 0));
	data.push_back(new PointGame(2, 0));
	data.push_back(new PointGame(0, 1));
	idBlock = 5;
	initCell();
}


LBrick::~LBrick(void)
{
}

int LBrick::getWidth()
{
	return 3;
}

int LBrick::getHeight()
{
	return 2;
}

