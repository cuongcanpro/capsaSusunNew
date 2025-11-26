#pragma once
#ifndef TetrisLLeftBrick_h__
#define TetrisLLeftBrick_h__
#include "TetrisBaseEntity.h"

class TetrisLLeftBrick : public TetrisBaseEntity
{
public:
	TetrisLLeftBrick(void);
	~TetrisLLeftBrick(void);

	void changeMap();
	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisLLeftBrick_h__

