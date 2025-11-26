#pragma once
#include "../Logic/Way.h"
#include <vector>
#include "../Logic/PointGame.h"
#include "axmol.h"
using namespace std;

#define BOARD_ROW_POP 10
#define BOARD_COLUMN_POP 10
#define LIMIT_SIZE_POP 9
#define NUM_SPECIAL 10000

enum BoardType
{
    POP_TYPE_NORMAL,
    POP_TYPE_HARD
};
class BoardDataPop
{
public:
	BoardDataPop(void);
	~BoardDataPop(void);

	vector <int> arrayNewBall;
	vector <int> arrayNewBallGen;
	vector <PointGame*> arrayNewPos;
	int arrayBall[BOARD_ROW_POP][BOARD_COLUMN_POP];
	int arrayMap[BOARD_ROW_POP][BOARD_COLUMN_POP];
	Way* arrayWay[BOARD_ROW_POP][BOARD_COLUMN_POP];
	vector<int> arrayEmpty;
	vector<PointGame*> arrayPoint;
	vector<PointGame*> arrayMoveEnd;
	vector<PointGame*> arrayMoveBegin;
	PointGame* currentPoint;
	int maxNum;
	int currentSize;
    int countToGen;
    BoardType type;
    

	void reset();
	void newGame();
    PointGame getCanTouchPoint();
	void loadGame();
	void loadCurrentSize();
	void updatePoint(int currentX, int currentY);
	void calculatePoint(int x, int y);
	void setWay(int targetY, int targetX);
	bool updateValueCurrent();
	vector<PointGame*> getListBall(int row, int column);
	bool checkExist(PointGame* value, vector<PointGame*> array2) ;
	bool checkNoMove();
	bool checkEndGame();
	bool checkNewBall();
	int getNumBall();
	void renewBall();
	int genBall();
    int getNumSpecial();
    PointGame getPosDestroy(int num);
};

