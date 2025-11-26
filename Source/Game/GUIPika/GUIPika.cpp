#include "guiPika.h"
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
#include "Engine/GUI/ParticleEffect.h"
#include "Engine/Utility/Utility.h"


#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 10
#define BTN_SOUND_ID 12
#define BTN_PAUSE_ID 13
#define BTN_PLAY_ID 14
#define BTN_OK 15
#define BTN_DEL 16
#define BTN_NEW_GAME 17
#define BTN_SEARCH_ID 18
std::string GUIPika::className = "GUIPika";
GUIPika::GUIPika(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	setKeypadEnabled(true);
}


GUIPika::~GUIPika(void)
{
}

void okBackFunction()
{
	AXLOGD("VAO DAY MA ********* ");
    game->changeToLandscape();
    JNIUtils::showAdsBanner(1);
    GUIManager::getInstance().removeAllGui();
    GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
}

void cancelBackFunction()
{
	//GUIManager::getInstance().guiPika->gameState = GameStatePika::PLAY;
}
void GUIPika::onBackKey()
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
            
		GUIManager::getInstance().isCallBackPress = true;
		GUIManager::getInstance().guiDialog->showGUI("Do you want to quit the game?", &okBackFunction, false, &cancelBackFunction);
		//GUIManager::getInstance().guiPika->gameState = PAUSE;
	}
}
void GUIPika::initGUI(){
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
	//bg1->getImg()->runAction(Sequence::create(FadeIn::create(0.8f), DelayTime::create(.8f), FadeOut::create(0.8f), CallFunc::create(AX_CALLBACK_0(GUIPika::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);
	callBackSplash();
	
}

void GUIPika::callBackSplash()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	background = addImage("gamePika/background.png");
//	background->getImg()->setColor(c3(0, 100, 100));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);
//	background->setVisible(false);

	btnBack = addButton(BTN_BACK_ID, "gamePika/btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 1.0f, size.height - btnBack->getHeight() * 0.7f);

	btnSound = addButton(BTN_SOUND_ID, "gamePika/btnSoundOn.png");
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());

	btnSearch = addButton(BTN_SEARCH_ID, "gamePika/btnSearch.png");
	btnSearch->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnSound->getPositionY());
	if(game->music)
	{
		btnSound->normalImage->setImage("gamePika/btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("gamePika/btnSoundOff.png");
	}

	bgScore = Scale9Sprite::create("GuiGame/gamePika/bgScoreNormal.png");
	addChild(bgScore);
	bgScore->setContentSize(Size(100, 45));
	bgScore->setPosition(bgScore->getContentSize().width * 0.6, btnBack->getPositionY() + 3);

	Text* lbScore = Text::create("SCORE", "fonts/tahomabd.ttf", 10);
	bgScore->addChild(lbScore);
	lbScore->enableOutline(Color4B(115, 37, 31, 255), 1);
    
	lbScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.9));

	Scale9Sprite *bgBest = Scale9Sprite::create("GuiGame/gamePika/bgScoreBest.png");
	addChild(bgBest);
	bgBest->setContentSize(Size(100, 45));
	bgBest->setPosition(bgScore->getPositionX() + bgBest->getContentSize().width * 1.1, bgScore->getPositionY());

	Text* lbBest = Text::create("BEST", "fonts/tahomabd.ttf", 10);
	bgBest->addChild(lbBest);
	lbBest->enableOutline(Color4B(115, 37, 31, 255), 1);
	lbBest->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.9));

	labelScore = Text::create("0", "fonts/tahomabd.ttf", 14);
	labelScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelScore->enableOutline(Color4B(115, 37, 31, 255), 1);
	labelScore->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgScore->addChild(labelScore);
	labelScore->setPosition(Vec2(bgScore->getContentSize().width * 0.5, bgScore->getContentSize().height * 0.46));

	labelHighscore = Text::create("0", "fonts/tahomabd.ttf", 14);
	labelHighscore->setTextHorizontalAlignment(TextHAlignment::CENTER);
    labelHighscore->enableOutline(Color4B(115, 37, 31, 255), 1);
	labelHighscore->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgBest->addChild(labelHighscore);
	labelHighscore->setPosition(Vec2(bgBest->getContentSize().width * 0.5, bgBest->getContentSize().height * 0.46));

	iconHeart = addImage("gamePika/iconHeart.png");
	iconHeart->setPosition(bgBest->getPositionX() + bgBest->getContentSize().width * 0.5 + iconHeart->getWidth() * 0.7, btnBack->getPositionY());
	iconHeart->setScale(0.8);

	labelLife = Text::create("1", "fonts/tahomabd.ttf", 14);
	labelLife->setAnchorPoint(Vec2(0.5f, 0.5f));
	labelLife->setPosition(iconHeart->getPosition());
    addChild(labelLife);

	labelLevel = Text::create("1", "fonts/tahomabd.ttf", 14);
	labelLevel->setPositionX(size.width * 0.5f);
	labelLevel->setPositionY(labelLevel->getContentSize().height * 1.2);
    addChild(labelLevel);

	widthProgress = btnSearch->getPositionX() - btnSearch->getWidth() * 0.7f - (iconHeart->getPositionX() + iconHeart->getWidth() * 0.8f);
	bgProgress = addImage("gamePika/progress_bg.png");
	//bgProgress->setColor(c3(100, 100, 100));
	bgProgress->setWidth(widthProgress);
	bgProgress->setHeight(btnBack->getHeight() * 0.75f);
	bgProgress->setPos(iconHeart->getPositionX() + iconHeart->getWidth() * 0.8f + widthProgress * 0.5f, btnBack->getPositionY());


	progress = ProgressTimer::create(Sprite::create("GuiGame/gamePika/progress.png"));
	progress->setType(ProgressTimer::Type::BAR);
	progress->setMidpoint(Vec2(0, 0.5));
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setPercentage(50);
	progress->setPositionX(bgProgress->getWidth() * 0.495 - progress->getContentSize().width * 0.5);
	progress->setPositionY(bgProgress->getHeight() * 0.45 - progress->getContentSize().height * 0.5);
	bgProgress->addChild(progress);

	boardData = new BoardDataPika();
	//boardData->reset(level);
	currentTouch = new PointGame();

	for (int i = 0; i < 4; i++) {
		arrayLine[i] = new GameImage("gamePika/green.png");
		addChild(arrayLine[i]);
		arrayLine[i]->setVisible(false);
		arrayLine[i]->setWidth(2);
		arrayLine[i]->setHeight(2);
		arrayLine[i]->setLocalZOrder(5);
		arrayLine[i]->getImg()->setAnchorPoint(Vec2(0, 0));
	}

	for(int i = 0; i < BOARD_ROW_PIKA; i++)
		for(int j = 0; j < BOARD_COLUMN_PIKA; j++)
			arrayNumber[i][j] = NULL;

	state       = GameStatePika::PLAY_PIKA;
	touchPoint2 = new PointGame();
	touchPoint1 = new PointGame();
	level = 1;

	bgDark = this->addImage("bgDark.png");
	bgDark->setWidth(size.width);
	bgDark->setHeight(size.height);
	bgDark->setPos(size.width * 0.5f, size.height * 0.5f);

	btnPlay = this->addButton(BTN_PLAY_ID, "gamePika/btnPlay.png");
	btnPlay->setPosition(size.width * 0.5f, size.height * 0.5f);
	bgDark->setLocalZOrder(5);
	btnPlay->normalImage->setLocalZOrder(5);
	bgDark->setVisible(false);
	btnPlay->setVisible(false);
	//makeNewLevel();

	timeGame = 0;
	currentTime = 0;

	// init Challenge Mode

	groupBonus = Node::create();
	addChild(groupBonus);
	groupBonus->setPosition(iconHeart->getPositionX() + iconHeart->getWidth() * 0.7 + size.width * 0.1, btnBack->getPositionY());

	bgProgressBonus = new GameImage("gamePika/progress_bg.png");
	groupBonus->addChild(bgProgressBonus);
	//bgProgress->setColor(c3(100, 100, 100));
	//bgProgress->setWidth(widthProgress);
	//bgProgress->setHeight(btnBack->getHeight() * 0.75f);
	//bgProgressBonus->setPos(size.width - bgProgressBonus->getWidth() * 1.3, size.height * 0.5);
	bgProgressBonus->setWidth(size.width * 0.2);
	bgProgressBonus->setHeight(btnBack->getHeight() * 0.5);
	//bgProgressBonus->setPos(iconHeart->getPositionX() + iconHeart->getWidth() * 0.7 + bgProgressBonus->getRealWidth() * 0.5, btnBack->getPositionY());

	progressBonus = ProgressTimer::create(Sprite::create("GuiGame/gamePika/progress.png"));
	progressBonus->setType(ProgressTimer::Type::BAR);
	progressBonus->setMidpoint(Vec2(0, 0.5));
	progressBonus->setBarChangeRate(Vec2(1, 0));
	progressBonus->setPercentage(50);
	progressBonus->setPositionX(bgProgressBonus->getWidth() * 0.495 - progressBonus->getContentSize().width * 0.5);
	progressBonus->setPositionY(bgProgressBonus->getHeight() * 0.45 - progressBonus->getContentSize().height * 0.5);
	this->bgProgressBonus->addChild(progressBonus);

	iconGift = new GameImage("gamePika/iconStar.png");
	groupBonus->addChild(iconGift);
	iconGift->setPositionX(bgProgressBonus->getRealWidth() * 0.52);;
	iconGift->setScale(0.5);

	iconBomb = new GameImage("gamePika/iconBomb.png");
	groupBonus->addChild(iconBomb);
	iconBomb->setPositionX(-bgProgressBonus->getRealWidth() * 0.52);
	iconBomb->setScale(0.5);

	imgEffectBomb = new GameImage("iconBomb.png");
	this->addChild(imgEffectBomb);
	imgEffectBomb->setVisible(false);
	imgEffectBomb->setLocalZOrder(3);

	labelEffectStar = Text::create("0", "fonts/tahomabd.ttf", 30);
	labelEffectStar->setTextHorizontalAlignment(TextHAlignment::CENTER);
	labelEffectStar->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgProgressBonus->addChild(labelEffectStar);
	labelEffectStar->setPositionY(bgProgressBonus->getContentSize().height * 0.5);

    auto effect = efk::Effect::create("fire.efk", 80.0f);
    if (effect != nullptr)
    {
        effBomb = efk::EffectEmitter::create(game->manager);
        effBomb->setEffect(effect);
        effBomb->setPlayOnEnter(false);
        effBomb->setRemoveOnStop(false);
        effBomb->setSpeed(0.5);
        effBomb->setPosition(bgProgress->getPositionX() + bgProgress->getContentSize().width * 0.5,
                             bgProgress->getPositionY());
        // emitter->setScale(13);
       // effBomb->setPosition(clock->getPosition());
        this->addChild(effBomb, 10);
    }
}


void okSearchFunction() {
	/*DBArmatureNode* eff1 = DBFactory::getInstance()->buildArmatureNode("bom_change");
	if (eff1) {
		GUIManager::getInstance().guiPika->addChild(eff1);
		eff1->setLocalZOrder(2);
		eff1->setPosition(GUIManager::getInstance().guiPika->labelLife->getPositionX(), GUIManager::getInstance().guiPika->labelLife->getPositionY() - 30);
		eff1->gotoAndPlay("run", 0.0, -1, 1);
		eff1->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
			armature->removeFromParent();
		});
	}*/
	GUIManager::getInstance().guiPika->countLife--;
	GUIManager::getInstance().guiPika->boardData->resetCheck();
	GUIManager::getInstance().guiPika->labelLife->setString(GameUtility::toString(GUIManager::getInstance().guiPika->countLife).c_str());
	vector<PointGame*>arrayPoint = GUIManager::getInstance().guiPika->boardData->getMovePoint();
	if (arrayPoint.size() > 0) {
		PointGame* p1 = arrayPoint.at(0);
		PointGame* p2 = arrayPoint.at(1);
		GUIManager::getInstance().guiPika->arrayNumber[p1->y][p1->x]->setSelect(true);
		GUIManager::getInstance().guiPika->arrayNumber[p2->y][p2->x]->setSelect(true);
		GUIManager::getInstance().guiPika->showParticleFire(GUIManager::getInstance().guiPika->arrayNumber[p1->y][p1->x]->getX() + WIDTH_BALL_PIKA * 0.5, GUIManager::getInstance().guiPika->arrayNumber[p1->y][p1->x]->getY() + HEIGHT_BALL_PIKA * 0.5, 0);
	}
	GameSound::playHit();
}

 void GUIPika::onButtonRelease(int buttonID, Touch* touch)
 {
	 GameSound::playClick();
	 switch (buttonID)
	 {
	 case BTN_SEARCH_ID:
	 {
		 //this->countLife = 0;
		 if (gameMode == GameMode::NORMAL_MODE || gameMode == GameMode::CHALLENGE_MODE) {
			 if (this->countLife > 1) {
				 GUIManager::getInstance().guiDialog->showGUI("You will lose 1 life, do you want to use Search Function?", &okSearchFunction, false, NULL);
			 }
			 else {
				 GUIManager::getInstance().guiDialog->showGUI("You have 1 life, you can't use Search Function", NULL, true);
			 }
		 }
		 else {
			 boardData->resetCheck();

			 vector<PointGame*>arrayPoint = boardData->getMovePoint();
			 if (arrayPoint.size() > 0) {
				 PointGame* p1 = arrayPoint.at(0);
				 PointGame* p2 = arrayPoint.at(1);
				 arrayNumber[p1->y][p1->x]->setSelect(true);
				 arrayNumber[p2->y][p2->x]->setSelect(true);
				 this->showParticleFire(arrayNumber[p1->y][p1->x]->getX() + WIDTH_BALL_PIKA * 0.5, arrayNumber[p1->y][p1->x]->getY() + HEIGHT_BALL_PIKA * 0.5, 0);
				 this->showParticleFire(arrayNumber[p2->y][p2->x]->getX() + WIDTH_BALL_PIKA * 0.5, arrayNumber[p2->y][p2->x]->getY() + HEIGHT_BALL_PIKA * 0.5, 0);
			 }
		 }

	 }
	 break;
	 case BTN_BACK_ID:
		 {
		 onBackKey();
		 
		 }

		 break;
	 case BTN_SOUND_ID:
		 {
		// onPause();
			 game->music = !game->music;
			 if(game->music)
			 {
				 btnSound->normalImage->setImage("gamePika/btnSoundOn.png");
			 }
			 else
			 {
				 btnSound->normalImage->setImage("gamePika/btnSoundOff.png");
			 }

			 UserDefault::getInstance()->setBoolForKey("music", game->music);
			 UserDefault::getInstance()->flush();
		 }
		 break;
	 case BTN_PLAY_ID:
		 {
			resumeGame();
		 }
		 break;
	 default:
		
		 break;
	 }
 }

 void GUIPika::act()
 {
	 if (score != targetScore) {
		 if ((targetScore - score) * deltaScore > 0) {
			 score = score + deltaScore;
			 if (abs(score - targetScore) <= deltaScore * 1.1) {
				 score = targetScore;
			 }
		 }
		 else {
			 score = targetScore;
		 }
		 labelScore->setString((GameUtility::standardizeNumber(score)).c_str());
	 }
         if (state == GameStatePika::PAUSE_PIKA || state == GameStatePika::END_PIKA ||
             state == GameStatePika::EFFECT_PIKA)
		 return;
	 
	 if (timeGame > 0) {
		 currentTime = currentTime + game->deltaTime;
		 if (currentTime >= timeGame) {
			 GameSound::playLose();
			 endGame();
			 return;
		 }
		 
		 float percent = currentTime / timeGame * 100;
		 percent = 100 - percent;
		 progress->setPercentage(percent);
		 //timeGame = timeGame - game->deltaTime;
		
		 int index = timeGame - currentTime;
		 if (index >= 0 && index < 10) {
			 if (arrayPlayTime[index] == false) {
				 arrayPlayTime[index] = true;
				 GameSound::playTime();
			 }
		 }
	 }
	 if (gameMode == CHALLENGE_MODE) {
		 
	 }
 }

 void GUIPika::callbackBonus() {
     state = GameStatePika::PLAY_PIKA;
 }

 void GUIPika::callbackBomb() {
	 imgEffectBomb->setVisible(false);
	 currentTime = currentTime + 20;
	/* effectBomb->setVisible(true);
	 effectBomb->gotoAndPlay("run", 0, -1, 1);
	 effectBomb->setPosition(imgEffectBomb->getPosition());*/
    effBomb->stop();
    effBomb->setVisible(true);
    effBomb->play(0);
    effBomb->setPosition(imgEffectBomb->getPosition());

	 state = GameStatePika::PLAY_PIKA;
	 GameSound::playBomb();
 }

 void GUIPika::startTime(float time, float currentTime)
 {
	 progress->stopAllActions();
	 // progress->setWidth(widthProgress);
	 rootProgress = progress->getScaleX();
	 // runAction(Sequence::create(DelayTime::create(time),CallFunc::create(AX_CALLBACK_0(GUIPika::endGame)), NULL));
	 // progress->runAction(Sequence::create(ScaleTo::create(time, 0, progress->getScaleY()), CallFunc::create(AX_CALLBACK_0(GUIPika::endGame)), NULL));
	 progress->setPercentage(99.99);
	 progress->runAction(Sequence::create(ProgressTo::create(time, 0)
		 , CallFunc::create(AX_CALLBACK_0(GUIPika::endGame, this)), NULL));
	 timeGame = time;
 }

 void okFunctionPika() {
     game->showAdsFull();
     //JNIUtils::showAdsFull();
	// GUIManager::getInstance().guiWaiting.showAds(false);
 }

 void cancelFunctionPika() {
	 if (GUIManager::getInstance().guiPika->gameMode == GameMode::NORMAL_MODE) {
		 game->isPlayingPika = false;
		 UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
		 UserDefault::getInstance()->flush();
	 }
	
	 GUIManager::getInstance().guiPika->resumeGame();
	 GUIManager::getInstance().guiPika->makeNewLevel();
	 
 }

 void okContinueLastGame() {
	 GUIManager::getInstance().guiPika->resumeGame();
 }

 void GUIPika::makeNewLevel()
 {
	 labelEffectStar->setVisible(false);
	 imgEffectBomb->setVisible(false);
	 deltaBonus = 0;
	 //timeBonus = TIME_BONUS / 2;
	 genLevel();
	 genRowColumnTime();
	 genData();
	 startGameAfterGen();
	 if (gameMode == GameMode::NORMAL_MODE) {
		 if (game->isPlayingPika) {
			 onPause();
			 GUIManager::getInstance().guiDialog->showGUI("Do you want to continue the last game?", &okContinueLastGame, false, &cancelFunctionPika, NULL, "btnNewGame.png");
		 }
	 }
	
 }

 void GUIPika::newGame() {
     effBomb->setVisible(false);
	 timeAds = 0;
     state   = GameStatePika::PLAY_PIKA;
	 
	 background->getImg()->stopAllActions();
	// background->getImg()->setColor(c3(0, 100, 100));
	// background->getImg()->runAction(TintTo::create(timeGame - currentTime, c3(150, 0, 0)));
	// boardData->resetLevel(level);
	 currentTouch->x = -1;

	 for (int i = NUM_ROW_PIKA - 1; i >= 0; i--)
	 {
		 for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			 if (boardData->arrayBall[i][j] >= 0) {
				 arrayNumber[i][j]->setNumber(boardData->arrayBall[i][j]);
				 arrayNumber[i][j]->setSelect(false);
				 arrayNumber[i][j]->setVisible(true);
				 arrayNumber[i][j]->effectNewGame(GameUtility::getRandom() * 0.4);
			 }
			 else {
				 arrayNumber[i][j]->setVisible(false);
			 }
		 }
	 }

	 JNIUtils::showAds(0);
	 startMode();
	 for (int i = 0; i < 10; i++) {
		 arrayPlayTime[i] = false;
	 }
	 for (int i = 0; i < 4; i++) {
		 arrayLine[i]->setVisible(false);
	 }
 }

 void GUIPika::resetGame()
 {
	 for(int i = 0; i < NUM_ROW_PIKA; i++)
		 for(int j = 0; j < NUM_COLUMN_PIKA; j++)
		 {
			 if(arrayNumber[i][j] != NULL)
			 {
				 this->removeChild(arrayNumber[i][j]->ball);
				 this->removeChild(arrayNumber[i][j]->image);
				 arrayNumber[i][j] = NULL;
			 }
		 }

	 for(int i = 0; i < arrayEffectN.size(); i++)
	 {
		 this->removeChild(arrayEffectN.at(i)->ball);
		 this->removeChild(arrayEffectN.at(i)->image);
	 }
	 arrayEffectN.clear();
	 updateScore();
 }

 void okEndPika()
 {
	 GUIManager::getInstance().guiPika->level = 1;
	 GUIManager::getInstance().guiPika->timeAds = 0;
	 GUIManager::getInstance().guiPika->makeNewLevel();
 }

 void GUIPika::endGame() {
     state = END_PIKA;
	 if (gameMode == GameMode::NORMAL_MODE) {
		 game->isPlayingPika = false;
		 UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
		 JNIUtils::sendEvent(("normal_" + GameUtility::toString(level)).c_str(), GameUtility::toString(countLife).c_str());
	 }
	 
	 string s;
	 for (int i = 0; i < NUM_ROW_PIKA; i++)
		 for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			 if (arrayNumber[i][j]->isVisible()) {
				 arrayNumber[i][j]->effectEndGame(GameUtility::getRandom() * 0.3);

				// showParticleFire(arrayNumber[i][j]->getX(), arrayNumber[i][j]->getY(), boardData->arrayBall[i][j]);

				 //DBArmatureNode* effBest = getEffectBomb();
				 //if (effBest)
				 //{
					// effBest->setPosition(Vec2(arrayNumber[i][j]->getX(), arrayNumber[i][j]->getY()));
					// //effBest->setVisible(false);
					// effBest->gotoAndPlay("run", GameUtility::getRandom() * 1.0, -1, 1);
					// effBest->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
					//	 armature->setVisible(false);
					// });
				 //}
			 }
		 }
    // JNIUtils::preloadAdsInter();
	 runAction(Sequence::create(DelayTime::create(1.5f), CallFunc::create(AX_CALLBACK_0(GUIPika::callbackEndGame, this)), NULL));
 }

 void GUIPika::callbackEndGame() {
	 if (gameMode == GameMode::NORMAL_MODE)
	 {
		 if (score == game->highscorePika) {
			 GameSound::playWin();
		 }
		 else {
			 GameSound::playLose();
		 }
		 GUIManager::getInstance().guiResult->showGUI(score, game->highscorePika);
	 }
	 
	 UserDefault::getInstance()->flush();
	 // GUIManager::getInstance().guiDialog->showGUI(s.c_str(), &okEnd, true);
	 
 }

 void GUIPika::showParticle(BlockItem* number) {
	
 }

 void GUIPika::showParticleFire(float posX, float posY, int id) {
	 GameSound::playChooseBall();
	 Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	 ParticleEffect *effect = new ParticleEffect();
	 effect->create("ParticlesGame/bigbet.plist", layer);
	 effect->particle->setPosition(posX, posY);
	 effect->particle->setBlendAdditive(false);
	 Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	 float scale = WIDTH_BALL_PIKA / size.height / 0.1f * 1.5f;
	 effect->particle->setScale(scale);
    // effect->particle->setTexture(
    //TextureCache::sharedTextureCache()->addImage(("480_800/icon_" + GameUtility::toString(id + 1) + ".png").c_str()));
	// AXLOGD("Color %i %i %i ", color.r, color.g, color.b);
	// Color color1 = c4FFromc3B(color);
	 //effect->particle->setStartColor(color1);
	 //effect->particle->setEndColor(color1);
 }

 bool GUIPika::onTouchBegan( Touch*touch, Event* event )
 {
	// TODO Auto-generated method stub
	PointGame* point = convertPoint(touch->getLocation().x, touch->getLocation().y);
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    JNIUtils::showAdsBanner(0);
	if (state == GameStatePika::PLAY_PIKA) {
		if (point->x < 0 || point->x >= NUM_COLUMN_PIKA || point->y < 0 || point->y >= NUM_ROW_PIKA) {

		} else if (boardData->arrayBall[point->y][point->x] >= 0) {
			state = GameStatePika::TOUCH_PIKA;
			boardData->updatePoint(point->x, point->y);
			arrayNumber[point->y][point->x]->setSelect(true);
			GameSound::playClick();
		}
	} else if (state == GameStatePika::TOUCH_PIKA) {

		if (point->x < 0 || point->x >= NUM_COLUMN_PIKA || point->y < 0 || point->y >= NUM_ROW_PIKA) {

		} else if (point->x == boardData->currentPoint->x && point->y == boardData->currentPoint->y) {

		} else {
			touchPoint2->y = point->y;
			touchPoint2->x = point->x;
			touchPoint1->y = boardData->currentPoint->y;
			touchPoint1->x = boardData->currentPoint->x;
			float fix = size.height * 0.015f;
			if (boardData->checkCanEat(point)) {

				vector<PointGame*> way = boardData->getWay(point);
				PointGame* nextPoint = way.at(0);
				for(int i = 1; i < way.size() && i < 4; i++)
				{
					if(nextPoint->y == way.at(i)->y)
					{
						arrayLine[i]->setScaleY(fix / arrayLine[i]->getHeight());
						float add = way.at(i)->x > nextPoint->x ? fix : -fix;
						arrayLine[i]->setScaleX(((-nextPoint->x + way.at(i)->x) * (WIDTH_BALL_PIKA + pad) + add) / arrayLine[i]->getWidth());
						arrayLine[i]->setPosition(arrayNumber[nextPoint->y][nextPoint->x]->x + WIDTH_BALL_PIKA * 0.5f - add * 0.5f, arrayNumber[nextPoint->y][nextPoint->x]->y+ HEIGHT_BALL_PIKA * 0.5f - fix * 0.5f);
					}
					else
					{
						float add = way.at(i)->y > nextPoint->y ? fix : -fix;
						arrayLine[i]->setScaleX(size.height * 0.015f / arrayLine[i]->getWidth());
						arrayLine[i]->setScaleY(((-nextPoint->y + way.at(i)->y) * (HEIGHT_BALL_PIKA + pad) + add)/ arrayLine[i]->getHeight());
						arrayLine[i]->setPosition(arrayNumber[nextPoint->y][nextPoint->x]->x + WIDTH_BALL_PIKA * 0.5f - fix * 0.5f, arrayNumber[nextPoint->y][nextPoint->x]->y+ HEIGHT_BALL_PIKA * 0.5f - add * 0.5f );
					}
					nextPoint = way.at(i);
					arrayLine[i]->setVisible(true);
				}

				showParticleFire(arrayNumber[touchPoint1->y][touchPoint1->x]->x + WIDTH_BALL_PIKA * 0.5f,
					arrayNumber[touchPoint1->y][touchPoint1->x]->y + HEIGHT_BALL_PIKA * 0.4f, boardData->arrayBall[touchPoint1->y][touchPoint1->x]);

				showParticleFire(arrayNumber[touchPoint2->y][touchPoint2->x]->x + WIDTH_BALL_PIKA * 0.5f,
					arrayNumber[touchPoint2->y][touchPoint2->x]->y + HEIGHT_BALL_PIKA * 0.4f,boardData->arrayBall[touchPoint2->y][touchPoint2->x]);

				runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create(AX_CALLBACK_0(GUIPika::finishEat, this)), NULL));
				state = GameStatePika::EFFECT_PIKA;
				boardData->resetCheck();
				//score = score + 10;
				targetScore = targetScore + 10;
				deltaScore = (targetScore - score) / 10;
				//updateScore();
				boardData->arrayBall[touchPoint1->y][touchPoint1->x] = -1;
				boardData->arrayBall[touchPoint2->y][touchPoint2->x] = -1;
				//timeBonus = timeBonus + 4;
				targetBonus = timeBonus + 5;
				deltaBonus = 5.0f / 30;
			}
			else
			{
				if(arrayNumber[point->y][point->x]->isVisible())
				{
					state = GameStatePika::PLAY_PIKA;
					arrayNumber[boardData->currentPoint->y][boardData->currentPoint->x]->setSelect(false);
					boardData->resetCheck();
					GameSound::playHit();
					//Log.println("CAN MOVE " + boardData->checkCanMove());
				}
			}
		}


	}
	return BaseGUI::onTouchBegan(touch, event);
 }

 void GUIPika::updateScore() {
	 // TODO Auto-generated method stub
	 labelScore->setString(("" + GameUtility::standardizeNumber(score)).c_str());
	 if (gameMode == GameMode::NORMAL_MODE)
	 {
		 if(score > game->highscorePika)
		 {
			 game->highscorePika = score;
             labelHighscore->setString((GameUtility::standardizeNumber(score)).c_str());
             UserDefault::getInstance()->setIntegerForKey("highscorePika", game->highscorePika);
			 UserDefault::getInstance()->flush();
		 }
	 }
	 
 }

 void GUIPika::checkNewLevel()
 {
     if (gameMode == GameMode::NORMAL_MODE || gameMode == GameMode::CHALLENGE_MODE)
     {
         level++;
         labelLevel->setString(("Level: " + GameUtility::toString(level)).c_str());

         // if (level <= 7) {
         genRowColumnTime();
         /*if (level == 7)
                boardData->resetLevel(level);
         else*/
         boardData->reset(level);
         currentTime = 0;
         saveData();
         startGameAfterGen();
         onPause();
         // JNIUtils::preloadAdsInter();
         GUIManager::getInstance().guiDialog->showGUI(("You have finished level " + to_string(level - 1)).c_str(),
                                                     &okFunctionPika, true);
         //}
         // else
         //{
         //// JNIUtils::preloadAdsInter();
         // endGame();
         //}

         timeAds = 0;
     }
	 else
	 {
		 level++;
		 labelLevel->setString(("Level: " + GameUtility::toString(level)).c_str());
		 
		 if (level <= 11) {
			 genRowColumnTime();
			 boardData->reset(level);
			 currentTime = 0;
			 saveData();
			 startGameAfterGen();
			 if (level > 2 && level % 3 == 0)
			 {
				 onPause();
				// JNIUtils::preloadAdsInter();
				 GUIManager::getInstance().guiDialog->showGUI(("You have finished level " + to_string(level - 1)).c_str(), &okFunctionPika, true);
			 }
		 }
		 else
		 {
			// JNIUtils::preloadAdsInter();
			 endGame();
		 }
		 timeAds = 0;
	 }
 }

 void GUIPika::effectStar(Vec2 posStart, Vec2 posEnd, float time)
 {
	 string resource = "ParticlesGame/stars.png";
	 Node* parent = this;
	 Sprite* fairy = Sprite::create(resource);
	 parent->addChild(fairy);
	 fairy->setScale(0.8);
	 fairy->setPosition(posStart);

	 Vec2 posMedium = Vec2((posStart.x + posEnd.x) * 0.5, (posStart.y + posEnd.y) * 0.5 - 100 - 200 * GameUtility::getRandom());
	 ccBezierConfig bezier;
	 bezier.controlPoint_1 = posStart;
	 bezier.controlPoint_2 = posMedium;
	 bezier.endPosition = posEnd;
	 fairy->runAction(
		 Sequence::create(
			 EaseInOut::create(BezierTo::create(time, bezier), 1),
			 RemoveSelf::create(),
			 NULL
		 )
	 );

	 fairy->runAction(
		 RepeatForever::create(
			 Sequence::create(
				 FadeIn::create(0.02), CallFuncN::create(AX_CALLBACK_1(GUIPika::callbackEffectStar, this)),
				 NULL
			 )
		 )
	 );
 }


 void GUIPika::callbackEffectStar(Node* sender)
 {
	 string resource = "ParticlesGame/stars.png";
	 float random = floor(GameUtility::getRandom() * 3 + 2);
	 AXLOGD("RUn here");
	 for (int i = 0; i < random; i++) {
		 Sprite* sprite = Sprite::create(resource);
             sprite->setBlendFunc(BlendFunc{backend::BlendFactor::DST_COLOR, backend::BlendFactor::ONE});
		 sprite->setPosition(sender->getPosition());
		 this->addChild(sprite);
		 float randomTime = GameUtility::getRandom() * 2 + 1;
		 float rAction1 = GameUtility::getRandom();
		 float rAction2 = GameUtility::getRandom();
		 float rScale = GameUtility::getRandom() * 0.3 + 0.2;
		 float rOpacity = GameUtility::getRandom() * 100 + 155;
		 float rTimeOpacity = GameUtility::getRandom();
		 float rTimeBlink = GameUtility::getRandom() + 0.1;
		 Vec2 pos = sprite->getPosition();
		 sprite->setScale(rScale);
		 sprite->setOpacity(rOpacity);
		 sprite->setPosition(pos);
		 Vec2 p1 = pos;
		 Vec2 p2 = Vec2(pos.x + GameUtility::getRandom() * 40 + 20, pos.y - GameUtility::getRandom() * 150 + 75);
		 Vec2 p3 = Vec2(p1.x / 2 + p2.x / 2 + GameUtility::getRandom() * 50 - 25, p1.y / 2 + p2.y / 2 + GameUtility::getRandom() * 100 - 50);
		 Vec2 p4 = Vec2(p1.x / 2 + p2.x / 2 + GameUtility::getRandom() * 50 - 25, p1.y / 2 + p2.y / 2 + GameUtility::getRandom() * 100 - 50);
		 ccBezierConfig bezier;
		 bezier.controlPoint_1 = p2;
		 bezier.controlPoint_2 = p3;
		 bezier.endPosition = p4;
		 sprite->runAction(
			 Sequence::create(
				 Spawn::create(
					 BezierTo::create(randomTime, bezier),
					 Sequence::create(
						 FadeOut::create(randomTime),
						 NULL
					 ),
					 NULL
				 ),
				 RemoveSelf::create(),
				 NULL
			 )
		 );
		 sprite->runAction(
			 RepeatForever::create(
				 Sequence::create(
					 Spawn::create(
						 Sequence::create(
							 FadeIn::create(rTimeBlink),
							 FadeOut::create(rTimeBlink),
							 NULL
						 ),
						 NULL
					 ),
					 NULL
				 )
			 )
		 );
	 }
 }

 void GUIPika::finishEat()
 {
	 int i;
	 for(i = 0; i < 4; i++)
	 {
		 arrayLine[i]->setVisible(false);
	 }

	 arrayNumber[touchPoint1->y][touchPoint1->x]->setVisible(false);
	 arrayNumber[touchPoint2->y][touchPoint2->x]->setVisible(false);
	 boardData->arrayBall[touchPoint1->y][touchPoint1->x] = -1;
	 boardData->arrayBall[touchPoint2->y][touchPoint2->x] = -1;
	 state = GameStatePika::PLAY_PIKA;
	 if(boardData->checkEnd())
	 {
		 // Ket thuc level nay
		 //score = score + (progress->getPercentage() / 100 * timeGame) * 10 + 100;
		 targetScore = targetScore + (progress->getPercentage() / 100 * timeGame) * 10 + 100 * level;
		 deltaScore = (targetScore - score) / 100;
		 
		 progress->stopAllActions();
		 progress->runAction(Sequence::create(ProgressTo::create(0.2, 0), DelayTime::create(1.0)
			 , CallFunc::create(AX_CALLBACK_0(GUIPika::checkNewLevel, this)), NULL));
		 float targetX = progress->getPositionX() + (progress->getPercentage() / 100 - 0.5) * progress->getContentSize().width * progress->getScaleX();
		 Vec2 posStart = Vec2(progress->getPositionX() + (progress->getPercentage() / 100 - 0.5) * progress->getContentSize().width, progress->getPositionY());
		 posStart = bgProgress->convertToWorldSpace(posStart);
		 //targetX = bgProgressBonus->getPositionX() - bgProgressBonus->getRealWidth() * 0.5 + 
		 effectStar(Vec2(targetX, bgProgress->getPositionY()), bgScore->getPosition(), 1.0);
		// GameSound::playGift();
		 
		 state = GameStatePika::END_PIKA;
		 return;
	 }
	 
	 PointGame* p1, *p2;
	 bool countInvisible = false;
	 //if (gameMode == GameMode::NORMAL_MODE || gameMode == GameMode::CHALLENGE_MODE) {
		/* GameType arrayType[6] = { DOWN_PIKA, UP_PIKA, RIGHT_PIKA, LEFT_PIKA, CENTER, NORMAL };
		 int index = GameUtility::getRandom() * 5.999;
		 gameType = arrayType[index];*/
	 //}
	 switch (gameType) {
	 case DOWN_PIKA:

		 if(touchPoint1->x == touchPoint2->x)
		 {
			 if(touchPoint1->y < touchPoint2->y)
			 {
				 p1 = touchPoint1;
				 p2 = NULL;
			 }
			 else
			 {
				 p1 = touchPoint2;
				 p2 = NULL;
			 }
			 countInvisible = true;
		 }
		 else
		 {
			 p1 = touchPoint1;
			 p2 = touchPoint2;
		 }

		 for(i = p1->y + 1; i < NUM_ROW_PIKA; i++)
		 {
			 if(arrayNumber[i][p1->x]->isVisible())
			 {
				 int j;
				 for(j = i - 1; j > 0; j--)
				 {
					 if(boardData->arrayBall[j][p1->x] != -1)
					 {
						 break;
					 }
				 }
				 j = j + 1;

				 arrayNumber[j][p1->x]->setNumber(arrayNumber[i][p1->x]->id);
				 arrayNumber[j][p1->x]->setVisible(true);
				 arrayNumber[j][p1->x]->setSelect(false);
				 boardData->arrayBall[i][p1->x] = -1;
				 arrayNumber[i][p1->x]->setVisible(false);
				 boardData->arrayBall[j][p1->x] = arrayNumber[i][p1->x]->id;
				// arrayNumber[j][p1->x]->setPosition(arrayNumber[i][p1->x]->getX(), arrayNumber[i][p1->x]->getY());
				 arrayNumber[j][p1->x]->runAction(0, (j - i)* (HEIGHT_BALL_PIKA + pad));
			 }
			 else
			 {
				 if(countInvisible)
					 countInvisible = false;
				 else
					 break;
			 }
		 }
		 for(i--; i < NUM_ROW_PIKA; i++)
		 {
			 arrayNumber[i][p1->x]->setVisible(false);
			 boardData->arrayBall[i][p1->x] = -1;

		 }
		 if(p2 != NULL)
		 {
			 for(i = p2->y + 1; i < NUM_ROW_PIKA; i++)
			 {
				 if(arrayNumber[i][p2->x]->isVisible())
				 {
					 arrayNumber[i - 1][p2->x]->setNumber(arrayNumber[i][p2->x]->id);
					 arrayNumber[i - 1][p2->x]->setVisible(true);
					 arrayNumber[i - 1][p2->x]->setSelect(false);
					 arrayNumber[i][p2->x]->setVisible(false);
					 boardData->arrayBall[i - 1][p2->x] = arrayNumber[i][p2->x]->id;
					 boardData->arrayBall[i][p2->x] = -1;
					// arrayNumber[i - 1][p2->x]->setPosition(arrayNumber[i][p2->x]->getX(), arrayNumber[i][p2->x]->getY());
					 arrayNumber[i - 1][p2->x]->runAction(0, -HEIGHT_BALL_PIKA - pad);
				 }
				 else
				 {
					 break;
				 }
			 }
			 for(i--; i < NUM_ROW_PIKA; i++)
			 {
				 arrayNumber[i][p2->x]->setVisible(false);
				 boardData->arrayBall[i][p2->x] = -1;
			 }
		 }
		 break;

	 case UP_PIKA:
		 if(touchPoint1->x == touchPoint2->x)
		 {
			 if(touchPoint1->y > touchPoint2->y)
			 {
				 p1 = touchPoint1;
				 p2 = NULL;
			 }
			 else
			 {
				 p1 = touchPoint2;
				 p2 = NULL;
			 }
			 countInvisible = true;
		 }
		 else
		 {
			 p1 = touchPoint1;
			 p2 = touchPoint2;
		 }

		 for(i = p1->y - 1; i > 0; i--)
		 {
			 if(arrayNumber[i][p1->x]->isVisible())
			 {
				 int j;
				 for(j = i + 1; j < NUM_ROW_PIKA - 1; j++)
				 {
					 if(boardData->arrayBall[j][p1->x] != -1)
					 {
						 break;
					 }
				 }
				 j = j - 1;

				 arrayNumber[j][p1->x]->setNumber(arrayNumber[i][p1->x]->id);
				 arrayNumber[j][p1->x]->setVisible(true);
				 arrayNumber[j][p1->x]->setSelect(false);
				 boardData->arrayBall[i][p1->x] = -1;
				 arrayNumber[i][p1->x]->setVisible(false);
				 boardData->arrayBall[j][p1->x] = arrayNumber[i][p1->x]->id;
				// arrayNumber[j][p1->x]->setPosition(arrayNumber[i][p1->x]->getX(), arrayNumber[i][p1->x]->getY());
				 arrayNumber[j][p1->x]->runAction(0, (j - i)* (HEIGHT_BALL_PIKA + pad));
			 }
			 else
			 {
				 if(countInvisible)
					 countInvisible = false;
				 else
					 break;
			 }
		 }
		 for(i++; i > 0; i--)
		 {
			 arrayNumber[i][p1->x]->setVisible(false);
			 boardData->arrayBall[i][p1->x] = -1;

		 }
		 if(p2 != NULL)
		 {
			 for(i = p2->y - 1; i > 0; i--)
			 {
				 if(arrayNumber[i][p2->x]->isVisible())
				 {
					 arrayNumber[i + 1][p2->x]->setNumber(arrayNumber[i][p2->x]->id);
					 arrayNumber[i + 1][p2->x]->setVisible(true);
					 arrayNumber[i + 1][p2->x]->setSelect(false);
					 arrayNumber[i][p2->x]->setVisible(false);
					 boardData->arrayBall[i + 1][p2->x] = arrayNumber[i][p2->x]->id;
					 boardData->arrayBall[i][p2->x] = -1;
					 //arrayNumber[i + 1][p2->x]->setPosition(arrayNumber[i][p2->x]->getX(), arrayNumber[i][p2->x]->getY());
					 arrayNumber[i + 1][p2->x]->runAction(0, HEIGHT_BALL_PIKA + pad);

				 }
				 else
				 {
					 break;
				 }
			 }
			 for(i++; i > 0; i--)
			 {
				 arrayNumber[i][p2->x]->setVisible(false);
				 boardData->arrayBall[i][p2->x] = -1;
			 }
		 }
		 break;
	 case RIGHT_PIKA:
		 if(touchPoint1->y == touchPoint2->y)
		 {
			 if(touchPoint1->x > touchPoint2->x)
			 {
				 p1 = touchPoint1;
				 p2 = NULL;
			 }
			 else
			 {
				 p1 = touchPoint2;
				 p2 = NULL;
			 }
			 countInvisible = true;
		 }
		 else
		 {
			 p1 = touchPoint1;
			 p2 = touchPoint2;
		 }

		 for(i = p1->x - 1; i > 0; i--)
		 {
			 if(arrayNumber[p1->y][i]->isVisible())
			 {
				 int j;
				 for(j = i + 1; j < NUM_COLUMN_PIKA - 1; j++)
				 {
					 if(boardData->arrayBall[p1->y][j] != -1)
					 {
						 break;
					 }
				 }
				 j = j - 1;

				 arrayNumber[p1->y][j]->setNumber(arrayNumber[p1->y][i]->id);
				 arrayNumber[p1->y][j]->setVisible(true);
				 arrayNumber[p1->y][j]->setSelect(false);
				 boardData->arrayBall[p1->y][i] = -1;
				 arrayNumber[p1->y][i]->setVisible(false);
				 boardData->arrayBall[p1->y][j] = arrayNumber[p1->y][i]->id;
				 //arrayNumber[p1->y][j]->setPosition(arrayNumber[p1->y][i]->getX(), arrayNumber[p1->y][i]->getY());
				 arrayNumber[p1->y][j]->runAction((j - i)* (WIDTH_BALL_PIKA + pad), 0);
			 }
			 else
			 {
				 if(countInvisible)
					 countInvisible = false;
				 else
					 break;
			 }
		 }
		 for(i++; i > 0; i--)
		 {
			 arrayNumber[p1->y][i]->setVisible(false);
			 boardData->arrayBall[p1->y][i] = -1;

		 }
		 if(p2 != NULL)
		 {
			 for(i = p2->x - 1; i > 0; i--)
			 {
				 if(arrayNumber[p2->y][i]->isVisible())
				 {
					 arrayNumber[p2->y][i + 1]->setNumber(arrayNumber[p2->y][i]->id);
					 arrayNumber[p2->y][i + 1]->setVisible(true);
					 arrayNumber[p2->y][i + 1]->setSelect(false);
					 arrayNumber[p2->y][i]->setVisible(false);
					 boardData->arrayBall[p2->y][i + 1] = arrayNumber[p2->y][i]->id;
					 boardData->arrayBall[p2->y][i] = -1;
				//	 arrayNumber[p2->y][i]->setPosition(arrayNumber[p2->y][i]->getX(), arrayNumber[p2->y][i]->getY());
					 arrayNumber[p2->y][i]->runAction(WIDTH_BALL_PIKA + pad, 0);
				 }
				 else
				 {
					 break;
				 }
			 }
			 for(i++; i > 0; i--)
			 {
				 arrayNumber[p2->y][i]->setVisible(false);
				 boardData->arrayBall[p2->y][i] = -1;
			 }
		 }
		 break;
	 case LEFT_PIKA:

		 if(touchPoint1->y == touchPoint2->y)
		 {
			 if(touchPoint1->x < touchPoint2->x)
			 {
				 p1 = touchPoint1;
				 p2 = NULL;
			 }
			 else
			 {
				 p1 = touchPoint2;
				 p2 = NULL;
			 }
			 countInvisible = true;
		 }
		 else
		 {
			 p1 = touchPoint1;
			 p2 = touchPoint2;
		 }

		 for(i = p1->x + 1; i < NUM_COLUMN_PIKA; i++)
		 {
			 if(arrayNumber[p1->y][i]->isVisible())
			 {
				 int j;
				 for(j = i - 1; j > 0; j--)
				 {
					 if(boardData->arrayBall[p1->y][j] != -1)
					 {
						 break;
					 }
				 }
				 j = j + 1;

				 arrayNumber[p1->y][j]->setNumber(arrayNumber[p1->y][i]->id);
				 arrayNumber[p1->y][j]->setVisible(true);
				 arrayNumber[p1->y][j]->setSelect(false);
				 boardData->arrayBall[p1->y][i] = -1;
				 arrayNumber[p1->y][i]->setVisible(false);
				 boardData->arrayBall[p1->y][j] = arrayNumber[p1->y][i]->id;
			//	 arrayNumber[p1->y][j]->setPosition(arrayNumber[p1->y][i]->getX(), arrayNumber[p1->y][i]->getY());
				 arrayNumber[p1->y][j]->runAction((j - i)* (WIDTH_BALL_PIKA + pad), 0);
			 }
			 else
			 {
				 if(countInvisible)
					 countInvisible = false;
				 else
					 break;
			 }
		 }
		 for(i--; i < NUM_COLUMN_PIKA; i++)
		 {
			 arrayNumber[p1->y][i]->setVisible(false);
			 boardData->arrayBall[p1->y][i] = -1;

		 }
		 if(p2 != NULL)
		 {
			 for(i = p2->x + 1; i < NUM_COLUMN_PIKA; i++)
			 {
				 if(arrayNumber[p2->y][i]->isVisible())
				 {
					 arrayNumber[p2->y][i - 1]->setNumber(arrayNumber[p2->y][i]->id);
					 arrayNumber[p2->y][i - 1]->setVisible(true);
					 arrayNumber[p2->y][i - 1]->setSelect(false);
					 arrayNumber[p2->y][i]->setVisible(false);
					 boardData->arrayBall[p2->y][i - 1] = arrayNumber[p2->y][i]->id;
					 boardData->arrayBall[p2->y][i] = -1;
					// arrayNumber[p2->y][i - 1]->setPosition(arrayNumber[p2->y][i]->getX(), arrayNumber[p2->y][i]->getY());
					 arrayNumber[p2->y][i - 1]->runAction(-WIDTH_BALL_PIKA - pad, 0);
				 }
				 else
				 {
					 break;
				 }
			 }
			 for(i--; i < NUM_ROW_PIKA; i++)
			 {
				 arrayNumber[p2->y][i]->setVisible(false);
				 boardData->arrayBall[p2->y][i] = -1;
			 }
		 }
		 break;
	 case CENTER_PIKA:
		 {
			 int num = (NUM_COLUMN_PIKA - 2)/ 2;
			 int numEmpty = 0;
			 int row = touchPoint1->y;
			 doCenter(row);
			 if(touchPoint2->y != row)
			 {
				 doCenter(touchPoint2->y);
			 }
		 }
		
		 break;
	 default:
		 break;
	 }

	 if (gameMode == GameMode::NORMAL_MODE) {
		 game->isPlayingPika = true;
	 }
	 
	 if(arrayEffectN.size() > 0)
	 {
		 runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create(AX_CALLBACK_0(GUIPika::callbackEffect, this)), NULL));
	 }
	 else
	 {
		 newData();
	 }
	 saveData();
 }

 void GUIPika::newData()
 {
	 if(boardData->checkCanMove() == false)
	 {
		 boardData->newData(level);
		 for (int i = 0; i < NUM_ROW_PIKA; i++)
			 for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
				 if (boardData->arrayBall[i][j] >= 0) {
					 arrayNumber[i][j]->setVisible(true);
					 arrayNumber[i][j]->setNumber(boardData->arrayBall[i][j]);
				 } else {
					 arrayNumber[i][j]->setVisible(false);
				 }
			 }
			if (gameMode == GameMode::NORMAL_MODE || gameMode == GameMode::CHALLENGE_MODE)
			 {
				 countLife--;
				 if(countLife <= 0)
				 {
					 JNIUtils::sendEvent("out_of_life", GameUtility::toString(level).c_str());
					 endGame();
				 }
				 labelLife->setString(("" + GameUtility::toString(countLife)).c_str());
			 }
	 }

 }

 void GUIPika::doCenter(int row)
 {
	 int numEmpty = 0;
	 int i, count1 = 0, count2 = 0;
	 for(i = 0; i <= (NUM_COLUMN_PIKA - 2)/2; i++)
		 if(arrayNumber[row][i]->isVisible())
			 count1++;
	 for(i = NUM_COLUMN_PIKA/2; i < NUM_COLUMN_PIKA ; i++)
		 if(arrayNumber[row][i]->isVisible())
			 count2++;
	 if(count1 == 0 && count2 == 0)
		 return;
	 if(abs(count1-count2) < 2)
	 {
		 int check = 0; // mot lan dut doan
		 for(i = 0; i < NUM_COLUMN_PIKA; i++)
		 {
			 if(arrayNumber[row][i]->isVisible())
			 {
				 check = 1;
				 break;
			 }
		 }
		 for(i++; i < NUM_COLUMN_PIKA; i++)
			 if(!arrayNumber[row][i]->isVisible())
			 {
				 check++;
				 break;
			 }
			 for(i++; i < NUM_COLUMN_PIKA; i++)
				 if(arrayNumber[row][i]->isVisible())
				 {
					 check++;
					 break;
				 }
				 if(check < 3)
					 return;
	 }
	 int saveId[BOARD_COLUMN_PIKA];
	 for(i = 1; i < NUM_COLUMN_PIKA - 1; i++)
	 {
		 if(!arrayNumber[row][i]->isVisible())
		 {
			 numEmpty++;
		 }
		 else
		 {
			 saveId[i] = arrayNumber[row][i]->id;
		 }
	 }
	 int numAvailable = NUM_COLUMN_PIKA - 2 - numEmpty;
	 int startX = numEmpty / 2 + 1;
	 int newRow[BOARD_COLUMN_PIKA];
	 int j = 1;
	 for(i = startX; i - startX < numAvailable; i++)
	 {
		 for(; j < NUM_COLUMN_PIKA - 1; j++)
			 if(arrayNumber[row][j]->isVisible())
				 break;
		 newRow[i] = j;
		 arrayNumber[row][j]->setVisible(false);
	 }
	 for(i = startX; i - startX < numAvailable; i++)
	 {
		 if(newRow[i] != i)
		 {
			 arrayNumber[row][i]->setNumber(saveId[newRow[i]]);
			 arrayNumber[row][i]->setVisible(true);
			 arrayNumber[row][i]->setSelect(false);
			 //arrayNumber[row][i]->setVisible(false);
			 boardData->arrayBall[row][i] = arrayNumber[row][i]->id;
			 //boardData->arrayBall[row][newRow[i]] = -1;
			 BlockItem* n = new BlockItem();
			 n->setNumber(arrayNumber[row][i]->id);
			 AXLOGD("pos %f %f ", arrayNumber[row][newRow[i]]->getX(), arrayNumber[row][newRow[i]]->getY());
			// arrayNumber[row][i]->setPosition(arrayNumber[row][newRow[i]]->getX(), arrayNumber[row][newRow[i]]->getY());
			// n->addToParent(this);
			// arrayNumber[row][i]->runAction((i - newRow[i]) * (WIDTH_BALL_PIKA + pad), 0);
			 n->boss = new PointGame(i, row);
			// arrayEffectN.push_back(n);
		 }
		 else
		 {
			 arrayNumber[row][i]->setVisible(true);
		 }
	 }
	 AXLOGD("ljfdsj  %i ", i);
	 for(i = 1; i < startX; i++)
		 boardData->arrayBall[row][i] = -1;
	 for(i = startX + numAvailable; i < NUM_COLUMN_PIKA; i++)
		 boardData->arrayBall[row][i] = -1;
	
 }



 PointGame* GUIPika::convertPoint(float x, float y) {
	 PointGame* currentTouch = new PointGame();
	 currentTouch->x = (int) ((x - START_X_PIKA) / (WIDTH_BALL_PIKA + pad));
	 currentTouch->y = (int) floor(((y - START_Y_PIKA) / (HEIGHT_BALL_PIKA + pad)));

	 return currentTouch;
 }

 PointGame* GUIPika::checkNotMove(PointGame* center, int id) {
	 // if(center->y > START_Y_PIKA + WIDTH_BALL_PIKA * )

	 float posX, posY;
	 posX = center->x - WIDTH_BALL_PIKA * 0.5f;
	 posY = center->y + WIDTH_BALL_PIKA * 0.5f;

	 for (int i = 0; i < 2; i++)
		 for (int j = 0; j < 2; j++) {

			 posX = center->x + (i * 2 - 1) * WIDTH_BALL_PIKA * 0.5f;
			 posY = center->y + (j * 2 - 1) * WIDTH_BALL_PIKA * 0.5f;

			 PointGame* pointCheck = convertPoint(posX, posY);
			 if (pointCheck->x >= 0 && pointCheck->y >= 0 && pointCheck->x < 7) {
				 if (pointCheck->y < 8 && pointCheck->y >= 0 && arrayNumber[pointCheck->y][pointCheck->x]->isVisible()
					 && arrayNumber[pointCheck->y][pointCheck->x]->id != id) {
						 return pointCheck;
				 }
			 }
		 }

		 return NULL;
 }


 vector<BlockItem*> GUIPika::getListTouch(BlockItem* number) {
	 vector<BlockItem*> arrayN;

	 float posX, posY;
	 PointGame* center = new PointGame(number->getX() + WIDTH_BALL_PIKA * 0.5f, number->getY() + WIDTH_BALL_PIKA * 0.5f);

	 for (int i = 0; i < 2; i++)
		 for (int j = 0; j < 2; j++) {

			 posX = center->x + (i * 2 - 1) * WIDTH_BALL_PIKA * 0.5f;
			 posY = center->y + (j * 2 - 1) * WIDTH_BALL_PIKA * 0.5f;

			 PointGame* pointCheck = convertPoint(posX, posY);
			 if (pointCheck->x >= 0 && pointCheck->y >= 0 && pointCheck->x < 7) {
				 if (pointCheck->y < 8 && pointCheck->y >= 0 && arrayNumber[pointCheck->y][pointCheck->x]->isVisible()
					 && arrayNumber[pointCheck->y][pointCheck->x]->id != number->id) {
						 arrayN.push_back(arrayNumber[pointCheck->y][pointCheck->x]);
				 }
			 }
		 }

		 return arrayN;
 }


 int GUIPika::getFirstVisible() {
	 int row = 0;
	 for (int i = 0; i < 8; i++) {
		 int j;
		 for (j = 0; j < 7; j++) {
			 if (arrayNumber[i][j]->isVisible()) {
				 break;
			 }
		 }
		 if (j != 7) {
			 row = i;
			 break;
		 }
	 }
	 if (row != 0) {
		 START_Y_PIKA = START_Y_PIKA - row * WIDTH_BALL_PIKA;

		 for (int i = row; i <= currentRow; i++) {
			 for (int j = 0; j < 7; j++) {
				 arrayNumber[i - row][j]->setVisible(arrayNumber[i][j]->isVisible());
				 arrayNumber[i - row][j]->setPosition(arrayNumber[i][j]->getX(), arrayNumber[i][j]->getY());
				 if (arrayNumber[i][j]->isVisible()) {
					 arrayNumber[i - row][j]->setNumber(arrayNumber[i][j]->id);
				 }
			 }
		 }
		 currentRow = currentRow - row;
		 for (int i = currentRow + 1; i < 8; i++) {
			 for (int j = 0; j < 7; j++) {
				 arrayNumber[i][j]->setVisible(false);

			 }
		 }
	 }
	 return 0;
 }

 bool GUIPika::checkCanMove(PointGame* newpoint, PointGame* oldpoint) {
	 // Log.println("CHECK OR DAY NEW POInt " + newpoint->x + " " + newpoint->y
	 // + " OLD POINT " + oldpoint->x + " "
	 // + oldpoint->y);
	 if (newpoint->x != oldpoint->x && newpoint->y != oldpoint->y) {
		 if (newpoint->x > oldpoint->x && newpoint->y > oldpoint->y) {

			 if ((oldpoint->y + 1 < 0 || oldpoint->y + 1 > currentRow || !arrayNumber[oldpoint->y + 1][oldpoint->x]->isVisible())
				 && (oldpoint->y < 0 || oldpoint->x + 1 > 6 || !arrayNumber[oldpoint->y][oldpoint->x + 1]->isVisible()))
				 return true;
			 return false;
		 } else if (newpoint->x > oldpoint->x && newpoint->y < oldpoint->y) {
			 if ((oldpoint->y - 1 < 0 || !arrayNumber[oldpoint->y - 1][oldpoint->x]->isVisible())
				 && (oldpoint->y < 0 || oldpoint->x + 1 > 6 || !arrayNumber[oldpoint->y][oldpoint->x + 1]->isVisible()))
				 return true;
			 return false;
		 } else if (newpoint->x < oldpoint->x && newpoint->y > oldpoint->y) {
			 if ((oldpoint->y + 1 < 0 || oldpoint->y + 1 > currentRow || !arrayNumber[oldpoint->y + 1][oldpoint->x]->isVisible())
				 && (oldpoint->y < 0 || oldpoint->x - 1 < 0 || !arrayNumber[oldpoint->y][oldpoint->x - 1]->isVisible()))
				 return true;
			 return false;
		 } else if (newpoint->x < oldpoint->x && newpoint->y < oldpoint->y) {

			 if ((oldpoint->y - 1 < 0 || !arrayNumber[oldpoint->y - 1][oldpoint->x]->isVisible())
				 && (oldpoint->y < 0 || oldpoint->x - 1 < 0 || !arrayNumber[oldpoint->y][oldpoint->x - 1]->isVisible()))
				 return true;
			 return false;
		 }
	 }
	 return true;

 }

 void GUIPika::onPause() {
	 // TODO Auto-generated method stub
	// if (state == PLAY) {
		// MyCaro.game.caroScreen.showPauseLayer();
         state = PAUSE_PIKA;
	// }
	// progress->cleanup();
	 progress->stopAllActions();
	// saveTime = (progress->getScaleX() / rootProgress * timeGame);
	 bgDark->setVisible(true);
	 btnPlay->setVisible(true);
 }

 void GUIPika::startMode()
 {
	 if (gameMode == GameMode::NORMAL_MODE)
	 {
		// countLife = 10;
		 labelHighscore->setString(("" + GameUtility::standardizeNumber(game->highscorePika)).c_str());
	 }
	 
	 labelLife->setString(("" + GameUtility::toString(countLife)).c_str());
	 labelLevel->setString(("Level: " + GameUtility::toString(level)).c_str());

	 labelScore->setString((GameUtility::standardizeNumber(score)).c_str());
 }

 void GUIPika::callbackEffect()
 {
	 for(int i = 0; i < arrayEffectN.size(); i++)
	 {
		 BlockItem* item = arrayEffectN[i];
		 this->removeChild(item->ball);
		 this->removeChild(item->image);
		 if (item->boss->y < 11 && item->boss->y >= 0 && item->boss->x < 18 && item->boss->x >= 0)
			arrayNumber[item->boss->y][item->boss->x]->setVisible(true);
	 }
	 arrayEffectN.clear();
	 newData();
 }

 void GUIPika::showGui(GameMode mode)
 {
     score = 0;
	 this->gameMode = mode;
	 if (mode == GameMode::CHALLENGE_MODE) {
		 groupBonus->setVisible(true);
		 widthProgress = btnSearch->getPositionX() - btnSearch->getWidth() * 1.0f - (groupBonus->getPositionX() + bgProgressBonus->getRealWidth() * 0.5f);
		 bgProgress->setWidth(widthProgress);
		 bgProgress->setPos(groupBonus->getPositionX() + bgProgressBonus->getRealWidth() * 0.5f + widthProgress * 0.5f + btnSearch->getWidth() * 0.4f, btnBack->getPositionY());
	 }
	 else {
		 groupBonus->setVisible(false);
		 widthProgress = btnSearch->getPositionX() - btnSearch->getWidth() * 0.7f - (iconHeart->getPositionX() + iconHeart->getWidth() * 0.8f);
		 bgProgress->setWidth(widthProgress);
		 bgProgress->setPos(iconHeart->getPositionX() + iconHeart->getWidth() * 0.8f + widthProgress * 0.5f, btnBack->getPositionY());
	 }
	
		  makeNewLevel();
 }

 void GUIPika::saveData() {
	 if (gameMode == GameMode::NORMAL_MODE) {
		 game->saveScorePika = targetScore;
		 game->timePika = currentTime;
		 game->levelPika = level;
		 game->numLifePika = countLife;
		 if (targetScore > game->highscorePika) {
			 game->highscorePika = targetScore;
			 labelHighscore->setString(GameUtility::standardizeNumber(game->highscorePika));
		 }

		 string s = "";
		 int index = 0;
		 for (int i = 0; i < BOARD_ROW_PIKA; i++)
			 for (int j = 0; j < BOARD_COLUMN_PIKA; j++)
			 {
				 if (i == 0 && j == 0)
				 {
					 s = s + GameUtility::toString(boardData->arrayBall[i][j]);
				 }
				 else
				 {
					 s = s + "," + GameUtility::toString(boardData->arrayBall[i][j]);
				 }
				 game->dataPika[i * BOARD_COLUMN_PIKA + j] = boardData->arrayBall[i][j];
			 }
		 UserDefault::getInstance()->setIntegerForKey("numLifePika", game->numLifePika);
		 UserDefault::getInstance()->setIntegerForKey("levelPika", level);
		 UserDefault::getInstance()->setBoolForKey("isPlayingPika1", true);
		 UserDefault::getInstance()->setIntegerForKey("saveScorePika", game->saveScorePika);
		 UserDefault::getInstance()->setIntegerForKey("highscorePika", game->highscorePika);
		 UserDefault::getInstance()->setFloatForKey("timePika", game->timePika);
		 UserDefault::getInstance()->setStringForKey("dataPika", s);
	 }
	 
	 UserDefault::getInstance()->flush();
 }

 void GUIPika::genLevel() {
	 if (gameMode == GameMode::NORMAL_MODE) {
		 if (game->isPlayingPika == false) {
			 level = 1;
		 }
		 else {
			 level = game->levelPika;
		 }
	 }
	 
     
 }

 void GUIPika::genRowColumnTime()
 {
	 Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	 float rateDefault = 800.0f / 480;
	 float rateReal = size.width / size.height;
	 float rateChallenge = size.width * 0.9 / size.height;
	 resetGame();
	 //startMode();
         timeGame       = 200;
         int indexType  = (level - 1) % 6;
         int indexLevel = (level - 1) / 6;

         if (gameMode == GameMode::NORMAL_MODE)
         {
             switch (indexType)
             {
             case 0:
                 gameType = GameType::NORMAL_PIKA;
                 break;
             case 1:
                 gameType = GameType::LEFT_PIKA;
                 break;
             case 2:
                 gameType = GameType::RIGHT_PIKA;
                 break;
             case 3:
                 gameType = GameType::DOWN_PIKA;
                 break;
             case 4:
                 gameType = GameType::UP_PIKA;
                 break;
             case 5:
                 gameType = GameType::CENTER_PIKA;
                 break;
             default:
                 break;
             }

             NUM_COLUMN_PIKA = 16 + indexLevel;
             NUM_ROW_PIKA    = 9 + indexLevel;
             NUM_ROW_PIKA    = NUM_ROW_PIKA > 11 ? 11 : NUM_ROW_PIKA;
             NUM_COLUMN_PIKA = NUM_COLUMN_PIKA > 18 ? 18 : NUM_COLUMN_PIKA;
             timeGame   = 150;
             if (indexLevel == 0)
             {
                 timeGame = 150;
             }
             else if (indexLevel == 1)
             {
                 timeGame = 200;
             }
             else if (indexLevel == 2)
             {
                 timeGame = 300;
             }
             else
             {
                 timeGame = 300 - 5 * indexLevel;
             }

             if (rateReal > rateDefault)
             {
                 NUM_ROW_PIKA    = NUM_ROW_PIKA - 1;
                 NUM_COLUMN_PIKA = NUM_COLUMN_PIKA + 1;
             }

             //  NUM_COLUMN = 10;
             // NUM_ROW = 6;
         }
        // timeGame        = 10;
	 float rateBlock = 0.9;
	 /*if ((gameMode == GameMode::NORMAL_MODE || gameMode == GameMode::CHALLENGE_MODE) && level == 7) {
		 NUM_COLUMN_PIKA = game->arrNumColumn[level];
		 NUM_ROW_PIKA = game->arrNumRow[level];
		 rateBlock = 0.9;
	 }*/

	  //	NUM_ROW_PIKA = 6; NUM_COLUMN_PIKA = 8;
	  //NUM_ROW_PIKA = game->arrNumRow[1];
	  //NUM_COLUMN_PIKA = game->arrNumColumn[1];
     
	 pad = size.width * 0.002f;
	 
		if (NUM_ROW_PIKA * 1.0f / (NUM_COLUMN_PIKA * rateBlock) > size.height / size.width)
		{
			HEIGHT_BALL_PIKA = (size.height - pad * NUM_ROW_PIKA) / (NUM_ROW_PIKA - 0.8f);
			WIDTH_BALL_PIKA = rateBlock * HEIGHT_BALL_PIKA;
			START_Y_PIKA = -0.75f * HEIGHT_BALL_PIKA;
			START_Y_PIKA = size.height - START_Y_PIKA;
			START_X_PIKA = (size.width - NUM_COLUMN_PIKA * WIDTH_BALL_PIKA - (NUM_COLUMN_PIKA - 1) * pad) * 0.5f;
		}
		else
		{
			WIDTH_BALL_PIKA = (size.width - pad * NUM_COLUMN_PIKA) / (NUM_COLUMN_PIKA - 1.2f);
			HEIGHT_BALL_PIKA = WIDTH_BALL_PIKA / rateBlock;
			//START_X_PIKA = -0.6f * WIDTH_BALL_PIKA;
			START_X_PIKA = (size.width - NUM_COLUMN_PIKA * WIDTH_BALL_PIKA - (NUM_COLUMN_PIKA - 1) * pad) * 0.5f;
			
		}
	 
		START_Y_PIKA = (size.height - NUM_ROW_PIKA * HEIGHT_BALL_PIKA - (NUM_ROW_PIKA - 1) * pad) * 0.5f;
		float saveStart = START_Y_PIKA;
		START_Y_PIKA = bgProgress->getPositionY() - bgProgress->getRealHeight() * 0.1 - START_Y_PIKA;
	 for (int i = NUM_ROW_PIKA - 1; i >= 0; i--)
		 for (int j = 0; j < NUM_COLUMN_PIKA; j++) {
			 arrayNumber[i][j] = new BlockItem();
			 //arrayNumber[i][j]->setPosition(START_X_PIKA + (WIDTH_BALL_PIKA + pad) * j, START_Y_PIKA +
				// (HEIGHT_BALL_PIKA + pad) * (NUM_ROW_PIKA - 1) - (HEIGHT_BALL_PIKA + pad)* (NUM_ROW_PIKA - 1 - i));
			 int convert = NUM_ROW_PIKA - 1 - i;
			 arrayNumber[i][j]->setPosition(START_X_PIKA + (WIDTH_BALL_PIKA + pad) * j, START_Y_PIKA - HEIGHT_BALL_PIKA * (convert + 1) - pad * convert);
			// arrayNumber[i][j]->setPosition(START_X_PIKA + (WIDTH_BALL_PIKA + pad) * j, START_Y_PIKA);
			 arrayNumber[i][j]->addToParent(this);
		 }
       //  START_Y_PIKA = saveStart
        START_Y_PIKA = arrayNumber[0][0]->getY() + HEIGHT_BALL_PIKA * 0.2;
	    
 }

 void GUIPika::genData() {
	 currentTime = 0;
	 if (gameMode == GameMode::NORMAL_MODE) {
		 if (game->isPlayingPika) {
			 score = game->saveScorePika;
			 targetScore = game->saveScorePika;
			 countLife = game->numLifePika;
			 boardData->loadGame();
			 currentTime = game->timePika;
			 level = game->levelPika;
		 }
		 else {
			 
			 boardData->reset(level);
             //boardData->resetLevel(level);
			 score = 0;
			 targetScore = 0;
			 countLife = 10;
			 currentTime = 0;
		 }
	 }
	 
	 //countLife = 1;
	// currentTime = timeGame - 10;
 }

 void GUIPika::startGameAfterGen() {
	 startMode();
	 newGame();
 }

 void GUIPika::resumeGame() {
     state = GameStatePika::PLAY_PIKA;
	 progress->stopAllActions();
	 bgDark->setVisible(false);
	 btnPlay->setVisible(false);
 }
