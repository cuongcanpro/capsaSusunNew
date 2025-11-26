#include "LobbyScene.h"
#include "core/utils/LanguageMgr.h"
#include "../InGameMgr.h"
#include "Game/Utility/JNIUtils.h"
#include "../logic/gamePlay/TienlenGroupCard.h"
#include "../logic/gamePlay/TienlenPlayerCard.h"
#include "core/utils/TienlenGameSound.h"
#include "GUILevel.h"
#include "../logic/GameLogic.h"
#include "GUIHelp.h"
#include "common/ChooseGameScene.h"

#define NUM_DOT  42

#define WIDTH_ROW 383
#define HEIGHT_ROW 60

const int LobbyScene::BTN_SOLO = 0;
const int LobbyScene::BTN_MULTI = 1;
const int LobbyScene::BTN_TOP_WIN = 2;
const int LobbyScene::BTN_TOP_GOLD = 3;
const int LobbyScene::BTN_TOP = 4;
const int LobbyScene::BTN_EDIT = 5;
const int LobbyScene::BTN_LEVEL = 6;
const int LobbyScene::BTN_BACK    = 7;

const std::string LobbyScene::className = "LobbyScene";
LobbyScene::LobbyScene()
{

}

LobbyScene::~LobbyScene()
{

}

bool LobbyScene::init()
{
	BaseLayer::init(LobbyScene::className);
	//setKeyboardEnabled(true);
	initWithBinaryFile("LobbyScene.csb");
	return true;
}

void LobbyScene::initGUI()
{
	Size size = Director::getInstance()->getVisibleSize();
	ImageView* bg = (ImageView*)getControl("bg");
	bg->loadTexture("GuiGame/bg.jpg");
	// BG LOADING
	pRight = getControl("pRight");
    pLeft = getControl("pLeft");
	btnSolo = customButton("btnSolo", LobbyScene::BTN_SOLO, pRight);
	btnMulti = customButton("btnMulti", LobbyScene::BTN_MULTI, pRight);
	btnLevel = customButton("btnLevel", LobbyScene::BTN_LEVEL, pRight);
	bgInfo = getControl("bgInfo", pLeft);
	lbGold = (Text*) getControl("lbGold", bgInfo);
	lbLevel = (Text*) getControl("lbLevel", bgInfo);
	lbWin = (Text*) getControl("lbWin", bgInfo);
	lbRank = (Text*) getControl("lbRank", bgInfo);
	lbName = (Text*)getControl("lbName", bgInfo);
	
	ImageView* avatar = (ImageView*)getControl("avatar", bgInfo);
	avatar->loadTexture("avatarIOS/avatar_0.png");
	borderAvatar = (ImageView*) getControl("borderAvatar", bgInfo);
	btnBack = customButton("btnBack", LobbyScene::BTN_BACK, _layout);
    btnTop = customButton("btnTop", LobbyScene::BTN_TOP, _layout);
    btnTop->setVisible(false);
}

void LobbyScene::onEnterFinish()
{
	// cap nhat lai du lieu top
	gameMgr->pushMyData();
	lbGold->setString("Gold: " + StringUtility::formatNumberSymbol(gameMgr->gold));
	lbWin->setString("Win: " + StringUtility::formatNumberSymbol(gameMgr->winCount));
	lbLevel->setString("Level: " + to_string(gameMgr->getLevel(gameMgr->winCount)));
	borderAvatar->loadTexture("avatar/level" + std::to_string(gameMgr->idAvatar) + ".png");

    moveHorizontal(bgInfo, getDefaultPos(bgInfo).x, -200, 0);
    moveHorizontal(btnSolo, getDefaultPos(btnSolo).x, 200, 0);
    moveHorizontal(btnMulti, getDefaultPos(btnMulti).x, 200, 0.1);
    moveHorizontal(btnLevel, getDefaultPos(btnLevel).x, 200, 0.2);

    moveHorizontal(btnTop, getDefaultPos(btnTop).x, -200, 0.0);
    moveHorizontal(btnBack, getDefaultPos(btnBack).x, -200, 0.1);
}

void LobbyScene::backKeyPress()
{
	if (gameMgr->fakeApp == 1)
		gameMgr->endGame();
	else
		sceneMgr->openScene(ChooseGameScene::className);
}

void LobbyScene::onButtonRelease(ax::ui::Button* button, int id)
{
	TienlenGameSound::playClick();
	switch (id)
	{
	case BTN_MULTI:
		GameLogic::getInstance()->endPosture();
		inGameMgr->openBoardScene(false);
		JNIUtils::sendEvent("mode_4", "1");
		break;
	case BTN_SOLO:
		GameLogic::getInstance()->endPosture();
		inGameMgr->openBoardScene(true);
		JNIUtils::sendEvent("mode_solo", "1");
		break;
	case BTN_LEVEL:
		sceneMgr->openScene(GUILevel::className);
		JNIUtils::sendEvent("mode_level", "1");
		break;
    case BTN_BACK:
        sceneMgr->openScene(ChooseGameScene::className);
        break;
    case BTN_TOP:
        JNIUtils::submitScore(0, gameMgr->winCount);
        break;
	default:
		break;
	}
}
