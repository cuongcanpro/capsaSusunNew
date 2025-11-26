#ifndef _CommonResultGroup_h__
#define _CommonResultGroup_h__

#include "axmol.h"

#include <Engine/GUI/Paper.h>

using namespace ax;
using namespace ax::ui;
class CommonResultGroup : public Node
{
public:
	CommonResultGroup(void);
	~CommonResultGroup(void);

	void showMauBinh(int type);
    void showEffectWin();
    void showEffectLose();
    void showTitle();

protected:
	Sprite* imgMauBinh;
	Sprite* bg;
	Paper* paperRight;
	Paper* paperLeft;
    Sprite* bgLightBottom;
    Sprite* bgLightTop;
    Sprite* iconLeafLeft;
    Sprite* iconLeafRight;
    Sprite* iconCrown;
    Sprite* iconLeft;
    Sprite* iconRight;
    Sprite* title;
    Sprite* bgTitle;
    ParticleSystemQuad* particle;
};

#endif

