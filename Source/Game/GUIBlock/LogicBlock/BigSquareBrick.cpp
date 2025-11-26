#include "BigSquareBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


BigSquareBrick::BigSquareBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(0, 1));
	data.push_back(new PointGame(0, 2));
	data.push_back(new PointGame(1, 0));
	data.push_back(new PointGame(1, 1));
	data.push_back(new PointGame(1, 2));
	data.push_back(new PointGame(2, 0));
	data.push_back(new PointGame(2, 1));
	data.push_back(new PointGame(2, 2));
	idBlock = 2;
	initCell();
}


BigSquareBrick::~BigSquareBrick(void)
{
}

int BigSquareBrick::getWidth()
{
	return 3;
}

int BigSquareBrick::getHeight()
{
	return 3;
}
