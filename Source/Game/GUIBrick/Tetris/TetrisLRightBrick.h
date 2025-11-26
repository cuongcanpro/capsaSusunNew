#pragma once
#ifndef TetrisLRightBrick_h__
#define TetrisLRightBrick_h__
#include "TetrisBaseEntity.h"

class TetrisLRightBrick : public TetrisBaseEntity
{
public:
	TetrisLRightBrick(void);
	~TetrisLRightBrick(void);

	void changeMap();
	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisLRightBrick_h__

