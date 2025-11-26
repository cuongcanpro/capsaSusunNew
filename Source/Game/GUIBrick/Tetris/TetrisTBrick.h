#pragma once
#ifndef TetrisTBrick_h__
#define TetrisTBrick_h__
#include "TetrisBaseEntity.h"

class TetrisTBrick : public TetrisBaseEntity
{
public:
	TetrisTBrick(void);
	~TetrisTBrick(void);

	void changeMap();
	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisTBrick_h__

