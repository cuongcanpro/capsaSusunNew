#ifndef _ObjectNumber_h__
#define _ObjectNumber_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ax::ui;
class ObjectNumber : public Node
{
public:

	ObjectNumber(void);
	~ObjectNumber(void);
	Sprite* ball;
	Sprite* border;
	Text* label;
//	DBCCArmatureNode* eff;
//	DBCCArmatureNode* eff1;
	
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
	
private:
	bool available;
};
#endif
