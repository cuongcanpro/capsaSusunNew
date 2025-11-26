#include "ChooseGameScene.h"
#include "core/utils/LanguageMgr.h"
#include "Game/Utility/JNIUtils.h"
#include "core/utils/TienlenGameSound.h"
#include "core/gui/SceneMgr.h"
#include "gameTienlen/ui/LobbyScene.h"
#include "gameTala/ui/TalaLobbyScene.h"
#include "app/GameMgr.h"
#include "ChooseCardGUI.h"
#include "gameBinh/ui/BinhLobbyScene.h"
#include <Game/GUIManager.h>

#define NUM_DOT  42

#define WIDTH_ROW 383
#define HEIGHT_ROW 60
ChooseGameScene::ChooseGameScene()
{

}

ChooseGameScene::~ChooseGameScene()
{

}

bool ChooseGameScene::init()
{
	BaseLayer::init();
	//setKeyboardEnabled(true);
	initGUI();
	
	return true;
}

void ChooseGameScene::initGUI()
{
	Size size = Director::getInstance()->getVisibleSize();


	// BG LOADING
	auto bg = Sprite::create("GuiGame/bg.jpg");
	bg->setScaleX(size.width / bg->getContentSize().width);
	bg->setScaleY(size.height / bg->getContentSize().height);
	//bg->setScale(_scale);
	addChild(bg);
	bg->setPosition(size.width / 2, size.height / 2);
//	bg->setOpacity(10);

	
	string resource = "Card/IconInGameTienLen.png";
	btnTienLen = Button::create(resource, resource, resource);
	btnTienLen->setPosition(Vec2(size.width * 0.5, size.height * 0.5));
	addChild(btnTienLen);

	btnTienLen->addClickEventListener([this](Object*) {
		if (gameMgr->checkUpdate())
			return;
		sceneMgr->openScene(LobbyScene::className);
		JNIUtils::sendEvent("game_tienlen", "1");
	});

	resource = "Card/IconInGameTala.png";
	btnTala = Button::create(resource, resource, resource);
	btnTala->setPosition(Vec2(size.width * 0.5 - btnTala->getContentSize().width * 1.3, size.height * 0.5));
	addChild(btnTala);

	btnTala->addClickEventListener([this](Object*) {
		if (gameMgr->checkUpdate())
			return;
		sceneMgr->openScene(TalaLobbyScene::className);
		JNIUtils::sendEvent("game_tala", "1");
	});


	resource = "Card/IconMauBinh.png";
	btnBinh = Button::create(resource, resource, resource);
	btnBinh->setPosition(Vec2(size.width * 0.5 + btnBinh->getContentSize().width * 1.3, size.height * 0.5));
	addChild(btnBinh);

	btnBinh->addClickEventListener([this](Object*) {
		if (gameMgr->checkUpdate())
			return;
		sceneMgr->openScene(BinhLobbyScene::className);
		JNIUtils::sendEvent("game_binh", "1");
	});


	resource = "Board/BlueTheme/btnBack.png";
	btnBack = Button::create(resource, resource, resource);
    btnBack->setPosition(Vec2(size.width - btnBack->getContentSize().width * 0.7,
                                  size.height - btnBack->getContentSize().height * 0.7));
	addChild(btnBack);

	btnBack->addClickEventListener([this](Object*) {
		backKeyPress();
	});

	resource = "Board/Dialog/cardSelect_0.png";
	Button* btnCard = Button::create(resource, resource, resource);
	btnCard->setPosition(Vec2(size.width - btnCard->getContentSize().width * 0.6 * 0.7, size.height - btnCard->getContentSize().height * 0.6 * 0.7));
	addChild(btnCard);
	btnCard->setScale(0.7);

	btnCard->addClickEventListener([this](Object*) {
		sceneMgr->openGUI(ChooseCardGUI::className, 205, 205);
	});
    btnCard->setVisible(false);
    
}

void ChooseGameScene::onEnterFinish()
{
	
    Size size = Director::getInstance()->getVisibleSize();
    moveVertical(btnTala, size.height * 0.5, 500, 0);
    moveVertical(btnTienLen, size.height * 0.5, 500, 0.1);
    moveVertical(btnBinh, size.height * 0.5, 500, 0.2);
    moveHorizontal(btnBack, btnBack->getContentSize().width * 0.8, -200, 0.0);
}

const std::string ChooseGameScene::className = "ChooseGameScene";

void ChooseGameScene::callbackLoading()
{
}

void ChooseGameScene::backKeyPress()
{
	//gameMgr->endGame();
    
    sceneMgr->layerGUI    = nullptr;
    sceneMgr->layerSystem = nullptr;
    Director::getInstance()->replaceScene(mainScene);
    sceneMgr->curGui = "";
}
