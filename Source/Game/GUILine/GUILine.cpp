#include "GUILine.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "Game/Data/GlobalData.h"

#include <DragonBones/CCFactory.h>
#include <spine/spine-cocos2dx.h>
#include <Game/Utility/JNIUtils.h>
#include <Game/Utility/GameUtility.h>
#include <Game/Utility/GameSound.h>
#include "Engine/GUI/ParticleEffect.h"
#include <Engine/Utility/LocalizedString.h>
#include <Game/Utility/Toast.h>

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3
#define BTN_BALL_ID  4
#define BTN_NEW_GAME_ID  5
#define BTN_CLASSIC_ID 6
#define BTN_TOP_ID 7
#define BTN_BOARD_ID       8
#define BTN_BG_ID     9
#define BTN_RESIZE_ID   10
std::string GUILine::className = "GUILine";
GUILine::GUILine(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	//setKeypadEnabled(true);
}

GUILine::~GUILine(void)
{
}

void GUILine::initGUI(){
    BaseGUI::initGUI();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    callBackSplash();
    //runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create(AX_CALLBACK_0(GUILine::callBackSplash, this)), NULL));
}


void GUILine::update(float delta) {
    //manager->update();
    if (currentScore != game->saveScore)
    {
        currentScore = currentScore + deltaScore;
        if ((game->saveScore - currentScore) * deltaScore < 0)
        {
            currentScore = game->saveScore;
        }
        updateScore();
    }
    for (int i = 0; i < arrayImageEffect.size(); i++)
    {
        if (arrayImageEffect.at(i)->isVisible())
        {
            arrayImageEffect.at(i)->updateCoin(game->deltaTime);
        }
    }

}

void GUILine::callBackSplash()
{
    Size size             = Director::getInstance()->getRenderView()->getVisibleSize();
    background = addImage("bg.jpg");
    background->setWidth(size.width);
    background->setHeight(size.height);
    background->setPos(size.width * 0.5f, size.height * 0.5f);
    //background->setVisible(false);

    initMenu();
    
    initBoard();
    
    initBall();
    initLabel();
    board = new BoardData();
}

void GUILine::initMenu() {
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();

    btnBack = addButton(BTN_BACK_ID, "btnBack.png", new BubbleBehavior(), NULL, false);
    btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);
    if (size.width / size.height < 11.0 / 20.0)
    {
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.5f);
    }
    else
    {
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);
    }

    btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
    btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.05f, btnBack->getPositionY());
    if (game->music)
    {
        btnSound->normalImage->setImage("btnSoundOn.png");
    }
    else
    {
        btnSound->normalImage->setImage("btnSoundOff.png");
    }

    btnTrophy = addButton(BTN_TOP_ID, "btnTop.png", new BubbleBehavior(), NULL, false);
    btnTrophy->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.05, btnBack->getPositionY());
   // btnTrophy->setVisible(false);

    btnUndo = addButton(BTN_UNDO_ID, "btnUndo.png", new BubbleBehavior(), NULL, false);
    btnUndo->setPosition(btnTrophy->getPositionX() - btnTrophy->getWidth() * 1.05, btnBack->getPositionY());

    //btnTrophy->setVisible(false);
    btnNewGame = addButton(BTN_NEW_GAME_ID, "btnNewGameSmall.png", new BubbleBehavior(), NULL, false);
    btnNewGame->setPosition(size.width * 0.5, btnBack->getPositionY() - btnNewGame->getHeight() * 1.5);
   // btnNewGame->setPosition(btnClassic->getPositionX(), btnClassic->getPositionY());

    groupBest = new CommonResultGroup();
    addChild(groupBest, 100);
    groupBest->setPosition(size.width * 0.5, size.height * 0.55);
}

void GUILine::initBoard() {
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    bgBoard = Sprite::create("GuiGame/Line/board.png");
    addChild(bgBoard);
    bgBoard->setPosition(size.width * 0.5, size.height * 0.5);

    float sX  = bgBoard->getContentSize().width * 0.04;
    float sY  = bgBoard->getContentSize().height * 0.01;
    float pad = 71;
    updateBoard();
}

void GUILine::updateBoard()
{
    Size size         = Director::getInstance()->getRenderView()->getVisibleSize();
    float heightBoard = 0;
    widthBoard  = 0;
    float scale       = size.width * 0.95 / bgBoard->getContentSize().width;
   // scale             = 1.3;
    startY            = btnNewGame->getPositionY() - btnNewGame->getHeight() * 1.1 -
             bgBoard->getContentSize().height * scale;
   // startY      = size.height * 0.2;
    heightBoard       = bgBoard->getContentSize().height * scale;
   if (startY < size.height * 0.15)
    {
        heightBoard = btnNewGame->getPositionY() - btnNewGame->getHeight() * 0.8 - size.height * 0.15;
        scale       = heightBoard / bgBoard->getContentSize().height;
        startY      = size.height * 0.15;
    }
    bgBoard->setScale(scale);
    bgBoard->setPosition(size.width * 0.5, startY + heightBoard * 0.5);
    widthBoard = bgBoard->getContentSize().width * scale;

    float viewBoard = widthBoard * 0.92;
    startX          = bgBoard->getPositionX() - widthBoard * 0.495f;
    startY          = bgBoard->getPositionY() - heightBoard * 0.495f;
    sizeCell        = widthBoard * 0.99f * (1 / 9.0f);

    Scale9Sprite* bgLayer = Scale9Sprite::create("bgDark.png");
    addChild(bgLayer);
    bgLayer->setContentSize(Size(viewBoard, viewBoard));
    bgLayer->setPosition(startX + bgLayer->getContentSize().width * 0.5,
                         startY + bgLayer->getContentSize().height * 0.5);
    bgLayer->setVisible(false);

     iconHand = addImage("iconHand.png", 0, 0, 0, false);
     iconHand->setAnchorPoint(Vec2(-0.4, 0.4));
     iconHand->setVisible(false);
     iconHand->setLocalZOrder(10);
}

void GUILine::initBall() {
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            Sprite* sprite = Sprite::create("GuiGame/shadowBall.png");
            addChild(sprite);
            sprite->setOpacity(100);
            arrayShadow[i][j] = sprite;

            Sprite* sprite1 = Sprite::create("GuiGame/iconBomb.png");
            addChild(sprite1);
            sprite1->setVisible(false);
            sprite1->setScale(0.3);
            sprite1->setOpacity(255);
            arrayBomb[i][j] = sprite1;

            arrayBall[i][j]            = new BallAnimationNew(GameUtility::getResourceBall(1).c_str(), false);
            arrayBall[i][j]->nameImage = GameUtility::getResourceBall(1);
            addImage(arrayBall[i][j]);
            arrayBall[i][j]->setWidth(sizeCell * game->scaleBall);
            arrayBall[i][j]->setHeight(sizeCell * game->scaleBall);
            arrayBall[i][j]->rootScaleX = arrayBall[i][j]->getScaleX();
            arrayBall[i][j]->rootScaleY = arrayBall[i][j]->getScaleY();
            arrayBall[i][j]->setPos(sizeCell * (j + 0.5f) + startX, startY + sizeCell * (i + 0.5f));
            sprite->setPosition(arrayBall[i][j]->getPosition());
            sprite->setScale(sizeCell * 1.1 / sprite->getContentSize().width);
            arrayBall[i][j]->shadow = sprite;

            arrayBomb[i][j]->setPosition(arrayBall[i][j]->getPosition().x + 25, arrayBall[i][j]->getPosition().y + 25);
        }

     _streak = MotionStreak::create(0.15f, 5.0f, 40, Color3B(255, 255, 255), "GuiGame/" + GameUtility::getResourceBall(1));
    Texture2D* texture = _director->getTextureCache()->addImage("GuiGame/" + GameUtility::getResourceBall(1));
    _streak->setTexture(texture);
    addChild(_streak);
    _streak->setPosition(100, 100);
    //_streak->setLocalZOrder(2);
    _streak->setVisible(false);
    
    ballMove = addImage(GameUtility::getResourceBall(1).c_str(), 0, 0, 0, false);
    ballMove->setLocalZOrder(2);
    ballMove->setVisible(false);

    for (int i = 0; i < 3; i++)
    {
        arrayNext[i] = new GameImage(GameUtility::getResourceBall(1).c_str());
        bgBoard->addChild(arrayNext[i]);
        arrayNext[i]->setVisible(false);
        arrayNext[i]->setWidth(bgBoard->getContentSize().width * 0.075f);
        arrayNext[i]->setHeight(arrayNext[i]->getRealWidth());
        if (i == 0)
        {
            arrayNext[i]->setPos(bgBoard->getContentSize().width * 0.5 - arrayNext[i]->getRealWidth() * 1.1f,
                                 bgBoard->getContentSize().height * 0.95f);
        }
        else
        {
            arrayNext[i]->setPos(arrayNext[i - 1]->getPositionX() + arrayNext[i - 1]->getRealWidth() * 1.1f,
                                 arrayNext[0]->getPositionY());
        }
    }

    

    layerDark = LayerColor::create(Color4B(0, 0, 0, 150));
    addChild(layerDark, 3);
    layerDark->setContentSize(Vec2(size.width, size.height));
   // layerDark->setPosition(Vec2(size.width * 0.5, size.height * 0.5));

    imgNewBest = Sprite::create("GuiGame/best.png");
    addChild(imgNewBest);
    imgNewBest->setLocalZOrder(3);
    imgNewBest->setVisible(false);

    scoreGroup = new ScoreGroup(0);
    bgBoard->addChild(scoreGroup);
    scoreGroup->setPositionX(bgBoard->getContentSize().width * 0.01f);
    scoreGroup->setPositionY(bgBoard->getContentSize().height * 0.9f);

    highscoreGroup = new ScoreGroup(0);
    bgBoard->addChild(highscoreGroup);
    highscoreGroup->setPositionX(bgBoard->getContentSize().width * 0.99f - highscoreGroup->getContentSize().width);
    highscoreGroup->setPositionY(scoreGroup->getPositionY());
    highscoreGroup->setMoney(game->highscore);

    bgEffect = Sprite::create("GuiGame/bgEffect.png");
    bgBoard->addChild(bgEffect);
    bgEffect->setPosition(arrayNext[1]->getPosition());
    bgEffect->setColor(Color3B(247, 239, 150));
    bgEffect->setVisible(false);

    imgCombo = Sprite::create("GuiGame/effect_1.png");
    bgBoard->addChild(imgCombo, 10);
    imgCombo->setPosition(bgEffect->getPosition());
    imgCombo->setVisible(false);

    lbRemove = Text::create("15 balls to remove", "fonts/tahomabd.ttf", 33);
    addChild(lbRemove);
    lbRemove->setColor(Color3B(172, 232, 251));
    lbRemove->enableOutline(Color4B(115, 37, 31, 255), 2);
    lbRemove->setPosition(Vec2(btnNewGame->getPositionX(), btnNewGame->getPositionY()));
    lbRemove->setVisible(false);
    lbRemove->setTextHorizontalAlignment(TextHAlignment::CENTER);
    lbRemove->setAnchorPoint(Vec2(0.5, 0.5));
}

void GUILine::initLabel() {
    labelAddScore = ui::Text::create("20", "fonts/tahomabd.ttf", 110);
    bgBoard->addChild(labelAddScore, 45);
    labelAddScore->setColor(Color3B(2, 134, 246));
    labelAddScore->enableOutline(Color4B(23, 107, 100, 255), 2);
    
}

bool GUILine::onTouchBegan(Touch* pTouch, Event* pEvent) {
    AXLOGD("Touch Event 1");
    Vec2 point = pTouch->getLocation();

    if (point.y < startY)
        return BaseGUI::onTouchBegan(pTouch, pEvent);
    AXLOGD("Touch Event 2");
    int row    = (int)((point.y - startY) / sizeCell);
    int column = (int)((point.x - startX) / sizeCell);
    if (row < 0 || column < 0 || row >= 9 || column >= 9 ||
        (gameState != GameState::NORMAL_GAME && gameState != GameState::PLAY && gameState != GameState::TOUCH &&
         gameState != GameState::CHOOSE_REMOVE))
        return BaseGUI::onTouchBegan(pTouch, pEvent);
    AXLOGD("Touch Event 3");
    showScaleBall(false);
    hideSetting();
    if (board->arrayBall[row][column] >= 1 && board->arrayBall[row][column] <= 7)
    {
        if (gameState == GameState::CHOOSE_REMOVE)
        {
            removeBall(row, column);
            return false;
        }
        if (arrayBall[row][column]->state == BallState::JUMP)
        {
            arrayBall[row][column]->setState(BallState::NORMAL);
            gameState  = GameState::PLAY;
            currentRow = -1;
        }
        else
        {
            if (currentRow >= 0)
                arrayBall[currentRow][currentColumn]->setState(BallState::NORMAL);
            arrayBall[row][column]->setState(BallState::JUMP);
            board->updatePoint(column, row);
            gameState     = GameState::TOUCH;
            currentRow    = row;
            currentColumn = column;

            if (iconHand->isVisible())
            {
                if (row == 3 && column == 1)
                {
                    showHand(this->arrayBall[4][3]->getPosition());
                    string content = CCLocalizedString("TUTORIAL_4");
                    Toast::makeToast(3, content.c_str());
                }
            }
        }
        GameSound::playChooseBall();
    }
    else
    {
        if (gameState == GameState::TOUCH)
        {
            iconHand->setVisible(false);
            board->setWay(row, column);
            if (board->arrayPoint.size() > 0)
            {
                gameState = GameState::MOVE;
                SPEED     = 100 / board->arrayPoint.size();
                ballMove->setVisible(true);
                int id = board->arrayBall[currentRow][currentColumn] - 1;
                if (id < 0 || id > 6)
                {
                    if (currentRow >= 0 && currentRow <= 8 && currentColumn >= 0 && currentColumn <= 8)
                        arrayBall[currentRow][currentColumn]->setState(BallState::NORMAL);
                    gameState  = GameState::PLAY;
                    currentRow = -1;
                    return BaseGUI::onTouchBegan(pTouch, pEvent);
                }
                string s = GameUtility::getResourceBall(board->arrayBall[currentRow][currentColumn]);
                ballMove->setImage(s.c_str(), false);
                ballMove->setWidth(sizeCell * game->scaleBall);
                ballMove->setHeight(sizeCell * game->scaleBall);
                ballMove->setPositionX(arrayBall[currentRow][currentColumn]->getPositionX());
                ballMove->setPositionY(arrayBall[currentRow][currentColumn]->getPositionY());
                // ballMove->setVisible(false);

                _streak->reset();
                Texture2D* texture = _director->getTextureCache()->addImage("GuiGame/" + s);
                _streak->setTexture(texture);
                _streak->setVisible(true);
                _streak->setPosition(ballMove->getPosition());
                GameSound::playMove();

                // luu lai mang gia tri
                for (int i = 0; i < 9; i++)
                    for (int j = 0; j < 9; j++)
                    {
                        saveBall[i][j] = board->arrayBall[i][j];
                    }
                SPEED = 0.1f / board->arrayPoint.size();
                doMoveBall();
                game->isPlaying = true;
               
                arrayBall[currentRow][currentColumn]->setIdBall(-1);

                int saveValue = board->arrayBall[currentRow][currentColumn];
                saveValue2    = board->arrayBall[row][column];
                board->updateValue(currentRow, currentColumn, -1);

                board->updateValue(row, column, saveValue);

                arrayOldBall[currentRow][currentColumn] = -1;
                arrayOldBall[row][column]               = board->arrayBall[currentRow][currentColumn];
                currentRow                              = -1;

                nextRow    = row;
                nextColumn = column;
            }
            else
            {
                JNIUtils::vibrate(5);
                GameSound::playFail();
                // this->stopAllActions();
                // this->runAction(Sequence::create(RotateTo::create(0.1, 1), RotateTo::create(0.1, 0), NULL));
                for (int i = 0; i < 9; i++)
                    for (int j = 0; j < 9; j++)
                    {
                        if (board->arrayBall[i][j] >= 0 && board->arrayBall[i][j] < 8)
                        {
                            arrayBall[i][j]->effectVibrate();
                        }
                    }
            }
        }
    }
    return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUILine::effectOpen()
{
    moveEffect(btnNewGame->normalImage, 0, 500, 0.0);
    moveEffect(btnBack->normalImage, 0, 500, 0.2);
    moveEffect(btnSound->normalImage, 0, 500, 0.25);
    moveEffect(btnUndo->normalImage, 0, 500, 0.35);

    moveEffect(btnTrophy->normalImage, 0, 500, 0.45);

    bgBoard->setOpacity(0);
    bgBoard->runAction(FadeIn::create(0.4));
}

void GUILine::showGui()
{
 //   btnBall->normalImage->setImage(GameUtility::getResourceBall(1).c_str());
    effectOpen();
    newGame();
}

void GUILine::newGame()
{
    lbRemove->setVisible(false);
    btnNewGame->setVisible(true);
    groupBest->setVisible(false);
    iconHand->setVisible(false);
    bgEffect->setVisible(false);
    imgCombo->setVisible(false);
    isDev = false;
    countDev = 0;
    layerDark->setVisible(false);
    labelAddScore->setVisible(false);
    for (int i = 0; i < arrayEffectBall.size(); i++)
    {
        arrayEffectBall.at(i)->setVisible(false);
    }
  //  game->isPlaying = false;
    score           = 0;
    highscore       = game->highscore;
    highscoreGroup->setMoney(game->highscore);
    currentScore    = 0;
    if (game->isPlaying)
    {
        board->loadGame();
        int addScore = game->saveScore;
        game->saveScore = 0;
        this->addScore(addScore);
        //  btnNewGame->setVisible(false);
        if (game->showNewGame && idAdsFull != 3)
        {
            showNewGame();
        }
    }
    else
    {
        game->saveScore = 0;
       // game->highscore = 0;
        if (game->highscore > 0 || true)
            board->newGame();
        else
        {
            showHand(arrayBall[3][1]->getPosition());
            board->newGameTutorial();
            string content = CCLocalizedString("TUTORIAL_1");
            Toast::makeToast(3, content.c_str());
        }
        addScore(0);
        
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arrayOldBall[i][j] = -1;
            arrayBall[i][j]->setIdBall(-1);
            arrayShadow[i][j]->setVisible(false);
        }
    }
    updateNextBall();
    updateViewBall();
    gameState = GameState::PLAY;
    canUndo   = false;
    btnUndo->setEnable(canUndo);
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        string s = "";
        for (int j = 0; j < 9; j++)
        {
            
            saveBall[i][j]     = board->arrayBall[i][j];
            // s = s + " " + GameUtility::toString(board->arrayBall[i][j]);
            if (board->arrayBall[i][j] > 0)
            {
                arrayBall[i][j]->animationNewGame();
                count++;
            }
        }
    }
    for (int i = 0; i < arrayImageEffect.size(); i++)
    {
        arrayImageEffect.at(i)->setVisible(false);
    }
    GameSound::playStartGame();
}


void GUILine::genBall(int i, int j)
{
    if (i < 0 || i > 8 || j < 0 || j > 8)
        return;
    int id = ((board->arrayBall[i][j] - 1) % 7);

    if (id < 0 || id >= 7)
        return;

    string s = GameUtility::getResourceBall(id + 1);
    arrayBall[i][j]->setImage(s.c_str());
    arrayBall[i][j]->setVisible(true);
    if (board->arrayBall[i][j] > 7)
    {
        arrayBall[i][j]->setState(BallState::SMALL);
    }
    else
    {
        arrayBall[i][j]->setState(BallState::NORMAL);
    }
}

void GUILine::updateViewBall()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (board->arrayBall[i][j] > 0 && board->arrayBall[i][j] != arrayOldBall[i][j])
            {
                //genBall(i, j);
                arrayBall[i][j]->setIdBall(board->arrayBall[i][j]);
                arrayOldBall[i][j] = board->arrayBall[i][j];
                //arrayShadow[i][i]->setVisible(true);
            }
            else if (board->arrayBall[i][j] <= 0)
            {
                arrayBall[i][j]->setVisible(false);
                arrayShadow[i][i]->setVisible(false);
            }
        }
}

void GUILine::updateNextBall()
{
    int count = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (board->arrayBall[i][j] >= 8)
            {
                string s = "count " + GameUtility::toString(count) + " id " +
                           GameUtility::toString(board->arrayBall[i][j] - 7) + " resource " +
                           GameUtility::getResourceBall(board->arrayBall[i][j] - 7);

                arrayNext[count]->setImage(GameUtility::getResourceBall(board->arrayBall[i][j] - 7).c_str(), false);
               // arrayNext[count]->setWidth(sizeCell * 0.75f);
               // arrayNext[count]->setHeight(sizeCell * 0.75f);
                arrayNext[count]->setVisible(true);
                count++;
            }
        }

    for (int i = count; i < 3; i++)
    {
        arrayNext[i]->setVisible(false);
    }
}


void GUILine::addScore(int _score)
{
    game->saveScore = game->saveScore + _score;
    deltaScore      = (game->saveScore - currentScore) / 10.0f;
    updateScore();
    UserDefault::getInstance()->setIntegerForKey("saveScore", game->saveScore);
    if (game->saveScore > game->highscore)
    {
        game->highscore = game->saveScore;
        UserDefault::getInstance()->setIntegerForKey("highscore", game->highscore);
       // showNewBest();
    }
    UserDefault::getInstance()->flush();
}

void GUILine::updateScore()
{
    int oldScore = score;
    score        = (int)currentScore;
    scoreGroup->setMoney(score);
    scoreGroup->stopAllActions();
    scoreGroup->setScale(1);
    scoreGroup->runAction(Sequence::create(ScaleTo::create(0.05, 1.15), ScaleTo::create(0.05, 1), NULL));

    if (score > highscore)
    {
        highscore = score;
        highscoreGroup->setMoney(score);
    }
}


void GUILine::undo()
{
    board->loadGame(saveBall);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            arrayOldBall[i][j] = -1;
        }
    updateNextBall();
    updateViewBall();

    addScore(oldScore - game->saveScore);
}

void GUILine::onFinish()
{
    // TODO Auto-generated method stub
    if (valueSaveBall >= 8)
    {
        int row    = positionSaveBall / 9;
        int column = positionSaveBall % 9;
        board->updateValue(row, column,
                                                             valueSaveBall);
        updateNextBall();
        updateViewBall();
    }
}

void GUILine::doMoveBall()
{

    if (board->arrayPoint.size() > 0)
    {
        int nextRow    = board->arrayPoint.at(board->arrayPoint.size() - 1)->y;
        int nextColumn = board->arrayPoint.at(board->arrayPoint.size() - 1)->x;
        board->arrayPoint.erase(board->arrayPoint.begin() + board->arrayPoint.size() - 1);

        ballMove->cleanup();
        Vec2 p = arrayBall[nextRow][nextColumn]->getPosition();
        _streak->runAction(Sequence::create(MoveTo::create(SPEED, p), NULL));
        ballMove->runAction(Sequence::create(MoveTo::create(SPEED, p),
                                             CallFunc::create(AX_CALLBACK_0(GUILine::doMoveBall, this)), NULL));

        // for (int i = 0; i < 4; i++) {
        //	//arrayMoveBall[i]->setVisible(false);
        //	arrayMoveBall[i]->runAction(Sequence::create(
        //		DelayTime::create(0.02 * i),
        //		Show::create(),
        //		MoveTo::create(SPEED, p),
        //		NULL
        //	));
        // }
    }
    else
    {
        ballMove->setVisible(false);
        genBall(nextRow, nextColumn);
        checkAfterMove();
        /*for (int i = 0; i < 4; i++) {
                arrayMoveBall[i]->setVisible(false);
        }*/
    }
}

void GUILine::checkAfterMove()
{
    // check xem co kha nang an quan ko, neu co thi ko lam bong
    // lon len
    arrayChange.clear();
    arrayChange.push_back(new PointGame(nextColumn, nextRow));
    checkGenNextBall();
    if (saveValue2 >= 8)
    {
        // thay the vi tri bong nho sang cho khac
        if (genNext)
        {
            board->randomReplace(saveValue2);
            updateViewBall();
            valueSaveBall = 0;
        }
        else
        {
            valueSaveBall    = saveValue2;
            positionSaveBall = nextRow * 9 + nextColumn;
        }
    }
    else
    {
        valueSaveBall = 0;
    }
    if (genNext)
    {
        makeBiggerBall();
        this->runAction(Sequence::create(DelayTime::create(0.16f),
                                         CallFunc::create(AX_CALLBACK_0(GUILine::checkAfterMove2, this)), NULL));
    }
    else
    {
        checkAfterMove2();
    }
    canUndo = true;
    btnUndo->setEnable(canUndo);
}

void GUILine::checkAfterMove2()
{
    
    if (genNext)
        board->randomNext();
    
    updateNextBall();
    updateViewBall();
    
    if (gameState == GameState::TOUCH)
    {
        if (currentRow >= 0 && currentColumn >= 0 && board->arrayBall[currentRow][currentColumn] >= 0)
        {
        }
        else
        {
            gameState = GameState::PLAY;
        }
    }
    else
    {
        gameState = GameState::PLAY;
    }

    checkEatPoint();
    checkEndGame();
}

void GUILine::autoBiggerBall()
{
    arrayChange.clear();
    makeBiggerBall();
    this->runAction(Sequence::create(DelayTime::create(0.16f),
                                     CallFunc::create(AX_CALLBACK_0(GUILine::checkAfterMove2, this)), NULL));
    genNext = true;
    canUndo = false;
    btnUndo->setEnable(false);
}


void GUILine::makeBiggerBall()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (board->arrayBall[i][j] >= 8)
            {
                arrayBall[i][j]->setState(BallState::BIGGER);
                board->updateValue(i, j, board->arrayBall[i][j] - 7);
                arrayChange.push_back(new PointGame(j, i));
            }
        }
}


void GUILine::checkEndGame()
{
    if (board->checkEndGame())
    {
        game->isPlaying = false;
        UserDefault::getInstance()->setBoolForKey("isPlayingNormal", false);
       
        UserDefault::getInstance()->flush();
        gameState = GAME_OVER;
        
        canUndo = false;
        btnUndo->setEnable(canUndo);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                arrayBall[i][j]->effectEndGame(0.01 * i * 7 + 0.01 * j);
            }
        }
        if (game->showContinue == 1)
        {
            runAction(Sequence::create(DelayTime::create(1.2),
                                       CallFunc::create(AX_CALLBACK_0(GUILine::callbackEffectEndGame1, this)), NULL));
        }
        else
        {
            
            runAction(Sequence::create(DelayTime::create(1.2),
                                       CallFunc::create(AX_CALLBACK_0(GUILine::callbackEffectEndGame, this)), NULL));
        }
        GameSound::playSoundLose();
    }
   
}

void GUILine::callbackEffectEndGame()
{
    GameSound::playFirework();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            arrayBall[i][j]->setVisible(false);
            effectImage(arrayBall[i][j]);
            /*if (GameUtility::getRandom() > 0.5)
            {
                showParticle(arrayBall[i][j]->getPositionX(), arrayBall[i][j]->getPositionY(), board->arrayBall[i][j],
                             0);
            }*/
        }
    runAction(Sequence::create(DelayTime::create(1.0),
                               CallFunc::create(AX_CALLBACK_0(GUILine::callbackEffectEndGame1, this)), NULL));
}

void GUILine::callbackEffectEndGame1()
{
    GUIManager::getInstance().guiResult->showGUI(score, game->highscore);
   
}

void GUILine::checkGenNextBall()
{
    board->result.clear();
    for (int i = 0; i < arrayChange.size(); i++)
    {
        board->getListBall(arrayChange.at(i)->y, arrayChange.at(i)->x);
    }

    if (board->result.size() < 5)
        genNext = true;
    else
        genNext = false;
}

void GUILine::checkEatPoint()
{
    oldScore = score;
    board->result.clear();
    for (int i = 0; i < arrayChange.size(); i++)
    {
        board->getListBall(arrayChange.at(i)->y, arrayChange.at(i)->x);
    }

    Vec2 posScore;
    int count = 0;
    for (int i = 0; i < board->result.size(); i++)
    {
        arrayBall[board->result.at(i)->y][board->result.at(i)->x]->setState(BallState::DISAPPEAR);
        arrayBall[board->result.at(i)->y][board->result.at(i)->x]->setIdBall(-1);
        showParticle(arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootX,
                     arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootY,
                     arrayOldBall[board->result.at(i)->y][board->result.at(i)->x], count * 0.1);
        count++;
        if (i == 2)
        {
            posScore.x = arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootX;
            posScore.y = arrayBall[board->result.at(i)->y][board->result.at(i)->x]->rootY;
        }
        board->updateValue(board->result.at(i)->y, board->result.at(i)->x, -1);
        arrayOldBall[board->result.at(i)->y][board->result.at(i)->x] = -1;
        if (i == 0)
        {
            arrayBall[board->result.at(i)->y][board->result.at(i)->x]->isAct = true;
        }
        else
        {
            arrayBall[board->result.at(i)->y][board->result.at(i)->x]->isAct = false;
        }
    }
    int addScore   = 0;
    int typeEffect = 0;
    onFinish();
    int numBall = board->result.size();
    if (numBall >= 5)
    {
        effectCombo(numBall);
        switch (board->result.size())
        {
        case 5:
        {
            GameSound::playScore1();
            addScore = 5;
        }

        break;
        case 6:
        {
            GameSound::playScore2();
            addScore   = 12;
            typeEffect = 1;
        }

        break;
        case 7:
        {
            GameSound::playScore3();
            addScore   = 21;
            typeEffect = 2;
        }

        break;
        case 8:
        {
            GameSound::playScore4();
            addScore   = 32;
            typeEffect = 3;
        }

        break;
        case 9:
        {
            GameSound::playScore5();
            addScore   = 45;
            typeEffect = 3;
        }

        break;
        case 10:
        {
            GameSound::playScore6();
            addScore   = 60;
            typeEffect = 3;
        }

        break;
        case 11:
        {
            GameSound::playScore6();
            addScore   = 77;
            typeEffect = 3;
        }

        break;
        case 12:
        {
            GameSound::playScore6();
            addScore   = 96;
            typeEffect = 3;
        }

        break;
        case 13:
        {
            GameSound::playScore6();
            addScore   = 117;
            typeEffect = 3;
        }

        break;
        case 14:
        {
            GameSound::playScore6();
            addScore   = 140;
            typeEffect = 3;
        }

        break;
        default:
            GameSound::playScore6();
            addScore   = 200;
            typeEffect = 3;
            break;
        }
        if (addScore > 0)
        {
            if (typeEffect > 0)
                JNIUtils::vibrate(addScore);
            checkIsNewBest(addScore);
            this->addScore(addScore);
            labelAddScore->setVisible(true);
            labelAddScore->stopAllActions();
            labelAddScore->setOpacity(0);
            labelAddScore->setString(("+" + GameUtility::toString(addScore)).c_str());
            labelAddScore->setPosition(Vec2(scoreGroup->getPositionX() + scoreGroup->getContentSize().width * 0.5,
                                            scoreGroup->getPositionY() + scoreGroup->getContentSize().height * 0.5));
            // labelScore->runAction(Spawn::create(FadeOut::create(0.6),
            // Sequence::create(EaseBackOut::create(MoveBy::create(0.6, ccp(0, 50))), Hide::create(), NULL), NULL));
            labelAddScore->runAction(Sequence::create(DelayTime::create(0.8), FadeIn::create(0.5),
                                                   EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 100))),
                                                   FadeOut::create(0.5), Hide::create(), NULL));
        }
    }
    if (board->checkNoBigBall())
        autoBiggerBall();
    savePreference();
}


void GUILine::checkIsNewBest(int add)
{
    if (isNewBest)
        return;
    if (!isNewBest && game->saveScore <= game->highscore && game->highscore > 0 &&
        game->saveScore + add > game->highscore)
    {
        // show Effect Best Score
        layerDark->setVisible(true);
        layerDark->runAction(
            Sequence::create(
                FadeTo::create(0.5, 150),
                DelayTime::create(1.0),
                FadeOut::create(0.5),
                Hide::create(),
                NULL
            )
        );
        isNewBest = true;
        groupBest->showMauBinh(1);
        //imgNewBest->setVisible(true);
       // showEffectLabel("GuiGame/best.png");
        GameSound::playWin();
       // paperLeft->startEffect();
       // paperRight->startEffect();
    }
}

void GUILine::showEffectLabel(string s)
{
    // Sprite* img = Sprite::create(s.c_str());
    // addChild(img);
    Sprite* img = imgNewBest;
    img->setPosition(bgBoard->getPositionX(), bgBoard->getPositionY() + 100);
    img->setOpacity(0);
    img->setScale(6);
    img->runAction(Sequence::create(EaseBounceOut::create(ScaleTo::create(0.6, 1.5)), DelayTime::create(2.0),
                                    FadeOut::create(0.5), Hide::create(),
                                    //	RemoveSelf::create(),
                                    NULL));
    img->runAction(FadeIn::create(0.5));
}


void GUILine::showParticle(float posX, float posY, int id, float time)
{
    if (id < 1 || id > 7)
        return;
   
    Layer* layer           = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
    ParticleEffect* effect = new ParticleEffect();
    effect->create("ParticlesGame/breakBall.plist", layer);
    string s = "GuiGame/" + GameUtility::getResourceBall(id);
    effect->particle->setTexture(Director::getInstance()->getTextureCache()->addImage(s.c_str()));
    effect->particle->setPosition(posX, posY);
    Size size   = Director::getInstance()->getWinSize();
    float scale = (size.width / DEFAULT_SCREEN_WIDTH) > (size.height / DEFAULT_SCREEN_HEIGHT)
                        ? (size.width / DEFAULT_SCREEN_WIDTH)
                        : (size.height / DEFAULT_SCREEN_HEIGHT);
    effect->particle->setScale(scale);
    effect->particle->setAutoRemoveOnFinish(true);
    effect->particle->setBlendAdditive(false);
}

void GUILine::savePreference()
{
    if (game->isPlaying)
    {
        string s  = "";
        int index = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (i == 0 && j == 0)
                {
                    s = s + GameUtility::toString(board->arrayBall[i][j]);
                }
                else
                {
                    s = s + "," + GameUtility::toString(board->arrayBall[i][j]);
                }
                game->data[i * 9 + j] = board->arrayBall[i][j];
               
            }
        UserDefault::getInstance()->setBoolForKey("isPlaying", true);
        UserDefault::getInstance()->setBoolForKey("isPlayingNormal", true);
        UserDefault::getInstance()->setIntegerForKey("score", score);
        UserDefault::getInstance()->setStringForKey("dataTest", s);
        UserDefault::getInstance()->setStringForKey("dataNormal", s);
    }
    else
    {
        UserDefault::getInstance()->setBoolForKey("isPlaying", false);
        UserDefault::getInstance()->setBoolForKey("isPlayingNormal", false);
    }

    UserDefault::getInstance()->flush();
}

void GUILine::onBackKey()
{
    if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
    {
        game->changeToLandscape();
        UserDefault::getInstance()->setFloatForKey("scaleBall", game->scaleBall);
        UserDefault::getInstance()->setFloatForKey("brightBall", game->brightBall);
        savePreference();
        GUIManager::getInstance().isCallBackPress = true;
        game->showAdsFull();
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
        //game->endGame();
    }
}


void cancelNewGame2() {}

void okNewGame2()
{
    if (game->saveScore > 100)
    {
        JNIUtils::showAdsFull();
    }
    game->isPlaying = false;
    GUIManager::getInstance().guiLine->newGame();
    UserDefault::getInstance()->setBoolForKey("isPlayingNormal", false);
    UserDefault::getInstance()->flush();
}

void GUILine::onButtonRelease(int buttonId, Touch* event)
{
    GameSound::playClick();
    if (buttonId != BTN_RESIZE_ID)
    {
        showScaleBall(false);
    }
    if (buttonId != BTN_BALL_ID)
    {
        hideSetting();
    }
    switch (buttonId)
    {
    case BTN_BACK_ID:
    {
        onBackKey();
    }
    break;
    case BTN_TOP_ID:
    {
       // GUIManager::getInstance().guiResult->showGUI(100, 100);
        JNIUtils::submitScore(0, game->highscore);
        break;
    }
    case BTN_SOUND_ID:
    {
        //GUIManager::getInstance().guiResult->showGUI(10, 100);
        //groupBest->showMauBinh(1);
        game->music = !game->music;
        if (game->music)
        {
            btnSound->normalImage->setImage("btnSoundOn.png");
        }
        else
        {
            btnSound->normalImage->setImage("btnSoundOff.png");
        }

        UserDefault::getInstance()->setBoolForKey("music", game->music);
        UserDefault::getInstance()->flush();
    }
    break;
    case BTN_CLASSIC_ID:
    {
        
        break;
    }
    case BTN_UNDO_ID:
    {
        if (canUndo)
        {
            undo();
            canUndo = false;
            btnUndo->setEnable(canUndo);
            game->showAdsForOldUser(true);
        }
    }
    break;
    case BTN_BOARD_ID:
    {
       
        break;
    }
    case BTN_BG_ID:
    {
       
        break;
    }
    
    case BTN_NEW_GAME_ID:
    {
        showNewGame();
        break;
    }
    case BTN_RESIZE_ID:
    {
        break;
    }
    }
}

void GUILine::effectImage(BallAnimationNew* ball)
{
    ImageEffect* image = NULL;
    for (int i = 0; i < arrayImageEffect.size(); i++)
    {
        if (!arrayImageEffect.at(i)->isVisible())
        {
            image = arrayImageEffect.at(i);
            break;
        }
    }
    if (image == NULL)
    {
        image = ImageEffect::create();
        this->addChild(image, 5);
        arrayImageEffect.push_back(image);
    }
    image->setVisible(true);
    image->setOpacity(255);
    image->setScale(ball->rootScaleX * 1.1);
    image->setTexture("GuiGame/" + ball->nameImage);
    image->initCoin(ImageEffect::TYPE_FLOW, 0, ball->getPositionX(), ball->getPositionY());
}

void GUILine::effectCombo(int count) {
    if (count <= 5)
        return;
    bgEffect->setVisible(true);
    bgEffect->setOpacity(0);
    bgEffect->runAction(
        Sequence::create(
            FadeIn::create(0.5),
            DelayTime::create(1.5),
            FadeOut::create(0.5),
            Hide::create(),
            NULL
        )
    );

    int index = count - 5;
    index     = index > 3 ? 3 : index;
    imgCombo->setTexture("GuiGame/effect_" + to_string(index) + ".png");
    imgCombo->setVisible(true);
    imgCombo->setOpacity(0);
    imgCombo->setPosition(arrayNext[1]->getPosition());
    imgCombo->setScaleX(10);
    imgCombo->runAction(
        Sequence::create(
            Spawn::create(
                FadeIn::create(0.5),
                EaseBackOut::create(ScaleTo::create(0.5, 1)),
                NULL
            ),
            DelayTime::create(1.0),
            Spawn::create(
                FadeOut::create(0.8),
                EaseBackIn::create(MoveBy::create(0.5, Vec2(0, 100))),
                NULL
            ),
            Hide::create(),
            NULL
        )
    );

    Layer* layer           = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
    ParticleEffect* effect = new ParticleEffect();
    effect->create("ParticlesGame/combo1.plist", layer);
    effect->particle->setEmissionRate(40);
    Vec2 pos = bgBoard->convertToWorldSpace(arrayNext[1]->getPosition());
    effect->particle->setPosition(pos);
    Size size   = Director::getInstance()->getWinSize();
    float scale = (size.width / DEFAULT_SCREEN_WIDTH) > (size.height / DEFAULT_SCREEN_HEIGHT)
                      ? (size.width / DEFAULT_SCREEN_WIDTH)
                      : (size.height / DEFAULT_SCREEN_HEIGHT);
    // effect->particle->setScale(scale);
    effect->particle->setAutoRemoveOnFinish(true);
    effect->particle->setBlendAdditive(true);
}

void GUILine::renewGall()
{
    board->renewBall();
    for (int i = 0; i < board->arrRenew.size(); i++)
    {
        int row                = board->arrRenew.at(i) / 9;
        int column             = board->arrRenew.at(i) % 9;
        BallAnimationNew* ball = arrayBall[row][column];
        showParticle(ball->getPositionX(), ball->getPositionY(), arrayOldBall[row][column], 0);
        ball->setVisible(false);
        arrayOldBall[row][column] = board->arrayBall[row][column];
        if (board->arrayBall[row][column] > 0)
            ball->setIdBall(board->arrayBall[row][column]);
    }
    runAction(Sequence::create(DelayTime::create(2.0), CallFunc::create(AX_CALLBACK_0(GUILine::callbackRenew, this)), NULL));
    game->isPlaying = true;
    savePreference();
    gameState = PLAY;
    int add   = -100;
    if (score < 100)
        add = -score;
    addScore(add);
    btnUndo->setEnable(false);
}

void GUILine::callbackRenew()
{
    updateNextBall();
}

void GUILine::showScaleBall(bool show) {
    //btnNewGame->setVisible(!show);
    //btnBall->setVisible(!show);
}

void GUILine::showHand(Vec2 posStart)
{
    iconHand->getImg()->stopAllActions();
    iconHand->setPosition(posStart.x + iconHand->getWidth() * 0.4, posStart.y - iconHand->getHeight() * 0.4);
    iconHand->setVisible(true);
    iconHand->getImg()->setOpacity(0);
    iconHand->getImg()->runAction(FadeIn::create(1.0));
    iconHand->stopAllActions();
    iconHand->runAction(
        RepeatForever::create(
            Sequence::create(
                ScaleTo::create(0.2, 1.1),
                ScaleTo::create(0.2, 1.0),
                NULL
            )
        )
    );
}

void GUILine::updateContentBall() {
    updateNextBall();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (board->arrayBall[i][j] > 0)
            {
                arrayBall[i][j]->idBall = 0;
                arrayBall[i][j]->setIdBall(board->arrayBall[i][j]);
            }
        }
}

void GUILine::hideSetting() {
   
}

void GUILine::showSetting() {
    
  
}

void GUILine::showNewGame() {
    GUIManager::getInstance().guiDialog->showGUI(CCLocalizedString("START_NEW_GAME").c_str(), &okNewGame2, false,
                                                &cancelNewGame2, NULL, NULL);
}

void GUILine::changeToRemoveBall()
{
    numRemove = game->numDestroy;
    gameState = GameState::CHOOSE_REMOVE;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arrayBomb[i][j]->setVisible(true);
        }
    }
    btnNewGame->setVisible(false);
    lbRemove->setVisible(true);
    lbRemove->setString(to_string(numRemove) + " " + CCLocalizedString("BALL_TO_REMOVE"));
    score = game->saveScore;
    updateScore();
}

void GUILine::removeBall(int row, int column)
{
    if (board->arrayBall[row][column] <= 0)
        return;
    arrayBall[row][column]->setVisible(false);
    arrayBomb[row][column]->setVisible(false);
    showParticle(arrayBall[row][column]->getPositionX(), arrayBall[row][column]->getPositionY(),
                 board->arrayBall[row][column], 0);
    board->removeBall(row, column);
    saveBall[row][column] = 0;
    numRemove--;
    lbRemove->setString(to_string(numRemove) + " " + CCLocalizedString("BALL_TO_REMOVE"));
    lbRemove->runAction(Sequence::create(ScaleTo::create(0.1, 1.06), ScaleTo::create(0.1, 1.0), NULL));
    Toast::makeToast(2.0, (to_string(numRemove) + " " + CCLocalizedString("BALL_TO_REMOVE")).c_str());

    GameSound::playChooseBall();
    if (numRemove <= 0)
    {
        gameState = GameState::PLAY;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                arrayBomb[i][j]->setVisible(false);
                game->isPlaying = true;
            }
        }
        btnNewGame->setVisible(true);
        lbRemove->setVisible(false);
        savePreference();
    }
}
