#ifndef _Viewing_h__
#define _Viewing_h__
#include "axmol.h"

using namespace ax;
class Viewing : public Node
{
public:
	Viewing(void);
	~Viewing(void);

	void startEffect();
	void stopEffect();

private:
	Sprite *imgView;
};
#endif
