#ifndef _ResultGroup_h__
#define _ResultGroup_h__

#include "axmol.h"

#include "core/gui/BaseLayer.h"
#include "core/gui/StarFly.h"
#include "Engine/GUI/Paper.h"

using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class ResultGroup : public Node
{
public:
	ResultGroup(void);
	~ResultGroup(void);

	void showMauBinh(int type);
    void showEffectWin();
    void showEffectLose();
    void showTitle();

protected:
	Sprite* imgMauBinh;
	Sprite* bg;
	Paper* paperRight;
	Paper* paperLeft;
	StarFly* starFly;
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

