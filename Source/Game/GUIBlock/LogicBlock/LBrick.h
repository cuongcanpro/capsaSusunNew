#pragma once
#ifndef LBrick_h__
#define LBrick_h__
#include "BaseEntity.h"

class LBrick : public BaseEntity
{
public:
	LBrick(void);
	~LBrick(void);
	int getWidth();
	int getHeight();
};
#endif // LBrick_h__

