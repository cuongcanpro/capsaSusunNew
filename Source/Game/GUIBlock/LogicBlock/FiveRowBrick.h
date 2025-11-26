#pragma once
#ifndef FiveRowBrick_h__
#define FiveRowBrick_h__
#include "BaseEntity.h"

class FiveRowBrick : public BaseEntity
{
public:
	FiveRowBrick(void);
	~FiveRowBrick(void);
	int getWidth();
	int getHeight();
};
#endif // FiveRowBrick_h__

