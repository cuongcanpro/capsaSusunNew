#pragma once
#ifndef TetrisZRightBrick_h__
#define TetrisZRightBrick_h__
#include "TetrisBaseEntity.h"

class TetrisZRightBrick : public TetrisBaseEntity
{
public:
	TetrisZRightBrick(void);
	~TetrisZRightBrick(void);

	void changeMap();
	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisZRightBrick_h__

