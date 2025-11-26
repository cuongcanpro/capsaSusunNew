#ifndef _LAYER_H_
#define _LAYER_H_
#include "axmol.h"
using namespace ax;
class GameLayer :
	public Layer
{
public:
	unsigned short	idLayer;
	GameLayer(void);
	~GameLayer(void);
	GameLayer(int);
};

#endif
