#include "GUIResult.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"
#include <Engine/Utility/CStringUtils.h>

#define GUI_RESULT_BTN_OK 1
#define GUI_RESULT_BTN_CONTINUE 2
std::string GUIResult::className = "GUIResult";
GUIResult::GUIResult(void) : BaseGUI()
{
    BaseGUI();
    setKeypadEnabled(true);
}

GUIResult::~GUIResult(void) {}
void GUIResult::initGUI()
{
    BaseGUI::initGUI();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size   = Director::getInstance()->getRenderView()->getVisibleSize();

    bg = Scale9Sprite::create("GuiGame/bgDialog.png");
    addChild(bg);
    bg->setPosition(size.width * 0.5, size.height * 0.55);
    bg->setContentSize(Size(400, 400 * 0.95));

    // eff->setPosition(size.width * 0.5, bg->getPositionY() + bg->getContentSize().height * 0.5);

    title = new GameImage("iconCongrat.png", false);
    bg->addChild(title);
    title->setPosition(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.92);

    float pad = 45;

    lbScore1 = Text::create("SCORE", "fonts/tahomabd.ttf", 20);
    bg->addChild(lbScore1);
    lbScore1->enableOutline(Color4B(115, 37, 31, 255), 2);
    lbScore1->setPosition(Vec2(bg->getContentSize().width * 0.5, title->getPositionY() - title->getHeight() * 0.5));

    bgScore = Scale9Sprite::create("GuiGame/bgScoreNormal.png");
    // bgScore->setInsetTop(22);
    //  bgScore->setInsetBottom(22);
    bg->addChild(bgScore);
    bgScore->setContentSize(Size(150, 60));
    bgScore->setPosition(lbScore1->getPositionX(), lbScore1->getPositionY() - pad);

    lbScore = Text::create("0", "fonts/tahomabd.ttf", 30);
    lbScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    lbScore->enableOutline(Color4B(4, 85, 186, 255), 2);
    lbScore->setAnchorPoint(Vec2(0.5f, 0.5f));
    bgScore->addChild(lbScore);
    lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.53));

    lbBestScore1 = Text::create("BEST", "fonts/tahomabd.ttf", 20);
    bg->addChild(lbBestScore1);
    lbBestScore1->enableOutline(Color4B(115, 37, 31, 255), 2);
    lbBestScore1->setPosition(Vec2(bg->getContentSize().width * 0.5, bgScore->getPositionY() - pad));

    bgBest = Scale9Sprite::create("GuiGame/bgScoreBest.png");
    bg->addChild(bgBest);
    bgBest->setContentSize(Size(150, 60));
    bgBest->setPosition(bg->getContentSize().width * 0.5, lbBestScore1->getPositionY() - pad);

    lbBestScore = Text::create("0", "fonts/tahomabd.ttf", 30);
    lbBestScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    lbBestScore->setAnchorPoint(Vec2(0.5f, 0.5f));
    lbBestScore->enableOutline(Color4B(180, 112, 4, 255), 2);
    bgBest->addChild(lbBestScore);
    lbBestScore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.53));

	btnPlay = addButton(GUI_RESULT_BTN_OK, new GameImage("btnNewGame.png", false), bg);
	btnPlay->setPosition(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.15);
	btnPlay->addBehavior(new BubbleBehavior());

    btnContinue = addButton(GUI_RESULT_BTN_CONTINUE, new GameImage("btnContinue.png", false), bg);
	btnContinue->setPosition(bg->getContentSize().width * 0.5 - btnContinue->getWidth() * 0.55, bg->getContentSize().height * 0.15);
    btnContinue->addBehavior(new BubbleBehavior());
	
	iconBest = Sprite::create("GuiGame/best.png");
	bg->addChild(iconBest);
	iconBest->setPosition(bg->getContentSize().width * 0.83, bgBest->getPositionY());

	//effBest = DBFactory::getInstance()->buildArmatureNode("fire_work");
	//if (effBest)
	//{
	//	addChild(effBest);
	//	effBest->setPosition(Vec2(size.width * 0.5, bg->getPositionY() + bg->getContentSize().height * 0.6));
	//	effBest->setVisible(false);
	//	//effBest->gotoAndPlay("run", -1, -1, -1);
	//}

    auto effect = efk::Effect::create("TestEffect/firework.efk", 13.0f);
    if (effect != nullptr)
    {
        effFirework = efk::EffectEmitter::create(game->manager);
        effFirework->setEffect(effect);
        effFirework->setPlayOnEnter(false);
        effFirework->setRemoveOnStop(false);

        effFirework->setRotation3D(ax::Vec3(0, 90, 0));
        effFirework->setPosition(Vec2(bg->getContentSize().width * 0.5, 0));

        // emitter->setScale(13);
        this->bg->addChild(effFirework, 0);
    }
}

void okContinue()
{
   // game->isWaitContinue = true;
    JNIUtils::showRewardedAds();
}


void okContinueNormal()
{
    //JNIUtils::showAdsFull();
 //   game->showAdsFull();
    GUIManager::getInstance().guiResult->setVisible(false);
    GUIManager::getInstance().removeFromListGui();
    int subScore    = floor(game->saveScore / game->numDivide);
    game->saveScore = game->saveScore - subScore;
    if (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())
        GUIManager::getInstance().guiLine->changeToRemoveBall();
    
}

void GUIResult::onButtonRelease(int buttonId, Touch* event)
{
    GameSound::playClick();
    switch (buttonId)
    {
    case GUI_RESULT_BTN_OK:
        bg->runAction(Sequence::create(EaseBackIn::create(ScaleTo::create(0.5, 0)),
                                       CallFunc::create(AX_CALLBACK_0(GUIResult::hideGUI, this)), NULL));

        //JNIUtils::showAdsFull();

        break;
    case GUI_RESULT_BTN_CONTINUE:
    {
        int subScore = floor(game->saveScore / game->numDivide);
        // game->saveScore = game->saveScore - subScore;
        if (game->useReward)
        {
            string s = CCLocalizedString("VIEW_REWARD_CONTINUE");
            CStringUtils::replaceAll(s, "@num", game->numDestroy);
            CStringUtils::replaceAll(s, "@score", subScore);
            GUIManager::getInstance().guiDialog->showGUI(s.c_str(), &okContinue, false, NULL);
        }
        else
        {
            string s = CCLocalizedString("VIEW_NORMAL_CONTINUE");
            CStringUtils::replaceAll(s, "@num", game->numDestroy);
            CStringUtils::replaceAll(s, "@score", subScore);
            GUIManager::getInstance().guiDialog->showGUI(s.c_str(), &okContinueNormal, false, NULL);
        }
        break;
    }
    }
}

void GUIResult::hideGUI()
{
	setVisible(false);
	GUIManager::getInstance().removeFromListGui();
        if (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())
        {
            GUIManager::getInstance().guiLine->newGame();
        }
        else if (GUIManager::getInstance().guiGame != NULL && GUIManager::getInstance().guiGame->isVisible())
        {
            GUIManager::getInstance().guiGame->newGame();
        }
        else if (GUIManager::getInstance().guiTwenty != NULL && GUIManager::getInstance().guiTwenty->isVisible())
            GUIManager::getInstance().guiTwenty->newGame();
        else if (GUIManager::getInstance().guiMerge != NULL && GUIManager::getInstance().guiMerge->isVisible())
            GUIManager::getInstance().guiMerge->newGame();
        else if (GUIManager::getInstance().guiBomb != NULL && GUIManager::getInstance().guiBomb->isVisible())
            GUIManager::getInstance().guiBomb->newGame();
        else if (GUIManager::getInstance().guiBlock != NULL && GUIManager::getInstance().guiBlock->isVisible())
            GUIManager::getInstance().guiBlock->newGame();
        else if (GUIManager::getInstance().guiPop != NULL && GUIManager::getInstance().guiPop->isVisible())
            GUIManager::getInstance().guiPop->newGame();
        else if (GUIManager::getInstance().guiPika != NULL && GUIManager::getInstance().guiPika->isVisible())
            GUIManager::getInstance().guiPika->makeNewLevel();
        else if (GUIManager::getInstance().guiBubble != NULL && GUIManager::getInstance().guiBubble->isVisible())
            GUIManager::getInstance().guiBubble->newGame();
        else if (GUIManager::getInstance().gui2048 != NULL && GUIManager::getInstance().gui2048->isVisible())
            GUIManager::getInstance().gui2048->newGame(true);
        else if (GUIManager::getInstance().guiSudoku != NULL && GUIManager::getInstance().guiSudoku->isVisible())
            GUIManager::getInstance().guiSudoku->newGame();
        else if (GUIManager::getInstance().guiSwing != NULL && GUIManager::getInstance().guiSwing->isVisible())
            GUIManager::getInstance().guiSwing->genNewGame();
        else if (GUIManager::getInstance().guiAa != NULL && GUIManager::getInstance().guiAa->isVisible())
            GUIManager::getInstance().guiAa->newGame();
}

void GUIResult::showGUI(int score, int highscore, bool isTime)
{
    game->showAdsFull();
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);
    this->isTime = isTime;
    if (!this->isTime) {
        schedule(AX_SCHEDULE_SELECTOR(GUIResult::updateResult), 0.1);
        this->score     = score;
        this->highscore = highscore;
        currentScore    = 0;
        currentBest     = 0;
        deltaScore      = (score - currentScore) / 20.0f;
        deltaBest       = (highscore - currentBest) / 20.0f;
    }
    else
    {
        string timeGame = GameUtility::convertToTime(score);
        lbScore->setString(timeGame);
        
        string timeBest = GameUtility::convertToTime(highscore);
        this->lbBestScore->setString(timeGame);
    }
    
	bg->setScale(1);
	//bg->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	bg->setPositionY(size.height * 1.1);
	bg->runAction(EaseBackOut::create(MoveTo::create(0.5, Vec2(size.width * 0.5, size.height * 0.55))));
	bg->setScaleY(0.7);
	bg->runAction(EaseBounceOut::create(ScaleTo::create(0.5, 1.0, 1.0)));
	
    if (isTime)
    {
        title->setImage("iconCongrat.png", false);
        title->setPositionY(bg->getContentSize().height * 0.91);
        GameSound::playWin();
        if (score <= highscore)
        {
            iconBest->setVisible(true);
            iconBest->setOpacity(0);
            iconBest->setScale(10);
            iconBest->runAction(
                Sequence::create(DelayTime::create(1.5), EaseExponentialOut::create(ScaleTo::create(0.5, 0.5)), NULL));
            iconBest->runAction(Sequence::create(DelayTime::create(1.5), FadeIn::create(0.5), NULL));
            effFirework->setVisible(true);
            effFirework->play(1);
        }
        else
        {
            iconBest->setVisible(false);
            effFirework->setVisible(false);
        }
    }
    else
    {
        if (score == highscore)
        {
            iconBest->setVisible(true);
            iconBest->setOpacity(0);
            iconBest->setScale(10);
            iconBest->runAction(
            Sequence::create(DelayTime::create(1.5), EaseExponentialOut::create(ScaleTo::create(0.5, 0.5)), NULL));
            iconBest->runAction(Sequence::create(DelayTime::create(1.5), FadeIn::create(0.5), NULL));
            effFirework->setVisible(true);
            effFirework->play(1);

            title->setImage("iconCongrat.png", false);
            title->setPositionY(bg->getContentSize().height * 0.91);
            GameSound::playWin();
        }
        else
        {
            iconBest->setVisible(false);
            effFirework->setVisible(false);

            title->setImage("iconGameOver.png", false);
            title->setPositionY(bg->getContentSize().height * 0.93);
            GameSound::playLose();
        }
    }
   
    if (game->showContinue == 1 &&
        (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())) {
        btnContinue->setVisible(true);
        btnPlay->setPosition(bg->getContentSize().width * 0.5 + btnPlay->getWidth() * 0.55, btnPlay->getPositionY());
    }
    else
    {
        btnContinue->setVisible(false);
        btnPlay->setPosition(bg->getContentSize().width * 0.5, btnPlay->getPositionY());
    }
    moveEffect(title, 1, 0.5);
    moveEffect(lbScore1, 1, 0.4);
    moveEffect(bgScore, 1, 0.3);
    moveEffect(lbBestScore1, 1, 0.2);
    moveEffect(bgBest, 1, 0.1);
    moveEffect(btnPlay->normalImage, 1, 0.0);
}

void GUIResult::moveEffect(Node* node, int rate, float delay)
{
	float save = node->getPositionY();
	node->setPositionY(save + 100 * rate);
    node->setOpacity(0);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
        Spawn::create(
		    EaseBackOut::create(MoveBy::create(0.7, Vec2(0, -100 * rate))),
            FadeIn::create(0.7),
            NULL
        ),
		NULL
	));
}

void GUIResult::updateResult(float dt)
{
	if (currentScore != score) {
		currentScore = currentScore + deltaScore;
		if (abs(currentScore - score) <= deltaScore) {
			currentScore = score;
		}
		lbScore->setString(GameUtility::toString(currentScore));
	}
	if (currentBest != highscore) {
		currentBest = currentBest + deltaBest;
		if (abs(currentBest - highscore) <= deltaBest) {
			currentBest = highscore;
			if (score == highscore) {

			}
		}
        lbBestScore->setString(GameUtility::toString(currentBest));
	}
}
