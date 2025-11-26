#include "FourColumnBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


FourColumnBrick::FourColumnBrick(void)
{
	BaseEntity();
	data.push_back(new PointGame(0, 0));
	data.push_back(new PointGame(0, 1));
	data.push_back(new PointGame(0, 2));
	data.push_back(new PointGame(0, 3));
	idBlock = 4;
	initCell();
}


FourColumnBrick::~FourColumnBrick(void)
{
}

int FourColumnBrick::getWidth()
{
	return 1;
}

int FourColumnBrick::getHeight()
{
	return 4;
}
