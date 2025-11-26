#include "BoardDataBubble.h"
#include "Engine/GlobalVar.h"
#include "../Utility/GameUtility.h"
#include "../Data/GlobalData.h"
#include <Game/Logic/Constant.h>

BoardDataBubble::BoardDataBubble(void)
{
	for (int i = 0; i < 4; i++)
	{
		arrayRand[i] = pow(2, i);
	}
	for (int i = 0; i < MAX_NEXT; i++)
		arrayPointNext[i] = new PointGame();
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++) {
			arrayWay[i][j] = new Way();
		}

	currentPoint = new PointGame();
	numRandStart[0] = 5;
	numRandStart[1] = 6;

	arrayMaxNumber[0] = 256;
	arrayMaxNumber[1] = 512;
	arrayMaxNumber[3] = 256;
	arrayMaxNumber[4] = 256;
	level = 0;

	NUM_ROW_BUBBLE = 9;
	NUM_COLUMN_BUBBLE = 5;
	for (int i = 0; i < NUM_ROW_BUBBLE; i++)
		for (int j = 0; j < NUM_COLUMN_BUBBLE; j++)
		{
			arrayBallTutorial[i][j] = 0;
		}
	arrayBallTutorial[7][0] = 1;
	arrayBallTutorial[7][1] = 2;
	arrayBallTutorial[8][1] = 1;
	arrayBallTutorial[2][2] = 8;
	arrayBallTutorial[3][4] = 4;
	arrayBallTutorial[4][0] = 8;

	arrayNextIdTutorial[0][0] = 1;
	arrayNextIdTutorial[0][1] = 8;
	arrayNextIdTutorial[0][2] = 4;
	arrayNextIdTutorial[0][3] = 1;
	arrayNextIdTutorial[0][4] = 8;

	arrayNextPosTutorial[0][0] = new PointGame(0, 6);
	arrayNextPosTutorial[0][1] = new PointGame(1, 2);
	arrayNextPosTutorial[0][2] = new PointGame(4, 2);
	arrayNextPosTutorial[0][3] = new PointGame(3, 5);
	arrayNextPosTutorial[0][4] = new PointGame(2, 5);

	arrayNextIdTutorial[1][0] = 8;
	arrayNextIdTutorial[1][1] = 2;
	arrayNextIdTutorial[1][2] = 2;
	arrayNextIdTutorial[1][3] = 4;
	arrayNextIdTutorial[1][4] = 8;

	arrayNextPosTutorial[1][0] = new PointGame(1, 4);
	arrayNextPosTutorial[1][1] = new PointGame(2, 3);
	arrayNextPosTutorial[1][2] = new PointGame(3, 3);
	arrayNextPosTutorial[1][3] = new PointGame(0, 2);
	arrayNextPosTutorial[1][4] = new PointGame(2, 1);
}


BoardDataBubble::~BoardDataBubble(void)
{
}

void BoardDataBubble:: reset() {
	arrayEmpty.clear();
	for (int i = 0; i < NUM_ROW_BUBBLE; i++)
		for (int j = 0; j < NUM_COLUMN_BUBBLE; j++) {
			arrayBall[i][j] = 0;
			arrayEmpty.push_back(i * NUM_COLUMN_BUBBLE + j);
		}
	numRand = 2;
	//level = 0;
}

void BoardDataBubble:: newGame() {
	reset();
	// random 5 vien to
	int count = 0;
	if (level < 3)
	{
		int numStart;
		if (level == 0)
		{
			numStart = 6;
		}
		else 
			numStart = 22;
	
		for (int i = 0; i < numStart; i++) {
			int rand, row, column, color, oldRand;
			oldRand = rand = (int)(GameUtility::getRandom() * arrayEmpty.size());
			rand = arrayEmpty.at(rand);
			arrayEmpty.erase(arrayEmpty.begin() + oldRand);
			row = rand / NUM_COLUMN_BUBBLE;
			column = rand % NUM_COLUMN_BUBBLE;
			int index = (int)(GameUtility::getRandom() * 4);

			color = arrayRand[index];
		//	color = pow(2, count);
		//	color = 128;
			count++;
			arrayBall[row][column] = color;
		}

		// random 3 vien nho
		numRand = numRandStart[level];
		randomNextId();
	}
	else
	{
		for (int i = 0; i < NUM_ROW_BUBBLE; i++)
		{
			for (int j = 0; j < NUM_COLUMN_BUBBLE; j++)
			{
				arrayBall[i][j] = arrayBallTutorial[i][j];
			}
		}
		randomNextId();
	}
}

void BoardDataBubble::loadGame() {
	reset();
	for (int i = 0; i < NUM_ROW_BUBBLE * NUM_COLUMN_BUBBLE; i++) {
		int row = i / NUM_COLUMN_BUBBLE;
		int column = i % NUM_COLUMN_BUBBLE;
		arrayBall[row][column] = game->dataBubble[i];
		if (game->dataBubble[i] > 0)
			for (int j = 0; j < arrayEmpty.size(); j++) {
				if (i == arrayEmpty.at(j))
					arrayEmpty.erase(arrayEmpty.begin()+j);
			}
	}

	int count = 0;
	for (int i = 0; i < MAX_NEXT; i++)
	{
		arrayNext[i] = game->saveRandBubble[i];
		if (arrayNext[i] > 0)
			count++;
	}
	numRand = count;
}

void BoardDataBubble::loadGameTime() {
	reset();
	for (int i = 0; i < NUM_ROW_BUBBLE * NUM_COLUMN_BUBBLE; i++) {
		int row = i / NUM_COLUMN_BUBBLE;
		int column = i % NUM_COLUMN_BUBBLE;
		arrayBall[row][column] = game->dataBubble1[i];
		if (game->dataBubble1[i] > 0)
			for (int j = 0; j < arrayEmpty.size(); j++) {
				if (i == arrayEmpty.at(j))
					arrayEmpty.erase(arrayEmpty.begin()+j);
			}
	}
	int count = 0;
	for (int i = 0; i < MAX_NEXT; i++)
	{
		//arrayNext[i] = game->saveRandTime[i];
		if (arrayNext[i] > 0)
			count++;
	}
	numRand = count;
}

// ham nay khong dung
void BoardDataBubble::loadGame(int arrayData[MAX_ROW][MAX_COLUMN]) {
	reset();
	for (int i = 0; i < NUM_ROW_BUBBLE; i++)
		for (int j = 0; j < NUM_COLUMN_BUBBLE; j++) {
			arrayBall[i][j] = arrayData[i][j];

			if (arrayBall[i][j] > 0)
			{
				for (int k = 0; k < arrayEmpty.size(); k++) {
					if ((i * NUM_COLUMN_BUBBLE + j) == arrayEmpty.at(k))
					{
						arrayEmpty.erase(arrayEmpty.begin()+k);
						break;
					}
				}
			}
		}
}

void BoardDataBubble:: randomNext() {
	if (level < 3)
	{
		if (numRand > arrayEmpty.size())
			numRand = arrayEmpty.size();
		for (int i = 0; i < numRand; i++) {
			if (arrayEmpty.size() == 0)
				return;
			int rand, row, column, color, oldRand;
			oldRand = rand = (int)(GameUtility::getRandom() * arrayEmpty.size());
			rand = arrayEmpty.at(rand);
			arrayEmpty.erase(arrayEmpty.begin() + oldRand);
			row = rand / NUM_COLUMN_BUBBLE;
			column = rand % NUM_COLUMN_BUBBLE;
			arrayPointNext[i]->x = column;
			arrayPointNext[i]->y = row;
			arrayBall[row][column] = arrayNext[i];
		}
	}
	else
	{
		for (int i = 0; i < numRand; i++)
		{
			arrayPointNext[i]->x = arrayNextPosTutorial[level - 3][i]->x;
			arrayPointNext[i]->y = arrayNextPosTutorial[level - 3][i]->y;
			arrayBall[arrayPointNext[i]->y][arrayPointNext[i]->x] = arrayNext[i];
		}
		
	}
}

// ham nay ko dung nua
void BoardDataBubble:: randomReplace(int color) {
	if (arrayEmpty.size() == 0)
		return;
	int rand, row, column, oldRand;
	oldRand = rand = (int) (GameUtility::getRandom() * arrayEmpty.size());
	rand = arrayEmpty.at(rand);
	arrayEmpty.erase(arrayEmpty.begin()+oldRand);
	row = rand / 9;
	column = rand % 9;
	arrayBall[row][column] = color;
}

void BoardDataBubble:: updatePoint(int currentX, int currentY) {
	int i, j;
	for (i = 0; i < NUM_ROW_BUBBLE; i++) {
		for (j = 0; j < NUM_COLUMN_BUBBLE; j++) {
			arrayWay[i][j]->reset();
		}
	}

	arrayWay[currentY][currentX]->point = 0;
	currentPoint->x = currentX;
	currentPoint->y = currentY;
	calculatePoint(currentX, currentY);
}

void BoardDataBubble:: calculatePoint(int x, int y) {

	bool check[8];
	for(int i = 0; i < 8; i++)
		check[i] = false;

	if(x < 0 || x >= NUM_COLUMN_BUBBLE)
		return;
	if(y < 0 || y >= NUM_ROW_BUBBLE)
		return;

	if (x + 1 < NUM_COLUMN_BUBBLE) {
		if (arrayWay[y][x + 1]->point == -1 || arrayWay[y][x + 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y][x + 1] <= 0) {
				arrayWay[y][x + 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x + 1]->previousPoint->x = x;
				arrayWay[y][x + 1]->previousPoint->y = y;
				check[0] = true;
			}
		}

	}

	if (x - 1 >= 0) {
		if (arrayWay[y][x - 1]->point == -1 || arrayWay[y][x - 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y][x - 1] <= 0) {
				arrayWay[y][x - 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x - 1]->previousPoint->x = x;
				arrayWay[y][x - 1]->previousPoint->y = y;

				check[1] = true;
			}
		}

	}

	if (y + 1 < NUM_ROW_BUBBLE) {
		if (arrayWay[y + 1][x]->point == -1 || arrayWay[y + 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y + 1][x] <= 0) {

				arrayWay[y + 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y + 1][x]->previousPoint->x = x;
				arrayWay[y + 1][x]->previousPoint->y = y;

				check[2] = true;

			}
		}

	}

	if (y - 1 >= 0) {
		if (arrayWay[y - 1][x]->point == -1 || arrayWay[y - 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y - 1][x] <= 0) {
				arrayWay[y - 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y - 1][x]->previousPoint->x = x;
				arrayWay[y - 1][x]->previousPoint->y = y;

				// calculatePoint(x, y - 1);
				check[3] = true;
			}
		}

	}

	if(x + 1 < NUM_COLUMN_BUBBLE)
	{
		if(x % 2 == 1)
		{
			if(y + 1 < NUM_ROW_BUBBLE)
			{
				if (arrayWay[y + 1][x + 1]->point == -1 || arrayWay[y + 1][x + 1]->point - 1 > arrayWay[y][x]->point) {
					if (arrayBall[y + 1][x + 1] <= 0) {
						arrayWay[y + 1][x + 1]->point = arrayWay[y][x]->point + 1;
						arrayWay[y + 1][x + 1]->previousPoint->x = x;
						arrayWay[y + 1][x + 1]->previousPoint->y = y;

						// calculatePoint(x, y - 1);
						check[4] = true;
					}
				}
			}
		}
		else
		{
			if(y - 1 >= 0)
			{
				if (arrayWay[y - 1][x + 1]->point == -1 || arrayWay[y - 1][x + 1]->point - 1 > arrayWay[y][x]->point) {
					if (arrayBall[y - 1][x + 1] <= 0) {
						arrayWay[y - 1][x + 1]->point = arrayWay[y][x]->point + 1;
						arrayWay[y - 1][x + 1]->previousPoint->x = x;
						arrayWay[y - 1][x + 1]->previousPoint->y = y;

						// calculatePoint(x, y - 1);
						check[5] = true;
					}
				}
			}
		}
	}

	if(x - 1 >= 0)
	{
		if(x % 2 == 1)
		{
			if(y + 1 < NUM_ROW_BUBBLE)
			{
				if (arrayWay[y + 1][x - 1]->point == -1 || arrayWay[y + 1][x - 1]->point - 1 > arrayWay[y][x]->point) {
					if (arrayBall[y + 1][x - 1] <= 0) {
						arrayWay[y + 1][x - 1]->point = arrayWay[y][x]->point + 1;
						arrayWay[y + 1][x - 1]->previousPoint->x = x;
						arrayWay[y + 1][x - 1]->previousPoint->y = y;

						// calculatePoint(x, y - 1);
						check[6] = true;
					}
				}
			}
		}
		else
		{
			if(y - 1 >= 0)
			{
				if (arrayWay[y - 1][x - 1]->point == -1 || arrayWay[y - 1][x - 1]->point - 1 > arrayWay[y][x]->point) {
					if (arrayBall[y - 1][x - 1] <= 0) {
						arrayWay[y - 1][x - 1]->point = arrayWay[y][x]->point + 1;
						arrayWay[y - 1][x - 1]->previousPoint->x = x;
						arrayWay[y - 1][x - 1]->previousPoint->y = y;

						// calculatePoint(x, y - 1);
						check[7] = true;
					}
				}
			}
		}
	}

	if (check[0]) {
		calculatePoint(x + 1, y);
	}

	if (check[1]) {
		calculatePoint(x - 1, y);
	}

	if (check[2]) {
		calculatePoint(x, y + 1);
	}

	if (check[3]) {
		calculatePoint(x, y - 1);
	}

	if (check[4]) {
		calculatePoint(x + 1, y + 1);
	}
	if (check[5]) {
		calculatePoint(x + 1, y - 1);
	}
	if (check[6]) {
		calculatePoint(x - 1, y + 1);
	}
	if (check[7]) {
		calculatePoint(x - 1, y - 1);
	}
}

void BoardDataBubble:: setWay(int targetY, int targetX) {
	int ty = targetY;
	int tx = targetX;
	arrayPoint.clear();
	// arrayPoint.push_back(new Point(targetX, targetY));

	while (arrayWay[targetY][targetX]->point > 0) {
		arrayPoint.push_back(new PointGame(targetX, targetY));
		int oldTargetX = targetX;
		targetX = arrayWay[targetY][targetX]->previousPoint->x;
		targetY = arrayWay[targetY][oldTargetX]->previousPoint->y;

	}

}

void BoardDataBubble:: updateValue(int row, int column, int value) {
	if (arrayBall[row][column] <= 0) {
		if (value > 0) {
			for (int i = 0; i < arrayEmpty.size(); i++) {
				if ((int) arrayEmpty.at(i) == row * NUM_COLUMN_BUBBLE + column) {

					arrayEmpty.erase(arrayEmpty.begin()+i);
				}
			}
		}
	} else {
		if (value <= 0) {
			arrayEmpty.push_back(row * NUM_COLUMN_BUBBLE + column);
		}
	}
	arrayBall[row][column] = value;
}

void BoardDataBubble::getListBall(int row, int column, int idBall, int idResult) {

	if (arrayCheck[row][column])
		return;
	if (idBall <= 0)
		return;
	if (arrayBall[row][column] != idBall)
		return;
	
	result.at(idResult)->arrayPoint.push_back(new PointGame(column, row));
	arrayCheck[row][column] = true;
	if (column + 1 < NUM_COLUMN_BUBBLE)
	{
		getListBall(row, column + 1, idBall, idResult);
		
	}
	if (column - 1 >= 0)
		getListBall(row, column - 1, idBall, idResult);
	if (row + 1 < NUM_ROW_BUBBLE)
	{
		getListBall(row + 1, column, idBall, idResult);
		if(column % 2 == 1)
		{
			if(column + 1 < NUM_COLUMN_BUBBLE)
				getListBall(row + 1, column + 1, idBall, idResult);
			if(column - 1 >= 0)
				getListBall(row + 1, column - 1, idBall, idResult);
		}
	}
	if (row - 1 >= 0)
	{
		getListBall(row - 1, column, idBall, idResult);
		if(column % 2 == 0)
		{
			if(column + 1 < NUM_COLUMN_BUBBLE)
				getListBall(row - 1, column + 1, idBall, idResult);
			if(column - 1 >= 0)
				getListBall(row - 1, column - 1, idBall, idResult);
		}
	}
}

bool BoardDataBubble::checkExist(PointGame *value, vector<PointGame*> array2) {
	for (int i = 0; i < array2.size(); i++) {
		if (value->x == array2.at(i)->x && value->y == array2.at(i)->y) {
			return true;
		}
	}

	return false;
}

bool BoardDataBubble::checkEndGame() {
	for (int i = 0; i < NUM_ROW_BUBBLE; i++)
		for (int j = 0; j < NUM_COLUMN_BUBBLE; j++) {
			if (arrayBall[i][j] <= 0)
				return false;
		}
		return true;
}

void BoardDataBubble::randomNextId()
{
	if (level < 3)
	{
		if (arrayEmpty.size() > NUM_COLUMN_BUBBLE * NUM_ROW_BUBBLE / 3)
		{
			numRand = numRandStart[level];
		}
		else if (arrayEmpty.size() > NUM_COLUMN_BUBBLE * NUM_ROW_BUBBLE / 5)
		{
			numRand = numRandStart[level] - 1;
		}
		else
		{
			numRand = numRandStart[level] - 2;
		}

		for (int i = 0; i < numRand; i++)
		{
			int rand = GameUtility::getRandom() * 4;
			arrayNext[i] = arrayRand[rand];
			if (arrayNext[i] == 0)
				arrayNext[i] = 1;
		}
	}
	else
	{
		numRand = 5;
		for (int i = 0; i < numRand; i++)
			arrayNext[i] = arrayNextIdTutorial[level - 3][i];
	}
	
}

void BoardDataBubble::resetCheck()
{
	for(int i = 0; i < NUM_ROW_BUBBLE; i++)
		for(int j = 0; j < NUM_COLUMN_BUBBLE; j++)
			arrayCheck[i][j] = false;
}
