#include "Arrow.h"
#include <math.h>
#include "Game/Logic/Constant.h"

Arrow::Arrow(void)
{
	headArrow = new GameImage("Egg/headArrow.png");
	bodyArrow = new GameImage("Egg/bodyArrow.png");

	headArrow->setHeight(WIDTH_BALL / headArrow->getWidth() * headArrow->getHeight());
	headArrow->setWidth(WIDTH_BALL);

	bodyArrow->setWidth(WIDTH_BALL * 0.7f);
	//bodyArrow->setHeight(2);

	bodyArrow->getImg()->setAnchorPoint(Vec2(0.5f, 0));
	headArrow->getImg()->setAnchorPoint(Vec2(0.5f, 0));
}


Arrow::~Arrow(void)
{
}

void Arrow::setHeightArrow( float height )
{
	bodyArrow->setScaleY(height / bodyArrow->getHeight());
}

void Arrow::setRotateArrow( float angle )
{
	bodyArrow->setRotation(angle);
	headArrow->setRotation(angle);

	angle = (float)(angle / 180 * 3.14);
	float posX = (float)(sin(angle)) * bodyArrow->getRealHeight();
		//+ bodyArrow->getRealWidth() * 0.5f - headArrow->getRealWidth() * 0.5f;
	float posY = (float)(cos(angle)) * bodyArrow->getRealHeight();
	headArrow->setPosition(bodyArrow->getPositionX() + posX, bodyArrow->getPositionY() + posY);

	this->angle = angle;
}

void Arrow::setPos( float x, float y )
{
	bodyArrow->setPosition(x, y);
	this->x = x;
	this->y = y;
}

float Arrow::getWidth()
{
	return bodyArrow->getRealWidth();
}

float Arrow::getArrowHeight()
{
	return headArrow->getRealHeight();
}

float Arrow::getRadian()
{
	return angle;
}

void Arrow::addToParent( BaseGUI* gui )
{
	gui->addChild(bodyArrow);
	gui->addChild(headArrow);
}
