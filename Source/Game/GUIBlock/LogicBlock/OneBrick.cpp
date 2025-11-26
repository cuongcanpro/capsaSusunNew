#include "OneBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


OneBrick::OneBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	
	idBlock = 7;
	initCell();
}


OneBrick::~OneBrick(void)
{
}

int OneBrick::getWidth()
{
	return 1;
}

int OneBrick::getHeight()
{
	return 1;
}

