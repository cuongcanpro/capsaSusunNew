#ifndef CardButton_h__
#define CardButton_h__
#include "axmol.h"
#include "extensions/cocos-ext.h"
#include "SelfUI.h"
using namespace ax;
using namespace ax::ui;
using namespace std;

class SelfUI;

class CardButton : public ax::ui::Button
{
public:
	CardButton(void);
	CardButton(int id, SelfUI* myPlayer);
	~CardButton(void);
public:
	int id;
	int index;
	SelfUI* myPlayer;
	float posDefaultY, posDefaultX;
	bool isSelect;
	bool IsSelect();
	void setIdCard(int id);
	void setSize(float width, float height);
	string getResource();
	void setDark( bool isDark );
	void touchEvent(Object *pSender, Widget::TouchEventType type);
	void setCardSize(float scale);
	float getCardWidth();
	float getCardHeight();
	void setPosDefaultY(float pos);
	void setPosDefaultX(float pos);
	void setDefaultPos();
	void moveCard(bool up);
	void setSelect(bool select);
	void hideCard();
	void callbackHideCard();
	void openCard();
	void callbackOpenCard();
	void eatCard();
	void resetCard();
	Vec2 lastPos;
	bool isTouchMove;
};
#endif // CardButton_h__

