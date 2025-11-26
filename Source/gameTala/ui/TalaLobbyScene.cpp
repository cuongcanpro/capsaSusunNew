#include "TalaLobbyScene.h"
#include "core/utils/LanguageMgr.h"
#include "../TalaInGameMgr.h"
#include "Game/Utility/JNIUtils.h"
#include "../logic/TalaGameLogic.h"
#include "common/ChooseGameScene.h"

#define NUM_DOT  42

#define WIDTH_ROW 383
#define HEIGHT_ROW 60

const int TalaLobbyScene::BTN_SOLO = 0;
const int TalaLobbyScene::BTN_MULTI = 1;
const int TalaLobbyScene::BTN_TOP_WIN = 2;
const int TalaLobbyScene::BTN_TOP_GOLD = 3;
const int TalaLobbyScene::BTN_TOP = 4;
const int TalaLobbyScene::BTN_EDIT = 5;
const int TalaLobbyScene::BTN_BACK = 6;

const std::string TalaLobbyScene::className = "TalaLobbyScene";
TalaLobbyScene::TalaLobbyScene()
{

}

TalaLobbyScene::~TalaLobbyScene()
{

}

bool TalaLobbyScene::init()
{
	BaseLayer::init(TalaLobbyScene::className);
	//setKeyboardEnabled(true);
	initWithBinaryFile("TalaLobbyScene.csb");
	return true;
}

void TalaLobbyScene::initGUI()
{
    Size size     = Director::getInstance()->getVisibleSize();
    ImageView* bg = (ImageView*)getControl("bg");
    bg->loadTexture("GuiGame/bg.jpg");
    // BG LOADING
    pRight           = getControl("pRight");
    pLeft            = getControl("pLeft");
    btnMulti = customButton("btnMulti", TalaLobbyScene::BTN_MULTI, pRight);
    bgInfo     = getControl("bgInfo", pLeft);
    lbGold           = (Text*)getControl("lbGold", bgInfo);
    lbLevel          = (Text*)getControl("lbLevel", bgInfo);
    lbWin            = (Text*)getControl("lbWin", bgInfo);
    lbRank           = (Text*)getControl("lbRank", bgInfo);
    lbName           = (Text*)getControl("lbName", bgInfo);

    ImageView* avatar = (ImageView*)getControl("avatar", bgInfo);
    avatar->loadTexture("avatarIOS/avatar_0.png");
    borderAvatar    = (ImageView*)getControl("borderAvatar", bgInfo);
    btnBack = customButton("btnBack", TalaLobbyScene::BTN_BACK, _layout);
    btnTop = customButton("btnTop", TalaLobbyScene::BTN_TOP, _layout);
    btnTop->setVisible(false);
}

void TalaLobbyScene::onEnterFinish()
{
	// cap nhat lai du lieu top
	gameMgr->pushMyData();
	lbGold->setString("Gold: " + StringUtility::formatNumberSymbol(gameMgr->goldTala));
	lbWin->setString("Win: " + StringUtility::formatNumberSymbol(gameMgr->winCountTala));
	lbLevel->setString("Level: " + to_string(gameMgr->getLevel(gameMgr->winCountTala)));
	borderAvatar->loadTexture("avatar/level" + std::to_string(gameMgr->idAvatarTala) + ".png");

    moveHorizontal(btnMulti, getDefaultPos(btnMulti).x, 200, 0);
    moveHorizontal(bgInfo, getDefaultPos(bgInfo).x, -200, 0);

    moveHorizontal(btnTop, getDefaultPos(btnTop).x, -200, 0.0);
    moveHorizontal(btnBack, getDefaultPos(btnBack).x, -200, 0.1);
}

void TalaLobbyScene::backKeyPress()
{
	sceneMgr->openScene(ChooseGameScene::className);
}

void TalaLobbyScene::onButtonRelease(ax::ui::Button* button, int id)
{
	//GameSound::playClick();
	switch (id)
	{
	case BTN_MULTI:
		talaInGameMgr->openBoardScene(false);
	//	JNIUtils::sendEvent("mode_4", "1");
		break;
	case BTN_SOLO:
		talaInGameMgr->openBoardScene(true);
		//JNIUtils::sendEvent("mode_solo", "1");
		break;
	case BTN_BACK:
        sceneMgr->openScene(ChooseGameScene::className);
        break;
	case BTN_TOP:
        JNIUtils::submitScore(2, gameMgr->winCountTala);
        break;
	default:
		break;
	}
}
