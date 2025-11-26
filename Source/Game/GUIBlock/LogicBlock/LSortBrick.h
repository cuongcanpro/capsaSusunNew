#pragma once
#ifndef LSortBrick_h__
#define LSortBrick_h__
#include "BaseEntity.h"

class LSortBrick : public BaseEntity
{
public:
	LSortBrick(void);
	~LSortBrick(void);
	int getWidth();
	int getHeight();
};
#endif // LSortBrick_h__

