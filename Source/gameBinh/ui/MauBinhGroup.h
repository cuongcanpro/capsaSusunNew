#ifndef _MauBinhGroup_h__
#define _MauBinhGroup_h__

#include "axmol.h"

#include "core/gui/BaseLayer.h"
#include "core/gui/StarFly.h"
#include "gameTienlen/ui/ResultGroup.h"

using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class MauBinhGroup : public ResultGroup
{
public:
	MauBinhGroup(void);
	~MauBinhGroup(void);

	void showMauBinh(int type);
};

#endif

