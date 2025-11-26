#ifndef _PopGroupNewNumber_h__
#define _PopGroupNewNumber_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"

#include "PopObjectNumber.h"

#include "EffekseerForCocos2d-x.h"
#include <Engine/GUI/Paper.h>
using namespace ax;
using namespace ax::ui;
class PopGroupNewNumber : public Node
{
public:

	PopGroupNewNumber(void);
	~PopGroupNewNumber(void);
	ax::LayerColor* layerColor;
	PopObjectNumber* newNumber;
    efk::EffectEmitter* effFirework;
	Paper* paperRight;
	Paper* paperLeft;
	//StarFly* starFly;
	Button* btnOk;
	Sprite* imgCongrat;
	Text* lbCongrat;
	void showNewNumber(int number, Vec2 pos, float scale);
	void callbackShowNew();
};
#endif
