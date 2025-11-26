#ifndef SelfUI_h__
#define SelfUI_h__
#include "core/gui/BaseLayer.h"
#include "PlayerUI.h"
#include "CardButton.h"
#include "../data/GameConstant.h"


class CardButton;

using namespace ax;
using namespace ax::ui;
class SelfUI : public PlayerUI
{
public:
	SelfUI();
	~SelfUI();

	bool init();
	void initGUI();
	void initMyUI();
	void initGroupCard();
	void newGame();
	void updateDealCard(int num);
	void endDealCard();
	void updateCard();
	void changeTurn(int time);
	void endTurnCard();
	void showAutoTurn();
	void showCancel(bool show);
	void getRank(char rank, bool isCong);
	void endCard();
	void endCard1();
	void endCard2();
	bool checkCardSelectByMove(Vec2 point, int i, int index, float direct);

	void onMoveCard(Vec2 point, Vec2 startPoint, int id);
	bool onTouchBegan(Touch*touch, Event* event);
	void onTouchMoved(Touch*touch, Event* event);
	void onTouchEnded(Touch*touch, Event* event);
public:
	Size getCardSize();
	Vec2 getCardPos(int index);
	Vec2 getCardPosById(int id);
	void setEnableButton(Button* button, bool show, bool enable);
	void showArrowButton(bool show, float posX);
	void normalAllPosition();
	void hideAllButton();
	void sortCard(bool isSortNormal);
	bool checkCanThrowCard();
	vector <int> getArraySelect();
	void autoCard(vector <int> arrayId);
	void setDarkCard(bool isDark);
	void updateLevel();
	void updateMoney();
    void updateLanguage();
private:
	ax::ui::Button *btnArrange, *btnChoose, *btnCancel, *btnEmo, *btnChat;
	Node* panelCard;
	ImageView *arrow;
	void onButtonRelease(Button* button, int id);
	CardButton *arrayCard[NUM_CARD];
	Text* lbLevel;
	LoadingBar* progress;
};
#endif // SelfUI_h__
