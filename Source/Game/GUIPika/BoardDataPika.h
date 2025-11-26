#pragma once
#include "Game/Logic/PointGame.h"
#include <vector>
#include "WayPika.h"
#include "axmol.h"
#ifndef BoardDataPika_h__
#define BoardDataPika_h__
using namespace std;

#define BOARD_ROW_PIKA 13
#define BOARD_COLUMN_PIKA 23

class BoardDataPika
{
public:
	BoardDataPika();
	~BoardDataPika();

	int arrayBall[BOARD_ROW_PIKA][BOARD_COLUMN_PIKA];
	WayPika* arrayWay[BOARD_ROW_PIKA][BOARD_COLUMN_PIKA];
	vector<PointGame*> arrayPoint;
	vector<PointGame*> result; // mang ghi cac bong an diem

	PointGame* currentPoint;
	PointGame* oldMovePoint;
	bool arrayCheck[BOARD_ROW_PIKA][BOARD_COLUMN_PIKA];
	void reset(int level);
	void resetLevel(int level);
	void loadGame();
	void loadGameExtend();
	void loadGameChallenge();
	void updatePoint(int currentX, int currentY);
	void doUpdate(int x, int y, int dx, int dy, bool sameRow, int countBreak, int forceSameOther);
	void calculatePoint(int x, int y);
	void updateValue(int row, int column, int value);
	vector<PointGame*> getListBall(int row, int column);
	bool checkExist(PointGame* value, vector<PointGame*> array2);
	bool checkEndGame();
	bool checkCanMove(int row, int column, int countBreak, bool sameRow);
	bool checkCanMove();
	bool checkSameId(PointGame* point);
	vector <PointGame*> getWay(PointGame* point);
	bool checkCanEat(PointGame* point);
	void resetCheck();
	void newData(int level);
	bool checkEnd();
    vector <PointGame*> getMovePoint();
};

#endif // BoardDataPika_h__

