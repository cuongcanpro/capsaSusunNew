#pragma once
#ifndef FourColumnBrick_h__
#define FourColumnBrick_h__
#include "BaseEntity.h"

class FourColumnBrick : public BaseEntity
{
public:
	FourColumnBrick(void);
	~FourColumnBrick(void);
	int getWidth();
	int getHeight();
};
#endif // FourColumnBrick_h__

