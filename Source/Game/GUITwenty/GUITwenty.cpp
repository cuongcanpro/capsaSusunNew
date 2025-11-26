#include "GUITwenty.h"
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
#include "Game/Utility/Toast.h"
#include "Number.h"
#include "Engine/GUI/ParticleEffect.h"
#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_PAUSE_ID 3
#define BTN_PLAY_ID 4
#define BTN_TOP_ID 5
#define BTN_OK_ID 6

GUITwenty::GUITwenty(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	setKeypadEnabled(true);
}
std::string GUITwenty::className = "GUITwenty";

GUITwenty::~GUITwenty(void)
{
}

void GUITwenty::initGUI(){
	BaseGUI::initGUI();
	//this->setAnchorPoint(Vec2(0.5f, 0.5f));

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	TextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(Sequence::create(FadeIn::create(0.8f), DelayTime::create(.8f), FadeOut::create(0.8f), CallFunc::create(this, AX_CALLBACK_0(GUITwenty::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);
	callBackSplash();

}


void GUITwenty::callbackCompleteEndGame()
{
	GUIManager::getInstance().removeAllGui();
}

void cancelContinueFunction()
{
}

void GUITwenty::callBackSplash()
{

	/*DBFactory::getInstance()->loadDragonBonesData("animation/Oqua/skeleton.xml", "Oqua");
	DBFactory::getInstance()->loadTextureAtlas("animation/Oqua/texture.plist", "Oqua");*/
	countGame = 0;
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	GameImage* background = addImage("bg.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);
	Color3B color = Color3B(50, 50, 50);
	//background->setColor(color);
	
	btnBack = addButton(BTN_BACK_ID, "btnBack.png");
    if (size.width / size.height < 11.0 / 20.0)
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.7f);
    else
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.8f);
//	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);

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

	btnTop = addButton(BTN_TOP_ID, "btnTop.png");
	btnTop->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());
    btnTop->setVisible(false);

	labelScore = Text::create("Number: 0", "fonts/tahomabd.ttf", 30);
	labelScore->setColor(Color3B(50, 50, 50));
	labelScore->setPositionX(size.width * 0.15f);
	labelScore->setPositionY(btnBack->getPositionY());
    labelScore->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
	labelScore->setVisible(false);

	curNumber = new GroupNumber();
	addChild(curNumber);
	curNumber->setScale(0.5);
	curNumber->setPosition(curNumber->getContentSize().width * 0.6 * 0.5, btnBack->getPositionY());

	labelHighscore = Text::create("Number: 0", "fonts/tahomabd.ttf", 30);
	//labelHighscore->setColor(Color3B(50, 50, 50));
	labelHighscore->setPositionX(size.width * 0.5f);
	labelHighscore->setPositionY(labelScore->getPositionY());
	labelHighscore->setTextHorizontalAlignment(ax::TextHAlignment::LEFT);
	labelHighscore->setVisible(false);

	Scale9Sprite* bgScore = Scale9Sprite::create("GuiGame/bgScoreNormal.png");
	//bgScore->setColor(Color3B(25, 25, 25));
	addChild(bgScore);
	bgScore->setContentSize(Size(100, 40));
	bgScore->setPosition(bgScore->getContentSize().width * 0.55 + curNumber->getContentSize().width * 0.5 * 0.5 + curNumber->getPositionX(), btnBack->getPositionY());

	Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 14);
	bgScore->addChild(lbScore);
	lbScore->enableOutline(Color4B(115, 37, 31, 255), 1);
    lbScore->enableOutline(Color4B(4, 85, 186, 255), 1);
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 1.0));

	Scale9Sprite *bgBest = Scale9Sprite::create("GuiGame/bgScoreBest.png");
	//bgBest->setColor(Color3B(25, 25, 25));
	addChild(bgBest);
	bgBest->setContentSize(Size(100, 40));
	bgBest->setPosition(bgScore->getPositionX() + bgScore->getContentSize().width * 1.05, bgScore->getPositionY());

	Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 14);
	bgBest->addChild(lbBest);
	lbBest->enableOutline(Color4B(115, 37, 31, 255), 1);
    lbBest->enableOutline(Color4B(180, 112, 4, 255), 1);
	lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 1.0));

	labelScoreSum = Text::create("0", "fonts/tahomabd.ttf", 14);
    labelScoreSum->setTextHorizontalAlignment(ax::TextHAlignment::CENTER);
	labelScoreSum->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgScore->addChild(labelScoreSum);
	labelScoreSum->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.46));

	labelHighscoreSum = Text::create("0", "fonts/tahomabd.ttf", 14);
	labelHighscoreSum->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelHighscoreSum->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgBest->addChild(labelHighscoreSum);
	labelHighscoreSum->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.46));
	labelHighscoreSum->setString(GameUtility::standardizeNumber(game->highscoreSum).c_str());
	
	//labelHighscoreSum->setAlignment(TextAlignment::kTextAlignmentLeft);

	tutorialLabel = Text::create("0", "fonts/tahomabd.ttf", 14);
    addChild(tutorialLabel);
	tutorialLabel->setScale(1.3f);
	tutorialLabel->setColor(Color3B(250, 0, 250));
	tutorialLabel->setContentSize(Size(size.width * 0.9f, 200));
	//tutorialLabel->setLineBreakWithoutSpace(true);
	tutorialLabel->setPositionX(size.width * 0.5f);
	tutorialLabel->setPositionY(labelScore->getPositionY());
	tutorialLabel->setVisible(false);
	tutorialLabel->setLocalZOrder(300);

	bgProgress = addImage("bgProgressLevel.png");
	bgProgress->setWidth(size.width * 0.9);
	//bgProgress->setHeight(size.width * 0.035f);
	bgProgress->setPos(size.width * 0.5f, btnBack->getPositionY() - btnBack->getHeight() - bgProgress->getRealHeight() * 0.5f);

	progress = ProgressTimer::create(Sprite::create("GuiGame/progressLevel.png"));
    progress->setType(ax::ProgressTimer::Type::BAR);
    progress->setMidpoint(Vec2(0, 0.5));
    progress->setBarChangeRate(Vec2(1, 0));
    progress->setPercentage(50);
   // progress->setPositionX(bgProgress->getWidth() * 0.495 - progress->getContentSize().width * 0.5);
  //  progress->setPositionY(bgProgress->getHeight() * 0.5 - progress->getContentSize().height * 0.5);
    bgProgress->addChild(progress);

	if (size.width / size.height < 0.2f / 0.3f)
	{
		widthBoard = size.width * 0.96f;
	}
	else
	{
		widthBoard = size.width * 0.76f;
	}

	if (size.width / size.height < 0.2f / 0.3f)
	{
		WIDTH_SQUARE = widthBoard / NUM_COLUMN;
		START_X = size.width * 0.02f;
		START_Y = bgProgress->getPositionY() - bgProgress->getRealHeight() * 0.5f - WIDTH_SQUARE * 1.4f;
	}
	else
	{
		WIDTH_SQUARE = widthBoard / NUM_COLUMN;
		START_X = size.width * 0.12f;
		START_Y = bgProgress->getPositionY() - bgProgress->getRealHeight() * 0.5f - WIDTH_SQUARE * 1.3f;
	}
	WIDTH_BALL_TWENTY = WIDTH_SQUARE * 0.9f;

	bgDark1 = addImage("bgWhite.png");
	bgDark1->getImg()->setAnchorPoint(Vec2(0, 0));
	bgDark1->getImg()->setColor(Color3B(30, 30, 30));
	bgDark1->setWidth(WIDTH_SQUARE * 7);
	bgDark1->setHeight(WIDTH_SQUARE * 8);
	bgDark1->setPosition(size.width * 0.5f - bgDark1->getRealWidth() * 0.5f, START_Y - 7 * WIDTH_SQUARE);

    border = addImage("border2.png");
    border->setLocalZOrder(3);
    border->setWidth(bgDark1->getRealWidth() + 20);
    border->setHeight(bgDark1->getRealHeight() + 20);
    border->setPosition(size.width * 0.5, START_Y - 7 * WIDTH_SQUARE - 10 + border->getRealHeight() * 0.5);
    border->setColor(Color3B(120, 130, 170));

	currentTouch = new PointGame();
	currentTouch->x = -1;
	for (int i = 0; i < MAX_ROW_TWENTY; i++)
		for (int j = 0; j < MAX_COLUMN_TWENTY; j++) {
			arrayNumber[i][j] = new Number();
			/*arrayNumber[i][j]->setPosition(START_X + (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f
				+ WIDTH_SQUARE * j, START_Y - WIDTH_SQUARE * i
				);*/
			arrayNumber[i][j]->addToParent(this);
			arrayNumber[i][j]->setNumber((int) (GameUtility::getRandom() * 5) + 1);
		}

	LIMIT_Y = START_Y + WIDTH_SQUARE;

	bgDark2 = addImage("bgWhite.png");
	bgDark2->setLocalZOrder(2);
	bgDark2->setWidth(size.width);
	
	bgDark2->setColor(color);

	updateSizeNumber();

	labelAddScore = Text::create("0", "fonts/tahomabd.ttf", 14);
    addChild(labelAddScore);
	//labelHighscoreSum->setScale(1.3f);
//	labelAddScore->setColor(Color3B(50, 50, 50));
	labelAddScore->setLocalZOrder(10);
	labelAddScore->setColor(Color3B(255, 255, 255));
	labelAddScore->setPositionX(labelHighscore->getPositionX());
	labelAddScore->setPositionY(labelScoreSum->getPositionY());
	//WIDTH = size.width * 0.005f;
	countReverse = 0;
	state = GameStateTwenty::PLAY_TWENTY;
	currentRow = 7;
	moveY = -1;
	layerColor = LayerColor::create(Color4B(0, 0, 0, 100), size.width, size.height);
	addChild(layerColor);
	layerColor->setLocalZOrder(1);
	layerColor->setContentSize(size);

	imgNewBest = Sprite::create("GuiGame/iconNewBest.png");
	addChild(imgNewBest);
	imgNewBest->setLocalZOrder(3);

	paperLeft = new Paper(size.width * 0.5, 300, 1, 1);
	addChild(paperLeft);
	paperLeft->setPosition(0, size.height * 0.45);
	paperLeft->startEffect();
	paperLeft->setLocalZOrder(4);

	paperRight = new Paper(size.width * 0.5, 300, -1, 1);
	addChild(paperRight);
	paperRight->setPosition(size.width, size.height * 0.45);
	paperRight->startEffect();
	paperRight->setLocalZOrder(4);


	//starFly = new StarFly(size.width, size.height * 0.6);
	//addChild(starFly);
	//starFly->setPosition(0, size.height * 0.3);
	////starFly->startEffect();
	//starFly->setLocalZOrder(3);

	newNumber = new GroupNumber();
	addChild(newNumber);
	newNumber->setLocalZOrder(3);

	deleteNumber = new GroupNumber();
	addChild(deleteNumber);
	deleteNumber->setLocalZOrder(3);
	deleteNumber->setPosition(size.width * 0.5, size.height * 0.4);

	iconX = Sprite::create("GuiGame/iconX.png");
	deleteNumber->addChild(iconX);
	iconX->setLocalZOrder(2);
	//iconX->setPosition(deleteNumber->ball->getWidth() * 0.5, deleteNumber->ball->getHeight() * 0.5);

	btnOk = addButton(BTN_OK_ID, "btnOk.png");
	btnOk->setPosition(size.width * 0.5, deleteNumber->getPositionY() - deleteNumber->ball->getHeight() * 1.1);
	btnOk->normalImage->setLocalZOrder(3);
	

	//runAction(Sequence::create(DelayTime::create(3.1f), CallFunc::create(this, AX_CALLBACK_0(GUITwenty::initAds)), NULL));
	isInitAds = false;
	arrayLevel.push_back(10);
	arrayLevel.push_back(13);
	arrayLevel.push_back(16);
	arrayLevel.push_back(18);
	arrayLevel.push_back(20);
	arrayLevel.push_back(22);
	arrayLevel.push_back(24);
	arrayLevel.push_back(26);
	arrayLevel.push_back(28);
	arrayLevel.push_back(30);

	/*arrayLevel.push_back(7);
	arrayLevel.push_back(8);
	arrayLevel.push_back(9);
	arrayLevel.push_back(10);*/
}

void GUITwenty::initAds()
{
	
}


void GUITwenty::checkIsNewBest(int add)
{
	if (isNewBest)
		return;
	if (!isNewBest && this->score <= game->highscoreSum && game->highscoreSum > 0 && this->score + add > game->highscoreSum) {
		// show Effect Best Score
		isNewBest = true;
		showEffectLabel("GuiGame/brick/iconNewBest.png");
		GameSound::playWin();
	}
}

void GUITwenty::showEffectLabel(string s)
{
	layerColor->setVisible(false);
	layerColor->setOpacity(0);
	layerColor->runAction(
		Sequence::create(
			FadeTo::create(0.5, 100),
			DelayTime::create(2.5),
			FadeOut::create(0.5),
			Hide::create(),
			NULL
		)
	);
	

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Vec2 pos = Vec2(size.width * 0.5, size.height * 0.6);

	/*DBArmatureNode* eff = DBFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setLocalZOrder(2);
		eff->setPosition(pos);
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->removeFromParent();
		});
	}

	DBArmatureNode* eff1 = DBFactory::getInstance()->buildArmatureNode("cast_skill_vua_le_hoi");
	if (eff1) {
		this->addChild(eff1);
		eff1->setLocalZOrder(2);
		eff1->setPosition(pos.x, pos.y + 50);
		eff1->gotoAndPlay("run", 0.5, -1, 1);
		eff1->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->removeFromParent();
		});
	}*/
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

void GUITwenty::doFall() {
	if (moveY >= 0)
		return;
	bool isFall = false;
	for (int i = 0; i < currentNumber.size(); i++) {
		if (currentNumber.at(i)->isVisible() && currentNumber.at(i)->isFall) {
			isFall = true;
			currentNumber.at(i)->setY(currentNumber.at(i)->getY() - WIDTH_BALL_TWENTY * 0.2f);
			PointGame* p = convertPoint(currentNumber.at(i)->getX() + WIDTH_BALL_TWENTY * 0.5f, currentNumber.at(i)->getY() + WIDTH_BALL_TWENTY * 0.5f);
			if (p->y >= 0) {
				if (p->y + 1 > currentRow || (p->y + 1 < NUM_ROW && p->x >= 0 && p->x < NUM_COLUMN && arrayNumber[p->y + 1][p->x]->isVisible() && arrayNumber[p->y + 1][p->x]->id != currentNumber.at(i)->id)) {
					// dung lai
					if (p->y >= 0 && p->y < NUM_ROW && p->x >= 0 && p->x < NUM_COLUMN) {
						if (arrayNumber[p->y][p->x]->isVisible()) {
							doEat(arrayNumber[p->y][p->x]);
							currentNumber.at(i)->remove();
							if (i < idCurrentNumber) {
								idCurrentNumber--;
							}
							currentNumber.erase(currentNumber.begin() + i);
							i--;

						}
						else {
							arrayNumber[p->y][p->x]->setVisible(true);
							arrayNumber[p->y][p->x]->setNumber(currentNumber.at(i)->id);
							currentNumber.at(i)->remove();
							if (i < idCurrentNumber) {
								idCurrentNumber--;
							}
							currentNumber.erase(currentNumber.begin() + i);
							i--;

							GameSound::playHit();
						}
					}

				}
				else if (p->y >= 0 && p->y < NUM_ROW && p->x >= 0 && p->x < NUM_COLUMN && arrayNumber[p->y][p->x]->isVisible()) {
					arrayNumber[p->y][p->x]->setNumber(arrayNumber[p->y][p->x]->id + 1);
					currentNumber.at(i)->remove();
					if (i < idCurrentNumber) {
						idCurrentNumber--;
					}
					currentNumber.erase(currentNumber.begin() + i);
					i--;
					GameSound::playHit();
				}
			}
			else {
				if (p->y == -1 && p->x >= 0 && p->x < NUM_COLUMN && arrayNumber[0][p->x]->isVisible()) {
					if (arrayNumber[0][p->x]->id == currentNumber.at(i)->id) {
						currentNumber.at(i)->remove();
						currentNumber.erase(currentNumber.begin() + i);
						i--;
						doEat(arrayNumber[0][p->x]);
					}
					else {
						currentRow = currentRow + 1;
						updateBg();
						if (currentRow >= NUM_ROW) {
							endGame();
							return;
						}

						START_Y = bgDark1->getPositionY() + currentRow * WIDTH_SQUARE;
						for (int i1 = currentRow; i1 > 0; i1--) {
							for (int j = 0; j < NUM_COLUMN; j++) {
								arrayNumber[i1][j]->setVisible(arrayNumber[i1 - 1][j]->isVisible());
								arrayNumber[i1][j]->setNumber(arrayNumber[i1 - 1][j]->id);
								arrayNumber[i1][j]->setPosition(arrayNumber[i1 - 1][j]->getX(),
									arrayNumber[i1 - 1][j]->getY());
							}
						}
						for (int j = 0; j < NUM_COLUMN; j++) {
							arrayNumber[0][j]->setVisible(false);
							arrayNumber[0][j]->setPosition(arrayNumber[0][j]->getX(), arrayNumber[0][j]->getY()
								+ WIDTH_SQUARE);
						}
						arrayNumber[0][p->x]->setVisible(true);
						arrayNumber[0][p->x]->setNumber(currentNumber.at(i)->id);
						currentNumber.at(i)->remove();
						if (i < idCurrentNumber) {
							idCurrentNumber--;
						}
						currentNumber.erase(currentNumber.begin() + i);
						i--;
						GameSound::playHit();
					}
				}
			}
		}
	}

	if (isFall) {
		int i;
		for (i = 0; i < currentNumber.size(); i++) {
			if (currentNumber.at(i)->isVisible() && currentNumber.at(i)->isFall)
				break;
		}
		//if (i == currentNumber.size()) {
		if (currentNumber.size() == 0) {
			checkListFall();
		}
	}

}

void okQuit() {
    game->changeToLandscape();
	GUIManager::getInstance().removeAllGui();
	GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
}

void GUITwenty::onBackKey()
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		if (state == PLAY) {
			GUIManager::getInstance().guiDialog->showGUI("Do you want to quit the Game?", okQuit, false, NULL);
			UserDefault::getInstance()->setIntegerForKey("currentRow", currentRow);
			UserDefault::getInstance()->setIntegerForKey("maxNumber", maxNumber);
			UserDefault::getInstance()->setFloatForKey("time", timeProgress);
			UserDefault::getInstance()->setIntegerForKey("saveScore", score);
			for (int i = 0; i <= currentRow; i++)
				for (int j = 0; j < 7; j++) {
					int convert = i * 7 + j;
					if (arrayNumber[i][j]->isVisible())
					{
						UserDefault::getInstance()->setIntegerForKey(("numTwenty" + GameUtility::toString(convert)).c_str(), arrayNumber[i][j]->id);
					}
					else
					{
						UserDefault::getInstance()->setIntegerForKey(("numTwenty" + GameUtility::toString(convert)).c_str(), -1);
					}
				}
			UserDefault::getInstance()->flush();
		}
		else {
                    game->changeToLandscape();
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
		}
		GUIManager::getInstance().isCallBackPress = true;
	}
	
}

void GUITwenty::update()
{
	if(state == GameStateTwenty::PLAY_TWENTY || state == GameStateTwenty::NEXT_NUMBER_TWENTY)
	{
		if (moveY >= 0) {
			moveY = moveY + WIDTH_SQUARE / 20;
			if (moveY >= WIDTH_SQUARE) {
				moveY = -1;
				START_Y = bgDark1->getPositionY() + currentRow * WIDTH_SQUARE;
			}
			else {
				START_Y = START_Y + WIDTH_SQUARE / 20;
			}
			
			for (int i = 0; i < NUM_ROW; i++)
				for (int j = 0; j < NUM_COLUMN; j++) {
					arrayNumber[i][j]->setPosition(START_X + (WIDTH_SQUARE - WIDTH_BALL_TWENTY)
						* 0.5f + WIDTH_SQUARE * j, START_Y - WIDTH_SQUARE * i + (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f
						);
				}

				if (idCurrentNumber >= 0) {
					if (currentNumber.at(idCurrentNumber)->getY() + WIDTH_SQUARE / 20 > bgDark1->getPositionY()
						+ bgDark1->getRealHeight() - WIDTH_SQUARE) {
							currentNumber.at(idCurrentNumber)->setY(bgDark1->getPositionY()
								+ bgDark1->getRealHeight() - WIDTH_SQUARE);
							return;
					} else {
						currentNumber.at(idCurrentNumber)->setY(
							currentNumber.at(idCurrentNumber)->getY() + WIDTH_SQUARE / 20);
					}

				}
		}

		doFall();
		
	}

	if (state == GameStateTwenty::PLAY_TWENTY)
        {
		currentTime = currentTime - game->deltaTime;
		if (currentTime <= 0) {
			genRow();
		}
		else {
			Size size = Director::getInstance()->getRenderView()->getVisibleSize();
			float rate = currentTime / timeProgress;
			//progress->setWidth(size.width * rate);
            progress->setPercentage(rate * 100);
		}
	}

	for (int i = 0; i < arrayImageEffect.size(); i++) {
		if (arrayImageEffect.at(i)->isVisible()) {
			arrayImageEffect.at(i)->updateCoin(game->deltaTime);
		}
	}
}


void GUITwenty::onTouchEnded( Touch *pTouch, Event *pEvent )
{
	BaseGUI::onTouchEnded(pTouch, pEvent);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	
	if (state == PLAY) {
		if (idCurrentNumber >= 0) {
			Number* number = currentNumber.at(idCurrentNumber);

			PointGame* currentPoint = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY()
				+ WIDTH_BALL_TWENTY * 0.5f);
			AXLOGD("CURRENT POINT *** %i ", currentPoint->y);
			if (currentPoint->y >= 0 && currentPoint->y < NUM_ROW && currentPoint->x < NUM_COLUMN) {
				arrayNumber[currentPoint->y][currentPoint->x]->setVisible(true);
				arrayNumber[currentPoint->y][currentPoint->x]->setNumber(number->id);
				number->setVisible(false);
				number->isFall = false;
				idCurrentNumber = -1;
			} else {
				number->setX(arrayNumber[0][currentPoint->x]->getX());
				number->setY(number->getY() + WIDTH_BALL_TWENTY * 0.3f);
				idCurrentNumber = -1;

			}
			checkListFall();

		}

		UserDefault::getInstance()->setIntegerForKey("currentRow", currentRow);
		UserDefault::getInstance()->setIntegerForKey("maxNumber", maxNumber);
		UserDefault::getInstance()->setFloatForKey("time", timeProgress);
		UserDefault::getInstance()->setIntegerForKey("saveScore", score);
		for (int i = 0; i <= currentRow; i++)
			for (int j = 0; j < 7; j++) {
				int convert = i * 7 + j;
				if (arrayNumber[i][j]->isVisible())
				{
					UserDefault::getInstance()->setIntegerForKey(("numTwenty" + GameUtility::toString(convert)).c_str(), arrayNumber[i][j]->id);
				}
				else
				{
					UserDefault::getInstance()->setIntegerForKey(("numTwenty" + GameUtility::toString(convert)).c_str(), -1);
				}
			}
		UserDefault::getInstance()->flush();
	}
}

void GUITwenty::playParticle( float posX, float posY, Color3B color, int id)
{
	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	ParticleEffect *effect = new ParticleEffect();
	effect->create("particles/particle_texture.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
	effect->particle->setPosition(posX, posY);
	effect->particle->setBlendAdditive(true);
    Color3B c1 = GameUtility::getColorTwenty(id);
    Color4F color1 = Color4F(c1);
	color1.a = 0;
	Color4F color2 = Color4F(c1);
//	color2.a = 1;
	//color2.r = 255;
	//color2.g = 255;
	//color2.b = 255;
	effect->particle->setStartColor(color1);
	effect->particle->setStartColorVar(Color4F(0, 0, 0, 0));
	effect->particle->setEndColor(color2);
	effect->particle->setEndColorVar(Color4F(0, 0, 0, 0));
	effect->particle->setAutoRemoveOnFinish(true);
    string s = "GuiGame/Merge/" + GameUtility::toString(id % 25) + ".png";
    effect->particle->setTexture(Director::getInstance()->getTextureCache()->addImage(s.c_str()));


	ParticleEffect *effectStar = new ParticleEffect();
	effectStar->create("particles/smallStar.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
	effectStar->particle->setPosition(posX, posY);
	effectStar->particle->setBlendAdditive(true);
	//ccColor color1 = ccc4FFromColor4BB(color);
	//color1.a = 0;
	//ccColor color2 = ccc4FFromColor4BB(color);
	//	color2.a = 1;
		//color2.r = 255;
		//color2.g = 255;
		//color2.b = 255;
	color1.a = 1;
	//color1.r = 255;
	//color2.r = 255;
	effectStar->particle->setStartColor(color1);
	effectStar->particle->setStartColorVar(Color4F(0, 0, 0, 0));
	effectStar->particle->setEndColor(color2);
	effectStar->particle->setEndColorVar(Color4F(0, 0, 0, 0));
	effect->particle->setAutoRemoveOnFinish(true);
	
	Sprite* iconSmoke = getSmoke();
	iconSmoke->setScale(0);
	iconSmoke->setOpacity(0);
	iconSmoke->setPosition(posX, posY - WIDTH_BALL_TWENTY * 0.5);
	float rate = WIDTH_SQUARE * 1.6 / iconSmoke->getContentSize().width;
   // ax::Blendfa
        
	iconSmoke->setBlendFunc(BlendFunc{backend::BlendFactor::DST_COLOR, backend::BlendFactor::ONE});
	iconSmoke->runAction(
		Sequence::create(
            DelayTime::create(0.05),
			Spawn::create(
				EaseBackOut::create(ScaleTo::create(0.3, rate)),
				FadeTo::create(0.3, 250),
				EaseBackOut::create(MoveBy::create(0.3, Vec2(0, 50))),
                NULL
			),
			FadeOut::create(0.6),
			Hide::create(),
            NULL
		)
	);
	iconSmoke->setColor(GameUtility::getColorTwenty(id));
}

void GUITwenty::updateScore()
{
	//labelScore->setString(("Number: " + GameUtility::toString(maxNumber)).c_str());
	curNumber->setNumber(maxNumber);
	if(maxNumber > game->highscore)
	{
		game->highscore = maxNumber;
		labelHighscore->setString(("Best: " + GameUtility::toString(maxNumber)).c_str());
		UserDefault::getInstance()->setIntegerForKey("highscore", game->highscore);
		UserDefault::getInstance()->flush();
	}
}

void GUITwenty::updateScoreSum()
{
	labelScoreSum->setString(("" + GameUtility::standardizeNumber(score)).c_str());
	if(score > game->highscoreSum)
	{
		game->highscoreSum = score;
		labelHighscoreSum->setString(("" + GameUtility::standardizeNumber(score)).c_str());
		UserDefault::getInstance()->setIntegerForKey("highscoreSum", game->highscoreSum);
		UserDefault::getInstance()->flush();
	}
}

void GUITwenty::onButtonRelease(int buttonID, Touch* touch)
{
	GameSound::playClick();
	switch (buttonID)
	{
	case BTN_TOP_ID:
	{
		//showNewNumber(arrayNumber[0][0]);
        JNIUtils::submitScore(GAME_TWENTY, game->highscoreSum);
	}

	break;
	case BTN_BACK_ID:
		{
			onBackKey();
		/*arrayNumber[2][4]->setVisible(false);
		checkListFall();*/
		}

		break;
	case BTN_SOUND_ID:
		{
		
		//tutorial1();
		//curNumber->increaseNumber();
		//showEffectLabel("GuiGame/brick/iconNewBest.png");
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
	case BTN_PLAY_ID:
		{
			state = GameStateTwenty::PLAY_TWENTY;
			btnPlay->setVisible(false);
		}
		break;
	case BTN_PAUSE_ID:
		{
			onPause();
		}
		break;
	case BTN_OK_ID:
	{
		hideNewNumber();
	}
	break;
	default:
		break;
	}
}


void GUITwenty::endGame()
{
	for (int i = 0; i < NUM_ROW; i++)
		for (int j = 0; j < NUM_COLUMN; j++) {
			if (arrayNumber[i][j]->isVisible())
				arrayNumber[i][j]->effectEndGame();
		}
	state = GameStateTwenty::END_TWENTY;
    UserDefault::getInstance()->setIntegerForKey("currentRow", -1);
    UserDefault::getInstance()->flush();
	
	runAction(Sequence::create(
		DelayTime::create(1.0),
		CallFunc::create(AX_CALLBACK_0(GUITwenty::callbackEffectEndGame, this)),
		NULL
	));
	JNIUtils::sendEvent("max_number", GameUtility::toString(maxNumber).c_str());
}



void GUITwenty::callbackEffectEndGame()
{
	for (int i = 0; i < NUM_ROW; i++)
		for (int j = 0; j < NUM_COLUMN; j++) {
			arrayNumber[i][j]->setVisible(false);
			arrayNumber[i][j]->stopAllActions();
			/*if (GameUtility::getRandom() > 0.7) {
				showParticle(arrayBall[i][j]->getPositionX(), arrayBall[i][j]->getPositionY(), board->arrayBall[i][j], 0);
			}*/
			effectImage(arrayNumber[i][j]);
		}
	runAction(Sequence::create(
		DelayTime::create(1.0),
		CallFunc::create(AX_CALLBACK_0(GUITwenty::callbackEffectEndGame1, this)),
		NULL
	));
}


void GUITwenty::effectImage(Number* ball)
{
	ImageEffect* image = NULL;
	for (int i = 0; i < arrayImageEffect.size(); i++) {
		if (!arrayImageEffect.at(i)->isVisible()) {
			image = arrayImageEffect.at(i);
			break;
		}
	}
	if (image == NULL) {
		image = ImageEffect::create();
		this->addChild(image);
		arrayImageEffect.push_back(image);
	}
	image->setTexture("GuiGame/Merge/" + GameUtility::toString(ball->id % 10) + ".png");
	image->setVisible(true);
	image->setOpacity(255);
	image->setColor(ball->ball->getImg()->getColor());
	//image->setScale(ball->rootScaleX * 1.1);
	//image->setTexture("GuiGame/bgNumber.png");
	image->initCoin(ImageEffect::TYPE_FLOW, 0, ball->x, ball->y);
	image->setScale(ball->ball->getScaleX());
}

void GUITwenty::callbackEffectEndGame1()
{
	GUIManager::getInstance().guiResult->showGUI(score, game->highscoreSum);
}

void GUITwenty::onPause()
{
	
}

void GUITwenty::newGame()
{
//	starFly->setVisible(false);
	newNumber->setVisible(false);
	paperLeft->setVisible(false);
	paperRight->setVisible(false);
	deleteNumber->setVisible(false);
	btnOk->setVisible(false);
	isNewBest = false;
	imgNewBest->setVisible(false);
	layerColor->setVisible(false);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	score = 0;
	tutorialLabel->setVisible(false);
	idCurrentNumber = -1;
	moveY = -1;
	state = GameStateTwenty::PLAY_TWENTY;
	timeAds = 0;
    progress->setPercentage(0);
	//progress.startTime(10);
	//progress->cleanup();
	//progress->setWidth(size.width);
	runAction(Sequence::create(DelayTime::create(10),CallFunc::create(AX_CALLBACK_0(GUITwenty::genRow, this)), NULL));
	//progress->runAction(ScaleTo::create(10, 0, progress->getScaleY()));
	currentRow = 1;
	START_Y = bgDark1->getPositionY() + currentRow * WIDTH_SQUARE;
	maxNumber = 5;
	updateScore();
	updateScoreSum();
	NUM_ROW = 8;
	NUM_COLUMN = 7;
	//updateSizeNumber();
	labelAddScore->setVisible(false);
	for (int i = 0; i < MAX_ROW_TWENTY; i++) {
		for (int j = 0; j < MAX_COLUMN_TWENTY; j++) {
			arrayNumber[i][j]->setVisible(false);
		}
	}

	for (int i = 0; i <= currentRow; i++) {
		for (int j = 0; j < NUM_COLUMN; j++) {
			if (i == 0) {
				arrayNumber[i][j]->setNumber((int) (GameUtility::getRandom() * (maxNumber - 2) + 1));
			} else {
				int id = 0;
				do {
					id = (int) (GameUtility::getRandom() * (maxNumber - 2) + 1);
				} while (id == arrayNumber[i - 1][j]->id);
				arrayNumber[i][j]->setNumber(id);

			}
			arrayNumber[i][j]->setVisible(true);
			arrayNumber[i][j]->setPosition(START_X + (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f
				+ WIDTH_SQUARE * j, START_Y - WIDTH_SQUARE * i
				+ (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f);
			//arrayNumber[i][j]->effectNewGame();
		}
	}

	for (int i = 0; i < currentNumber.size(); i++) {
		currentNumber.at(i)->remove();
		//currentNumber.at(i)->isFall = false;
	}
	currentNumber.clear();
  //  timeProgress = 12;
	updateBg();
}

void GUITwenty::newGame(int maxNumber, int row, int data[8][7], int saveScore)
{
	for (int i = 0; i < arraySmoke.size(); i++) {
		arraySmoke.at(i)->setVisible(false);
	}
	//starFly->setVisible(false);
	newNumber->setVisible(false);
	paperLeft->setVisible(false);
	paperRight->setVisible(false);
	deleteNumber->setVisible(false);
	btnOk->setVisible(false);
	isNewBest = false;
	imgNewBest->setVisible(false);
	layerColor->setVisible(false);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	this->maxNumber = maxNumber;
	this->score = saveScore;
	if (saveScore == game->highscoreSum) {
		isNewBest = true;
	}
	updateScore();
	updateScoreSum();
	labelAddScore->setVisible(false);
	//tutorialLabel->setVisible(false);
	idCurrentNumber = -1;
	moveY = -1;
	state = GameStateTwenty::PLAY_TWENTY;
    timeAds = 0;
	//progress.startTime(10);
    progress->setPercentage(0);
	//progress->setWidth(size.width);
	runAction(Sequence::create(DelayTime::create(timeProgress),CallFunc::create(AX_CALLBACK_0(GUITwenty::genRow, this)), NULL));
	currentRow = row;
	START_Y = bgDark1->getPositionY() + currentRow * WIDTH_SQUARE;
	this->maxNumber = maxNumber;

	for (int i = 0; i < MAX_ROW_TWENTY; i++) {
		for (int j = 0; j < MAX_COLUMN_TWENTY; j++) {
			arrayNumber[i][j]->setVisible(false);
		}
	}

	for (int i = 0; i <= currentRow; i++) {
		for (int j = 0; j < NUM_COLUMN; j++) {
			arrayNumber[i][j]->setVisible(true);
			arrayNumber[i][j]->setPosition(START_X + (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f
				+ WIDTH_SQUARE * j, START_Y - WIDTH_SQUARE * i
				+ (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f);

			if (data[i][j] >= 0) {
				arrayNumber[i][j]->setNumber(data[i][j]);
				arrayNumber[i][j]->setVisible(true);
				arrayNumber[i][j]->effectNewGame();
			} else {
				arrayNumber[i][j]->setVisible(false);
			}
		}
	}

	for (int i = 0; i < currentNumber.size(); i++) {
		currentNumber.at(i)->remove();
	}
	currentNumber.clear();
}

void GUITwenty::onTouchMoved( Touch*touch, Event* event )
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	float screenX = touch->getLocation().x;
	if (state == PLAY) {
		int convertY = touch->getLocation().y;
		if(convertY < START_Y - currentRow * WIDTH_SQUARE + WIDTH_BALL_TWENTY * 0.5f)
			convertY = (int)(START_Y - currentRow * WIDTH_SQUARE + WIDTH_BALL_TWENTY * 0.5f) + 1;
		if (touch->getLocation().x > START_X + WIDTH_BALL_TWENTY * 0.5f
			&& touch->getLocation().x < WIDTH_SQUARE * 7 - WIDTH_BALL_TWENTY * 0.5f + START_X
			&& convertY > START_Y - currentRow * WIDTH_SQUARE + WIDTH_BALL_TWENTY * 0.5f
			&& convertY < LIMIT_Y) {
				if (idCurrentNumber >= 0) {

					// kiem tra xem quang duong di chuyen tu cho number hien tai
					// den
					// cho move co vuong gi ko
					Number* number = currentNumber.at(idCurrentNumber);
					float dx = touch->getLocation().x - number->getX() - WIDTH_BALL_TWENTY * 0.5f;
					float dy = convertY - number->getY() - WIDTH_BALL_TWENTY * 0.5f;

					double d = sqrt(dx * dx + dy * dy);
					PointGame* oldPoint = new PointGame();
					int i;
					float moveX = 0, moveY = 0;
					float newMoveX = 0;
					float newMoveY = 0;

					float oldX = number->getX();
					float oldY = number->getY();
					float dMoveX = dx / 10;
					float oldMoveX = 0;
					float oldMoveY = 0;
					if (fabs(dMoveX) > WIDTH_SQUARE * 0.4f) {
						dMoveX = WIDTH_SQUARE * 0.4f * (dx > 0 ? 1 : -1);
					}

					oldPoint = convertPoint(oldX + WIDTH_BALL_TWENTY * 0.5f, oldY + WIDTH_BALL_TWENTY * 0.5f);
					PointGame* newPoint = convertPoint(screenX, convertY);
					for (i = 0;; i++) {
						oldMoveX = moveX;
						oldMoveY = moveY;
						moveX = i * dMoveX;
						moveY = fabs(moveX / dx) * dy;
						// moveX = i * dx / 10;
						// moveY = i * dy / 10;

						bool canBreak = false;
						if (fabs(moveX) >= fabs(dx) || fabs(moveY) >= fabs(dy)) {
							moveX = dx;
							moveY = dy;
							canBreak = true;
						}

						newPoint = convertPoint(number->getX() + moveX + WIDTH_BALL_TWENTY * 0.5f, number->getY()
							+ moveY + WIDTH_BALL_TWENTY * 0.5f);
						// Log.println("NEW POINT " + newPoint.x + "  " +
						// newPoint.y + " OLD POINT " + oldPoint->x + " "
						// + oldPoint->y);
						if (checkCanMove(newPoint, oldPoint)
							&& newPoint->x < NUM_COLUMN
							&& newPoint->x >= 0 && newPoint->y < NUM_ROW
							&& (newPoint->y < 0 || !arrayNumber[newPoint->y][newPoint->x]->isVisible() || arrayNumber[newPoint->y][newPoint->x]->id == number->id)) {
								// co the di chuyen duoc nen tiep tuc di
								if (canBreak) {
									number->setPosition(number->getX() + moveX, number->getY() + moveY);
									newPoint = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY()
										+ WIDTH_BALL_TWENTY * 0.5f);
								}
								else
								{
									if((newPoint->x != oldPoint->x || newPoint->y != oldPoint->y) 
										&& newPoint->y >= 0 && arrayNumber[newPoint->y][newPoint->x]->isVisible() && arrayNumber[newPoint->y][newPoint->x]->id == number->id)
									{
										number->setVisible(false);
										//arrayNumber[newPoint->y][newPoint->x]->setNumber(number->id + 1);
										doEat(arrayNumber[newPoint->y][newPoint->x]);
										idCurrentNumber = -1;
										canBreak = true;
										checkListFall();
										break;
									}
								}
						} else {
							// khong the di khoi diem nay, dung o
							canBreak = true;
							// tim diem dung, check diem dung theo truc x
							float x, y;
							if (newPoint->x > oldPoint->x) {
								x = WIDTH_SQUARE * (newPoint->x - 0.01f);
								y = fabs((x - number->getX() - WIDTH_BALL_TWENTY * 0.5f) / dx) * dy
									+ number->getY() + WIDTH_BALL_TWENTY * 0.5f;

							} else if (newPoint->x < oldPoint->x) {
								x = WIDTH_SQUARE * (newPoint->x + 1.01f);
								y = fabs((x - number->getX() - WIDTH_BALL_TWENTY * 0.5f) / dx) * dy
									+ number->getY() + WIDTH_BALL_TWENTY * 0.5f;

							} else if (newPoint->y > oldPoint->y) {
								y = START_Y - WIDTH_SQUARE * (newPoint->y - 1.01f);
								x = fabs((y - number->getY() - WIDTH_BALL_TWENTY * 0.5f) / dy) * dx
									+ number->getX() + WIDTH_BALL_TWENTY * 0.5f;

							} else {
								y = START_Y - WIDTH_SQUARE * (newPoint->y + 0.01f);
								x = fabs((y - number->getY() - WIDTH_BALL_TWENTY * 0.5f) / dy) * dx
									+ number->getX() + WIDTH_BALL_TWENTY * 0.5f;

							}

							newPoint = convertPoint(x, y);
							if ((newPoint->x != oldPoint->x && newPoint->y != oldPoint->y)
								|| (newPoint->y >= 0 && newPoint->x >= 0 && newPoint->x < NUM_COLUMN && newPoint->y < NUM_ROW
								&& arrayNumber[newPoint->y][newPoint->x]->isVisible() && arrayNumber[newPoint->y][newPoint->x]->id != number->id)) {
									number->setPosition(number->getX() + oldMoveX, number->getY() + oldMoveY);
									newPoint = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY()
										+ WIDTH_BALL_TWENTY * 0.5f);
							} else {
								number->setPosition(x - WIDTH_BALL_TWENTY * 0.5f, y - WIDTH_BALL_TWENTY * 0.5f);

							}
						}

						if (canBreak) {
							// Log.println("NEW POINT " + newPoint->x + "  " +
							// newPoint->y + " OLD POINT " + oldPoint->x + " " +
							// oldPoint->y);
							if (newPoint->x != oldPoint->x || newPoint->y != oldPoint->y) {
								checkEat(number);
								checkListFall();
							}
							break;
						}
					}

				}

		}
	}
}

bool GUITwenty::onTouchBegan( Touch*touch, Event* event )
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	float screenX = touch->getLocation().x;
	if (state == PLAY) {
		if(idCurrentNumber < 0)
		{
			int convertY = touch->getLocation().y;

			idCurrentNumber = -1;
			for (int i = 0; i < currentNumber.size(); i++) {
				Number* number = currentNumber.at(i);
				if (number->isVisible() && number->getX() <= screenX && number->getX() + number->getWidth() >= screenX
					&& number->getY() <= convertY && number->getY() + number->getHeight() >= convertY) {
						// cham vao khoi hop hien tai
						idCurrentNumber = i;
						number->isFall = false;
						//GameSound::playHit();
						break;
				}
			}

			if (idCurrentNumber == -1) {
				currentTouch = convertPoint(screenX, convertY);

				if (currentTouch->y < NUM_ROW && currentTouch->y >= 0 && currentTouch->x >= 0 && currentTouch->x < NUM_COLUMN) {
					if (arrayNumber[currentTouch->y][currentTouch->x]->isVisible()) {
						int i;
						for (i = 0; i < currentNumber.size(); i++) {
							if (!currentNumber.at(i)->isVisible()) {
								break;
							}
						}
						Number* number;
						//GameSound::playHit();
						if (i == currentNumber.size()) {
							number = new Number();
							number->addToParent(this);
							currentNumber.push_back(number);
							idCurrentNumber = currentNumber.size() - 1;
						} else {
							number = currentNumber.at(i);
							idCurrentNumber = i;
						}
						number->setVisible(true);
						number->isFall = false;
						number->setNumber(arrayNumber[currentTouch->y][currentTouch->x]->id);
						arrayNumber[currentTouch->y][currentTouch->x]->setVisible(false);
						number->setPosition(arrayNumber[currentTouch->y][currentTouch->x]->getX(),
							arrayNumber[currentTouch->y][currentTouch->x]->getY());

						getFirstVisible();
					}
				}

			}
		}
		else
		{
			Number* number = currentNumber.at(idCurrentNumber);

			PointGame* currentPoint = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY()
				+ WIDTH_BALL_TWENTY * 0.5f);
			if (currentPoint->y >= 0) {
				arrayNumber[currentPoint->y][currentPoint->x]->setVisible(true);
				arrayNumber[currentPoint->y][currentPoint->x]->setNumber(number->id);
				number->setVisible(false);
				number->isFall = false;
				idCurrentNumber = -1;
			} else {
				number->setX(arrayNumber[0][currentPoint->x]->getX());
				number->setY(number->getY() + WIDTH_BALL_TWENTY * 0.3f);
				idCurrentNumber = -1;

			}
			checkListFall();
		}
	}
	return BaseGUI::onTouchBegan(touch, event);
}

void GUITwenty::checkFall(Number* number, PointGame* oldPoint) {
	// TODO Auto-generated method stub

	PointGame* currentPoint = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY()
		+ WIDTH_BALL_TWENTY * 0.5f);
	if (currentPoint->x != oldPoint->x || currentPoint->y != oldPoint->y) {
		// number o cu se tu dong roi xuong
		makelistFall(oldPoint);
	}

	if (currentPoint->y + 1 < NUM_ROW && arrayNumber[currentPoint->y + 1][currentPoint->x]->isVisible()
		&& arrayNumber[currentPoint->y][currentPoint->x]->id == arrayNumber[currentPoint->y + 1][currentPoint->x]->id) {
			makelistFall(currentPoint);
	}
}
void GUITwenty::makelistFall(PointGame* oldPoint) {
	for (int i = 0;; i++) {
		if (oldPoint->y - i < 0)
			break;
		if (!arrayNumber[oldPoint->y - i][oldPoint->x]->isVisible() && i != 0)
			break;
		if (arrayNumber[oldPoint->y - i][oldPoint->x]->isVisible()) {
			int j;
			Number* n = NULL;
			for (j = 0; j < currentNumber.size(); j++) {
				if (!currentNumber.at(j)->isVisible()) {

					n = currentNumber.at(j);
					break;
				}
			}

			if (j == currentNumber.size()) {
				n = new Number();
				n->addToParent(this);
				currentNumber.push_back(n);
				AXLOGD("SIze current number %i " , currentNumber.size());
			}
			n->setPosition(arrayNumber[oldPoint->y - i][oldPoint->x]->getX(),
				arrayNumber[oldPoint->y - i][oldPoint->x]->getY());
			n->setNumber(arrayNumber[oldPoint->y - i][oldPoint->x]->id);
			arrayNumber[oldPoint->y - i][oldPoint->x]->setVisible(false);
			n->isFall = true;
			n->setVisible(true);
		}
	}
}

PointGame* GUITwenty::convertPoint(float x, float y) {
	PointGame* currentTouch = new PointGame();
	currentTouch->x = (int) ((x - START_X) / WIDTH_SQUARE);
	currentTouch->y = (int) floor(((START_Y + WIDTH_SQUARE - y) / WIDTH_SQUARE));
	return currentTouch;
}

PointGame* GUITwenty::checkNotMove(Point center, int id) {
	// if(center.y > START_Y + WIDTH_SQUARE * )

	float posX, posY;
	posX = center.x - WIDTH_BALL_TWENTY * 0.5f;
	posY = center.y + WIDTH_BALL_TWENTY * 0.5f;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {

			posX = center.x + (i * 2 - 1) * WIDTH_BALL_TWENTY * 0.5f;
			posY = center.y + (j * 2 - 1) * WIDTH_BALL_TWENTY * 0.5f;

			PointGame* pointCheck = convertPoint(posX, posY);
			if (pointCheck->x >= 0 && pointCheck->y >= 0 && pointCheck->x < NUM_COLUMN) {
				if (pointCheck->y < NUM_ROW && pointCheck->y >= 0 && arrayNumber[pointCheck->y][pointCheck->x]->isVisible()
					&& arrayNumber[pointCheck->y][pointCheck->x]->id != id) {
						return pointCheck;
				}
			}
		}

		return NULL;
}
void GUITwenty::checkEat(Number* number) {
	PointGame* point = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f,
		WIDTH_BALL_TWENTY * 0.5f + number->getY());
	if (point->y >= 0 && point->y < NUM_ROW && point->x >= 0 && point->x < NUM_COLUMN && arrayNumber[point->y][point->x]->isVisible()
		&& arrayNumber[point->y][point->x]->id == number->id) {
			doEat(arrayNumber[point->y][point->x]);
			number->setVisible(false);
			idCurrentNumber = -1;
	}
}
void GUITwenty::doEat(Number* number) {
	//showParticle(number);
	
	checkIsNewBest(number->id * 2);
	score = score + number->id * 2;
	updateScoreSum();
	labelAddScore->setVisible(true);
	labelAddScore->setString((GameUtility::toString(number->id * 2)).c_str());
	labelAddScore->setPosition(Vec2(number->getX() + number->getWidth() * 0.5f, number->getY() + number->getHeight() * 0.5f));
	labelAddScore->setOpacity(255);
	labelAddScore->cleanup();
	labelAddScore->runAction(Spawn::create(FadeOut::create(2.5f), EaseBackOut::create(MoveBy::create(0.6f, Vec2(0, 80))), NULL));

	number->setNumber(number->id + 1);
	playParticle(number->getX() + number->getWidth() * 0.5f, number->getY() + number->getHeight() * 0.5f, number->ball->getImg()->getColor(), number->id);
	number->effectEat();
	GameSound::playEat();
	if (number->id > maxNumber) {
		maxNumber = maxNumber + 1;
		curNumber->increaseNumber();
		//updateScore();
		GameSound::playUpNumber();

		/*DBArmatureNode* eff1 = DBFactory::getInstance()->buildArmatureNode("bom_change");
		if (eff1) {
			this->addChild(eff1);
			eff1->setLocalZOrder(2);
			eff1->setPosition(curNumber->getPositionX(), curNumber->getPositionY() - 30);
			eff1->gotoAndPlay("run", 0.5, -1, 1);
			eff1->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
				armature->removeFromParent();
			});
		}*/
		int level = -1;
		for (int i = 0; i < arrayLevel.size(); i++) {
			if (arrayLevel[i] == maxNumber) {
				level = i;
				break;
			}
		}
		if (level >= 0) {
			
			/*runAction(Sequence::create(
				DelayTime::create(1.0),
				CallFunc::create(this, AX_CALLBACK_0(GUITwenty::showNextNumber)),
				NULL
			));*/
			showNewNumber(number);
		}
	}
	checkGenRow();
	//effectStar(number);
	JNIUtils::vibrate(10);
   // Device::vibrate(10);
}
bool GUITwenty::setPosNumber(Number* number, float posX, float posY) {
	if (!(posX > START_X + WIDTH_BALL_TWENTY * 0.5f
		&& posX < WIDTH_SQUARE * NUM_COLUMN - WIDTH_BALL_TWENTY * 0.5f + START_X && posX > START_Y
		- NUM_COLUMN * WIDTH_SQUARE + WIDTH_BALL_TWENTY * 0.5f)) {
			return false;
	}
	float oldX, oldY;
	oldX = number->getX();
	oldY = number->getY();
	number->setPosition(posX, posY);
	
	checkEat(number);

	return true;
}

void GUITwenty::setPos(Number* number, float posX, float posY) {
	if (!(posX > START_X + WIDTH_BALL_TWENTY * 0.5f
		&& posX < WIDTH_SQUARE * NUM_COLUMN - WIDTH_BALL_TWENTY * 0.5f + START_X && posX > START_Y
		- NUM_COLUMN * WIDTH_SQUARE + WIDTH_BALL_TWENTY * 0.5f)) {
			return;
	}
	number->setPosition(posX, posY);
	checkEat(number);
}

vector<Number*> GUITwenty::getListTouch(Number* number) {
	vector<Number*> arrayN ;

	float posX, posY;
	Point center = Point(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY() + WIDTH_BALL_TWENTY* 0.5f);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {

			posX = center.x + (i * 2 - 1) * WIDTH_BALL_TWENTY * 0.5f;
			posY = center.y + (j * 2 - 1) * WIDTH_BALL_TWENTY * 0.5f;

			PointGame* pointCheck = convertPoint(posX, posY);
			if (pointCheck->x >= 0 && pointCheck->y >= 0 && pointCheck->x < NUM_COLUMN) {
				if (pointCheck->y < NUM_ROW && pointCheck->y >= 0 && arrayNumber[pointCheck->y][pointCheck->x]->isVisible()
					&& arrayNumber[pointCheck->y][pointCheck->x]->id != number->id) {
						arrayN.push_back(arrayNumber[pointCheck->y][pointCheck->x]);
				}
			}
		}

		return arrayN;
}

void GUITwenty::checkListFall() {
	for (int i = 0; i < currentNumber.size(); i++) {
		if (i != idCurrentNumber && currentNumber.at(i)->isVisible() && !currentNumber.at(i)->isFall) {
			PointGame* p = convertPoint(currentNumber.at(i)->getX() + WIDTH_BALL_TWENTY * 0.5f, currentNumber.at(i)
				->getY() + WIDTH_BALL_TWENTY * 0.5f);
			if (p->x < 0 || p->x >= NUM_ROW || p->y >= NUM_COLUMN || p->y < 0 || !arrayNumber[p->y][p->x]->isVisible()) {
				currentNumber.at(i)->isFall = true;
				// printCurrent();
			}
		}
	}

	checkListFall1();
}

void GUITwenty::checkListFall1() {
	if (currentRow < 0 || currentRow > NUM_ROW - 1)
		return;
	bool arrayFall[7];
	for (int i = 0; i < 7; i++)
		arrayFall[i] = false;
	bool makeFall = false;
	for (int i = currentRow; i >= 0; i--) {
		for (int j = 0; j < NUM_COLUMN; j++) {
			if (arrayFall[j] == false) {
				if (arrayNumber[i][j]->isVisible()) {
					if (i - 1 >= 0 && arrayNumber[i - 1][j]->isVisible() && arrayNumber[i][j]->isVisible()
						&& arrayNumber[i - 1][j]->id == arrayNumber[i][j]->id) {
						// roi tai day
						makelistFall(new PointGame(j, i - 1));
						arrayFall[j] = true;
						makeFall = true;
					}
				}
				else {
					if (i - 1 >= 0 && arrayNumber[i - 1][j]->isVisible()) {
						makelistFall(new PointGame(j, i - 1));
						arrayFall[j] = true;
						makeFall = true;
					}
				}
			}
		}
	}

	if (makeFall) {
		getFirstVisible();
	}
	doFall();
}


int GUITwenty::getFirstVisible() {
	int row = 0;
	for (int i = 0; i < NUM_ROW; i++) {
		int j;
		for (j = 0; j < NUM_COLUMN; j++) {
			if (arrayNumber[i][j]->isVisible()) {
				break;
			}
		}
		if (j != NUM_COLUMN) {
			row = i;
			break;
		}
	}
	if (row != 0) {
		for (int i = row; i <= currentRow; i++) {
			for (int j = 0; j < NUM_COLUMN; j++) {
				arrayNumber[i - row][j]->setVisible(arrayNumber[i][j]->isVisible());
				arrayNumber[i - row][j]->setPosition(arrayNumber[i][j]->getX(), arrayNumber[i][j]->getY());
				if (arrayNumber[i][j]->isVisible()) {
					arrayNumber[i - row][j]->setNumber(arrayNumber[i][j]->id);
				}
			}
		}
		currentRow = currentRow - row;
		updateBg();
		START_Y = bgDark1->getPositionY() + currentRow * WIDTH_SQUARE;
		for (int i = currentRow + 1; i < NUM_ROW; i++) {
			for (int j = 0; j < NUM_COLUMN; j++) {
				arrayNumber[i][j]->setVisible(false);

			}
		}
	}
	return 0;
}

bool GUITwenty::checkCanMove(PointGame* newPoint, PointGame* oldPoint) {
	// Log.println("CHECK OR DAY NEW POInt " + newPoint->x + " " + newPoint->y
	// + " OLD POINT " + oldPoint->x + " "
	// + oldPoint->y);
	if (newPoint->x != oldPoint->x && newPoint->y != oldPoint->y) {
		if (newPoint->x > oldPoint->x && newPoint->y > oldPoint->y) {

			if ((oldPoint->y + 1 < 0 || oldPoint->y + 1 > currentRow || !arrayNumber[oldPoint->y + 1][oldPoint->x]
			->isVisible())
				&& (oldPoint->y < 0 || oldPoint->x + 1 > 6 || !arrayNumber[oldPoint->y][oldPoint->x + 1]
			->isVisible()))
				return true;
			return false;
		} else if (newPoint->x > oldPoint->x && newPoint->y < oldPoint->y) {
			if ((oldPoint->y - 1 < 0 || !arrayNumber[oldPoint->y - 1][oldPoint->x]->isVisible())
				&& (oldPoint->y < 0 || oldPoint->x + 1 > 6 || !arrayNumber[oldPoint->y][oldPoint->x + 1]
			->isVisible()))
				return true;
			return false;
		} else if (newPoint->x < oldPoint->x && newPoint->y > oldPoint->y) {
			if ((oldPoint->y + 1 < 0 || oldPoint->y + 1 > currentRow || !arrayNumber[oldPoint->y + 1][oldPoint->x]
			->isVisible())
				&& (oldPoint->y < 0 || oldPoint->x - 1 < 0 || !arrayNumber[oldPoint->y][oldPoint->x - 1]
			->isVisible()))
				return true;
			return false;
		} else if (newPoint->x < oldPoint->x && newPoint->y < oldPoint->y) {

			if ((oldPoint->y - 1 < 0 || !arrayNumber[oldPoint->y - 1][oldPoint->x]->isVisible())
				&& (oldPoint->y < 0 || oldPoint->x - 1 < 0 || !arrayNumber[oldPoint->y][oldPoint->x - 1]
			->isVisible()))
				return true;
			return false;
		}
	}
	return true;

}

void GUITwenty::genRow() {
	if (idCurrentNumber >= 0) {
		Number* number = currentNumber.at(idCurrentNumber);

		PointGame* currentPoint = convertPoint(number->getX() + WIDTH_BALL_TWENTY * 0.5f, number->getY()
			+ WIDTH_BALL_TWENTY * 0.5f);
		AXLOGD("CURRENT POINT *** %i ", currentPoint->y);
		if (currentPoint->y >= 0 && currentPoint->y < NUM_ROW && currentPoint->x < NUM_COLUMN) {
			arrayNumber[currentPoint->y][currentPoint->x]->setVisible(true);
			arrayNumber[currentPoint->y][currentPoint->x]->setNumber(number->id);
			number->setVisible(false);
			number->isFall = false;
			idCurrentNumber = -1;
		}
		else {
			number->setX(arrayNumber[0][currentPoint->x]->getX());
			number->setY(number->getY() + WIDTH_BALL_TWENTY * 0.3f);
			idCurrentNumber = -1;
		}
		checkListFall();
	}
	
	if (currentRow == NUM_ROW - 1) {
		endGame();
		return;
	}
	GameSound::playMove();
	moveY = 0;
	currentRow = currentRow + 1;
	updateBg();
	rootY = START_Y + WIDTH_SQUARE; // next target START_Y
	int level = 0;
	for (int i = arrayLevel.size() - 1; i >= 0; i--) {
		if (arrayLevel[i] <= maxNumber) {
			level = i + 1;
			break;
		}
	}
	int maxGen = maxNumber - 3 - level;
	for (int i = 0; i < NUM_COLUMN; i++) {
		int id = 0;
		do {
			id = (int) (GameUtility::getRandom() * maxGen) + 1 + level;
		} while (id == arrayNumber[currentRow - 1][i]->id);
		arrayNumber[currentRow][i]->setNumber(id);
		arrayNumber[currentRow][i]->setVisible(true);

		arrayNumber[currentRow][i]->setPosition(START_X + (WIDTH_SQUARE - WIDTH_BALL_TWENTY)
			* 0.5f + WIDTH_SQUARE * i, START_Y - WIDTH_SQUARE * currentRow
			+ (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f);
	}

	if (maxNumber <= 10)
		timeProgress = 7;
	else
		timeProgress = 10.4 - maxNumber / 10.0f;
	currentTime = timeProgress;
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	//progress->cleanup();
    progress->setVisible(true);
    progress->setPercentage(100);
	//progress->setWidth(size.width);
	//runAction(Sequence::create(DelayTime::create(timeProgress),CallFunc::create(this, AX_CALLBACK_0(GUITwenty::genRow)), NULL));
	//progress->runAction(ScaleTo::create(timeProgress, 0, progress->getScaleY()));
	

	if (idCurrentNumber >= 0) {
		if (currentNumber.at(idCurrentNumber)->getY() > bgDark1->getPositionY() + bgDark1->getRealHeight()
			- WIDTH_SQUARE) {
				currentNumber.at(idCurrentNumber)->setY(bgDark1->getPositionY()
					+ bgDark1->getRealHeight() - WIDTH_SQUARE);
		}
	}
}

void GUITwenty::checkGenRow() {
    vector<PointGame *> arrayNum;
	for(int i = 0; i < maxNumber + 1; i++)
    {
        PointGame* p = new PointGame();
        p->x = 0;
        arrayNum.push_back(p);
    }
	bool canGen = true;
	for (int i = 0; i < NUM_ROW - 1; i++) {
		for (int j = 0; j < NUM_COLUMN; j++) {
			if (arrayNumber[i][j]->isVisible() && arrayNumber[i][j]->id > 0 && arrayNumber[i][j]->id < arrayNum.size()) {
				arrayNum.at(arrayNumber[i][j]->id)->x = arrayNum.at(arrayNumber[i][j]->id)->x + 1;
				if (arrayNum.at(arrayNumber[i][j]->id)->x > 1) {
					canGen = false;
					break;
				}
			}
		}
		if (canGen == false)
			break;
	}
    for(int i = 0; i < maxNumber; i++)
    {
        delete arrayNum.at(i);
    }
    arrayNum.clear();

    
	if (canGen) {
		//progress.startTime(10);
		
		genRow();
	}
}

void GUITwenty::doTutorial()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	int data[8][7];
	for(int i = 0; i < 8 ; i++)
		for(int j = 0; j < 7; j++)
			data[i][j] = -1;
	data[0][0] = -1;
	data[0][1] = -1;
	data[0][2] = -1;
	data[0][3] = -1;
	data[0][4] = -1;
	data[0][5] = 1;
	data[0][6] = 3;

	data[1][0] = -1;
	data[1][1] = -1;
	data[1][2] = -1;
	data[1][3] = -1;
	data[1][4] = -1;
	data[1][5] = 4;
	data[1][6] = 2;

	data[2][0] = 1;
	data[2][1] = -1;
	data[2][2] = -1;
	data[2][3] = -1;
	data[2][4] = -1;
	data[2][5] = 5;
	data[2][6] = 6;

    timeProgress = 10;
	newGame(5, 2, data, 0);
	state = GameStateTwenty::TUTORIAL_TWENTY;

	tutorialLabel->setString("Pick up tile, drop it on to tile with the same value");
	tutorialLabel->setPosition(Vec2(size.width * 0.5f, size.height * 0.6f));
	tutorialLabel->setVisible(true);
	runAction(Sequence::create(DelayTime::create(1.5f),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial1, this)), NULL));
}

void GUITwenty::tutorial1()
{
	Number* n = new Number();
	n->addToParent(this);
	arrayNumber[0][5]->setVisible(false);
	n->setNumber(1);
	n->setPosition(arrayNumber[0][5]->getX(), arrayNumber[0][5]->getY());

	GameImage* hand = addImage("iconHand.png");
	hand->setPosition(n->getX() + n->getWidth() * 0.75f, n->getY() - n->getWidth() * 0.5f);

	float time = 0.7;

	n->ball->runAction(Sequence::create(MoveTo::create(time, Vec2(arrayNumber[2][0]->getX() + n->getWidth() * 0.5, arrayNumber[2][0]->getY() + n->getWidth() * 0.5)), RemoveSelf::create(true), NULL));
	hand->runAction(Sequence::create(MoveTo::create(time, Vec2(arrayNumber[2][0]->getX() + n->getWidth() * 0.75f, arrayNumber[2][0]->getY() - n->getWidth() * 0.5f)), RemoveSelf::create(true), NULL));
	
	runAction(Sequence::create(DelayTime::create(time),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial2, this)), NULL));
}

void GUITwenty::tutorial2()
{
	arrayNumber[2][0]->setNumber(2);
	tutorialLabel->runAction(Sequence::create(FadeOut::create(1.05f), FadeIn::create(1.05f), NULL));
	runAction(Sequence::create(DelayTime::create(1.5f),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial3, this)), NULL));
}

void GUITwenty::tutorial3()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Number* n = new Number();
	n->addToParent(this);
	arrayNumber[1][5]->setVisible(false);
	n->setNumber(4);
	n->setPosition(arrayNumber[1][5]->getX(), arrayNumber[1][5]->getY());

	GameImage* hand = addImage("iconHand.png");
	hand->setPosition(n->getX() + n->getWidth() * 0.5f, n->getY());

	tutorialLabel->setString("Move another tile out of the way to make a match");
	tutorialLabel->setPosition(Vec2(size.width * 0.5f, size.height * 0.6f));
	float time = 0.7;
	n->ball->runAction(Sequence::create(MoveTo::create(time, Vec2(arrayNumber[2][4]->getX() + n->getWidth() * 0.5, arrayNumber[2][4]->getY() + n->getWidth() * 0.5)), RemoveSelf::create(true), NULL));
	hand->runAction(Sequence::create(MoveTo::create(time, Vec2(arrayNumber[2][4]->getX()+ n->getWidth() * 0.75f, arrayNumber[2][4]->getY() - n->getWidth() * 0.5f)), RemoveSelf::create(true), NULL));

	runAction(Sequence::create(DelayTime::create(time),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial4, this)), NULL));
}

void GUITwenty::tutorial4()
{
	arrayNumber[2][4]->setNumber(4);
	arrayNumber[2][4]->setVisible(true);
	runAction(Sequence::create(DelayTime::create(2.0f),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial5, this)), NULL));
}

void okTutorial()
{
	GUIManager::getInstance().guiTwenty->newGame();
}

void GUITwenty::tutorial5()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	Number* n = new Number();
	n->addToParent(this);
	arrayNumber[1][6]->setVisible(false);
	n->setNumber(2);
	n->setPosition(arrayNumber[1][6]->getX(), arrayNumber[1][6]->getY());

	GameImage* hand = addImage("iconHand.png");
	hand->setPosition(n->getX() + n->getWidth() * 0.5f , n->getY());
	float time = 0.7;
	n->ball->runAction(Sequence::create(MoveTo::create(time, Vec2(arrayNumber[2][0]->getX() + n->getWidth() * 0.5, arrayNumber[2][0]->getY() + n->getWidth() * 0.5)), RemoveSelf::create(true), NULL));
	hand->runAction(Sequence::create(MoveTo::create(time, Vec2(arrayNumber[2][0]->getX()+ n->getWidth() * 0.75f, arrayNumber[2][0]->getY() - n->getWidth() * 0.5f)), RemoveSelf::create(true), NULL));

	runAction(Sequence::create(DelayTime::create(time),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial6, this)), NULL));
	
}

void GUITwenty::tutorial6()
{
	arrayNumber[2][0]->setNumber(3);
	arrayNumber[2][0]->setVisible(true);
	runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create(AX_CALLBACK_0(GUITwenty::tutorial7, this)), NULL));
}

void GUITwenty::tutorial7()
{
	GUIManager::getInstance().guiDialog->showGUI("Are you ready to play?", &okTutorial, true);
}


void GUITwenty::effectStar(Number* ball)
{
	//StarFly* image = NULL;
	//for (int i = 0; i < arrayStarEffect.size(); i++) {
	//	if (!arrayStarEffect.at(i)->isVisible()) {
	//		image = arrayStarEffect.at(i);
	//		break;
	//	}
	//}
	//if (image == NULL) {
	//	image = new StarFly(ball->getWidth(), ball->getHeight());
	//	this->addChild(image);
	//	arrayStarEffect.push_back(image);
	//	image->setLocalZOrder(10);
	//}
	//image->setVisible(true);
	//image->setOpacity(255);
	//image->setColor(ball->ball->getImg()->getColor());
	////image->setScale(ball->rootScaleX * 1.1);
	//image->startEffect();
	//image->setPosition(ball->getX(), ball->getY());
}

void GUITwenty::updateBg()
{
	bgDark1->getImg()->stopAllActions();
	if (currentRow == 7) {
		bgDark1->getImg()->runAction(
			RepeatForever::create(
				Sequence::create(
					TintTo::create(0.5, Color3B(100, 50, 50)),
					TintTo::create(0.5, Color3B(30, 30, 30)),
					NULL
				)
			)
		);
	}
	else {
		bgDark1->getImg()->setColor(Color3B(30, 30, 30));
	}
}

void GUITwenty::updateSizeNumber()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    if (size.width / size.height < 0.2f / 0.3f)
    {
        WIDTH_SQUARE = widthBoard / NUM_COLUMN;
        START_X      = size.width * 0.02f;
        START_Y      = bgProgress->getPositionY() - bgProgress->getRealHeight() * 0.5f - WIDTH_SQUARE * 1.4f;
    }
    else
    {
        WIDTH_SQUARE = widthBoard / NUM_COLUMN;
        START_X      = size.width * 0.12f;
        START_Y      = bgProgress->getPositionY() - bgProgress->getRealHeight() * 0.5f - WIDTH_SQUARE * 1.3f;
    }
	WIDTH_BALL_TWENTY = WIDTH_SQUARE * 0.9f;

	bgDark1->setWidth(WIDTH_SQUARE * NUM_COLUMN);
	bgDark1->setHeight(WIDTH_SQUARE * NUM_ROW);
	bgDark1->setPosition(size.width * 0.5f - bgDark1->getRealWidth() * 0.5f, START_Y - (NUM_ROW - 1) * WIDTH_SQUARE);

	for (int i = 0; i < NUM_ROW; i++)
		for (int j = 0; j < NUM_COLUMN; j++) {
			arrayNumber[i][j]->updateSize();
			arrayNumber[i][j]->setPosition(START_X + (WIDTH_SQUARE - WIDTH_BALL_TWENTY) * 0.5f
				+ WIDTH_SQUARE * j, START_Y - WIDTH_SQUARE * i
			);
			arrayNumber[i][j]->setNumber((int)(GameUtility::getRandom() * 5) + 1);
		}

	LIMIT_Y = START_Y + WIDTH_SQUARE;
	bgDark2->setHeight(bgDark1->getPositionY());
	bgDark2->setPos(size.width * 0.5f, bgDark2->getRealHeight() * 0.5f);
}

void GUITwenty::showNextNumber()
{
	int level = 0;
	for (int i = arrayLevel.size() - 1; i >= 0; i--) {
		if (arrayLevel[i] <= maxNumber) {
			level = i + 1;
			break;
		}
	}
	for (int i = 0; i < NUM_ROW; i++) {
		for (int j = 0; j < NUM_COLUMN; j++) {
			if (arrayNumber[i][j]->isVisible() && arrayNumber[i][j]->id <= level) {
				arrayNumber[i][j]->setVisible(false);
				playParticle(arrayNumber[i][j]->getX(), arrayNumber[i][j]->getY(), GameUtility::getColorTwenty(arrayNumber[i][j]->id), arrayNumber[i][j]->id);
			}
		}
	}
	score = score + maxNumber * maxNumber;
	updateScoreSum();
	checkListFall();
	state = GameStateTwenty::PLAY_TWENTY;
}

Sprite* GUITwenty::getSmoke()
{
	Sprite* image = NULL;
	for (int i = 0; i < arraySmoke.size(); i++) {
		if (!arraySmoke.at(i)->isVisible()) {
			image = arraySmoke.at(i);
			break;
		}
	}
	if (image == NULL) {
		image = Sprite::create("GuiGame/smoke.png");
		this->addChild(image);
		arraySmoke.push_back(image);
	}
	image->setVisible(true);
	image->setOpacity(255);
    return  image;
}

void GUITwenty::showNewNumber(Number* number)
{
	state = GameStateTwenty::NEXT_NUMBER_TWENTY;
	GameSound::playLevelUp();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	layerColor->setVisible(true);
	layerColor->setOpacity(0);
	layerColor->stopAllActions();
	layerColor->runAction(Sequence::create(
		EaseIn::create(FadeTo::create(0.5, 200), 2),
		DelayTime::create(1.8),
		NULL
	));

	Vec2 pos = Vec2(size.width * 0.5, size.height * 0.65);
	/*DBArmatureNode* eff = DBFactory::getInstance()->buildArmatureNode("tile_light");
	if (eff) {
		this->addChild(eff);
		eff->setLocalZOrder(2);
		eff->setPosition(pos);
		eff->gotoAndPlay("run", 0.5, -1, 1);
		eff->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->removeFromParent();
		});
	}

	DBArmatureNode* eff1 = DBFactory::getInstance()->buildArmatureNode("cast_skill_vua_le_hoi");
	if (eff1) {
		this->addChild(eff1);
		eff1->setLocalZOrder(2);
		eff1->setPosition(pos.x, pos.y + 50);
		eff1->gotoAndPlay("run", 0.5, -1, 1);
		eff1->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->removeFromParent();
		});
	}*/

	newNumber->setVisible(true);
	newNumber->setNumber(maxNumber);
	newNumber->setPosition(number->getX(), number->getY());
	newNumber->setScale(number->ball->getScaleX(), number->ball->getScaleY());
	newNumber->setOpacity(255);
	newNumber->runAction(
		Sequence::create(
			Spawn::create(
				EaseOut::create(ScaleTo::create(0.4, 2), 2),
				EaseOut::create(MoveTo::create(0.4, Vec2(size.width * 0.5, size.height * 0.65)), 2),
				NULL
			),
			Spawn::create(RotateTo::create(0.4, Vec3(0, -20, 0)), MoveBy::create(0.4, Vec2(-5, 0)), NULL),
			Spawn::create(RotateTo::create(0.4, Vec3(10, 20, 0)), MoveBy::create(0.4, Vec2(10, 0)), NULL),
			Spawn::create(RotateTo::create(0.4, Vec3(0, 0, 0)), MoveBy::create(0.4, Vec2(-5, 0)), NULL),
            CallFunc::create(AX_CALLBACK_0(GUITwenty::showDeleteNumber, this)),
			NULL
		)
	);
	paperRight->startEffect();
	paperLeft->startEffect();
}

void GUITwenty::playSoundMove()
{
	GameSound::playNewNumber();
}

void GUITwenty::showDeleteNumber()
{
	int level = 0;
	for (int i = arrayLevel.size() - 1; i >= 0; i--) {
		if (arrayLevel[i] <= maxNumber) {
			level = i + 1;
			break;
		}
	}

	//starFly->setVisible(true);
	//starFly->startEffect();

	deleteNumber->setNumber(level);
	deleteNumber->setVisible(true);
	deleteNumber->setScale(0);
	deleteNumber->setOpacity(0);
	deleteNumber->runAction(
		Spawn::create(
			FadeIn::create(0.3),
			EaseBounceOut::create(ScaleTo::create(0.5, 1)),
			NULL
		)
	);

	iconX->setOpacity(0);
	iconX->runAction(
		Sequence::create(
			DelayTime::create(0.5),
			FadeTo::create(0.5, 150),
			CallFunc::create(AX_CALLBACK_0(GUITwenty::showAdsFull, this)),
			NULL
		)
	);
	btnOk->setVisible(true);
}

void GUITwenty::hideNewNumber()
{
	//starFly->setVisible(false);
	GameSound::playLevelUp();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	layerColor->stopAllActions();
	layerColor->runAction(Sequence::create(
		EaseIn::create(FadeOut::create(0.5), 2),
		Hide::create(),
		NULL
	));
	playSoundMove();
	newNumber->runAction(
		Sequence::create(
			Spawn::create(RotateTo::create(0.6, Vec3(-10, 0, 0)), ScaleTo::create(0.6, 2.5), NULL),
			Spawn::create(
				EaseIn::create(RotateTo::create(0.4, Vec3(0, 0, 0)), 2),
				EaseIn::create(ScaleTo::create(0.4, 0.5), 2),
				EaseIn::create(MoveTo::create(0.4, curNumber->getPosition()), 2),
				NULL
			),
			FadeOut::create(0.4),
			DelayTime::create(0.4),
			CallFunc::create(AX_CALLBACK_0(GUITwenty::showNextNumber, this)),
			Hide::create(),
			NULL
		)
	);
	btnOk->setVisible(false);
	deleteNumber->runAction(
		Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.5, 0)),
			Hide::create(),
			NULL
		)
	);
}

void GUITwenty::showAdsFull()
{
	int level = 0;
	for (int i = arrayLevel.size() - 1; i >= 0; i--) {
		if (arrayLevel[i] <= maxNumber) {
			level = i + 1;
			break;
		}
	}

	if (level % 2 == 0) {
	//	JNIUtils::showAdsFull();
	}
}

void GUITwenty::showGui()
{

	//game->isFirstTimeTwenty = true;
	if (game->isFirstTimeTwenty)
	{
		doTutorial();
		game->isFirstTimeTwenty = false;
		UserDefault::getInstance()->setIntegerForKey("isFirstTimeTwenty", false);
		UserDefault::getInstance()->flush();
	}
	else
	{
		int currentRow = UserDefault::getInstance()->getIntegerForKey("currentRow", -1);
		//currentRow = -1;
		if (currentRow == -1)
		{
			newGame();
		}
		else
		{
			int maxNumber = UserDefault::getInstance()->getIntegerForKey("maxNumber", -1);
			int data[8][7];
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 7; j++)
				{
					int convert = i * 7 + j;
					data[i][j] = UserDefault::getInstance()->getIntegerForKey(("numTwenty" + GameUtility::toString(convert)).c_str(), -1);
				}
			int savescore = UserDefault::getInstance()->getIntegerForKey("saveScore", 0);
			timeProgress = UserDefault::getInstance()->getFloatForKey("time");
			newGame(maxNumber, currentRow, data, savescore);
			//GUIManager::getInstance().guiDialog->showGUI("Do you want to play the last game?", NULL, false, &cancelContinueFunction);
		}
	}
}
