#include "GUIaa.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"
#include "aaConfig.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3


GUIaa::GUIaa(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	setKeypadEnabled(true);
}


GUIaa::~GUIaa(void)
{
}
std::string GUIaa::className = "GUIaa";

void GUIaa::initGUI(){

	Size size   = Director::getInstance()->getRenderView()->getVisibleSize();
    callBackSplash();
}


void okEndGameAa()
{
    game->changeToLandscape();
    GUIManager::getInstance().removeAllGui();
    GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
}
void GUIaa::onBackKey()
{
    if (GUIManager::getInstance().isCallBackPress == false &&
        GUIManager::getInstance().getLastGui() == this)
    {
        GUIManager::getInstance().guiDialog->showGUI("Are you sure you want to quit the game?", &okEndGameAa, false);
        GUIManager::getInstance().isCallBackPress = true;
    }
}

void GUIaa::onButtonRelease(int buttonID, Touch* touch)
{
	switch (buttonID)
	{
	case BTN_BACK_ID:
		{
			GUIManager::getInstance().guiDialog->showGUI("Are you sure you want to quit the game?",&okEndGameAa, false);
		}
		
		break;
	case BTN_SOUND_ID:
		{
			game->music = !game->music;
			if(game->music)
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
	
	default:
		break;
	}
}

void GUIaa::callBackSplash()
{
	BaseGUI::initGUI();
	Size size   = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = addImage("bg1.jpg");
	bg->setWidth(size.width);
	bg->setHeight(size.height);
	bg->setPos(size.width * 0.5f, size.height * 0.5f);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if(game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png");
	}

	labelLevel = Text::create("1", "fonts/tahomabd.ttf", 60);
	labelLevel->setColor(Color3B(0, 0, 0));
	addChild(labelLevel);
	labelLevel->setPosition(Vec2(size.width * 0.5f, btnBack->getPositionY() - 50));
	
	AA_WIDTH_BALL   = size.width * 0.06f;
    AA_ROOT_WIDTH_BALL = WIDTH_BALL;
    AA_ROOT_X          = size.width * 0.5f;
    AA_ROOT_Y          = size.height * 0.6f;
    AA_RADIUS          = size.width * 0.41f;
    for (int i = 0; i < 4; i++)
    {
        arrayBallMove[i] = new BallMove();
        addChild(arrayBallMove[i]);
        arrayBallMove[i]->setPositionX(AA_ROOT_X - AA_WIDTH_BALL * 0.5f);
    }

	complete = addImage("complete.png");
	complete->setLocalZOrder(2);
	complete->setPosition(size.width * 0.5f, size.height * 0.87f);

	next = addImage("next.png");
	next->setPosition(size.width * 0.5f, complete->getPositionY());
    next->setLocalZOrder(2);

	gameover = addImage("gameover.png");
	gameover->setPosition(size.width * 0.5f, complete->getPositionY());
    gameover->setLocalZOrder(2);

	tryAgain = addImage("tryAgain.png");
	tryAgain->setPosition(size.width * 0.5f, complete->getPositionY());
	tryAgain->setLocalZOrder(2);

	complete->setVisible(false);
	next->setVisible(false);
	gameover->setVisible(false);
	tryAgain->setVisible(false);
	countGame = 0;
	level = game->level;

    auto effect = efk::Effect::create("fire.efk", 80.0f);
    if (effect != nullptr)
    {
        effectBreakBall = efk::EffectEmitter::create(game->manager);
        effectBreakBall->setEffect(effect);
        effectBreakBall->setPlayOnEnter(false);
        effectBreakBall->setRemoveOnStop(false);
        effectBreakBall->setSpeed(0.5);
        // emitter->setScale(13);
        //  effectBreakBall->setPosition(clock->getPosition());
        this->addChild(effectBreakBall, 10);
    }
    Scale9Sprite* bgScore = Scale9Sprite::create("GuiGame/bgScoreNormal.png");
    addChild(bgScore);
    bgScore->setContentSize(Size(110, 50));
    bgScore->setPosition(Vec2(bgScore->getContentSize().width * 0.54, btnBack->getPositionY()));

    Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 14);
    bgScore->addChild(lbScore);
    lbScore->enableOutline(Color4B(3, 85, 188, 255), 1);
    lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.75));

    Scale9Sprite* bgBest = Scale9Sprite::create("GuiGame/bgScoreBest.png");
    addChild(bgBest);
    bgBest->setContentSize(bgScore->getContentSize());
    bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.05, bgScore->getPositionY());

    Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 14);
    bgBest->addChild(lbBest);
    lbBest->enableOutline(Color4B(175, 108, 3, 255), 1);
    lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.75));

    labelScore = Text::create("0", "fonts/tahomabd.ttf", 18);
    labelScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelScore->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelScore->enableOutline(Color4B(3, 85, 188, 255), 1);
    bgScore->addChild(labelScore);
    labelScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.3));

    highscore      = UserDefault::getInstance()->getIntegerForKey("highscoreAa", 0);
    labelHighscore = Text::create(GameUtility::standardizeNumber(highscore), "fonts/tahomabd.ttf", 18);
    labelHighscore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelHighscore->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelHighscore->enableOutline(Color4B(175, 108, 3, 255), 1);
    bgBest->addChild(labelHighscore);
    labelHighscore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.3));
	isUpdate = true;

    Sprite* bgCircle = Sprite::create("GuiGame/circle.png");
    addChild(bgCircle);
    bgCircle->setPosition(Vec2(AA_ROOT_X, AA_ROOT_Y));
    bgCircle->setColor(Color3B(222, 196, 143));

    labelLevel->setPosition(bgCircle->getPosition());
    labelLevel->setLocalZOrder(1);
    labelLevel->setColor(Color3B(152, 146, 103));
    labelLevel->enableOutline(Color4B(102, 96, 53, 255), 2);
}

void GUIaa::act(float delta) {
	// TODO Auto-generated method stub
    if (isUpdate != true)
        return;
    if (state == GameState::PLAY)
    {
        for (int i = 0; i < arrayBall.size(); i++)
        {
            arrayBall.at(i)->act(delta);
        }

        arrayBallMove[0]->act1(delta);
    }
}

void GUIaa::makeNew() {
	// TODO Auto-generated method stub
	Size size   = Director::getInstance()->getRenderView()->getVisibleSize();
    GameSound::playHit();
    BallCircle* a = new BallCircle();
    arrayBall.push_back(a);

    addChild(a->bar);
    addChild(a->ball);
    a->setPosition(AA_ROOT_X, AA_ROOT_Y);

    AA_NUM_BALL_MOVE--;
    if (AA_NUM_BALL_MOVE >= 1)
        reArrangeBall();
    else
    {
        finishGame();
    }
    score++;
    labelScore->setString(GameUtility::standardizeNumber(score).c_str());
    if (score > highscore)
    {
        highscore = score;
        labelHighscore->setString(GameUtility::standardizeNumber(highscore).c_str());
        UserDefault::getInstance()->setIntegerForKey("highscoreAa", score);
        UserDefault::getInstance()->flush();
    }
}

void GUIaa::finishGame() {
	state = GameState::END_GAME;
	GameSound::playWin();
	for (int i = 0; i < arrayBall.size(); i++) {
		arrayBall.at(i)->finishGame();

	}

	arrayBallMove[0]->setVisible(false);

	complete->setVisible(true);
	next->setVisible(true);
	complete->getImg()->setOpacity(0);
	next->getImg()->setOpacity(0);
	level++;
	game->level = level;

	//game->savePreference();
	complete->getImg()->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(1.0f), FadeOut::create(0.3f), 
		CallFunc::create(AX_CALLBACK_0(GUIaa::callbackCompleteEndGame, this)), NULL));
	bg->setColor(Color3B(0, 255, 0));

	countGame++;
	if(countGame > 4 + GameUtility::getRandom() * 3)
	{
		countGame = 0;
        game->showAdsFull();
	}
}

void GUIaa::reArrangeBall() {
	cleanup();

    for (int i = 0; i < 3 && i < AA_NUM_BALL_MOVE; i++)
    {
        arrayBallMove[i]->setVisible(true);
        arrayBallMove[i]->setText(AA_NUM_BALL_MOVE - i);
        arrayBallMove[i]->setPosition(AA_ROOT_X - AA_WIDTH_BALL * 0.5f,
                                        AA_ROOT_Y - AA_RADIUS - AA_WIDTH_BALL * (3 + i * 2));
    }

	for (int i = AA_NUM_BALL_MOVE; i < 3; i++) {
		arrayBallMove[i]->setVisible(false);
	}

	arrayBallMove[0]->state = BallMove::StateBall::STOP;

	arrayBallMove[3]->setVisible(false);
}

	
void GUIaa::newGame() {
    effectBreakBall->setVisible(false);
	for (int i = 0; i < arrayBall.size(); i++) {
		arrayBall.at(i)->ball->removeFromParentAndCleanup(true);
		arrayBall.at(i)->bar->removeFromParentAndCleanup(true);
	}
	arrayBall.clear();
	state = PLAY;

    AA_NUM_BALL = ((level - 1) / 3) + 5;
    int type = (level - 1) % 3;

    switch (type)
    {
    case 0:
        AA_TIME_WHEEL = 4;
        AA_NUM_BALL_MOVE = (int)(AA_NUM_BALL * 1.5f);
        break;
    case 1:
        AA_TIME_WHEEL = 4;
        AA_NUM_BALL_MOVE = (int)(AA_NUM_BALL * 1.5f + 2);
        break;
    case 2:
        AA_TIME_WHEEL = 3.7f;
        AA_NUM_BALL_MOVE = (int)(AA_NUM_BALL * 1.5f + 3);
        break;

    default:
        break;
    }

    if (level > 12)
    {
        AA_WIDTH_BALL = AA_ROOT_WIDTH_BALL * (30 + 12.0f) / (30 + level);
        for (int i = 0; i < 4; i++)
        {
            arrayBallMove[i]->setRealWidth(AA_WIDTH_BALL);
        }

        AA_TIME_WHEEL = AA_TIME_WHEEL * (30 + level) / (30 + 12.0f);
    }

    for (int i = 0; i < AA_NUM_BALL; i++)
    {
        BallCircle* a = new BallCircle();
        arrayBall.push_back(a);
        addChild(a->bar);
        addChild(a->ball);
        a->countTime = (AA_TIME_WHEEL * 1.0f / AA_NUM_BALL * 1.0f) * i;
    }

    AA_SPEED_BALL = AA_WIDTH_BALL * 0.5f;
	

	labelLevel->setString((GameUtility::toString(level)).c_str());
	bg->setColor(Color3B(255, 255, 255));
	reArrangeBall();

	if(level == 1)
	{
		Size size   = Director::getInstance()->getRenderView()->getVisibleSize();
        Text* labelLine = Text::create("Touch screen to move number ball, avoid blank ball", "fonts/tahoma.ttf", 20);
		labelLine->setColor(Color3B(200, 200, 200));
		//labelLine->setWidth(size.width * 0.9f);
		this->addChild(labelLine);
		labelLine->setPosition(Vec2(size.width * 0.5f, btnBack->getPositionY() - 50));
		labelLine->runAction(FadeOut::create(4));
        score = 0;
        labelScore->setString("0");
	}
}

void GUIaa::endGame() {
	state = GameState::END_GAME;
	bg->setColor(Color3B(255, 0, 0));
    GameSound::playBomb();

	gameover->setVisible(true);
	tryAgain->setVisible(true);
	gameover->getImg()->setOpacity(0);
	tryAgain->getImg()->setOpacity(0);

	tryAgain->getImg()->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(1.0f), FadeOut::create(0.3f), 
		CallFunc::create(AX_CALLBACK_0(GUIaa::callbackEndGame, this)), NULL));
	countGame++;
    effectBreakBall->setVisible(true);
    effectBreakBall->setPosition(arrayBallMove[0]->getPosition());
    effectBreakBall->play();
}

void GUIaa::callbackEndGame() {
    GUIManager::getInstance().guiResult->showGUI(score, highscore);
}

void GUIaa::onTouchEnded( Touch *pTouch, Event *pEvent )
{
	Size size   = Director::getInstance()->getRenderView()->getVisibleSize();
	if(pTouch->getLocation().y < size.height * 0.9f)
	{
		if(state == PLAY)
		{
			// TODO Auto-generated method stub
			arrayBallMove[0]->state = BallMove::StateBall::MOVE;
			arrayBallMove[3]->setVisible(true);
			if (AA_NUM_BALL_MOVE > 3) {
				arrayBallMove[3]->setText(AA_NUM_BALL_MOVE - 3);
				arrayBallMove[3]->setPositionY(arrayBallMove[2]->getPositionY() - AA_WIDTH_BALL * 2);
			}
			for (int i = 1; i < 4 && i < AA_NUM_BALL_MOVE; i++) {
				arrayBallMove[i]->setVisible(true);
				arrayBallMove[i]->runAction(MoveTo::create(0.1f, Vec2(arrayBallMove[i]->getPositionX(), arrayBallMove[i - 1]->getPositionY())));
			}
			for (int i = AA_NUM_BALL_MOVE; i < 4; i++) {
				arrayBallMove[i]->setVisible(false);
			}
		}
	}
	else
	{
		BaseGUI::onTouchEnded(pTouch, pEvent);
	}
}

void GUIaa::callbackCompleteEndGame()
{
    next->getImg()->runAction(
        Sequence::create(FadeIn::create(0.5f), DelayTime::create(1.0f), FadeOut::create(0.3f),
                                               CallFunc::create(AX_CALLBACK_0(GUIaa::newGame, this)), NULL));
}

void GUIaa::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
    BaseGUI::showGUI(parent, hasFog);
    newGame();
}
