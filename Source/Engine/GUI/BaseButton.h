#ifndef BaseButton_h__
#define BaseButton_h__

#include "GameImage.h"
#include <vector>
#include "axmol.h"

using namespace ax;
using namespace std;
class BaseBehavior;
class BaseGUI;
class BaseButton
{

// Data
public:
	GameImage* normalImage;
	int buttonID;
	string idObjet;
	Rect touchArea;
	// Only avalaible in buttons using touchArea
	Node* parent;
	Vec2	touchPosition;

	// Buttons Behavior list
	vector<BaseBehavior*> behaviorList;
	bool canTouch;
	bool canMove;
	bool canTouchOut;
	BaseGUI* baseGui;
public:
	BaseButton(void);
	BaseButton(int buttonID, GameImage* image);
	BaseButton(int buttonID, Rect touchArea, Node* parent);
	~BaseButton(void);
	void setEnable(bool enable=true);
	void setDisable();
        void addIcon(GameImage* icon, Vec2 pos);
	void setPosText(float x,float y);

public:
	bool containsTouchLocation(Touch* touch);
	void setPosition(float x, float y);
	Vec2 getPosition();
	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight();
	void updatePosOfBehavior();

	// Add a behavior to the list
	void addBehavior(BaseBehavior* behavior);
	bool hasBehavior(int idBehavior);

	void setVisible(bool visible,bool visibleBehavior);
	void setVisible(bool visible);
	bool getVisible();
	bool isEnable();
	BaseBehavior* getBehavior(int id);
	void clear();
	void setParent(BaseGUI* baseGui);
public:
	virtual void onTouched();
	virtual void onReleased();
private:
	BaseGUI* _baseGui;
};

#endif // BaseButton_h__
