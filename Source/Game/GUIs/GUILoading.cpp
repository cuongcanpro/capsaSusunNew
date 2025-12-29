#include "GUILoading.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "Game/Data/GlobalData.h"

#include <DragonBones/CCFactory.h>
#include <spine/spine-cocos2dx.h>
#include <Game/Utility/JNIUtils.h>
#include <Game/Utility/GameUtility.h>
#include <Game/Utility/GameSound.h>
#include "spine/spine.h"
#include <cocostudio/ArmatureDataManager.h>
#include <cocostudio/Armature.h>
#include <DragonBones/DragonBonesHeaders.h>
#include "core/gui/Sparkle.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3

std::string GUILoading::className = "GUILoading";
GUILoading::GUILoading(void) : BaseGUI()
{
	BaseGUI();
    retain();
	//Node::onEnter();
	//setKeypadEnabled(true);
}

GUILoading::~GUILoading(void)
{
}

void GUILoading::initGUI(){

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(Sequence::create(FadeIn::create(0.8f), DelayTime::create(.8f), FadeOut::create(0.8f), CallFunc::create(this, callfunc_selector(GUILoading::callBackSplash)), NULL));
    runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create(AX_CALLBACK_0(GUILoading::callBackSplash, this)), NULL));
	
}

void GUILoading::callbackCompleteEndGame() {
   
    background->getImg()->runAction(
        Sequence::create(DelayTime::create(0.5), FadeOut::create(0.5f),
                         CallFunc::create(AX_CALLBACK_0(GUILoading::callbackCompleteEndGame1, this)), NULL));
}

void GUILoading::callbackCompleteEndGame1()
{
    if ((updateGame != 0  && updateGame < 3) || game->message != "")
        return;
   
    
    GUIManager::getInstance().removeAllGui();
    //GUIManager::getInstance().guiPop.showGUI();
    //game->typeTheme = -1;
   
    GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
    //GUIManager::getInstance().showGuiWithName(GUIMerge::className);
}

void GUILoading::callbackTest() {
    AXLOG("CALLBACK +++++++++ ");
}

void GUILoading::update(float delta) {
    //manager->update();
}

void GUILoading::callBackSplash()
{
    Size size             = Director::getInstance()->getRenderView()->getVisibleSize();
    background = addImage("bg2.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);

    Sprite* iconBall = Sprite::create("GuiGame/logo.png");
    addChild(iconBall);
    iconBall->setAnchorPoint(Vec2(0.5, 0));
    iconBall->setPosition(size.width * 0.5, size.height * 1.1);
    iconBall->runAction(
        Sequence::create(
            EaseBounceOut::create(MoveTo::create(0.8, Vec2(size.width * 0.5, size.height * 0.5 - iconBall->getContentSize().height * 0.5))),
            DelayTime::create(0.8),
            FadeOut::create(0.5),
            NULL
        )
    );
    iconBall->runAction(
        Sequence::create(
            DelayTime::create(0.4),
            ScaleTo::create(0.2, 1.2, 0.65),
            EaseBounceOut::create(ScaleTo::create(0.4, 1.0, 1.0)),
            NULL
        )
    );
    //iconBall->setVisible(false);

	background->getImg()->runAction(
        Sequence::create(
            DelayTime::create(2.5),
           // FadeOut::create(0.5f), 
            CallFunc::create(AX_CALLBACK_0(GUILoading::callbackCompleteEndGame1, this)),
            NULL
        )
    );
    GameSound::playLevelUp();

    auto factory = dragonBones::CCFactory::getFactory();
    factory->loadDragonBonesData("dragonbone/kyby_eff_gold_bomb_ske.json");
    factory->loadTextureAtlasData("dragonbone/kyby_eff_gold_bomb_tex.json");

    //auto armatureDisplay = factory->buildArmatureDisplay("kyby_eff_gold_bomb");
    //armatureDisplay->setPosition(ax::Vec2(300, 400));
    ////this->addChild(armatureDisplay);
    //armatureDisplay->getEventDispatcher()->setEnabled(true);
    //armatureDisplay->addDBEventListener(dragonBones::EventObject::COMPLETE,
    //                                    AX_CALLBACK_0(GUILoading::callbackTest, this));
   // armatureDisplay->getAnimation()->play("lightning");

  ////  skeletonNode->setAnimation(0, "walk", true);

  //  // alternative setting two color tint for groups of 10 skeletons
  //  // should end up with #skeletons / 10 batches
  //  // if (j++ < 10)
  //  //			skeletonNode->setTwoColorTint(true);
  //  //		if (j == 20) j = 0;
  //  // skeletonNode->setTwoColorTint(true);


   // spine::SkeletonAnimation* skeletonNode =
   //     spine::SkeletonAnimation::createWithJsonFile("spine/firework.json", "spine/firework.atlas", 1.0f);
   // //skeletonNode->setAnimation(0, "idle", true);
   //// skeletonNode->setSkin("idle");
   // skeletonNode->setPosition(Vec2(300, 300));
   // addChild(skeletonNode);

   // // huong tu duoi len tren
   // skeletonNode->setRotation(50); // sang ben phai
   // skeletonNode->setRotation(-30); // huong ben tren
   // skeletonNode->setRotation(-80); // cheo tu phai sang trai
   // skeletonNode->setRotation(10); // cheo tu trai sang phai

   // // huong tu tren xuong duoi
   // skeletonNode->setRotation(150); // huong xuong duoi
   // skeletonNode->setRotation(0); // cheo tu trai sang phai
   // skeletonNode->setRotation(-170); // cheo tu phai sang trai

  //  skeletonNode->setRotation(90);
  /*  skeletonNode->setScale(0);
    skeletonNode->runAction(
        Sequence::create(
            Spawn::create(
                EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 30))),
                EaseExponentialOut::create(ScaleTo::create(0.5, 1.0)),
                NULL
            ),
            EaseExponentialIn::create(MoveTo::create(1.0, Vec2(500, 110))),
            NULL
        )
    );*/
  //  skeletonNode->setVisible(false);

   // Sparkle* test = new Sparkle(500, 200, "Board/Particles/flare.png");
   //// addChild(test);
   // test->setPosition(size.width * 0.2, size.height * 0.2);
   // test->emitTime = 0.2;
   // test->type = SPARKLE_SHOW;
   // test->startEffect();
    
    
}
