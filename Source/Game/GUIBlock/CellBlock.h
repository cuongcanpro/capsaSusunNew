#pragma once
#ifndef CellBlock_h__
#define CellBlock_h__
#include "../../Engine/GUI/GameImage.h"
#include "string"
#include "ui/CocosGUI.h"

using namespace std;
using namespace ax;
using namespace ax::ui;
enum CellBonus {
	NONE = 0,
	X2 = 1,
	BOMB = 2,
	EXCHANGE = 3,
	EXTRA = 4
};

class CellBlock : public Node
{
public:
	CellBlock(void);
	~CellBlock(void);
	bool isVibrate;
	void doVibrate(bool vibrate);
	void callbackVibrate();
	CellBonus idBonus;
	void setBg(int id);
	void setBonus(CellBonus idBonus, int num = 0);
	void decreaseBonus();
	ImageView* bg;
	ImageView* iconBonus;
	Text* lbNum;
	int num;
	void setWidth(float width);
	void setHeight(float height);
	float getWidth();
	float getHeight();
	float getRealWidth();
	float getRealHeight();
	void endGame(float time);
	void callbackEndGame();
	void newGame();
	void doVibrateNTime(int n);
};
#endif // CellBlock_h__

