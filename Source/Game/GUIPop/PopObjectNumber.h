#ifndef _PopObjectNumber_h__
#define _PopObjectNumber_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"
#include "ui/CocosGUI.h"
#include "PopNumberGroup.h"
using namespace ax;
using namespace ax::ui;
class PopObjectNumber : public Node
{
public:

	PopObjectNumber(void);
	~PopObjectNumber(void);
	Sprite* ball;
	Sprite* border;
	Sprite* bomb;
	Text* label;
	PopNumberGroup* group;
	
	int number;
	float rootX;
	float rootY;
	bool isEffect();
	void playEffect();
	bool getAvailable() const { return available; }
	void setAvailable(bool val) { available = val; }
	void setRootPosition();
	void resetPosition();
	void setNumber(int number);
	int getNumber() { return number; };
	void increaseNumber(int num);
	void callback1();
	void callback2();
	bool checkSame(int _number);
	void moveDown(float time);
	void callbackMoveDown();
	void moveToEat(float time, Vec2 pos);
	void callbackMoveEat();
	void effectNewGame();
	void effectEndGame();
	void showBomb(bool show);
	void setNewNumber();
	
private:
	bool available;
};
#endif
