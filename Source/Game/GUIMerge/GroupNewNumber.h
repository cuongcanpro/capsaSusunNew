#ifndef _GroupNewNumber_h__
#define _GroupNewNumber_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"

#include "ObjectNumber.h"
#include "Engine/GUI/Paper.h"

using namespace ax;
using namespace ax::ui;
class GroupNewNumber : public Node
{
public:

	GroupNewNumber(void);
	~GroupNewNumber(void);
	ax::LayerColor* layerColor;
	ObjectNumber* newNumber;
	Paper* paperRight;
	Paper* paperLeft;
	Button* btnOk;

	void showNewNumber(int number, Vec2 pos, float scale);
	void callbackShowNew();
};
#endif
