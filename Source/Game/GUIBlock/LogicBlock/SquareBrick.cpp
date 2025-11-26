#include "SquareBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


SquareBrick::SquareBrick(void)
{
	BaseEntity();
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			data.push_back(new PointGame(j, i));
		}
	idBlock = 8;
	initCell();
}


SquareBrick::~SquareBrick(void)
{
}

int SquareBrick::getWidth()
{
	return 2;
}

int SquareBrick::getHeight()
{
	return 2;
}


