#pragma once
#ifndef TetrisBaseEntity_h__
#define TetrisBaseEntity_h__
#include <vector>
#include "../../Logic/PointGame.h"
#include "TetrisBrickData.h"
#include "axmol.h"
using namespace std;

#define COLUMN 0
#define LLEFT 1
#define LRIGHT 2
#define SQUARE 3
#define TBRICK 4
#define ZLEFT 5
#define ZRIGHT 6
class TetrisBaseEntity
{
public:
	TetrisBaseEntity(void);
	~TetrisBaseEntity(void);

	int x, y;

	float frame;
	float countTime;

	bool visible;
	int type;
	int state;

	vector <PointGame *> data;
	int countPoint ;
	float countTimePress ;
	bool firstPress ;
	void update();
	virtual void changeMap();
	virtual void changeState();
	virtual void makeState();
	virtual int getWidth();
	virtual int getHeight();
	void moveLeft();
	void moveRight();
	bool checkStop();
	bool notMove(int disX, int disY);
	void moveDown();
	void checkKeyPress();
	void addPoint(int x, int y);
	void setData(TetrisBrickData *data);
	void setPos(int x, int y);
};
#endif // TetrisBaseEntity_h__

