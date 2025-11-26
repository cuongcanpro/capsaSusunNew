#include "GUIChoose.h"
#include "Game/Utility/GameSound.h"
#include "Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "Engine/GUI/ParticleEffect.h"
#include "../Utility/JNIUtils.h"
#include "Game/Utility/GameUtility.h"

#define BTN_BACK 1
#define BTN_SOUND 2
#define BTN_STOMP 3
#define BTN_TIME 4
#define BTN_END 5
#define BTN_LINES 6
#define BTN_TWENTY 7
#define BTN_MERGE 8
#define BTN_VIBRATE 9
#define BTN_MINESWEEPER 10

GUIChoose::GUIChoose(void)
{
	setKeypadEnabled(true);
}


GUIChoose::~GUIChoose(void)
{
}

void GUIChoose::initGUI(){
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    callBackSplash();
	//runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create(this, callfunc_selector(GUIChoose::callBackSplash)), NULL));
}

void GUIChoose::onBackKey(void)
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this) {
		game->endGame();
	}
}

void GUIChoose::callBackSplash()
{
	BaseGUI::initGUI();
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	GameImage* background = addImage("bg.jpg");
	background->setAnchorPoint(Vec2(0, 0));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	btnBack = addButton(BTN_BACK, "btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);

	btnSound = addButton(BTN_SOUND, "btnSoundOff.png");
	btnSound->setPosition(btnBack->getPositionX() - btnSound->getWidth() * 1.2f, btnBack->getPositionY());

	if(game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png");
	}

    btnVibrate = addButton(BTN_VIBRATE, "btnSoundOff.png");
    btnVibrate->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.2f, btnBack->getPositionY());
    loadVibrate();

	float pad = 1.6f;
	if (size.width / size.height >= 2.0f / 3.0f) {
		pad = 1.4f;
	}

    btnLines = addButton(BTN_LINES, "lines.png");
    btnLines->setPosition(size.width * 0.5f, btnBack->getPositionY() - btnLines->getHeight() * 0.6);
    labelLine = Text::create("LINE 98", "fonts/tahomabd.ttf", 30);
    btnLines->normalImage->addChild(labelLine);
    labelLine->setPosition(Vec2(0, - btnLines->getHeight() * 0.65f));
    
	btnEndless = addButton(BTN_END, "endless.png");
	btnEndless->setPosition(size.width * 0.25f, btnLines->getPositionY() - btnLines->getHeight() * 1.1f);
    labelEndless = Text::create("Egg Shoot", "fonts/tahomabd.ttf", 22);
    btnEndless->normalImage->addChild(labelEndless);
    labelEndless->setPosition(Vec2(0, -btnEndless->getHeight() * 0.8f));

    btnMinesweeper = addButton(BTN_MINESWEEPER, "btnMine.png");
    btnMinesweeper->setPosition(size.width * 0.75f, btnEndless->getPositionY());
    Text* label = Text::create("Minesweeper", "fonts/tahomabd.ttf", 22);
    btnMinesweeper->normalImage->addChild(label);
    label->setPosition(Vec2(0, -btnMinesweeper->getHeight() * 0.8f));

    btnMerge = addButton(BTN_MERGE, "btnMerge.png");
    btnMerge->setPosition(btnEndless->getPositionX(), btnEndless->getPositionY() - btnEndless->getHeight() * 1.8);
    labelMerge = Text::create("Number Drop", "fonts/tahomabd.ttf", 22);
    btnMerge->normalImage->addChild(labelMerge);
    labelMerge->setPosition(Vec2(0, -btnMerge->getHeight() * 0.8f));

    btnTwenty = addButton(BTN_TWENTY, "twenty.png");
    btnTwenty->setPosition(btnMinesweeper->getPositionX(), btnMerge->getPositionY());
    labelTwenty = Text::create("Twenty Number", "fonts/tahomabd.ttf", 22);
    btnTwenty->normalImage->addChild(labelTwenty);
    labelTwenty->setPosition(Vec2(0, -btnTwenty->getHeight() * 0.8f));

    btnStomp = addButton(BTN_STOMP, "stomp.png");
    btnStomp->setPosition(btnMerge->getPositionX(), btnMerge->getPositionY() - btnMerge->getHeight() * 1.8);
    labelStomp = Text::create("Egg Shoot Stomp", "fonts/tahomabd.ttf", 22);
    btnStomp->normalImage->addChild(labelStomp);
    labelStomp->setPosition(Vec2(0, -btnStomp->getHeight() * 0.8f));

	btnTime = addButton(BTN_TIME, "timetrial.png");
    btnTime->setPosition(btnTwenty->getPositionX(), btnStomp->getPositionY());
    labelTime = Text::create("Eggh Shoot Timerial", "fonts/tahomabd.ttf", 22);
    btnTime->normalImage->addChild(labelTime);
    labelTime->setPosition(Vec2(0, -btnTime->getHeight() * 0.8f));

	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	string s = "particles/leaf.plist";
	//	s = "particles/vip.plist";

	ParticleEffect *effect = new ParticleEffect();
	effect->create(s.c_str(), layer);
	effect->particle->setPosition(size.width * 0.5f, size.height);
	effect->particle->setBlendAdditive(false);
    btnVibrate->setVisible(false);
}

void GUIChoose::showGUI(Node* parent, bool hasFog )
{
	JNIUtils::showAdsBanner(1);
    BaseGUI::showGUI(parent, hasFog);
    if(game->music && isInitted())
    {
        btnSound->normalImage->setImage("btnSoundOn.png");
    }
    else
    {
        btnSound->normalImage->setImage("btnSoundOff.png");
    }

    float pad = 300;

    moveElement(btnLines->normalImage, 0, -pad, 0.1);

    moveElement(btnStomp->normalImage, pad, 0, 0.2);
    moveElement(btnMinesweeper->normalImage, -pad, 0, 0.2);
    
    moveElement(btnMerge->normalImage, pad, 0, 0.3);
    moveElement(btnTwenty->normalImage, -pad, 0, 0.3);

    moveElement(btnEndless->normalImage, pad, 0, 0.4);
    moveElement(btnTime->normalImage, -pad, 0, 0.4);
}

void GUIChoose::onButtonRelease( int buttonID, Touch* touch )
{
	GameSound::playClick();
    //if (buttonID != BTN_BACK && game->isInitAds == false) {
    //    string packageApp = JNIUtils::getPackageApp();
    //    if (packageApp.compare("com.lightgames.eggShoot2017") == 0) {
    //        // google test
    //        AXLOGD("INIT ADS");
    //        //JNIUtils::initAds("ca-app-pub-3500982632045294~9038691366", "ca-app-pub-3940256099942544/6300978111", "ca-app-pub-3940256099942544/1033173712", 1, 1);

    //        // my ads
    //       // idAdsBanner = 1;
    //       // JNIUtils::initAds("ca-app-pub-3500982632045294~7897289512", "ca-app-pub-3500982632045294/3958044502", "ca-app-pub-3500982632045294/7182634333", idAdsBanner, idAdsBanner); // viettv
    //    }
    //    else {
    //        AXLOGD("PACKAGE %s", packageApp.c_str());
    //    }
    //}
    game->initAds();
	
	switch (buttonID)
	{
	case BTN_BACK:
		{

			game->endGame();
		}

		break;
	case BTN_SOUND:
		{
			
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("btnSoundOn.png");
			}
			else
			{
				btnSound->normalImage->setImage("btnSoundOff.png");
			}

			UserDefault::getInstance()->setBoolForKey("music", game->music);
			UserDefault::getInstance()->flush();

		}
		break;
        case BTN_VIBRATE:
		{
			game->vibrate = !game->vibrate;
            loadVibrate();
			UserDefault::getInstance()->setBoolForKey("vibrate", game->vibrate);
			UserDefault::getInstance()->flush();

		}
		break;
	case BTN_END:
		{
            JNIUtils::sendEvent("game_endless", "1");
		GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().guiGame->showGui(ENDLESS);
		return;
			
		}
		break;
	case BTN_TWENTY:
	{
            JNIUtils::sendEvent("game_twenty", "1");
		GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().guiTwenty->showGui();
	}
	break;
	case BTN_MERGE:
	{
            JNIUtils::sendEvent("game_dropNumber", "1");
		GUIManager::getInstance().removeAllGui();
       // GUIManager::getInstance().guiMerge->showGUI();
	}
	break;
	case BTN_STOMP:
		{
            JNIUtils::sendEvent("game_stomp", "1");
			GUIManager::getInstance().removeAllGui();

		}
		break;
	case BTN_TIME:
		{
            JNIUtils::sendEvent("game_time", "1");
		GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().guiGame->showGui(TIME);
		//GUIManager::getInstance().guiTop.showTop(TOP_TIME);
		}
		break;
	case BTN_LINES:
		{
            JNIUtils::sendEvent("game_line", "1");
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().guiLine->showGui();
		
		}
		break;
    case BTN_MINESWEEPER:
    {
        JNIUtils::sendEvent("game_minesweeper", "1");
        GUIManager::getInstance().removeAllGui();
        //GUIManager::getInstance().showGui(&GUIManager::getInstance().guiBomb);
    }
    break;
	default:
		break;
	}
}

void GUIChoose::loadVibrate() {

    if (game->vibrate)
    {
        btnVibrate->normalImage->setImage("btnSoundOn.png");
    }
    else
    {
        btnVibrate->normalImage->setImage("btnSoundOff.png");
    }
}
