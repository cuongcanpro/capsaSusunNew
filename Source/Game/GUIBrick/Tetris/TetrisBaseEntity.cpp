#include "TetrisBaseEntity.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "Game/Utility/GameSound.h"


TetrisBaseEntity::TetrisBaseEntity(void)
{
	frame = 15 * DELTA_TIME;
	state = 0;
	countTime = 0;
	countTimePress = 0;
	firstPress = true;
	countPoint = 0;
	x = 0;
	y = 0;
    visible = true;
	data.push_back(new PointGame());
	data.push_back(new PointGame());
	data.push_back(new PointGame());
	data.push_back(new PointGame());
	type = 0;
	makeState();
}


TetrisBaseEntity::~TetrisBaseEntity(void)
{
	for(int i = 0; i < 4; i++)
	{
		delete data.at(i);
	}
	data.clear();
}

void TetrisBaseEntity::update()
{
	if(game->state != GameState::PLAY)
		return;
	if (!visible)
		return;
	countTime = countTime + game->deltaTime;
	if(checkStop())
	{
		countTime = 0;
		countTimePress = 0;
		return;
	}
	if (countTime >= frame / (1 + game->speedBrick / 5)) {
		countTime = 0;
		moveDown();

	}
// 	if (x < 0 || x > NUM_WIDTH - 1 || y < 0 || y > NUM_HEIGHT - 1) {
// 		visible = false;
// 	}

	checkKeyPress();
}

void TetrisBaseEntity::changeMap()
{
	
	for (int i = 0; i < this->data.size(); i++) {
		game->setCell(this->data.at(i)->x, this->data.at(i)->y);
	}
}

void TetrisBaseEntity::changeState()
{
	switch (type)
	{
	case COLUMN:
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
		break;
	case SQUARE:
		{
			
		}
		break;
	case TBRICK:
		{
			int saveState, saveX, saveY;
			saveState = state;
			saveX = x;
			saveY = y;
			state++;
			if(state == 4)
				state = 0;


			makeState();
			if(notMove(0, 0))
			{
				state = saveState;
				x = saveX;
				y = saveY;
				makeState();
			}
		}
		break;
	case ZRIGHT:
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
		break;
	case ZLEFT:
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
		break;
	case LLEFT:
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
		break;
	case LRIGHT:
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
		break;
	default:
		break;
	}
}

void TetrisBaseEntity::makeState()
{
	countPoint = 0;
	switch (type)
	{
	case COLUMN:
		{
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
				addPoint(x, y);
				addPoint(x, y + 1);
				addPoint(x, y + 2);
				addPoint(x, y + 3);
				break;
			}
		}
		break;
	case SQUARE:
		{
			for(int i = 0; i < 2; i++)
				for(int j = 0; j < 2; j++)
				{
					addPoint(x + j, y + i);
				}
		}
		break;
	case TBRICK:
		{
			switch (state) {
			case 0:
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x + 2, y);
				addPoint(x + 1, y + 1);

				break;
			case 1:
				addPoint(x, y);
				addPoint(x, y + 1);
				addPoint(x + 1, y + 1);
				addPoint(x, y + 2);
				break;
			case 2:
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x, y + 1);
				addPoint(x + 2, y + 1);
				break;
			case 3:
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x, y + 1);
				addPoint(x + 1, y + 2);
				break;
			default:
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x + 2, y);
				addPoint(x + 1, y + 1);
				break;
			}
		}
		break;
	case ZRIGHT:
		{
			switch (state) {
			case 0:
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x + 2, y + 1);

				break;
			case 1:
				addPoint(x + 1, y);
				addPoint(x, y + 1);
				addPoint(x + 1, y + 1);
				addPoint(x, y + 2);
				break;

			default:
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x + 2, y + 1);
				break;
			}
		}
		break;
	case ZLEFT:
		{
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
				addPoint(x + 2, y);
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x, y + 1);
				break;
			}
		}
		break;
	case LLEFT:
		{
			switch (state) {
			case 0:
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x, y + 1);
				addPoint(x, y + 2);

				break;
			case 1:
				addPoint(x, y);
				addPoint(x, y + 1);
				addPoint(x + 1, y + 1);
				addPoint(x + 2, y + 1);
				break;
			case 2:
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x, y + 2);
				addPoint(x + 1, y + 2);
				break;
			case 3:
				addPoint(x + 2, y);
				addPoint(x + 1, y);
				addPoint(x, y);
				addPoint(x + 2, y + 1);
				break;
			default:
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x, y + 1);
				addPoint(x, y + 2);
				break;
			}
		}
		break;
	case LRIGHT:
		{
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
				addPoint(x, y);
				addPoint(x + 1, y);
				addPoint(x + 1, y + 1);
				addPoint(x + 1, y + 2);
				break;
			}
		}
		break;
	default:
		break;
	}
	
}

int TetrisBaseEntity::getWidth()
{
	switch (type)
	{
	case COLUMN:
		{
			if (state == 1)
				return 4;
			return 1;
		}
		break;
	case SQUARE:
		{
			return 2;
		}
		break;
	case TBRICK:
		{
			if(state == 1 || state == 3)
				return 2;
			return 3;	
		}
		break;
	case ZLEFT:
		{
			if(state == 0)
				return 3;
			return 2;	
		}
		break;
	case ZRIGHT:
		{
			if(state == 0)
				return 3;
			return 2;	
		}
		break;
	case LLEFT:
		{
			if(state == 0 || state == 2)
				return 2;
			return 3;
		}
		break;
	case LRIGHT:
		{
			if(state == 0 || state == 2)
				return 2;
			return 3;
		}
		break;
	default:
		return 0;
		break;
	}
}

int TetrisBaseEntity::getHeight()
{
	switch (type)
	{
	case COLUMN:
		{
			if (state == 1)
				return 1;
			return 4;
		}
		break;
	case SQUARE:
		{
			return 2;
		}
		break;
	case TBRICK:
		{
			if(state == 1 || state == 3)
				return 3;
			return 2;	
		}
		break;
	case ZLEFT:
		{
			if(state == 1)
				return 3;
			return 2;
		}
		break;
	case ZRIGHT:
		{
			if(state == 1)
				return 3;
			return 2;
		}
		break;
	case LLEFT:
		{
			if(state == 0 || state == 2)
				return 3;
			return 2;
		}
		break;
	case LRIGHT:
		{
			if(state == 0 || state == 2)
				return 3;
			return 2;
		}
		break;
	default:
		return 0;
		break;
	}
}

void TetrisBaseEntity::moveLeft()
{
	if (game->state != GameState::PLAY)
		return;

	if (x > 0 && !notMove(-1, 0))
		x--;
	countTimePress = 0;
	makeState();
}

void TetrisBaseEntity::moveRight()
{
	if (game->state != GameState::PLAY)
		return;
	if (x < NUM_WIDTH - getWidth() && !notMove(1, 0))
		x++;

	countTimePress = 0;
	makeState();
}

bool TetrisBaseEntity::checkStop()
{
	if (countTime >= frame / (1 + game->speedBrick / 4)) {
		if (y == 0) {
			GUIManager::getInstance().guiBrick->tetrisLayer->genNew();
			return true;

		} else {
			if (notMove(0, -1))
			{
				GUIManager::getInstance().guiBrick->tetrisLayer->genNew();
				return true;
			}

		}
	}
	return false;
}

bool TetrisBaseEntity::notMove( int disX, int disY )
{
	TetrisBrickData* brickData = GUIManager::getInstance().guiBrick->tetrisLayer->data;
	PointGame* check = new PointGame();
	for (int i = 0; i < data.size(); i++) {

		check->x = data.at(i)->x + disX;
		check->y = data.at(i)->y + disY;

		if (brickData->inData(check)) {
			return true;
		}

	}
	return false;
}

void TetrisBaseEntity::moveDown()
{
	if (game->state != GameState::PLAY)
		return;
	
	if (y > 0 && !notMove(0, -1))
		y--;

	//countTime = 0;
	countTimePress = 0;
	makeState();
}

void TetrisBaseEntity::checkKeyPress()
{
	//GUIManager::getInstance().guiBrick->checkLeft();
	//GUILoading layer = GUIManager::getInstance().guiBrick;
	if (GUIManager::getInstance().guiBrick->checkLeft() || GUIManager::getInstance().guiBrick->checkRight() || GUIManager::getInstance().guiBrick->checkDown()) {
		countTimePress = countTimePress + game->deltaTime;
		

		if (GUIManager::getInstance().guiBrick->checkRight() || GUIManager::getInstance().guiBrick->checkLeft()) {
			if ((firstPress && countTimePress > 7 * DELTA_TIME) || (!firstPress && countTimePress > 2 * DELTA_TIME)) {
				firstPress = false;
				countTimePress = 0;
				if (GUIManager::getInstance().guiBrick->checkLeft()) {
					moveLeft();
				} else if (GUIManager::getInstance().guiBrick->checkRight()) {
					moveRight();
				}
			}
		} else {
			if (countTimePress > DELTA_TIME) {
				moveDown();
			}
		}
	}
	else
	{
		firstPress = true;
	//	GameSound::playMove();
	}
}

void TetrisBaseEntity::addPoint( int x, int y )
{
	if (countPoint >= data.size())
		return;
	data.at(countPoint)->x = x;
	data.at(countPoint)->y = y;
	countPoint++;
}

void TetrisBaseEntity::setData( TetrisBrickData *data )
{
	for (int i = 0; i < this->data.size(); i++) {
		if(this->data.at(i)->y < 20)
			data->setCell(this->data.at(i)->x, this->data.at(i)->y);
	}
}

void TetrisBaseEntity::setPos( int x, int y )
{
	for (int i = 0; i < data.size(); i++) {
		data.at(i)->x = data.at(i)->x + x - this->x;
		data.at(i)->y = data.at(i)->y + y - this->y;
	}

	this->x = x;
	this->y = y;
}
