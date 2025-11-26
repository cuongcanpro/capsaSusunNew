#include "BaseGUI.h"
#include "../GlobalVar.h"
#include "BaseBehavior.h"
#include "BubbleBehavior.h"

BaseGUI::BaseGUI(void)
{
	touchedButton	=	NULL;
	_hasFog			=	false;
	isTouchFog		=	false;
	bgGui			=	NULL;
	isInit			=	false;
	_isShown = false;
	fog				= NULL;
    //retain();
}

void BaseGUI::showGUI(Node* parent, bool hasFog)
{
	if(isShown())
		this->hideGUI();
	if(parent == NULL)
	{
		parent = layerMgr->getLayerByIndex(LAYER_GUI);
	}
	this->parent = parent;

	if(fog == NULL)
	{
		fog= LayerColor::create(Color4B(0, 0, 0, 100) );
		this->addChild(fog);
		
	}
	setVisible(true);
	parent->addChild(this);
	
	
	if(!isInit)
	{
		
		initGUI();
		isInit = true;
	}
	_hasFog = hasFog;
	fog->setVisible(hasFog);
	
	
	_isShown = true;
//	GameSound::playSoundOpenWindow();
}

void BaseGUI::onHideGUI()
{
}

void BaseGUI::hideGUI()
{
	onHideGUI();
	setVisible(false);
	_isShown = false;
	if(parent != NULL)
	{
		parent->removeChild(this);
	}
}

bool BaseGUI::isShown()
{
	return _isShown;
}

bool BaseGUI::isInitted()
{
	return isInit;
}

void BaseGUI::initWithParent(Layer* layer)
{
	layer->addChild(this);
}

void BaseGUI::initWithParent(int LayerID)
{
	// Get layer
	Layer* layer;
	layer = layerMgr->getLayerByIndex(LayerID);
	
	// Attach to layer
	initWithParent(layer);
}

// TODO: write clean up code
BaseGUI::~BaseGUI(void)
{}

void BaseGUI::setKeypadEnabled(bool value) {
   
}

BaseButton* BaseGUI::addButton(int buttonID, GameImage* buttonImage, Node* parent) 
{
	// Create new Button
	BaseButton* createButton =  new BaseButton(buttonID, buttonImage);
	createButton->buttonID = buttonID;

	// Add to button list
	buttonList.insert(std::pair<int, BaseButton*>(buttonID, createButton));
	
	// Add to current rendering layer
	if (parent == NULL)
		this->addChild(createButton->normalImage, 0);
	else
		parent->addChild(createButton->normalImage, 0);
	
	return createButton;
}

BaseButton* BaseGUI::addButton(int buttonID, Rect touchArea)
{
	// Create new Button
	BaseButton* createButton = new BaseButton(buttonID, touchArea, this);
	createButton->buttonID = buttonID;

	// Add to button list
	buttonList.insert(std::pair<int, BaseButton*>(buttonID, createButton));

	return createButton;
}

GameImage* BaseGUI::addImage(const char* nameImg, float x, float y, int idImage, bool frame)
{
	// Create new Image
	GameImage* newImage = new GameImage(nameImg, frame);
	newImage->id = idImage;

	// Add to current rendering layer
	this->addChild(newImage);

	// Set position
	newImage->setPosition(x, y);

	listImage.push_back(newImage);

	return newImage;
}


void BaseGUI::addImage(GameImage *image, int imageId)
{

	// Add to current rendering layer
	this->addChild(image);
	if(imageId != 0)
		image->id = imageId;

	// Add to button list
	listImage.push_back(image);
}

BaseButton* BaseGUI::addButton(int buttonID, const char *pszFilename, BaseBehavior* behavior, Node* parent, bool isFrame)
{
	// Get image
	GameImage *buttonImage = new GameImage(pszFilename, isFrame);

	BaseButton* btn = addButton(buttonID, buttonImage,parent);
	if(behavior != NULL)
		btn->addBehavior(behavior);
	return btn;
}

void BaseGUI::addToListButton(BaseButton *btn, int id)
{
	buttonList.insert(std::pair<int, BaseButton*>(id, btn));
}

void BaseGUI::addButton( BaseButton* btn,int id , Node* parent)
{
	// Create new Button
	btn->buttonID = id;

	// Add to button list
	buttonList.insert(std::pair<int, BaseButton*>(id, btn));

	this->addChild(btn->normalImage);
}



void BaseGUI::setVisible(bool visible)
{
	// Set all child GUIs invisible
	Object *pChild = NULL;
	/*ARRAY_FOREACH(getChildren(), pChild)
	{
	     BaseGUI* GUI = (BaseGUI*)pChild;

		// if (GUI != NULL)
		//	GUI->setVisible(visible);
	}
	*/
	Layer::setVisible(visible);
	//if(hasFog())
	//if(!visible)
	//{
	//	guiMgr->hideFog();
	//}
	//else
	//{
	//	guiMgr->showFog();
	//}
}

void BaseGUI::onEnter()
{
	Director* pDirector = Director::getInstance();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	Node::onEnter();

	if (!isInit)
	{
		initGUI();

	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = AX_CALLBACK_2(BaseGUI::onTouchBegan, this);
	listener->onTouchMoved = AX_CALLBACK_2(BaseGUI::onTouchMoved, this);
	listener->onTouchEnded = AX_CALLBACK_2(BaseGUI::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = AX_CALLBACK_2(BaseGUI::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseGUI::onExit()
{
	Director* pDirector = Director::getInstance();
	//pDirector->getTouchDispatcher()->removeDelegate(this);
	Node::onExit();
}

void BaseGUI::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		// IMPLEMENT YOUR BACK BUTTON LOGIN HERE
		AXLOGD("ON BACK PRESS ");
		onBackKey();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
		// the backspace of PC/Mac is pressed
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		// the escape of PC/Mac is pressed
	}
}

void BaseGUI::onBackKey() {
	
}

void BaseGUI::onButtonTouched(int ButtonID, Touch* touch)
{

}

bool BaseGUI::onTouchBegan(Touch*touch, Event* event)
{
	if (!isVisible()) return false;
	onTouchFirstBegan(touch, event);
	// Check Button click
	std::map<int, BaseButton*>::iterator i;


	// Transverse through all buttons, stop at collided

	i = buttonList.end();
	if (buttonList.size() == 0)
		return true;
	do
	{
		--i;
		BaseButton* TempButton = i->second;

		bool a, b;
		if (TempButton->normalImage != NULL)
		{

			a = TempButton->normalImage->getVisible();
			b = TempButton->normalImage->getParent()->isVisible();
		}
		// For normal Button, check visible first
		if (TempButton->normalImage != NULL)
		if (!TempButton->normalImage->getVisible() &&
			!TempButton->normalImage->getParent()->isVisible())
			continue;

		if (TempButton->getVisible() &&
			TempButton->canTouch)
		{
			if (TempButton->containsTouchLocation(touch))
			{
				if (touchedButton && touchedButton != TempButton)
				{
					runCancelBehavior(touchedButton);
				}
				touchedButton = TempButton;

				// Running touch Button behaviors:
				runTouchBehavior(touch, TempButton);

				touchedButton->onTouched();
				// Logic Callbacks
				onButtonTouched(TempButton->buttonID, touch);

				// End search / Swallow Touch
				return true;
			}
		}
	} while (i != buttonList.begin());
	isTouchFog = hasFog();
	if(bgGui&&bgGui->containsTouchLocation(touch))
	{
		return true;
	}
	return hasFog();
	return false;
}

void BaseGUI::onTouchMoved(Touch*touch, Event* event)
{
	// Call on button drag
	if (touchedButton != NULL)
	{
		if (touchedButton->canMove)
		{
			// Run drag call backs
			runDragBehavior(touch, touchedButton);

			// Logic call back
			onButtonDrag(touchedButton->buttonID, touch);
		}

	}
}

void BaseGUI::onTouchEnded(Touch*touch, Event* event)
{
	// Call on button release
	if (touchedButton != NULL)
	{


		// Run release behavior
		runReleaseBehavior(touch, touchedButton);
		//
		touchedButton->onReleased();
		if (touchedButton->containsTouchLocation(touch) || touchedButton->canTouchOut)

			onButtonRelease(touchedButton->buttonID, touch);

	}

	/*if(guiMgr&&guiMgr->tooltip)
	{
	guiMgr->tooltip->hide();
	}*/

	// Reset Button
	touchedButton = NULL;
	/*if(isTouchFog)
	{
	isTouchFog=false;
	if( bgGui && bgGui->containsTouchLocation(touch) && bgGui->isVisible())
	{
	return;
	}
	if(this->isVisible())
	{
	hide();
	}
	else
	{
	if(hasFog())
	{
	guiMgr->hideFog();
	}
	}
	}*/
}

void BaseGUI::initGUI()
{
	isInit = true;
}

void BaseGUI::onButtonDrag(int buttonID, Touch* touch)
{

}

void BaseGUI::onButtonRelease(int buttonID, Touch* touch)
{

}

void BaseGUI::onButtonAction( int buttonID, int index )
{

}

void BaseGUI::setPos(float x, float y)
{
	this->setPosition(x, y);
}

void runCancelBehavior( BaseButton* touchButton)
{

}
void BaseGUI::runTouchBehavior(Touch*touch, BaseButton* touchButton)
{
	for (unsigned int i=0;i<touchButton->behaviorList.size();i++)
	{
		executeTouchBehavior(touchButton->behaviorList.at(i), touch, touchButton);
	}
}

void BaseGUI::runDragBehavior(Touch*touch, BaseButton* dragButton)
{
	for (unsigned int i=0;i<dragButton->behaviorList.size();i++)
	{
		executeDragBehavior(dragButton->behaviorList.at(i), touch, dragButton);
	}
}

void BaseGUI::runReleaseBehavior(Touch*touch, BaseButton* releaseButton)
{
	for (unsigned int i=0;i<releaseButton->behaviorList.size();i++)
	{
		executeReleaseBehavior(releaseButton->behaviorList.at(i), touch, releaseButton);
	}
}
void BaseGUI::runCancelBehavior( BaseButton* touchButton)
{
	for (unsigned int i=0;i<touchButton->behaviorList.size();i++)
	{
		executeCancelBehavior(touchButton->behaviorList.at(i), touchButton);
	}
}
void BaseGUI::executeDragBehavior(BaseBehavior* behavior, Touch* touch, BaseButton* dragButton)
{
	behavior->onTouchMoved(touch, dragButton);
}

void BaseGUI::executeReleaseBehavior(BaseBehavior* behavior, Touch* touch, BaseButton* releaseButton)
{
	behavior->onTouchEnded(touch, releaseButton);
}

void BaseGUI::executeTouchBehavior(BaseBehavior* behavior, Touch* touch, BaseButton* touchButton)
{
	behavior->onTouchBegan(touch, touchButton);
}
void BaseGUI::executeCancelBehavior(BaseBehavior* behavior,BaseButton* touchButton)
{
	behavior->onCanceled(touchButton);
}
BaseButton* BaseGUI::getButton( int buttonID )
{
	if(buttonList.find(buttonID)!=buttonList.end())
	{
		return  buttonList.at(buttonID);
	}
	return NULL;
}

Action* BaseGUI::runAction(Action* action)
{
	this->stopAllActions();
	return Node::runAction(action);
}

GameImage* BaseGUI::getImage(int imageId)
{
	/*if(imageList.find(imageId)!=imageList.end())
	{
		return  imageList.at(imageId);
	}*/
	return NULL;
}

void BaseGUI::removeImage( int idImage )
{
	GameImage *image;
	if(listImage.size() > 0)
	{
		for(int i = 0; i < listImage.size(); i++)
		{
			image = listImage[i];
			if(image != NULL && image->id == idImage)
			{
				this->removeChild(image);
				listImage.erase(listImage.begin() + i);
				image->clear();
			}
		}
	}
}

void BaseGUI::removeImage(GameImage* image)
{
	for(int i = 0; i < listImage.size(); i++)
	{
		if(listImage[i] == image)
		{
			listImage.erase(listImage.begin() + i);
			break;
		}
	}
	//if(listImage.size() > 0)
		//listImage.erase(find(listImage.begin(), listImage.end(), image) );
	this->removeChild(image);
	image->clear();
}



void BaseGUI::removeButton( int idButton )
{
	BaseButton*btn;
	if(buttonList.size()>0)
	{
		if(buttonList.find(idButton)!=buttonList.end())
		{	
			btn=buttonList.at(idButton);
			if (btn!=NULL)
			{
				buttonList.erase(idButton);
				delete btn;
				btn=NULL;
			}
		}
	}
	
}

ax::Point BaseGUI::getPos()
{
	return this->getPosition();
}

void BaseGUI::show()
{
	this->setVisible(true);
	/*if(hasFog())
	{
		guiMgr->showFog();
	}*/
	/*ActionInterval*  actionTo = ScaleTo::create(0.46f,1.0f);
		ActionInterval* move_ease_in = EaseBackOut::create((ActionInterval*)actionTo->copy()->autorelease());
	this->runAction(move_ease_in);*/
}

void BaseGUI::hide()
{
	this->setVisible(false);
	//if(hasFog())
	//{
	//	guiMgr->hideFog();
	//}

}

void BaseGUI::onTouchFirstBegan(Touch*touch, Event* event)
{

}

void BaseGUI::setFog( bool fog )
{
	_hasFog= fog;
}

bool BaseGUI::hasFog()
{
	return _hasFog;
}

void BaseGUI::onUpdate(float delta)
{

}

void BaseGUI::disableGUI()
{

}

void BaseGUI::enableGUI()
{

}

BaseButton* BaseGUI::getTouchedButton()
{
	return touchedButton;
}

void BaseGUI::moveHorizontal(Node* btn, float sX, float dX, float delay)
{
    btn->setPositionX(sX + dX);
    btn->setOpacity(0);
    btn->runAction(Sequence::create(DelayTime::create(delay),
                                      EaseBackOut::create(MoveBy::create(0.5, Vec2(-dX, 0))), NULL));
    btn->runAction(Sequence::create(DelayTime::create(delay), FadeIn::create(0.7), NULL));
}

void BaseGUI::moveVertical(Node* btn, float sY, float dY, float delay)
{
    btn->setPositionY(sY + dY);
    btn->setOpacity(0);
    btn->runAction(Sequence::create(DelayTime::create(delay),
                                      EaseBackOut::create(MoveBy::create(0.5, Vec2(0, -dY))), NULL));
    btn->runAction(Sequence::create(DelayTime::create(delay), FadeIn::create(0.7), NULL));
}

void BaseGUI::moveEffect(Node* node, float dx, float dy, float delay)
{
    node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
    node->runAction(
        Sequence::create(DelayTime::create(delay), EaseBackOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))), NULL));
}

void BaseGUI::moveEffectSineOut(Node* node, float dx, float dy, float delay)
{
    node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
    node->runAction(
        Sequence::create(DelayTime::create(delay), EaseSineOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))), NULL));
}

void BaseGUI::moveOutEffect(Node* node, float dx, float dy, float delay)
{
    node->runAction(
        Sequence::create(DelayTime::create(delay), EaseBackIn::create(MoveBy::create(0.7, Vec2(dx, dy))), NULL));
}

void BaseGUI::moveElement(Node* btn, float dx, float dy, float delay)
{
    btn->setPositionX(btn->getPositionX() - dx);
    btn->setPositionY(btn->getPositionY() - dy);
    btn->setOpacity(0);
    btn->runAction(Sequence::create(
        DelayTime::create(delay),
        Spawn::create(EaseBackOut::create(MoveBy::create(0.5, Vec2(dx, dy))), FadeIn::create(0.7), NULL), NULL));
}

GameImage* BaseGUI::addImageToNode(const char* nameImg, Node* parent, float x, float y, int idImage, bool frame)
{
    // Create new Image
    GameImage* newImage = new GameImage(nameImg, frame);
    newImage->id        = idImage;

    // Add to current rendering layer
    if (parent == NULL)
        this->addChild(newImage);
    else
        parent->addChild(newImage);

    // Set position
    newImage->setPosition(x, y);

    listImage.push_back(newImage);

    return newImage;
}

Text* BaseGUI::addText(string text, Node* parent)
{
    Text* lb = Text::create(text, "fonts/tahoma.ttf", 20);
    if (parent != NULL)
        parent->addChild(lb);
    else
        addChild(lb);
    return lb;
}
