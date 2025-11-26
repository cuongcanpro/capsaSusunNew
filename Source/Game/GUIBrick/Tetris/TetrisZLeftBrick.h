#pragma once
#ifndef TetrisZLeftBrick_h__
#define TetrisZLeftBrick_h__
#include "TetrisBaseEntity.h"

class TetrisZLeftBrick : public TetrisBaseEntity
{
public:
	TetrisZLeftBrick(void);
	~TetrisZLeftBrick(void);

	void changeMap();
	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisZLeftBrick_h__

