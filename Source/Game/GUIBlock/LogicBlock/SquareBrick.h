#pragma once
#ifndef SquareBrick_h__
#define SquareBrick_h__
#include "BaseEntity.h"

class SquareBrick : public BaseEntity
{
public:
	SquareBrick(void);
	~SquareBrick(void);
	int getWidth();
	int getHeight();
};
#endif // SquareBrick_h__

