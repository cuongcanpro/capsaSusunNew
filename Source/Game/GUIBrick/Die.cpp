#include "Die.h"
#include "Engine/GlobalVar.h"


Die::Die(void)
{
	frame = 3 * DELTA_TIME;
	state = 0;
	countTime = 0;
}


Die::~Die(void)
{
}

void Die::update()
{
	if (visible) {
		countTime = countTime + game->deltaTime;

		if (countTime >= frame) {
			state = 1 - state;
			countTime = 0;
		}
	}
}

void Die::changeMap()
{
	if (!visible)
		return;
	if (state == 0) {
		int row = y;
		game->dataBrick[row][x] = 1;
		game->dataBrick[row][x + 3] = 1;
		game->dataBrick[row][x + 1] = 0;
		game->dataBrick[row][x + 2] = 0;

		row++;
		game->dataBrick[row][x + 1] = 1;
		game->dataBrick[row][x + 2] = 1;
		game->dataBrick[row][x + 0] = 0;
		game->dataBrick[row][x + 3] = 0;

		row++;
		game->dataBrick[row][x + 1] = 1;
		game->dataBrick[row][x + 2] = 1;
		game->dataBrick[row][x + 0] = 0;
		game->dataBrick[row][x + 3] = 0;

		row++;
		game->dataBrick[row][x] = 1;
		game->dataBrick[row][x + 3] = 1;
		game->dataBrick[row][x + 1] = 0;
		game->dataBrick[row][x + 2] = 0;
	} else {
		int row = y;
		game->dataBrick[row][x + 1] = 1;
		game->dataBrick[row][x + 2] = 1;
		game->dataBrick[row][x + 0] = 0;
		game->dataBrick[row][x + 3] = 0;

		row++;
		game->dataBrick[row][x] = 1;
		game->dataBrick[row][x + 3] = 1;
		game->dataBrick[row][x + 1] = 0;
		game->dataBrick[row][x + 2] = 0;

		row++;
		game->dataBrick[row][x] = 1;
		game->dataBrick[row][x + 3] = 1;
		game->dataBrick[row][x + 1] = 0;
		game->dataBrick[row][x + 2] = 0;

		row++;
		game->dataBrick[row][x + 1] = 1;
		game->dataBrick[row][x + 2] = 1;
		game->dataBrick[row][x + 0] = 0;
		game->dataBrick[row][x + 3] = 0;
	}
}
	
void Die::setPos( int x, int y )
{
	if(x < 0)
		x = 0;
	if(y < 0)
		y = 0;
	if (x >= NUM_WIDTH - 3)
		this->x = NUM_WIDTH - 4;
	else
		this->x = x;

	if (y >= NUM_HEIGHT - 3)
		this->y = NUM_HEIGHT - 4;
	else
		this->y = y;
}
