#pragma once
#ifndef OneBrick_h__
#define OneBrick_h__
#include "BaseEntity.h"

class OneBrick : public BaseEntity
{
public:
	OneBrick(void);
	~OneBrick(void);
	int getWidth();
	int getHeight();
};
#endif // OneBrick_h__

