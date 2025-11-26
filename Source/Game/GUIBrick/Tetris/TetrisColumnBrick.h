#pragma once
#ifndef TetrisColumnBrick_h__
#define TetrisColumnBrick_h__
#include "TetrisBaseEntity.h"

class TetrisColumnBrick : public TetrisBaseEntity
{
public:
	TetrisColumnBrick(void);
	~TetrisColumnBrick(void);


	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisColumnBrick_h__

