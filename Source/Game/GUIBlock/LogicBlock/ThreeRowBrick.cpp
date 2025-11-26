#include "ThreeRowBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


ThreeRowBrick::ThreeRowBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(1, 0));
	data.push_back(new PointGame(2, 0));
	idBlock = 10;
	initCell();
}


ThreeRowBrick::~ThreeRowBrick(void)
{
}

int ThreeRowBrick::getWidth()
{
	return 3;
}

int ThreeRowBrick::getHeight()
{
	return 1;
}
