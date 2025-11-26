#ifndef _BombEffect_h__
#define _BombEffect_h__
#include "axmol.h"
#include <Engine/GUI/ParticleEffect.h>

using namespace ax;
class BombEffect : public Node
{
public:
	int max;
	BombEffect(void);
	~BombEffect(void);
    Sprite* imgBomb;
    ParticleEffect* effect;
    void showBomb(float timeDelay);
    void callbackShow();
};
#endif
