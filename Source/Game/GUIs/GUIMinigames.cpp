#include "GUIMinigames.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"
#include "core/gui/SceneMgr.h"
#include "common/ChooseGameScene.h"
#include "MainScene.h"
#include <app/GameMgr.h>
//#include <gameBinh/BinhInGameMgr.h>

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_UPDATE_ID 33
#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_NORMAL_ID 3
#define BTN_TIME_ID 4
#define BTN_OLD_VERSION 5
#define BTN_EXTRA_ID 6
#define BTN_SETTING 7
#define BTN_LEVEL 8
#define BTN_BLOCK_ID 9
#define BTN_ONLINE_ID 10
#define BTN_CHALLENGE_ID 11
#define BTN_GAME 19
#define BTN_TWENTY 20
#define BTN_EGG 21
#define BTN_BUBBLE 22
#define BTN_DROP 23
#define BTN_CAPSA_SUSUN 24
#define BTN_POP 25
#define BTN_BOMB 26
#define BTN_CHESS 27
#define BTN_LINE 28


std::string GUIMinigames::className = "GUIMinigames";
GUIMinigames::GUIMinigames(void) : BaseGUI()
{
	BaseGUI();
	setKeypadEnabled(true);
}

GUIMinigames::~GUIMinigames(void)
{

}

void GUIMinigames::initGUI(){
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
    callBackSplash();
}

void GUIMinigames::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
        //game->changeToLandscape();
        
		//GUIManager::getInstance().removeAllGui();
		//GUIManager::getInstance().showGui(GUIManager::getInstance().guiLoading);
		GUIManager::getInstance().isCallBackPress = true;
        game->endGame();
	}
}


void GUIMinigames::callBackSplash()
{
//	game->showChess = false;
	BaseGUI::initGUI();
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();

	GameImage* background = addImage("bgWhite.jpg");
    background->setColor(Color3B(15, 36, 60));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	btnBack = addButton(BTN_BACK_ID, "btnQuit.png", new BubbleBehavior(), NULL, false);
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);
    
    btnUpdate = addButton(BTN_UPDATE_ID, "btnUpdate.png", new BubbleBehavior(), NULL, false);
    btnUpdate->setPosition(btnUpdate->getWidth() * 0.5f, btnBack->getPositionY() - 30);
    btnUpdate->normalImage->setScale(0.8);
    btnUpdate->setVisible(updateGame > 2);

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png", new BubbleBehavior(), NULL, false);
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if (game->music)
	{
            btnSound->normalImage->setImage("btnSoundOn.png", false);
	}
	else
	{
            btnSound->normalImage->setImage("btnSoundOff.png", false);
	}

    int numGame = game->extendGame == 1 ? 11 : 10;
    
	//btnChess->setVisible(false);
    initInfoUser();

    btnChess = addButton(BTN_LINE, "iconCard.png", new BubbleBehavior(), NULL, false);
    btnChess->setPosition(bgInfo->getPositionX(), bgInfo->getPositionY() + btnChess->getHeight() * 0.6 + bgInfo->getContentSize().height * 0.5);
	
    float heightBg = btnBack->getPositionY() - btnBack->getHeight() * 0.7 - size.height * 0.15;
    float widthBg  = size.width * 0.95f - bgInfo->getPositionX() - bgInfo->getContentSize().width * 0.5 - size.width * 0.05;
	//game->showChess = false;
    //if (game->showChess)
        
    //else
    	//btnChess->setVisible(false);
    if (game->numPlayGame > 3) {
        numGame = 13;
    }
	else {
		numGame = 12;
	}

	bgGame = Scale9Sprite::create("IconGame/popup.png");
	addChild(bgGame);
	bgGame->setPosition(size.width * 0.95f - widthBg * 0.5, size.height * 0.15 + heightBg * 0.5);
	bgGame->setContentSize(Size(widthBg, heightBg));
	bgGame->setOpacity(50);

    float padX = 125;
    float padY = 130;
    int numPerRow = widthBg / padX;
    int numRow = ceil(numGame * 1.0 / numPerRow);
    float _pX     = (widthBg - numPerRow * padX) / (numPerRow + 1);
	scrollView = ax::extension::ScrollView::create();
    scrollView->setTouchEnabled(true);
    scrollView->setDirection(ax::extension::ScrollView::Direction::VERTICAL);
    scrollView->setSwallowTouches(false);
    scrollView->setContentSize(size);
	float heightList = padY * numRow;
    scrollView->setContentSize(Size(bgGame->getContentSize().width, heightList));
	scrollView->setViewSize(Size(bgGame->getContentSize().width, bgGame->getContentSize().height * 0.95));
	scrollView->setPosition(bgGame->getPositionX() - scrollView->getContentSize().width * 0.5, bgGame->getPositionY() - bgGame->getContentSize().height * 0.5 + 5);
   // scrollView->addChild(imageView);
	scrollView->setContentOffsetInDuration(Vec2(0, scrollView->getViewSize().height - heightList), 0);
	addChild(scrollView);
    scrollView->setDelegate(this);

	string arrayResource[15] = {"", "", "", "", "", "", "", ""};
	string arrayName[15] = {"", "", "", "", "", "", "", ""};
	arrayResource[GAME_LINE] = "IconGame/iconLine.png";
	arrayResource[GAME_POP] = "IconGame/iconPop.png";
	arrayResource[GAME_DROP] = "IconGame/iconDrop.png";
	arrayResource[GAME_TWENTY] = "IconGame/icon24.png";
	arrayResource[GAME_BOMB] = "IconGame/iconBomb.png";
	arrayResource[GAME_BUBBLE] = "IconGame/iconBubble.png";
    arrayResource[GAME_BLOCK] = "IconGame/iconBlock.png";
	//arrayResource[GAME_CHESS] = "IconGame/iconGame.png";
    arrayResource[GAME_EGG] = "IconGame/iconEgg.png";
	arrayResource[GAME_TIENLEN] = "IconGame/iconCard.png";
    arrayResource[GAME_PIKA] = "IconGame/iconPika.png";
    arrayResource[GAME_BRICK]    = "IconGame/iconBrick.png";
	arrayResource[GAME_2048] = "IconGame/icon2048.png";
    arrayResource[GAME_SUDOKU]        = "IconGame/iconSudoku.png";
    arrayResource[GAME_SWING]  = "IconGame/iconSwing.png";
    arrayResource[GAME_AA]        = "IconGame/iconAa.png";

    arrayNameGame[GAME_LINE]    = "GAME_LINE";
    arrayNameGame[GAME_POP]           = "GAME_POP";
    arrayNameGame[GAME_DROP]          = "GAME_DROP";
    arrayNameGame[GAME_TWENTY]        = "GAME_TWENTY";
    arrayNameGame[GAME_BOMB]          = "GAME_BOMB";
    arrayNameGame[GAME_BUBBLE]        = "GAME_BUBBLE";
    arrayNameGame[GAME_BLOCK]         = "GAME_BLOCK";
    arrayNameGame[GAME_EGG]           = "GAME_EGG";
    arrayNameGame[GAME_TIENLEN]       = "GAME_TIENLEN";
    arrayNameGame[GAME_PIKA]          = "GAME_PIKA";
    arrayNameGame[GAME_BRICK]         = "GAME_BRICK";
    arrayNameGame[GAME_2048]          = "GAME_2048";
    arrayNameGame[GAME_SUDOKU]        = "GAME_SUDOKU";
    arrayNameGame[GAME_AA]        = "GAME_AA";
    arrayNameGame[GAME_SWING]        = "GAME_SWING";
    
    int arrayGame1[15] = {0, 1, 2, 11, 12, 3, 4, 5, 13, 14, 6, 7, 8, 9, 10};
    int arrayGame2[13] = {12, 3, 11, 2, 1, 7, 0, 4, 5, 6, 8, 9, 10};
    // split string to array
    //game->arrayGame = "3,11,0,1,7,2,4,5,6,8,9,10";

    
    for (int i = 0; i < numGame; i++)
    {
        // check if i in vector arrayIdGame
        if (std::find(game->arrayIdGame.begin(), game->arrayIdGame.end(), arrayGame1[i]) == game->arrayIdGame.end())
        {
            // insert at begin of vector arrayIdGame
            game->arrayIdGame.insert(game->arrayIdGame.begin(), arrayGame1[i]);
        }
    }
    
    for (int i = 0; i < numGame; i++) {
       // s = arrayResource[i];
        int idGame         = game->arrayIdGame.at(i);
        Button* buttonGame = Button::create();
        buttonGame->setTouchEnabled(true);
        buttonGame->setTag(idGame);
        buttonGame->loadTextures(arrayResource[idGame], arrayResource[idGame], arrayResource[idGame]);
      //  button->setPosition(Vec2(50, 50));
        scrollView->addChild(buttonGame);
        //button->addTouchEventListener(AX_CALLBACK_2(BaseLayer::onTouchEventHandler, this));
        buttonGame->addTouchEventListener(AX_CALLBACK_2(GUIMinigames::onTouchGame, this));
        buttonGame->setSwallowTouches(false);
		int row = numRow - 1 - floor(i / (numPerRow * 1.0f));
		int column = i % numPerRow;
        float posX = _pX * (column + 1) + padX * (column + 0.5);
        buttonGame->setPosition(Vec2(posX, padY * (row + 0.5)));
        
       /* if (idGame == GAME_PIKA) {
            Sprite* iconHot = Sprite::create("IconGame/iconHot.png");
            buttonGame->addChild(iconHot);
            iconHot->setPosition(buttonGame->getContentSize().width * 0.9, buttonGame->getContentSize().height * 0.9);
        }*/
        arrayButtonGame.push_back(buttonGame);
    }
	countScroll = 0;
}

void GUIMinigames::initInfoUser() {
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    bgInfo = Scale9Sprite::create("IconGame/popup.png");
    addChild(bgInfo);
    bgInfo->setContentSize(Size(300, 200));
    bgInfo->setPosition(Vec2(size.width * 0.05 + bgInfo->getContentSize().width * 0.5, size.height * 0.15 + bgInfo->getContentSize().height * 0.5));

    avatar = ImageView::create("avatarIOS/avatar_0.png");
    bgInfo->addChild(avatar);
    avatar->setPosition(Vec2(avatar->getContentSize().width * 0.7, bgInfo->getContentSize().height / 2));

    borderAvatar = ImageView::create("avatarIOS/avatar_0.png");
    bgInfo->addChild(borderAvatar);
    borderAvatar->setPosition(avatar->getPosition());

    float posX = avatar->getPositionX() + avatar->getContentSize().width * 0.9;
    float padY = 40;
    lbName = Text::create("Player", "fonts/tahoma.ttf", 22);
    bgInfo->addChild(lbName);
    lbName->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
    lbName->setAnchorPoint(Vec2(0, 0.5f));
    lbName->setPosition(Vec2(posX, bgInfo->getContentSize().height - 30));

    lbGold = Text::create("Player", "fonts/tahoma.ttf", 22);
    bgInfo->addChild(lbGold);
    lbGold->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
    lbGold->setAnchorPoint(Vec2(0, 0.5f));
    lbGold->setPosition(Vec2(posX, lbName->getPositionY() - padY));

    lbWin = Text::create("Player", "fonts/tahoma.ttf", 22);
    bgInfo->addChild(lbWin);
    lbWin->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
    lbWin->setAnchorPoint(Vec2(0, 0.5f));
    lbWin->setPosition(Vec2(posX, lbGold->getPositionY() - padY));

    lbLevel = Text::create("Player", "fonts/tahoma.ttf", 22);
    bgInfo->addChild(lbLevel);
    lbLevel->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
    lbLevel->setAnchorPoint(Vec2(0, 0.5f));
    lbLevel->setPosition(Vec2(posX, lbWin->getPositionY() - padY));
}

void GUIMinigames::onButtonRelease(int buttonID, Touch* touch)
{
	//GUIManager::getInstance().guiLoadingAds.showAds(false);
	//return;

	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_BACK_ID:
		{
		onBackKey();
		}
		
		break;
        case BTN_UPDATE_ID:
            {
                JNIUtils::openApp(urlUpdate.c_str());
            }
            
            break;
	case BTN_SOUND_ID:
		{
       //     GUIManager::getInstance().guiLoadingAds.showAds(false);
		//playEgg();
			game->music = !game->music;
			if(game->music)
			{
                            btnSound->normalImage->setImage("btnSoundOn.png", false);
			}
			else
			{
                            btnSound->normalImage->setImage("btnSoundOff.png", false);
			}

			UserDefault::getInstance()->setBoolForKey("music", game->music);
			UserDefault::getInstance()->flush();
		}
		break;
		case BTN_CHESS:
		{
			
		}
		break;
		case BTN_LINE:
		{
            JNIUtils::sendEvent(("minigame_" + arrayNameGame[GAME_TIENLEN]).c_str(), "1");
            playCard();
		}
		break;
		case BTN_EGG:
		{
			playEgg();
		}
		break;
       
	default:
		break;
	}
}

void GUIMinigames::sendData(int mode) {
	
}


void GUIMinigames::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
    if (game->isInitAds == false)
        game->initAds();
    else
    {
        if (idAdsBanner != 3)
            game->showAdsFull();
        else if (game->timeNoAds > 300)
        {
            game->showAdsFull();
        }
    }
        
	countScroll = 0;
	BaseGUI::showGUI(parent, hasFog);
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	float sY = size.height - btnBack->getHeight() * 0.7;
	float sX = size.width * 0.5;

	moveVertical(btnBack->normalImage->_img, 0, 400, 0);
	moveVertical(btnSound->normalImage->_img, 0, 400, 0.1);
    moveHorizontal(btnChess->normalImage->_img, 0, -400, 0.0);
    moveHorizontal(bgInfo, bgInfo->getPositionX(), -400, 0.1);
    moveHorizontal(scrollView, scrollView->getPositionX(), 400, 0.0);
	for (int i = 0; i < arrayButtonGame.size(); i++) {
        /*int column = i % 2;
        arrayButtonGame.at(i)->setPositionX(
            scrollView->getContentSize().width * 0.5 +
            (arrayButtonGame.at(i)->getContentSize().width * 0.5 + 15) * (column == 1 ? 1 : -1)
        );*/
        moveVertical(arrayButtonGame.at(i), arrayButtonGame.at(i)->getPositionY(), 100,
                        0.0 + 0.05 * i);
	}

    lbGold->setString("Gold: " + StringUtility::formatNumberSymbol(gameMgr->goldBinh));
    lbWin->setString("Win: " + StringUtility::formatNumberSymbol(gameMgr->winCountBinh));
    lbLevel->setString("Level: " + to_string(gameMgr->getLevel(gameMgr->winCountBinh)));
    borderAvatar->loadTexture("avatar/level" + std::to_string(gameMgr->idAvatarBinh) + ".png");
}

void GUIMinigames::playLine() {
    game->changeToPortrait();
    game->loadPlayNormal();
    GUIManager::getInstance().removeAllGui();
    GUILine* gui = (GUILine*)GUIManager::getInstance().showGuiWithName(GUILine::className);
    gui->showGui();
}

void GUIMinigames::playBlock() {
	
}

void GUIMinigames::playTwenty()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
    GUITwenty* gui = (GUITwenty*)GUIManager::getInstance().showGuiWithName(GUITwenty::className);
    gui->showGui();
}

void GUIMinigames::playEgg()
{
    game->changeToPortrait();
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
    GUIGame* gui = (GUIGame*)GUIManager::getInstance().showGuiWithName(GUIGame::className);
    gui->showGui(ENDLESS);
}


void GUIMinigames::playBubble()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
    GUIBubble* gui = (GUIBubble*)GUIManager::getInstance().showGuiWithName(GUIBubble::className);
    gui->showGui();
}

void GUIMinigames::playBomb()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
    GUIBomb* gui = (GUIBomb*)GUIManager::getInstance().showGuiWithName(GUIBomb::className);
    gui->showGUI();
}

void GUIMinigames::playCard()
{
    gameMgr->openBinhScene();
}

void GUIMinigames::updateButton()
{
	
//	btnCapsa->setVisible(false);
}

void GUIMinigames::onTouchGame(ax::Object* pSender, ax::ui::Widget::TouchEventType type)
{
	AXLOGD("touch ne ");    
   
	
    
    Button* btn = dynamic_cast<Button*>(pSender);
    switch (type) {
    case ax::ui::Widget::TouchEventType::BEGAN:
			countScroll = 0;
            break;
    case ax::ui::Widget::TouchEventType::ENDED:
    {
			if (countScroll > 5) {
				countScroll = 0;
				return;
			}
			countScroll = 0;
			int buttonId = btn->getTag();
            JNIUtils::sendEvent(("minigame_" + arrayNameGame[buttonId]).c_str(), "1");
            
            // move buttonId to Top of vector game->arrayIdGame
            auto it = std::find(game->arrayIdGame.begin(), game->arrayIdGame.end(), buttonId);
            if (it != game->arrayIdGame.end())
            {
                game->arrayIdGame.erase(it);
            }
            game->arrayIdGame.insert(game->arrayIdGame.begin(), buttonId);
            // make string contains idGame in vector game->arrayIdGame, split by ','
            string s = "";
            for (int i = 0; i < game->arrayIdGame.size(); i++)
            {
                s += to_string(game->arrayIdGame.at(i));
                if (i < game->arrayIdGame.size() - 1)
                {
                    s += ",";
                }
            }
            // and save to UserDefault
            UserDefault::getInstance()->setStringForKey("arrayIdGame", s);
            UserDefault::getInstance()->flush();
			switch (buttonId) {
				case GAME_POP: {
                    game->changeToPortrait();
                    game->loadPop();
					GUIManager::getInstance().removeAllGui();
                    GUIPop* gui = (GUIPop*)GUIManager::getInstance().showGuiWithName(GUIPop::className);
                    gui->showGUI(BoardType::POP_TYPE_NORMAL);
				}
				break;
				case GAME_LINE: {
                                    
                    playLine();
				}
				break;
				case GAME_DROP: {
                    game->changeToPortrait();
                    //GUIManager::getInstance().removeAllGui();
                    //GUIManager::getInstance().guiLoadingGame->showGame(GAME_DROP);
					
                    GUIMerge* gui = (GUIMerge*) GUIManager::getInstance().showGuiWithName(GUIMerge::className);
                    //gui->showGUI();
				}
				break;
				case GAME_BLOCK: {
				    game->changeToPortrait();
					game->loadBlock();
					GUIManager::getInstance().removeAllGui();
                    GUIBlock* gui = (GUIBlock*) GUIManager::getInstance().showGuiWithName(GUIBlock::className);
                    gui->showGUI();
				}
				break;
                case GAME_TWENTY: {
                    game->changeToPortrait();
					game->loadTwenty();
                    GUIManager::getInstance().removeAllGui();
                    GUITwenty* gui = (GUITwenty*) GUIManager::getInstance().showGuiWithName(GUITwenty::className);
                    gui->showGui();
                }
                break;
				case GAME_BOMB:
                    game->changeToPortrait();
					game->loadBomb();
					playBomb();
				break;
				case GAME_BUBBLE:
                    game->changeToPortrait();
					game->loadBubble();
					playBubble();
				break;
                case GAME_CHESS:
                   
                break;
				case GAME_EGG:
				//	game->loadEgg();
					playEgg();
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
                                        //GUIManager::getInstance().removeAllGui();
                    sceneMgr->openScene(ChooseGameScene::className, "", false, true);
				//	game->enterCard = true;
				//	UserDefault::getInstance()->setBoolForKey("enterCard", true);
					//UserDefault::getInstance()->flush();
                    break;
				}
                case GAME_BRICK:
                {
                    game->changeToPortrait();
                    game->loadBrick();
                    GUIManager::getInstance().removeAllGui();
                    GUIManager::getInstance().showGuiWithName(GUIBrick::className);
                }
                break;
				case GAME_CARO:
				{
					//GUIManager::getInstance().removeAllGui();
					//GUIManager::getInstance().guiCaro.showGUI();
				}
				break;
                case GAME_2048:
                {
                    
                    game->changeToPortrait();
                    GUIManager::getInstance().removeAllGui();
                    GUIManager::getInstance().showGuiWithName(GUI2048::className);
                }
                break;
                case GAME_SUDOKU:
                {
                    game->changeToPortrait();
                    GUIManager::getInstance().removeAllGui();
                    GUIManager::getInstance().showGuiWithName(GUISudoku::className);
                }
                break;
                case GAME_SWING:
                {
                    game->changeToPortrait();
                    GUIManager::getInstance().removeAllGui();
                    GUIManager::getInstance().showGuiWithName(GUISwing::className);
                }
                break;
                case GAME_AA:
                {
                    game->changeToPortrait();
                    GUIManager::getInstance().removeAllGui();
                    GUIManager::getInstance().showGuiWithName(GUIaa::className);
                }
                break;
				default:
            	break;
			}
		}
        default:
            break;
    }
}

void GUIMinigames::scrollViewDidScroll(ax::extension::ScrollView *view) {
    AXLOGD("Dis scroll");
	countScroll++;
}

void GUIMinigames::scrollViewDidZoom(ax::extension::ScrollView *view) {
  //  AXLOGD("Did Zoom");
}

void GUIMinigames::onEnter() {
    BaseGUI::onEnter();
    //ax::Layer* layer = (Layer*)mainScene->getChildByTag(104);
   // layer->sc
   
}

bool GUIMinigames::onTouchBegan( Touch*touch, Event* event )
{
    Vec2 p = touch->getLocation();
    if (p.y > bgGame->getPosition().y + bgGame->getContentSize().height * 0.5) {
        countScroll = 10;
    }
    return BaseGUI::onTouchBegan(touch, event);
}
