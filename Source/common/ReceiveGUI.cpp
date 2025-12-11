#include "ReceiveGUI.h"
#include "core/gui/SceneMgr.h"
#include "UserInfoGUI.h"
#include "gameTienlen/logic/PlayerInfo.h"
#include "gameTienlen/logic/GameLogic.h"
#include "gameTala/logic/TalaPlayerInfo.h"
#include "gameTala/logic/TalaGameLogic.h"
#include "gameBinh/logic/BinhPlayerInfo.h"
#include "gameBinh/logic/BinhGameLogic.h"


using namespace ax::ui;

ReceiveGUI::ReceiveGUI()
{
	
}

ReceiveGUI::~ReceiveGUI()
{

}

bool ReceiveGUI::init()
{
	BaseLayer::init(ReceiveGUI::className);
	initWithBinaryFile("ReceiveGUI.csb");
	return true;
}

void ReceiveGUI::initGUI()
{
	Node* bg = getControl("bg");
	_bg = bg;

	lbCongrat = (Text*)getControl("lbCongrat", bg);

	btnClose = customButton("btnClose", ReceiveGUI::BTN_CLOSE, bg);

	effectGift = spine::SkeletonAnimation::createWithJsonFile("spine/ruong.json", "spine/ruong.atlas", 0.6f);
    effectGift->setPosition(Vec2(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.35));
    bg->addChild(effectGift);
}

void ReceiveGUI::onEnterFinish()
{
	setShowHideAnimate(_bg, true);
	setFog(true);

	effectGift->setAnimation(0, "idle", true);
}


void ReceiveGUI::showMessage(string message)
{
    lbCongrat->setString(message);
}

void ReceiveGUI::onButtonRelease(ax::ui::Button* button, int id)
{
	_btnId = id;
    effectGift->setAnimation(0, "open", true);
    runAction(Sequence::create(DelayTime::create(0.5f),
                            CallFunc::create(AX_CALLBACK_0(ReceiveGUI::onCloseShowEffect, this)),
                            NULL));
}

void ReceiveGUI::onCloseDone()
{
	BaseLayer::onCloseDone();
	//BaseLayer* layer = sceneMgr->openGUI(UserInfoGUI::className, UserInfoGUI::ZODER, UserInfoGUI::TAG);
	
}

void ReceiveGUI::onCloseShowEffect() {
    gameMgr->showReceiveGold();
    runAction(Sequence::create(DelayTime::create(1.0f),
                    CallFunc::create(AX_CALLBACK_0(ReceiveGUI::onClose, this)), NULL));
}

std::string ReceiveGUI::className = "ReceiveGUI";

const int ReceiveGUI::BTN_CLOSE = 0;


const int ReceiveGUI::ZODER = 10022;

const int ReceiveGUI::TAG = 10022;

const int ReceiveGUI::SUPPORT = 800;

