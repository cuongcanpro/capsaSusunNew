#pragma once
#ifndef BlockItem_h__
#define BlockItem_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"
#include "Game/Logic/PointGame.h"

using namespace ax;
class BlockItem
{
public:
	BlockItem(void);
	~BlockItem(void);

	GameImage* ball;
	GameImage* image;
	int id;
	bool isFall;

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
	void setNumber(int id);
	void setSelect(bool isSelect);
	void runAction(float x, float y);
	void effectNewGame(float delayTime);
	void effectEndGame(float delayTime);
	PointGame* boss;
};
#endif // BlockItem_h__

