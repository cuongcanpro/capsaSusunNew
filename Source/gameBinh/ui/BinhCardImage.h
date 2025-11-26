#include "axmol.h"

#ifndef BinhCardImage_h__
#define BinhCardImage_h__

using namespace std;
using namespace ax;
class BinhCardImage : public Sprite
{
public:
	BinhCardImage(void);
	BinhCardImage( int id );
	~BinhCardImage(void);
	float posDefaultY, posDefaultX;
	float rootScale;
	int rootZOrder;
	int saveIdCard;
	void setIdCard(int id);
	string getResource();
	void setDark(bool isDark);
	float getCardWidth();
	float getCardHeight();
	void setPosDefaultY(float pos);
	void setPosDefaultX(float pos);
	void setDefaultPos();
	void saveDefaultPos();
	Vec2 getDefaultPos();
	void saveScale();
	void saveZOrder();
	int getRootZOrder();
	void saveInfoCard();
	void showCard();
	void moveToDefault(float time, float delayTime = 0);
	void callbackMoveCard(Node* pSender);
	void callbackShowCard(Node* pSender);
private:
	int id;
};
#endif // BinhCardImage_h__

