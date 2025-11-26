#include "BoardData.h"
#include "Engine/GlobalVar.h"
#include "../Utility/GameUtility.h"
#include <Game/Utility/JNIUtils.h>


BoardData::BoardData(void)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayWay[i][j] = new Way();
			arrayBall[i][j] = 0;
		}
		currentPoint = new PointGame();
}


BoardData::~BoardData(void)
{
}

void BoardData:: reset() {
	arrayEmpty.clear();
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayBall[i][j] = 0;
			arrayEmpty.push_back(i * 9 + j);
		}
}

void BoardData:: newGame() {
	reset();
	// random 5 vien to

    int _array[81] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 3, 3, 3, -1, -1, -1,
        1, 1, 1, -1, 7, -1, -1, -1, -1,
        1, 1, 1, -1, -1, 5, -1, -1, -1,
        1, 1, 1, -1, 5, 7, -1, -1, -1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    /* int _array[81] = {
        1, 2, 5, 4, 1, 2, 3, 1, 4,
        2, 4, 1, 6, 4, 3, 6, 4, 5,
        4, 3, 5, 6, 1, 2, 5, 7, 1,
        6, 5, 4, 3, 2, 1, 1, 5, 6,
        1, 3, 2, 4, -1, 3, 2, 4, -1,
        3, 2, 1, 5, 2, 4, 5, 6, 1,
        1, 11, 1, 3, 2, 5, 12, 5, 3,
        2, 3, 5, 4, -1, 1, 2, 3, 4,
        1, 2, 3, 4, 5, 6, 7, 10, 1
    };*/

	for (int i = 0; i < 5; i++) {
		int rand, row, column, color, oldRand;
		oldRand = rand = (int) (GameUtility::getRandom() * arrayEmpty.size() * 0.99999f);
		rand = arrayEmpty.at(rand);
		arrayEmpty.erase(arrayEmpty.begin() + oldRand);
		row = rand / 9;
		column = rand % 9;
		color = 1 + (int) (GameUtility::getRandom() * 6.999999f);
		arrayBall[row][column] = color;
	}

	// random 3 vien nho
	randomNext();
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
              //  arrayBall[i][j] = _array[i * 9 + j];
            }
}

void BoardData:: loadGame() {
	reset();
    /* int _array[81] = {
        1, 2, 5, 4, 1, 2, 3, 1, 4,
        2, 4, 1, 6, 4, 3, 6, 4, 5,
        6, 5, 4, 3, 2, 1, 1, 5, 6,
        6, 5, 4, 3, 2, 1, 1, 5, 6,
        1, 3, 2, 4, -1, 3, 2, 4, -1,
        3, 2, 1, 5, 2, 4, 5, 6, 1,
        1, 11, 1, 3, 2, 5, 12, 5, 3,
        2, 3, 5, 4, -1, 1, 2, 3, 4,
        1, 2, 3, 4, 5, 6, 7, 10, 1
    };*/
     int _array[81] = {
        7, 5, 6, 7, 3, 1, 13, 3, 7,
        4, 1, 3, 1, -1, 6, 5, 2, 1,
        1, 14, 4, 3, 3, 2, 10, 2, 5,
        2, 5, 4, 1, 4, 4, 6, 7, 7,
        6, 6, 7, 5, -1, 4, 3, 4, -1,
        6, 1, 3, 1, 7, 5, 5, 7, 2,
        4, 5, 6, 3, 7, 3, 4, 4, 1,
        1, 7, 1, 4, 6, 2, 5, 2, 5,
        7, 3, 6, 6, 5, 2, 3, 3, 5
    };
	for (int i = 0; i < 81; i++) {
		int row = i / 9;
		int column = i % 9;
      //  game->data[i] = _array[i];
		if (game->data[i] > 14) {
			game->data[i] = 0;
		}
		arrayBall[row][column] = game->data[i];

		if (game->data[i] > 0)
			for (int j = 0; j < arrayEmpty.size(); j++) {
				if (i == arrayEmpty.at(j))
					arrayEmpty.erase(arrayEmpty.begin()+j);
			}
	}
}


void BoardData::loadGameData(int _data[81]) {
	reset();
	for (int i = 0; i < 81; i++) {
		int row = i / 9;
		int column = i % 9;
		if (_data[i] > 14)
			_data[i] = 0;
		arrayBall[row][column] = _data[i];
		if (_data[i] > 0)
			for (int j = 0; j < arrayEmpty.size(); j++) {
				if (i == arrayEmpty.at(j))
					arrayEmpty.erase(arrayEmpty.begin() + j);
			}
	}
}

void BoardData:: loadGameTime() {
	reset();
	
}

void BoardData::loadGameBattle(vector <int> data) {
	reset();
	for (int i = 0; i < data.size(); i++) {
		int row = data.at(i) / 9;
		int column = data.at(i) % 9;
		arrayBall[row][column] = data.at(i + 1);
		i = i + 1;
	}
}

void BoardData::loadGame(int arrayData[9][9]) {
	reset();
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			arrayBall[i][j] = arrayData[i][j];
			if (arrayBall[i][j] > 14) {
				arrayBall[i][j] = 0;
			}

			if (arrayBall[i][j] > 0)
			{
				for (int k = 0; k < arrayEmpty.size(); k++) {
					if ((i * 9 + j) == arrayEmpty.at(k))
					{
						arrayEmpty.erase(arrayEmpty.begin()+k);
						break;
					}
				}
			}
		}
}

void BoardData::randomArrayNext()
{
	vector <int> arrayEmpty1;
	for (int i = 0; i < arrayEmpty.size(); i++) {
		arrayEmpty1.push_back(arrayEmpty.at(i));
	}
	for (int i = 0; i < 4; i++) {
		if (arrayEmpty1.size() == 0)
			return;
		int rand, row, column, color, oldRand;
		oldRand = rand = (int)(GameUtility::getRandom() * arrayEmpty1.size() * 0.999999f);
		rand = arrayEmpty1.at(rand);
		arrayEmpty1.erase(arrayEmpty1.begin() + oldRand);
		row = rand / 9;
		column = rand % 9;
		if (i == 3) {
			// random bong thay the vi tri bong nho bi de vao
			posReplace = rand;
		}
		else {
			color = 8 + (int)(GameUtility::getRandom() * 6.9999999f);
			if (color <= 8)
				color = 8;
			if (color >= 15)
				color = 14;
			arrayPosNext[i] = rand;
			arrayIdNext[i] = color;
			//arrayBall[row][column] = color;
		}
		
	}
}

void BoardData::randomNextBattle()
{
	for (int i = 0; i < 3; i++) {
		if (arrayPosNext[i] >= 0) {
			for (int j = 0; j < arrayEmpty.size(); j++) {
				if (arrayEmpty.at(j) == arrayPosNext[i]) {
					arrayEmpty.erase(arrayEmpty.begin() + j);
				}
			}
			int row, column;
			int rand = arrayPosNext[i];
			row = rand / 9;
			column = rand % 9;
			arrayBall[row][column] = arrayIdNext[i];
		}
	}
}

void BoardData::randomReplaceBattle(int color)
{
	if (posReplace >= 0) {
		for (int j = 0; j < arrayEmpty.size(); j++) {
			if (arrayEmpty.at(j) == posReplace) {
				arrayEmpty.erase(arrayEmpty.begin() + j);
			}
		}
		int row, column;
		int rand = posReplace;
		row = rand / 9;
		column = rand % 9;
		arrayBall[row][column] = color;
	}
}

void BoardData:: randomNext() {
	for (int i = 0; i < 3; i++) {
		if (arrayEmpty.size() == 0)
			return;
		int rand, row, column, color, oldRand;
		oldRand = rand = (int) (GameUtility::getRandom() * arrayEmpty.size() * 0.999999f);
		rand = arrayEmpty.at(rand);
		if (game->showHelp && game->countHelp > 0) {
			if (rand == 40 || rand == 44 || rand == 13) {
				i--;
				continue;
			}
		}
		arrayEmpty.erase(arrayEmpty.begin() + oldRand);
		row = rand / 9;
		column = rand % 9;
        float maxValue = 6.999999f;
        if (game->highscore < 20)
            maxValue = 3.999999f;
        else if (game->highscore < 40)
            maxValue = 4.999999f;
        else if (game->highscore < 70)
            maxValue = 5.999999f;
		color = 8 + (int) (GameUtility::getRandom() * maxValue);
		if (color <= 8)
			color = 8;
		if (color >= 15)
			color = 14;
		arrayBall[row][column] = color;
	}
}

void BoardData:: randomReplace(int color) {
	if (arrayEmpty.size() == 0)
		return;
	int rand, row, column, oldRand;
	oldRand = rand = (int) (GameUtility::getRandom() * arrayEmpty.size() * 0.999999f);
	rand = arrayEmpty.at(rand);
	arrayEmpty.erase(arrayEmpty.begin()+oldRand);
	row = rand / 9;
	column = rand % 9;
	arrayBall[row][column] = color;
}

void BoardData:: updatePoint(int currentX, int currentY) {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			arrayWay[i][j]->reset();
		}
	}

	arrayWay[currentY][currentX]->point = 0;
	currentPoint->x = currentX;
	currentPoint->y = currentY;
	calculatePoint(currentX, currentY);
}

void BoardData:: calculatePoint(int x, int y) {

	bool check[4];
	for(int i = 0; i < 4; i++)
		check[i] = false;

	if(x < 0 || x >= 9)
		return;
	if(y < 0 || y >= 9)
		return;

	if (x + 1 < 9) {
		if (arrayWay[y][x + 1]->point == -1 || arrayWay[y][x + 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y][x + 1] < BIG_PINK || arrayBall[y][x + 1] > BIG_YELLOW) {
				arrayWay[y][x + 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x + 1]->previousPoint->x = x;
				arrayWay[y][x + 1]->previousPoint->y = y;
				check[0] = true;
			}
		}
	}

	if (x - 1 >= 0) {
		if (arrayWay[y][x - 1]->point == -1 || arrayWay[y][x - 1]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y][x - 1] < BIG_PINK || arrayBall[y][x - 1] > BIG_YELLOW) {
				arrayWay[y][x - 1]->point = arrayWay[y][x]->point + 1;
				arrayWay[y][x - 1]->previousPoint->x = x;
				arrayWay[y][x - 1]->previousPoint->y = y;

				check[1] = true;
			}
		}

	}

	if (y + 1 < 9) {
		if (arrayWay[y + 1][x]->point == -1 || arrayWay[y + 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y + 1][x] < BIG_PINK || arrayBall[y + 1][x] > BIG_YELLOW) {

				arrayWay[y + 1][x]->point = arrayWay[y][x]->point + 1;
				arrayWay[y + 1][x]->previousPoint->x = x;
				arrayWay[y + 1][x]->previousPoint->y = y;

				check[2] = true;

			}
		}

	}

	if (y - 1 >= 0) {
		if (arrayWay[y - 1][x]->point == -1 || arrayWay[y - 1][x]->point - 1 > arrayWay[y][x]->point) {
			if (arrayBall[y - 1][x] < BIG_PINK || arrayBall[y - 1][x] > BIG_YELLOW) {
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

void BoardData:: setWay(int targetY, int targetX) {
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

void BoardData:: updateValue(int row, int column, int value) {
	if (arrayBall[row][column] <= 0) {
		if (value > 0) {
			for (int i = 0; i < arrayEmpty.size(); i++) {
				if ((int) arrayEmpty.at(i) == row * 9 + column) {

					arrayEmpty.erase(arrayEmpty.begin()+i);
				}
			}
		}
	} else {
		if (value < 0) {
			arrayEmpty.push_back(row * 9 + column);
		}
	}
	arrayBall[row][column] = value;
}

vector<PointGame*> BoardData::getListBall(int row, int column) {

	vector<PointGame*> result1 ;

	// check hang ngang
	result1.clear();
	result1.push_back(new PointGame(column, row));
	for (int i = column + 1; i < 9; i++) {
		if (arrayBall[row][i] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(i, row));
	}
	for (int i = column - 1; i >= 0; i--) {
		if (arrayBall[row][i] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(i, row));
	}

	if (result1.size() >= 5) {
		for (int i = 0; i < result1.size(); i++) {
			if (!checkExist(result1.at(i), result)) {
				result.push_back(result1.at(i));
			}
		}
	}

	// check hang doc
	result1.clear();
	result1.push_back(new PointGame(column, row));
	for (int i = row + 1; i < 9; i++) {
		if (arrayBall[i][column] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(column, i));
	}
	for (int i = row - 1; i >= 0; i--) {
		if (arrayBall[i][column] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(column, i));
	}

	if (result1.size() >= 5) {
		for (int i = 0; i < result1.size(); i++) {
			if (!checkExist(result1.at(i), result)) {
				result.push_back(result1.at(i));
			}
		}
	}

	// check hang cheo tu cao xuong thap
	result1.clear();
	result1.push_back(new PointGame(column, row));
	for (int i = 1; column - i >= 0 && row + i < 9; i++) {
		if (arrayBall[row + i][column - i] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(column - i, row + i));
	}
	for (int i = 1; column + i < 9 && row - i >= 0; i++) {
		if (arrayBall[row - i][column + i] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(column + i, row - i));
	}

	if (result1.size() >= 5) {
		for (int i = 0; i < result1.size(); i++) {
			if (!checkExist(result1.at(i), result)) {
				result.push_back(result1.at(i));
			}
		}
	}

	// check hang cheo tu thap len cao
	result1.clear();
	result1.push_back(new PointGame(column, row));
	for (int i = 1; column - i >= 0 && row - i >= 0; i++) {
		if (arrayBall[row - i][column - i] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(column - i, row - i));
	}
	for (int i = 1; column + i < 9 && row + i < 9; i++) {
		if (arrayBall[row + i][column + i] != arrayBall[row][column])
			break;
		result1.push_back(new PointGame(column + i, row + i));
	}

	if (result1.size() >= 5) {
		for (int i = 0; i < result1.size(); i++) {
			if (!checkExist(result1.at(i), result)) {
				result.push_back(result1.at(i));
			}
		}
	}
	return result1;
}

bool BoardData::checkExist(PointGame *value, vector<PointGame*> array2) {
	for (int i = 0; i < array2.size(); i++) {
		if (value->x == array2.at(i)->x && value->y == array2.at(i)->y) {
			return true;
		}
	}

	return false;
}

bool BoardData::checkEndGame() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (arrayBall[i][j] > 7 || arrayBall[i][j] < 1)
				return false;
		}
		return true;
}

bool BoardData::checkNewBall()
{
	if (arrayNewBall.size() > 0) {
		for (int i = 0; i < arrayNewBall.size(); i++) {
			if (arrayEmpty.size() == 0)
				return true;
			int rand, row, column, color, oldRand;
			oldRand = rand = (int)(GameUtility::getRandom() * arrayEmpty.size() * 0.99999f);
			rand = arrayEmpty.at(rand);
			arrayEmpty.erase(arrayEmpty.begin() + oldRand);
			row = rand / 9;
			column = rand % 9;
			
			arrayBall[row][column] = arrayNewBall.at(i);
			PointGame* p = new PointGame();
			p->y = row;
			p->x = column;
			arrayNewPos.push_back(p);
			arrayNewBallGen.push_back(arrayNewBall.at(i));
			arrayBall[row][column] = arrayNewBall.at(i);
		}
		arrayNewBall.clear();
		return true;
	}
	return false;
}


void BoardData::printBoard()
{
	string s = "";
	for (int i = 0; i < 9; i++) {
		s = "";
		for (int j = 0; j < 9; j++) {
			s = s + " " + GameUtility::toString(arrayBall[i][j]);
		}
		AXLOGD("%s", s.c_str());
	}
}

void BoardData::newGameTutorial() {
	reset();
	// random 5 vien to
	int arrayColor[17]  = {3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 1, 5, 9, 10, 11 };
	int arrayRow[17]    = {4, 4, 4, 4, 8, 8, 7, 6, 5, 2, 0, 0, 1, 2, 3, 8, 7};
	int arrayColumn[17] = {0, 1, 2, 3, 1, 3, 4, 5, 6, 7, 0, 2, 1, 0, 7, 8, 0 };

     int _array[81] = {
        12, 0, 3, 2, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 2, 2, 2, 2,
        0, 0, 0, 0, 0, 0, 0, 3, 0,
        0, 1, 0, 0, 0, 0, 0, 3, 3,
        4, 0, 0, 0, 0, 0, 0, 0, 10,
        4, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 10,
        0, 0, 3, 0, 0, 0, 1, 0, 0,
        0, 4, 0, 0, 4, 0, 0, 1, 0
    };
	for (int i = 0; i < 81; i++) {
		int row = i / 9;
		int column = i % 9;
        game->data[i] = _array[i];
		
		arrayBall[row][column] = game->data[i];

		if (game->data[i] > 0)
			for (int j = 0; j < arrayEmpty.size(); j++) {
				if (i == arrayEmpty.at(j))
					arrayEmpty.erase(arrayEmpty.begin()+j);
			}
	}


	/*for (int i = 0; i < 17; i++) {
		int rand, row, column, color, oldRand;
		row = arrayRow[i];
		column = arrayColumn[i];
		int value = arrayRow[i] * 9 + arrayColumn[i];
		for (int j = 0; j < arrayEmpty.size(); j++) {
			if (arrayEmpty.at(j) == value) {
				arrayEmpty.erase(arrayEmpty.begin() + j);
				break;
			}
		}
		arrayBall[row][column] = arrayColor[i];
	}*/
}

void BoardData::getMovePoint()
{
	AXLOGD("GET MOVE POINT ***** ");
	printBoard();
	int maxPoint = 0;
	vector <PointGame> arrayStartPoint;
	vector <PointGame> arrayTargetPoint;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (arrayBall[i][j] < 8 && arrayBall[i][j] > 0) {
				// tim diem ma no co the di chuyen den
				updatePoint(j, i);
				int mPoint = 0;
				int savePoint = getPointBall(i, j, arrayBall[i][j], false, 0);
				PointGame targetPoint;
				for (int i1 = 0; i1 < 9; i1++) {
					for (int j1 = 0; j1 < 9; j1++) {
						if ((i != i1 || j != j1) && (arrayBall[i1][j1] <= 0 || arrayBall[i1][j1] >= 8)) {
							setWay(i1, j1);
							if (arrayPoint.size() > 0) {
								// co the di duoc den diem nay, tim so luong bong ma diem nay connect
								int saveId = arrayBall[i][j];
								arrayBall[i][j] = -1;
								int point = getPointBall(i1, j1, saveId, true, savePoint);
								arrayBall[i][j] = saveId;
								if (point > mPoint) {
									mPoint = point;
									targetPoint.x = i1;
									targetPoint.y = j1;
								}
							}
						}
					}
				}
				PointGame startPoint;
				startPoint.x = i;
				startPoint.y = j;
				if (mPoint == maxPoint) {
					arrayStartPoint.push_back(startPoint);
					arrayTargetPoint.push_back(targetPoint);
				}
				else if (mPoint > maxPoint) {
					arrayTargetPoint.clear();
					arrayStartPoint.clear();
					arrayStartPoint.push_back(startPoint);
					arrayTargetPoint.push_back(targetPoint);
					maxPoint = mPoint;
				}
			}
		}
	}
	// trong so nhung diem co kha nang nhat de di chuyen, tim diem it ket noi nhat
	int minPoint = 1000;
	int index;
	for (int i = 0; i < arrayStartPoint.size(); i++) {
		int point = getPointBall(arrayStartPoint[i].x, arrayStartPoint[i].y, arrayBall[arrayStartPoint[i].x][arrayStartPoint[i].y], false, 0);
		if (point < minPoint) {
			minPoint = point;
			index = i;
		}
	}
	startPoint = arrayStartPoint[index];
	endPoint = arrayTargetPoint[index];
}

/**
 * checkSavePoint: kiem tra xem co can phai check Point moi cua no so voi last Point san co tai diem nay khong
 */
int BoardData::getPointBall(int row, int column, int id, bool checkSavePoint, int savePoint)
{
	int maxPoint = 0;
	int point = 1;
	// check hang ngang
	// check xem co du 5 o duoc khong
	int count = 0;
	for (int i = column + 1; i < 9; i++) {
		if (arrayBall[row][i] != id && arrayBall[row][i] > 0)
			break;
		count++;
	}
	for (int i = column - 1; i >= 0; i--) {
		if (arrayBall[row][i] != id && arrayBall[row][i] > 0)
			break;
		count++;
	}
	
	if (count >= 4) {
		for (int i = column + 1; i < 9; i++) {
			if (arrayBall[row][i] != id)
				break;
			point++;
		}
		for (int i = column - 1; i >= 0; i--) {
			if (arrayBall[row][i] != id)
				break;
			point++;
		}

		if (point > maxPoint) {
			if (checkSavePoint) {
				if (point > savePoint)
					maxPoint = point;
			}
			else {
				maxPoint = point;
			}
		}
	}

	// check hang doc
	// check xem co du 5 o duoc khong
	count = 0;
	for (int i = row + 1; i < 9; i++) {
		if (arrayBall[i][column] != id && arrayBall[i][column] > 0)
			break;
		count++;
	}
	for (int i = row - 1; i >= 0; i--) {
		if (arrayBall[i][column] != id && arrayBall[i][column] > 0)
			break;
		count++;
	}
	if (count >= 4) {
		point = 1;
		for (int i = row + 1; i < 9; i++) {
			if (arrayBall[i][column] != id)
				break;
			point++;
		}
		for (int i = row - 1; i >= 0; i--) {
			if (arrayBall[i][column] != id)
				break;
			point++;
		}
		if (point > maxPoint) {
			if (checkSavePoint) {
				if (point > savePoint)
					maxPoint = point;
			}
			else {
				maxPoint = point;
			}
		}
	}

	// check hang cheo tu cao xuong thap
	// check xem co du 5 o duoc khong
	count = 0;
	for (int i = 1; column - i >= 0 && row + i < 9; i++) {
		if (arrayBall[row + i][column - i] != id && arrayBall[row + i][column - i] > 0)
			break;
		count++;
	}
	for (int i = 1; column + i < 9 && row - i >= 0; i++) {
		if (arrayBall[row - i][column + i] != id && arrayBall[row - i][column + i] > 0)
			break;
		count++;
	}
	if (count >= 4) {
		point = 1;
		for (int i = 1; column - i >= 0 && row + i < 9; i++) {
			if (arrayBall[row + i][column - i] != id)
				break;
			point++;
		}
		for (int i = 1; column + i < 9 && row - i >= 0; i++) {
			if (arrayBall[row - i][column + i] != id)
				break;
			point++;
		}

		if (point > maxPoint) {
			if (checkSavePoint) {
				if (point > savePoint)
					maxPoint = point;
			}
			else {
				maxPoint = point;
			}
		}
	}

	// check hang cheo tu thap len cao
	count = 0;
	for (int i = 1; column - i >= 0 && row - i >= 0; i++) {
		if (arrayBall[row - i][column - i] != id && arrayBall[row - i][column - i] > 0)
			break;
		count++;
	}
	for (int i = 1; column + i < 9 && row + i < 9; i++) {
		if (arrayBall[row + i][column + i] != id && arrayBall[row + i][column + i] > 0)
			break;
		count++;
	}
	if (count >= 4) {
		point++;
		for (int i = 1; column - i >= 0 && row - i >= 0; i++) {
			if (arrayBall[row - i][column - i] != id)
				break;
			point++;
		}
		for (int i = 1; column + i < 9 && row + i < 9; i++) {
			if (arrayBall[row + i][column + i] != id)
				break;
			point++;
		}

		if (point > maxPoint) {
			if (checkSavePoint) {
				if (point > savePoint)
					maxPoint = point;
			}
			else {
				maxPoint = point;
			}
		}
	}
	return maxPoint;
}

int BoardData::getNumBall()
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

bool BoardData::checkNoBigBall()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (arrayBall[i][j] <= 7 && arrayBall[i][j] >= 1)
                return false;
        }
    return true;
}

string BoardData::getDataBall()
{
    string s = "";
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            s = s + to_string(arrayBall[i][j]) + ",";
        }
    return s;
}

void BoardData::renewBall()
{
    vector<int> arrRand;
    for (int i = 1; i < 8; i++)
    {
        for (int j = 1; j < 8; j++)
        {
            arrRand.push_back(i * 9 + j);
        }
    }
    arrRenew.clear();
    arrayEmpty.clear();
    vector<int> arrRenew1;
    for (int i = 0; i < game->numDestroy; i++)
    {
        int rand = arrRand.size() * GameUtility::getRandom() * 0.9999;
        arrRenew.push_back(arrRand.at(rand));
        arrRenew1.push_back(arrRand.at(rand));
        arrRand.erase(arrRand.begin() + rand);
    }
    for (int i = 0; i < 3; i++)
    {
        int rand  = arrRenew1.size() * GameUtility::getRandom() * 0.9999;
        int value = arrRenew1.at(rand);
        arrRenew1.erase(arrRenew1.begin() + rand);
        int row                = value / 9;
        int column             = value % 9;
        arrayBall[row][column] = 8 + (int)(GameUtility::getRandom() * 6.9999999f);
    }

    for (int i = 0; i < arrRenew1.size(); i++)
    {
        int value              = arrRenew1.at(i);
        int row                = value / 9;
        int column             = value % 9;
        arrayBall[row][column] = -1;
        arrayEmpty.push_back(value);
    }
}

void BoardData::removeBall(int row, int column)
{
    arrayBall[row][column] = -1;
    arrayEmpty.push_back(row * 9 + column);
}
