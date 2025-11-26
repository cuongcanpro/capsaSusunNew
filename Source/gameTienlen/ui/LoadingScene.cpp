#include "LoadingScene.h"
#include "core/utils/LanguageMgr.h"
#include "../InGameMgr.h"
#include "Game/Utility/JNIUtils.h"
#include "../logic/gamePlay/TienlenGroupCard.h"
#include "../logic/gamePlay/TienlenPlayerCard.h"
#include "core/utils/TienlenGameSound.h"
#include "LobbyScene.h"
#include "common/ChooseGameScene.h"
#include "ResultGroup.h"
#include <gameBinh/ui/MauBinhGroup.h>
#include <gameBinh/logic/gamePlay/MaubinhPlayerCard.h>
#include <gameTala/ui/TalaResultGroup.h>


using namespace efk;
#define NUM_DOT  42

#define WIDTH_ROW 383
#define HEIGHT_ROW 60
LoadingScene::LoadingScene()
{

}

LoadingScene::~LoadingScene()
{

}

bool LoadingScene::init()
{
	BaseLayer::init();
	//setKeyboardEnabled(true);
	initGUI();
	
	return true;
}

void LoadingScene::initGUI()
{
	Size size = Director::getInstance()->getVisibleSize();
    gameMgr->typeCard = 0;

	// BG LOADING
	auto bg = Sprite::create("GuiGame/bg.jpg");
	bg->setScaleX(size.width / bg->getContentSize().width);
	bg->setScaleY(size.height / bg->getContentSize().height);
	//bg->setScale(_scale);
	addChild(bg);
	bg->setPosition(size.width / 2, size.height / 2);
   // bg->setVisible(false);
	//bg->setOpacity(10);

	auto icon = Sprite::create("IconInGame.png");
	if (gameMgr->isIOS())
		icon->setTexture("IconInGameIOS.png");
	//bg->setScaleX(size.width / bg->getContentSize().width);
	//bg->setScaleY(size.height / bg->getContentSize().height);
	//bg->setScale(_scale);
	addChild(icon);
	icon->setPosition(size.width * 0.5, size.height / 2);
	icon->setOpacity(10);
	icon->setVisible(false);

	//bg->setScale(0.01);
	float time = 1.0;
	if (gameMgr->winCount < 3) {
		time = 2.0;
	}
    
	bg->runAction(
		Sequence::create(
			FadeIn::create(0.2),
			DelayTime::create(time),
			FadeTo::create(0.6, 100),
			CallFunc::create(AX_CALLBACK_0(LoadingScene::callbackLoading, this)),
			NULL
		)
	);
	icon->runAction(
		Sequence::create(
			EaseExponentialOut::create(FadeIn::create(0.5)),
			DelayTime::create(time - 0.7),
			EaseExponentialIn::create(FadeOut::create(0.5)),
			NULL
		)
	);

	// var effect = efk.Effect.create("test.efk");
			// if (effect)
			// {
			//     var emitter = efk.EffectEmitter.create(this._manager, "");
			//     emitter.setEffect(effect);
			//     emitter.setPlayOnEnter(true);
			//     // emitter.setRotation3D(.math.vec3(0, 90, 0));
			//     emitter.setPosition(.p(320, 200));
			//
			//     emitter.setScale(13);
			//     this.addChild(emitter, 0);
	/*manager = EffectManager::create(size);
	Effect* effect = Effect::create("flame.efk", 50);
	emitter = EffectEmitter::create(manager);
	emitter->setEffect(effect);
	emitter->setPlayOnEnter(true);
	emitter->setPosition(size.width * 0.5, size.height * 0.2);
	addChild(emitter);
	emitter->setRemoveOnStop(false);
	scheduleUpdate();*/

   /* TalaResultGroup* group = new TalaResultGroup();
    addChild(group);
    group->setPosition(300, 300);
    group->showMauBinh(5);*/

	string resource = "Board/BlueTheme/btnBack.png";
	Button* btnBack = Button::create(resource, resource, resource);
	btnBack->setPosition(Vec2(btnBack->getContentSize().width * 0.7, size.height - btnBack->getContentSize().height * 0.1));
	addChild(btnBack);

	btnBack->addClickEventListener([this](Object*) {
		//emitter->play
	});
	btnBack->setVisible(false);
}

void LoadingScene::onEnterFinish()
{
	
}

const std::string LoadingScene::className = "LoadingScene";

void LoadingScene::callbackLoading()
{
	//inGameMgr->openBoardScene(true);
	/*if (gameMgr->isIOS() == false) {
		if (gameMgr->fakeApp == 1) {
			if (gameMgr->countryName.compare("VN") == 0 || gameMgr->countryName.compare("KR") == 0
				|| gameMgr->countryName.compare("vn") == 0 || gameMgr->countryName.compare("kr") == 0) {
				gameMgr->fakeApp = 0;
			}
		}
	}
	if (gameMgr->fakeApp == 1)
		sceneMgr->openScene(LobbyScene::className);
	else*/
		sceneMgr->openScene(ChooseGameScene::className);
}

void LoadingScene::update(float delta)
{
	//manager->update(delta);
}
