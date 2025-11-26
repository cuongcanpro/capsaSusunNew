#include "guiBomb.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"

#define GUI_MENU_BTN_BACK  1
#define GUI_MENU_BTN_SOUND 2
#define GUI_MENU_BTN_PLAY  3
#define GUI_MENU_BTN_MODE  4
#define GUI_MENU_BTN_TOP  5
#define GUI_MENU_BTN_NEW_GAME  6
#define GUI_MENU_BTN_NEW 7
std::string GUIBomb::className = "GUIBomb";
void GUIBomb::initGUI()
{
	BaseGUI::initGUI();
	setKeypadEnabled(true);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = Scale9Sprite::create("GuiGame/brickWhite.png");
	bg->setColor(Color3B(50, 50, 50));
    bg->setColor(Color3B(15, 36, 60));
	bg->setContentSize(Size(size.width, size.height));
	addChild(bg, -1);
	bg->setPosition(size.width * 0.5, size.height * 0.5);

	groupCell = Node::create();
	addChild(groupCell);

	bgMenu = Scale9Sprite::create("GuiGame/brickWhite.png");
	addChild(bgMenu);
	bgMenu->setColor(Color3B(100, 100, 100));
        bgMenu->setColor(Color3B(15, 36, 60));
	float marginY = 30;

    if (size.width / size.height < 11.0 / 20.0)
    {
        bgMenu->setContentSize(Size(size.width + 10, 180 + marginY));
    }
    else
    {
        bgMenu->setContentSize(Size(size.width + 10, 180));
    }
    bgMenu->setPosition(size.width * 0.5, size.height - bgMenu->getContentSize().height * 0.5);

	bgAds = Scale9Sprite::create("GuiGame/brickWhite.png");
	bgAds->setColor(Color3B(20, 20, 20));
	addChild(bgAds);
	bgAds->setContentSize(Size(size.width + 10, 130));
	bgAds->setPosition(size.width * 0.5, bgAds->getContentSize().height * 0.5);

	btnBack = addButton(GUI_MENU_BTN_BACK, new GameImage("btnBack.png", false));
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6, size.height - marginY - btnBack->getHeight() * 0.5);
	btnBack->addBehavior(new BubbleBehavior());

	btnSound = addButton(GUI_MENU_BTN_SOUND, new GameImage("btnSoundOn.png", false));
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1, btnBack->getPositionY());
	btnSound->addBehavior(new BubbleBehavior());
	loadSound();

	btnTop = addButton(GUI_MENU_BTN_TOP, new GameImage("btnTop.png", false));
	btnTop->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1, btnBack->getPositionY());
	btnTop->addBehavior(new BubbleBehavior());
    btnTop->setVisible(false);

	Scale9Sprite *bgMode = Scale9Sprite::create("GuiGame/Bomb/bg.png");
	bgMode->setColor(Color3B(230, 230, 230));
	addChild(bgMode);
	bgMode->setContentSize(Size(90, 70));
	
	btnMode = addButton(GUI_MENU_BTN_MODE, new GameImage("Bomb/iconSmile.png", false));
	btnMode->addBehavior(new BubbleBehavior());

	bgNewGame = Scale9Sprite::create("GuiGame/brickWhite.png");
	addChild(bgNewGame);
	bgNewGame->setColor(Color3B(50, 50, 50));
	bgNewGame->setContentSize(Size(size.width, 50));
	bgNewGame->setPosition(size.width * 0.5, bgAds->getPositionY() + bgAds->getContentSize().height * 0.6);

	btnNewGame = addButton(GUI_MENU_BTN_PLAY, new GameImage("btnWhite.png", false));
	btnNewGame->addBehavior(new BubbleBehavior());
	btnNewGame->setPosition(size.width * 0.5, bgNewGame->getPositionY());
	btnNewGame->normalImage->setOpacity(0);
	//btnNewGame->normalImage->setScaleY(4);

	lbEndGame = Text::create("0", "fonts/tahomabd.ttf", 18);
	lbEndGame->enableOutline(Color4B(20, 20, 20, 255), 2);
	lbEndGame->setColor(Color3B(240, 240, 240));
	addChild(lbEndGame, 2);
	lbEndGame->setPosition(Vec2(size.width * 0.5, btnNewGame->getPositionY()));
	lbEndGame->setAnchorPoint(Vec2(0.5, 0.5));
	lbEndGame->setTextHorizontalAlignment(TextHAlignment::CENTER);

	Scale9Sprite *bgBomb = Scale9Sprite::create("GuiGame/Bomb/bg.png");
	//bgBomb->setColor(Color3B(150, 150, 150));
	addChild(bgBomb);
	bgBomb->setContentSize(Size(100, 70));
	bgBomb->setPosition(bgBomb->getContentSize().width * 0.5 + 5, btnBack->getPositionY());

	iconBomb = Sprite::createWithSpriteFrameName("iconBomb.png");
	addChild(iconBomb);
	iconBomb->setPosition(bgBomb->getPositionX() - bgBomb->getContentSize().width * 0.5 + iconBomb->getContentSize().width * 0.6, btnBack->getPositionY());

	lbBomb = Text::create("0", "fonts/tahomabd.ttf", 20);
	lbBomb->enableOutline(Color4B(120, 120, 120, 255), 2);
	lbBomb->setColor(Color3B(240, 240, 240));
	addChild(lbBomb);
	lbBomb->setPosition(Vec2(iconBomb->getPositionX() + iconBomb->getContentSize().width * 0.55, iconBomb->getPositionY()));
	lbBomb->setAnchorPoint(Vec2(0, 0.5));
	lbBomb->setTextHorizontalAlignment(TextHAlignment::LEFT);

	Scale9Sprite *bgTime = Scale9Sprite::create("GuiGame/Bomb/bg.png");
	//bgTime->setColor(Color3B(150, 150, 150));
	addChild(bgTime);
	bgTime->setContentSize(Size(110, 70));
	bgTime->setPosition(bgBomb->getPositionX() + bgBomb->getContentSize().width * 0.5 + 2 + bgTime->getContentSize().width * 0.5, btnBack->getPositionY());

	bgMode->setPosition(bgTime->getPositionX() + bgTime->getContentSize().width * 0.5 + bgMode->getContentSize().width * 0.5 + 2, btnBack->getPositionY());
	if (size.width * 0.5 + bgMode->getContentSize().width * 0.5 + 10 < btnTop->getPositionX() - btnTop->getWidth() * 0.5 && bgMode->getPositionX() < size.width * 0.5) {
		bgMode->setPosition(size.width * 0.5, bgMode->getPositionY());
	}
    bgMode->setPosition(size.width * 0.5, btnBack->getPositionY() - bgMode->getContentSize().height - 10);
	btnMode->setPosition(bgMode->getPositionX(), bgMode->getPositionY());
	//btnMode->setPosition(bgTime->getPositionX() + bgTime->getContentSize().width * 0.5 + btnMode->getWidth() * 0.6, btnBack->getPositionY());
	/*if (size.width * 0.5 + btnMode->getWidth() * 0.5 + 10 < btnTop->getPositionX() - btnTop->getWidth() * 0.5 && btnMode->getPositionX() < size.width * 0.5) {
		btnMode->setPosition(size.width * 0.5, btnMode->getPositionY());
	}*/

	Text* lbSetting = Text::create("Setting", "fonts/tahomabd.ttf", 14);
	lbSetting->enableOutline(Color4B(30, 40, 80, 255), 2);
	lbSetting->setColor(Color3B(240, 240, 240));
	addChild(lbSetting);
	lbSetting->setPosition(Vec2(btnMode->getPositionX(), btnMode->getPositionY() + 35));

	lbLevel = Text::create("Easy", "fonts/tahomabd.ttf", 14);
	lbLevel->enableOutline(Color4B(30, 40, 80, 255), 2);
	lbLevel->setColor(Color3B(240, 240, 240));
	addChild(lbLevel);
	lbLevel->setPosition(Vec2(btnMode->getPositionX(), btnMode->getPositionY() - 35));

	lbTimeGame = Text::create("0", "fonts/tahomabd.ttf", 20);
	lbTimeGame->enableOutline(Color4B(120, 120, 120, 255), 2);
	lbTimeGame->setColor(Color3B(240, 240, 240));
	addChild(lbTimeGame);
	lbTimeGame->setPosition(Vec2(bgTime->getPositionX(), btnBack->getPositionY() - 12));
	lbTimeGame->setAnchorPoint(Vec2(0.5, 0.5));
	lbTimeGame->setTextHorizontalAlignment(TextHAlignment::CENTER);

	lbTimeBest = Text::create("0", "fonts/tahomabd.ttf", 20);
	lbTimeBest->enableOutline(Color4B(120, 120, 120, 255), 2);
	lbTimeBest->setColor(Color3B(240, 240, 0));
	addChild(lbTimeBest);
	lbTimeBest->setPosition(Vec2(lbTimeGame->getPositionX(), btnBack->getPositionY() + 12));
	lbTimeBest->setAnchorPoint(Vec2(0.5, 0.5));
	lbTimeBest->setTextHorizontalAlignment(TextHAlignment::CENTER);

	boardData = new BoardDataBomb();
	boardData->setLevel(game->currentMode);
	
	for (int i = 0; i < BOARD_ROW_BOMB; i++) {
		for (int j = 0; j < BOARD_COLUMN_BOMB; j++) {
			arrayCell[i][j] = new CellBomb();
			groupCell->addChild(arrayCell[i][j]);
		}
	}
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, ax::Event* event) {
		Size size = Director::getInstance()->getRenderView()->getVisibleSize();
		if (keyCode == EventKeyboard::KeyCode::KEY_1) {
			Touch* touch = new Touch();
			touch->setTouchInfo(1, 200, size.height - 200);
			GUIManager::getInstance().guiBomb->changeListTouch(touch, ChangeTouch::TOUCH_ADD);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
			Touch* touch = new Touch();
			Size size = Director::getInstance()->getRenderView()->getVisibleSize();
			touch->setTouchInfo(1, 200,size.height - 200);
			GUIManager::getInstance().guiBomb->changeListTouch(touch, ChangeTouch::TOUCH_REMOVE);
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	iconDot = Sprite::create("GuiGame/stars.png");
	groupCell->addChild(iconDot);
	iconDot->setColor(Color3B(255, 255, 0));
	iconDot->setVisible(false);
	

	// Mouse Event
	//auto mouseListener = EventListenerMouse::create();
	//mouseListener->onMouseScroll = [this](ax::EventMouse* event) {
	//	//AXLOGD("Scoll x %f y %f ", event->getScrollX(), event->getScrollY());
 //       if (GUIManager::getInstance().guiBomb != NULL && GUIManager::getInstance().guiBomb->isVisible())
 //       {
 //           if (event->getScrollY() > 0)
 //           {
 //               GUIManager::getInstance().guiBomb->groupCell->setScale(
 //                   GUIManager::getInstance().guiBomb->groupCell->getScale() * 1.1);
 //           }
 //           else
 //           {
 //               GUIManager::getInstance().guiBomb->groupCell->setScale(
 //                   GUIManager::getInstance().guiBomb->groupCell->getScale() * 0.9);
 //           }
 //       }
 //       else
 //       {
 //           if (event->getScrollY() > 0)
 //           {
 //              // GUIManager::getInstance().guiBombExtend.groupCell->setScale(
 //              //     GUIManager::getInstance().guiBombExtend.groupCell->getScale() * 1.1);
 //           }
 //           else
 //           {
 //              // GUIManager::getInstance().guiBombExtend.groupCell->setScale(
 //                  // GUIManager::getInstance().guiBombExtend.groupCell->getScale() * 0.9);
 //           }
 //       }
	//	
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	manager = EffectManager::create(size);
	Effect* effect = Effect::create("fire.efk", 60);
	emitter = EffectEmitter::create(manager);
	emitter->setEffect(effect);
	emitter->setPlayOnEnter(false);
	emitter->setIsLooping(false);
	emitter->setPosition(size.width * 0.5, size.height * 0.5 - 50);
	groupCell->addChild(emitter);
	emitter->setRemoveOnStop(false);
	emitter->stop();
	emitter->setVisible(false);
	emitter->setSpeed(0.5);


	heightView = size.height - bgMenu->getContentSize().height - bgAds->getContentSize().height;
	posCenter = Vec2(size.width * 0.5, bgAds->getPositionY() + bgAds->getContentSize().height * 0.5 + heightView * 0.5);

	groupHelp = new GroupBombHelp();
	addChild(groupHelp);

	auto listener2 = EventListenerTouchAllAtOnce::create();
    listener2->onTouchesBegan = AX_CALLBACK_2(GUIBomb::onTouchesBegan, this);
    typeBoard = TypeBoard::BOARD_NORMAL;

    border = addImage("border2.png");
    border->setLocalZOrder(3);
    border->setWidth(size.width);
    border->setHeight(heightView + 20);
    border->setPosition(size.width * 0.5, posCenter.y);
    border->setColor(Color3B(120, 130, 170));
}

void GUIBomb::onButtonRelease(int buttonId, Touch* event)
{
    GameSound::playClick();
	switch(buttonId)
	{
	case GUI_MENU_BTN_PLAY:
		//hideGUI();
		bg->setVisible(false);
		
		startGame();
		break;
	case GUI_MENU_BTN_BACK:
		onBackKey();
		
		break;
        case GUI_MENU_BTN_MODE:
        {
            GUIMenuBomb* gui = (GUIMenuBomb*)GUIManager::getInstance().showGuiWithName(GUIMenuBomb::className);
            gui->showGUI();
            break;
        }
        case GUI_MENU_BTN_NEW_GAME:
        {
            game->showAdsFull();
            startGame();
            break;
        }
	case GUI_MENU_BTN_SOUND:
		game->music = !game->music;
		UserDefault::getInstance()->setBoolForKey("music", game->music);
		UserDefault::getInstance()->flush();
		loadSound();
		break;
	case GUI_MENU_BTN_TOP: {
		int time = game->arrBestTime[boardData->level] * 1000;
        if (time <= 0)
        {
            time = 10000000;
        }
		JNIUtils::submitScore(time, boardData->level);
		break;
	}
	case GUI_MENU_BTN_NEW: {
		break;
	}
	}
}

void GUIBomb::onBackKey()
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
        game->changeToLandscape();
		GUIManager::getInstance().isCallBackPress = true;
		saveData();
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
	}
}

void GUIBomb::hideGUI()
{
	setVisible(false);
	GUIManager::getInstance().removeFromListGui();
	
	/*if (GUIManager::getInstance().guiPop != NULL && GUIManager::getInstance().guiPop.isVisible())
		GUIManager::getInstance().guiPop.newGame();*/
}

void GUIBomb::showGUI()
{
	//BaseGUI::showGUI();
	//setVisible(true);
    startGame();
}

void GUIBomb::moveEffect(Node* node, int rate, float delay)
{
	float save = node->getPositionY();
	node->setPositionY(save + 100 * rate);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseBackOut::create(MoveBy::create(0.7, Vec2(0, -100 * rate))),
		NULL
	));
}

void GUIBomb::loadSound()
{
	if (game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png", false);
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png", false);
	}
	
}

void GUIBomb::startGame()
{
    newGame();
}

Size GUIBomb::getSizeGroupCell()
{
    return Size(cellSize * boardData->sizeColumn, cellSize * boardData->sizeRow);
}

void GUIBomb::loadSaveGame() {
    timeGame = game->currentTime;
    boardData->setLevel(game->currentMode);
    boardData->loadData();
    gameState = BOMB_GAME_PLAY;
}

void GUIBomb::newGame()
{
    for (int i = 0; i < arrayBomb.size(); i++)
    {
        arrayBomb[i]->setVisible(false);
    }
    //game->showHelpBomb = true;
	bgNewGame->setVisible(false);
	lbEndGame->setVisible(false);
	btnNewGame->setVisible(false);
	GameSound::playStartGame();
	for (int i = 0; i < BOARD_ROW_BOMB; i++) {
		for (int j = 0; j < BOARD_COLUMN_BOMB; j++) {
			arrayCell[i][j]->setVisible(false);
		}
	}
	timeTouch = -1;
	arrTouch.clear();
	

	if (typeBoard == TypeBoard::BOARD_NORMAL && (game->currentTime <= 0 || game->showHelpBomb)) {
		timeGame = 0;
        boardData->resetMap();
		gameState = BOMB_GAME_WAIT_FIRST_TOUCH;
        UserDefault::getInstance()->setBoolForKey("showHelpBomb", false);
        UserDefault::getInstance()->flush();
	}
	else {
        loadSaveGame();
	}
	
	lbBomb->setString(to_string(boardData->getNumBombRemain()));
	float pad = 50;
	cellSize = 83;
	
    groupCell->setContentSize(Size(cellSize * boardData->sizeColumn, cellSize * boardData->sizeRow));
	startX = -groupCell->getContentSize().width * 0.5;
	startY = -groupCell->getContentSize().height * 0.5;
	for (int i = 0; i < boardData->sizeRow; i++) {
		for (int j = 0; j < boardData->sizeColumn; j++) {
			arrayCell[i][j]->setState(boardData->arrayCell[i][j], boardData->arrayData[i][j], 0);
			arrayCell[i][j]->setPosition(startX + cellSize * (j + 0.5), startY + cellSize * (i + 0.5));
			arrayCell[i][j]->setVisible(true);
		}
	}
	
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	groupCell->setPosition(posCenter);

	// zoom de Board Fit man hinh
	scaleToFitScreen(0);
	
	if (gameState == BOMB_GAME_WAIT_FIRST_TOUCH) {
		int medium = boardData->getNumCell() / 2;
		int row = medium / boardData->sizeColumn;
		int column = medium % boardData->sizeColumn;
		row = boardData->sizeRow / 2;
		column = boardData->sizeColumn / 2;
		arrayCell[row][column]->effectNewGame(0);


		for (int i = 1; i < boardData->sizeColumn + 1; i++) {
			int rowTop = row + i;
			int rowBottom = row - i;
			int columnLeft = column - i;
			int columnRight = column + i;
			float time = i * 0.1;

			for (int j = 1; j < i * 2; j++) {
				if (boardData->checkPointInBoard(rowTop, columnLeft + j))
					arrayCell[rowTop][columnLeft + j]->effectNewGame(time);

				if (boardData->checkPointInBoard(rowBottom, columnLeft + j))
					arrayCell[rowBottom][columnLeft + j]->effectNewGame(time);

				if (boardData->checkPointInBoard(rowBottom + j, columnLeft))
					arrayCell[rowBottom + j][columnLeft]->effectNewGame(time);

				if (boardData->checkPointInBoard(rowBottom + j, columnRight))
					arrayCell[rowBottom + j][columnRight]->effectNewGame(time);
			}
			if (boardData->checkPointInBoard(rowBottom, columnLeft))
				arrayCell[rowBottom][columnLeft]->effectNewGame(time);

			if (boardData->checkPointInBoard(rowBottom, columnRight))
				arrayCell[rowBottom][columnRight]->effectNewGame(time);

			if (boardData->checkPointInBoard(rowTop, columnRight))
				arrayCell[rowTop][columnRight]->effectNewGame(time);

			if (boardData->checkPointInBoard(rowTop, columnLeft))
				arrayCell[rowTop][columnLeft]->effectNewGame(time);
		}

		// Zoom de size Cell = 1/10 size man hinh
        float scale = size.width * 0.1 / cellSize;
		lbEndGame->setVisible(true);
		if (game->showHelpBomb) {
			scale = groupCell->getScale();
			
			lbEndGame->setString("Let's try Tutorial!");
		}
		else {
			lbEndGame->setString("You can zoom in or zoom out");
		}
        
        if (typeBoard == TypeBoard::BOARD_NORMAL)
        {
            groupCell->runAction(
                Sequence::create(DelayTime::create(0.1 * row), ScaleTo::create(0.5, scale),
                                    CallFunc::create(AX_CALLBACK_0(GUIBomb::callbackNewGame, this)), NULL));
        }
	}
	game->currentTime = 0;
	lbTimeBest->setString(GameUtility::convertToTime(game->arrBestTime[boardData->level]));
	if (game->showHelpBomb) {
		groupHelp->setVisible(true);
		groupHelp->hideHelp();
	}
	else {
		groupHelp->setVisible(false);
	}
	btnMode->normalImage->setImage("Bomb/iconSmile.png");
	string arr[4] = { "Easy", "Medium", "Hard", "Extreme" };
	lbLevel->setString(arr[boardData->level]);
	UserDefault::getInstance()->setIntegerForKey("currentMode", boardData->level);
	UserDefault::getInstance()->flush();
	JNIUtils::sendEvent(("newGame" + to_string(boardData->level)).c_str(), "1");
}

void GUIBomb::callbackNewGame()
{
	if (game->showHelpBomb) {
		groupHelp->setVisible(true);
		Vec2 pos = groupCell->convertToWorldSpace(arrayCell[3][2]->getPosition());
		groupHelp->indexHelp = 0;
		groupHelp->showHelp(pos, 0.5);
	}
}

void okWinGame() {
    game->showHelpBomb = false;
	GUIManager::getInstance().guiBomb->newGame();
}

void GUIBomb::update(float delta)
{
	manager->update(delta);
	if (gameState == BOMB_GAME_PLAY) {
		if (timeTouch >= 0 && arrTouch.size() == 1) {
			timeTouch = timeTouch + delta;
			if (timeTouch >= 0.3) {
				if (groupHelp->checkCanAction(currentRow, currentColumn, HelpType::HELP_GUESS) == false)
					return;
				JNIUtils::vibrate(10);
                if (boardData->isGenData == false) {
                    boardData->genData(PointGame(currentRow, currentColumn));
                }
				if (boardData->arrayCell[currentRow][currentColumn] != CellDataState::CELL_OPEN) {
					if (boardData->arrayCell[currentRow][currentColumn] == CellDataState::CELL_NOT_OPEN) {
						boardData->setCell(currentRow, currentColumn, CellDataState::CELL_BOMB_GUESS);
						arrayCell[currentRow][currentColumn]->setState(CellDataState::CELL_BOMB_GUESS);
						GameSound::playBombGuess();
						if (boardData->checkWin()) {
							//GUIManager::getInstance().guiDialog->showGUI("Win Game", okWinGame, true);
							endGame();
							clearData();
						}
						else {
							saveData();
						}
						if (groupHelp->isVisible()) {
							groupHelp->indexHelp++;
							Vec2 pos;
							if (groupHelp->indexHelp == HELP_TWO_BOMB) {
								pos = groupCell->convertToWorldSpace(arrayCell[4][3]->getPosition());
								groupHelp->showHelp(pos, 1.0);
							}
                            else if (groupHelp->indexHelp >= HELP_GUESS_TWO_BOMB) {
								
                                game->showHelpBomb = false;
								timeGame = 0;
								UserDefault::getInstance()->setIntegerForKey("currentTime", 0);
								UserDefault::getInstance()->setBoolForKey("showHelpBomb", false);
								UserDefault::getInstance()->flush();
								boardData->setLevel(0);
								groupHelp->setVisible(false);
								GUIManager::getInstance().guiDialog->showGUI("Find all bombs and open all cells to finish the game. Let's try!", okWinGame, true);
							}
							else if (groupHelp->indexHelp == HELP_GUESS_THIRD_BOMB) {
								pos = groupCell->convertToWorldSpace(arrayCell[2][0]->getPosition());
								groupHelp->showHelp(pos, 1.0);
							}
							else if (groupHelp->indexHelp == HELP_GUESS_FOUR_BOMB) {
								pos = groupCell->convertToWorldSpace(arrayCell[0][1]->getPosition());
								groupHelp->showHelp(pos, 1.0);
								
							}
							else if (groupHelp->indexHelp > HELP_GUESS_FOUR_BOMB) {
								game->showHelpBomb = false;
								timeGame = 0;
								UserDefault::getInstance()->setIntegerForKey("currentTime", 0);
								UserDefault::getInstance()->setBoolForKey("showHelpBomb", false);
								UserDefault::getInstance()->flush();
								boardData->setLevel(0);
								groupHelp->setVisible(false);
								GUIManager::getInstance().guiDialog->showGUI("Find all bombs and open all cells to finish the game. Let's try!", okWinGame, true);
							}
						}
					}
					else {
						boardData->setCell(currentRow, currentColumn, CellDataState::CELL_NOT_OPEN);
						arrayCell[currentRow][currentColumn]->setState(CellDataState::CELL_NOT_OPEN);
						GameSound::playBombUnGuess();
						saveData();
					}
					lbBomb->setString(to_string(boardData->getNumBombRemain()));
					if (boardData->getNumBombRemain() < 0){
						lbBomb->setColor(Color3B(255, 0, 0));
						iconBomb->stopAllActions();
						iconBomb->runAction(
							RepeatForever::create(
								Sequence::create(
									ScaleTo::create(0.2, 1.1),
									ScaleTo::create(0.2, 1.0),
									NULL
								)
							)
						);
					}
					else {
						lbBomb->setColor(Color3B(240, 240, 240));
						iconBomb->stopAllActions();
						iconBomb->setScale(1.0);
					}
				}
				timeTouch = -1;
			}
		}
		timeGame = timeGame + delta;
	}
    if (typeBoard == TypeBoard::BOARD_NORMAL)
    {
        lbTimeGame->setString(GameUtility::convertToTime(timeGame));
    }
}

void GUIBomb::endGame()
{
	bgNewGame->setVisible(true);
	bgNewGame->runAction(
		RepeatForever::create(
			Sequence::create(
				FadeIn::create(0.2),
				FadeOut::create(0.2),
				NULL
			)
		)
	);
	btnNewGame->setVisible(true);
	lbEndGame->setVisible(true);
	gameState = BOMB_GAME_END;
	string convert = GameUtility::convertToTime(timeGame);
	if (boardData->checkWin()) {
		JNIUtils::sendEvent(("endGame" + to_string(boardData->level)).c_str(), "1");
		btnMode->normalImage->setImage("Bomb/iconGlasses.png");
		
		if (game->showHelpBomb) {
			game->showHelpBomb = false;
			UserDefault::getInstance()->setBoolForKey("showHelpBomb", false);
			UserDefault::getInstance()->flush();
			boardData->setLevel(0);
            GameSound::playWin();
		}
        else
        {
            GUIManager::getInstance().guiResult->showGUI(timeGame, game->arrBestTime[boardData->level], true);
        }
		//GameSound::playWin();
	}
	else {
		btnMode->normalImage->setImage("Bomb/iconCry.png");
		int count = 0;
        float delayBomb = 0.1 / (boardData->level * 2 + 1);
                float numShow   = 1.0 / (boardData->level + 1);
		for (int i = 0; i < boardData->sizeRow; i++) {
			for (int j = 0; j < boardData->sizeColumn; j++) {
				if (boardData->arrayBomb[i][j] == 0 && arrayCell[i][j]->cellState == CellDataState::CELL_BOMB_GUESS) {
					arrayCell[i][j]->showIconWrong();
				}
				else if (boardData->arrayCell[i][j] == CELL_NOT_OPEN) {
					if (boardData->arrayBomb[i][j] == 1) {
						count++;
						arrayCell[i][j]->setState(CELL_BOMB_REAL_CLOSE, 0, count * delayBomb);
                        Vec2 pos = arrayCell[i][j]->getPosition();
                        if (GameUtility::getRandom() < numShow) {
                            
                            showBomb(pos.x, pos.y, count * delayBomb);
                        }
					}
					/*else {
						arrayCell[i][j]->setState(CELL_OPEN, boardData->arrayData[i][j], count* 0.01);
					}*/

				}
			}
		}
        numVibrate = 0;
        effectVibrateSmall();
		float timeDelay = 1.0;
		//startSoundOpen(count);
		if (count > 0)
			timeDelay = 5.0;
		lbEndGame->setString("You Lose. New Game ->>>>>>");
        runAction(
            Sequence::create(
                DelayTime::create(3.0),
                CallFunc::create(AX_CALLBACK_0(GUIBomb::callbackShowAds, this)),
                DelayTime::create(0.1),
                CallFunc::create(AX_CALLBACK_0(GUIBomb::showEndGame, this)),
                NULL
            )
        );
	}
	scaleToFitScreen(0.5);
	clearData();
    
	//bg->setVisible(true);
}


void GUIBomb::callbackShowAds()
{
    game->showAdsFull();
}


void GUIBomb::showEndGame() {
    if (gameState == BOMB_GAME_END)
    {
        GUIMenuBomb* gui = (GUIMenuBomb*)GUIManager::getInstance().showGuiWithName(GUIMenuBomb::className);
        gui->currentLevel = boardData->level;
    }
        
}

void GUIBomb::effectEndGame(PointGame p) {
    JNIUtils::vibrate(100);
    numVibrate       = 0;
    saveGroupCellPos = groupCell->getPosition();
    effectVibrate();
    gameState = BOMB_GAME_END;
    
    runAction(Sequence::create(DelayTime::create(1.0), CallFunc::create(AX_CALLBACK_0(GUIBomb::endGame, this)), NULL));
    for (int i1 = 0; i1 < boardData->sizeRow; i1++)
    {
        for (int j1 = 0; j1 < boardData->sizeColumn; j1++)
        {
            arrayCell[i1][j1]->numVibrate = 0;
            arrayCell[i1][j1]->effectVibrate();
        }
    }
    if (p.x >= 0)
    {
        arrayCell[p.x][p.y]->setState(CellDataState::CELL_BOMB_REAL_OPEN);
        emitter->setVisible(true);
        emitter->play(0);
        emitter->setPosition(this->arrayCell[p.x][p.y]->getPosition());
    }
    
    
    GameSound::playBomb();
    clearData();
}

void GUIBomb::showBomb(float px, float py, float delayTime)
{
    
    BombEffect* group = NULL;
    for (int i = 0; i < arrayBomb.size(); i++)
    {
        if (!arrayBomb.at(i)->isVisible())
        {
            arrayBomb.at(i)->setOpacity(255);
            group = arrayBomb.at(i);
            break;
        }
    }
    if (group == NULL)
    {
        group = new BombEffect();
        groupCell->addChild(group);
    }
    group->setLocalZOrder(100);
    arrayBomb.push_back(group);
    group->setPosition(px, py);
    group->showBomb(delayTime);
}


void okEndGameBomb() {
	GUIManager::getInstance().guiBomb->newGame();
}

void GUIBomb::showDialogEndGame()
{
	if (GUIManager::getInstance().guiMenuBomb != NULL && GUIManager::getInstance().guiMenuBomb->isVisible())
		return;
	string convert = GameUtility::convertToTime(timeGame);
    GUIManager::getInstance().guiDialog->showGUI(("Your Time: " + convert).c_str(), okEndGameBomb, true);
}

void GUIBomb::showDialogWinGame()
{
	if (GUIManager::getInstance().guiMenuBomb != NULL && GUIManager::getInstance().guiMenuBomb->isVisible())
		return;
	string convert = GameUtility::convertToTime(timeGame);
    GUIManager::getInstance().guiDialog->showGUI(("New Best Time: " + convert).c_str(), okEndGameBomb, true);
}

void GUIBomb::showDialogLoseGame()
{
	if (GUIManager::getInstance().guiMenuBomb != NULL && GUIManager::getInstance().guiMenuBomb->isVisible())
		return;
	string convert = GameUtility::convertToTime(timeGame);
    GUIManager::getInstance().guiDialog->showGUI("You Lose. Try Again", okEndGameBomb, true);
}

bool GUIBomb::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	groupCell->setColor(Color3B(255, 255, 255));
	isMoving = false;
	Vec2 pos = pTouch->getLocation();
    if (pos.y < bgAds->getContentSize().height)
    {
        timeTouch = -1;
        return BaseGUI::onTouchBegan(pTouch, pEvent);
    }
	pos = groupCell->convertToNodeSpace(pos);
	pos.x = pos.x - startX;
	pos.y = pos.y - startY;
	int row = floor(pos.y / cellSize);
	int column = floor(pos.x / cellSize);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	
	if (row < 0 || row >= boardData->sizeRow || column < 0 || column >= boardData->sizeColumn || (pTouch->getLocation().y) >= (bgMenu->getPositionY() - bgMenu->getContentSize().height * 0.5)) {
		timeTouch = -1;
		return BaseGUI::onTouchBegan(pTouch, pEvent);
	}
	else {
		currentRow = row;
		currentColumn = column;
	}

	if (gameState == BOMB_GAME_WAIT_FIRST_TOUCH) {
		gameState = BOMB_GAME_PLAY;
	}
	
	if (gameState != BOMB_GAME_PLAY) {
		timeTouch = -1;
		return BaseGUI::onTouchBegan(pTouch, pEvent);
	}
	timeTouch = 0;
	changeListTouch(pTouch, ChangeTouch::TOUCH_ADD);
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIBomb::onTouchMoved(Touch*touch, Event* event)
{
	if (groupHelp->isVisible())
		return;
	if (gameState != BOMB_GAME_PLAY) {
		BaseGUI::onTouchMoved(touch, event);
		return;
	}
	//timeTouch = -1;
	changeListTouch(touch, ChangeTouch::TOUCH_CHANGE);
	if (arrTouch.size() >= 2) {
		timeTouch = -1;
		float newDistance = arrTouch[0].getLocation().getDistance(arrTouch[1].getLocation());
		float changeDistance = newDistance - lastDistance;
		if (abs(changeDistance) > 1) {
			// Zoom to
			float rateScale = abs(changeDistance) / 170 + 1;
			if (changeDistance > 0) {
				groupCell->setScale(groupCell->getScale() * rateScale);
			}
			else {
				groupCell->setScale(groupCell->getScale() / rateScale);
			}
			Vec2 newPointView1 = groupCell->convertToWorldSpace(pointViewLocal);
			float newPosX = groupCell->getPositionX() + pointViewGlobal.x - newPointView1.x;
			float newPosY = groupCell->getPositionY() + pointViewGlobal.y - newPointView1.y;
			groupCell->setPosition(newPosX, newPosY);
		}
		else {
			// Moving
			if (isTouchMove(touch)) {
				isMoving = true;
				groupCell->setPosition(groupCell->getPositionX() + touch->getDelta().x, groupCell->getPositionY() + touch->getDelta().y);
			}
		}
		lastDistance = arrTouch[0].getLocation().getDistance(arrTouch[1].getLocation());
		isMoving = true;
	}
	else {
		
		Vec2 currentPos = touch->getLocation();
		Vec2 lastPos = touch->getPreviousLocation();
		float distancePos = currentPos.getDistance(lastPos);
		//AXLOGD("Distance Pos %f ", distancePos);
		if (distancePos > 5) {
			timeTouch = -1;
			isMoving = true;
			if (distancePos > 7) {
				// move and slide
				float deltaX = currentPos.x - lastPos.x;
				float deltaY = currentPos.y - lastPos.y;
				lastMoveY = deltaY * 5;
				lastMoveX = deltaX * 5;
				isContinueMove = true;
			}
			else {
				isContinueMove = false;
			}
			groupCell->setPosition(groupCell->getPositionX() + touch->getDelta().x, groupCell->getPositionY() + touch->getDelta().y);
		}
	}
	
	BaseGUI::onTouchMoved(touch, event);
}

void GUIBomb::onTouchesBegan(const std::vector<Touch *>& touches, Event *event)
{
	AXLOGD("TOUCH SIze ==== %i ", touches.size());
	
}

void GUIBomb::changeListTouch(Touch* touch, ChangeTouch change)
{
	if (change == ChangeTouch::TOUCH_CHANGE) {
		for (int i = 0; i < arrTouch.size(); i++) {
			if (arrTouch.at(i).getID() == touch->getID()) {
				arrTouch.at(i).setTouchInfo(touch->getID(), touch->getLocation().x, touch->getLocation().y);
				return;
			}
		}
	}
	else {
		if (change == ChangeTouch::TOUCH_ADD) {
			Touch touchNew;
			touchNew.setTouchInfo(touch->getID(), touch->getLocation().x, touch->getLocation().y);
			arrTouch.push_back(touchNew);
		}
		else {
			for (int i = 0; i < arrTouch.size(); i++) {
				if (arrTouch.at(i).getID() == touch->getID()) {
					arrTouch.erase(arrTouch.begin() + i);
				}
			}
		}
		if (arrTouch.size() == 2) {
			pointViewGlobal = Vec2((arrTouch[0].getLocationInView().x + arrTouch[1].getLocationInView().x) * 0.5, (arrTouch[0].getLocationInView().y + arrTouch[1].getLocationInView().y) * 0.5);
			pointViewLocal = groupCell->convertToNodeSpace(pointViewGlobal);
			lastDistance = arrTouch[0].getLocation().getDistance(arrTouch[1].getLocation());
			iconDot->setPosition(pointViewLocal);
		}
	}
	
	AXLOGD("Size Touch %i" , arrTouch.size());
}


void GUIBomb::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (gameState != BOMB_GAME_PLAY) {
		BaseGUI::onTouchEnded(pTouch, pEvent);
		return;
	}

	if (arrTouch.size() == 1) {
		AXLOGD("TimeTouch %f ", timeTouch);
		if (timeTouch > 0) {
			Vec2 pos = pTouch->getLocation();
			pos = groupCell->convertToNodeSpace(pos);
			pos.x = pos.x - startX;
			pos.y = pos.y - startY;
			int row = floor(pos.y / cellSize);
			int column = floor(pos.x / cellSize);
			AXLOGD("Time Touch %f ", timeTouch);
			if (row < 0 || row >= boardData->sizeRow || column < 0 || column >= boardData->sizeColumn ||
				boardData->arrayCell[row][column] == CellDataState::CELL_BOMB_GUESS || groupHelp->checkCanAction(row, column, HelpType::HELP_OPEN) == false) {
				timeTouch = -1;
				isMoving = false;
				changeListTouch(pTouch, ChangeTouch::TOUCH_REMOVE);
				BaseGUI::onTouchEnded(pTouch, pEvent);
				return;
			}
            if (boardData->isGenData == false)
            {
                boardData->genData(PointGame(row, column));
            }
			vector<PointGame> arrPoint = boardData->getDataFromPoint(PointGame(row, column));
			if (arrPoint.size() > 0) {
				if (groupHelp->isVisible()) {
					groupHelp->indexHelp++;
					Vec2 pos;
					if (groupHelp->indexHelp == HELP_ONE_BOMB)
						pos = groupCell->convertToWorldSpace(arrayCell[2][4]->getPosition());
					groupHelp->showHelp(pos, 1.0);
				}
				int numSize = arrPoint.size();
				startSoundOpen(numSize);
				for (int i = 0; i < arrPoint.size(); i++) {
					PointGame p = arrPoint.at(i);
					arrayCell[p.x][p.y]->setState(CellDataState::CELL_OPEN, boardData->arrayData[p.x][p.y], i * 0.02);
					boardData->setCell(p.x, p.y, CellDataState::CELL_OPEN);
					if (boardData->arrayData[p.x][p.y] == -1) {
                        effectEndGame(p);
						return;
					}
				}
				if (boardData->checkWin()) {
					//GUIManager::getInstance().guiDialog->showGUI("Win Game", okWinGame, true);
                    saveHighscore();
					endGame();
					clearData();
				}
				else {
					saveData();
				}
			}
			else {
				GameSound::playError();
				arrPoint = boardData->getDataNotiFromPoint(PointGame(row, column));
				for (int i = 0; i < arrPoint.size(); i++) {
					PointGame p = arrPoint.at(i);
					arrayCell[p.x][p.y]->effectNoti();
				}
			}
		}
		else {
			if (isMoving) {
				if (isContinueMove) {
					// move and slide
					groupCell->runAction(
						Sequence::create(
							EaseSineOut::create(MoveBy::create(0.5, Vec2(lastMoveX, lastMoveY))),
							CallFunc::create(AX_CALLBACK_0(GUIBomb::checkBound, this)),
							NULL
						)
					);
				}
				else {
					checkBound();
				}
			}
		}
	}
	timeTouch = -1;
	isMoving = false;
	changeListTouch(pTouch, ChangeTouch::TOUCH_REMOVE);
	BaseGUI::onTouchEnded(pTouch, pEvent);
}


bool GUIBomb::isTouchMove(Touch* touch)
{
	if (arrTouch.at(0).getID() == touch->getID()) {
		return true;
	}
	return false;
}

void GUIBomb::checkBound()
{
	float boundWidth = 100;
	float boundHeightTop = bgMenu->getContentSize().height;
	float boundHeightBottom = boundHeightTop + bgAds->getContentSize().height - bgMenu->getContentSize().height;
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Size sizeGroup = Size(groupCell->getContentSize().width * groupCell->getScale(), groupCell->getContentSize().height * groupCell->getScale());
	float targetPosX = groupCell->getPositionX(), targetPosY = groupCell->getPositionY();
	if (groupCell->getPositionX() - sizeGroup.width * 0.5 > boundWidth && groupCell->getPositionX() + sizeGroup.width * 0.5 > size.width) {
		targetPosX = boundWidth + sizeGroup.width * 0.5;
		if (targetPosX + sizeGroup.width * 0.5 < size.width - boundWidth) {
			targetPosX = size.width - boundWidth - sizeGroup.width * 0.5;
		}
	}
	else if (groupCell->getPositionX() + sizeGroup.width * 0.5 < size.width - boundWidth && groupCell->getPositionX() - sizeGroup.width * 0.5 < 0) {
		targetPosX = size.width - boundWidth - sizeGroup.width * 0.5;
		if (targetPosX - sizeGroup.width * 0.5 > boundWidth)
			targetPosX = boundWidth + sizeGroup.width * 0.5;
	}
	if (groupCell->getPositionY() - sizeGroup.height * 0.5 > boundHeightBottom && groupCell->getPositionY() + sizeGroup.height * 0.5 > size.height - boundHeightTop) {
		targetPosY = boundHeightBottom + sizeGroup.height * 0.5;
		if (targetPosY + sizeGroup.height * 0.5 < size.height - boundHeightTop) {
			targetPosY = size.height - boundHeightTop - sizeGroup.height * 0.5;
		}
	}
	else if (groupCell->getPositionY() + sizeGroup.height * 0.5 < size.height - boundHeightTop && groupCell->getPositionY() - sizeGroup.height * 0.5 < boundHeightBottom) {
		targetPosY = size.height - boundHeightTop - sizeGroup.height * 0.5;
		if (targetPosY - sizeGroup.height * 0.5 > boundHeightBottom) {
			targetPosY = boundHeightBottom + sizeGroup.height * 0.5;
		}
	}
	groupCell->runAction(EaseSineOut::create(MoveTo::create(0.5, Vec2(targetPosX, targetPosY))));
}

void GUIBomb::effectVibrate()
{
	if (numVibrate >= 8)
		return;
	Vec2 pos = Vec2(saveGroupCellPos.x + 10 - AXRANDOM_0_1() * 20, saveGroupCellPos.y + 10 - AXRANDOM_0_1() * 20);
	if (numVibrate == 7)
		pos = saveGroupCellPos;
	groupCell->runAction(
		Sequence::create(
			MoveTo::create(0.05, pos),
			CallFunc::create(AX_CALLBACK_0(GUIBomb::effectVibrate, this)),
			NULL
		)
	);
	numVibrate++;
}


void GUIBomb::effectVibrateSmall()
{
    if (numVibrate >= 20)
        return;
    Vec2 pos = Vec2(saveGroupCellPos.x + 5 - AXRANDOM_0_1() * 10, saveGroupCellPos.y + 5 - AXRANDOM_0_1() * 10);
    if (numVibrate == 20)
        pos = saveGroupCellPos;
    groupCell->runAction(Sequence::create(MoveTo::create(0.05, pos),
                                          CallFunc::create(AX_CALLBACK_0(GUIBomb::effectVibrateSmall, this)), NULL));
    numVibrate++;
}

void GUIBomb::startSoundOpen(int count)
{
	countOpen = 0;
	if (count < 3) {
		maxSoundOpen = count;
	}
	else if (count < 6) {
		maxSoundOpen = 4;
	}
	else if (count < 15) {
		maxSoundOpen = 5;
	}
	else {
		maxSoundOpen = 6;
	}
	playSoundOpen();
}

void GUIBomb::playSoundOpen()
{
	if (countOpen >= maxSoundOpen)
		return;
	GameSound::playOpenCell();
	runAction(
		Sequence::create(
			DelayTime::create(0.1),
			CallFunc::create(AX_CALLBACK_0(GUIBomb::playSoundOpen, this)),
			NULL
		)
	);
	countOpen++;
}

void GUIBomb::scaleToFitScreen(float delayTime)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

    Size sizeGroupCell = getSizeGroupCell();
	float scaleX = size.width / sizeGroupCell.width;
    float scaleY       = heightView / sizeGroupCell.height;
	float scale = scaleX < scaleY ? scaleX : scaleY;
	if (delayTime == 0)
		groupCell->setScale(scale);
	else
		groupCell->runAction(
			Sequence::create(
				DelayTime::create(delayTime),
				Spawn::create(
					EaseSineOut::create(ScaleTo::create(0.5, scale)),
					EaseSineOut::create(MoveTo::create(0.5, posCenter)),
					NULL
				),
				NULL
			)
		);
}

void GUIBomb::saveData()
{
	if (gameState != BOMB_GAME_PLAY) {
		UserDefault::getInstance()->setIntegerForKey("currentTime", 0);
		UserDefault::getInstance()->flush();
		return;
	}
	AXLOGD("Save Data %f ", timeGame);
	int time = ceil(timeGame);
	UserDefault::getInstance()->setIntegerForKey("currentTime", time);
	UserDefault::getInstance()->setIntegerForKey("currentMode", boardData->level);
	string s1 = "", s2 = "", add = "";
	for (int i = 0; i < SIZE_BOARD; i++)
		for (int j = 0; j < SIZE_BOARD; j++)
		{
			switch (boardData->arrayCell[i][j])
			{
			case CellDataState::CELL_BOMB_GUESS:
				add = "2";
				break;
			case CellDataState::CELL_NOT_OPEN:
				add = "0";
				break;
			case CellDataState::CELL_OPEN:
				add = "1";
				break;
			default:
				add = "0";
				break;
			}
			if (i == 0 && j == 0)
			{
				s1 = s1 + GameUtility::toString(boardData->arrayBomb[i][j]);
				
				s2 = s2 + add;
			}
			else
			{
				s1 = s1 + "," + GameUtility::toString(boardData->arrayBomb[i][j]);
				s2 = s2 + "," + add;
			}
		}
	UserDefault::getInstance()->setStringForKey("arrCell", s2);
	UserDefault::getInstance()->setStringForKey("arrBomb", s1);
	UserDefault::getInstance()->flush();
}

void GUIBomb::clearData()
{
	UserDefault::getInstance()->setIntegerForKey("currentTime", 0);
	UserDefault::getInstance()->flush();
}

void GUIBomb::saveHighscore() {
    string convert = GameUtility::convertToTime(timeGame);
    if (game->arrBestTime[boardData->level] == 0 || timeGame < game->arrBestTime[boardData->level])
    {
        if (game->showHelpBomb == false)
        {
            UserDefault::getInstance()->setIntegerForKey(("bestTime" + to_string(boardData->level)).c_str(), timeGame);
            UserDefault::getInstance()->flush();
            game->arrBestTime[boardData->level] = timeGame;
            lbEndGame->setString("New Best Time: " + convert + ". Click here to contine >>>>>>");
            lbTimeBest->setString(convert);
        }
        else
        {
            lbEndGame->setString("Finish Tutorial. New Game ->>>>>>");
        }
        // showDialogWinGame();
        // GameSound::playFirework();
    }
    else
    {
        lbEndGame->setString("Your Time: " + convert + ". New Game ->>>>>>");
    }
}

Vec2 GUIBomb::getPosCell(int row, int column)
{
	return groupCell->convertToWorldSpace(arrayCell[row][column]->getPosition());
}

bool GUIBomb::isPlaying()
{
	return gameState == BOMB_GAME_PLAY;
}

void GUIBomb::initAds()
{
	
}
