#ifndef BubbleBehavior_h__
#define BubbleBehavior_h__

#include "BaseBehavior.h"

class BubbleBehavior :
	public BaseBehavior
{
public:
	BubbleBehavior(void);
	~BubbleBehavior(void);

public:
	void onTouchBegan(Touch*touch, BaseButton* touchButton);
	void onTouchEnded(Touch* touch, BaseButton* releaseButton);
};
#endif // BubbleBehavior_h__

