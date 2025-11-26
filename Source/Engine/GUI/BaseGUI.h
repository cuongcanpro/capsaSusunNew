#ifndef BaseGUI_h__
#define BaseGUI_h__

#include "axmol.h"
//#include "Gui/Image.h"

#include <map>
//#include "RenderingSurface.h"
#include "BaseButton.h"
//#include "LabelBM.h"
#include "../Layers/GameLayer.h"
//#include "axmol-ext.h"
#include "BubbleBehavior.h"
#include "extensions/axmol-ext.h"
#include "ui/CocosGUI.h"
using namespace ax;
using namespace ax::ui;
using namespace std;

class BaseGUI : public Layer
{
protected:
	// Rendering Unit (Layer)
//	RenderingSurface* RenderLayer;
	bool _hasFog;
	bool isTouchFog;
	GameImage* bgGui;
	LayerColor* fog;
	bool _isShown;

	// Check to init this GUI once
	bool isInit;

	vector<GameImage*> listImage;
	Node* parent;
public:
	map<int, BaseButton*> buttonList;
	bool isShown();
protected:



	// Current touched button
	// TODO: replace for multitouches on multiple buttons
	BaseButton *touchedButton;

public:
	BaseGUI(void);
	~BaseGUI(void);
        void setKeypadEnabled(bool value);
	void initWithParent(Layer* layer);
	void initWithParent(int LayerID);
	void setFog(bool fog);
	bool hasFog();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//void keyBackClicked();
	virtual void onBackKey();
	virtual void showGUI(Node* parent = NULL, bool hasFog = true);
	void hideGUI();
	void onHideGUI();
	bool isInitted();
	int lastGUI;

public:
 
	BaseButton* addButton(int buttonID, GameImage* buttonImage, Node* parent = NULL);
	BaseButton* addButton(int buttonID, const char *pszFilename, BaseBehavior* behavior = new BubbleBehavior(), Node* parent = NULL, bool isFrame = NULL);
	BaseButton* addButton(int buttonID, Rect touchArea);
	void addButton(BaseButton* btn,int id, Node* parent = NULL);

	BaseButton* getButton(int buttonID);
	void initRenderSurface();
	
	GameImage* addImage(const char* nameImg, float x = 0, float y = 0, int imageId = 0, bool frame = false);
	void addImage(GameImage *image, int imageId = 0);
	GameImage* getImage(int imageId);
	virtual void	setVisible(bool visible);

	virtual void setPos(float x, float y);
	Vec2 getPos();
    void moveHorizontal(Node* btn, float sX, float dX, float delay);
    void moveVertical(Node* btn, float sY, float dY, float delay);
    void moveEffect(Node* node, float dx, float dy, float delay);
    void moveEffectSineOut(Node* node, float dx, float dy, float delay);
    void moveOutEffect(Node* node, float dx, float dy, float delay);
    void moveElement(Node* btn, float dx, float dy, float delay);
        // Event Handlers
public:
	void onEnter();
	void onExit();

// Inherit events
public:
	// Call backs for input events
	virtual bool onTouchBegan(Touch*touch, Event* event);
	virtual void onTouchMoved(Touch*touch, Event* event);
	virtual void onTouchEnded(Touch*touch, Event* event);

	// Call backs to execute button behaviors

	void runTouchBehavior(Touch*touch, BaseButton* touchButton);
	void runDragBehavior(Touch*touch, BaseButton* dragButton);
	void runReleaseBehavior(Touch*touch, BaseButton* releaseButton);
	void runCancelBehavior( BaseButton* touchButton);

	// Call backs to derived button behaviors execution
	virtual void executeTouchBehavior(BaseBehavior* behavior, Touch* touch, BaseButton* touchButton);
	virtual void executeDragBehavior(BaseBehavior* behavior, Touch* touch, BaseButton* dragButton);
	virtual void executeReleaseBehavior(BaseBehavior* behavior, Touch* touch, BaseButton* releaseButton);
	virtual void executeCancelBehavior(BaseBehavior* behavior,BaseButton* touchButton);

	// Call backs to derived logic execution
	virtual void onButtonTouched(int ButtonID, Touch* touch);
	virtual void onButtonDrag(int buttonID, Touch* touch);
	virtual void onButtonRelease(int buttonID, Touch* touch);
	virtual void onButtonAction(int buttonID, int index);
	
	// Call backs to GUIs initialisation
	virtual void initGUI();
	virtual void disableGUI();
	virtual void enableGUI();

	Action* runAction(Action* action);


	void removeImage(int idImage);
	void removeImage(GameImage* image);
	void removeLabelBM(int idLabel);
	void removeButton(int idButton);

	BaseButton* getTouchedButton();
    GameImage* addImageToNode(const char* nameImg, Node* parent = NULL, float x = 0, float y = 0, int imageId = 0, bool frame = false);
    Text* addText(string text, Node* parent = NULL);

public:
	virtual void show();
	virtual void hide();
public:
	virtual void onTouchFirstBegan(Touch*touch, Event* event);
	virtual void onUpdate(float delta);
	void addToListButton(BaseButton *btn, int id);
};

#endif // BaseGUI_h__
