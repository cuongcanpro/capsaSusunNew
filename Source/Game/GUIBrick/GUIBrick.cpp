#include "GUIBrick.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_OFF_ID 1
#define BTN_MENU_ID 2
#define BTN_PAUSE_ID 3
#define BTN_SOUND_ID 4
#define BTN_DOWN_ID 5
#define BTN_UP_ID 6
#define BTN_LEFT_ID 7
#define BTN_RIGHT_ID 8
#define BTN_ROTATE_ID 9

GUIBrick::GUIBrick(void) : BaseGUI()
{
	BaseGUI();
	currentLayer = NULL;
        tetrisLayer  = NULL;
	setKeypadEnabled(true);
}


GUIBrick::~GUIBrick(void)
{
}
std::string GUIBrick::className = "GUIBrick";
void GUIBrick::initGUI(){
   
	run = false;
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUIBrick::callBackSplash)), NULL));
	//runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIBrick::callBackSplash)), NULL));
    callBackSplash();
	//bg1->setPos(size.width / 2, size.height / 2);
    isInit = false;
  

}

void GUIBrick::initAds() {
   
}
//
//
//bool GUIBrick::onTouchBegan( CCTouch*touch, CCEvent* event )
//{
//	return false;
//}

void GUIBrick::update()
{
	if(currentLayer == NULL)
	{
		if(run == false)
			return;
		else
		{
			game->endGame();
		}
	}
	run = true;
	for (int i = 0; i < NUM_HEIGHT; i++) {

		for (int j = 0; j < NUM_WIDTH; j++) {
			game->dataBrick[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			game->dataNext[i][j] = 0;
		}
	}

	currentLayer->update();
	//AXLOGD("UPDATE ");
	for (int i = 0; i < NUM_HEIGHT; i++) {

		for (int j = 0; j < NUM_WIDTH; j++) {
			if(game->dataBrick[i][j] == 0)
			{
				//arrayEmpty[i][j]->setVisible(true);
				arrayCell[i][j]->setVisible(false);
			}
			else
			{
				//arrayEmpty[i][j]->setVisible(false);
				arrayCell[i][j]->setVisible(true);
			}

		}
	}

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			if(game->dataNext[i][j] == 0)
			{
				arrayEmptyNext[i][j]->setVisible(true);
				arrayCellNext[i][j]->setVisible(false);
			}
			else
			{
				arrayEmptyNext[i][j]->setVisible(false);
				arrayCellNext[i][j]->setVisible(true);
			}
		}
	}
}

void GUIBrick::updateLevel()
{
	labelLevel->setString(CStringUtils::toString(game->level).c_str());
}

void GUIBrick::updateSpeed()
{
	labelSpeed->setString(CStringUtils::toString(game->speedBrick).c_str());
}
void GUIBrick::updateHighscore()
{
    labelHighscore->setString(game->standartNum(game->highscoreBrick).c_str());
    UserDefault::getInstance()->setIntegerForKey("highscoreBrick", game->highscoreBrick);
    UserDefault::getInstance()->flush();
}
void GUIBrick::updateScore()
{
    labelScore->setString(game->standartNum(game->scoreBrick).c_str());

	if (game->scoreBrick > game->highscoreBrick)
    {
        game->highscoreBrick = game->scoreBrick;
		updateHighscore();
       // game->savePreferenceType(game->levelTypeBrick);
	}
}
void GUIBrick::updateInfoGame()
{
    game->scoreBrick = 0;
	updateScore();
	updateHighscore();
}

void okQuitBrick() {
    game->changeToLandscape();
    GUIManager::getInstance().removeAllGui();
    GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
}

void GUIBrick::onButtonRelease( int buttonID, Touch* touch )
{
	//JNIUtils::vibrate();
    JNIUtils::vibrate(1);
	switch (buttonID)
	{
	case BTN_DOWN_ID:
		currentLayer->onButtonDown();
		break;
	case BTN_UP_ID:
		currentLayer->onButtonUp();
		break;
	case BTN_LEFT_ID:
		currentLayer->onButtonLeft();
		break;
	case BTN_RIGHT_ID:
		currentLayer->onButtonRight();
		break;
	case BTN_ROTATE_ID:
        if (game->state != GameState::GAME_OVER)
        {
            currentLayer->onButtonRotate();        
        }
        else
        {
            GameSound::playClick();
            showTetrisLayer();
        }
		break;
	case BTN_SOUND_ID:
		{
			GameSound::playClick();
			game->music = !game->music;
			imageMusic->setVisible(game->music);
			UserDefault::getInstance()->setBoolForKey("music", game->music);
			UserDefault::getInstance()->flush();
			//JNIUtils::showAdsFull();
		}
		
		break;
	case BTN_OFF_ID:
		{
            GUIManager::getInstance().guiDialog->showGUI("Do you want to quit the game?",&okQuitBrick, false, NULL);
			GameSound::playClick();
		}
		
		break;
	case BTN_MENU_ID:
		{
			GameSound::playClick();
            showTetrisLayer();
			//showLevelLayer();
		}
		
		break;
	case BTN_PAUSE_ID:
		{
			GameSound::playClick();

			if (game->state != GameState::PAUSE) {
				imagePause->setVisible(true);
				game->saveState = game->state;
				game->state = GameState::PAUSE;
			} else {
				game->state = game->saveState;
				imagePause->setVisible(false);
			}
		}
		
		break;
	default:
		break;
	}
}
void GUIBrick::updateLabelGame() {
	labelUp->setString("UP");
	labelDown->setString("DOWN");
	labelLeft->setString("LEFT");
	labelRight->setString("RIGHT");
	labelRotate->setString("ROTATE");
}
void GUIBrick::updateLabelLevel() {
	labelUp->setString("SPEED");
	labelDown->setString("LEVEL");
	labelLeft->setString("PRE");
	labelRight->setString("NEXT");
	labelRotate->setString("PLAY");
}

bool GUIBrick::checkRotate()
{
	if(getTouchedButton() == NULL)
		return false;
	if(getTouchedButton() != NULL && getTouchedButton()->buttonID == BTN_ROTATE_ID)
		return true;
	return false;
}

bool GUIBrick::checkLeft()
{

	if(getTouchedButton() != NULL && getTouchedButton()->buttonID == BTN_LEFT_ID)
		return true;
	return false;
}

bool GUIBrick::checkRight()
{
	if(getTouchedButton() == NULL)
		return false;
	if(getTouchedButton() != NULL && getTouchedButton()->buttonID == BTN_RIGHT_ID)
		return true;
	return false;
}

bool GUIBrick::checkUp()
{
	if(getTouchedButton() == NULL)
		return false;
	if(getTouchedButton() != NULL && getTouchedButton()->buttonID == BTN_UP_ID)
		return true;
	return false;
}

bool GUIBrick::checkDown()
{
	if(getTouchedButton() == NULL)
		return false;
	if(getTouchedButton() != NULL && getTouchedButton()->buttonID == BTN_DOWN_ID)
		return true;
	return false;
}

void GUIBrick::showTetrisLayer()
{
    game->levelTypeBrick = 3;
    game->speedBrick     = 1;
    game->levelBrick     = 1;
	if(!tetrisLayer)
	{

		tetrisLayer = new TetrisLayer();
	}

	currentLayer = tetrisLayer;
	currentLayer->show();
    updateInfoGame();
}


void GUIBrick::callBackSplash()
{
	AXLOGD("CALL BACK SPLASH ");
	BaseGUI::initGUI();
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	GameImage *bg = addImage("bg.jpg");
	float scale = size.width / bg->getWidth();
	bg->setWidth(size.width);
	bg->setHeight(size.height);
	bg->setPos(size.width * 0.5, size.height * 0.5);
    float sx = 0;
    bool isWide = false;
    if(size.width / size.height >= 2.0f/3.0f)
    {
        sx = size.width * 0.13f;
        isWide = true;
    }
    else
        sx = 0;

	sx = 0;
	
    btnDown = this->addButton(BTN_DOWN_ID, "brick/btnYellowSmall.png");
	btnDown->setPosition(btnDown->getWidth() * 1.6f + sx, size.height * 0.18 + btnDown->getHeight() * 0.5);

	btnLeft = this->addButton(BTN_LEFT_ID, "brick/btnYellowSmall.png");
	btnLeft->setPosition(btnDown->getPositionX() - btnLeft->getWidth() * 1.0f, btnDown->getPositionY() + btnDown->getHeight() * 0.6f);

	btnRight = this->addButton(BTN_RIGHT_ID, "brick/btnYellowSmall.png");
	btnRight->setPosition(btnDown->getPositionX() + btnDown->getWidth() + btnLeft->getWidth() * 0.0f, btnLeft->getPositionY());

	btnUp = this->addButton(BTN_UP_ID, "brick/btnYellowSmall.png");
	btnUp->setPosition(btnDown->getPositionX(), btnDown->getPositionY() + btnDown->getHeight() * 1.2f);

	btnRotate = this->addButton(BTN_ROTATE_ID, "brick/btnYellow.png");
	btnRotate->setPosition(size.width - btnRotate->getWidth() * 0.7f + sx, btnRight->getPositionY());

    
	btnOff = this->addButton(BTN_OFF_ID, "brick/btnQuit.png");
	btnOff->setPosition(btnOff->getWidth() * 1.0f, btnUp->getPositionY() + btnUp->getHeight() * 0.55 + btnOff->getHeight() * 0.5f);

	btnMenu = this->addButton(BTN_MENU_ID, "brick/btnYellowTiny.png");
//	btnMenu->setPosition(btnOff->getPositionX() - btnOff->getWidth() * 1.8f, btnOff->getPositionY());
	btnMenu->setPosition(size.width - btnMenu->getWidth() * 1.2f + sx, btnOff->getPositionY());

	btnPause = this->addButton(BTN_PAUSE_ID, "brick/btnYellowTiny.png");
	btnPause->setPosition(btnMenu->getPositionX() - btnMenu->getWidth() * 1.5f, btnOff->getPositionY());

	btnSound = this->addButton(BTN_SOUND_ID, "brick/btnYellowTiny.png");
	btnSound->setPosition(btnPause->getPositionX() - btnPause->getWidth() * 1.5f, btnOff->getPositionY());

    btnOff->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.5f, btnOff->getPositionY());
    
    labelOff = this->addText("EXIT");
    labelOff->setFontSize(12);
    labelOff->setColor(Color3B(250, 120, 150));
    labelOff->setPositionX(btnOff->getPositionX());
    labelOff->setPositionY(btnOff->getPositionY() - labelOff->getContentSize().height - btnOff->getHeight() * 0.3f);
    
    labelMenu = this->addText("NewGame");
    labelMenu->setFontSize(12);
    labelMenu->setColor(Color3B(250, 250, 250));
    labelMenu->setPositionX(btnMenu->getPositionX());
    labelMenu->setPositionY(labelOff->getPositionY());
    
    
    labelPause = this->addText("PAUSE");
    labelPause->setFontSize(12);
    labelPause->setColor(Color3B(250, 250, 250));
    labelPause->setPositionX(btnPause->getPositionX());
    labelPause->setPositionY(labelOff->getPositionY());
    
    labelSound = this->addText("SOUND");
    labelSound->setFontSize(12);
    labelSound->setColor(Color3B(250, 250, 250));
    labelSound->setPositionX(btnSound->getPositionX());
    labelSound->setPositionY(labelOff->getPositionY());

	labelDown = this->addText("DOWN");
	labelDown->setColor(Color3B(250, 250, 250));
	labelDown->setPositionX(btnDown->getPositionX());
        labelDown->setPositionY(btnDown->getPositionY() - btnDown->getHeight() * 0.5f -
                                labelDown->getContentSize().height * 0.7f);

	labelLeft = this->addText("LEFT");
	labelLeft->setColor(Color3B(250, 250, 250));
	labelLeft->setPositionX(btnLeft->getPositionX());
        labelLeft->setPositionY(btnLeft->getPositionY() - btnLeft->getHeight() * 0.5f -
                                labelLeft->getContentSize().height * 0.7f);

	labelRight = this->addText("RIGHT");
	labelRight->setColor(Color3B(250, 250, 250));
	labelRight->setPositionX(btnRight->getPositionX());
        labelRight->setPositionY(btnRight->getPositionY() - btnRight->getHeight() * 0.5f -
                                 labelRight->getContentSize().height * 0.7f);

	labelUp = this->addText("UP");
	labelUp->setColor(Color3B(250, 250, 250));
	labelUp->setPositionX(btnUp->getPositionX());
        labelUp->setPositionY(btnUp->getPositionY() - btnUp->getHeight() * 0.5f -
                              labelUp->getContentSize().height * 0.7f);

	labelRotate = this->addText("ROTATE");
	labelRotate->setColor(Color3B(250, 250, 250));
	labelRotate->setPositionX(btnRotate->getPositionX());
	labelRotate->setPositionY(btnRotate->getPositionY() - btnRotate->getHeight() * 0.5f - labelRotate->getContentSize().height * 0.7f);

	
	//bg->setVisible(false);
	/*if (isWide)
		bg->setPos(size.width / 2 + sx, size.height - bg->getRealHeight() * 0.5f);
	else
		bg->setPos(size.width / 2 + sx, size.height * 0.95 - bg->getRealHeight() * 0.5f);*/
	GameImage *bgCenter = addImage("brick/bgNew.png");
	float height1 = size.height * 0.98 - btnOff->getPositionY() - btnOff->getHeight();
	float scaleHeight = height1 / bgCenter->getHeight();
	float scaleWidth = size.width * 0.9 / bgCenter->getWidth();
	if (scaleWidth < scaleHeight)
		bgCenter->setScale(scaleWidth);
	else
		bgCenter->setScale(scaleHeight);
	bgCenter->setPosition(size.width * 0.5, btnOff->getPositionY() + btnOff->getHeight() * 1.0 + bgCenter->getRealHeight() * 0.5);

	startX = bgCenter->getPositionX() - bgCenter->getRealWidth() * 0.45;
	startY = bgCenter->getPositionY() - bgCenter->getRealHeight() * 0.46;
	sizeCell = bgCenter->getRealWidth() * 0.059;

	float pad = sizeCell * 0.1f;
	float widthCenter = sizeCell * 10 + pad * 10;
	float heightCenter = sizeCell * 20 + pad * 20;
	/*bgCenter->setWidth(widthCenter);
	bgCenter->setHeight(heightCenter);
	bgCenter->setPos(startX + widthCenter * 0.445f, startY + heightCenter * 0.475f);*/

	imagePause = addImageToNode("brick/pause.png", bgCenter);
	imagePause->setPositionX(bgCenter->getWidth() * 0.33);
	imagePause->setPositionY(-bgCenter->getHeight() * 0.5 + imagePause->getHeight() * 0.7);
	imagePause->setVisible(false);

	imageMusic = addImageToNode("brick/music.png", bgCenter);
	imageMusic->setPositionX(imagePause->getPositionX());
	imageMusic->setPositionY(imagePause->getPositionY() + imagePause->getHeight() * 0.8f);

	imageLevel = addImageToNode("brick/level.png", bgCenter);
	imageLevel->setPositionX(imagePause->getPositionX());
	imageLevel->setPositionY(imageMusic->getPositionY() + imageMusic->getHeight() * 1.2f);

	imageSpeed = addImageToNode("brick/speed.png", bgCenter);
	imageSpeed->setPositionX(imagePause->getPositionX());
	imageSpeed->setPositionY(imageLevel->getPositionY() + imageLevel->getHeight() * 4.5f);

	imageScore = addImageToNode("brick/score.png", bgCenter);
	imageScore->setPositionX(imagePause->getPositionX());
	imageScore->setPositionY(bgCenter->getHeight() * 0.48 - imageScore->getHeight() * 0.5);

	imageHighScore = addImageToNode("brick/hiscore.png", bgCenter);
	imageHighScore->setPositionX(imagePause->getPositionX());
	imageHighScore->setPositionY(imageScore->getPositionY() - imageScore->getHeight() * 3);

	labelScore = this->addText("000000", bgCenter);
	labelScore->setColor(Color3B(50, 50, 50));
	labelScore->setPositionX(imagePause->getPositionX());
	labelScore->setPositionY(imageScore->getPositionY() - imageScore->getHeight() * 1.2f);

	labelHighscore = this->addText("000000", bgCenter);
	labelHighscore->setColor(Color3B(50, 50, 50));
	labelHighscore->setPositionX(labelScore->getPositionX());
	labelHighscore->setPositionY(imageHighScore->getPositionY() - imageHighScore->getHeight() * 1.2f);

	labelLevel = this->addText("1", bgCenter);
	labelLevel->setColor(Color3B(50, 50, 50));
	labelLevel->setPositionX(imagePause->getPositionX());
	labelLevel->setPositionY(imageLevel->getPositionY() + imageLevel->getHeight() * 1.2f);

	labelSpeed = this->addText("1", bgCenter);
	labelSpeed->setColor(Color3B(50, 50, 50));
	labelSpeed->setPositionX(labelLevel->getPositionX());
	labelSpeed->setPositionY(imageSpeed->getPositionY() - imageSpeed->getHeight() * 1.2f);


	for (int i = 0; i < NUM_HEIGHT; i++) {
		for (int j = 0; j < NUM_WIDTH; j++) {
			arrayCell[i][j] = addImage("brick/cell.png");
			arrayCell[i][j]->setWidth(sizeCell);
			arrayCell[i][j]->setHeight(sizeCell);
			arrayCell[i][j]->setPosition(startX + pad * j + sizeCell * j,
				startY + pad * i + sizeCell * i);
			game->dataBrick[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arrayEmptyNext[i][j] = addImage("brick/cell_empty.png");
			arrayEmptyNext[i][j]->setWidth(sizeCell);
			arrayEmptyNext[i][j]->setHeight(sizeCell);

			arrayEmptyNext[i][j]->setPosition(startX + bgCenter->getRealWidth() * 0.69f + pad * j + sizeCell* j,
				startY + bgCenter->getRealHeight() * 0.45 + pad * i + sizeCell * i);

			arrayCellNext[i][j] = addImage("brick/cell.png");
			arrayCellNext[i][j]->setWidth(sizeCell);
			arrayCellNext[i][j]->setHeight(sizeCell);

			arrayCellNext[i][j]->setPosition(arrayEmptyNext[i][j]->getPositionX(), arrayEmptyNext[i][j]->getPositionY());

			game->dataNext[i][j] = 0;
			//arrayCellNext[i][j]->setVisible(false);
		}
	}


	/*splashLayer = new SplashLayer();
	splashLayer->show();
	currentLayer = splashLayer;*/
    
    showTetrisLayer();
	imageMusic->setVisible(game->music);
	GameSound::playStartApp();
}
