#include "TetrisSquare.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


TetrisSquare::TetrisSquare(void)
{
    TetrisBaseEntity();
}


TetrisSquare::~TetrisSquare(void)
{
}




void TetrisSquare::changeState()
{

}

void TetrisSquare::makeState()
{
	countPoint = 0;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
		{
			addPoint(x + j, y + i);
		}

}

int TetrisSquare::getWidth()
{
		return 2;
}

int TetrisSquare::getHeight()
{
	return 2;
}

void TetrisSquare::changeMap()
{
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
		{
			game->dataBrick[y + i][x + j] = 1;
		}
}
