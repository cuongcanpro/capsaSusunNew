#include "TetrisZLeftBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


TetrisZLeftBrick::TetrisZLeftBrick(void)
{
    TetrisBaseEntity();
}


TetrisZLeftBrick::~TetrisZLeftBrick(void)
{
}




void TetrisZLeftBrick::changeState()
{
	int saveState, saveX, saveY;
	saveState = state;
	saveX = x;
	saveY = y;
	state++;
	if(state == 2)
		state = 0;
	if(x + getWidth() >= NUM_WIDTH)
		x = NUM_WIDTH - getWidth();
	makeState();

	if(notMove(0, 0))
	{
		state = saveState;
		x = saveX;
		y = saveY;
		makeState();
	}
}

void TetrisZLeftBrick::makeState()
{
	countPoint = 0;
	switch (state) {
	case 0:
		addPoint(x + 2, y);
		addPoint(x + 1, y);
		addPoint(x + 1, y + 1);
		addPoint(x, y + 1);

		break;
	case 1:
		addPoint(x, y);
		addPoint(x, y + 1);
		addPoint(x + 1, y + 1);
		addPoint(x + 1, y + 2);
		break;

	default:
		break;
	}

}

int TetrisZLeftBrick::getWidth()
{
	if(state == 0)
		return 3;
	return 2;	
}

int TetrisZLeftBrick::getHeight()
{
	if(state == 1)
		return 3;
	return 2;
}

void TetrisZLeftBrick::changeMap()
{
	switch (state) {
	case 0:
		game->setCell(x + 2, y);
		game->setCell(x + 1, y);
		game->setCell(x + 1, y + 1);
		game->setCell(x, y + 1);

		break;
	case 1:
		game->setCell(x, y);
		game->setCell(x, y + 1);
		game->setCell(x + 1, y + 1);
		game->setCell(x + 1, y + 2);
		break;

	default:
		break;
	}
}
