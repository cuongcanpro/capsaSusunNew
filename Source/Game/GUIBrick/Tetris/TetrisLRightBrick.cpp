#include "TetrisLRightBrick.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"


TetrisLRightBrick::TetrisLRightBrick(void)
{
    TetrisBaseEntity();
}


TetrisLRightBrick::~TetrisLRightBrick(void)
{
}




void TetrisLRightBrick::changeState()
{
	int saveState, saveX, saveY;
	saveState = state;
	saveX = x;
	saveY = y;

	state++;
	if(state == 4)
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

void TetrisLRightBrick::makeState()
{
	countPoint = 0;

	switch (state) {
	case 0:
		addPoint(x, y);
		addPoint(x + 1, y);
		addPoint(x + 1, y + 1);
		addPoint(x + 1, y + 2);

		break;
	case 1:
		addPoint(x, y + 1);
		addPoint(x, y);
		addPoint(x + 1, y);
		addPoint(x + 2, y);
		break;
	case 2:
		addPoint(x, y);
		addPoint(x, y + 1);
		addPoint(x, y + 2);
		addPoint(x + 1, y + 2);
		break;
	case 3:
		addPoint(x + 2, y);
		addPoint(x + 1, y + 1);
		addPoint(x, y + 1);
		addPoint(x + 2, y + 1);
		break;
	default:
		break;
	}

}

int TetrisLRightBrick::getWidth()
{
	if(state == 0 || state == 2)
		return 2;
	return 3;
}

int TetrisLRightBrick::getHeight()
{
	if(state == 0 || state == 2)
		return 3;
	return 2;
}

void TetrisLRightBrick::changeMap()
{
	switch (state) {
	case 0:
		game->setCell(x, y);
		game->setCell(x + 1, y);
		game->setCell(x + 1, y + 1);
		game->setCell(x + 1, y + 2);

		break;
	case 1:
		game->setCell(x, y + 1);
		game->setCell(x, y);
		game->setCell(x + 1, y);
		game->setCell(x + 2, y);
		break;
	case 2:
		game->setCell(x, y);
		game->setCell(x, y + 1);
		game->setCell(x, y + 2);
		game->setCell(x + 1, y + 2);
		break;
	case 3:
		game->setCell(x + 2, y);
		game->setCell(x + 1, y + 1);
		game->setCell(x, y + 1);
		game->setCell(x + 2, y + 1);
		break;
	default:
		break;
	}
}
