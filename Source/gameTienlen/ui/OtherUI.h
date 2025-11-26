#ifndef OtherUI_h__
#define OtherUI_h__
#include "core/gui/BaseLayer.h"
#include "PlayerUI.h"
#include "CardImage.h"
#include "../data/GameConstant.h"
using namespace ax;
using namespace ax::ui;

class OtherUI : public PlayerUI
{
public:
	OtherUI(int chairIndex);
	~OtherUI();

	bool init();
	void initGUI();
	void initGroupCard();
	void newGame();
	void updateDealCard(int num);
	void endDealCard();
	void updateCard();
	void endCard();
	void showCard();
	void updatePositionGroupCard(int num);

	Size getCardSize();
	Vec2 getCardPos(int index);
	Vec2 getCardPosById(int index);
	void setDarkCard(bool isDark);
private:
	ImageView* cardImage;
	Text* labelNumber;
	Text* lbShowCard;
	CardImage* arrayCard[NUM_CARD];

};
#endif // OtherUI_h__