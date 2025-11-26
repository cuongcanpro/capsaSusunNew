#ifndef _TalaResultGroup_h__
#define _TalaResultGroup_h__

#include "axmol.h"

#include "core/gui/BaseLayer.h"
#include "core/gui/StarFly.h"
#include "gameTienlen/ui/ResultGroup.h"

using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class TalaResultGroup : public ResultGroup
{
public:
	TalaResultGroup(void);
	~TalaResultGroup(void);
	void showMauBinh(int type);
};

#endif

