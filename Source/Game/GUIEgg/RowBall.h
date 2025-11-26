#pragma once
#ifndef RowBall_h__
#define RowBall_h__
#include "Ball.h"
#include "Game/Data/GlobalData.h"
#include <vector>
using namespace std;
class RowBall
{
public:
	RowBall(void);
	~RowBall(void);

	vector<Ball*> arrayBall;
	int idRow;
	int typeRow;

	RowBall(int _idRow);
	RowBall(int _idRow, int typeRow);
	void moveDown(float f);

	Ball* getBall(int idColumn);
	void resetCheckConnect(); 
	void copy(RowBall* rowBall); 
	void decreaseRow(int num);
	void renew(int typeRow2);
	void newRow(int typeRow);
	void callbackRemove(Node* pSender);

	void moveUp(int countUp);
	void setIdRow( int _idRow, int _typeRow);
	void setVisibleAll();
	void effectNewGame(float delayTime);
	vector<int> getArrayId();
};
#endif // RowBall_h__

