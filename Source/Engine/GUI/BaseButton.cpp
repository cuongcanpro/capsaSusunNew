#include "BaseButton.h"
#include "BaseBehavior.h"
#define TIME_DELAY_ACTION 0.4f
BaseButton::BaseButton(int buttonID, GameImage* image)
{
	this->buttonID = buttonID;
	this->normalImage = image;
	this->normalImage->setAnchorPoint(Point(0, 0));
	canTouch=true;
	canMove=true;
	canTouchOut = false;
	touchArea = Rect(0, 0, 0,0);
}

BaseButton::BaseButton(int buttonID, Rect touchArea, Node* parent)
{
	this->buttonID	=	buttonID;
	canTouch		=	true;
	canMove			=	true;
	normalImage		=	NULL;
	canTouchOut		= false;

	this->touchArea = touchArea;
	this->parent	= parent;
}

BaseButton::BaseButton( void )
{
	canTouch=true;
	canMove=true;
	canTouchOut		= false;
	_baseGui = NULL;
}


BaseButton::~BaseButton(void)
{
	delete normalImage;
	normalImage=NULL;
	canTouchOut		= false;
	int n=behaviorList.size();
	BaseBehavior* behavior;
	for (int i=0;i<n;i++)
	{
		behavior=behaviorList.at(i);
		delete behavior;
	}
}

bool BaseButton::containsTouchLocation(Touch* touch)
{
	if (normalImage != NULL)
	{
		return normalImage->containsTouchLocation(touch);
	}
	else
	{
		Point touchLocation = touch->getLocation();
		// Touch Area has to take parent position into account
		Rect checkTouchArea = touchArea;
		checkTouchArea.origin.x += parent->getPositionX() + touchPosition.x;
		checkTouchArea.origin.y += parent->getPositionY() + touchPosition.y;
		bool result = checkTouchArea.containsPoint(touchLocation);
		return result;
	}
	return false;
}

void BaseButton::setPosition(float x, float y)
{
	if (normalImage != NULL)
	{
		normalImage->setPos(x, y);
	}

	touchPosition.x = x;
	touchPosition.y = y;
	/*if (touchArea.size.width != 0 )
	{
		touchArea.origin.x = x - touchArea.size.width/2;
		touchArea.origin.y = y - touchArea.size.height/2;
	}*/
}

Point BaseButton::getPosition()
{
	if(normalImage != NULL)
		return normalImage->getPosition();
	return Vec2(0, 0);
}

float BaseButton::getPositionX()
{
	if(normalImage != NULL)
		return normalImage->getPositionX();
	return 0;
}

float BaseButton::getPositionY()
{
	if(normalImage != NULL)
		return normalImage->getPositionY();
	return 0;
}

float BaseButton::getWidth()
{
	if(normalImage != NULL)
		return normalImage->getWidth();
	return 0;
}

float BaseButton::getHeight()
{
	if(normalImage != NULL)
		return normalImage->getHeight();
	return 0;
}


void BaseButton::addBehavior(BaseBehavior* behavior)
{
	behaviorList.push_back(behavior);
	behavior->onAdd(this);
}

void BaseButton::setVisible(bool visible)
{
	if (normalImage != NULL)
		this->setVisible(visible, true);
	canTouch = visible;
}

void BaseButton::setVisible(bool visible,bool visibleBehavior)
{
	this->normalImage->setVisible(visible);
	BaseBehavior* behavior;
	int n=behaviorList.size();
	for (int i=0;i<n;i++)
	{
		behavior=behaviorList.at(i);
		behavior->setVisible(visibleBehavior&visible);
	}
}

BaseBehavior* BaseButton::getBehavior( int id )
{
	int n=behaviorList.size();
	BaseBehavior *bhv;
	for (int i=0;i<n;i++)
	{
		bhv=behaviorList.at(i);
		if(bhv->getId()==id)
		{
			return bhv;
		}
	}
	return NULL;

}

void BaseButton::setEnable(bool enable)
{
	normalImage->setEnable(enable);
	canTouch=enable;
	canMove=enable;
	BaseBehavior* behavior;
	int n=behaviorList.size();
	for (int i=0;i<n;i++)
	{
		behavior=behaviorList.at(i);
		behavior->setVisible(enable);
	}

}

void BaseButton::setDisable()
{
	setEnable(false);
}

bool BaseButton::hasBehavior( int idBehavior )
{
	int n=behaviorList.size();
	BaseBehavior *bhv;
	for (int i=0;i<n;i++)
	{
		bhv=behaviorList.at(i);
		if(bhv->getId()==idBehavior)
		{
			return true;
		}
	}
	return false;

}

void BaseButton::updatePosOfBehavior()
{
	int n=behaviorList.size();
	BaseBehavior* behavior;
	for (int i=0;i<n;i++)
	{
		behavior=behaviorList.at(i);
		behavior->updatePos(this);
	}
}

bool BaseButton::getVisible()
{
	if (normalImage != NULL)
		return normalImage->getVisible();
	else
		return true;

}


bool BaseButton::isEnable()
{
	return normalImage->isEnable();
}

void BaseButton::clear()
{
	
}

void BaseButton::addIcon( GameImage* icon,Point pos )
{
	normalImage->addChild(icon);
	icon->setPosition(pos);
}
void BaseButton::onTouched()
{

}
void BaseButton::onReleased()
{
	//LOG("release button %i", buttonID);
}
void BaseButton::setParent(BaseGUI* baseGui)
{
	_baseGui = baseGui;
}

void BaseButton::setPosText( float x,float y  )
{
}
