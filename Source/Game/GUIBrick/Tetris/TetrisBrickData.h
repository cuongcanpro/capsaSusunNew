#pragma once
#ifndef TetrisBrickData_h__
#define TetrisBrickData_h__
#include "../../Logic/PointGame.h"
#include <vector>
#include "axmol.h"
using namespace std;
class TetrisBrickData
{
public:
	TetrisBrickData(void);
	~TetrisBrickData(void);

	int data[20][10];

	vector<int> arrayScore;

	float countTime;
	float frame;

	void update();
	void setCell(int x, int y);
	void changeMap();
	bool inData(PointGame* point);
	void checkScore();
	void newGame();
	void checkEnd();
};
#endif // TetrisBrickData_h__

