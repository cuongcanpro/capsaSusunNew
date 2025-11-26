#include "axmol.h"
#include "CardImage.h"

#ifndef CardEffect_h__
#define CardEffect_h__
typedef std::function<void(int indexCard, int indexPlayer)> CardEffectListener;
using namespace std;
using namespace ax;
class CardEffect : public CardImage
{
public:
	CardEffect(void);
	CardEffect(int id);
	~CardEffect(void);
	CardEffectListener _callback;

	void setListener(const CardEffectListener& listener);
	void callbackEffectCard();
	void setInfoCard(int _index, int indexPlayer);
	void moveToOpen(Vec2 posStart, Vec2 posEnd, float scaleStart, float scaleEnd, float delayTime);
	void moveTo(Vec2 posStart, Vec2 posEnd, float scaleStart, float scaleEnd, float delayTime);
	void moveEnd(Vec2 posStart, Vec2 posEnd, Vec2 posEnd2, float scaleStart, float scaleEnd, float scaleEnd2, float delayTime);
	void moveToiTrang(Vec2 posStart, Vec2 posEnd, float scaleStart, float scaleEnd, int index, bool isConvert, float delayTime);
	void playCardFly();
	void playCardDown();
	int zOrder;
	float scaleEnd;
	bool isConvert;
	float lastDiff;
	int index;
	int indexPlayer;
	void update();
private:
	int id;
};
#endif // CardEffect_h__

