#pragma once
#ifndef ThreeRowBrick_h__
#define ThreeRowBrick_h__
#include "BaseEntity.h"

class ThreeRowBrick : public BaseEntity
{
public:
	ThreeRowBrick(void);
	~ThreeRowBrick(void);
	int getWidth();
	int getHeight();
};
#endif // ThreeRowBrick_h__

