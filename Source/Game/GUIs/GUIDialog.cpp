#include "GUIDialog.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../Utility/GameSound.h"

#define GUI_DIALOG_BTN_OK 1
#define GUI_DIALOG_BTN_CANCEL 2
#define GUI_DIALOG_BTN_OK_ONLY 3

#define GUI_DIALOG_IMG_BG "bgDialog.png"
#define GUI_DIALOG_IMG_BTN_AGREE "btnOk.png"
#define GUI_DIALOG_IMG_BTN_CANCEL "btnCancel.png"
#define GUI_DIALOG_IMG_BTN_CHANGE "GUI/GUIDialog/btnChangeGold.png"
std::string GUIDialog::className = "GUIDialog";
void GUIDialog::initGUI()
{
	BaseGUI::initGUI();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	groupAll = new Node();
	addChild(groupAll);
	this->setPos(origin.x, origin.y);

	bgGui = new GameImage(GUI_DIALOG_IMG_BG, false);
	bgGui->setPos(size.width/2, size.height/2);
	groupAll->addChild(bgGui);
	
	/*btnOk = this->addButton(GUI_DIALOG_BTN_OK, GUI_DIALOG_IMG_BTN_AGREE);
	btnOk->setPosition(size.width/2 - 100, size.height/2 - bgGui->getHeight() * 0.36f);*/

	btnOk = new BaseButton(GUI_DIALOG_BTN_OK, new GameImage(GUI_DIALOG_IMG_BTN_AGREE, false));
	groupAll->addChild(btnOk->normalImage);
	addToListButton(btnOk, GUI_DIALOG_BTN_OK);
	btnOk->setPosition(0, size.height/2 - bgGui->getHeight() * 0.28f);
	btnOk->addBehavior(new BubbleBehavior());
	
	btnCancel = new BaseButton(GUI_DIALOG_BTN_CANCEL, new GameImage(GUI_DIALOG_IMG_BTN_CANCEL, false));
	groupAll->addChild(btnCancel->normalImage);
	addToListButton(btnCancel, GUI_DIALOG_BTN_CANCEL);
	btnCancel->setPosition(0, btnOk->getPositionY());
	btnCancel->addBehavior(new BubbleBehavior());
	

	labelMessage = Label::createWithTTF("Content Dialog", "fonts/tahomabd.ttf", 25);
    labelMessage->setColor(Color3B(249, 248, 211));
	labelMessage->setHorizontalAlignment(TextHAlignment::CENTER);
	labelMessage->setPosition(size.width / 2, size.height / 2 + bgGui->getHeight() * 0.15f);
	labelMessage->setWidth(bgGui->getWidth() * 0.9f);
	groupAll->addChild(labelMessage);
	setContentSize(Size(size.width, size.height));
	groupAll->setContentSize(Size(size.width, size.height));
	groupAll->setPosition(size.width / 2, size.height / 2);
}

void GUIDialog::onButtonRelease(int buttonId, Touch* event)
{
	GUIManager::getInstance().removeFromListGui();
    GameSound::playClick();
	switch(buttonId)
	{
	case GUI_DIALOG_BTN_OK:
	case GUI_DIALOG_BTN_OK_ONLY:
		//this->hideGUI();
		if(okFunction != NULL)
			okFunction();
		break;
	case GUI_DIALOG_BTN_CANCEL:
		//this->hideGUI();
		if(cancelFunction != NULL)
			cancelFunction();
		break;
	}

	
}

void GUIDialog::showGUI(const char* message, void (*okFunction)(), bool onlyOk, void (*cancelFunction)(), const char* sourceOK, const char* sourceCancel)
{
	if(isShown())
		GUIManager::getInstance().removeFromListGui();
	this->okFunction = okFunction;
	this->cancelFunction = cancelFunction;

	setVisible(true);


	if(parent == NULL)
	{
		parent = layerMgr->getLayerByIndex(LAYER_GUI);
	}
	this->parent = parent;
	if(fog == NULL)
	{
		fog= LayerColor::create( Color4B(0, 0, 0, 10) );
		this->addChild(fog);

	}
	parent->addChild(this, 1);
	if(!isInit)
	{

		initGUI();
		isInit = true;
	}
        Size size = Director::getInstance()->getRenderView()->getVisibleSize();
        groupAll->setPosition(Vec2(size.width / 2, size.height / 2));
        fog->setContentSize(size);
	fog->setVisible(true);
	_hasFog = true;
	_isShown = true;


	if(sourceOK == NULL)
	{
		btnOk->normalImage->setImage(GUI_DIALOG_IMG_BTN_AGREE, false);
	}
	else
	{
            btnOk->normalImage->setImage(sourceOK, false);
	}
	if(sourceCancel == NULL)
	{
            btnCancel->normalImage->setImage(GUI_DIALOG_IMG_BTN_CANCEL, false);
	}
	else
	{
            btnCancel->normalImage->setImage(sourceCancel, false);
	}

	labelMessage->setString(message);
	
	Size size1 = groupAll->getContentSize();
    if (!onlyOk)
    {
        float pad = (bgGui->getWidth() - btnCancel->getWidth() - btnOk->getWidth()) / 3;
        btnOk->setPosition(size1.width / 2 - bgGui->getWidth() / 2 + pad + btnOk->getWidth() / 2,
                            btnOk->getPositionY());
        btnCancel->setPosition(btnOk->getPositionX() + btnOk->getWidth() / 2 + pad + btnCancel->getWidth() / 2,
                                btnCancel->getPositionY());

        btnCancel->setVisible(true);
        btnOk->setVisible(true);
    }
    else
    {
        btnOk->setPosition(size1.width / 2, btnOk->getPositionY());
        btnCancel->setVisible(false);
        btnOk->setVisible(true);

        /*btnOk->setPosition(size.width/2 - 100, size.height/2 - 90);
        btnCancel->setPosition(size.width/2 + 100, size.height/2 - 90);
        btnCancel->setVisible(true);*/
    }

	GUIManager::getInstance().addToListGui(this);
	groupAll->setAnchorPoint(Vec2(0.5f, 0.5f));
	
	groupAll->setScale(0.2f);
	ActionInterval *a1 = EaseBackOut::create(ScaleTo::create(0.4f, 1, 1));
//	ActionInterval* move_ease_out = EaseBounceOut::create((ActionInterval*)(a1->copy()->autorelease()) );
	
	groupAll->runAction(a1);
	
	fog->setOpacity(0);
	
	FadeTo *tintTo = FadeTo::create(0.75f, 180);
	fog->runAction(tintTo);
	
}

void GUIDialog::onHideGUI()
{
	this->okFunction = NULL;
	this->cancelFunction = NULL;
}
