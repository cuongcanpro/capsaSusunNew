#ifndef TalaCardView_h__
#define TalaCardView_h__

#include "core/gui/BaseLayer.h"

class TalaCardView : public Sprite {
public:
	static TalaCardView* create(int id);
	TalaCardView();
	~TalaCardView();
	bool init(int id);
	void onEnter();

public:
	int id;
	bool isUp, isDark;
	float vx, vy, a, turnSpeed;

	Sprite *arrow, *eatable, *eaten;

public:
	void setID(int id);
	void setUp(bool up, bool animate=false);
	void setDark(bool dark, bool animate=false);
	void showArrow(bool show);
	void showEatable(bool show);
	void showEaten(bool show);
	void effectClear();
	void update(float dt);
	
	bool containTouchPoint(ax::Point point);
	ax::Point calculateAnchorPoint(ax::Point point);
	ax::Point calculateNewPositionWithNewAnchor(ax::Point anchor);

public:
	static string getCardResource(int id);

	static float SMALL_SCALE;
	static float START_Y;
	static const float OFFSET_Y;
	static const int UP_ACTION_TAG;
	static const int DARK_ACTION_TAG;
};

#endif //TalaCardView_h__
