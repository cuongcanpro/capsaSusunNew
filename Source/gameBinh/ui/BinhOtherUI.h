#ifndef BinhOtherUI_h__
#define BinhOtherUI_h__
#include "core/gui/BaseLayer.h"
#include "BinhPlayerUI.h"
#include "../data/GameConstant.h"
using namespace ax;
using namespace ax::ui;

class BinhOtherUI : public BinhPlayerUI
{
public:
    BinhOtherUI(int chairIndex, Node* panel, efk::EffectManager* manager);
	~BinhOtherUI();
	void initGUI();
	void onEnterFinish();
	void newGame();
	void updateDealCard(int num);
	void endDealCard();
	void ready();
	void unReady();
	void endCard();
	void chiIndex(char chi);
	void compareChi(char chi, double money, int result);
	void sapLang(char chair, double money);
	void update(float delta);
	
public:
	float timeArrange;

};
#endif // BinhOtherUI_h__
