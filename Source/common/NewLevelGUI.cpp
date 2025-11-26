#include "NewLevelGUI.h"
#include "core/gui/SceneMgr.h"
#include "UserInfoGUI.h"
#include "gameTienlen/logic/PlayerInfo.h"
#include "gameTienlen/logic/GameLogic.h"
#include "gameTala/logic/TalaPlayerInfo.h"
#include "gameTala/logic/TalaGameLogic.h"
#include "gameBinh/logic/BinhPlayerInfo.h"
#include "gameBinh/logic/BinhGameLogic.h"


using namespace ax::ui;

NewLevelGUI::NewLevelGUI()
{
	
}

NewLevelGUI::~NewLevelGUI()
{

}

bool NewLevelGUI::init()
{
	BaseLayer::init(NewLevelGUI::className);
	initWithBinaryFile("NewLevelGUI.csb");
	return true;
}

void NewLevelGUI::initGUI()
{
	Node* bg = getControl("bg");
	_bg = bg;

	lbCongrat = (Text*)getControl("lbCongrat", bg);
	borderAvatar = (ImageView*)getControl("borderAvatar", bg);

	btnClose = customButton("btnClose", NewLevelGUI::BTN_CLOSE, bg);

	//effectWin = DBCCFactory::getInstance()->buildArmatureNode("Chest");
	//if (effectWin) {
	//	bg->addChild(effectWin, -1);
	//	effectWin->setVisible(false);
	//	effectWin->setPosition(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.95);
	//	//effectMauBinh->setScale(0.65);
	//}
}

void NewLevelGUI::onEnterFinish()
{
	setShowHideAnimate(_bg, true);
	setFog(true);

	/*effectWin->setVisible(true);
	effectWin->getAnimation()->gotoAndPlay("1", -1, -1, 1);
	effectWin->runAction(
		Sequence::create(
			DelayTime::create(5.0),
			Hide::create(),
			NULL
		)
	);*/
}


void NewLevelGUI::showInfo(int idGame)
{
	currentGame = idGame;
	if (currentGame == TypeGame::TIEN_LEN) {
		PlayerInfo* info = GameLogic::getInstance()->arrayPlayer[0];
		int idAvatar = info->getLevel();
		borderAvatar->loadTexture("avatar/level" + to_string(idAvatar) + ".png");
		lbCongrat->setString("Congratulations you just leveled " + to_string(info->getLevel() + 1) + " and unlocked new Avatar");
	}
	else if (currentGame == TypeGame::BINH) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->arrayPlayer[0];
		int idAvatar = info->getLevel();
		borderAvatar->loadTexture("avatar/level" + to_string(idAvatar) + ".png");
		lbCongrat->setString("Congratulations you just leveled " + to_string(info->getLevel() + 1) + " and unlocked new Avatar");
	}
	else {
		TalaPlayerInfo* info = TalaGameLogic::getInstance()->players[0];
		int idAvatar = info->getLevel();
		borderAvatar->loadTexture("avatar/level" + to_string(idAvatar) + ".png");
		lbCongrat->setString("Congratulations you just leveled " + to_string(info->getLevel() + 1) + " and unlocked new Avatar");
	}

}

void NewLevelGUI::onButtonRelease(ax::ui::Button* button, int id)
{
	_btnId = id;
	onClose();
}

void NewLevelGUI::onCloseDone()
{
	BaseLayer::onCloseDone();
	BaseLayer* layer = sceneMgr->openGUI(UserInfoGUI::className, UserInfoGUI::ZODER, UserInfoGUI::TAG);
	UserInfoGUI *gui = dynamic_cast<UserInfoGUI*> (layer);
	gui->showInfo(currentGame);
}

std::string NewLevelGUI::className = "NewLevelGUI";

const int NewLevelGUI::BTN_CLOSE = 0;


const int NewLevelGUI::ZODER = 10022;

const int NewLevelGUI::TAG = 10022;

const int NewLevelGUI::SUPPORT = 800;

