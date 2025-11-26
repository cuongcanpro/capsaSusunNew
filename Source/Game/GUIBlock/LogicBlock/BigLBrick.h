#pragma once
#ifndef BigLBrick_h__
#define BigLBrick_h__
#include "BaseEntity.h"

class BigLBrick : public BaseEntity
{
public:
	BigLBrick(void);
	~BigLBrick(void);

	int getWidth();
	int getHeight();

};
#endif // BigLBrick_h__

