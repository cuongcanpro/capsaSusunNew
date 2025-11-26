#pragma once
#include "Way.h"
#include <vector>
#include "PointGame.h"
#include "axmol.h"
using namespace std;

#define BIG_RED  2
#define BIG_PINK  1
#define BIG_SEA_BLUE  3
#define BIG_SKY_BLUE  4
#define BIG_GREEN  5
#define BIG_VIOLET  6
#define BIG_YELLOW  7

#define SMALL_RED  9
#define SMALL_PINK  8
#define SMALL_SEA_BLUE  10
#define SMALL_SKY_BLUE  11
#define SMALL_GREEN  12
#define SMALL_VIOLET  13
#define SMALL_YELLOW  14

class BoardData
{
public:
	BoardData(void);
	~BoardData(void);

	vector <int> arrayNewBall;
	vector <int> arrayNewBallGen;
	vector <PointGame*> arrayNewPos;
	int arrayBall[9][9];
	Way* arrayWay[9][9];
	vector<int> arrayEmpty;
	vector<PointGame*> arrayPoint;
	vector<PointGame*> result; // mang ghi cac bong an diem

	PointGame* currentPoint;

	int arrayIdNext[3];
	int arrayPosNext[3];
	int posReplace;

	void reset();
	void newGame();
	void loadGame();
	void loadGameData(int [81]);
	void loadGameTime();
	void loadGameBattle(vector <int> data);
	void loadGame(int arrayData[9][9]);
	void randomArrayNext();
	void randomNextBattle();
	void randomReplaceBattle(int color);
	
	void randomNext();
	void randomReplace(int color);
	void updatePoint(int currentX, int currentY);
	void calculatePoint(int x, int y);
	void setWay(int targetY, int targetX);
	void updateValue(int row, int column, int value);
	vector<PointGame*> getListBall(int row, int column);
	bool checkExist(PointGame* value, vector<PointGame*> array2) ;
	bool checkEndGame();
	bool checkNewBall();
	void printBoard();

	void newGameTutorial();
	void getMovePoint();
	int getPointBall(int row, int column, int id, bool checkSavePoint, int savePoint);
	int getNumBall();
	PointGame startPoint;
	PointGame endPoint;
    bool checkNoBigBall();
    string getDataBall();
    void renewBall();
    vector<int> arrRenew;
    void removeBall(int row, int column);
};

