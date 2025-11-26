#include "GUITypeNormal.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"


#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_NORMAL_ID 3
#define BTN_EXTEND_ID 4


GUITypeNormal::GUITypeNormal(void) : BaseGUI()
{
	BaseGUI();
	setKeypadEnabled(true);
}

GUITypeNormal::~GUITypeNormal(void)
{
}


void GUITypeNormal::initGUI(){
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    callBackSplash();
	
}

void GUITypeNormal::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().isCallBackPress = true;
        game->endGame();
	}
}


void GUITypeNormal::callBackSplash()
{
	BaseGUI::initGUI();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	GameImage* background = addImage("background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);


	btnBack = addButton(BTN_BACK_ID, "btnBack.png", new BubbleBehavior(), NULL, false);
	if (size.width / size.height < 11.0 / 20.0) {
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 1.1f);
	}
	else {
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);
	}

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png", new BubbleBehavior(), NULL, false);
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if (game->music)
	{
            btnSound->normalImage->setImage("btnSoundOn.png", false);
	}
	else
	{
            btnSound->normalImage->setImage("btnSoundOff.png", false);
	}

	//auto *label = Label::createWithTTF(CCLocalizedString("CHOOSE_TYPE").c_str(), "fonts/tahomabd.ttf", 24);
	//label->setHorizontalAlignment(TextHAlignment::CENTER);
	//label->setWidth(size.width * 0.8);
	////	label->setScale(0.8);
	//this->addChild(label);
	
	btnNormal = addButton(BTN_NORMAL_ID, "btnNormal.png", new BubbleBehavior(), NULL, false);
	btnNormal->setPosition(size.width * 0.5, size.height * 0.7);
	//label->setPosition(size.width * 0.5f, btnNormal->getPositionY() + btnNormal->getHeight() * 1.0f);

    btnExtend = addButton(BTN_EXTEND_ID, "btnExtend.png", new BubbleBehavior(), NULL, false);
    btnExtend->setPosition(btnNormal->getPositionX(), btnNormal->getPositionY() - btnNormal->getHeight() * 1.5f);

	arrayButton.push_back(btnNormal);
    arrayButton.push_back(btnExtend);
}

void GUITypeNormal::onButtonRelease(int buttonID, Touch* touch)
{
	AXLOGD("Click here ");
	string packageApp = JNIUtils::getPackageApp();
	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_BACK_ID:
		{
		onBackKey();
			
		}
		
		break;
	case BTN_SOUND_ID:
		{
		//JNIUtils::openApp("com.bcsofts.colorLines2016&referrgder=lfdjflfdjlfsj");
			game->music = !game->music;
			if(game->music)
			{
                            btnSound->normalImage->setImage("btnSoundOn.png", false);
			}
			else
			{
                            btnSound->normalImage->setImage("btnSoundOff.png", false);
			}

			UserDefault::getInstance()->setBoolForKey("music", game->music);
			UserDefault::getInstance()->flush();
		}
		break;
	
	case BTN_NORMAL_ID:
		{
		//game->loadPlayNormal();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().guiBubble->showGuiWithMode(0);
		}
		break;
	case BTN_EXTEND_ID:
	{
		//game->loadPlayNormal();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().guiBubble->showGuiWithMode(1);
	}
	break;

	default:
		break;
	}
}

void GUITypeNormal::initAds()
{
	
}


void GUITypeNormal::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
	BaseGUI::showGUI(parent, hasFog);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	float sY = size.height - btnBack->getHeight() * 0.7;
	float sX = size.width * 0.5;

	moveVertical(btnBack->normalImage->_img, 0, 400, 0);
	moveVertical(btnSound->normalImage->_img, 0, 400, 0.1);

	for (int i = 0; i < arrayButton.size(); i++) {
		moveHorizontal(arrayButton.at(i)->normalImage->_img, 0, i % 2 == 0 ? -400 : 400, 0.1 + 0.05 * i);
	}
}

void GUITypeNormal::updateButton()
{
	
//	btnCapsa->setVisible(false);
}
