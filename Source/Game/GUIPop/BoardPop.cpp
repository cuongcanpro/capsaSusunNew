#include "BoardPop.h"
#include <cmath>  
#include <string>
#include "../Utility/GameUtility.h"
#include "Engine/GUI/ParticleEffect.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "Game/Utility/GameSound.h"
#include "Game/Utility/JNIUtils.h"
#include <Game/Utility/Toast.h>

BoardPop::BoardPop(void)
{
	// khoi tao mang cac khoi number
	for (int i = 0; i < BOARD_ROW_POP; i++) {
		for (int j = 0; j < BOARD_COLUMN_POP; j++) {
			arrayNumber[i][j] = new PopObjectNumber();
			this->addChild(arrayNumber[i][j]);
			//	arrayNumber[i][j]->setNumber(i);
			//arrayNumber[i][j]->setVisible(false);
		}
	}
	sizeCell = arrayNumber[0][0]->getContentSize().width * RATE_SIZE;
	for (int i = 0; i < BOARD_ROW_POP; i++) {
		for (int j = 0; j < BOARD_COLUMN_POP; j++) {
			arrayNumber[i][j]->setPosition(sizeCell * (j + 0.5), sizeCell * (i + 0.5));
			arrayNumber[i][j]->setRootPosition();
		}
	}
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	lbNotMove = Text::create("No Move, you need to use bomb to destroy block", "fonts/tahomabd.ttf", 22);
    lbNotMove->setTextHorizontalAlignment(ax::TextHAlignment::CENTER);
    lbNotMove->setTextAreaSize(Size(size.width * 0.9, -1));
	lbNotMove->enableOutline(Color4B(50, 10, 0, 255), 2);
	addChild(lbNotMove, 10);

	data = new BoardDataPop();

     auto effect = efk::Effect::create("fire.efk", 80.0f);
    if (effect != nullptr)
    {
        effBomb = efk::EffectEmitter::create(game->manager);
        effBomb->setEffect(effect);
        effBomb->setPlayOnEnter(false);
        effBomb->setRemoveOnStop(false);
        effBomb->setSpeed(0.5);
        // emitter->setScale(13);
        this->addChild(effBomb, 10);
    }

    for (int i = 0; i < 10; i++)
    {
        _streak =
            MotionStreak::create(0.5f, 5.0f, 100, Color3B(255, 255, 255), "GuiGame/" + GameUtility::getResourceBall(1));
        Texture2D* texture = _director->getTextureCache()->addImage("GuiGame/" + GameUtility::getResourceBall(1));
        _streak->setTexture(texture);
        addChild(_streak);
        _streak->setLocalZOrder(10);
        _streak->setVisible(false);
        arrayStreak[i] = _streak;
    }
    
}

BoardPop::~BoardPop(void)
{
}

void BoardPop::updateBoardSize()
{
	float width = sizeCell * data->currentSize;
	float height = sizeCell * data->currentSize;
	lbNotMove->setPosition(Vec2(width * 0.5, 20));
	setContentSize(Size(width, height));
}

void BoardPop::newGame() {
    timeNoTouch = -1;
	state = POP_NORMAL;
	lbNotMove->setVisible(false);
	//effBomb->setVisible(false);
	
    string add         = data->type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
	int saveScoreMerge = UserDefault::getInstance()->getIntegerForKey(("saveScorePop" + add).c_str(), 0);
	//saveScoreMerge = 0;
	if (saveScoreMerge > 0) {
		// dang choi do
		data->loadGame();
		for (int i = 0; i < BOARD_ROW_POP; i++) {
			for (int j = 0; j < BOARD_COLUMN_POP; j++) {
				if (data->arrayBall[i][j] > 0) {
					arrayNumber[i][j]->setNumber(data->arrayBall[i][j]);
					arrayNumber[i][j]->effectNewGame();
				}
			}
		}
		callbackGenNew();
	}
    else
    {
        data->newGame();
        for (int i = 0; i < BOARD_ROW_POP; i++)
        {
            for (int j = 0; j < BOARD_COLUMN_POP; j++)
            {
                arrayNumber[i][j]->setVisible(false);
            }
        }
        for (int i = 0; i < data->currentSize; i++)
        {
            for (int j = 0; j < data->currentSize; j++)
            {
                //	arrayNumber[i][j]->setVisible(false);
                arrayNumber[i][j]->setNumber(data->arrayBall[i][j]);
                arrayNumber[i][j]->setAvailable(false);
                arrayNumber[i][j]->resetPosition();
                arrayNumber[i][j]->showBomb(false);
            }
        }
        for (int i = 0; i < arrayLabel.size(); i++)
        {
            arrayLabel[i]->setVisible(false);
        }
        
    }
}

void BoardPop::saveGame()
{
	string s = "";
	for (int i = 0; i < BOARD_ROW_POP; i++)
		for (int j = 0; j < BOARD_COLUMN_POP; j++)
		{
			int num = 0;
			if (arrayNumber[i][j]->getAvailable()) {
				num = arrayNumber[i][j]->getNumber();
			}
			else {
				num = 0;
			}
			if (i == 0 && j == 0)
			{
				s = s + GameUtility::toString(num);
			}
			else
			{
				s = s + "," + GameUtility::toString(num);
			}
		}
        string add = data->type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
	UserDefault::getInstance()->setStringForKey(("dataPop" + add).c_str(), s);
	UserDefault::getInstance()->setIntegerForKey(("maxNum" + add).c_str(), data->maxNum);
	UserDefault::getInstance()->setIntegerForKey(("numBomb" + add).c_str(), GUIManager::getInstance().guiPop->numBomb);
	UserDefault::getInstance()->flush();
}

bool BoardPop::checkInBoard(float posX, float posY)
{
	if (posX < 0 || posX > getContentSize().width || posY < 0 || posY > sizeCell * data->currentSize)
		return false;
	return true;
}

/**
 * Khi User tha tay khoi man hinh
 */
void BoardPop::doTouchEnd(float posX, float posY)
{
    if (state != POP_NORMAL && state != POP_BOMB)
        return;
	if (checkInBoard(posX, posY) == false)
		return;
	int column = (posX / sizeCell);
	if (column >= data->currentSize)
		return;
	int row = (posY / sizeCell);
	if (row >= data->currentSize)
		return;
    timeNoTouch = 0;
	// neu dang su dung bomb, dien Effect Bomb va gen number moi
	if (state == POP_BOMB) {
		data->arrayBall[row][column] = 0;
		state = POP_EFFECT;
		for (int i = 0; i < data->currentSize; i++) {
			for (int j = 0; j < data->currentSize; j++) {
				arrayNumber[i][j]->showBomb(false);
			}
		}
		effectBomb(arrayNumber[row][column]->getPosition());
		genNew();
		return;
	}

	// cap nhat diem so cua cac o so khac tinh tu diem cham
    if (data->arrayBall[row][column] > NUM_SPECIAL)
    {
        AXLOGD("No Touch");
        Toast::makeToast(2.0, ("You need eat " + to_string(data->arrayBall[row][column] - NUM_SPECIAL) + " Blocks to destroy this Block").c_str());
        return;
    }
	countEat = 0;
	data->updatePoint(column, row);
	float maxTime = 0;
    float DEFAULT_TIME = 0.1;
    vector<PointGame> arr;
	for (int i = 0; i < data->currentSize; i++)
		for (int j = 0; j < data->currentSize; j++) {
			if ((i != row || j != column) && data->arrayWay[i][j]->point >= 0) {
				// voi nhung diem co cung so voi diem cham, gia tri cua no gan lai = 0 dong thoi di chuyen ve phia diem cham
				data->arrayBall[i][j] = 0;
				countEat++;
				data->setWay(i, j);
				ax::Vector<ax::FiniteTimeAction*> actions;
				int size = data->arrayPoint.size();
                
				float time = DEFAULT_TIME / size;
                float sumTime = 0;
				for (int k = 1; k < size; k++) {
                    time = DEFAULT_TIME - 0.015 * k;
					if (time < 0.03)
						time = 0.03;
					sumTime = sumTime + time;
					actions.pushBack(MoveTo::create(time, convertToPosition(data->arrayPoint.at(k)->y, data->arrayPoint.at(k)->x)));
				}
				sumTime = sumTime + time;
				if (sumTime > maxTime) {
					maxTime = sumTime;
				}
                //maxTime = DEFAULT_TIME;
				actions.pushBack(MoveTo::create(time, convertToPosition(row, column)));
				auto action = Sequence::create(actions);
                arrayNumber[i][j]->stopAllActions();
				arrayNumber[i][j]->runAction(action);
				arrayNumber[i][j]->setLocalZOrder(1);

                PointGame p;
                p.x = i;
                p.y = j;
                arr.push_back(p);
			}
		}
    AXLOGD("MAX TIME %f ", maxTime);
	PopObjectNumber* obj = arrayNumber[row][column];
	if (countEat > 0) {
        state = POP_EFFECT;
            bool isDestroy = false;
        if (countEat > 0 && data->getNumSpecial() > 0) {
            PointGame p = data->getPosDestroy(countEat + 1);
            if (p.x >= 0 && p.y >= 0)
            {
                // Destroy o nay
                data->arrayBall[p.x][p.y] = 0;
                for (int i = 0; i < arr.size() && i < 10; i++)
                {
                    MotionStreak* _streak = arrayStreak[i];
                    _streak->reset();
                    Texture2D* texture = _director->getTextureCache()->addImage("GuiGame/pop/bubble.png");
                    _streak->setTexture(texture);
                    _streak->setColor(GameUtility::getColorPop(obj->number));
                    AXLOGD("XONG XUOI 3 ");
                    _streak->setVisible(true);
                    _streak->setPosition(arrayNumber[arr[i].x][arr[i].y]->getPosition());
                    ccBezierConfig config;
                    config.controlPoint_1 = _streak->getPosition();
                    config.endPosition    = arrayNumber[p.x][p.y]->getPosition();
                    config.controlPoint_2 = Vec2(700 * AXRANDOM_0_1(), 700 * AXRANDOM_0_1());
                    _streak->runAction(
                        Sequence::create(
                            DelayTime::create(0.1 * i),
                            EaseExponentialOut::create(BezierTo::create(0.8, config)),
                            NULL
                        )
                    );
                    isDestroy = true;
                }
                pointDestroy.x = p.x;
                pointDestroy.y = p.y;
            }
        }
        if (isDestroy)
        {
            if (maxTime < 1.0)
            {
                maxTime = 1.0;
            }
            runAction(
			Sequence::create(
				DelayTime::create(0.5),
                CallFunc::create(AX_CALLBACK_0(BoardPop::callbackDestroy, this)),
				NULL
			)
		);
        }

		// kiem tra cac khoi an sau khi roi xuong
		playParticle(obj->getPositionX(), obj->getPositionY(), obj->number);
		runAction(
			Sequence::create(
				DelayTime::create(maxTime),
                CallFunc::create(AX_CALLBACK_0(BoardPop::callbackAfterMove, this)),
				NULL
			)
		);
		GameSound::playEat(countEat);
        
	}
	else {
		GameSound::playError();
		//JNIUtils::vibrate();
	}
}

void BoardPop::callbackDestroy() {
    effectBomb(arrayNumber[pointDestroy.x][pointDestroy.y]->getPosition());
}

void BoardPop::callbackAfterMove() {
    int row    = data->currentPoint->y;
    int column = data->currentPoint->x;
    if (row < 0 || column < 0 || row > BOARD_ROW_POP || column > BOARD_COLUMN_POP)
        return;
	int score = countEat * data->arrayBall[row][column];
	effectScore(score, convertToPosition(row, column));
	GUIManager::getInstance().guiPop->addScore(score);

	// tang gia tri cua ho hien tai, neu o hien tai dat moc level moi thi Show Effect
    if (data->updateValueCurrent())
    {
        GUIManager::getInstance().guiPop->updateMaxNum();
        if (data->type == BoardType::POP_TYPE_NORMAL)
        {
            if (data->maxNum > game->bestNum)
            {
                game->bestNum = data->maxNum;
                UserDefault::getInstance()->setIntegerForKey("bestNum", game->bestNum);
                UserDefault::getInstance()->flush();
                GUIManager::getInstance().guiPop->updateBestNum();
            }
        }
        else
        {
            if (data->maxNum > game->bestNumHard)
            {
                game->bestNum = data->maxNum;
                UserDefault::getInstance()->setIntegerForKey("bestNumHard", game->bestNum);
                UserDefault::getInstance()->flush();
                GUIManager::getInstance().guiPop->updateBestNum();
            }
        }
        Vec2 pos = convertToWorldSpace(arrayNumber[row][column]->getPosition());
        if (data->maxNum > LIMIT_SIZE_POP)
        {
            GameSound::playNewNumber();
            GUIManager::getInstance().guiPop->showNewNumber(data->maxNum, pos, 1);
        }
        else
        {
            GameSound::playUpNumber();
            GUIManager::getInstance().guiPop->showFlyNumber(data->maxNum, pos, 1);
        }
    }
	genNew();
}

void BoardPop::genNew() {
	data->renewBall();
	for (int i = 0; i < data->currentSize; i++)
		for (int j = 0; j < data->currentSize; j++) {
			arrayNumber[i][j]->setNumber(data->arrayBall[i][j]);
			arrayNumber[i][j]->setLocalZOrder(0);
		}
	for (int i = 0; i < data->arrayMoveEnd.size(); i++) {
		PointGame* pBegin = data->arrayMoveBegin[i];
		PointGame* pEnd = data->arrayMoveEnd[i];
		PopObjectNumber* number = arrayNumber[pEnd->y][pEnd->x];
		number->setPosition(convertToPosition(pBegin->y, pBegin->x));
		number->moveDown(0.2);
	}
	//GameSound::playHit();
	runAction(
		Sequence::create(
			DelayTime::create(0.23),
			CallFunc::create(AX_CALLBACK_0(BoardPop::callbackGenNew, this)),
			NULL
		)
	);
	
}

void BoardPop::callbackGenNew() {
    if (state == POP_BOMB || state == POP_END || state == POP_WILL_USE_BOMB)
        return;
	state = POP_NORMAL;
	if (data->checkNoMove()) {
		GameSound::playError();
		//JNIUtils::vibrate();
		// Neu khong the di chuyen them nua, dua vao trang thai su dung Bomb hoac End Game
		if (GUIManager::getInstance().guiPop->numBomb > 0) {
            state = POP_WILL_USE_BOMB;
			lbNotMove->setVisible(true);
			lbNotMove->setScale(5);
			lbNotMove->runAction(
				Sequence::create(
					EaseBounceOut::create(ScaleTo::create(0.6, 1)),
					DelayTime::create(0.5),
                    CallFunc::create(AX_CALLBACK_0(BoardPop::callbackNoMove, this)),
					NULL
				)
			);
			saveGame();
		}
		else {
            endGame();
		}
	}
	else {
		saveGame();
	}
}

void BoardPop::callbackNoMove()
{
    if (state == POP_BOMB)
        return;
    GUIManager::getInstance().guiPop->useBomb();
}

void BoardPop::endGame() {
    for (int i = 0; i < data->currentSize; i++)
    {
        for (int j = 0; j < data->currentSize; j++)
        {
            arrayNumber[i][j]->effectEndGame();
        }
    }
    state = POP_END;
    string add = data->type == BoardType::POP_TYPE_NORMAL ? "" : "Hard";
    UserDefault::getInstance()->setIntegerForKey(("saveScorePop" + add).c_str(), 0);
    UserDefault::getInstance()->flush();
    JNIUtils::sendEvent(("number_" + GameUtility::toString(data->maxNum)).c_str(), "1");
    runAction(Sequence::create(DelayTime::create(1.5),
                               CallFunc::create(AX_CALLBACK_0(BoardPop::callbackEffectEndGame, this)), NULL));
}

void BoardPop::useBomb()
{
	state = POP_BOMB;
	for (int i = 0; i < data->currentSize; i++) {
		for (int j = 0; j < data->currentSize; j++) {
			arrayNumber[i][j]->stopAllActions();
			arrayNumber[i][j]->resetPosition();
			arrayNumber[i][j]->showBomb(true);
		}
	}
}

void BoardPop::effectBomb(Vec2 pos)
{
	float dx = 10;
	float dy = 10;
	runAction(
		Sequence::create(
			MoveBy::create(0.1, Vec2(dx  * 0.5 - GameUtility::getRandom() * dx, dy * 0.5 - GameUtility::getRandom() * dy)),
			MoveBy::create(0.1, Vec2(dx  * 0.5 - GameUtility::getRandom() * dx, dy * 0.5 - GameUtility::getRandom() * dy)),
			MoveBy::create(0.1, Vec2(dx  * 0.5 - GameUtility::getRandom() * dx, dy * 0.5 - GameUtility::getRandom() * dy)),
			MoveTo::create(0.1, getPosition()),
			NULL
		)
	);
	lbNotMove->setVisible(false);
	/*effBomb->setPosition(pos);
	effBomb->setLocalZOrder(1);
	effBomb->setVisible(true);
	effBomb->gotoAndPlay("run", -1, -1, 1);*/
    effBomb->stop();
    effBomb->setPosition(pos);
    effBomb->setVisible(true);
    effBomb->play(0);
	GameSound::playBomb();
}

Vec2 BoardPop::getPosCell(int row, int column)
{
    return convertToWorldSpace(this->arrayNumber[row][column]->getPosition());
}


void BoardPop::callbackEffectEndGame()
{
	for (int i = 0; i < data->currentSize; i++)
		for (int j = 0; j < data->currentSize; j++) {
			arrayNumber[i][j]->setVisible(false);
			arrayNumber[i][j]->stopAllActions();
			effectImage(arrayNumber[i][j]);
		}
	runAction(Sequence::create(
		DelayTime::create(1.0),
        CallFunc::create(AX_CALLBACK_0(BoardPop::callbackEffectEndGame1, this)),
		NULL
	));
	GameSound::playFirework();
}


void BoardPop::callbackEffectEndGame1()
{
	GUIManager::getInstance().guiPop->endGame();
}

void BoardPop::effectImage(PopObjectNumber* ball)
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
	image->setTexture("GuiGame/brickWhite.png");
	image->setVisible(true);
	image->setOpacity(255);
	image->setColor(GameUtility::getColorMerge(ball->getNumber()));
	//image->setScale(ball->rootScaleX * 1.1);
	//image->setTexture("480_800/bgNumber.png");
	image->initCoin(ImageEffect::TYPE_FLOW, 0, ball->getPositionX(), ball->getPositionY());
}

void BoardPop::playParticle(float posX, float posY, int id)
{
	Vec2 globalPos = convertToWorldSpace(Vec2(posX, posY));
	globalPos.y = globalPos.y - sizeCell * 0.4;
	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);

	ParticleEffect *effect = new ParticleEffect();
	effect->create("ParticlesGame/FlyUp.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
	effect->particle->setPosition(globalPos.x, globalPos.y);
	effect->particle->setBlendAdditive(true);
        Color4F color1 = Color4F(GameUtility::getColorMerge(id));
	/*color1.r = 1;
	color1.g = 1;
	color1.b = 1;*/
	color1.a = 1;
        Color4F color2 = Color4F(GameUtility::getColorMerge(id));
	effect->particle->setStartColor(color1);
	effect->particle->setStartColorVar(Color4F(0, 0, 0, 0));
	/*color2.r = 1;
	color2.g = 1;
	color2.b = 1;*/
	color2.a = 0;
	effect->particle->setEndColor(color2);
	effect->particle->setCascadeOpacityEnabled(true);
	effect->particle->setEndColorVar(Color4F(0, 0, 0, 0));
	effect->particle->setAutoRemoveOnFinish(true);
	//effect->particle->setTexture(TextureCache::sharedTextureCache()->addImage(("480_800/cell_" + GameUtility::toString(id % 10) + ".png").c_str()));

	ParticleEffect *effectSlow = new ParticleEffect();
	effectSlow->create("ParticlesGame/FlyUpSlow.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
	effectSlow->particle->setPosition(globalPos.x, globalPos.y);
	effectSlow->particle->setBlendAdditive(true);
	effectSlow->particle->setStartColor(color1);
	effectSlow->particle->setStartColorVar(Color4F(0, 0, 0, 0));
	effectSlow->particle->setEndColor(color2);
	effectSlow->particle->setCascadeOpacityEnabled(true);
	effectSlow->particle->setEndColorVar(Color4F(0, 0, 0, 0));
	effectSlow->particle->setAutoRemoveOnFinish(true);
}


Sprite* BoardPop::getSmoke()
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
		addChild(image);
		arraySmoke.push_back(image);
	}
	image->setVisible(true);
	image->setOpacity(255);
	return  image;
}

void BoardPop::update(float delta)
{
	for (int i = 0; i < arrayImageEffect.size(); i++) {
		if (arrayImageEffect.at(i)->isVisible()) {
			arrayImageEffect.at(i)->updateCoin(game->deltaTime);
		}
	}

    if (timeNoTouch >= 0)
    {
        timeNoTouch = timeNoTouch + delta;
        if (timeNoTouch > 2)
        {
            // reset lai position va mang touch point
            for (int i = 0; i < data->currentSize; i++)
            {
                for (int j = 0; j < data->currentSize; j++)
                {
                    arrayNumber[i][j]->resetPosition();
                }
            }
            timeNoTouch = -1;
        }
    }
}

void BoardPop::effectScore(int score, Vec2 pos)
{
	Text* label = NULL;
	for (int i = 0; i < arrayLabel.size(); i++) {
		if (!arrayLabel.at(i)->isVisible()) {
			label = arrayLabel.at(i);
			break;
		}
	}
	if (label == NULL) {
		label = Text::create("SCORE", "fonts/tahomabd.ttf", 50);
		addChild(label);
		label->enableOutline(Color4B(115, 37, 31, 255), 1);
		arrayLabel.push_back(label);
	}
	label->setVisible(true);
	label->setOpacity(0);
	label->setLocalZOrder(2);
	label->setPosition(pos);
	label->setString(GameUtility::toString(score));
	label->runAction(
		Sequence::create(
			Spawn::create(
				FadeTo::create(0.3, 180),
				EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 70))),
				NULL
			),
			DelayTime::create(0.5),
			FadeOut::create(0.5),
			Hide::create(),
			NULL
		)
	);
}

ax::Vec2 BoardPop::convertToPosition(int row, int column)
{
	return Vec2((column + 0.5) * sizeCell, (row + 0.5) * sizeCell);
}

