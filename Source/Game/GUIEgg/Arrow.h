#pragma once
#ifndef Arrow_h__
#define Arrow_h__
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/BaseGUI.h"

class Arrow
{
public:
	Arrow(void);
	~Arrow(void);

	GameImage* headArrow;
	GameImage* bodyArrow;

	float x, y;
	float angle;

	void setHeightArrow(float height);
	
	void setRotateArrow(float angle);
	
	void setPos(float x, float y);
	
	float getWidth();
	
	float getArrowHeight();
	
	float getRadian();
	
	void addToParent(BaseGUI* gui);
	
};
#endif // Arrow_h__

