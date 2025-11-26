#include "GUIMerge.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_PAUSE_ID 3
#define BTN_PLAY_ID 4
#define BTN_TOP_ID 5
#define BTN_OK_ID 6
#define BTN_DOWNLOAD_ID 7
std::string GUIMerge::className = "GUIMerge";
void GUIMerge::initGUI()
{
	BaseGUI::initGUI();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	

	GameImage* background = addImage("bg.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);
	Color3B color = Color3B(50, 50, 50);
	//background->setColor(color);

	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
	if (size.width / size.height < 11.0 / 20.0)
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.4f);
	else
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.8f);
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

	btnDownload = addButton(BTN_DOWNLOAD_ID, "btnDownload.png");
	btnDownload->setPosition(btnSound->getPositionX() - btnDownload->getWidth() * 0.65f, btnBack->getPositionY());
	#if _TARGET_PLATFORM == _PLATFORM_IOS
	btnDownload->setVisible(false);
	#endif

	btnTop = addButton(BTN_TOP_ID, "btnTop.png");
	btnTop->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());
	btnTop->setVisible(false);

	labelScore = Text::create("0", "fonts/tahomabd.ttf", 14);
	labelScore->setColor(Color3B(50, 50, 50));
	labelScore->setPositionX(size.width * 0.15f);
	labelScore->setPositionY(btnBack->getPositionY());
    labelScore->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
	labelScore->setVisible(false);

	labelHighscore = Text::create("0", "fonts/tahomabd.ttf", 14);
	//labelHighscore->setColor(Color3B(50, 50, 50));
	labelHighscore->setPositionX(size.width * 0.5f);
	labelHighscore->setPositionY(labelScore->getPositionY());
	labelHighscore->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
	labelHighscore->setVisible(false);

	bgScore = Scale9Sprite::create("GuiGame/bgScoreNormal.png");
	//bgScore->setColor(Color3B(25, 25, 25));
	addChild(bgScore);
	bgScore->setContentSize(Size(120, 45));
	bgScore->setPosition(bgScore->getContentSize().width * 0.55, btnBack->getPositionY());

	Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 15);
	bgScore->addChild(lbScore);
	lbScore->enableOutline(Color4B(115, 37, 31, 255), 1);
    lbScore->enableOutline(Color4B(4, 85, 186, 255), 2);
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 1.0));

	bgBest = Scale9Sprite::create("GuiGame/bgScoreBest.png");
	//bgBest->setColor(Color3B(25, 25, 25));
	addChild(bgBest);
	bgBest->setContentSize(bgScore->getContentSize());
	bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.2, bgScore->getPositionY());

	Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 15);
	bgBest->addChild(lbBest);
	lbBest->enableOutline(Color4B(115, 37, 31, 255), 1);
    lbBest->enableOutline(Color4B(180, 112, 4, 255), 2);
	lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 1.0));

	score = UserDefault::getInstance()->getIntegerForKey("saveScoreMerge", 0);
	highscore = UserDefault::getInstance()->getIntegerForKey("highscoreMerge", 0);
	labelScoreSum = Text::create("0", "fonts/tahomabd.ttf", 22);
	labelScoreSum->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelScoreSum->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgScore->addChild(labelScoreSum);
	labelScoreSum->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.46));

	labelHighscoreSum = Text::create("0", "fonts/tahomabd.ttf", 22);
	labelHighscoreSum->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelHighscoreSum->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgBest->addChild(labelHighscoreSum);
	labelHighscoreSum->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.46));
	labelHighscoreSum->setString(GameUtility::standardizeNumber(highscore).c_str());

	updateScoreSum();

	bgCenter = Sprite::create("GuiGame/bgWhite.png");
	bgCenter->setAnchorPoint(Vec2(0.5, 0));
	addChild(bgCenter);
	bgCenter->setColor(Color3B(0, 0, 0));

	groupCenter = new GroupCenter();
	groupCenter->setAnchorPoint(Vec2(0.5, 0));
	widthCenter = size.width * 0.9f;
	float scale = widthCenter / groupCenter->getContentSize().width;
	heightCenter = groupCenter->getContentSize().height * scale;
	float posY = btnBack->getPositionY() - btnBack->getHeight() - groupCenter->getContentSize().height * scale;
	if (posY < size.height * 0.11) {
		heightCenter = btnBack->getPositionY() - btnBack->getHeight() - size.height * 0.11;
		scale = heightCenter / groupCenter->getContentSize().height;
		widthCenter = groupCenter->getContentSize().width * scale;
		posY = size.height * 0.11;
	}
	
	groupCenter->setScale(scale);
	groupCenter->setPosition(Vec2(size.width * 0.5, posY));
	addChild(groupCenter);
	groupCenter->setClippingEnabled(true);

	groupNewNumber = new GroupNewNumber();
	addChild(groupNewNumber);

    border = addImage("border2.png");
    border->setWidth(widthCenter + 20);
    border->setHeight(heightCenter + 20);
    border->setPosition(size.width * 0.5, posY + border->getRealHeight() * 0.5 - 10);
    border->setColor(Color3B(120, 130, 170));

	bgCenter->setScale(groupCenter->getContentSize().width / bgCenter->getContentSize().width * scale, (groupCenter->getContentSize().height * scale + 4) / bgCenter->getContentSize().height);
	bgCenter->setPosition(size.width * 0.5, groupCenter->getPositionY() - 2);
	setKeypadEnabled(true);

	//showEffect();
	//newGame();
}

void GUIMerge::onBackKey()
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		if (score > 0) {
			groupCenter->saveGame();
		}
		//game->endGame();
        game->changeToLandscape();
		GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
		GUIManager::getInstance().isCallBackPress = true;
	}
}

void GUIMerge::onButtonRelease(int buttonId, Touch* event)
{
    GameSound::playClick();
	switch(buttonId)
	{
	case BTN_BACK_ID:
	{
		onBackKey();
	}
	break;
	case BTN_DOWNLOAD_ID:
	{
		JNIUtils::openApp("com.bcsofts.dropNumber");
	}
	break;
	case BTN_SOUND_ID:
	{
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
    case BTN_TOP_ID:
        JNIUtils::submitScore(GAME_DROP, highscore);
        break;
	}
}

void GUIMerge::hideGUI()
{
	
}

void GUIMerge::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
    BaseGUI::showGUI();
	showEffect();
	newGame();
}

void GUIMerge::showEffect()
{
	bgCenter->setOpacity(0);
	float scale = bgCenter->getScaleX();
	bgCenter->runAction(
		Spawn::create(
			FadeIn::create(1.5),
			NULL
		)
	);
    
	border->getImg()->setOpacity(0);
    border->getImg()->runAction(
		Spawn::create(
			FadeIn::create(1.5),
			NULL
		)
	);
	//bgCenter->setScaleX(bgCenter->getScaleX() * 5);
	moveEffect(groupCenter, 0, -500, 0);
	moveEffect(bgScore, -300, 0, 0.2);
	moveEffect(bgBest, -300, 0, 0.3);
	moveEffect(btnSound->normalImage, 300, 0, 0.2);
	moveEffect(btnBack->normalImage, 300, 0, 0.3);
}

void GUIMerge::moveEffect(Node* node, float dx, float dy, float delay)
{
	node->setPosition(node->getPositionX() + dx, node->getPositionY() + dy);
	node->runAction(Sequence::create(
		DelayTime::create(delay),
		EaseBackOut::create(MoveBy::create(0.7, Vec2(-dx, -dy))),
		NULL
	));
}

void GUIMerge::update()
{
	groupCenter->update(game->deltaTime);
}

void GUIMerge::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	BaseGUI::onTouchEnded(pTouch, pEvent);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(pTouch->getLocation());
	groupCenter->doDropBall(convertPoint.x, convertPoint.y);
}

bool GUIMerge::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(pTouch->getLocation());
	groupCenter->doMoveBall(convertPoint.x, convertPoint.y);
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIMerge::onTouchMoved(Touch*touch, Event* event)
{
	BaseGUI::onTouchMoved(touch, event);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 convertPoint = groupCenter->convertToNodeSpace(touch->getLocation());
	groupCenter->doMoveBall(convertPoint.x, convertPoint.y);
}

void GUIMerge::addScore(int _score)
{
	score = score + _score;
	updateScoreSum();
}

void GUIMerge::updateScoreSum()
{
	labelScoreSum->setString(("" + GameUtility::standardizeNumber(score)).c_str());
	UserDefault::getInstance()->setIntegerForKey("saveScoreMerge", score);
	if (score > highscore) {
		highscore = score;
		labelHighscoreSum->setString(("" + GameUtility::standardizeNumber(score)).c_str());
		UserDefault::getInstance()->setIntegerForKey("highscoreMerge", highscore);
	}
	UserDefault::getInstance()->flush();
}

void GUIMerge::endGame()
{
	GUIManager::getInstance().guiResult->showGUI(score, highscore);
	score = 0;
}

void GUIMerge::newGame()
{
	groupNewNumber->setVisible(false);
	groupCenter->newGame();
	updateScoreSum();
}

void GUIMerge::showNewNumber(int number, Vec2 pos, float scale)
{
	groupNewNumber->showNewNumber(number, pos, scale);
}

void GUIMerge::resumeGame()
{
	groupCenter->resumeGame();
}
