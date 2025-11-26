#pragma once
#ifndef BigSquareBrick_h__
#define BigSquareBrick_h__
#include "BaseEntity.h"

class BigSquareBrick : public BaseEntity
{
public:
	BigSquareBrick(void);
	~BigSquareBrick(void);
	int getWidth();
	int getHeight();
};
#endif // BigSquareBrick_h__

