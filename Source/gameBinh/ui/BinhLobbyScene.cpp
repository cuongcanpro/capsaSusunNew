#include "BinhLobbyScene.h"
#include "core/utils/LanguageMgr.h"
#include "../BinhInGameMgr.h"
#include "Game/Utility/JNIUtils.h"
#include "core/utils/TienlenGameSound.h"
#include "common/ChooseGameScene.h"

#define NUM_DOT  42

#define WIDTH_ROW 383
#define HEIGHT_ROW 60

const int BinhLobbyScene::BTN_SOLO = 0;
const int BinhLobbyScene::BTN_MULTI = 1;
const int BinhLobbyScene::BTN_TOP_WIN = 2;
const int BinhLobbyScene::BTN_TOP_GOLD = 3;
const int BinhLobbyScene::BTN_TOP = 4;
const int BinhLobbyScene::BTN_BACK = 5;
const std::string BinhLobbyScene::className = "BinhLobbyScene";
BinhLobbyScene::BinhLobbyScene()
{

}

BinhLobbyScene::~BinhLobbyScene()
{

}

bool BinhLobbyScene::init()
{
	BaseLayer::init(BinhLobbyScene::className);
	//setKeyboardEnabled(true);
	initWithBinaryFile("BinhLobbyScene.csb");
	return true;
}

void BinhLobbyScene::initGUI()
{
    Size size     = Director::getInstance()->getVisibleSize();
    ImageView* bg = (ImageView*)getControl("bg");
    bg->loadTexture("GuiGame/bg.jpg");
    // BG LOADING
    pRight           = getControl("pRight");
    pLeft            = getControl("pLeft");
    btnMulti = customButton("btnMulti", BinhLobbyScene::BTN_MULTI, pRight);
    bgInfo     = getControl("bgInfo", pLeft);
    lbGold           = (Text*)getControl("lbGold", bgInfo);
    lbLevel          = (Text*)getControl("lbLevel", bgInfo);
    lbWin            = (Text*)getControl("lbWin", bgInfo);
    lbRank           = (Text*)getControl("lbRank", bgInfo);
    lbName           = (Text*)getControl("lbName", bgInfo);

    ImageView* avatar = (ImageView*)getControl("avatar", bgInfo);
    avatar->loadTexture("avatarIOS/avatar_0.png");
    borderAvatar = (ImageView*)getControl("borderAvatar", bgInfo);
    btnBack = customButton("btnBack", BinhLobbyScene::BTN_BACK, _layout);
    btnTop = customButton("btnTop", BinhLobbyScene::BTN_TOP, _layout);
    btnTop->setVisible(false);
}

void BinhLobbyScene::onEnterFinish()
{
	// cap nhat lai du lieu top
	gameMgr->pushMyData();
	lbGold->setString("Gold: " + StringUtility::formatNumberSymbol(gameMgr->goldBinh));
	lbWin->setString("Win: " + StringUtility::formatNumberSymbol(gameMgr->winCountBinh));
	lbLevel->setString("Level: " + to_string(gameMgr->getLevel(gameMgr->winCountBinh)));
	borderAvatar->loadTexture("avatar/level" + std::to_string(gameMgr->idAvatarBinh) + ".png");

    moveHorizontal(btnMulti, getDefaultPos(btnMulti).x, 200, 0);
    moveHorizontal(bgInfo, getDefaultPos(bgInfo).x, -200, 0);

    moveHorizontal(btnTop, getDefaultPos(btnTop).x, -200, 0.0);
    moveHorizontal(btnBack, getDefaultPos(btnBack).x, -200, 0.1);
    string res = "Board/table/" + BinhGameLogic::getInstance()->getRes() + "btnStart1.png";
    btnMulti->loadTextures(res, res, res);
}

void BinhLobbyScene::backKeyPress()
{
	exit(0);
}


void BinhLobbyScene::onButtonRelease(ax::ui::Button* button, int id)
{
	TienlenGameSound::playClick();
	switch (id)
	{
	case BTN_MULTI:
		binhInGameMgr->openBoardScene();
		break;
    case BTN_BACK:
        sceneMgr->openScene(ChooseGameScene::className);
        break;
    case BTN_TOP:
        JNIUtils::submitScore(1, gameMgr->winCountBinh);
        break;
	default:
		break;
	}
}
