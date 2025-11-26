#include "BoardDataBomb.h"
#include "Engine/GlobalVar.h"
#include "../Utility/GameUtility.h"
#include "../Utility/GameSound.h"

int configLevel[CONFIG_ROWS][CONFIG_COLS] = {{12, 10, 10, 40}, {14, 11, 11, 50}, {14, 11, 11, 50}, {14, 11, 11, 50},
                                             {14, 11, 11, 50}, {14, 11, 11, 50}, {14, 11, 11, 50}, {14, 11, 11, 50},
                                             {14, 11, 11, 50}, {14, 11, 11, 50}};

BoardDataBomb::BoardDataBomb(void)
{
    for (int i = 0; i < BOARD_ROW_BOMB + 2; i++)
        for (int j = 0; j < BOARD_COLUMN_BOMB + 2; j++)
        {
            arrayWay[i][j]  = new Way();
        }
    currentPoint = new PointGame(0, 0);
    
}


BoardDataBomb::~BoardDataBomb(void)
{
}

void BoardDataBomb::setLevel(int level)
{
	this->level = level;
	switch (level)
	{
	case 0:
		numBomb = 12;
		sizeRow = 10;
		sizeColumn = 10;
		break;
	case 1:
		numBomb = 40;
		sizeRow = 18;
		sizeColumn = 14;
		break;
	case 2:
		numBomb = 70;
		sizeRow = 20;
		sizeColumn = 16;
		break;
	case 3:
		numBomb = 100;
		sizeRow = 25;
		sizeColumn = 20;
		break;
	default:
		break;
	}
	
}

void BoardDataBomb::setLevelExtend(int level) {
    
    numBomb                = configLevel[level][0];
    sizeRow                = configLevel[level][1];
    sizeColumn             = configLevel[level][2];
    timeGame               = configLevel[level][3];
}

bool BoardDataBomb::isValid(int row, int column)
{
    if (row < 0 || row >= sizeRow || column < 0 || column >= sizeColumn)
        return false;
    return true;
}

bool BoardDataBomb::checkValidMap()
{
    vector<vector<bool>> visited(sizeRow, vector<bool>(sizeColumn, false));
    queue<PointGame> q;

    // Bắt đầu từ tất cả ô trống ở hàng cuối cùng
    for (int j = 0; j < sizeColumn; ++j)
    {
        if (arrayBomb[sizeRow - 1][j] == 0)
        {
            q.push({sizeRow - 1, j});
            visited[sizeRow - 1][j] = true;
        }
    }

    const vector<PointGame> directions = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

    while (!q.empty())
    {
        PointGame cur = q.front();
        q.pop();

        if (cur.x == 0)
            return true;  // Đã đến hàng trên cùng

        for (auto d : directions)
        {
            int nx = cur.x + d.x, ny = cur.y + d.y;
            if (isValid(nx, ny) && !visited[nx][ny] && arrayBomb[nx][ny] == 0)
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return false;
}

void BoardDataBomb::resetMap()
{
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            arrayCell[i][j] = CellDataState::CELL_NOT_OPEN;
            arrayBomb[i][j] = 0;
        }
    }
    numBombGuess = 0;
    isGenData    = false;
    if (game->showHelpBomb)
    {
        numBomb    = 4;
        sizeColumn = 5;
        sizeRow    = 5;

        arrayBomb[0][1] = 1;
        arrayBomb[2][0] = 1;
        arrayBomb[3][4] = 1;
        arrayBomb[4][4] = 1;
    }
}

void BoardDataBomb::genData(PointGame pSelect)
{
    isGenData    = true;
	numBombGuess = 0;
	vector <int> randomPos;
	
	if (game->showHelpBomb) {
		numBomb = 4;
		sizeColumn = 5;
		sizeRow = 5;

		//numBomb = 2;
		//sizeColumn = 3;
		//sizeRow = 3;

		arrayBomb[0][1] = 1;
		arrayBomb[2][0] = 1;
		arrayBomb[3][4] = 1;
		arrayBomb[4][4] = 1;
	}
	else {
        while (true)
        {
            randomPos.clear();
            for (int i = 0; i < sizeRow; i++)
            {
                for (int j = 0; j < sizeColumn; j++)
                {
                    if (abs(i - pSelect.x) > 1 || abs(j - pSelect.y) > 1)
                    {
                        if (i == pSelect.x && j == pSelect.y)
                            continue;
                        if (AXRANDOM_0_1() < 0.2)
                            continue;
                        int pos         = i * sizeColumn + j;
                        randomPos.push_back(pos);
                    }
                }
            }
            for (int i = 0; i < numBomb; i++)
            {
                int index = randomPos.size() * AXRANDOM_0_1() * 0.9999;
                int pos   = randomPos.at(index);
                randomPos.erase(randomPos.begin() + index);
                arrayBomb[pos / sizeColumn][pos % sizeColumn] = 1;
            }
            if (true || checkValidMap())
            {
                break;
            }
        }
	}

	// Dem so Bomb
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeColumn; j++) {
			if (arrayBomb[i][j] == 0) {
				int startRow = i - 1;
				int startColumn = j - 1;
				int count = 0;
				for (int i1 = 0; i1 < 3; i1++) {
					for (int j1 = 0; j1 < 3; j1++) {
						if (checkPointInBoard(startRow + i1, startColumn + j1) &&
							arrayBomb[startRow + i1][startColumn + j1] == 1) {
							count++;
						}
					}
				}
				arrayData[i][j] = count;
			}
			else {
				arrayData[i][j] = -1;
			}
		}
	}
	AXLOGD("End Gen");
}

void BoardDataBomb::loadData()
{
    isGenData    = true;
	numBombGuess = 0;
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeColumn; j++) {
			arrayBomb[i][j] = game->arrBomb[i][j];
			switch (game->arrCell[i][j])
			{
			case 0:
				arrayCell[i][j] = CellDataState::CELL_NOT_OPEN;
				break;
			case 2:
				arrayCell[i][j] = CellDataState::CELL_BOMB_GUESS;
				numBombGuess++;
				break;
			case 1:
				arrayCell[i][j] = CellDataState::CELL_OPEN;
				break;
			default:
				arrayCell[i][j] = CellDataState::CELL_NOT_OPEN;
				break;
			}
		}
	}
	// Dem so Bomb
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeColumn; j++) {
			if (arrayBomb[i][j] == 0) {
				int startRow = i - 1;
				int startColumn = j - 1;
				int count = 0;
				for (int i1 = 0; i1 < 3; i1++) {
					for (int j1 = 0; j1 < 3; j1++) {
						if (checkPointInBoard(startRow + i1, startColumn + j1) &&
							arrayBomb[startRow + i1][startColumn + j1] == 1) {
							count++;
						}
					}
				}
				arrayData[i][j] = count;
			}
			else {
				arrayData[i][j] = -1;
			}
		}
	}
}

void BoardDataBomb::loadDataExtend() {
    numBombGuess = 0;
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            arrayBomb[i][j] = game->arrBomb[i][j];
            switch (game->arrCell[i][j])
            {
            case 0:
                arrayCell[i][j] = CellDataState::CELL_NOT_OPEN;
                break;
            case 2:
                arrayCell[i][j] = CellDataState::CELL_BOMB_GUESS;
                numBombGuess++;
                break;
            case 1:
                arrayCell[i][j] = CellDataState::CELL_OPEN;
                break;
            default:
                arrayCell[i][j] = CellDataState::CELL_NOT_OPEN;
                break;
            }
        }
    }
    // Dem so Bomb
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            if (arrayBomb[i][j] == 0)
            {
                int startRow    = i - 1;
                int startColumn = j - 1;
                int count       = 0;
                for (int i1 = 0; i1 < 3; i1++)
                {
                    for (int j1 = 0; j1 < 3; j1++)
                    {
                        if (checkPointInBoard(startRow + i1, startColumn + j1) &&
                            arrayBomb[startRow + i1][startColumn + j1] == 1)
                        {
                            count++;
                        }
                    }
                }
                arrayData[i][j] = count;
            }
            else
            {
                arrayData[i][j] = -1;
            }
        }
    }
}

std::vector<PointGame> BoardDataBomb::getDataFromPoint(PointGame point)
{
	vector<PointGame> result;
	vector<PointGame> arrNeedCheck;
	bool arrChecked[BOARD_ROW_BOMB][BOARD_COLUMN_BOMB];
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeColumn; j++) {
			arrChecked[i][j] = false;
		}
	}
	arrNeedCheck.push_back(point);
	arrChecked[point.x][point.y] = true;
	while (arrNeedCheck.size() > 0)
	{
		PointGame pointCheck = arrNeedCheck.front();
		if (arrayCell[pointCheck.x][pointCheck.y] == CellDataState::CELL_NOT_OPEN)
			result.push_back(pointCheck);
		/*if (arrayBomb[pointCheck.x][pointCheck.y] == 1) {
			return result;
		}*/
		arrNeedCheck.erase(arrNeedCheck.begin());

		// Neu xung quanh diem nay da mo du so Bomb -> mo tiep cac o xung quanh
		if (arrayBomb[pointCheck.x][pointCheck.y] != 1 && checkOpenAllBomb(pointCheck)) {
			int startRow = pointCheck.x - 1;
			int startColumn = pointCheck.y - 1;
			int count = 0;
			for (int i1 = 0; i1 < 3; i1++) {
				for (int j1 = 0; j1 < 3; j1++) {
					int row1 = startRow + i1;
					int column1 = startColumn + j1;
					if (checkPointInBoard(row1, column1) &&
						(row1 != pointCheck.x || column1 != pointCheck.y) && arrChecked[row1][column1] == false && arrayCell[row1][column1] == CellDataState::CELL_NOT_OPEN) {
						// Cell nay du dieu kien mo khi 
						PointGame p(row1, column1);
						arrNeedCheck.push_back(p);
						arrChecked[row1][column1] = true;
					}
				}
			}
		}
	}
	return result;
}

std::vector<PointGame> BoardDataBomb::getDataNotiFromPoint(PointGame pointCheck)
{
	vector<PointGame> result;
	int startRow = pointCheck.x - 1;
	int startColumn = pointCheck.y - 1;
	int count = 0;
	for (int i1 = 0; i1 < 3; i1++) {
		for (int j1 = 0; j1 < 3; j1++) {
			int row1 = startRow + i1;
			int column1 = startColumn + j1;
			if (checkPointInBoard(row1, column1) &&
				(row1 != pointCheck.x || column1 != pointCheck.y) && arrayCell[row1][column1] == CellDataState::CELL_NOT_OPEN) {
				result.push_back(PointGame(row1, column1));
			}
		}
	}
	return result;
}

bool BoardDataBomb::checkOpenAllBomb(PointGame pointCheck)
{
	if (arrayData[pointCheck.x][pointCheck.y] == 0)
		return true;
	int startRow = pointCheck.x - 1;
	int startColumn = pointCheck.y - 1;
	int count = 0;
	for (int i1 = 0; i1 < 3; i1++) {
		for (int j1 = 0; j1 < 3; j1++) {
			if (checkPointInBoard(startRow + i1 , startColumn + j1) &&
				(startRow + i1 != pointCheck.x || startColumn + j1 != pointCheck.y) && arrayCell[startRow + i1][startColumn + j1] == CellDataState::CELL_BOMB_GUESS) {
				count++;
			}
		}
	}
	if (count >= arrayData[pointCheck.x][pointCheck.y])
		return true;
	return false;
}

int BoardDataBomb::getNumCell()
{
	return sizeRow * sizeColumn;
}

void BoardDataBomb::setCell(int row, int column, CellDataState state)
{
	if (state == CellDataState::CELL_BOMB_GUESS) {
		numBombGuess++;
	}
	else if (state == CellDataState::CELL_NOT_OPEN) {
		if (arrayCell[row][column] == CellDataState::CELL_BOMB_GUESS) {
			numBombGuess--;
		}
	}
	arrayCell[row][column] = state;
}

int BoardDataBomb::getNumBombRemain()
{
	return numBomb - numBombGuess;
}

bool BoardDataBomb::checkPointInBoard(int row, int column)
{
	if (row < sizeRow && column < sizeColumn && row >= 0 && column >= 0)
		return true;
	return false;
}

bool BoardDataBomb::checkWin()
{
	//if (getNumBombRemain() != 0)
		//return false;
    int count = 0;
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeColumn; j++) {
			if (arrayCell[i][j] == CellDataState::CELL_OPEN)
				count++;
		}
	}
    if (sizeRow * sizeColumn - numBomb == count)
	    return true;
    return false;
}

void BoardDataBomb::updatePoint()
{
    int i, j;
    for (i = 0; i < sizeRow + 2; i++)
    {
        for (j = 0; j < sizeColumn + 2; j++)
        {
            arrayWay[i][j]->reset();
            if (i == 0 || j == 0 || i == sizeRow + 1 || j == sizeColumn + 1)
            {
                arrayMap[i][j] = CellDataState::CELL_OPEN;
            }
            else
            {
                arrayMap[i][j] = arrayCell[i - 1][j - 1];
            }
        }
    }

    arrayWay[currentPoint->y][currentPoint->x]->point = 0;
    calculatePoint(currentPoint->x, currentPoint->y);
}

void BoardDataBomb::calculatePoint(int x, int y)
{

    bool check[4];
    for (int i = 0; i < 4; i++)
        check[i] = false;

    if (x < 0 || x >= sizeColumn + 2)
        return;
    if (y < 0 || y >= sizeRow + 2)
        return;

    if (x + 1 < sizeColumn + 2)
    {
        if (arrayWay[y][x + 1]->point == -1 || arrayWay[y][x + 1]->point - 1 > arrayWay[y][x]->point)
        {
            if (checkCanMove(y,x + 1))
            {
                arrayWay[y][x + 1]->point            = arrayWay[y][x]->point + 1;
                arrayWay[y][x + 1]->previousPoint->x = x;
                arrayWay[y][x + 1]->previousPoint->y = y;
                check[0]                             = true;
            }
        }
    }

    if (x - 1 >= 0)
    {
        if (arrayWay[y][x - 1]->point == -1 || arrayWay[y][x - 1]->point - 1 > arrayWay[y][x]->point)
        {
            if (checkCanMove(y, x - 1))
            {
                arrayWay[y][x - 1]->point            = arrayWay[y][x]->point + 1;
                arrayWay[y][x - 1]->previousPoint->x = x;
                arrayWay[y][x - 1]->previousPoint->y = y;

                check[1] = true;
            }
        }
    }

    if (y + 1 < sizeRow + 2)
    {
        if (arrayWay[y + 1][x]->point == -1 || arrayWay[y + 1][x]->point - 1 > arrayWay[y][x]->point)
        {
            if (checkCanMove(y + 1, x))
            {

                arrayWay[y + 1][x]->point            = arrayWay[y][x]->point + 1;
                arrayWay[y + 1][x]->previousPoint->x = x;
                arrayWay[y + 1][x]->previousPoint->y = y;

                check[2] = true;
            }
        }
    }

    if (y - 1 >= 0)
    {
        if (arrayWay[y - 1][x]->point == -1 || arrayWay[y - 1][x]->point - 1 > arrayWay[y][x]->point)
        {
            if (checkCanMove(y - 1, x))
            {
                arrayWay[y - 1][x]->point            = arrayWay[y][x]->point + 1;
                arrayWay[y - 1][x]->previousPoint->x = x;
                arrayWay[y - 1][x]->previousPoint->y = y;

                // calculatePoint(x, y - 1);
                check[3] = true;
            }
        }
    }

    if (check[0])
    {
        calculatePoint(x + 1, y);
    }

    if (check[1])
    {
        calculatePoint(x - 1, y);
    }

    if (check[2])
    {
        calculatePoint(x, y + 1);
    }

    if (check[3])
    {
        calculatePoint(x, y - 1);
    }
}

bool BoardDataBomb::checkCanMove(int row, int column)
{
    if (row < 0 || row >= sizeRow + 2)
        return false;
    if (column < 0 || column >= sizeColumn + 2)
        return false;
    if (arrayMap[row][column] == CellDataState::CELL_NOT_OPEN || arrayMap[row][column] == CELL_BOMB_GUESS)
        return false;
}

void BoardDataBomb::setWay(int targetY, int targetX)
{
    updatePoint();
    int ty = targetY;
    int tx = targetX;
    arrayPoint.clear();
    // arrayPoint.push_back(new Point(targetX, targetY));
    currentPoint->x = targetX;
    currentPoint->y = targetY;
    while (arrayWay[targetY][targetX]->point > 0)
    {
        arrayPoint.push_back(new PointGame(targetX, targetY));
        int oldTargetX = targetX;
        targetX        = arrayWay[targetY][targetX]->previousPoint->x;
        targetY        = arrayWay[targetY][oldTargetX]->previousPoint->y;
    }
   
}

PointGame BoardDataBomb::getFirstBomb()
{
    PointGame p = PointGame(-1, -1);
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            if (arrayCell[i][j] != CELL_BOMB_GUESS && arrayBomb[i][j] == 1)
            {
                p.x = i;
                p.y = j;
            }
        }
    }
    return p;
}

int BoardDataBomb::calculatePointExtend()
{
    int point = 0;
    for (int i = 0; i < level; i++)
    {
        point = point + configLevel[i][1];
    }
    for (int i = sizeRow - 1; i >= 0; i--)
    {
        bool open = false;
        for (int j = 0; j < sizeColumn; j++)
        {
            if (arrayCell[i][j] == CELL_OPEN)
            {
                point = point + j + 1;
                open = true;
                break;
            }
        }
        if (open)
        {
            break;
        }
    }
    return point;
}
