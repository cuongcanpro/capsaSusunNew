#include "GUILoadingGame.h"
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
#define BTN_UNDO_ID 3


GUILoadingGame::GUILoadingGame(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	setKeypadEnabled(true);
}
std::string GUILoadingGame::className = "GUILoadingGame";

GUILoadingGame::~GUILoadingGame(void)
{
}

void GUILoadingGame::initGUI(){
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    runAction(Sequence::create(DelayTime::create(0.1f),
                               CallFunc::create(AX_CALLBACK_0(GUILoadingGame::callBackSplash, this)), NULL));
}


void GUILoadingGame::callbackCompleteEndGame()
{
    game->changeToPortrait();
    switch (currentGame)
    {
    case GAME_POP:
    {
        game->loadPop();
        GUIManager::getInstance().removeAllGui();
        GUIPop* gui = (GUIPop*)GUIManager::getInstance().showGuiWithName(GUIPop::className);
        gui->showGUI(BoardType::POP_TYPE_NORMAL);
    }
    break;
    case GAME_LINE:
    {
        game->loadPlayNormal();
        GUIManager::getInstance().removeAllGui();
        GUILine* gui = (GUILine*)GUIManager::getInstance().showGuiWithName(GUILine::className);
        gui->showGui();
    }
    break;
    case GAME_DROP:
    {
        GUIManager::getInstance().removeAllGui();
        GUIMerge* gui = (GUIMerge*)GUIManager::getInstance().showGuiWithName(GUIMerge::className);
       // gui->showGUI();
    }
    break;
    case GAME_BLOCK:
    {
        game->loadBlock();
        GUIManager::getInstance().removeAllGui();
        GUIBlock* gui = (GUIBlock*)GUIManager::getInstance().showGuiWithName(GUIBlock::className);
        gui->showGUI();
    }
    break;
    case GAME_TWENTY:
    {
        game->loadTwenty();
        GUIManager::getInstance().removeAllGui();
        GUITwenty* gui = (GUITwenty*)GUIManager::getInstance().showGuiWithName(GUITwenty::className);
        gui->showGui();
    }
    break;
    case GAME_BOMB:
    {
        game->loadBomb();
        GUIManager::getInstance().removeAllGui();
        GUIBomb* gui = (GUIBomb*)GUIManager::getInstance().showGuiWithName(GUIBomb::className);
        break;
    }
    case GAME_BUBBLE:
    {
        game->loadBubble();
        GUIManager::getInstance().removeAllGui();
        GUIBubble* gui = (GUIBubble*)GUIManager::getInstance().showGuiWithName(GUIBubble::className);
        gui->showGui();
    }
        break;
    case GAME_CHESS:

        break;
    case GAME_EGG:
    {
        GUIManager::getInstance().removeAllGui();
        GUIGame* gui = (GUIGame*)GUIManager::getInstance().showGuiWithName(GUIGame::className);
        gui->showGui(ENDLESS);
    }
        break;
    case GAME_PIKA:
    {
        JNIUtils::showAdsBanner(0);
        game->loadPika();
        GUIManager::getInstance().removeAllGui();
        GUIPika* gui = (GUIPika*)GUIManager::getInstance().showGuiWithName(GUIPika::className);
        gui->showGui(GameMode::NORMAL_MODE);
        break;
    }
    case GAME_TIENLEN:
    {
        //	JNIUtils::loadAdsFullCard();
        // GUIManager::getInstance().removeAllGui();
       // sceneMgr->openScene(ChooseGameScene::className, "", false, true);
        //	game->enterCard = true;
        //	UserDefault::getInstance()->setBoolForKey("enterCard", true);
        // UserDefault::getInstance()->flush();
        break;
    }
    case GAME_BRICK:
    {
        game->loadBrick();
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIBrick::className);
    }
    break;
    case GAME_CARO:
    {
        // GUIManager::getInstance().removeAllGui();
        // GUIManager::getInstance().guiCaro.showGUI();
    }
    break;
    case GAME_2048:
    {
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUI2048::className);
    }
    break;
    case GAME_SUDOKU:
    {
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUISudoku::className);
    }
    break;
    case GAME_SWING:
    {
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUISwing::className);
    }
    break;
    case GAME_AA:
    {
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIaa::className);
    }
    break;
    default:
        break;
    }
}

void GUILoadingGame::showGame(int game) {
    BaseGUI::showGUI();
    setVisible(true);
    GUIManager::getInstance().addToListGui(this);
    currentGame = game;
    this->runAction(Sequence::create(
        FadeOut::create(0.5f), CallFunc::create(AX_CALLBACK_0(GUILoadingGame::callbackCompleteEndGame, this)), NULL));
}

void GUILoadingGame::callBackSplash()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();	
}
