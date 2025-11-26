#pragma once
#ifndef TBrick_h__
#define TBrick_h__
#include "BaseEntity.h"

class TBrick : public BaseEntity
{
public:
	TBrick(void);
	~TBrick(void);
	int getWidth();
	int getHeight();
};
#endif // TBrick_h__

