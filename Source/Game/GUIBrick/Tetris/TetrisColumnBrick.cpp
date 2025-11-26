#include "TetrisColumnBrick.h"
#include "Game/GameClient.h"


TetrisColumnBrick::TetrisColumnBrick(void) : TetrisBaseEntity() {
	
}


TetrisColumnBrick::~TetrisColumnBrick(void)
{
}




void TetrisColumnBrick::changeState()
{
	int saveState, saveX, saveY;
	saveState = state;
	saveX = x;
	saveY = y;

	state++;
	if (state == 2)
		state = 0;


	switch (state) {
	case 0:
		x = x + 1;
		y = y - 1;
		break;
	case 1:
		x = x - 1;
		y = y + 1;
		break;
	default:
		break;
	}
	if (x + getWidth() >= NUM_WIDTH)
		x = NUM_WIDTH - getWidth();

	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;


	makeState();
	if(notMove(0, 0))
	{
		state = saveState;
		x = saveX;
		y = saveY;
		makeState();
	}
}

void TetrisColumnBrick::makeState()
{
	countPoint = 0;

	switch (state) {
	case 0:
		addPoint(x, y);
		addPoint(x, y + 1);
		addPoint(x, y + 2);
		addPoint(x, y + 3);

		break;
	case 1:
		addPoint(x + 1, y);
		addPoint(x + 2, y);
		addPoint(x + 3, y);
		addPoint(x, y);
		break;
	default:
		break;
	}

}

int TetrisColumnBrick::getWidth()
{
	if (state == 1)
		return 4;
	return 1;
}

int TetrisColumnBrick::getHeight()
{
	if (state == 1)
		return 1;
	return 4;
}
