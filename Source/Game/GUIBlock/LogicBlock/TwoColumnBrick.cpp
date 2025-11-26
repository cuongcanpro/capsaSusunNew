#include "TwoColumnBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


TwoColumnBrick::TwoColumnBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(0, 1));
	idBlock = 11;
	initCell();
}


TwoColumnBrick::~TwoColumnBrick(void)
{
}

int TwoColumnBrick::getWidth()
{
	return 1;
}

int TwoColumnBrick::getHeight()
{
	return 2;
}

