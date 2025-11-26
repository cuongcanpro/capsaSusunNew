#include "BoardDataPop.h"
#include "Engine/GlobalVar.h"
#include "../Utility/GameUtility.h"
#include "../Utility/GameSound.h"
#include <Game/GUIManager.h>


BoardDataPop::BoardDataPop(void)
{
	for (int i = 0; i < BOARD_ROW_POP; i++)
		for (int j = 0; j < BOARD_COLUMN_POP; j++) {
			arrayWay[i][j] = new Way();
		}
		currentPoint = new PointGame();
		currentSize = 5;
		maxNum = 3;
}


BoardDataPop::~BoardDataPop(void)
{
}

void BoardDataPop::reset() {
	arrayEmpty.clear();
	for (int i = 0; i < BOARD_ROW_POP; i++)
		for (int j = 0; j < BOARD_COLUMN_POP; j++) {
			arrayBall[i][j] = 0;
			arrayEmpty.push_back(i * BOARD_COLUMN_POP + j);
		}

}

void BoardDataPop::newGame() {
	maxNum = 4;
	currentSize = 5;
    countToGen  = 0;

    //maxNum                              = 7;
    int _array[BOARD_ROW_POP][BOARD_COLUMN_POP] = {
        {7, 6,5, 5, 4, 0, 0, 0, 0, 0},
        {5, 5, 3, 5, 5, 0, 0, 0, 0, 0},
        {1, 5, 5, 1, 5, 0, 0, 0, 0, 0},
        {4, 5, 5, 5, 5, 0, 0, 0, 0, 0},
        {2, 5, 2, 5, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    //_array[0] = {3,3,3,3,3,3,3,3,3,3};
	for (int i = 0; i < BOARD_ROW_POP; i++)
		for (int j = 0; j < BOARD_COLUMN_POP; j++) {
			arrayBall[i][j] = genBall();
         //   arrayBall[i][j] = _array[i][j];
			//arrayBall[i][j] = i * BOARD_COLUMN_POP + j;
			//arrayBall[i][j] = 1;
		}
    if (checkNoMove())
    {
        newGame();
    }
	int color = 4;
	/*arrayBall[0][2] = color;
	arrayBall[1][1] = color;
	arrayBall[1][3] = color;
	arrayBall[2][0] = color;
	arrayBall[2][4] = color;
	arrayBall[3][1] = color;
	arrayBall[3][3] = color;
	arrayBall[4][2] = color;*/
}

PointGame BoardDataPop::getCanTouchPoint()
{
    vector<PointGame> arrayRandom;
    for (int i = 0; i < currentSize; i++)
        for (int j = 0; j < currentSize; j++)
        {
            PointGame p;
            p.x = i;
            p.y = j;
            arrayRandom.push_back(p);
        }
    while (true)
    {
        int rand = (int)(AXRANDOM_0_1() * currentSize * currentSize * 0.9999);
        if (rand >= arrayRandom.size())
        {
            return PointGame(-1, -1);
        }
        PointGame p = arrayRandom.at(rand);
        if (p.x - 1 >= 0 && arrayBall[p.x][p.y] == arrayBall[p.x - 1][p.y])
        {
            return p;
        }
        if (p.x + 1 < currentSize && arrayBall[p.x][p.y] == arrayBall[p.x + 1][p.y])
        {
            return p;
        }
        if (p.y - 1 >= 0 && arrayBall[p.x][p.y] == arrayBall[p.x][p.y - 1])
        {
            return p;
        }
        if (p.y + 1 < currentSize && arrayBall[p.x][p.y] == arrayBall[p.x][p.y + 1])
        {
            return p;
        }
        arrayRandom.erase(arrayRandom.begin() + rand);
        if (arrayRandom.size() == 0)
        {
            return PointGame(-1, -1);
        }
    }
}

void BoardDataPop::loadGame() {
    string add = type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
	string s = string(UserDefault::getInstance()->getStringForKey(("dataPop" + add).c_str(), ""));
	char * pch = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), pch);
	pch[s.size()] = '\0'; // don't forget the terminating 0
	int dataSave[BOARD_COLUMN_POP * BOARD_ROW_POP];
	char *num;
	num = strtok(pch, ",");
	dataSave[0] = atoi(num);
	for (int i = 1; i < BOARD_COLUMN_POP * BOARD_ROW_POP; i++)
	{
		num = strtok(NULL, ",");
		dataSave[i] = atoi(num);
	}
	for (int i = 0; i < BOARD_COLUMN_POP * BOARD_ROW_POP; i++) {
		int row = i / BOARD_COLUMN_POP;
		int column = i % BOARD_COLUMN_POP;
		arrayBall[row][column] = 0;
		if (dataSave[i] > 0) {
			arrayBall[row][column] = dataSave[i];
		}
	}
	maxNum = UserDefault::getInstance()->getIntegerForKey(("maxNum" + add).c_str(), 4);
	loadCurrentSize();
}

void BoardDataPop::loadCurrentSize()
{
	currentSize = 5;
	if (maxNum > LIMIT_SIZE_POP) {
            currentSize = (maxNum - LIMIT_SIZE_POP - 1) / 2 + 1 + currentSize;
	}
    if (currentSize > BOARD_ROW_POP)
        currentSize = BOARD_ROW_POP;
}

void BoardDataPop::updatePoint(int currentX, int currentY) {
	int i, j;
	for (i = 0; i < currentSize; i++) {
		for (j = 0; j < currentSize; j++) {
			arrayWay[i][j]->reset();
			if (arrayBall[currentY][currentX] == arrayBall[i][j]) {
				arrayMap[i][j] = 0;
			}
			else {
				arrayMap[i][j] = 1;
			}
		}
	}

	arrayWay[currentY][currentX]->point = 0;
	currentPoint->x = currentX;
	currentPoint->y = currentY;
	calculatePoint(currentX, currentY);
}

void BoardDataPop:: calculatePoint(int x, int y) {

	bool check[4];
	for(int i = 0; i < 4; i++)
		check[i] = false;

	if(x < 0 || x >= currentSize)
		return;
	if(y < 0 || y >= currentSize)
		return;

	if (x + 1 < currentSize) {
		if (arrayWay[y][x + 1]->point == -1 || arrayWay[y][x + 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y][x + 1] <= 0) {
				arrayWay[y][x + 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x + 1]->previousPoint->x = x;
				arrayWay[y][x + 1]->previousPoint->y = y;
				check[0] = true;
			}
		}

	}

	if (x - 1 >= 0) {
		if (arrayWay[y][x - 1]->point == -1 || arrayWay[y][x - 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y][x - 1] <= 0) {
				arrayWay[y][x - 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x - 1]->previousPoint->x = x;
				arrayWay[y][x - 1]->previousPoint->y = y;

				check[1] = true;
			}
		}

	}

	if (y + 1 < currentSize) {
		if (arrayWay[y + 1][x]->point == -1 || arrayWay[y + 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y + 1][x] <= 0) {

				arrayWay[y + 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y + 1][x]->previousPoint->x = x;
				arrayWay[y + 1][x]->previousPoint->y = y;

				check[2] = true;

			}
		}

	}

	if (y - 1 >= 0) {
		if (arrayWay[y - 1][x]->point == -1 || arrayWay[y - 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayMap[y - 1][x] <= 0) {
				arrayWay[y - 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y - 1][x]->previousPoint->x = x;
				arrayWay[y - 1][x]->previousPoint->y = y;

				// calculatePoint(x, y - 1);
				check[3] = true;
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
}

void BoardDataPop::setWay(int targetY, int targetX) {
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

bool BoardDataPop::updateValueCurrent() {
    PointGame p         = PointGame(currentPoint->x, currentPoint->y);
    arrayBall[p.y][p.x] = arrayBall[p.y][p.x] + 1;
    if (arrayBall[p.y][p.x] > maxNum)
    {
        maxNum = arrayBall[p.y][p.x];
        if (maxNum > LIMIT_SIZE_POP)
        {
            loadCurrentSize();
        }
        return true;
    }
    return false;
}

vector<PointGame*> BoardDataPop::getListBall(int row, int column) {

	vector<PointGame*> result1 ;

	return result1;
}

bool BoardDataPop::checkExist(PointGame *value, vector<PointGame*> array2) {
	for (int i = 0; i < array2.size(); i++) {
		if (value->x == array2.at(i)->x && value->y == array2.at(i)->y) {
			return true;
		}
	}

	return false;
}

bool BoardDataPop::checkNoMove()
{
	for (int i = 0; i < currentSize; i++)
		for (int j = 0; j < currentSize; j++) {
			int id = arrayBall[i][j];
			if (i + 1 < currentSize && id == arrayBall[i + 1][j] || j + 1 < currentSize && id == arrayBall[i][j + 1])
				return false;
		}
	return true;
}

bool BoardDataPop::checkEndGame() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			int id = arrayBall[i][j];
			if (i + 1 < currentSize && id == arrayBall[i + 1][j] || j + 1 < currentSize && id == arrayBall[i][j + 1])
				return false;
		}
	return true;
}

bool BoardDataPop::checkNewBall()
{
	
	return false;
}

int BoardDataPop::getNumBall()
{
	int count = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (arrayBall[i][j] > 0) {
				count++;
			}
		}
	return count;
}

void BoardDataPop::renewBall()
{
    bool genSpecial = false;
    if (type == BoardType::POP_TYPE_HARD)
    {
        countToGen--;
        if (countToGen < 0)
        {
            genSpecial = true;
            int num    = maxNum - 6;
            num        = num < 0 ? 0 : num;
            countToGen = 10 + num * 5;
        }
    }
    
	arrayMoveBegin.clear();
	arrayMoveEnd.clear();
	for (int i = 0; i < currentSize; i++) {
		int count = 0;
		for (int j = 0; j < currentSize; j++) {
			if (arrayBall[j][i] <= 0) {
				int k;
				for (k = j + 1; k < currentSize; k++) {
					if (arrayBall[k][i] > 0) {
						arrayBall[j][i] = arrayBall[k][i];
						arrayBall[k][i] = 0;
						arrayMoveBegin.push_back(new PointGame(i, k));
						break;
					}
				}
				if (k == currentSize) {
                    if (genSpecial)
                    {
                        genSpecial = false;
                        int add         = 3;
                        if (maxNum <= 6)
                        {
                            add = 7;
                        }
                        else
                        {
                            add = 7 - (maxNum - 6);
                        }
                        if (add < 3)
                        {
                            add = 3;
                        }
                        arrayBall[j][i] = NUM_SPECIAL + add;
                    }
                    else
                    {
                        arrayBall[j][i] = genBall();
                    }
					arrayMoveBegin.push_back(new PointGame(i, currentSize + count));
					count++;
				}
				arrayMoveEnd.push_back(new PointGame(i, j));
			}
		}
	}
    
}

int BoardDataPop::genBall()
{
	int maxGen;
	if (maxNum >= 8)
		maxGen = maxNum - 3;
	else if (maxNum == 7 || maxNum == 6)
		maxGen = 5;
	else if (maxNum == 5)
		maxGen = 4;
	else
		maxGen = maxNum;
	//maxGen = maxGen > 2 ? maxGen : 3;
	return floor(GameUtility::getRandom() * maxGen) + 1;
}

int BoardDataPop::getNumSpecial()
{
    int count = 0;
    for (int i = 0; i < currentSize; i++)
    {
        for (int j = 0; j < currentSize; j++)
        {
            if (arrayBall[i][j] > NUM_SPECIAL)
                count++;
        }
    }
    return count;
}

PointGame BoardDataPop::getPosDestroy(int num)
{
    PointGame p;
    p.x            = -1;
    p.y            = -1;
    int maxCurrent = 0;
    for (int i = 0; i < currentSize; i++)
    {
        for (int j = 0; j < currentSize; j++)
        {
            if (arrayBall[i][j] > NUM_SPECIAL)
            {
                int value = arrayBall[i][j] - NUM_SPECIAL;
                if (value <= num && value > maxCurrent)
                {
                    maxCurrent = value;
                    p.x        = i;
                    p.y        = j;
                }
            }
        }
    }
    return p;
}
