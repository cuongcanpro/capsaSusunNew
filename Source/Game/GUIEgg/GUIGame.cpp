#include "GUIGame.h"
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
#include "GroupScore.h"
#include "Engine/GUI/ParticleEffect.h"
#include "Game/Logic/Constant.h"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3
#define BTN_TOP_ID 4
std::string GUIGame::className = "GUIGame";
GUIGame::GUIGame(void) : BaseGUI()
{
	BaseGUI();

	setKeypadEnabled(true);
}


GUIGame::~GUIGame(void)
{
}

void endGameLoading()
{
	GameClient::endGame();
}


void GUIGame::initGUI(){

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	//runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create(this, AX_CALLBACK_0(GUIGame::callBackSplash)), NULL));
	callBackSplash();
}

void GUIGame::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
        game->changeToLandscape();
        JNIUtils::showAdsBanner(1);
		GUIManager::getInstance().removeAllGui();
		if (gameType == STOMP) {
			//GUIManager::getInstance().showGui(&GUIManager::getInstance().guiLevel);
			//JNIUtils::showAdsBanner(1);
		}
		else
			GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
		GUIManager::getInstance().isCallBackPress = true;
	}
}


void GUIGame::update()
{
	
}
void okEndGame()
{
	game->endGame();
}

void GUIGame::onButtonRelease(int buttonID, Touch* touch)
{
	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_BACK_ID:
		{
			onBackKey();
		}
		
		break;
	case BTN_SOUND_ID:
		{
	//	this->groupBall->setScale(0.3);
                 //   makeGenBall();
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
	case BTN_UNDO_ID:
		{
			
		}
		break;
    case BTN_TOP_ID:
    {
        if (gameType == ENDLESS)
            JNIUtils::submitScore(GAME_EGG, game->scoreEndless);
        else if (gameType == TIME)
        {
            if (game->scoreTime < 10)
            {
                JNIUtils::submitScore(2, game->scoreTime * 1000);
            }
            else
            {
                JNIUtils::submitScore(2, 1000 * 1000);
            }
        }
        break;
    }
	default:
		break;
	}
}

void makeNewGame()
{
	//GUIManager::getInstance().guiWaiting.showAds(false);
	GUIManager::getInstance().guiGame->newGame();
}

void makeBack()
{
	//game->showAdsForOldUser();
    GUIManager::getInstance().guiGame->onBackKey();
}
void GUIGame::callBackSplash()
{
	BaseGUI::initGUI();
	isUpdate = true;
	
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	GameImage* background = addImage("Egg/jungleback.jpg");
	background->setAnchorPoint(Vec2(0, 0));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);
   // background->getImg()->setOpacity(150);
    //background->setVisible(false);

	GameImage* black = addImage("blackLayer.png");
	black->getImg()->setAnchorPoint(Vec2(0, 0));
	black->setWidth(size.width);
	black->setHeight(size.height * 0.11);
	// black->setPosition(size.width * 0.5f, size.height);
	black->setVisible(true);
    black->setLocalZOrder(2);

	WIDTH_BALL = size.width * 0.8f / NINE_ROW;
	START_X_TWENTY = size.width * 0.1f;
	START_Y_TWENTY = size.height * 0.5f;
	HEIGH_BALL = WIDTH_BALL * 0.85f;
	WIDTH_GATE = WIDTH_BALL * 0.9f;
	LIMIT_X = START_X_TWENTY + WIDTH_BALL * NINE_ROW;

	arrow = new Arrow();
	arrow->setPos(200, 100);
	arrow->setHeightArrow(200);
	arrow->setRotateArrow(30);

	bar = addImage("Egg/ceiling.png");
	bar->getImg()->setAnchorPoint(Vec2(0, 0));
	bar->setWidth(size.width);
	bar->setPosition(size.width * 0.5f, size.height);
	bar->setVisible(true);

	int NUM_ROW = (int) (size.height * 0.73f / HEIGH_BALL);

	groupBall = new Node();
	addChild(groupBall);
	groupBall->setAnchorPoint(Vec2(0, 0));
	groupBall->setPosition(START_X_TWENTY, START_Y_TWENTY);

	cannon1 = addImage("Egg/cannon1.png");
	cannon1->getImg()->setAnchorPoint(Vec2(0, 0));
	cannon1->setHeight(WIDTH_BALL * 2.3f / cannon1->getRealWidth() * cannon1->getRealHeight());
	cannon1->setWidth(WIDTH_BALL * 2.3f);
	if (size.width / size.height < 320.0f / 480.0f) {
		cannon1->setPositionY(size.height * 0.12);
		black->setVisible(true);
		//JNIUtils::showAdsBanner(1);
	}
	else {
		black->setVisible(false);
		//JNIUtils::showAdsBanner(0);
	}

	GameImage* cannon2 = addImage("Egg/cannon2.png");
	cannon2->getImg()->setAnchorPoint(Vec2(0, 0));
	cannon2->setHeight(WIDTH_BALL * 2.3f / cannon2->getRealWidth() * cannon2->getRealHeight());
	cannon2->setWidth(WIDTH_BALL * 2.3f);
	cannon2->setPosition(size.width * 0.5f - cannon2->getRealWidth() * 0.5f, 0);
	if (size.width / size.height < 320.0f / 480.0f) {
		cannon2->setPositionY(size.height * 0.12);
		black->setVisible(true);
	}
	else {
		black->setVisible(false);
	}

	arrow->setPos(size.width * 0.5f, cannon2->getPositionY()+ cannon2->getRealHeight() * 1.05f);
	arrow->setHeightArrow(size.height * 0.3f);
	arrow->setRotateArrow(0);
	START_BALL_X = size.width * 0.5f - WIDTH_BALL * 0.5f;
	START_BALL_Y = arrow->y - WIDTH_BALL * 0.5f;

	speed = WIDTH_BALL * 0.9f;
	speedY = -1;

	rope = addImage("Egg/rop.png");
	rope->setWidth(size.width);
	rope->setAnchorPoint(Vec2(0, 0));
	rope->setPosition(size.width * 0.5f, START_BALL_Y + WIDTH_BALL * 1.5f);

	arrow->addToParent(this);

	moveBall = new Ball();
	addChild(moveBall);
	moveBall->setPosition(START_BALL_X, START_BALL_Y);

	nextBall = new Ball();
	addChild(nextBall);
	nextBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.8f,
		cannon1->getPositionY() + cannon1->getRealHeight() * 0.8f);

	leftWall = addImage("Egg/leftwall.png");
	leftWall->getImg()->setAnchorPoint(Vec2(0,0));
	leftWall->setHeight(size.height);
	leftWall->setPositionX(START_X_TWENTY - leftWall->getRealWidth() * 0.7f);

	rightWall = addImage("Egg/rightwall.png");
	rightWall->getImg()->setAnchorPoint(Vec2(0,0));
	rightWall->setHeight(size.height);
	rightWall->setPosition(LIMIT_X - rightWall->getRealWidth() * 0.3f, 0);

	upWall = addImage("Egg/upwall.png");
	upWall->getImg()->setAnchorPoint(Vec2(0,0));
	upWall->setWidth(size.width);
	upWall->setPosition(0, size.height - upWall->getRealHeight());
	// arrayRow.at(0]->arrayBall[0].runAction();

	ani = new Bird();
	addChild(ani);
	ani->setVisible(false);

	genBall = new Ball();
	genBall->setWidth(WIDTH_BALL);
	genBall->setHeight(WIDTH_BALL);
	addChild(genBall);
	genBall->setVisible(false);

	labelScore = Text::create("Score: 0", "fonts/tahomabd.ttf", 22);
    labelScore->setScale(0.9f);
	labelScore->setAnchorPoint(Vec2(0, 0));
	addChild(labelScore);
	labelScore->setPosition(Vec2(size.width * 0.02f, upWall->getPositionY() + upWall->getRealHeight() * 0.1f));

	labelHighscore = Text::create("Score: 0", "fonts/tahomabd.ttf", 22);
    labelHighscore->setScale(0.9f);
	labelHighscore->setAnchorPoint(Vec2(0, 0));
	addChild(labelHighscore);
    labelHighscore->setPosition(Vec2(size.width * 0.3f, labelScore->getPositionY()));

	GameImage* progress1 = new GameImage("Egg/progress.png");
	bgProgress = addImage("Egg/bgProgress.png");
	bgProgress->setAnchorPoint(Vec2(0, 1));
	bgProgress->addChild(progress1);
	progress1->setPositionX(bgProgress->getWidth() * 0.01f);
	bgProgress->setPos(size.width * 0.93f, size.height * 0.3f);
	progress = ProgressTimer::create(Sprite::create("GuiGame/Egg/bgProgress.png"));
    progress->setType(ProgressTimer::Type::BAR);
	progress->setMidpoint(Vec2(0,1));
	progress->setBarChangeRate(Vec2(0, 1));
	bgProgress->addChild(progress);

	bonusEffect = new BonusEffect();
	addChild(bonusEffect);
	bonusEffect->maxTime = 4;
	bonusEffect->radius = size.width * 0.12f;
	bonusEffect->rootX = LIMIT_X;
	bonusEffect->rootY = size.height * 0.2f;
	//bonusEffect->setVisible(false);

	bgRow = addImage("bgDark.png");
	bgRow->setAnchorPoint(Vec2(0, 0));
	bgRow->setHeight(upWall->getRealHeight() * 0.4f);
	bgRow->setWidth(size.width * 0.2f);
	bgRow->setPosition(size.width * 0.15f, upWall->getPositionY() + upWall->getRealHeight() * 0.5f);

	labelRow = Text::create("10 ROWS", "fonts/tahomabd.ttf", 22);
	labelRow->setAnchorPoint(Vec2(0, 0.5f));
	addChild(labelRow);
	labelRow->setPosition(Vec2(bgRow->getPositionX() - bgRow->getRealWidth() * 0.45f, bgRow->getPositionY()));

	btnBack = addButton(1, "btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, upWall->getPositionY() + upWall->getRealHeight() * 0.5f + btnBack->getHeight() * 0.5f);

	btnSound = addButton(2, "btnSoundOff.png");
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
	initDragonbone();


	//btnPause = addButton(3, "btnPause.png");
	//btnPause->setPosition(btnSound->getPositionX() - btnPause->getWidth() * 1.2f, btnBack->getPositionY());
}



Ball* GUIGame::getBall(int idRow, int idColumn) {
	if (idRow < 0 || idColumn < 0)
		return NULL;
	if (idRow >= arrayRow.size())
		return NULL;
	RowBall* row = arrayRow.at(idRow);
	if (idColumn > row->typeRow - 1)
		return NULL;
	Ball* ball = arrayRow.at(idRow)->getBall(idColumn);
	return ball;
}

void GUIGame::act(float delta)
{
    // TODO Auto-generated method stub
    float rateSpeed = delta * 60 * 1.7;
    float speed     = 42;
    if (isUpdate != true)
        return;
    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    if (state == GameState::PLAY)
    {
        START_Y_TWENTY = groupBall->getPositionY();
        if (gameType == ENDLESS)
        {
            // di chuyen chim cong qua bong moi
            genBall->setPosition(ani->getPositionX(), ani->getPositionY() - ani->getRealHeight() * 0.75f);
            ani->act(delta);

            // random ra qua bong rung
            countTimeVibrate = countTimeVibrate + delta;
            Ball* b;
            if (countTimeVibrate > 25)
            {
                countTimeVibrate = 0;
                int r, c;
                do
                {
                    r = (int)(GameUtility::getRandom() * 8);
                    c = (int)(GameUtility::getRandom() * 8);
                    b = arrayRow.at(r)->arrayBall[c];
                } while (!b->isVisible() || b->isBonus());
                b->countVibrate = 0;
                b->runActionVibrate();
            }

            // di chuyen group ball xuong
            if (groupBall->getContentSize().height > 0.9f * size.height)
            {
                groupBall->setPositionY(0.9f * size.height);
                START_Y_TWENTY = 0.9f * size.height;
            }
            if (bonusEffect->isVisible() && bonusEffect->idBonus == 4)
            {
                groupBall->setPositionY(groupBall->getPositionY() + speed * 0.03f * rateSpeed);
                START_Y_TWENTY = START_Y_TWENTY + speed * 0.03f * rateSpeed;
            }
            else if (increaseSpeed)
            {
                float dY = ((groupBall->getPositionY() - START_BALL_Y) - size.height * 0.3) * 0.025;
                groupBall->setPositionY(groupBall->getPositionY() - dY * rateSpeed);
                START_Y_TWENTY = START_Y_TWENTY - dY * rateSpeed;
                if (dY <= 2)
                {
                    increaseSpeed = false;
                }
            }
            else
            {
                float rate = 0.0033f;
                rate       = rate - 0.0015f * (NUM_BALL - 3) / 5.0f;

                groupBall->setPositionY(groupBall->getPositionY() - speed * rate * rateSpeed);
                START_Y_TWENTY = START_Y_TWENTY - speed * rate * rateSpeed;
            }

            // check xem co trung qua bong duoc chim cong
            if (speedY > 0 && genBall->isVisible())
            {
                // tinh khoang cach bong bay den qua bong duoc gen
                double distance = (genBall->getPositionX() - moveBall->getPositionX()) *
                                  (genBall->getPositionX() - moveBall->getPositionX());
                distance = distance + (genBall->getPositionY() - moveBall->getPositionY()) *
                                          (genBall->getPositionY() - moveBall->getPositionY());
                distance = sqrt(distance);

                if (distance <= WIDTH_BALL)
                {
                    // vo bong
                    genBall->setVisible(false);
                    GameSound::playWhirleyHit();
                    showParticle(genBall->getPositionX(), genBall->getPositionY(), NUM_BALL);
                    moveBall->setVisible(false);
                    speedY = -1;
                    score  = score + 50;
                    updateScore();

                    GroupScore* group = getGroupScore();
                    group->setVisible(true);
                    group->createBonusScore(50);
                    group->setPosition(moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f,
                                       moveBall->getPositionY() + moveBall->getRealHeight() * 0.5f);
                    group->runAction(Sequence::create(
                        EaseBackOut::create(MoveTo::create(
                            0.7f, Vec2(group->getPositionX(), group->getPositionY() + size.height * 0.1f))),
                        FadeOut::create(0.5), Hide::create(), NULL));

                    // Todo: Effect Later
                    /*effectBreakBall->stopAllActions();
                    effectBreakBall->setVisible(true);
                    effectBreakBall->getAnimation()->gotoAndPlay("run", -1, -1, -1);
                    effectBreakBall->setPosition(genBall->getPosition());*/
                    effectBreakBall->stop();
                    effectBreakBall->setVisible(true);
                    effectBreakBall->play(0);
                    effectBreakBall->setPosition(genBall->getPosition());
                    JNIUtils::vibrate(50);
                }
            }

            if (groupBall->getPositionY() - START_BALL_Y > size.height * 0.5f)
            {
                increaseSpeed = true;
            }

            if (bonusEffect->isVisible())
            {
                bonusEffect->act(delta);
            }
        }
        else if (gameType == TIME)
        {
            if (arrayRow.size() > 0)
            {
                bar->setPosition(0, groupBall->getPositionY() + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY +
                                        arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
                countTime = countTime + delta;
                updateTime();
            }

            float d = fabs(((double)(rope->getPositionY() + rope->getRealHeight() - groupBall->getPositionY())));
            if (d > HEIGH_BALL * 0.1f)
            {
                if (groupBall->getPositionY() > rope->getPositionY() + rope->getRealHeight())
                    groupBall->setPositionY(groupBall->getPositionY() - speed * 0.05f * rateSpeed);
                else
                    groupBall->setPositionY(groupBall->getPositionY() + speed * 0.05f * rateSpeed);
                START_Y_TWENTY = groupBall->getPositionY();
            }
        }
        else
        {
            if (arrayRow.size() > 0)
            {
                bar->setPosition(0, groupBall->getPositionY() + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY +
                                        arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
            }
            if (distanceY != 0)
            {
                countDistance = countDistance + speed * 0.05f * rateSpeed;
                if (countDistance >= distanceY)
                {
                    distanceY = 0;
                }
                else
                {
                    groupBall->setPositionY(groupBall->getPositionY() - speed * 0.05f * rateSpeed);
                    START_Y_TWENTY = groupBall->getPositionY();
                }
            }
        }

        if (speedY > 0)
        {
            oldX = moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f;
            oldY = moveBall->getPositionY() + moveBall->getRealWidth() * 0.5f;
            if (moveBall->getPositionY() >= START_Y_TWENTY)
                oldRow =
                    (int)((moveBall->getPositionY() + moveBall->getRealWidth() * 0.5f - START_Y_TWENTY) / HEIGH_BALL);
            else
                oldRow = (int)(floor((moveBall->getPositionY() + moveBall->getRealWidth() * 0.5f - START_Y_TWENTY) /
                                     HEIGH_BALL));
            int size1 = arrayRow.size();
            if (oldRow >= size1)
                oldRow = arrayRow.size() - 1;
            if (oldRow < -1)
            {
                oldColumn =
                    (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - START_X_TWENTY) / WIDTH_BALL);
                if (arrayRow.at(0)->typeRow == EIGHT_ROW)
                {
                    if (oldColumn >= NINE_ROW)
                        oldColumn = NINE_ROW - 1;
                }
                else
                {
                    if (oldColumn >= NINE_ROW - 1)
                        oldColumn = NINE_ROW - 2;
                }
            }
            else if (oldRow != -1)
            {
                if (arrayRow.at(oldRow)->typeRow == EIGHT_ROW)
                {
                    oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - WIDTH_BALL * 0.5f -
                                       START_X_TWENTY) /
                                      WIDTH_BALL);
                    if (oldColumn == NINE_ROW - 1)
                        oldColumn = NINE_ROW - 2;
                }
                else
                {
                    oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - START_X_TWENTY) /
                                      WIDTH_BALL);
                    if (oldColumn == NINE_ROW)
                        oldColumn = NINE_ROW - 1;
                }
            }
            else
            {
                if (arrayRow.at(0)->typeRow == EIGHT_ROW)
                {
                    oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - START_X_TWENTY) /
                                      WIDTH_BALL);
                    if (oldColumn >= NINE_ROW)
                        oldColumn = NINE_ROW - 1;
                }
                else
                {
                    oldColumn = (int)((moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f - WIDTH_BALL * 0.5f -
                                       START_X_TWENTY) /
                                      WIDTH_BALL);
                    if (oldColumn >= NINE_ROW - 1)
                        oldColumn = NINE_ROW - 2;
                }
            }
            moveBall->setPositionX(moveBall->getPositionX() + speedX);
            moveBall->setPositionY(moveBall->getPositionY() + speedY);

            if (moveBall->getPositionY() > size.height * 1.2f)
            {
                moveBall->setVisible(false);
                speedY = -1;
                if (delay)
                    delayReturn();
                delay = false;
                return;
            }

            getNearBall(moveBall->getPositionX() + moveBall->getRealWidth() * 0.5f,
                        moveBall->getPositionY() + moveBall->getRealHeight() * 0.5f);
            if (speedX > 0)
            {
                if ((LIMIT_X - moveBall->getPositionX()) <= WIDTH_BALL)
                {
                    speedX = -speedX;
                }
            }
            else
            {
                if ((moveBall->getPositionX() - START_X_TWENTY) <= 0)
                {
                    speedX = -speedX;
                }
            }
        }

        if (checkEndGame())
        {
            if (countVisible == 0)
            {
                countVisible = 1;
                GameSound::playWarn();
            }
            countTimeVisible = countTimeVisible + delta;
            if (countTimeVisible > 0.2f)
            {
                countTimeVisible = 0;
                for (int i = 0; i < NINE_ROW; i++)
                {
                    if (arrayRow.at(0)->arrayBall[i]->getImg()->getOpacity() >= 255)
                        arrayRow.at(0)->arrayBall[i]->setOpacity(0);
                    else
                        arrayRow.at(0)->arrayBall[i]->setOpacity(255);
                }
                countVisible++;
                if (countVisible >= 8)
                {
                    endGame();
                }
            }
        }
        else
        {
            countVisible = 0;
            if (arrayRow.size() == 0)
                return;
            for (int i = 0; i < NINE_ROW; i++)
            {
                arrayRow.at(0)->arrayBall[i]->setOpacity(255);
            }
        }
    }
    else
    {
    }
    for (int i = 0; i < arrayImageEffect.size(); i++)
    {
        if (arrayImageEffect.at(i)->isVisible())
        {
            arrayImageEffect.at(i)->updateCoin(game->deltaTime);
        }
    }
}

bool GUIGame::onTouchBegan( Touch *pTouch, Event *pEvent )
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if(pTouch->getLocation().y < size.height * 0.68f)
	{
		if (state == GameState::WAIT_PLAY || state == GameState::PAUSE) {
			state = GameState::PLAY;
			//btnPause->setChecked(false);
		}
		if (state == GameState::PLAY)
			moveArrow(pTouch->getLocation().x, pTouch->getLocation().y);
	}
	else
	{
		if (BaseGUI::onTouchBegan(pTouch, pEvent))
			return true;
	}
	return BaseGUI::onTouchBegan(pTouch, pEvent);
}

void GUIGame::onTouchMoved(Touch*touch, Event* event)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if(touch->getLocation().y < size.height * 0.8f)
	{
		
		if (state == GameState::PLAY)
			moveArrow(touch->getLocation().x, touch->getLocation().y);
	}
	else
	{
		BaseGUI::onTouchMoved(touch, event);
	}
}

void GUIGame::moveArrow(int screenX, int screenY) {

	float tag = getTag(screenX, screenY);
	arrow->setRotateArrow(tag);
}

float GUIGame::getTag(int screenX, int screenY) {
	//int convertY = (int) (getRealHeight() - screenY);
	int convertY = screenY;
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	float distance = (float) (sqrt((convertY - arrow->y) * (convertY - arrow->y)
		+ (screenX - arrow->x - arrow->getWidth() * 0.5f) * (screenX - arrow->x - arrow->getWidth() * 0.5f)));
	distance = distance - arrow->getArrowHeight();
	arrow->setHeightArrow(distance + size.height * 0.2f);

	float tagValue = (screenX - arrow->x - arrow->getWidth() * 0.5f) / (convertY - arrow->y);
	float tag = (float) (atan(tagValue) / 3.14f * 180);
	return tag;
}

void GUIGame::onTouchEnded( Touch *pTouch, Event *pEvent )
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if (pTouch->getLocation().y < size.height * 0.8f)
	{
		if (isMoving)
		{
			BaseGUI::onTouchEnded(pTouch, pEvent);
			return;
		}
		moveArrow(pTouch->getLocation().x, pTouch->getLocation().y);
		speedX = (float)(speed * sin(arrow->getRadian()));
		speedY = (float)(speed * cos(arrow->getRadian()));
		nextBall->setVisible(true);
		isMoving = true;
		ccBezierConfig c;
		c.controlPoint_1 = Vec2(nextBall->getPositionX(), nextBall->getPositionY());
		c.controlPoint_2 = Vec2(nextBall->getPositionX() + 40 - GameUtility::getRandom() * 20, nextBall->getPositionY() + 60 - GameUtility::getRandom() * 20);
		c.endPosition = Vec2(START_BALL_X, START_BALL_Y);

		nextBall->runAction(Sequence::create(EaseExponentialOut::create(BezierTo::create(0.5f, c))
			, CallFunc::create(AX_CALLBACK_0(GUIGame::callbackNextBall, this)), NULL));


        // Todo: Effect Later
		/*effectShootBall->stopAllActions();
		effectShootBall->getAnimation()->gotoAndPlay("vaoban", 0.3, -1, 1);
		effectShootBall->runAction(Sequence::create(DelayTime::create(0.4), Show::create(),
			DelayTime::create(1.0), Hide::create(), NULL));
		effectShoot->stopAllActions();
		effectShoot->setVisible(true);
		effectShoot->getAnimation()->gotoAndPlay("1", -1, -1, 1);
		effectShoot->runAction(Sequence::create(DelayTime::create(0.8), Hide::create(), NULL));*/
	}
	else
	{
		BaseGUI::onTouchEnded(pTouch, pEvent);
	}
}

void GUIGame::delayReturn() {
	moveBall->setVisible(true);
	moveBall->setPosition(START_BALL_X, START_BALL_Y);
	moveBall->setId(nextBall->idBall);
	if (nextBall->isBonus())
	{
		moveBall->setIdBonus(nextBall->idBonus);
	}
	nextBall->setIdBonus(-1);
	int idNextBall = 0;
	if (gameType == ENDLESS) {
		idNextBall = (int)(GameUtility::getRandom() * NUM_BALL);
	}
	else {
		vector<int> arrayId;
		for (int i = 0; i < arrayRow.size(); i++) {
			vector<int> arrayIdBall = arrayRow.at(i)->getArrayId();
			for (int j = 0; j < arrayIdBall.size(); j++) {
				if (std::count(arrayId.begin(), arrayId.end(), arrayIdBall[j]) >= 0) {
					arrayId.push_back(arrayIdBall[j]);
				}
				else {
				}
			}
		}
		if (arrayId.size() == 0)
			idNextBall = 0;
		else {
			idNextBall = (int)(GameUtility::getRandom() * arrayId.size());
			idNextBall = arrayId.at(idNextBall);
		}
	}
	
	nextBall->setId(idNextBall);
	nextBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.8f,
		cannon1->getPositionY() + cannon1->getRealHeight() * 0.8f);
	nextBall->stopAllActions();
	float scale = nextBall->rScaleX;
	nextBall->setScale(0);
	nextBall->runAction(EaseBounceOut::create(ScaleTo::create(0.5, scale)));
	if (nextBonus) {
		makeBonus();
	}
	isMoving = false;
}

// Update lai mang ball sau khi remove bong, day cac hang tren xuong neu
// hang duoi cung khong con bong
void GUIGame::updateArrayBall() {
	int i;
	for (i = arrayRow.size() - 1; i >= 0; i--) {
		int j;
		for (j = 0; j < arrayRow.at(i)->arrayBall.size(); j++) {
			if (arrayRow.at(i)->arrayBall[j]->isVisible()) {
				break;
			}
		}
		if (j >= arrayRow.at(i)->arrayBall.size())
			break;
	}
	if (i >= 0) {
		if (gameType == ENDLESS) {
			// update lai mang ball

			vector<RowBall*> arrayNew;
			for(int k = 0; k < i + 1; k++)
			{
				RowBall* rowBall = arrayRow.at(0);
				arrayRow.erase(arrayRow.begin());
				arrayNew.push_back(rowBall);
			}
			
			for(int k = 0; k < arrayRow.size(); k++)
				arrayRow.at(k)->moveUp(-i - 1);
			int sizeArray = arrayNew.size();
			while (sizeArray > 0)
			{
				RowBall* rowBall = arrayNew.at(arrayNew.size() - 1);
				arrayNew.pop_back();
				sizeArray = arrayNew.size();
				rowBall->setIdRow(arrayRow.at(arrayRow.size() - 1)->idRow + 1,  NINE_ROW + EIGHT_ROW - arrayRow.at(arrayRow.size() - 1)->typeRow);
				rowBall->setVisibleAll();
                rowBall->renew(rowBall->typeRow);
				arrayRow.push_back(rowBall);
			}
			START_Y_TWENTY = START_Y_TWENTY + (i + 1) * HEIGH_BALL;
			groupBall->setPositionY(START_Y_TWENTY);
			
// 			for (int k = 0; k + i + 1 < arrayRow.size(); k++) {
// 				arrayRow.at(k)->copy(arrayRow.at(k + i + 1));
// 			}
// 
// 			START_Y_TWENTY = START_Y_TWENTY + (i + 1) * HEIGH_BALL;
// 			groupBall->setPositionY(START_Y_TWENTY);
// 			int saveTypeRow, typeRow;
// 
// 			// re
// 			int rowAdd = arrayRow.size() - i - 2;
// 			saveTypeRow = typeRow = arrayRow.at(rowAdd)->typeRow;
// 			for (int k = rowAdd + 1; k < arrayRow.size(); k++) {
// 				typeRow = EIGHT_ROW + NINE_ROW - typeRow;
// 				arrayRow.at(k)->renew(typeRow);
// 			}
		} else {
			// update lai mang ball
			for (int k = 0; k + i + 1 < arrayRow.size(); k++) {
				arrayRow.at(k)->copy(arrayRow.at(k + i + 1));
			}

			START_Y_TWENTY = START_Y_TWENTY + (i + 1) * HEIGH_BALL;
			groupBall->setPositionY(START_Y_TWENTY);
			int saveTypeRow, typeRow;

			// remove het bon dang sau
			for (int k = 0; k < i + 1; k++) {
				for (int j = 0; j < NINE_ROW; j++) {
					arrayRow.at(arrayRow.size() - 1 - k)->arrayBall[j]->removeFromParent();
				}
			}

			for (int k = 0; k < i + 1; k++) {
					arrayRow.pop_back();
			}
		}
	}
}

PointGame* GUIGame::getPoint(float x, float y) {
	int row = (int) ((y - START_Y_TWENTY) / HEIGH_BALL);
	int column;
	if (row < 0)
		return new PointGame(-1, -1);

	RowBall* rowBall = arrayRow.at(row);
	if (rowBall->typeRow == EIGHT_ROW) {
		column = (int) ((x - START_X_TWENTY - WIDTH_BALL * 0.5f) / WIDTH_BALL);
	} else {
		column = (int) ((x - START_X_TWENTY) / WIDTH_BALL);
	}
	return new PointGame(column, row);
}

void GUIGame::resetCheckConnect() {
	for (int i = 0; i < arrayRow.size(); i++) {
		arrayRow.at(i)->resetCheckConnect();
	}
}

// lay nhung bong co the bi gan bong bay vao
void GUIGame::getNearBall(float x, float y) {
	int row;
	if (y >= START_Y_TWENTY)
		row = (int) ((y - START_Y_TWENTY) / HEIGH_BALL);
	else
		row = (int) (floor((y - START_Y_TWENTY) / HEIGH_BALL));
	int column;
	if (row < -1)
		return;
	int size = arrayRow.size();
	if (row >= size)
	{
		int n = arrayRow.size();
		row = arrayRow.size() - 1;
	}
	int idRow;
	int idColumn;
	Ball ballAdd;
	if (row > -1) {

		if (arrayRow.at(row)->typeRow == EIGHT_ROW) {
			column = (int) ((x - WIDTH_BALL * 0.5f - START_X_TWENTY) / WIDTH_BALL);
			if (column >= NINE_ROW - 1)
				column = NINE_ROW - 2;
			if (arrayRow.at(row)->arrayBall[column]->isVisible()) {
				float medX = (oldX + arrayRow.at(row)->arrayBall[column]->getPositionX() + WIDTH_BALL * 0.5f + START_X_TWENTY) / 2;
				float medY = (oldY + arrayRow.at(row)->arrayBall[column]->getPositionY() + WIDTH_BALL * 0.5f + START_Y_TWENTY) / 2;
				int medRow = (int) ((medY - START_Y_TWENTY) / HEIGH_BALL);
				int medColumn;
				if (medRow < 0)
					medRow = 0;
				if (arrayRow.at(medRow)->typeRow == EIGHT_ROW) {
					medColumn = (int) ((medX - START_X_TWENTY - WIDTH_BALL * 0.5f) / WIDTH_BALL);
					if (medColumn == NINE_ROW - 1)
						medColumn = NINE_ROW - 2;
				} else {
					medColumn = (int) ((medX - START_X_TWENTY) / WIDTH_BALL);
				}
				AXLOGD("MeRow %i OldRow %i ", medRow, oldRow);
				if (arrayRow.at(medRow)->arrayBall[medColumn]->isVisible()) {
					AXLOGD("Voa day ** ");
					addMoveBall(oldRow, oldColumn);
				} else {
					AXLOGD("Voa day ** 2");
					addMoveBall(medRow, medColumn);
				}

			} else {
				if (row < arrayRow.size() - 1) {
					// xet 6 vi tri quanh diem nay, neu co bong thi dung lai
					// ngay
					if (checkNearBall(x, y, row, column, 0, -1))
						return;
					if (checkNearBall(x, y, row, column, 0, 1))
						return;
					if (checkNearBall(x, y, row, column, -1, 0))
						return;
					if (checkNearBall(x, y, row, column, -1, 1))
						return;
					if (checkNearBall(x, y, row, column, 1, 0))
						return;
					if (checkNearBall(x, y, row, column, 1, 1))
						return;
				} else {
					AXLOGD("vao day co 5");
					addMoveBall(row, column);
				}
			}

		} else {
			column = (int) ((x - START_X_TWENTY) / WIDTH_BALL);
			if (column >= NINE_ROW)
				column = NINE_ROW - 1;
			if (arrayRow.at(row)->arrayBall[column]->isVisible()) {
				float medX = (oldX + arrayRow.at(row)->arrayBall[column]->getPositionX() + WIDTH_BALL * 0.5f + START_X_TWENTY) / 2;
				float medY = (oldY + arrayRow.at(row)->arrayBall[column]->getPositionY() + WIDTH_BALL * 0.5f + START_Y_TWENTY) / 2;
				int medRow = (int) ((medY - START_Y_TWENTY) / HEIGH_BALL);
				int medColumn;
				if (medRow < 0)
					medRow = 0;
				if (arrayRow.at(medRow)->typeRow == EIGHT_ROW) {
					medColumn = (int) ((medX - START_X_TWENTY - WIDTH_BALL * 0.5f) / WIDTH_BALL);
					if (medColumn == NINE_ROW - 1)
						medColumn = NINE_ROW - 2;
				} else {
					medColumn = (int) ((medX - START_X_TWENTY) / WIDTH_BALL);
				}
				AXLOGD("MeRow %i OldRow %i ", medRow, oldRow);
				if (arrayRow.at(medRow)->arrayBall[medColumn]->isVisible()) {
					AXLOGD("Voa day ** 3");
					addMoveBall(oldRow, oldColumn);
				} else {
					AXLOGD("Voa day ** 4");
					addMoveBall(medRow, medColumn);
				}
			} else {
				if (row < arrayRow.size() - 1) {
					if (checkNearBall(x, y, row, column, 0, -1))
						return;
					if (checkNearBall(x, y, row, column, 0, 1))
						return;
					if (checkNearBall(x, y, row, column, -1, 0))
						return;
					if (checkNearBall(x, y, row, column, -1, -1))
						return;
					if (checkNearBall(x, y, row, column, 1, 0))
						return;
					if (checkNearBall(x, y, row, column, 1, -1))
						return;
				} else {
					AXLOGD("vao day co 6");
					addMoveBall(row, column);
				}
			}
		}

	} else {
		if (arrayRow.at(0)->typeRow == EIGHT_ROW) {
			column = (int) ((x - START_X_TWENTY) / WIDTH_BALL);
			if (column >= NINE_ROW)
				column = NINE_ROW - 1;
			if (checkNearBall(x, y, row, column, 1, 0))
				return;
			if (checkNearBall(x, y, row, column, 1, -1))
				return;
			if (checkNearBall(x, y, row, column, 1, 1))
				return;
		} else {
			column = (int) ((x - WIDTH_BALL * 0.5f - START_X_TWENTY) / WIDTH_BALL);
			if (column >= NINE_ROW - 1)
				column = NINE_ROW - 2;
			if (checkNearBall(x, y, row, column, 1, 0))
				return;
			if (checkNearBall(x, y, row, column, 1, 1))
				return;
			if (checkNearBall(x, y, row, column, 1, -1))
				return;
		}
	}

}

// kiem tra khoang cach bong bay voi bong co san tren hang
bool GUIGame::checkNearBall(float x, float y, int row, int column,int dRow, int dColumn) 
{
	int idRow = row + dRow;
	int idColumn = column + dColumn;
	Ball* ballAdd = getBall(idRow, idColumn);
	if (ballAdd != NULL) {
		if (getDistance(ballAdd, x, y) < WIDTH_GATE) {
			// tao them bong o day
			addMoveBall(row, column);
			return true;
		}
	}
	return false;
}

void GUIGame::addMoveBall(int row, int column) {
	Ball* ball;
	speedY = -1;
	AXLOGD("Row %i column %i ", row, column);
	
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if (row <= -1) {
		if (gameType == ENDLESS) {
			// day het cac hang len tren, them hang moi

			START_Y_TWENTY = START_Y_TWENTY - HEIGH_BALL;
			groupBall->setPositionY(START_Y_TWENTY);
	
			RowBall* rowBall = arrayRow.at(arrayRow.size() - 1);
			arrayRow.pop_back();

			for(int i1 = 0; i1 < arrayRow.size(); i1++)
			{
				arrayRow.at(i1)->moveUp(1);
			}
			arrayRow.insert(arrayRow.begin(), rowBall);
			rowBall->setIdRow(0, NINE_ROW + EIGHT_ROW - arrayRow.at(1)->typeRow);


			ball = arrayRow.at(0)->arrayBall[column];
			row = 0;
		}
		else {
			// day het cac hang len tren, them hang moi
			START_Y_TWENTY = START_Y_TWENTY - HEIGH_BALL;
			groupBall->setPositionY(START_Y_TWENTY);

			RowBall* rowBall =  new RowBall(0);
			for(int i = 0; i < rowBall->arrayBall.size(); i++)
			{
				groupBall->addChild(rowBall->arrayBall.at(i));
			}

			for(int i1 = 0; i1 < arrayRow.size(); i1++)
			{
				arrayRow.at(i1)->moveUp(1);
			}
			arrayRow.insert(arrayRow.begin(), rowBall);
			rowBall->setIdRow(0, NINE_ROW + EIGHT_ROW - arrayRow.at(1)->typeRow);

			ball = arrayRow.at(0)->arrayBall[column];
			row = 0;
		}
	} else {
		// dinh qua bong nay vao
		ball = arrayRow.at(row)->arrayBall[column];

	}
	
	ball->setVisible(true);
	ball->setId(moveBall->idBall);
	ball->setIdRow(row);
	ball->idColumn = column;
	ball->typeRow = arrayRow.at(row)->arrayBall[column]->typeRow;
	if (moveBall->isBonus()) {
		ball->setIdBonus(moveBall->idBonus);
	}
	
	/*if (true)
		return;*/
	moveBall->setVisible(false);
	moveBall->setIdBonus(-1);
	
	if (ball->checkEatBall()) {
		// remove qua bong nay cung nhung thang co lien quan
		
		int bonusScore = 0;
		GameSound::playBreakEgg();
		AXLOGD("EAT BALL %i ", arrayEatBall.size());
		for (int i = 0; i < arrayEatBall.size(); i++) {
			showParticle(arrayEatBall.at(i)->getPositionX() + groupBall->getPositionX(),
				arrayEatBall.at(i)->getPositionY() + groupBall->getPositionY(), ball->idBall);
			if (arrayEatBall.at(i)->isVibrate) {
				nextBonus = true;
				bonusScore = bonusScore + 50;
				GameSound::playMama();

				GameImage* dinosaur = addImage("Egg/dinosaur.png");
				dinosaur->setPosition(arrayEatBall.at(i)->rootX + groupBall->getPositionX(), arrayEatBall.at(i)->rootY + groupBall->getPositionY());
                                dinosaur->runAction(Sequence::create(
                                    DelayTime::create(0.5), MoveBy::create(1, Vec2(0, -size.height)),
                                    CallFuncN::create(AX_CALLBACK_1(GUIGame::callbackRemove, this)), NULL));

                                    
                // Todo: effect later
				//effectBreakBall->stopAllActions();
				//effectBreakBall->setVisible(true);
				//effectBreakBall->getAnimation()->gotoAndPlay("run", -1, -1, -1);
				////   effectBreakBall->runAction(Sequence::create(DelayTime::create(1.0), Hide::create()));
				//effectBreakBall->setPosition(dinosaur->getPosition());
                effectBreakBall->stop();
                effectBreakBall->setVisible(true);
                effectBreakBall->play(0);
                effectBreakBall->setPosition(dinosaur->getPosition());
                JNIUtils::vibrate(50);
			}
			if (arrayEatBall.at(i)->isBonus()) {
					arrayEatBall.at(i)->bonusImage->setVisible(false);
					bonusEffect->setIdBonus(arrayEatBall.at(i)->idBonus);
			}
		}
	
		
		// int size = arrayRow.size();
		vector<vector<bool>> save;
		for (int i = 0; i < arrayRow.size(); i++) {
			vector<bool> save1;
			for (int j = 0; j < NINE_ROW; j++) {
				save1.push_back(arrayRow.at(i)->arrayBall[j]->isVisible());
			}
			save.push_back(save1);
		}
		ball->removeBall();
		int countEat = 0;

		int i;
		for (i = arrayRow.size() - 1; i >= 0; i--) {
			int j;
			for (j = 0; j < arrayRow.at(i)->arrayBall.size(); j++) {
				if (arrayRow.at(i)->arrayBall[j]->isVisible()) {
					break;
				}
			}
			if (j >= arrayRow.at(i)->arrayBall.size())
				break;
		}
		int rowRemove = i;

		for (int i = 0; i < arrayRow.size(); i++) {
			for (int j = 0; j < NINE_ROW; j++) {
				Ball* ball = arrayRow.at(i)->arrayBall[j];
				if (save[i][j] != arrayRow.at(i)->arrayBall[j]->isVisible()) {
					int i1;
					countEat++;
					for (i1 = 0; i1 < arrayEatBall.size(); i1++) {
						if (arrayEatBall.at(i1)->idColumn == j && arrayEatBall.at(i1)->idRow == i)
							break;
					}
					if (i1 == arrayEatBall.size()) {
						// hien effect bong roi
						AXLOGD("Bong roi ");
						this->dropBall(ball->idBall, ball->getPositionX() + START_X_TWENTY, ball->getPositionY() + START_Y_TWENTY);
					}
				}
			}
		}
		if (gameType == ENDLESS || gameType == STOMP) {
			score = score + GroupScore::getNormalBonusScore(arrayEatBall.size(), countEat - arrayEatBall.size(), bonusEffect->getMul(), bonusScore);
            if (score > 0)
            {
                JNIUtils::vibrate(10);
            }
			
			updateScore();
			GroupScore* group = getGroupScore();
			group->setVisible(true);
			group->createNormalBonusScore(arrayEatBall.size(), countEat - arrayEatBall.size(),
				bonusEffect->getMul(), bonusScore);
			group->setPosition(ball->rootX + groupBall->getPositionX() - group->getContentSize().width * 0.5f, ball->rootY + groupBall->getPositionY());
			group->runAction(Sequence::create(EaseBackOut::create(MoveBy::create(0.7f, Vec2(0, size.height * 0.1f))), FadeOut::create(0.5), Hide::create(), NULL));
		}

		updateArrayBall();

		if (gameType == STOMP) {

			if (arrayRow.size() == 0) {
				// hoan thanh stomp nay
				state = GameState::END_GAME;
				if (level >= game->level) {
					game->level = level + 1;
                    UserDefault::getInstance()->setIntegerForKey("level", game->level);
                    UserDefault::getInstance()->flush();
					//MyCaro.game.caroScreen.getLeveLayer().updateLobby();
					//PreferenceHandler.saveLevel();
				}
				// mo lobby stomp

				numRowScore = (int) ((bar->getPositionY() - rope->getPositionY() - rope->getRealHeight()) / HEIGH_BALL + 1);
				countRowScore = 1;
				makeEffectScore();
			}
		} else if (gameType == TIME) {

			if (arrayRow.size() == 0) {
				state = GameState::END_GAME;
				// Hoan thanh game
				string s;
				if (game->scoreTime == 0
					|| game->scoreTime > countTime) {
						game->scoreTime = (int) countTime;
						labelHighscore->setString(("Highscore: " + convertTime(countTime)).c_str());
						UserDefault::getInstance()->setIntegerForKey("scoreTime", game->scoreTime);
						UserDefault::getInstance()->flush();
						s = "New Best Time: " + convertTime(countTime);
				} else {
					s = "Finish. Your Time: " + convertTime(countTime);
				}
				GUIManager::getInstance().guiDialog->showGUI(s.c_str(), &makeNewGame, false, &makeBack);
				// update highscore
				
			}

		}

	} else {
		GameSound::playEggLands();
	}
	labelRow->setString((GameUtility::toString(arrayRow.size()) + " ROWS").c_str());
	if (gameType == TIME) {
		if (arrayRow.size() != 0)
			distanceY = rope->getPositionY() + rope->getRealHeight() - groupBall->getPositionY();
	}

	if (delay)
		delayReturn();
	delay = false;
}

double GUIGame::getDistance(Ball* ball, float x, float y) {
	double result;
	result = (groupBall->getPositionX() + ball->getPositionX() + ball->getRealWidth() * 0.5f - x)
		* (groupBall->getPositionX() + ball->getPositionX() + ball->getRealWidth() * 0.5f - x)
		+ (groupBall->getPositionY() + ball->getPositionY() + ball->getRealHeight() * 0.5f - y)
		* (groupBall->getPositionY() + ball->getPositionY() + ball->getRealHeight() * 0.5f - y);
	result = (float) (sqrt(result));
	return result;
}

bool GUIGame::checkEndGame() {
	if (gameType == TIME)
		return false;
	if (START_Y_TWENTY < rope->getPositionY() + rope->getRealHeight()) {
		return true;
	}
	return false;

}

void GUIGame::endGame() {
	state = GameState::END_GAME;
	genBall->setVisible(false);
    int count = 0;
	for (int i = 0; i < arrayRow.size(); i++) {
		for (int j = 0; j < NINE_ROW; j++) {
			if (arrayRow.at(i)->arrayBall[j]->isVisible()) {
				arrayRow.at(i)->arrayBall[j]->runAction(Sequence::create(DelayTime::create(count * 0.01), Hide::create(), NULL));
                if (GameUtility::getRandom() < 0.3f)
                {
                    showBomb(arrayRow.at(i)->arrayBall[j]->getPositionX() + groupBall->getPositionX(),
                             arrayRow.at(i)->arrayBall[j]->getPositionY() + groupBall->getPositionY(), count * 0.01);
                }
                count++;
				//showParticle(arrayRow.at(i)->arrayBall[j]->getPositionX() + groupBall->getPositionX(),
					//arrayRow.at(i)->arrayBall[j]->getPositionY() + groupBall->getPositionY(), arrayRow.at(i)->arrayBall[j]->idBall);
			}
		}

	}
	progress->cleanup();
	GameSound::playEnd();

	runAction(Sequence::create(DelayTime::create(1),  CallFunc::create(AX_CALLBACK_0(GUIGame::callbackEndGame, this)), NULL));
	
	// hien hop hoi thoai end game
}

void GUIGame::makeGenBall() {
	// TODO Auto-generated method stub
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if (state != GameState::PLAY)
		return;
	if (gameType == ENDLESS) {
		if (NUM_BALL == 8)
			return;
		ani->setVisible(true);
		genBall->setVisible(true);

		double rand = GameUtility::getRandom() * 45;
		rand = rand;
	//	rand = rand * (GameUtility::getRandom() > 0.5f ? 1 : -1);
		
		ani->setDegree(rand);
        ani->countAppear++;
		ani->setPosition(size.width * 0.5f, -ani->getRealHeight());
		genBall->setId(NUM_BALL);
		GameSound::playWhirley();
	} else if (gameType == STOMP) {
		// Tween.to(groupBall, ActorAccessor.POS_XY,
		// 500).target(groupBall->getPositionX(), groupBall->getPositionY() -
		// HEIGH_BALL)
		// .start(MyCaro.game.tweenManger);
		distanceY = HEIGH_BALL;
		countDistance = 0;
	}

}

void GUIGame::showParticle(float px, float py, int id) {
	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
    Size size    = Director::getInstance()->getRenderView()->getVisibleSize();

	string s = "particles/egg" + GameUtility::toString(id + 1) + ".plist";
//	s = "particles/vip.plist";
	ParticleEffect *effect = new ParticleEffect();
	effect->create(s.c_str(), layer);
	effect->particle->setPosition(px, py);
	effect->particle->setBlendAdditive(false);
	effect->particle->setAutoRemoveOnFinish(true);

    s = "GuiGame/Egg/bubble_" + to_string(id + 1) + ".png";
    effect->particle->setTexture(Director::getInstance()->getTextureCache()->addImage(s.c_str()));

// 	effect =  effectMgr->addParticleEffect("particles/egg.plist", Vec2 (px, py), layer);
// 	effect->particle->setBlendAdditive(false);
// 
	ParticleEffect *effect1 = new ParticleEffect();
	effect1->create("particles/ball.plist", layer);
	effect1->particle->setPosition(px, py);
	effect1->particle->setBlendAdditive(false);
	effect1->particle->setAutoRemoveOnFinish(true);

	if (bonusEffect->isVisible() && bonusEffect->getMul() > 1) {
		effect1 = new ParticleEffect();
		effect1->create("particles/bigbet.plist", layer);
		effect1->particle->setPosition(px, py);
		effect1->particle->setBlendAdditive(false);
		effect1->particle->setAutoRemoveOnFinish(true);
	}
}

void GUIGame::showBomb(float px, float py, float delayTime) {
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
        addChild(group);
    }
    group->setLocalZOrder(100);
    arrayBomb.push_back(group);
    group->setPosition(px, py);
    group->showBomb(delayTime);
}

void GUIGame::makeBonus() {
	for(int i = 0; i < arrayRow.size(); i++)
	{
		for(int j = 0; j < arrayRow.at(i)->arrayBall.size(); j++)
		{
			if(arrayRow.at(i)->arrayBall.at(j)->isVisible() && arrayRow.at(i)->arrayBall.at(j)->isBonus())
				return;
		}

	}
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	double rand = GameUtility::getRandom();
	int id;
	if (rand < 0.4f) {
		if (groupBall->getPositionY() < size.height * 0.35f) {
			if (GameUtility::getRandom() > 0.7f)
				nextBall->setIdBonus(4);
			else
				nextBall->setIdBonus(0);
		} else
			nextBall->setIdBonus(0);
	} else if (rand < 0.65f) {
		nextBall->setIdBonus(1);
	} else if (rand < 0.85f) {
		nextBall->setIdBonus(2);
	} else {
		nextBall->setIdBonus(3);
	}
	
	nextBonus = false;

}

void GUIGame::updateScore() {

	labelScore->setString(("Score: " + GameUtility::toString(score)).c_str());

	if (gameType == ENDLESS) {
		if (score > game->scoreEndless) {
			labelHighscore->setString(("Highscore: " + GameUtility::toString(score)).c_str());
			game->scoreEndless = score;
			UserDefault::getInstance()->setIntegerForKey("scoreEndless", score);
			UserDefault::getInstance()->flush();
			isNewhigh = true;
		}
	} else {
		if (score > game->scoreStomp[level]) {
			labelHighscore->setString(("Highscore: " + GameUtility::toString(score)).c_str());
			game->scoreStomp[level] = score;
			UserDefault::getInstance()->setIntegerForKey(("scoreStomp" + GameUtility::toString(level)).c_str(), score);
			UserDefault::getInstance()->flush();
			isNewhigh = true;
		}
	}
}

void GUIGame::newGame() {
	for (int i = 0; i < arrayGroupScore.size(); i++) {
		arrayGroupScore.at(i)->setVisible(false);
	}
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	//gameType = STOMP;
	//level = 4;
	initGame();
	arrayEatBall.clear();
	isNewhigh = false;
	int idBall = (int) (GameUtility::getRandom() * NUM_BALL);
	moveBall->setId(idBall);
	moveBall->setPosition(START_BALL_X, START_BALL_Y);

	int idNextBall = (int) (GameUtility::getRandom() * NUM_BALL);
	nextBall->setId(idNextBall);
	nextBall->setPosition(cannon1->getPositionX() + cannon1->getRealWidth() * 0.8f, cannon1->getPositionY() + cannon1->getRealHeight() * 0.8f);
	distanceY = 0;
	speedY = -1;
	if (gameType == ENDLESS) {
		START_Y_TWENTY = size.height * 0.5f;
		NUM_BALL = 3;
		rope->setPosition(size.width * 0.5f, START_BALL_Y + WIDTH_BALL * 1.5f);
		progress->setVisible(true);
		bgProgress->setVisible(true);
	} else if (gameType == TIME) {
		rope->setPosition(size.width * 0.5f, size.height * 0.4f);
		START_Y_TWENTY = rope->getPositionY() + rope->getRealHeight();
		progress->setVisible(false);
		bgProgress->setVisible(false);
		bar->setPosition(0, START_Y_TWENTY + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
	} else if (gameType == STOMP){
		rope->setPosition(size.width * 0.5f , START_BALL_Y + WIDTH_BALL * 1.5f);
		if(level == 11 || level ==16 || level == 17 || level == 18)
			START_Y_TWENTY = rope->getPositionY() + 3.9f * HEIGH_BALL;
		else if(level == 17)
			START_Y_TWENTY = rope->getPositionY() + 3.9f * HEIGH_BALL;
		else
			START_Y_TWENTY = rope->getPositionY() + 2.9f * HEIGH_BALL;
		progress->setVisible(true);
		bgProgress->setVisible(true);
		bar->setPosition(0,START_Y_TWENTY + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->getRealHeight());
	}
	groupBall->setPosition(START_X_TWENTY, START_Y_TWENTY);
        //bgProgress->setVisible(false);
	countTime = 0;
	countTimeVisible = 0;
	countVisible = -1;
	delay = false;
	arrayEatBall.clear();

	state = GameState::WAIT_PLAY;
	ani->newGame();

	genBall->setVisible(false);

	increaseSpeed = false;

	countTimeVibrate = 0;

	nextBonus = false;

    ani->setVisible(false);
	score = 0;
	if(gameType != TIME)
		updateScore();
	bonusEffect->setVisible(false);
	isMoving = false;

	for (int i = 0; i < arrayEffectBall.size(); i++) {
		arrayEffectBall.at(i)->setVisible(false);
	}

	// for (int i = 0; i < arrayRow.size(); i++) {
	// arrayRow.at(i)->renew(arrayRow.at(i)->typeRow);
	// }
}

void GUIGame::initGame() {
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	groupBall->removeAllChildren();
	arrayRow.clear();
	int NUM_ROW = 0;
	// START_X_TWENTY = 0;
	// WIDTH_BALL = WIDTH_BALL * 0.8f;
	// HEIGH_BALL = WIDTH_BALL * 0.9f;
	switch (gameType) {
	case ENDLESS:
		{
			labelHighscore->setString(("Highscore: " + GameUtility::toString(game->scoreEndless)).c_str());

			NUM_ROW = (int) (size.height * 0.73f / HEIGH_BALL);
			NINE_ROW = 9;
			EIGHT_ROW = NINE_ROW - 1;
			START_X_TWENTY = size.width * 0.1f;
			NUM_BALL = 3;
			for (int i = 0; i < NUM_ROW; i++) {
				RowBall* rowBall;
				rowBall = new RowBall(i);
				arrayRow.push_back(rowBall);
			}

			for (int i = 0; i < NUM_ROW; i++) {
				for (int j = 0; j < arrayRow.at(NUM_ROW - 1 - i)->arrayBall.size(); j++) {
					groupBall->addChild(arrayRow.at(i)->arrayBall[j]);
				}
				arrayRow[i]->effectNewGame(0.04 * i);
			}
			
			bar->setPositionY(size.height);

			labelRow->setVisible(false);
			bgRow->setVisible(false);

			bgProgress->setVisible(true);
			progress->cleanup();
			ProgressTo *to1 = ProgressTo::create(20, 100);
			//    Setup for a bar starting from the bottom since the midpoint is 0 for the y
			progress->setMidpoint(Vec2(0,1));
			//    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
			progress->setBarChangeRate(Vec2(0, 1));
			progress->setPercentage(0);
			progress->runAction(RepeatForever::create(Sequence::create(to1, CallFunc::create(AX_CALLBACK_0(GUIGame::callbackProgress, this)), NULL)));
			break;
		}
		
	case STOMP:
		{
            AXLOGD("Level %i ", level);
            JNIUtils::sendEvent("Level ", to_string(level).c_str());
            
			labelHighscore->setString(("Highscore: " + GameUtility::toString(game->scoreStomp[level])).c_str());
			game->readDataLevel(level);
            AXLOGD("Level Score %i ", game->scoreStomp[level]);
            JNIUtils::sendEvent("Score Level == ", GameUtility::toString(game->scoreStomp[level]).c_str());
			NUM_ROW = game->dataLevel[level].size();
			NINE_ROW = game->dataLevel[level][0].size();
			EIGHT_ROW = NINE_ROW - 1;
			NUM_BALL = game->numBall[level];
			START_X_TWENTY = (size.width - NINE_ROW * WIDTH_BALL) / 2;

			int typeRow = game->typeRow[level];
			for (int i = 0; i < NUM_ROW; i++) {
				RowBall* rowBall;
				rowBall = new RowBall(i, typeRow);
				typeRow = NINE_ROW + EIGHT_ROW - typeRow;
				arrayRow.push_back(rowBall);
			}

			for (int i = 0; i < NUM_ROW; i++) {
				for (int j = 0; j < arrayRow.at(NUM_ROW - 1 - i)->arrayBall.size(); j++) {
					groupBall->addChild(arrayRow.at(i)->arrayBall[j]);
					if (game->dataLevel[level][i][j] == -1) {
						arrayRow.at(i)->arrayBall[j]->setVisible(false);
					} else {
						arrayRow.at(i)->arrayBall[j]->setVisible(true);
						arrayRow.at(i)->arrayBall[j]->setId(game->dataLevel[level][i][j]);
					}
				}
			}
			
			bar->setVisible(true);

			labelRow->setVisible(false);
			bgRow->setVisible(false);
			labelRow->setString((to_string(NUM_ROW) + " ROWS").c_str());

			bgProgress->setVisible(true);
			progress->cleanup();
			ProgressTo *to1 = ProgressTo::create(10, 100);
			//    Setup for a bar starting from the bottom since the midpoint is 0 for the y
			progress->setMidpoint(Vec2(0,1));
			//    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
			progress->setBarChangeRate(Vec2(0, 1));
			progress->setPercentage(0);
			progress->runAction(RepeatForever::create(Sequence::create(to1, CallFunc::create(AX_CALLBACK_0(GUIGame::callbackProgress, this)), NULL)));
			break;
		}
		
	case TIME:
		{
			labelScore->setString("Time: 00:00");
			if (game->scoreTime == 0) {
				labelHighscore->setString("Best Time: --:-- ");
			} else {
				labelHighscore->setString(("Best Time: " + convertTime(game->scoreTime)).c_str());
			}
			NUM_ROW = 10;
			NINE_ROW = 9;
			EIGHT_ROW = NINE_ROW - 1;
			START_X_TWENTY = size.width * 0.1f;
			NUM_BALL = 7;

			for (int i = 0; i < NUM_ROW; i++) {
				RowBall* rowBall;
				rowBall = new RowBall(i);
				arrayRow.push_back(rowBall);
			}

			for (int i = 0; i < NUM_ROW; i++) {
				for (int j = 0; j < arrayRow.at(NUM_ROW - 1 - i)->arrayBall.size(); j++) {
					groupBall->addChild(arrayRow.at(i)->arrayBall[j]);
				}
			}

			bar->setVisible(true);
			bar->setPosition(0, groupBall->getPositionY() + arrayRow.at(arrayRow.size() - 1)->arrayBall[0]->rootY);
			labelRow->setVisible(true);
			bgRow->setVisible(true);
			break;
		}
		
	default:
		break;
	}

	LIMIT_X = START_X_TWENTY + WIDTH_BALL * NINE_ROW;
	leftWall->setPositionX(START_X_TWENTY - leftWall->getRealWidth() * 0.7f);
	rightWall->setPositionX(LIMIT_X - rightWall->getRealWidth() * 0.3f);

}

void GUIGame::updateTime() {

	labelScore->setString(GameUtility::convertTime(countTime).c_str());

}

string GUIGame::convertTime(float countTime) {
	int minute = (int) (countTime / 60);
	int second = (int) (countTime - minute * 60);

	string minuteS, secondS;
	if (minute < 10) {
		minuteS = "0" + GameUtility::toString(minute);
	} else {
		minuteS = "" + GameUtility::toString(minute);
	}

	if (second < 10) {
		secondS = "0" + GameUtility::toString(second);
	} else {
		secondS = "" + GameUtility::toString(second);
	}
	return minuteS + ":" + secondS;
}

void GUIGame::onPause() {
	
}

GroupScore * GUIGame::getGroupScore()
{
	GroupScore *group;
	for (int i = 0; i < arrayGroupScore.size(); i++) {
		if (!arrayGroupScore.at(i)->isVisible()) {
			arrayGroupScore.at(i)->setOpacity(255);
			return arrayGroupScore.at(i);
		}
	}
	group = new GroupScore();
	addChild(group);
	group->setLocalZOrder(100);

	arrayGroupScore.push_back(group);
	return group;
}


void GUIGame::callbackNextBall()
{
	moveBall->setVisible(true);
	if (speedY > 0) {
		delay = true;
	} else {
		// delay viec quay lai cua move ball
		delayReturn();
	}
}

void GUIGame::callbackRemove(Node* pSender)
{
	pSender->removeAllChildrenWithCleanup(true);
}

void GUIGame::callbackProgress()
{
	progress->setPercentage(0);
	makeGenBall();
	
}


void GUIGame::callbackEndGame()
{
	string s = "";

	if (gameType == ENDLESS || gameType == STOMP) {

		if (gameType == STOMP)
			GUIManager::getInstance().guiResult->showGUI(score, game->scoreStomp[level]);
		else
			GUIManager::getInstance().guiResult->showGUI(score, game->scoreEndless);
	} else {
		s = "Game Over";
		GUIManager::getInstance().guiDialog->showGUI(s.c_str(), &makeNewGame, false, &makeBack);
	}
	
}

void GUIGame::makeEffectScore()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	int add;
	if (countRowScore == numRowScore)
	{
		add = 1000;
		endGame();
	}
	else
	{
		add = countRowScore * 100;
		countRowScore++;
                runAction(Sequence::create(DelayTime::create(0.2f),
                                           CallFunc::create(AX_CALLBACK_0(GUIGame::makeEffectScore, this)), NULL));
	}

	score = score + add;
	updateScore();
	GroupScore* group = getGroupScore();
	group->setVisible(true);
	group->createBonusScore(add);
	group->setPosition(size.width * 0.5f - group->getContentSize().width * 0.5f, rope->getPositionY() + countRowScore * HEIGH_BALL);
	group->runAction(Sequence::create(Spawn::create(FadeOut::create(0.5f), 
		EaseBackOut::create(MoveBy::create(0.7f, Vec2(0, size.height * 0.1f))), NULL), FadeOut::create(0.5), Hide::create(), NULL));
}

void GUIGame::showGui( GameTypeEgg gameType )
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if (size.width / size.height < 320.0f / 480.0f) {
		JNIUtils::showAdsBanner(1);
	}
	else {
		JNIUtils::showAdsBanner(0);
	}
	this->gameType = gameType;
    newGame();
    btnTop->setVisible(false);
    if (gameType == ENDLESS || gameType == TIME)
    {
        btnTop->setVisible(true);
    }
    //btnTop->setVisible(false);
}

void GUIGame::showGui( int level )
{
    
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	if (size.width / size.height < 320.0f / 480.0f) {
		JNIUtils::showAdsBanner(1);
	}
	else {
		JNIUtils::showAdsBanner(0);
	}
	this->gameType = STOMP;
	this->level = level;
	if(isInitted() && isVisible())
		return;
	BaseGUI::showGUI();
	GUIManager::getInstance().addToListGui(this);
	newGame();
    btnTop->setVisible(false);
}


void GUIGame::initDragonbone()
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
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
}

void GUIGame::dropBall(int id, float posX, float posY)
{
	AXLOGD("DRO NE***");
	Ball* ball = getEffectBall();
	ball->setId(id);
	ball->setPosition(posX, posY);

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	posY = posY - size.height * 1.1f;

	ball->runAction(Sequence::create(EaseSineIn::create(MoveTo::create(1.2f, Vec2(posX, posY))), Hide::create(), NULL));
}

Ball* GUIGame::getEffectBall()
{
	Ball* ball = NULL;
	for (int i = 0; i < arrayEffectBall.size(); i++) {
		if (!arrayEffectBall.at(i)->isVisible()) {
			ball = arrayEffectBall.at(i);
			break;
		}
	}
	if (ball == NULL) {
		ball = new Ball();
		this->addChild(ball);
		arrayEffectBall.push_back(ball);
	}
	ball->setVisible(true);
	ball->stopAllActions();
	return ball;
}


void GUIGame::effectImage(int id)
{
	for (int j = 0; j < 10; j++) {
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
		image->setVisible(true);
		image->setOpacity(255);
		image->setScale(arrayRow.at(0)->arrayBall[0]->getScaleX());
		image->setTexture("GuiGame/Egg/bubble_" + to_string(id) + ".png");
		Size size = Director::getInstance()->getRenderView()->getVisibleSize();
		image->initCoin(ImageEffect::TYPE_FLOW, 0, size.width * GameUtility::getRandom(), size.height * 1);
	}
}

void GUIGame::addNewBall()
{
	NUM_BALL++;
	genBall->setVisible(false);
	effectImage(NUM_BALL);
}
