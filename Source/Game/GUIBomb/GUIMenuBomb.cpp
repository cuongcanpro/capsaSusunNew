#include "guiMenuBomb.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"

#define GUI_MENU_BTN_CLOSE  1
#define GUI_MENU_BTN_SOUND 2
#define GUI_MENU_BTN_PLAY  3
#define GUI_MENU_BTN_LEVEL  4
#define NUM_LEVEl 4
std::string GUIMenuBomb::className = "GUIMenuBomb";
void GUIMenuBomb::initGUI()
{
	BaseGUI::initGUI();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = Scale9Sprite::create("GuiGame/Bomb/common_panel_background.png");
	addChild(bg);
	bg->setPosition(size.width * 0.5, size.height * 0.55);
	bg->setContentSize(Size(size.width * 0.95, 400));
	
	btnClose = addButton(GUI_MENU_BTN_CLOSE, new GameImage("btnClose.png", false), bg);
	btnClose->setPosition(bg->getContentSize().width * 0.95, bg->getContentSize().height * 0.95);
	btnClose->addBehavior(new BubbleBehavior());

	btnNewGame = addButton(GUI_MENU_BTN_PLAY, new GameImage("btnNewGameBig.png", false), bg);
	btnNewGame->setPosition(bg->getContentSize().width * 0.5, btnNewGame->getHeight() * 0.95);
	btnNewGame->addBehavior(new BubbleBehavior());

	string arrString[NUM_LEVEl] = {"Easy", "Medium", "Hard", "Expert" };
	for (int i = 0; i < NUM_LEVEl; i++) {
		
		arrayButton[i] = addButton(GUI_MENU_BTN_LEVEL + i, new GameImage("Bomb/common_btn_gray.png", false), bg);
		arrayButton[i]->setPosition(bg->getContentSize().width * 0.2 + 50 * i, bg->getContentSize().height * 0.5);
		arrayButton[i]->addBehavior(new BubbleBehavior());

		Text* lbBomb = Text::create(arrString[i].c_str(), "fonts/tahomabd.ttf", 30);
		lbBomb->enableOutline(Color4B(100, 100, 100, 255), 3);
		lbBomb->setColor(Color3B(240, 240, 240));
		arrayButton[i]->normalImage->addChild(lbBomb);
		arrayLabel[i] = lbBomb;
		//lbBomb->setPosition(ccp(size.width * 0.05, btnBack->getPositionY()));
		//lbBomb->setAnchorPoint(ccp(0, 0.5));
		//lbBomb->setTextHorizontalAlignment(TextHAlignment::LEFT);
	}
	int numPerRow = 2;
	float padX = 10;
	float padY = 10;
	float sum = arrayButton[0]->getWidth() * numPerRow + padX * (numPerRow - 1);
	float startX = bg->getContentSize().width * 0.5 - sum * 0.5;
	int numRow = NUM_LEVEl / numPerRow;
	sum = arrayButton[0]->getHeight() * numRow + padY * (numRow - 1);
	float startY = bg->getContentSize().height * 0.5 - sum * 0.5 + btnNewGame->getHeight() * 0.8;
	for (int i = 0; i < NUM_LEVEl; i++) {
		int row = i / numPerRow;
		int column = i % numPerRow;
		arrayButton[i]->setPosition(startX + padX * column + arrayButton[0]->getWidth() * (column + 0.5), startY + padY * row + arrayButton[0]->getHeight() * (row + 0.5));
	}
}

void okNewGame() {
	GUIManager::getInstance().guiBomb->boardData->setLevel(GUIManager::getInstance().guiMenuBomb->currentLevel);
	UserDefault::getInstance()->setIntegerForKey("currentTime", 0);
	UserDefault::getInstance()->flush();
	GUIManager::getInstance().guiBomb->newGame();
	GUIManager::getInstance().guiMenuBomb->hideGUI();
	
}

void cancelNewGame() {
	GUIManager::getInstance().guiMenuBomb->hideGUI();
}

void GUIMenuBomb::onButtonRelease(int buttonId, Touch* event)
{
    GameSound::playClick();
	switch(buttonId)
	{
	case GUI_MENU_BTN_CLOSE:
		GUIManager::getInstance().guiMenuBomb->hideGUI();
		break;
	case GUI_MENU_BTN_PLAY:
		if (GUIManager::getInstance().guiBomb->isPlaying())
			GUIManager::getInstance().guiDialog->showGUI("Do you want to start new game ", okNewGame, false, cancelNewGame);
		else
			okNewGame();
		
		break;
	default:
		updateCurrentLevel(buttonId - GUI_MENU_BTN_LEVEL);
		break;
	}
}

void GUIMenuBomb::hideGUI()
{
	setVisible(false);
	GUIManager::getInstance().removeFromListGui();
	
	/*if (GUIManager::getInstance().guiPop != NULL && GUIManager::getInstance().guiPop.isVisible())
		GUIManager::getInstance().guiPop.newGame();*/
}

void GUIMenuBomb::showGUI()
{
	bg->setScale(1);
	
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	bg->setPositionY(size.height * 1.1);
	bg->runAction(EaseBackOut::create(MoveTo::create(0.5, Vec2(size.width * 0.5, size.height * 0.55))));
	bg->setScaleY(0.7);
	bg->runAction(EaseBounceOut::create(ScaleTo::create(0.5, 1.0, 1.0)));
	
		updateCurrentLevel(GUIManager::getInstance().guiBomb->boardData->level);
	
}

void GUIMenuBomb::moveEffect(Node* node, int rate, float delay)
{
	float save = node->getPositionY();
	node->setPositionY(save + 100 * rate);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseBackOut::create(MoveBy::create(0.7, Vec2(0, -100 * rate))),
		NULL
	));
}

void GUIMenuBomb::loadSound()
{
	
}

void GUIMenuBomb::updateCurrentLevel(int currentLevel)
{
	this->currentLevel = currentLevel;
	for (int i = 0; i < NUM_LEVEl; i++) {
		arrayLabel[i]->setColor(Color3B(240, 240, 240));
	}
	arrayLabel[currentLevel]->setColor(Color3B(240, 240, 0));
}
