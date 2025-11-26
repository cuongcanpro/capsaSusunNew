#ifndef BinhSelfUI_h__
#define BinhSelfUI_h__
#include "core/gui/BaseLayer.h"
#include "BinhPlayerUI.h"
#include "../data/GameConstant.h"



using namespace ax;
using namespace ax::ui;
class BinhSelfUI : public BinhPlayerUI
{
public:
    BinhSelfUI(Node* panel, efk::EffectManager* manager);
	~BinhSelfUI();

	void initGUI();
	void initMyUI();
	void initGroupCard();
	void newGame();
	void updateDealCard(int num);
	void endDealCard();
	void updateCard();
	void ready();
	void endCard();
	void chiIndex(char chi);
	void compareChi(char chi, double money, int result);
	void summary(double money);
	void sapBai(double money, SapBaiType sapTye);
	void updateLevel();
	void updateMoney();
public:
	void disableAllChi();
private:
	ImageView *arrow;
	ImageView* arrayImgChi[NUM_CHI];
	Text* lbLevel;
	LoadingBar* progress;
};
#endif // BinhSelfUI_h__
