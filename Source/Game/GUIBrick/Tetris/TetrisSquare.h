#pragma once
#ifndef TetrisSquare_h__
#define TetrisSquare_h__
#include "TetrisBaseEntity.h"

class TetrisSquare : public TetrisBaseEntity
{
public:
	TetrisSquare(void);
	~TetrisSquare(void);

	void changeMap();
	void changeState();

	void makeState();

	int getWidth();

	int getHeight();

};
#endif // TetrisSquare_h__

