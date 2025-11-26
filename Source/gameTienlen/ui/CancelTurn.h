#ifndef _CancelTurn_h__
#define _CancelTurn_h__
#include "axmol.h"

using namespace ax;
class CancelTurn : public Node
{
public:
	CancelTurn(void);
	~CancelTurn(void);

	void startEffect();
	void stopEffect();
	void update(float dt);

private:
	Sprite *imgCancel;
	Sprite *arrayArrow[5];
	int count;
};
#endif
