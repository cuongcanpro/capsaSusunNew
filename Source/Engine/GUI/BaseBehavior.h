#ifndef BaseBehaviors_h__
#define BaseBehaviors_h__
#include "axmol.h"
#include "BaseButton.h"

class BaseBehavior
{
private:
	int _idBehavior;
public:
	BaseBehavior(void);
	virtual ~BaseBehavior(void);

public:
	virtual void onTouchBegan(Touch* touch, BaseButton* touchButton);
	virtual void onTouchMoved(Touch* touch, BaseButton* dragButton);
	virtual void onTouchEnded(Touch* touch, BaseButton* releaseButton);
	virtual void onCanceled (BaseButton* button);
	virtual void setVisible(bool visible);

	// Callbacks on added to button
	virtual void onAdd(BaseButton* button);
	int getId();
	void setId(int id);
	virtual void updatePos(BaseButton* ownerBtn);
};

#endif // BaseBehaviors_h__
