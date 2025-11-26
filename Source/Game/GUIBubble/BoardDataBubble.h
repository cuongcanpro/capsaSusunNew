#pragma once
#include "Game/Logic/Way.h"
#include <vector>
#include "Game/Logic/PointGame.h"
#include "ResultData.h"
#include "axmol.h"
using namespace std;

const int MAX_ROW = 9;
const int MAX_COLUMN = 7;
const int MAX_NEXT = 6;
class BoardDataBubble
{
public:
	BoardDataBubble(void);
	~BoardDataBubble(void);

	int arrayBall[MAX_ROW][MAX_COLUMN];
	Way* arrayWay[MAX_ROW][MAX_COLUMN];
	vector<int> arrayEmpty;
	vector<PointGame*> arrayPoint;
	vector<ResultData*> result; // mang ghi cac bong an diem
	bool arrayCheck[MAX_ROW][MAX_COLUMN];
	PointGame* currentPoint;
	int arrayNext[MAX_NEXT];
	PointGame* arrayPointNext[MAX_NEXT];
	int arrayRand[4];
	int arrayMaxNumber[5];
	int numRand;
	int level;
	int numRandStart[2];


	// tutorial Data
	int arrayBallTutorial[9][5];
	int arrayNextIdTutorial[5][5];
	PointGame* arrayNextPosTutorial[5][5];
	PointGame* arrayPosHand[9];
	

	void reset();
	void newGame();
	void loadGame();
	void loadGameTime();
	void loadGame(int arrayData[MAX_ROW][MAX_COLUMN]);
	void randomNextId();
	void randomNext();
	void randomReplace(int color);
	void updatePoint(int currentX, int currentY);
	void calculatePoint(int x, int y);
	void setWay(int targetY, int targetX);
	void updateValue(int row, int column, int value);
	void getListBall(int row, int column, int idBall, int idResult);
	bool checkExist(PointGame* value, vector<PointGame*> array2) ;
	bool checkEndGame();
	void resetCheck();
};

