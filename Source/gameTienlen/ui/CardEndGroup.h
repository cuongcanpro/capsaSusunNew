#ifndef _CardEndGroup_h__
#define _CardEndGroup_h__

#include "axmol.h"

#include "core/gui/BaseLayer.h"
#include "core/gui/StarFly.h"
#include "CardEffect.h"
#include "EffekseerForCocos2d-x.h"
#include "Engine/GUI/Paper.h"
using namespace efk;
using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class CardEndGroup : public Node
{
public:
	CardEndGroup(void);
	~CardEndGroup(void);

	void showCardEnd(vector<int> ids, vector<Vec2> startPos, float startScale);
	void update(float delta);
	void showLight();
	void playSound();
	CardEffect* getCardEffect();
    void callbackVibrate();

    protected:
	vector <CardEffect*> cards;
	Sprite* bg;
	Paper* paperRight;
	Paper* paperLeft;
	StarFly* starFly;

	efk::EffectManager* manager;
	efk::EffectEmitter* lightExplore;
};

#endif

