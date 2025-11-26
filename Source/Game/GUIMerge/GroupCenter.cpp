#include "GroupCenter.h"
#include <cmath>  
#include <string>
#include "Game/Utility/GameUtility.h"
#include "Game/Logic/Logic.h"
#include "Engine/GUI/ParticleEffect.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "Game/Utility/GameSound.h"
#include "Game/Utility/JNIUtils.h"

GroupCenter::GroupCenter(void)
{
	// init cac cot, arrow o phia tren cung
	Sprite* arrayBgUp[NUM_COLUMN_MERGE];
	for (int i = 0; i < NUM_COLUMN_MERGE; i++) {
		arrayBgColumn[i] = Sprite::create("GuiGame/bgWhite.png");
		arrayBgColumn[i]->setAnchorPoint(Vec2(0.5, 0));
		Color3B color;
		if (i % 2 == 0) {
                    color = Color3B(30, 30, 30);
		}
		else {
                    color = Color3B(50, 50, 50);
		}
		arrayBgColumn[i]->setColor(color);
		this->addChild(arrayBgColumn[i]);

		Sprite* bgUp = Sprite::create("GuiGame/bgWhite.png");
		bgUp->setAnchorPoint(Vec2(0.5, 0));
		addChild(bgUp);
		bgUp->setColor(color);
		arrayBgUp[i] = bgUp;

		arrayArrow[i] = Sprite::create("GuiGame/Merge/iconArrow.png");
		addChild(arrayArrow[i]);
	}

	// cot effect roi xuong
	spriteColumnEffect = Sprite::create("GuiGame/bgWhite.png");
	spriteColumnEffect->setAnchorPoint(Vec2(0.5, 0));
	//	arrayBgColumn[i]->setOpacity(50);
	this->addChild(spriteColumnEffect);

	// khoi tao mang cac khoi number
	for (int i = 0; i < NUM_ROW_MERGE; i++) {
		for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
			arrayNumber[i][j] = new ObjectNumber();
			this->addChild(arrayNumber[i][j]);
			//	arrayNumber[i][j]->setNumber(i);
			arrayNumber[i][j]->setVisible(false);
		}
	}
	sizeCell = arrayNumber[0][0]->getContentSize().width * RATE_SIZE;
	for (int i = 0; i < NUM_ROW_MERGE; i++) {
		for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
			arrayNumber[i][j]->setPosition(sizeCell * (j + 0.5), sizeCell * (i + 0.5));
			arrayNumber[i][j]->setRootPosition();
		}
	}
	float width = sizeCell * NUM_COLUMN_MERGE;
	float height = sizeCell * NUM_ROW_MERGE;

	// tinh lai kich thuoc cho cac cot
	for (int i = 0; i < NUM_COLUMN_MERGE; i++) {
		Text* label = Text::create(GameUtility::toString(i), "fonts/tahomabd.ttf", 18);
		addChild(label);
		label->setPosition(Vec2(arrayNumber[0][i]->getPositionX(), -30));
		float sX = width / arrayBgColumn[i]->getContentSize().width / NUM_COLUMN_MERGE;
		float sY = height / arrayBgColumn[i]->getContentSize().height;
		arrayBgColumn[i]->setScale(sX, sY);
		arrayBgColumn[i]->setPosition(arrayNumber[0][i]->getPositionX(), 0);

		sY = sizeCell / arrayBgUp[i]->getContentSize().height;
		arrayBgUp[i]->setScale(sX, sY);
		arrayBgUp[i]->setPosition(arrayNumber[0][i]->getPositionX(), sizeCell * (NUM_ROW_MERGE + 0.05));

		arrayArrow[i]->setPosition(arrayNumber[0][i]->getPositionX(), sizeCell * (NUM_ROW_MERGE + 0.55));
	}
	spriteColumnEffect->setScale(arrayBgColumn[0]->getScaleX(), arrayBgColumn[0]->getScaleY());
	spriteColumnEffect->setVisible(false);

	moveNumber = new ObjectNumber();
	addChild(moveNumber);
	moveNumber->setVisible(false);
	moveNumber->setNumber(1);

	Text* label = Text::create("Next Number", "fonts/tahomabd.ttf", 24);
	addChild(label);
	label->setPosition(Vec2(width * 0.5 - 30, arrayBgUp[0]->getPositionY() + sizeCell + 40));

	nextNumber = new ObjectNumber();
	addChild(nextNumber);
	nextNumber->setScale(0.5);
	nextNumber->setPosition(label->getPositionX() + label->getContentSize().width * 0.5 + nextNumber->getContentSize().width * 0.5, label->getPositionY());
	nextNumber->setNumber(1);

	setContentSize(Size(width, label->getPositionY() + 30));
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);

	iconHand = Sprite::create("GuiGame/iconHand.png");
    iconHand->setAnchorPoint(Vec2(0.2, 0.8));
	this->addChild(iconHand);
	iconHand->setVisible(false);

	lastColumn = 0;
}

GroupCenter::~GroupCenter(void)
{
}

void GroupCenter::newGame() {
	for (int i = 0; i < NUM_ROW_MERGE; i++) {
		for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
			arrayNumber[i][j]->setVisible(false);
			arrayNumber[i][j]->setAvailable(false);
			arrayNumber[i][j]->resetPosition();
		}
	}
	for (int i = 0; i < arrayLabel.size(); i++) {
		arrayLabel[i]->setVisible(false);
	}
	lastColumn = NUM_COLUMN_MERGE / 2;
	numEat = 0;
	maxNum = 5;
	isPause = false;
	speedDown = -1.1;
	moveNumber->setVisible(false);

	isTutorial = UserDefault::getInstance()->getBoolForKey("isTutorial", true);
	//isTutorial = true;
	if (isTutorial) {
		// Show Tutorial
		nextNumber->setNumber(1);
		tutorialIndex = 0;
		UserDefault::getInstance()->setBoolForKey("isTutorial", false);
		UserDefault::getInstance()->flush();
		genBall();
		return;
	}

	int saveScoreMerge = UserDefault::getInstance()->getIntegerForKey("saveScoreMerge", 0);
	//saveScoreMerge = 0;
	if (saveScoreMerge > 0) {
		// dang choi do
		string s = (string)(UserDefault::getInstance()->getStringForKey("dataMerge", ""));
		char * pch = new char[s.size() + 1];
		std::copy(s.begin(), s.end(), pch);
		pch[s.size()] = '\0'; // don't forget the terminating 0
		int data[NUM_COLUMN_MERGE * NUM_ROW_MERGE];
		char *num;
		num = strtok(pch, ",");
		data[0] = atoi(num);
		for (int i = 1; i < NUM_COLUMN_MERGE * NUM_ROW_MERGE; i++)
		{
			num = strtok(NULL, ",");
			data[i] = atoi(num);
		}
		maxNum = 5;
		for (int i = 0; i < NUM_COLUMN_MERGE * NUM_ROW_MERGE; i++) {
			int row = i / NUM_COLUMN_MERGE;
			int column = i % NUM_COLUMN_MERGE;
			if (data[i] > 0) {
				if (data[i] > maxNum)
					maxNum = data[i];
				arrayNumber[row][column]->setNumber(data[i]);
				arrayNumber[row][column]->effectNewGame();
			}
		}
	}
	genBall();
}

void GroupCenter::saveGame()
{
	string s = "";
	for (int i = 0; i < NUM_ROW_MERGE; i++)
		for (int j = 0; j < NUM_COLUMN_MERGE; j++)
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

	UserDefault::getInstance()->setStringForKey("dataMerge", s);
}

void GroupCenter::genBall()
{
	for (int i = 0; i < NUM_ROW_MERGE; i++) {
		for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
			if (arrayNumber[i][j]->getAvailable() && arrayNumber[i][j]->getNumber() > maxNum) {
				maxNum = arrayNumber[i][j]->getNumber();
				if (maxNum >= 10) {
					Vec2 pos = convertToWorldSpace(arrayNumber[i][j]->getPosition());
					GUIManager::getInstance().guiMerge->showNewNumber(maxNum, pos, getScale());
					isPause = true;
				}
				speedDown = -1.1  * (1 + (maxNum - 5) / 10.0f);
			}
		}
	}

	if (moveNumber->isVisible() == false) {
		moveNumber->setVisible(true);
		moveNumber->stopAllActions();
		moveNumber->setNumber(nextNumber->getNumber());
		if (isTutorial) {
			if (tutorialIndex == 0) {
				nextNumber->setNumber(2);
				doTutorial();
			}
			else if (tutorialIndex == 1) {
				nextNumber->setNumber(2);
				doTutorial();
			}
			else if (tutorialIndex == 2) {
				nextNumber->setNumber(2);
				doTutorial();
			}
		}
		else {
			int randValue = GameUtility::getRandom() * (maxNum - 4) + 1;
			if (maxNum < 10) {
				randValue = GameUtility::getRandom() * 5 + 1;
			}
			else {
				randValue = GameUtility::getRandom() * (maxNum - 4) + 1;
			}
			nextNumber->setNumber(randValue);
		}

		nextNumber->runAction(
			Sequence::create(
				ScaleTo::create(0.1, 0),
				DelayTime::create(0.2),
				EaseBounceOut::create(ScaleTo::create(0.3, 0.5)),
				NULL
			)
		);

		//moveNumber->setPosition(sizeCell * (3 + 0.5), getContentSize().height * 0.9);
		moveNumber->setPosition(nextNumber->getPosition());
		moveNumber->setScale(nextNumber->getScale());
		moveNumber->runAction(
			Sequence::create(
				Spawn::create(
					EaseBounceOut::create(ScaleTo::create(0.3, 1)),
					EaseSineOut::create(MoveTo::create(0.3, arrayArrow[lastColumn]->getPosition())),
					NULL
				),
				CallFunc::create(AX_CALLBACK_0(GroupCenter::callbackGenBall, this)),
				NULL
			)
		);
		state = GroupState::GROUP_GEN;
		for (int i = 0; i < NUM_COLUMN_MERGE; i++) {
			arrayArrow[i]->setColor(Color3B(100, 100, 100));
		}
		arrayArrow[lastColumn]->setColor(Color3B(100, 100, 200));
	}
	saveGame();
}

void GroupCenter::callbackGenBall() {
	state = GroupState::GROUP_MOVE;
}

/**
 * Khi User di chuyen tay tren man hinh
 */
void GroupCenter::doMoveBall(float posX, float posY)
{
	if (state == GroupState::GROUP_GEN)
		return;
	if (checkInBoard(posX, posY) == false)
		return;
	int column = (posX / sizeCell);
	if (column >= NUM_COLUMN_MERGE)
		return;
	moveNumber->setPositionX(arrayNumber[0][column]->getPositionX());
}

bool GroupCenter::checkInBoard(float posX, float posY)
{
	if (posX < 0 || posX > getContentSize().width || posY < 0 || posY > sizeCell * NUM_ROW_MERGE)
		return false;
	return true;
}

/**
 * Khi User tha tay khoi man hinh
 */
void GroupCenter::doDropBall(float posX, float posY)
{
	numEat = 0;
	if (state != GroupState::GROUP_MOVE)
		return;
	if (checkInBoard(posX, posY) == false)
		return;
	if (moveNumber->isVisible() == false)
		return;
	int column = (posX / sizeCell);
	lastColumn = column;
	if (column >= NUM_COLUMN_MERGE)
		return;
	if (isTutorial) {
		if (tutorialIndex == 0) {
			if (column != NUM_COLUMN_MERGE / 2) {
				return;
			}
			else {
				tutorialIndex++;
				iconHand->stopAllActions();
				iconHand->runAction(ScaleTo::create(0.2, 0));
				spriteColumnEffect->stopAllActions();
				spriteColumnEffect->setVisible(false);
			}
		}
		else if (tutorialIndex == 1) {
			if (column != NUM_COLUMN_MERGE / 2 - 1) {
				return;
			}
			else {
				tutorialIndex++;
				iconHand->stopAllActions();
				iconHand->runAction(ScaleTo::create(0.2, 0));
				spriteColumnEffect->stopAllActions();
				spriteColumnEffect->setVisible(false);
				isTutorial = false;
			}
		}
	}
	doMoveBall(posX, posY);

	// Tim kiem index ma khoi roi xuong
	for (int i = NUM_ROW_MERGE - 1; i >= -1; i--) {
		if (i == -1 || arrayNumber[i][column]->getAvailable()) {
			if (checkEndGame(i + 1))
				return;
			ObjectNumber* number = arrayNumber[i + 1][column];
			dropToIndex(i + 1, column, MOVE_DOWN_TIME);
			spriteColumnEffect->setColor(GameUtility::getColorMerge(number->getNumber()));
			spriteColumnEffect->setVisible(true);
			spriteColumnEffect->setOpacity(100);
			spriteColumnEffect->runAction(
				FadeOut::create(MOVE_DOWN_TIME * 2.5)
			);
			spriteColumnEffect->setPosition(arrayBgColumn[column]->getPosition());
			break;
		}
	}
	// kiem tra cac khoi an sau khi roi xuong
	runAction(
		Sequence::create(
			DelayTime::create(DELAY_CHECK_DOWN_TIME),
			CallFunc::create(AX_CALLBACK_0(GroupCenter::checkEatAfterFall, this)),
			NULL
		)
	);
}

bool GroupCenter::checkEndGame(int index)
{
	if (index == NUM_ROW_MERGE) {
		// end game
		//GUIManager::getInstance().guiMerge.endGame();
		JNIUtils::sendEvent(("max_drop_" + GameUtility::toString(maxNum)).c_str(), "1");
		state = GroupState::GROUP_END;
		for (int i = 0; i < NUM_ROW_MERGE; i++)
			for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
				if (arrayNumber[i][j]->getAvailable())
					arrayNumber[i][j]->effectEndGame();
			}
		UserDefault::getInstance()->setIntegerForKey("saveScoreMerge", 0);
		UserDefault::getInstance()->flush();

		runAction(Sequence::create(
			DelayTime::create(1.0),
			CallFunc::create(AX_CALLBACK_0(GroupCenter::callbackEffectEndGame, this)),
			NULL
		));
		//JNIUtils::sendEvent("max_number", GameUtility::toString(maxNumber).c_str());
		return true;
	}
	return false;
}

void GroupCenter::callbackEffectEndGame()
{
	for (int i = 0; i < NUM_ROW_MERGE; i++)
		for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
			arrayNumber[i][j]->setVisible(false);
			arrayNumber[i][j]->stopAllActions();
			effectImage(arrayNumber[i][j]);
		}
	runAction(Sequence::create(
		DelayTime::create(1.0),
		CallFunc::create(AX_CALLBACK_0(GroupCenter::callbackEffectEndGame1, this)),
		NULL
	));
}

void GroupCenter::effectImage(ObjectNumber* ball)
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
	//image->setTexture("GuiGame/bgNumber.png");
	image->initCoin(ImageEffect::TYPE_FLOW, 0, ball->getPositionX(), ball->getPositionY());
}

void GroupCenter::callbackEffectEndGame1()
{
	GUIManager::getInstance().guiMerge->endGame();
}


void GroupCenter::dropToIndex(int index, int column, float time) {
	ObjectNumber* number = arrayNumber[index][column];
	number->resetPosition();
	number->setPositionY(moveNumber->getPositionY());
	number->moveDown(time);
	number->setNumber(moveNumber->getNumber());
	moveNumber->setVisible(false);
	pushChange(index, column);
}

/**
 * Kiem tra nhung o co the an tai mot vi tri
 */
bool GroupCenter::checkEat(int row, int column)
{
	if (arrayNumber[row][column]->isVisible() == false)
		return false;

	ObjectNumber* checkNumber = arrayNumber[row][column];
	playParticle(checkNumber->getPositionX(), checkNumber->getPositionY(), checkNumber->getNumber());
	int dX[4] = { 1, -1, 0, 0 };
	int dY[4] = { 0, 0, 1, -1 };
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int rowIndex = row + dY[i];
		int columnIndex = column + dX[i];
		ObjectNumber* number = arrayNumber[rowIndex][columnIndex];
        if (Logic::validCoordinate(rowIndex, columnIndex)) {
            AXLOGD("Available %i %i ", number->getAvailable(), number->checkSame(checkNumber->getNumber()));
        }
		if (Logic::validCoordinate(rowIndex, columnIndex)
			&& number->getAvailable()
			&& number->checkSame(checkNumber->getNumber())) {
			number->moveToEat(MOVE_EAT_TIME, checkNumber->getPosition());
			number->setLocalZOrder(0);
			count++;
		}
	}

	// Neu nhu co the an diem, kiem tra xem co khoi Block nao di chuyen xuong duoi khong sau khi da an
	// Sau khi da an thi cung kiem tra chinh khoi nay xem co the an tiep khong
	if (count > 0) {
		int add = 0;
		for (int i = 0; i < count; i++) {
			add = add + checkNumber->getNumber() + i;
		}
		GUIManager::getInstance().guiMerge->addScore(add);
		checkNumber->increaseNumber(count);
		checkNumber->setLocalZOrder(1);
		effectScore(checkNumber);
		numEat++;
		GameSound::playDrop(numEat);
		JNIUtils::vibrate(10 * numEat);
		runAction(
			Sequence::create(
				DelayTime::create(DELAY_CHECK_EAT_TIME),
				CallFunc::create(AX_CALLBACK_0(GroupCenter::callbackEat, this)),
				NULL
			)
		);
		pushChange(row, column);
		return true;
	}
	else {
		GameSound::playHit();
	}
	return false;
}

/**
 * Sau khi an diem thi check de di chuyen Number xuong ben duoi
 */
void GroupCenter::callbackEat()
{
	bool hasDrop = false;
	for (int j = 0; j < NUM_COLUMN_MERGE; j++) {
		int lastVisible = -1;
		for (int i = 0; i < NUM_ROW_MERGE; i++) {
			if (arrayNumber[i][j]->getAvailable()) {
				// chuyen khoi hien tai xuong khoi lastVisible neu khoang cach giua chung > 1
				if (i - lastVisible > 1) {
					arrayNumber[i][j]->setVisible(false);
					arrayNumber[i][j]->setAvailable(false);
					lastVisible = lastVisible + 1;

					// di chuyen khoi
					arrayNumber[lastVisible][j]->setNumber(arrayNumber[i][j]->getNumber());
					arrayNumber[lastVisible][j]->setPosition(arrayNumber[i][j]->getPosition());
					if (arrayNumber[i][j]->isEffect()) {
						arrayNumber[lastVisible][j]->playEffect();
					}
					arrayNumber[lastVisible][j]->moveDown(MOVE_DOWN_TIME);
					pushChange(lastVisible, j);
					hasDrop = true;
				}
				else {
					lastVisible = i;
				}
			}
		}
	}

	// Neu co khoi di chuyen xuong, thuc hien Check lai xem co the an diem khong, neu khong thi Gen bong moi
	if (hasDrop) {
		runAction(
			Sequence::create(
				DelayTime::create(DELAY_CHECK_DOWN_TIME),
				CallFunc::create(AX_CALLBACK_0(GroupCenter::checkEatAfterFall, this)),
				NULL
			)
		);
	}
	else {
		// neu khong thi kiem tra cac khoi thay doi ngay lap tuc
		AXLOGD("Khong co khoi di chuyen xuong");
		checkEatAfterFall();
	}
}

/**
 * Sau khi di chuyen bong xuong ben duoi thi lai Check xem co the an diem khong
 */
void GroupCenter::checkEatAfterFall() {
	bool canEat = false;
	vector <PointGame> arrayCheck;
	arrayCheck = arrayChange;
	arrayChange.clear();
	for (int i = arrayCheck.size() - 1; i >= 0; i--) {
		if (checkEat(arrayCheck[i].x, arrayCheck[i].y)) {
			canEat = true;
		}
	}
	if (canEat == false) {
		genBall();
	}
	//else {

	//	arrayChange.insert(arrayChange.begin(), arrayEat.begin(), arrayEat.end());
	//}
}


void GroupCenter::pushChange(int row, int column)
{
	bool isExist = false;
	for (int i = 0; i < arrayChange.size(); i++) {
		if (arrayChange[i].x == row && arrayChange[i].y == column) {
			isExist = true;
			break;
		}
	}
	if (isExist == false) {
		PointGame p;
		p.x = row;
		p.y = column;
		arrayChange.push_back(p);
	}
}

void GroupCenter::playParticle(float posX, float posY, int id)
{
	Vec2 globalPos = convertToWorldSpace(Vec2(posX, posY));
	globalPos.y = globalPos.y - sizeCell * 0.4;
	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);

	ParticleEffect *effect = new ParticleEffect();
	effect->create("particles/FlyUp.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
	effect->particle->setPosition(globalPos.x, globalPos.y);
	//effect->particle->setBlendAdditive(true);
    Color3B c1 = GameUtility::getColorMerge(id);
	Color4F color1 = Color4F(c1);
	/*color1.r = 1;
	color1.g = 1;
	color1.b = 1;*/
	color1.a = 1;
    Color4F color2 = Color4F(c1);
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
	//effect->particle->setTexture(TextureCache::sharedTextureCache()->addImage(("GuiGame/cell_" + GameUtility::toString(id % 10) + ".png").c_str()));

	ParticleEffect *effectSlow = new ParticleEffect();
	effectSlow->create("particles/FlyUpSlow.plist", layer);
	//ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
	effectSlow->particle->setPosition(globalPos.x, globalPos.y);
	//effectSlow->particle->setBlendAdditive(true);
	effectSlow->particle->setStartColor(color1);
	effectSlow->particle->setStartColorVar(Color4F(0, 0, 0, 0));
	effectSlow->particle->setEndColor(color2);
	effectSlow->particle->setCascadeOpacityEnabled(true);
	effectSlow->particle->setEndColorVar(Color4F(0, 0, 0, 0));
	effectSlow->particle->setAutoRemoveOnFinish(true);
	//effectSlow->particle->setTexture(TextureCache::sharedTextureCache()->addImage(("GuiGame/cell_" + GameUtility::toString(id % 10) + ".png").c_str()));

	/*Sprite* iconSmoke = getSmoke();
	iconSmoke->setScale(0);
	iconSmoke->setOpacity(0);
	iconSmoke->setPosition(posX, posY - sizeCell * 0.5);
	float rate = sizeCell * 1.6 / iconSmoke->getContentSize().width;
	iconSmoke->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ONE });
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
	iconSmoke->setColor(GameUtility::getColorTwenty(id));*/
}


Sprite* GroupCenter::getSmoke()
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

void GroupCenter::update(float delta)
{
    if (isTutorial)
        return;
    for (int i = 0; i < arrayImageEffect.size(); i++)
    {
        if (arrayImageEffect.at(i)->isVisible())
        {
            arrayImageEffect.at(i)->updateCoin(game->deltaTime);
        }
    }
    float rateSpeed = delta * 60 * 0.8;
    if (isPause == false && state == GroupState::GROUP_MOVE && moveNumber->isVisible())
    {
        moveNumber->setPositionY(moveNumber->getPositionY() + MOVE_NUMBER_SPEED * rateSpeed);
        int column = moveNumber->getPositionX() / sizeCell;
        for (int i = NUM_ROW_MERGE - 1; i >= -1; i--)
        {
            if (i == -1 || arrayNumber[i][column]->isVisible())
            {
                if (checkEndGame(i + 1))
                    return;
                float d = fabs(moveNumber->getPosition().y - arrayNumber[i + 1][column]->rootY);
                if (d < fabs(MOVE_NUMBER_SPEED * rateSpeed))
                {

                    dropToIndex(i + 1, column, 0);
                    checkEatAfterFall();
                }
                break;
            }
        }
    }
}

void GroupCenter::doTutorial()
{
	if (tutorialIndex == 0) {
		arrayNumber[0][0]->setNumber(3);
		//arrayNumber[0][1]->setNumber(3);
		arrayNumber[0][2]->setNumber(1);
		arrayNumber[0][3]->setNumber(4);
		arrayNumber[0][4]->setNumber(5);

		arrayNumber[1][0]->setNumber(4);
		arrayNumber[1][3]->setNumber(3);
		arrayNumber[1][4]->setNumber(4);

		arrayNumber[2][0]->setNumber(5);
		arrayNumber[2][4]->setNumber(1);
	}
	iconHand->stopAllActions();
	iconHand->setVisible(true);
	spriteColumnEffect->setVisible(true);
	spriteColumnEffect->stopAllActions();
	spriteColumnEffect->setColor(Color3B(200, 200, 200));
	switch (tutorialIndex)
	{
	case 0:
		iconHand->setPosition(arrayNumber[3][NUM_COLUMN_MERGE / 2]->getPosition());
		spriteColumnEffect->setPositionX(arrayNumber[3][NUM_COLUMN_MERGE / 2]->getPositionX());
		break;
	case 1:
		iconHand->setPosition(arrayNumber[3][NUM_COLUMN_MERGE / 2 - 1]->getPosition());
		spriteColumnEffect->setPositionX(arrayNumber[3][NUM_COLUMN_MERGE / 2 - 1]->getPositionX());
		break;
	default:
		break;
	}
	iconHand->setOpacity(0);
	iconHand->runAction(
		RepeatForever::create(
			Sequence::create(
				FadeIn::create(0.2),
				ScaleTo::create(0.1, 0.8),
				ScaleTo::create(0.1, 1.0),
				FadeOut::create(0.2),
				DelayTime::create(0.5),
				NULL
			)
		)
	);
	spriteColumnEffect->runAction(
		RepeatForever::create(
			Sequence::create(
				FadeTo::create(0.3, 150),
				FadeOut::create(0.5),
				NULL
			)
		)
	);
}

void GroupCenter::resumeGame()
{
	isPause = false;
}

void GroupCenter::effectScore(ObjectNumber* number)
{
	Text* label = NULL;
	for (int i = 0; i < arrayLabel.size(); i++) {
		if (!arrayLabel.at(i)->isVisible()) {
			label = arrayLabel.at(i);
			break;
		}
	}
	if (label == NULL) {
		label = Text::create("SCORE", "fonts/tahomabd.ttf", 35);
		addChild(label);
		//label->enableOutline(Color4B(115, 37, 31, 255), 1);
		arrayLabel.push_back(label);
	}
	label->setVisible(true);
	label->setOpacity(0);
	label->setLocalZOrder(2);
	label->setPosition(number->getPosition());
	label->setString(GameUtility::toString(number->getNumber()));
	label->runAction(
		Sequence::create(
			Spawn::create(
				FadeTo::create(0.3, 180),
				EaseBackOut::create(MoveBy::create(0.5, Vec2(0, 70))),
				NULL
			),
			DelayTime::create(0.5),
			FadeOut::create(0.5),
			NULL
		)
	);
}

