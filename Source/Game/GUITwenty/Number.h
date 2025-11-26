#pragma once
#ifndef Number_h__
#define Number_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"
#include "ui/CocosGUI.h"

using namespace ax;
using namespace ui;

class Number : public Object
{
public:
	Number(void);
	~Number(void);

	GameImage* ball;

	Text* label;
	int id;
	bool isFall;
	//DBCCArmatureNode* eff;
	float width,height;
	float x, y;
	bool visible;

	bool isVisible();
	void setVisible(bool visible);
	void addToParent(Node* parent);
	void setX(float x);
	void setY(float y);
	void setPosition(float x, float y);
	float getWidth();
	float getHeight();
	float getX();
	float getY();
	void setNumber(int number);
	void effectNewGame();
	void effectEndGame();
	void effectEat();
	void doEffectEat();
	int countEffect;
	void stopAllActions();
	void updateSize();
	void remove();
};
#endif // Number_h__

