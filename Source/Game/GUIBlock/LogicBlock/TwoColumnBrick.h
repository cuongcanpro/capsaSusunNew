#pragma once
#ifndef TwoColumnBrick_h__
#define TwoColumnBrick_h__
#include "BaseEntity.h"

class TwoColumnBrick : public BaseEntity
{
public:
	TwoColumnBrick(void);
	~TwoColumnBrick(void);
	int getWidth();
	int getHeight();
};
#endif // TwoColumnBrick_h__

