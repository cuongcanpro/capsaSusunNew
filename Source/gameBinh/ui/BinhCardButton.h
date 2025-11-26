#ifndef BinhCardButton_h__
#define BinhCardButton_h__
#include "axmol.h"
#include "extensions/cocos-ext.h"
#include "BinhTruyenThong.h"
#include "BinhTinhAt.h"
using namespace ax;
using namespace ax::ui;
using namespace std;
enum BinhCardButtonType {
	CENTER,
	BOTTOM
};
class BinhTruyenThong;
class BinhTinhAt;


class BinhCardButton : public ax::ui::Button
{
public:
	BinhCardButton(void);
	BinhCardButton(int id);
	BinhCardButton(int index, int id, BinhTruyenThong* binh);
	BinhCardButton(int index, int id, BinhCardButtonType type, BinhTinhAt* binh);
	~BinhCardButton(void);
public:
	int id;
	int index;
	int saveIdCard;
	BinhCardButtonType type;
	float posDefaultY, posDefaultX, rotateDefault;
	float rootScale;
	int rootZOrder;
	bool isSelect;
	bool IsSelect();
	void setIdCard(int id);
	string getResource();
	void setDark( bool isDark );
	void touchEvent(Object *pSender, Widget::TouchEventType type);
	void setCardSize(float scale);
	float getCardWidth();
	float getCardHeight();
	void setPosDefaultY(float pos);
	void setPosDefaultX(float pos);
	void setDefaultPos();
	void saveDefaultPos();
	void saveScale();
	void saveZOrder();
	void saveInfoCard();
	Vec2 getDefaultPos();
	void moveCard(bool up);
	void moveToDefault(float time, float delayTime = 0);
	void callbackMoveCard(Node* pSender);
	void setSelect(bool select);
	void showCard(Vec2 pos);
	void callbackShowCard(Node* pSender);
	void showAt();
};
#endif // BinhCardButton_h__

