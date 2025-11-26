#pragma once
#include <vector>
#include "Game/Logic/PointGame.h"
#include "CellState.h"
#include "axmol.h"
#include <Game/Logic/Way.h>
using namespace std;

#define BOARD_ROW_BOMB    25
#define BOARD_COLUMN_BOMB 25
#define LIMIT_SIZE        25
// Số hàng và cột của mảng
const int CONFIG_ROWS = 10;
const int CONFIG_COLS = 4;

// Khai báo mảng extern
extern int configLevel[CONFIG_ROWS][CONFIG_COLS];
class BoardDataBomb
{
public:
    BoardDataBomb(void);
    ~BoardDataBomb(void);
    bool isGenData;
    int level;
    int sizeRow;
    int sizeColumn;
    int numBomb;
    int numBombGuess;
    int timeGame;
    int** configLevel;
    int arrayBomb[BOARD_ROW_BOMB][BOARD_COLUMN_BOMB];         // mang bomb: 0 -> khong co bomb, 1 -> co bomb
    int arrayData[BOARD_ROW_BOMB][BOARD_COLUMN_BOMB];         // mang Data: dem so bomb xung quanh o nay
    int arrayMap[BOARD_ROW_BOMB + 2][BOARD_COLUMN_BOMB + 2];  // mang di chuyen cua Miner
    Way* arrayWay[BOARD_ROW_BOMB + 2][BOARD_COLUMN_BOMB + 2];
    CellDataState arrayCell[BOARD_ROW_BOMB]
                           [BOARD_COLUMN_BOMB];  // mang Cell: luu lai trang thai cac Cell da mo hay chua
    void setLevel(int level);
    void setLevelExtend(int level);
    bool isValid(int row, int column);
    bool checkValidMap();
    void resetMap();
    void genData(PointGame pSelect);
    void loadData();
    void loadDataExtend();
    vector<PointGame> getDataFromPoint(PointGame point);
    vector<PointGame> getDataNotiFromPoint(PointGame point);
    bool checkOpenAllBomb(PointGame point);
    int getNumCell();
    void setCell(int row, int column, CellDataState state);
    int getNumBombRemain();
    bool checkPointInBoard(int row, int column);
    bool checkWin();

    vector<PointGame*> arrayPoint;
    PointGame* currentPoint;
    void updatePoint();
    void calculatePoint(int x, int y);
    bool checkCanMove(int row, int column);
    void setWay(int targetY, int targetX);
    PointGame getFirstBomb();
    int calculatePointExtend();
};
