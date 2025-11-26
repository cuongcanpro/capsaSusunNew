#include "guiPop.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/Toast.h"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_PAUSE_ID 3
#define BTN_PLAY_ID 4
#define BTN_TOP_ID 5
#define BTN_OK_ID 6
#define BTN_MUSIC_ID 7
#define BTN_VIBRATE_ID 8
#define BTN_PAUSE_ID 9
#define BTN_RESUME_ID 10
#define BTN_BOMB 11
#define BTN_NEW_GAME       12
std::string GUIPop::className = "GUIPop";
void GUIPop::initGUI()
{
	BaseGUI::initGUI();
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();


	GameImage* background = addImage("bg.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);
	//Color4B color = c3(50, 50, 50);
	//background->setColor(color);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	if (size.width / size.height < 11.0 / 20.0)
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.3f);
	else
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.9f);
	//	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if (game->music)
	{
		btnSound->normalImage->setImage("btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("btnSoundOff.png");
	}

    btnTop = addButton(BTN_TOP_ID, "btnTrophy.png");
    btnTop->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());
    btnTop->setVisible(false);

	bgScore = Scale9Sprite::create("GuiGame/bgScoreNormal.png");
    addChild(bgScore);
    bgScore->setContentSize(Size(110, 50));
    bgScore->setPosition(Vec2(bgScore->getContentSize().width * 0.54, btnBack->getPositionY()));

    Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 14);
    bgScore->addChild(lbScore);
    lbScore->enableOutline(Color4B(3, 85, 188, 255), 1);
    lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.75));

    currentNumber = new PopObjectNumber();
    bgScore->addChild(currentNumber);
    currentNumber->setPosition(Vec2(bgScore->getContentSize().width * 0.9, bgScore->getContentSize().height * 0.9));
    currentNumber->setScale(0.25);
    currentNumber->setNumber(game->bestNum);
    currentNumber->setNewNumber();

    bgBest = Scale9Sprite::create("GuiGame/bgScoreBest.png");
    addChild(bgBest);
    bgBest->setContentSize(bgScore->getContentSize());
    bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.05, bgScore->getPositionY());

    Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 14);
    bgBest->addChild(lbBest);
    lbBest->enableOutline(Color4B(175, 108, 3, 255), 1);
    lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.75));

    bestNumber = new PopObjectNumber();
    bgBest->addChild(bestNumber);
    bestNumber->setPosition(Vec2(bgScore->getContentSize().width * 0.9, bgScore->getContentSize().height * 0.9));
    bestNumber->setScale(0.25);
    bestNumber->setNumber(game->bestNum);
    bestNumber->setNewNumber();

    labelScore = Text::create("0", "fonts/tahomabd.ttf", 18);
    labelScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelScore->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelScore->enableOutline(Color4B(3, 85, 188, 255), 1);
    bgScore->addChild(labelScore);
    labelScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.3));

    labelHighscore = Text::create(GameUtility::standardizeNumber(game->highscorePop), "fonts/tahomabd.ttf", 18);
    labelHighscore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelHighscore->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelHighscore->enableOutline(Color4B(175, 108, 3, 255), 1);
    bgBest->addChild(labelHighscore);
    labelHighscore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.3));
	
	updateScoreSum();

	bgCenter = Sprite::create("GuiGame/pop/bgWhite.jpg");
	bgCenter->setAnchorPoint(Vec2(0.5, 0));
	addChild(bgCenter);
	bgCenter->setColor(Color3B(0, 0, 0));
    bgCenter->setOpacity(150);

    btnNewGame = addButton(BTN_NEW_GAME, "pop/btnNewGameSmall.png");
    btnNewGame->setPosition(btnNewGame->getWidth() * 0.55, btnBack->getPositionY() - btnBack->getHeight() * 1.2);

    btnBomb = addButton(BTN_BOMB, "pop/btnBomb.png");
    btnBomb->setPosition(btnNewGame->getPositionX() + btnNewGame->getWidth() * 0.5 + btnBomb->getWidth() * 0.55, btnBack->getPositionY() - btnBack->getHeight() * 1.2);

	iconBomb = Sprite::create("GuiGame/pop/iconBomb.png");
    float widthProgress = size.width - btnBomb->getPositionX() - btnBomb->getWidth() * 0.6 - iconBomb->getContentSize().width * 1.1;
	bgProgress = addImage("pop/bgProgress.png");
	//bgProgress->setColor(c3(100, 100, 100));
	bgProgress->setWidth(widthProgress);
	//bgProgress->setHeight(btnBack->getHeight() * 0.75f);
    bgProgress->setPos(btnBomb->getPositionX() + btnBomb->getWidth() * 0.6 + widthProgress * 0.5, btnBomb->getPositionY());

	progress = ProgressTimer::create(Sprite::create("GuiGame/pop/progress.png"));
	progress->setType(ax::ProgressTimer::Type::BAR);
	progress->setMidpoint(Vec2(0, 0.5));
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setPercentage(50);
	progress->setPositionX(bgProgress->getWidth() * 0.495 - progress->getContentSize().width * 0.5);
	progress->setPositionY(bgProgress->getHeight() * 0.5 - progress->getContentSize().height * 0.5);
	bgProgress->addChild(progress);
	
	addChild(iconBomb);
	iconBomb->setPosition(bgProgress->getRealWidth() * 0.5 + bgProgress->getPositionX() + iconBomb->getContentSize().width * 0.6, bgProgress->getPositionY());

	iconBombEffect = Sprite::create("GuiGame/pop/iconBomb.png");
	addChild(iconBombEffect, 5);
	iconBombEffect->setPosition(iconBomb->getPosition());

	lbBomb = Text::create(GameUtility::standardizeNumber(numBomb).c_str(), "fonts/tahomabd.ttf", 27);
	lbBomb->enableOutline(Color4B(105, 70, 9, 255), 2);
	lbBomb->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbBomb->setAnchorPoint(Vec2(0.5f, 0.5f));
	//this->addChild(lbBomb, 2);
	btnBomb->normalImage->addChild(lbBomb);
	lbBomb->setPosition(Vec2(0, -btnBomb->getHeight() * 0.23));

	groupCenter = new BoardPop();
	groupCenter->setAnchorPoint(Vec2(0.5, 0));
	widthCenter = size.width * 0.95f;
    float posY  = iconBomb->getPositionY() - iconBomb->getContentSize().height - widthCenter;
	if (posY < size.height * 0.11) {
		widthCenter = bgProgress->getPositionY() - bgProgress->getRealHeight() - size.height * 0.11;
	}
	addChild(groupCenter);
	groupCenter->setClippingEnabled(true);

	imgNewBest = Sprite::create("GuiGame/best.png");
	addChild(imgNewBest);
	imgNewBest->setLocalZOrder(3);
	imgNewBest->setVisible(false);

	groupNewNumber = new PopGroupNewNumber();
	addChild(groupNewNumber, 2);

    flyNumber = new FlyNumber();
	addChild(flyNumber, 100);

	setKeypadEnabled(true);

	showEffect();
	//newGame();
	
}

void GUIPop::onBackKey()
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
            game->changeToLandscape();
		if (score > 0) {
			groupCenter->saveGame();
		}
		//game->endGame();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
		GUIManager::getInstance().isCallBackPress = true;
	}
}


void cancelNewGamePop() {}

void okNewGamePop()
{
    if (GUIManager::getInstance().guiPop->currentScore > 200)
    {
        game->showAdsFull();
    }
    string add = GUIManager::getInstance().guiPop->type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
    UserDefault::getInstance()->setIntegerForKey(("saveScorePop" + add).c_str(), 0);
    UserDefault::getInstance()->flush();
    GUIManager::getInstance().guiPop->newGame();
}


void GUIPop::onButtonRelease(int buttonId, Touch* event)
{
    GameSound::playClick();
	switch (buttonId)
	{
	case BTN_BACK_ID:
	{
		onBackKey();
	}
	break;
	case BTN_TOP_ID:
	{
        if (type == BoardType::POP_TYPE_NORMAL)
            JNIUtils::submitScore(GAME_POP, game->highscorePop);
        else
            JNIUtils::submitScore(1, game->highscorePopHard);
	}

	break;
	case BTN_SOUND_ID:
	{
		//groupNewNumber->showNewNumber(10, Vec2(200, 200), 1);
            //JNIUtils::submitScore(10, 0);
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
	case BTN_VIBRATE_ID:
	{
		
	}
	break;
	case BTN_BOMB:
	{
        if (groupCenter->state == POP_BOMB)
            return;
		if (numBomb > 0) {
			useBomb();
		}
		else {
			Toast::makeToast(2.0, "You don't have any bomb");
		}
	}
	break;
        case BTN_NEW_GAME:
        {
            GUIManager::getInstance().guiDialog->showGUI(CCLocalizedString("START_NEW_GAME").c_str(), &okNewGamePop, false,
                                                        &cancelNewGamePop, NULL, NULL);
            break;
        }
        break;
	}
}

void GUIPop::hideGUI()
{
	
}

void GUIPop::showGUI(BoardType type)
{
    this->type = type;
    groupCenter->data->type = type;
	showEffect();
	newGame();
}

void GUIPop::showEffect()
{
	bgCenter->setOpacity(0);
	float scale = bgCenter->getScaleX();
	bgCenter->runAction(
		Spawn::create(
			FadeTo::create(1.5, 150),
		//	ScaleTo::create(2.5, scale * 0.5, bgCenter->getScaleY()),
			NULL
		)
	);
	//bgCenter->setScaleX(bgCenter->getScaleX() * 5);
//	moveEffect(groupCenter, 0, -500, 0);

	moveEffectSineOut(bgScore, -500, 0, 0.2);
	moveEffectSineOut(bgBest, -500, 0, 0.1);
    moveEffectSineOut(btnNewGame->normalImage, -500, 0, 0.1);
	moveEffectSineOut(btnBomb->normalImage, -500, 0, 0.2);

    moveEffect(btnTop->normalImage, 500, 0, 0.1);
	moveEffect(btnSound->normalImage, 500, 0, 0.2);
	moveEffect(btnBack->normalImage, 500, 0, 0.3);

	moveEffect(bgProgress, 500, 0, 0.1);
	moveEffect(iconBomb, 500, 0, 0.2);
}

void GUIPop::moveEffect(Node* node, float dx, float dy, float delay)
{
	node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseBackOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))),
		NULL
	));
}

void GUIPop::moveEffectSineOut(Node* node, float dx, float dy, float delay)
{
	node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseSineOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))),
		NULL
	));
}

void GUIPop::update()
{
	if (currentScore != targetScore) {
		if ((targetScore - currentScore) * deltaScore < 0) {
			currentScore = targetScore;
		}
		else {
			currentScore = currentScore + deltaScore;
		}
		updateScoreSum();
	}
	groupCenter->update(game->deltaTime);

	if (groupCenter->state != POP_BOMB) {
		if (targetMana != manaPoint) {
			if ((targetMana - manaPoint) * deltaMana < 0) {
				manaPoint = targetMana;
				deltaMana = 0;
			}
			else {
				manaPoint = manaPoint + deltaMana;
			}
		}
		else {
			manaPoint = manaPoint - 0.02;
			targetMana = manaPoint;
		}

		if (manaPoint < 0)
			manaPoint = 0;
		float targetBonus = 150 * groupCenter->data->maxNum / 5.0f;
		float percent = manaPoint / targetBonus * 100;
		progress->setPercentage(percent);
		if (percent >= 100) {
			manaPoint = targetBonus - 1;
			addMana(-targetMana);
			numBomb = numBomb + 1;
			iconBombEffect->setVisible(true);
			iconBombEffect->setOpacity(255);
			iconBombEffect->setPosition(iconBomb->getPosition());
			iconBombEffect->runAction(
				Sequence::create(
					EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 40))),
					EaseExponentialOut::create(MoveTo::create(1.0, btnBomb->getPosition())),
					FadeOut::create(0.5),
					Hide::create(),
                    CallFunc::create(AX_CALLBACK_0(GUIPop::updateBomb, this)),
					NULL
				)
			);
			GameSound::playLevelUp();
		}
		//groupCenter->update(game->deltaTime);
	}
}

void GUIPop::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(pTouch->getLocation());
	groupCenter->doTouchEnd(convertPoint.x, convertPoint.y);
	BaseGUI::onTouchEnded(pTouch, pEvent);
}

bool GUIPop::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(pTouch->getLocation());
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIPop::onTouchMoved(Touch*touch, Event* event)
{
	BaseGUI::onTouchMoved(touch, event);
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(touch->getLocation());
}

void GUIPop::addScore(int _score)
{
	targetScore = targetScore + _score;
	deltaScore = (targetScore - currentScore) / 10.0f;
	addMana(_score);
	updateScoreSum();
    string add = type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
	UserDefault::getInstance()->setIntegerForKey(("saveScorePop" + add).c_str(), targetScore);
    if (type == BoardType::POP_TYPE_NORMAL)
    {
        if (targetScore > game->highscorePop)
        {
            game->highscorePop = targetScore;
            UserDefault::getInstance()->setIntegerForKey(("highscorePop" + add).c_str(), game->highscorePop);
            showNewBest();
        }
    }
    else
    {
        if (targetScore > game->highscorePopHard)
        {
            game->highscorePopHard = targetScore;
            UserDefault::getInstance()->setIntegerForKey(("highscorePop" + add).c_str(), game->highscorePopHard);
            showNewBest();
        }
    }
	
    if (game->showHelpTouch && iconHand)
    {
        iconHand->stopAllActions();
        iconHand->setVisible(false);
        game->showHelpTouch = false;
        UserDefault::getInstance()->setBoolForKey("showHelpTouch", false);
    }
	UserDefault::getInstance()->flush();
}

void GUIPop::addMana(int mana)
{
	targetMana = targetMana + mana;
	deltaMana = (targetMana - deltaMana) / 20.0f;
}

void GUIPop::updateMaxNum() {
    currentNumber->setNumber(groupCenter->data->maxNum);
    currentNumber->playEffect();
}

void GUIPop::updateBestNum() {
    if (type == BoardType::POP_TYPE_NORMAL)
        bestNumber->setNumber(game->bestNum);
    else
        bestNumber->setNumber(game->bestNumHard);
    bestNumber->playEffect();
}

void GUIPop::updateScoreSum()
{
	int oldScore = score;
	score = (int)currentScore;
	if (oldScore != score) {
		labelScore->setString(("" + GameUtility::standardizeNumber(score)).c_str());
        labelScore->stopAllActions();
        labelScore->setScale(1);
        labelScore->runAction(
			Sequence::create(
				ScaleTo::create(0.05, 1.3),
				ScaleTo::create(0.05, 1),
				NULL
			)
		);

		if (score > highscore) {
			highscore = score;
            labelHighscore->setString(("" + GameUtility::standardizeNumber(score)).c_str());
		}
	}
}

void GUIPop::updateBomb()
{
	lbBomb->setString(GameUtility::toString(numBomb));
}

void GUIPop::useBomb()
{
    if (groupCenter->state == POP_BOMB)
    {
        return;
    }
    if (numBomb <= 0)
        return;
	numBomb--;
	updateBomb();
	groupCenter->useBomb();
	iconBombEffect->setPosition(btnBomb->getPosition());
	iconBombEffect->setOpacity(255);
	iconBombEffect->runAction(
		Sequence::create(
			MoveBy::create(0.5, Vec2(0, 40)),
			DelayTime::create(0.5),
			FadeOut::create(0.5),
			NULL
		)
	);
}

void GUIPop::endGame()
{
    if (type == BoardType::POP_TYPE_NORMAL)
	    GUIManager::getInstance().guiResult->showGUI(targetScore, game->highscorePop);
    else
        GUIManager::getInstance().guiResult->showGUI(targetScore, game->highscorePopHard);
	score = 0;
}

void GUIPop::newGame()
{
    flyNumber->setVisible(false);
	score = 0;
	numBomb = 1;
	targetScore = 0;
	currentScore = 0;
    labelScore->setString(("" + GameUtility::standardizeNumber(score)).c_str());
    string add = type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
    int saveScore = UserDefault::getInstance()->getIntegerForKey(("saveScorePop" + add).c_str(), 0);
	if (saveScore > 0) {
		targetScore = saveScore;
		currentScore = saveScore;
		numBomb = UserDefault::getInstance()->getIntegerForKey(("numBomb" + add).c_str(), 1);
	}
	deltaScore = 0;
	groupNewNumber->setVisible(false);
	iconBombEffect->setVisible(false);
	imgNewBest->setVisible(false);
	imgNewBest->stopAllActions();
	manaPoint = 0;
	deltaMana = 0;
	targetMana = 0;
	
    if (type == BoardType::POP_TYPE_NORMAL) {
        highscore = game->highscorePop;
        labelHighscore->setString(GameUtility::standardizeNumber(game->highscorePop));
        if (game->highscorePop == 0 || game->highscorePop <= score)
        {
            isNewBest = true;
        }
    }
    else
    {
        highscore = game->highscorePopHard;
        labelHighscore->setString(GameUtility::standardizeNumber(game->highscorePopHard));
        if (game->highscorePopHard == 0 || game->highscorePopHard <= score)
        {
            isNewBest = true;
        }
    }
    
	addScore(0);
	groupCenter->newGame();
    updateMaxNum();
	updatePosCenter();
	updateScoreSum();
	updateBomb();

    runAction(Sequence::create(
        DelayTime::create(1.0),
        CallFunc::create(AX_CALLBACK_0(GUIPop::checkShowTouch, this)),
        NULL
    ));
}

void GUIPop::checkShowTouch() {

    if (game->showHelpTouch)
    {
        PointGame p = groupCenter->data->getCanTouchPoint();
        if (p.x < 0 || p.y < 0)
        {
            return;
        }
        iconHand    = Sprite::create("GuiGame/iconHand.png");
        iconHand->setAnchorPoint(Vec2(0.1, 0.8));
        addChild(iconHand);
        Vec2 pos      = groupCenter->getPosCell(p.x, p.y);
        Vec2 posStart = Vec2(pos.x + 80, pos.y + 80);
        iconHand->setPosition(pos);
        iconHand->setScale(3.2);
        iconHand->runAction(RepeatForever::create(Sequence::create(
            Show::create(),
            Spawn::create(MoveTo::create(0.5, pos), EaseBackOut::create(ScaleTo::create(0.5, 1)), NULL),
            DelayTime::create(0.5), Spawn::create(MoveTo::create(0, pos), ScaleTo::create(0, 3.2), NULL),
            Hide::create(),
            DelayTime::create(1.0),
            NULL))
        );
    }
}

void GUIPop::showNewBest()
{
	if (isNewBest)
		return;
	// show Effect Best Score
	isNewBest = true;
	showEffectLabel("GuiGame/brick/iconNewBest.png");
	GameSound::playWin();
}

void GUIPop::showEffectLabel(string s)
{
	/*layerColor->setVisible(false);
	layerColor->setOpacity(0);
	layerColor->runAction(
		Sequence::create(
			FadeTo::create(0.5, 100),
			DelayTime::create(2.5),
			FadeOut::create(0.5),
			Hide::create(),
			NULL
		)
	);*/


	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 pos = Vec2(size.width * 0.5, size.height * 0.6);

	imgNewBest->setVisible(true);
	imgNewBest->setPosition(pos);
	imgNewBest->setOpacity(0);
	imgNewBest->setScale(6);
	imgNewBest->runAction(Sequence::create(
		EaseBounceOut::create(ScaleTo::create(0.6, 1.5)),
		DelayTime::create(2.0),
		FadeOut::create(0.5),
		Hide::create(),
		NULL
	));
	imgNewBest->runAction(FadeIn::create(0.5));
}

void GUIPop::showNewNumber(int number, Vec2 pos, float scale)
{
	groupNewNumber->showNewNumber(number, pos, scale);
}

void GUIPop::showFlyNumber(int number, Vec2 pos, float scale)
{
    flyNumber->effectFly(pos);
    flyNumber->setNumber(number);
}

void GUIPop::initAds()
{
	
	
}

void GUIPop::updatePosCenter()
{
	groupCenter->updateBoardSize();
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	float scale = widthCenter / groupCenter->getContentSize().width;
	heightCenter = groupCenter->getContentSize().height * scale;
    float posY = iconBomb->getPositionY() - iconBomb->getContentSize().height * 0.8 - groupCenter->getContentSize().height * scale;
	if (posY < size.height * 0.13) {
		//heightCenter = bgScore->getPositionY() - bgScore->getContentSize().height - size.height * 0.13;
        heightCenter = iconBomb->getPositionY() - iconBomb->getContentSize().height * 0.8 - size.height * 0.13;
		scale = heightCenter / groupCenter->getContentSize().height;
		widthCenter = groupCenter->getContentSize().width * scale;
		posY = size.height * 0.13;
	}
	float time = 0.3;
	groupCenter->stopAllActions();
	groupCenter->runAction(
		Spawn::create(
			ScaleTo::create(time, scale),
			MoveTo::create(time, Vec2(size.width * 0.5, posY)),
			NULL
		)
	);
	float sX = (groupCenter->getContentSize().width  * scale + 10) / bgCenter->getContentSize().width;
	float sY = (groupCenter->getContentSize().height * scale + 10) / bgCenter->getContentSize().height;
	bgCenter->runAction(
		Spawn::create(
			ScaleTo::create(time, sX, sY),
			MoveTo::create(time, Vec2(size.width * 0.5, posY - 5)),
			NULL
		)
	);
}

void GUIPop::addBomb(int _bomb) {
    numBomb = numBomb + _bomb;
    updateBomb();

    Text* lbBest = Text::create("+" + to_string(_bomb), "fonts/tahomabd.ttf", 45);
    this->addChild(lbBest);
    lbBest->enableOutline(Color4B(175, 108, 3, 255), 3);
    lbBest->setPosition(btnBomb->getPosition());
    lbBest->runAction(
        Sequence::create(
            EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 100))),
            DelayTime::create(1.0),
            FadeOut::create(0.5),
            RemoveSelf::create(),
            NULL
        )
    );

    btnBomb->normalImage->runAction(
        Sequence::create(
            MoveBy::create(0.2, Vec2(0, 50)),
            EaseBounceOut::create(MoveBy::create(0.4, Vec2(0, -50))),
            NULL
        )
    );
}
