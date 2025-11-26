#include "BaseBehavior.h"


BaseBehavior::BaseBehavior(void)
{
	_idBehavior=0;
}


BaseBehavior::~BaseBehavior(void)
{
}

void BaseBehavior::onTouchBegan(Touch*touch, BaseButton* touchButton)
{

}

void BaseBehavior::onTouchMoved(Touch*touch, BaseButton* dragButton)
{

}

void BaseBehavior::onTouchEnded(Touch*touch, BaseButton* releaseButton)
{

}
void BaseBehavior::onCanceled (BaseButton* button)
{

}
void BaseBehavior::onAdd(BaseButton* button)
{

}

void BaseBehavior::setVisible( bool visible )
{

}

int BaseBehavior::getId()
{
	return _idBehavior;
}

void BaseBehavior::setId( int id )
{
	_idBehavior=id;

}

void BaseBehavior::updatePos( BaseButton* ownerBtn )
{

}
