#include "BoardDataPika.h"
#include "../Data/GlobalData.h"
#include "Game/Utility/GameUtility.h"
#include "Engine/GlobalVar.h"
#include <Game/Logic/Constant.h>

BoardDataPika::BoardDataPika()
{
	
}

BoardDataPika::~BoardDataPika()
{
}
void BoardDataPika::reset(int level)
{
	int num = (NUM_COLUMN_PIKA - 2) * (NUM_ROW_PIKA - 2);
	int numRand = num / 2;
	vector<int> arrayRand;
	int numAnimal = 37 - (11 - level);
	if (numAnimal > 37)
		numAnimal = 37;
	if (num < 80) {
		for (int i = 0; i < numRand; i++)
		{
			int rand = (int)(GameUtility::getRandom() * 37);
			arrayRand.push_back(rand);
			arrayRand.push_back(rand);
		}
	}
	else {
		vector <int> arrayNum;
		while (arrayRand.size() < num) {
			if (arrayNum.size() == 0) {
				
				for (int i = 0; i < numAnimal; i++) {
					arrayNum.push_back(i);
				}
			}
			
			int pos = (int)(GameUtility::getRandom() * arrayNum.size());
			arrayRand.push_back(arrayNum.at(pos));
			arrayRand.push_back(arrayNum.at(pos));
			arrayNum.erase(arrayNum.begin() + pos);
		}
	}
	
	for (int i = 0; i < NUM_ROW_PIKA; i++)
		for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			arrayWay[i][j] = new WayPika();
		}
	for (int i = 0; i < BOARD_ROW_PIKA; i++)
		for (int j = 0; j < BOARD_COLUMN_PIKA; j++)
		{
			arrayBall[i][j] = -1;
		}
	for (int i = 0; i < NUM_ROW_PIKA; i++)
		for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			if (i != 0 && i != NUM_ROW_PIKA - 1 && j != 0 && j != NUM_COLUMN_PIKA - 1) {
				int pos = (int)(GameUtility::getRandom() * arrayRand.size());
				arrayBall[i][j] = arrayRand.at(pos);
				arrayRand.erase(arrayRand.begin() + pos);
			}
			else {
				arrayBall[i][j] = -1;
			}
		}
	currentPoint = new PointGame();
	oldMovePoint = new PointGame();
	resetCheck();
	if (!checkCanMove()) {
		reset(level);
	}
}


void BoardDataPika::resetLevel(int level)
{
	int num = (NUM_COLUMN_PIKA - 2) * (NUM_ROW_PIKA - 2);
	int numRand = num / 2;
	numRand = 0;

	for (int i = 0; i < NUM_ROW_PIKA; i++) {
		for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			if (game->dataLevel[level][i][j] != -1) {
				numRand = numRand + 1;
			}
		}
	}
	vector<int> arrayRand;
	for (int i = 0; i < numRand; i++)
	{
		int rand = (int)(GameUtility::getRandom() * 36);
		arrayRand.push_back(rand);
		arrayRand.push_back(rand);
	}

	for (int i = 0; i < NUM_ROW_PIKA; i++)
		for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			arrayWay[i][j] = new WayPika();
		}
	for (int i = 0; i < BOARD_ROW_PIKA; i++)
		for (int j = 0; j < BOARD_COLUMN_PIKA; j++)
		{
			arrayBall[i][j] = -1;
		}
	for (int i = 0; i < NUM_ROW_PIKA; i++)
		for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			if (game->dataLevel[level][NUM_ROW_PIKA - 1 - i][j] != -1) {
				int pos = (int)(GameUtility::getRandom() * arrayRand.size());
				arrayBall[i][j] = arrayRand.at(pos);
				arrayRand.erase(arrayRand.begin() + pos);
			}
			else {
				arrayBall[i][j] = -1;
			}
		}
	currentPoint = new PointGame();
	oldMovePoint = new PointGame();
}


void BoardDataPika::loadGame()
{
	for (int i = 0; i < NUM_ROW_PIKA; i++)
		for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			arrayWay[i][j] = new WayPika();
		}
	for (int i = 0; i < BOARD_ROW_PIKA; i++)
		for (int j = 0; j < BOARD_COLUMN_PIKA; j++)
		{
			arrayBall[i][j] = -1;
		}
	for (int i = 0; i < BOARD_ROW_PIKA * BOARD_COLUMN_PIKA; i++) {
		int row = i / BOARD_COLUMN_PIKA;
		int column = i % BOARD_COLUMN_PIKA;
		arrayBall[row][column] = game->dataPika[i];
	}
	currentPoint = new PointGame();
	oldMovePoint = new PointGame();
}

void BoardDataPika::loadGameChallenge()
{
	
}


void BoardDataPika::loadGameExtend()
{
	
}


void BoardDataPika::updatePoint(int currentX, int currentY)
{
	int i, j;

	for (i = 0; i < NUM_ROW_PIKA; i++) {
		for (j = 0; j < NUM_COLUMN_PIKA; j++) {
			arrayWay[i][j]->reset();
		}
	}
    this->arrayWay[currentY][currentX]->countBreak = 0;
    this->arrayWay[currentY][currentX]->pointSameRow = 0;
    this->arrayWay[currentY][currentX]->pointSameColumn = 0;
    this->arrayWay[currentY][currentX]->sameRow = true;
    this->arrayWay[currentY][currentX]->sameColumn = true;
    this->currentPoint->x = currentX;
    this->currentPoint->y = currentY;
	//arrayWay[currentY][currentX]->point = 0;
	currentPoint->x = currentX;
	currentPoint->y = currentY;
	calculatePoint(currentX, currentY);
    
    
}

void BoardDataPika::doUpdate(int x, int y, int dx, int dy, bool sameRow, int countBreak, int forceSameOther) {
	this->arrayWay[y + dy][x + dx]->countBreak = countBreak;
        // var dPoint;
        // if (this->arrayWay[y + dy][x + dx]->point < 0)
        //     dPoint = 100;
        // else
        //     dPoint = this->arrayWay[y + dy][x + dx]->point - this->arrayWay[y][x]->point;

        if (sameRow)
        {
            this->arrayWay[y + dy][x + dx]->previousPointRow->x = x;
            this->arrayWay[y + dy][x + dx]->previousPointRow->y = y;
            if (this->arrayWay[y][x]->sameRow)
                this->arrayWay[y + dy][x + dx]->pointSameRow = this->arrayWay[y][x]->pointSameRow + 1;
            else
                this->arrayWay[y + dy][x + dx]->pointSameRow = this->arrayWay[y][x]->pointSameColumn + 1;
        }
        else
        {
            this->arrayWay[y + dy][x + dx]->previousPointColumn->x = x;
            this->arrayWay[y + dy][x + dx]->previousPointColumn->y = y;
            if (this->arrayWay[y][x]->sameColumn)
                this->arrayWay[y + dy][x + dx]->pointSameColumn = this->arrayWay[y][x]->pointSameColumn + 1;
            else
                this->arrayWay[y + dy][x + dx]->pointSameColumn = this->arrayWay[y][x]->pointSameRow + 1;
        }
        if (sameRow)
        {
            this->arrayWay[y + dy][x + dx]->sameRow = true;
            if (forceSameOther)
                this->arrayWay[y + dy][x + dx]->sameColumn = false;
        }
        else
        {
            this->arrayWay[y + dy][x + dx]->sameColumn = true;
            if (forceSameOther)
                this->arrayWay[y + dy][x + dx]->sameRow = false;
        }
}

void BoardDataPika::calculatePoint(int x, int y) {
    bool check [4];
    for (int i = 0; i < 4; i++)
    {
        check[i] = false;
    }
    if (this->arrayWay[y][x]->sameRow) {
        // check theo huong cung mot hang
        if (x + 1 < NUM_COLUMN_PIKA) {
            if (this->arrayBall[y][x + 1] < 0 || this->arrayBall[y][x + 1] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                if (this->arrayWay[y][x + 1]->countBreak < 0 || this->arrayWay[y][x + 1]->countBreak > this->arrayWay[y][x]->countBreak) {
                    this->doUpdate(x, y, 1, 0, true, this->arrayWay[y][x]->countBreak, 1);
                    check[0] = true;
                }
                else if (this->arrayWay[y][x + 1]->countBreak == this->arrayWay[y][x]->countBreak){
                    // check xem diem ke tiep o huong cung hang thi pointSameRow co lon hon point tai diem nay khong thi moi update
                    if (this->arrayWay[y][x + 1]->sameRow) {
                        if (this->arrayWay[y][x + 1]->pointSameRow > this->arrayWay[y][x]->pointSameRow + 1) {
                            this->doUpdate(x, y, 1, 0, true, this->arrayWay[y][x]->countBreak, 0);
                            check[0] = true;
                        }
                        else {
                            // check[0] = false;
                        }
                    }
                    else {// neu khong co sameRow o diem ke tiep thi mac dinh update cho diem ke tiep
                        this->doUpdate(x, y, 1, 0, true, this->arrayWay[y][x]->countBreak, 1);
                        check[0] = true;
                    }
                }
                else {
                    // check[0] = false;
                }
            }
        }
        if (x - 1 >= 0) {
            if (this->arrayBall[y][x - 1] < 0 || this->arrayBall[y][x - 1] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                if (this->arrayWay[y][x - 1]->countBreak < 0 || this->arrayWay[y][x - 1]->countBreak > this->arrayWay[y][x]->countBreak) {
                    this->doUpdate(x, y, -1, 0, true, this->arrayWay[y][x]->countBreak, 1);
                    check[1] = true;
                }
                else if (this->arrayWay[y][x - 1]->countBreak == this->arrayWay[y][x]->countBreak){
                    // check xem diem ke tiep o huong cung hang thi pointSameRow co lon hon point tai diem nay khong thi moi update
                    if (this->arrayWay[y][x - 1]->sameRow) {
                        if (this->arrayWay[y][x - 1]->pointSameRow > this->arrayWay[y][x]->pointSameRow + 1) {
                            this->doUpdate(x, y, -1, 0, true, this->arrayWay[y][x]->countBreak, 0);
                            check[1] = true;
                        }
                        else {
                            // check[1] = false;
                        }
                    }
                    else {// neu khong co sameRow o diem ke tiep thi mac dinh update cho diem ke tiep
                        this->doUpdate(x, y, -1, 0, true, this->arrayWay[y][x]->countBreak, 1);
                        check[1] = true;
                    }
                }
                else {
                    // check[1] = false;
                }
            }
        }

            if (y + 1 < NUM_ROW_PIKA) {
                if (this->arrayBall[y + 1][x] < 0 || this->arrayBall[y + 1][x] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                    if (this->arrayWay[y + 1][x]->countBreak < 0 || this->arrayWay[y + 1][x]->countBreak > this->arrayWay[y][x]->countBreak + 1) {
                        this->doUpdate(x, y, 0, 1, false, this->arrayWay[y][x]->countBreak + 1, 1);
                        check[2] = true;
                    }
                    else if (this->arrayWay[y + 1][x]->countBreak == this->arrayWay[y][x]->countBreak + 1){
                        // check xem diem ke tiep o huong cung Cot thi pointSameColumn co lon hon point tai diem nay khong thi moi update
                        if (this->arrayWay[y + 1][x]->sameColumn) {
                            if (this->arrayWay[y + 1][x]->pointSameColumn > this->arrayWay[y][x]->pointSameColumn + 1) {
                                this->doUpdate(x, y, 0, 1, false, this->arrayWay[y][x]->countBreak + 1, 0);
                                check[2] = true;
                            }
                            else {
                                // check[2] = false;
                            }
                        }
                        else {// neu khong co sameColumn o diem ke tiep thi mac dinh update cho diem ke tiep
                            this->doUpdate(x, y, 0, 1, false, this->arrayWay[y][x]->countBreak + 1, 1);
                            check[2] = true;
                        }
                    }
                    else {
                        // check[2] = false;
                    }
                }
            }
            if (y - 1 >= 0) {
                if (this->arrayBall[y - 1][x] < 0 || this->arrayBall[y - 1][x] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                    if (this->arrayWay[y - 1][x]->countBreak < 0 || this->arrayWay[y - 1][x]->countBreak > this->arrayWay[y][x]->countBreak + 1) {
                        this->doUpdate(x, y, 0, -1, false, this->arrayWay[y][x]->countBreak + 1, 1);
                        check[3] = true;
                    }
                    else if (this->arrayWay[y - 1][x]->countBreak == this->arrayWay[y][x]->countBreak + 1){
                        // check xem diem ke tiep o huong cung Cot thi pointSameColumn co lon hon point tai diem nay khong thi moi update
                        if (this->arrayWay[y - 1][x]->sameColumn) {
                            if (this->arrayWay[y - 1][x]->pointSameColumn > this->arrayWay[y][x]->pointSameColumn + 1) {
                                this->doUpdate(x, y, 0, -1, false, this->arrayWay[y][x]->countBreak + 1, 0);
                                check[3] = true;
                            }
                            else {
                                // check[3] = false;
                            }
                        }
                        else {// neu khong co sameColumn o diem ke tiep thi mac dinh update cho diem ke tiep
                            this->doUpdate(x, y, 0, -1, false, this->arrayWay[y][x]->countBreak + 1, 1);
                            check[3] = true;
                        }
                    }
                    else {
                        // check[3] = false;
                    }
                }
            }


    }
    if (this->arrayWay[y][x]->sameColumn) {
        if (x + 1 < NUM_COLUMN_PIKA) {
            if (this->arrayBall[y][x + 1] < 0|| this->arrayBall[y][x + 1] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                if (this->arrayWay[y][x + 1]->countBreak < 0 || this->arrayWay[y][x + 1]->countBreak > this->arrayWay[y][x]->countBreak + 1) {
                    this->doUpdate(x, y, 1, 0, true, this->arrayWay[y][x]->countBreak + 1, 1);
                    check[0] = true;
                }
                else if (this->arrayWay[y][x + 1]->countBreak == this->arrayWay[y][x]->countBreak + 1){
                    // check xem diem ke tiep o huong cung hang thi pointSameRow co lon hon point tai diem nay khong thi moi update
                    if (this->arrayWay[y][x + 1]->sameRow) {
                        if (this->arrayWay[y][x + 1]->pointSameRow > this->arrayWay[y][x]->pointSameRow + 1) {
                            this->doUpdate(x, y, 1, 0, true, this->arrayWay[y][x]->countBreak + 1, 0);
                            check[0] = true;
                        }
                        else {
                            //check[0] = false;
                        }
                    }
                    else {// neu khong co sameRow o diem ke tiep thi mac dinh update cho diem ke tiep
                        this->doUpdate(x, y, 1, 0, true, this->arrayWay[y][x]->countBreak + 1, 1);
                        check[0] = true;
                    }
                }
                else {
                    // check[0] = false;
                }
            }
        }
        if (x - 1 >= 0) {
            if (this->arrayBall[y][x - 1] < 0|| this->arrayBall[y][x -1] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                if (this->arrayWay[y][x - 1]->countBreak < 0 || this->arrayWay[y][x - 1]->countBreak > this->arrayWay[y][x]->countBreak + 1) {
                    this->doUpdate(x, y, -1, 0, true, this->arrayWay[y][x]->countBreak + 1, 1);
                    check[1] = true;
                }
                else if (this->arrayWay[y][x - 1]->countBreak == this->arrayWay[y][x]->countBreak + 1){
                    // check xem diem ke tiep o huong cung hang thi pointSameRow co lon hon point tai diem nay khong thi moi update
                    if (this->arrayWay[y][x - 1]->sameRow) {
                        if (this->arrayWay[y][x - 1]->pointSameRow > this->arrayWay[y][x]->pointSameRow + 1) {
                            this->doUpdate(x, y, -1, 0, true, this->arrayWay[y][x]->countBreak + 1, 0);
                            check[1] = true;
                        }
                        else {
                            // check[1] = false;
                        }
                    }
                    else {// neu khong co sameRow o diem ke tiep thi mac dinh update cho diem ke tiep
                        this->doUpdate(x, y, -1, 0, true, this->arrayWay[y][x]->countBreak + 1, 1);
                        check[1] = true;
                    }
                }
                else {
                    // check[1] = false;
                }
            }
        }
        if (y + 1 < NUM_ROW_PIKA) {
            if (this->arrayBall[y + 1][x] < 0|| this->arrayBall[y + 1][x] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                if (this->arrayWay[y + 1][x]->countBreak < 0 || this->arrayWay[y + 1][x]->countBreak > this->arrayWay[y][x]->countBreak) {
                    this->doUpdate(x, y, 0, 1, false, this->arrayWay[y][x]->countBreak, 1);
                    check[2] = true;
                }
                else if (this->arrayWay[y + 1][x]->countBreak == this->arrayWay[y][x]->countBreak){
                    // check xem diem ke tiep o huong cung Cot thi pointSameColumn co lon hon point tai diem nay khong thi moi update
                    if (this->arrayWay[y + 1][x]->sameColumn) {
                        if (this->arrayWay[y + 1][x]->pointSameColumn > this->arrayWay[y][x]->pointSameColumn + 1) {
                            this->doUpdate(x, y, 0, 1, false, this->arrayWay[y][x]->countBreak, 0);
                            check[2] = true;
                        }
                        else {
                            // check[2] = false;
                        }
                    }
                    else {// neu khong co sameColumn o diem ke tiep thi mac dinh update cho diem ke tiep
                        this->doUpdate(x, y, 0, 1, false, this->arrayWay[y][x]->countBreak, 1);
                        check[2] = true;
                    }
                }
                else {
                    // check[2] = false;
                }
            }
        }
        if (y - 1 >= 0) {
            if (this->arrayBall[y - 1][x] < 0|| this->arrayBall[y - 1][x] == this->arrayBall[this->currentPoint->y][this->currentPoint->x]) {
                if (this->arrayWay[y - 1][x]->countBreak < 0 || this->arrayWay[y - 1][x]->countBreak > this->arrayWay[y][x]->countBreak) {
                    this->doUpdate(x, y, 0, -1, false, this->arrayWay[y][x]->countBreak, 1);
                    check[3] = true;
                }
                else if (this->arrayWay[y - 1][x]->countBreak == this->arrayWay[y][x]->countBreak){
                    // check xem diem ke tiep o huong cung Cot thi pointSameColumn co lon hon point tai diem nay khong thi moi update
                    if (this->arrayWay[y - 1][x]->sameColumn) {
                        if (this->arrayWay[y - 1][x]->pointSameColumn > this->arrayWay[y][x]->pointSameColumn + 1) {
                            this->doUpdate(x, y, 0, -1, false, this->arrayWay[y][x]->countBreak, 0);
                            check[3] = true;
                        }
                        else {
                            // check[3] = false;
                        }
                    }
                    else {// neu khong co sameColumn o diem ke tiep thi mac dinh update cho diem ke tiep
                        this->doUpdate(x, y, 0, -1, false, this->arrayWay[y][x]->countBreak, 1);
                        check[3] = true;
                    }
                }
                else {
                    // check[3] = false;
                }
            }
        }
    }

	if (check[0] && arrayBall[y][x + 1] < 0) {
		calculatePoint(x + 1, y);
	}

	if (check[1] && arrayBall[y][x - 1] < 0) {
		calculatePoint(x - 1, y);
	}

	if (check[2] && arrayBall[y + 1][x] < 0) {
		calculatePoint(x, y + 1);
	}

	if (check[3] && arrayBall[y - 1][x] < 0) {
		calculatePoint(x, y - 1);
	}
}

void BoardDataPika::updateValue(int row, int column, int value) {
	arrayBall[row][column] = value;
}

vector<PointGame*> BoardDataPika::getListBall(int row, int column) {

	vector<PointGame*> result1;
	return result1;
}

bool BoardDataPika::checkExist(PointGame* value, vector<PointGame*> array2) {
	for (int i = 0; i < array2.size(); i++) {
		if (value->x == array2.at(i)->x && value->y == array2.at(i)->y) {
			return true;
		}
	}

	return false;
}

bool BoardDataPika::checkEndGame() {
	return true;
}

bool BoardDataPika::checkCanMove(int row, int column, int countBreak, bool sameRow) {
	if (sameRow)
	{
		if (arrayWay[row][column]->sameRow)
		{
			if (arrayWay[row][column]->countBreak <= 2)
				return true;
			else return false;
		}
		else
		{
			if (arrayWay[row][column]->countBreak <= 1)
				return true;
			else return false;
		}
	}
	else
	{
		if (arrayWay[row][column]->sameRow == false)
		{
			if (arrayWay[row][column]->countBreak <= 2)
				return true;
			else return false;
		}
		else
		{
			if (arrayWay[row][column]->countBreak <= 1)
				return true;
			else return false;
		}
	}

}


bool BoardDataPika::checkSameId(PointGame* point) {
	// TODO Auto-generated method stub
	if (arrayBall[point->y][point->x] == arrayBall[currentPoint->y][currentPoint->x])
		return true;
	return false;
}
vector <PointGame*> BoardDataPika::getWay(PointGame* point)
{
	vector<PointGame*> way;
	way.push_back(point);
	bool sameRow;
	if (abs(point->x - currentPoint->x) + abs(point->y - currentPoint->y) == 1)
	{
		way.push_back(currentPoint);
	}
	else
	{

		sameRow = arrayWay[point->y][point->x]->sameRow;
		PointGame* cPoint = point;
		PointGame* nextPoint = sameRow ? arrayWay[point->y][point->x]->previousPointRow : arrayWay[point->y][point->x]->previousPointColumn;
		while (nextPoint->y != currentPoint->y || nextPoint->x != currentPoint->x)
		{
			if (arrayWay[nextPoint->y][nextPoint->x]->sameColumn && arrayWay[nextPoint->y][nextPoint->x]->sameRow)
			{
				if (cPoint->x == nextPoint->x)
				{
					cPoint = nextPoint;
					nextPoint = arrayWay[nextPoint->y][nextPoint->x]->previousPointColumn;
				}
				else
				{
					cPoint = nextPoint;
					nextPoint = arrayWay[nextPoint->y][nextPoint->x]->previousPointRow;
				}

				//way.push_back(nextPoint);
			}
			else if (arrayWay[nextPoint->y][nextPoint->x]->sameColumn)
			{
				cPoint = nextPoint;
				nextPoint = arrayWay[nextPoint->y][nextPoint->x]->previousPointColumn;
				if (sameRow)
				{
					way.push_back(cPoint);
					sameRow = false;
				}
			}
			else
			{
				cPoint = nextPoint;
				nextPoint = arrayWay[nextPoint->y][nextPoint->x]->previousPointRow;
				if (sameRow == false)
					way.push_back(cPoint);
				sameRow = true;
			}

		}
		way.push_back(currentPoint);
	}
	return way;
}
bool BoardDataPika::checkCanEat(PointGame* point)
{
	if (checkSameId(point))
	{

		if (abs(point->x - currentPoint->x) + abs(point->y - currentPoint->y) == 1)
		{

			oldMovePoint->y = point->y;
			oldMovePoint->x = point->x;
			return true;
		}
		else
		{
			return arrayWay[point->y][point->x]->countBreak >= 0 && arrayWay[point->y][point->x]->countBreak <= 2;
		}
	}

	return false;
}

void BoardDataPika::resetCheck()
{
	for (int i = 0; i < NUM_ROW_PIKA; i++)
	for (int j = 0; j < NUM_COLUMN_PIKA; j++)
	{
		arrayCheck[i][j] = false;
	}
}

bool BoardDataPika::checkCanMove()
{

	for (int i = 0; i < NUM_ROW_PIKA; i++)
	for (int j = 0; j < NUM_COLUMN_PIKA; j++)
	{
		if (arrayBall[i][j] >= 0 && arrayCheck[i][j] == false)
		{
			oldMovePoint->x = j;
			oldMovePoint->y = i;

			updatePoint(oldMovePoint->x, oldMovePoint->y);
			for (int i1 = 0; i1 < NUM_ROW_PIKA; i1++)
			for (int j1 = 0; j1 < NUM_COLUMN_PIKA; j1++)
			{
				if ((oldMovePoint->x != j1 || oldMovePoint->y != i1) && checkCanEat(new PointGame(j1, i1)))
					return true;
			}
			//return checkCanMove();
		}
	}
	return false;
}

vector<PointGame*> BoardDataPika::getMovePoint()
{
    vector<PointGame*> arrayPoint;
    for (int i = 0; i < NUM_ROW_PIKA; i++)
    for (int j = 0; j < NUM_COLUMN_PIKA; j++)
    {
        if (arrayBall[i][j] >= 0 && arrayCheck[i][j] == false)
        {
            oldMovePoint->x = j;
            oldMovePoint->y = i;

            updatePoint(oldMovePoint->x, oldMovePoint->y);
            for (int i1 = 0; i1 < NUM_ROW_PIKA; i1++)
            for (int j1 = 0; j1 < NUM_COLUMN_PIKA; j1++)
            {
                
                if ((oldMovePoint->x != j1 || oldMovePoint->y != i1) && checkCanEat(new PointGame(j1, i1))){
                    arrayPoint.push_back(new PointGame(j1, i1));
                    arrayPoint.push_back(new PointGame(j, i));
                    return arrayPoint;
                }
                    
            }
            //return checkCanMove();
        }
    }
    return arrayPoint;
}

void BoardDataPika::newData(int level) {
	// TODO Auto-generated method stub
	int numRand = 0;
	for (int i = 0; i < NUM_ROW_PIKA; i++)
	for (int j = 0; j < NUM_COLUMN_PIKA; j++)
	{
		if (arrayBall[i][j] >= 0)
		{
			numRand++;
		}
	}
	numRand = numRand / 2;
	vector<int> arrayRand;
	int numAnimal = 37 - (11 - level);
	if (numAnimal > 37)
		numAnimal = 37;
	if (numRand * 2 < 80) {
		for (int i = 0; i < numRand; i++)
		{
			int rand = (int)(GameUtility::getRandom() * 37);
			arrayRand.push_back(rand);
			arrayRand.push_back(rand);
		}
	}
	else {
		vector <int> arrayNum;
		while (arrayRand.size() < numRand * 2) {
			if (arrayNum.size() == 0) {
				
				for (int i = 0; i < numAnimal; i++) {
					arrayNum.push_back(i);
				}
			}
			int pos = (int)(GameUtility::getRandom() * arrayNum.size());
			arrayRand.push_back(arrayNum.at(pos));
			arrayRand.push_back(arrayNum.at(pos));
			arrayNum.erase(arrayNum.begin() + pos);
		}
	}
	
	for (int i = 0; i < NUM_ROW_PIKA; i++)
		for (int j = 0; j < NUM_COLUMN_PIKA; j++)
		{
			if (arrayBall[i][j] >= 0)
			{
				int pos = (int)(GameUtility::getRandom() * arrayRand.size());
				arrayBall[i][j] = arrayRand.at(pos);
				arrayRand.erase(arrayRand.begin() + pos);
			}
		}
	if (checkCanMove() == false)
	{
		newData(level);
	}

}

bool BoardDataPika::checkEnd()
{
	for (int i = 0; i < NUM_ROW_PIKA; i++)
	for (int j = 0; j < NUM_COLUMN_PIKA; j++)
	{
		if (arrayBall[i][j] != -1)
			return false;
	}
	return true;

}
