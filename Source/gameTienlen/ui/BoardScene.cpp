#include "BoardScene.h"
#include "core/utils/StringUtility.h"
#include "../logic/GameLogic.h"
#include "core/gui/SceneMgr.h"
#include "../InGameMgr.h"
#include "OtherUI.h"
#include "SelfUI.h"
#include "core/utils/TienlenGameSound.h"
#include "LoadingScene.h"
#include "Game/Utility/JNIUtils.h"
#include "LobbyScene.h"
#include "GUILevel.h"
#include "GUIHelp.h"


using namespace ax::ui;
#define BOARD_SCENE_BTN_JACK_POT 0
#define BOARD_SCENE_BTN_MORE 1
#define BOARD_SCENE_BTN_CAMERA 2
#define BOARD_SCENE_BTN_QUIT 3
#define BOARD_SCENE_BTN_SOUND 4
#define BOARD_SCENE_BTN_HELP 5
#define BOARD_SCENE_BTN_START 6
#define BOARD_SCENE_BTN_EMO 7
#define BOARD_SCENE_BTN_LANGUAGE 8
#define BOARD_SCENE_BTN_TOP 9
#define BOARD_SCENE_BTN_GAME 10

BoardScene::BoardScene()
{
}
BoardScene::~BoardScene()
{

}

void BoardScene::onEnter()
{
	BaseLayer::onEnter();
}


bool BoardScene::init()
{
	BaseLayer::init();
	initWithBinaryFile("Board/BoardScene.csb");
	//setKeyboardEnabled(true);
	return true;
}


void BoardScene::initGUI()
{
	srand((unsigned int)time(NULL));
	Size size = Director::getInstance()->getVisibleSize();

	bgBoard = (ImageView *)getControl("bgBoard");

	Node *pTopLeft = getControl("pTopLeft");
	Node *pTopRight = getControl("pTopRight");
	pTopLeft->setLocalZOrder(100);

	Node * bgInfo = getControl("bgInfo", pTopLeft);
	labelRoom = (Text *)getControl("room", bgInfo);
	labelBet = (Text *)getControl("bet", bgInfo);
	//adult->setVisible(gamedata->enableAdult);
	

	// network state
	btnBack = customButton("btnBack", BOARD_SCENE_BTN_QUIT, pTopLeft);
	btnSound = customButton("btnSound", BOARD_SCENE_BTN_SOUND, pTopRight);
	btnLanguage = customButton("btnLanguage", BOARD_SCENE_BTN_LANGUAGE, pTopRight);
	btnGame = customButton("btnGame", BOARD_SCENE_BTN_GAME, pTopLeft);
	btnGame->setVisible(false);
	//btnTop = customButton("btnTop", BOARD_SCENE_BTN_TOP, pTopRight);
	Button* btn = customButton("btnHelp", BOARD_SCENE_BTN_HELP, pTopRight);
	

	btnStart = customButton("start", BOARD_SCENE_BTN_START, _layout, true);

	Node *bType = getControl("typeBoard");
	groupCard = (ImageView *)getControl("boxCard");

	// img van dau se bat dau sau
	clockCountDown = new ClockCountDown();
	this->addChild(clockCountDown);
	clockCountDown->setVisible(false);

	pEffect = getControl("pEffect");
	pGroup = getControl("pType", pEffect);
	pLight = getControl("pLight", pEffect);
	pCard = getControl("pCard", pEffect);
	pJackpot = getControl("pJackpot", pEffect);
	// Layout Effect Card nam duoi UI cua minh va nam tren UI cua nguoi khac
	pEffect->setLocalZOrder(3);
	pGroup->setLocalZOrder(100);
	//pEffect->setLocalZOrder(100);

	pEffectTop = getControl("pEffectTop");
	pEffectTop->setLocalZOrder(5);

	pEffectAll = Node::create();
	_layout->addChild(pEffectAll);
	pEffectAll->setLocalZOrder(100);

	resultGroup = new ResultGroup();
	this->addChild(resultGroup);
	resultGroup->setPosition(size.width * 0.5, size.height * 0.65);
	resultGroup->setScale(0.8);
	resultGroup->setLocalZOrder(10);

	manager = EffectManager::create(Size(size.width * 0.5, size.height * 0.5));
	Effect* effect = Effect::create("flame.efk", 40);
	emitter = EffectEmitter::create(manager);
	emitter->setEffect(effect);
	emitter->setPlayOnEnter(false);
	emitter->setPosition(size.width * 0.25, size.height * 0.5 - 100);
	addChild(emitter, 100);
	emitter->setRemoveOnStop(false);
	emitter->stop();

	Effect* effect1 = Effect::create("lightExplore.efk", 20);
	lightExplore = EffectEmitter::create(manager);
	lightExplore->setEffect(effect1);
	lightExplore->setPlayOnEnter(false);
	lightExplore->setPosition(size.width * 0.25, size.height * 0.25 - 50);
	addChild(lightExplore, 100);
	lightExplore->setRemoveOnStop(false);
	lightExplore->stop();

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [this](Touch* touch, ax::Event* event) {
		//((ChatPanelGUI*)event->getCurrentTarget())->onTouchBoard(touch);
		AXLOGD("TOUCH VO DAY NE");
		onTouchBoard();
		return true; // if you are consuming it
	}; ;
	listener1->onTouchMoved = [this](Touch* touch, ax::Event* event) {
	};

	// trigger when you let up
	listener1->onTouchEnded = [this](Touch* touch, ax::Event* event) {
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, ax::Event* event) {
		AXLOGD("DU MA NO CHU %i ", (int)keyCode);
		char buf[100] = { 0 };

		sprintf(buf, "Key %d was pressed!", (int)keyCode);
		//	auto label = static_cast<BoardScene*>(event->getCurrentTarget());
		int code = (int)keyCode;
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		vector <int> arrayId;
		vector <int> arrayRandom;
		for (int i = 0; i < 52; i++) {
			arrayRandom.push_back(i);
		}
		for (int i = 0; i < NUM_CARD; i++) {
			int r = floor(AXRANDOM_0_1() * arrayRandom.size());
			arrayId.push_back(arrayRandom[r]);
			arrayRandom.erase(arrayRandom.begin() + r);
		}
		
		GameLogic::getInstance()->myChair = 0;

		if (keyCode == EventKeyboard::KeyCode::KEY_1) {
			//GameLogic::getInstance()->genStartGame();
			gui->playEffectCard(NULL, EG_SUPER, Vec2(200, 200));
			gui->playEffectCard(NULL, EG_BA_CON_HAI, Vec2(200, 200));
			gui->playEffectCard(NULL, EG_TU_QUY, Vec2(200, 200));
			//GameLogic::getInstance()->autoPlay();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_2) {
			GameLogic::getInstance()->autoPlay();
			//gui->arrayPlayer[0]->changeTurn(20);
			//vector <char> ar = GameLogic::getInstance()->arrayPlayer[0]->getAutoPlayCard();
			//GameLogic::getInstance()->playCard(0, ar);
			//gui->playCard(ar, 0, EG_ONECARD);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_3) {

			GameLogic::getInstance()->endGame();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_4) {
			//gui->arrayPlayer[0]->showCancel(true);
			GameLogic::getInstance()->turnId++;
			if (GameLogic::getInstance()->turnId >= 4) {
				GameLogic::getInstance()->turnId = 0;
			}

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_5) {
			gui->arrayPlayer[1]->effectResult(1);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_6) {
			arrayId.at(0) = 50;
			arrayId.at(1) = 51;
			GameLogic::getInstance()->arrayPlayer[0]->setArrayCard(arrayId);
			gui->arrayPlayer[0]->endDealCard();

			vector <int> ar;
			ar.push_back(50);
			ar.push_back(51);
			gui->playCard(ar, 0, EG_DOI_HAI);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_7) {
			//gui->jackpot(100000);
			//gui->dealStartGame();
			//GameLogic::getInstance()->rate = 3;
			//gui->fineMoney(30000, 0, 1);
			gui->arrayPlayer[0]->effectGold(30000);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_8) {
			char* ar = new char(1);
			ar[0] = 3;
			ar[1] = 33;
			ar[2] = 32;
			ar[3] = 45;
			ar[4] = 49;
			ar[5] = 50;
			ar[6] = 51;
			//GameLogic::getInstance()->endCard(2, ar, 7);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_9) {
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, pJackpot);
	initPlayer();

	cardEndGroup = new CardEndGroup();
	this->_layout->addChild(cardEndGroup);
	cardEndGroup->setVisible(false);
	cardEndGroup->setPosition(size.width * 0.5, size.height * 0.5);
	cardEndGroup->setLocalZOrder(100);
    loadBtnSound();
	loadBtnLanguage();

}

void BoardScene::initPlayer()
{
	for (int i = NUM_PLAYER - 1; i >= 0; i--) {
		if (i != 0)
			arrayPlayer[i] = new OtherUI(i);
		else
			arrayPlayer[i] = new SelfUI();
		_layout->addChild(arrayPlayer[i]);
        
		arrayPlayer[i]->setPosition(getControl("p" + to_string(i))->getPosition());
		
	}
	arrayPlayer[0]->setLocalZOrder(4);
	arrayPlayer[1]->setLocalZOrder(2);
	arrayPlayer[3]->setLocalZOrder(2);
	arrayPlayer[2]->setLocalZOrder(1);
}

void BoardScene::onEnterFinish()
{
	//TODO
	// stop music
	///audioEngine.stopMusic();
	
	Size size = Director::getInstance()->getVisibleSize();
	pEffectAll->removeAllChildren();
	showMore = false;
	showMoreButton();
//	updateJackpot();
	//btnStart->setVisible(true);
	scheduleUpdate();
	//scheduleUpdate();
	GameLogic::getInstance()->timeAuto = -1;
	/*if (gameMgr->showedTop == false) {
		btnTop->stopAllActions();
		btnTop->runAction(RepeatForever::create(
			Sequence::create(
				ScaleTo::create(0.2, 1.2),
				ScaleTo::create(0.2, 1.0),
				NULL
			)
		));
	}*/
    joinRoomSuccess();
}

void BoardScene::update(float delta)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->update(delta);
	}

	if (GameLogic::getInstance()->timeAuto >= 0) {
		GameLogic::getInstance()->timeAuto = GameLogic::getInstance()->timeAuto - delta;
		if (GameLogic::getInstance()->timeAuto <= 0) {
			switch (autoState)
			{
			case AUTO_START_STATE:

				break;
			case CHECK_SUDDEN_WIN_STATE:
				GameLogic::getInstance()->checkAutoSuddenWin();
				break;
			case AUTO_PLAY_CARD:
				GameLogic::getInstance()->autoPlay();
				break;
			case AUTO_PASS: {
				if (GameLogic::getInstance()->isNewTurn) {
					GameLogic::getInstance()->autoPlay();
				}
				else {
					vector<char> arr;
					GameLogic::getInstance()->myPlay(arr);
				}
				
				break;
			}
			case PRE_END_GAME_STATE:
				GameLogic::getInstance()->caculateEndGame();
				break;
			case END_GAME_STATE:
				GameLogic::getInstance()->endGame();
				break;
			case REWARD_FAIL_STATE:
			{
				string reason = LocalizedString::to("NOT_FINISH_REWARD");
				sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {

				});
				JNIUtils::sendEvent("get_reward_fail", "1");
				break;
			}
			case REWARD_SUCCESS_STATE:
			{
				string reason = LocalizedString::to("RECEIVE_NUM");
				reason = StringUtility::replaceAll(reason, "@gold", "30.000");
				sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {
					GameLogic::getInstance()->arrayPlayer[0]->Gold(30000);
					BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
                    if (gui)
					    gui->updateUserMoney(0);
				});
				JNIUtils::sendEvent("get_reward_suess", "1");
				break;
			}
			default:
				break;
			}
		}
	}
	manager->update(delta);
	cardEndGroup->update(delta);

	for (int i = 0; i < arrayCardEffect.size(); i++) {
		arrayCardEffect[i]->update();
	}
	for (int i = 0; i < arrayCardEffectTop.size(); i++) {
		arrayCardEffectTop[i]->update();
	}
}

void BoardScene::newGame()
{
    newGame1();
    newGame2();
    newGame3();
    newGame4();
	//myPlayer->newGame();
	
}

void BoardScene::newGame1()
{
    cardEndGroup->setVisible(false);
    groupCard->setVisible(false);
    btnStart->setVisible(false);
}
void BoardScene::newGame2() {
    for (int i = 0; i < NUM_PLAYER; i++)
    {
        arrayPlayer[i]->newGame();
    }
    for (int i = 0; i < (int)arrayCardEffect.size(); i++)
    {
        arrayCardEffect.at(i)->setVisible(false);
    }
    for (int i = 0; i < (int)arrayCardEffectTop.size(); i++)
    {
        arrayCardEffectTop.at(i)->setVisible(false);
    }
}
void BoardScene::newGame3() {
    arrayCardOnBoard.clear();
    pEffectAll->removeAllChildren();
    clockCountDown->setVisible(false);
}
void BoardScene::newGame4() {
    btnStart->setVisible(true);
    resultGroup->setVisible(false);
}

void BoardScene::joinRoomSuccess()
{
	//return;
	// cap nhat nguoi choi
	newGame();
	labelRoom->setString(StringUtility::pointNumber(1000));
	for (int i = 0; i < NUM_PLAYER; i++) {
		PlayerUI *p = arrayPlayer[GameLogic::getInstance()->getChair(i)];
		PlayerInfo *pInfo = GameLogic::getInstance()->arrayPlayer[i];
		if (pInfo->Status() > 0) {
			p->setInfo(pInfo);
			p->setVisible(true);
		}
		else {
			p->setVisible(false);
		}
	}
	updateRoomOwner();
	//updateWaitOther();
	if (gameMgr->useMove == false && gameMgr->winCount > 2 && AXRANDOM_0_1() < 0.3) {
		sceneMgr->openGUI(GUIHelp::className, 205, 205);
	}
}

void BoardScene::setViewInfo()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		if (i != 0) {
			arrayPlayer[i]->updateCard();
		}
	}
}

void BoardScene::updateRoomOwner()
{
	char owner = GameLogic::getInstance()->roomOwner;
	owner = GameLogic::getInstance()->getChair(owner);
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->setRoomOwner(i == owner);
	}
	//myPlayer->setRoomOwner(owner == 0);
}

void BoardScene::updateWaitOther()
{
	if (GameLogic::getInstance()->getGameState() == GameState::GAME_WAITING) {

	}
	else {
	}
}

void BoardScene::newUserJoinRoom(char chair, PlayerInfo *info)
{
	arrayPlayer[chair]->setVisible(true);
	arrayPlayer[chair]->newGame();
	arrayPlayer[chair]->setInfo(info);
}

void BoardScene::userLeave(char chair)
{
	arrayPlayer[chair]->setVisible(false);
}

void BoardScene::autoStart(int time, char type) {
	if (type == 2) {
		//clockCountDown->setPause(false);
		//clockCountDown->setTime(time);
		if (GameLogic::getInstance()->isShowBtnStart()) {
			btnStart->setVisible(true);
		}
	}
	else {
		//clockCountDown->setPause(true);
		btnStart->setVisible(false);
		timeWaitOther = -1;
	}
}

void BoardScene::notifyStart()
{
	btnStart->setVisible(false);
	//clockCountDown->setPause(false);
	dealStartGame();
	TienlenGameSound::startGame();
}

void BoardScene::dealStartGame()
{
	//groupCard->setVisible(true);
	int count = 0;
	float timeDelay;
	float timeDeal = 0.02f;
	for (int i = 0; i < NUM_CARD; i++) {
		for (int j = 0; j < NUM_PLAYER; j++) {
			PlayerInfo* player = GameLogic::getInstance()->arrayPlayer[GameLogic::getInstance()->getChairInServer(j)];
			if (player->isPlaying() && i < player->arrayCard.size()) {
				timeDelay = timeDeal * count;
				count++;
				callbackDealCard(i, j, timeDelay);
			}
		}
	}

	//for (int i = 0; i < NUM_PLAYER; i++) {
	//	PlayerInfo* player = GameLogic::getInstance()->arrayPlayer[GameLogic::getInstance()->getChairInServer(i)];
	//	if (player->isPlaying()) {
	//		for (int j = 0; j < NUM_PLAYER; j++) {

	//		}
	//	}
	//	for (int j = 0; j < NUM_PLAYER; j++) {
	//		
	//		if (player->isPlaying()) {
	//			timeDelay = timeDeal * count;
	//			count++;
	//			callbackDealCard(i, j, timeDelay);
	//		}
	//	}
	//}
	timeDelay = timeDeal * count + 0.8;
	//timeDelay = 10;

    runAction(Sequence::create(DelayTime::create(timeDelay + 1),
                                CallFuncN::create(AX_CALLBACK_0(BoardScene::callbackEndDealCard, this)), NULL));
	TienlenGameSound::playSoundChiaBai();
}

void BoardScene::callbackDealCard(int num, int indexPlayer, float delayTime)
{
	Size size = Director::getInstance()->getVisibleSize();
	CardEffect *card = getCardEffect(true);
	
	Vec2 posStart = Vec2(pEffectTop->getContentSize().width * 0.5 + AXRANDOM_0_1() * 5 - 10, pEffectTop->getContentSize().height * 0.5 + AXRANDOM_0_1() * 8 - 16);
	double scale = arrayPlayer[indexPlayer]->getCardSize().width / card->getContentSize().width;
	Vec2 posEnd = arrayPlayer[indexPlayer]->getCardPos(num);
	posEnd = pEffectTop->convertToNodeSpace(posEnd);
	//card->setIdCard(3);
	card->setInfoCard(num, indexPlayer);
	//card->setOpacity(100);
	card->setListener([this](int index, int indexPlayer) {
		PlayerInfo* info = GameLogic::getInstance()->getInfo(indexPlayer);
		if (indexPlayer != 0)
			arrayPlayer[indexPlayer]->updateDealCard(index);
		
	});
	if (indexPlayer == 0) {
		PlayerInfo* info = GameLogic::getInstance()->getInfo(indexPlayer);
		card->setIdCard(info->arrayCard[num]);
		card->moveToOpen(posStart, posEnd, 0.5, scale, delayTime);
		/*card->runAction(
			Sequence::create(
				DelayTime::create(delayTime),
				Spawn::create(
					EaseExponentialOut::create(MoveTo::create(0.3, pos)),
					ScaleTo::create(0.3f, scale),
					NULL
				),
				Hide::create(),
				CallFuncN::create(AX_CALLBACK_1(BoardScene::callbackDealCard1, this, num, indexPlayer)),
				NULL
			)
		);*/
	}
	else {
		card->moveTo(posStart, posEnd, 0.5, scale, delayTime);
	}
}

void BoardScene::callbackDealCard1(Node* sender, int num, int indexPlayer)
{
	/*PlayerInfo* info = GameLogic::getInstance()->getInfo(indexPlayer);
	if (indexPlayer != 0)
		arrayPlayer[indexPlayer]->updateDealCard(num);*/
}

void BoardScene::callbackEndDealCard()
{
	for (int i = 0; i < arrayCardEffectTop.size(); i++)
		arrayCardEffectTop[i]->setVisible(false);
	groupCard->setVisible(false);
	GameLogic::getInstance()->setGameState(GameState::GAME_PLAYING);
	for (int i = 0; i < NUM_PLAYER; i++) {
	//	GameLogic::getInstance()->getInfo(i)->NumCard(NUM_CARD);
		arrayPlayer[i]->endDealCard();
	}
	updateMyCard();

	// kiem tra sudden Win
	autoState = CHECK_SUDDEN_WIN_STATE;
	GameLogic::getInstance()->timeAuto = 2;
}

void BoardScene::updateMyCard()
{
	arrayPlayer[0]->endDealCard();
}

void BoardScene::changeTurn(bool isNewTurn, char playerTurn, int turnTime)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->stopTurn();
	}
	if (isNewTurn) {
		endTurnCard();
	}
	else {
		if (playerTurn != 0) {
			if (GameLogic::getInstance()->CanPlayWithoutTurn()) {
				// co the danh khong can luot
				((SelfUI*)arrayPlayer[0])->showAutoTurn();
			}
			else {
				((SelfUI*)arrayPlayer[0])->endTurnCard();
			}
		}
	}
	arrayPlayer[playerTurn]->changeTurn(turnTime);
	if (playerTurn == 0) {
        //JNIUtils::vibrate(5);
		TienlenGameSound::playChangeTurn();
	}
}

void BoardScene::endTurnCard()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->showCancel(false);
	}
	for (int i = 0; i < (int)arrayCardOnBoard.size(); i++) {
		arrayCardOnBoard.at(i)->setIdCard(52);
		arrayCardOnBoard.at(i)->setDark(true);
	}
	arrayCardOnBoard.clear();
}

void BoardScene::playCard(vector<int> arrayId, char chair, char typeGroup, bool isEnd)
{
	for (int i = 0; i < (int)arrayCardOnBoard.size(); i++) {
		arrayCardOnBoard.at(i)->setDark(true);
		arrayCardOnBoard.at(i)->setLocalZOrder(0);
	}
	int num = arrayId.size();
	bool isEffect = GameLogic::getInstance()->checkEffectPlayCard(typeGroup);
	Size size = Director::getInstance()->getVisibleSize();
	float widthCard = 70;
	float padCard = widthCard * 0.4;
	float sum = num * padCard + widthCard;
	float startX = pCard->getContentSize().width * (0.7 - AXRANDOM_0_1() * 0.4) - sum * 0.5;
	float startY = pCard->getContentSize().height * (0.7 - AXRANDOM_0_1() * 0.2);
	if (typeGroup == TOI_TRANG) {
		startX = pCard->getContentSize().width * 0.5 - sum * 0.5;
		startY = pCard->getContentSize().height * 0.5;
	}
	if (isEffect) {
		widthCard = 90;
	}
    float widthStartCard = 100;
    if (chair >= 0)
        widthStartCard = arrayPlayer[chair]->getCardSize().width;
	
	float timeDelay = 0.3;
	float sumWidth = widthCard * num + padCard * (num - 1);
	vector<Vec2> arrPos;
	float scaleStart;
	// dua quan bai ra ban
	for (int i = 0; i < num; i++) {
		CardImage* card = getCardEffect(false);
		arrayCardOnBoard.push_back(card);
		card->setIdCard(arrayId[i]);
		//card->setLocalZOrder(i);
		Vec2 p = Vec2(0, 0);
		if (chair >= 0)
			p = arrayPlayer[chair]->getCardPosById(arrayId[i]);

		float scale = widthCard / card->getContentSize().width;
		float posX = startX + widthCard * 0.5 + padCard * i;

		if (isEnd) {
			arrPos.push_back(p);
			scaleStart = widthStartCard / card->getContentSize().width;
			card->setOpacity(0);
		}
		else {
			p = pCard->convertToNodeSpace(p);
			CardImage* card1 = getCardEffect(true);
			card1->setIdCard(arrayId[i]);
			card1->setLocalZOrder(i);
			if (isEffect) {
                JNIUtils::vibrate(10);
				// hien thi effect rieng cho bo bai to
				//card1->setPosition(posX, startY);
				card1->setPosition(p);
				card1->setScale(3);
				card1->setOpacity(0);
				card1->runAction(
					Sequence::create(
						DelayTime::create(0.05 * i),
						Spawn::create(
							FadeIn::create(0.3f),
							ScaleTo::create(0.3f, scale),
							MoveTo::create(0.3, Vec2(posX, startY)),
							NULL
						),
						DelayTime::create(1.5f),
						Hide::create(),
						NULL
					)
				);

			}
			else {
				// play effect bay tu nguoi choi ra ban choi
				float rootScale = widthStartCard / card1->getContentSize().width;
				card1->setScale(rootScale);
				card1->setPosition(p);
				card1->runAction(
					Sequence::create(
						DelayTime::create(0.05 * i),
						Spawn::create(
							MoveTo::create(0.3f, Vec2(posX, startY)),
							ScaleTo::create(0.1f, card1->getScale() * 1.3),
							NULL
						),
						ScaleTo::create(0.2f, scale),
						Hide::create(),
						NULL
					)
				);
			}
			// hien thi luon card nam o vi tri giua ban choi
			card->setOpacity(0);
			card->setPosition(Vec2(posX, startY));
			card->setScale(scale);
			card->runAction(Sequence::create(DelayTime::create(timeDelay + 0.05 * i), FadeTo::create(0, 255), NULL));
		}
	}
	if (isEnd) {
		cardEndGroup->showCardEnd(arrayId, arrPos, scaleStart);
        for (int i = 0; i < arrayCardEffect.size(); i++) {
            CardEffect* card = arrayCardEffect.at(i);
            if (card->isVisible() == false)
                continue;
            float scale     = card->getScale();
            int signalRotate = AXRANDOM_0_1() > 0.5 ? 1 : -1;
            int signalX      = AXRANDOM_0_1() > 0.5 ? 1 : -1;
            int signalY      = AXRANDOM_0_1() > 0.5 ? 1 : -1;
            card->runAction(
                Sequence::create(
                    DelayTime::create(1.5),
                    Spawn::create(
                        ScaleTo::create(0.2, scale * 1.2),
                        RotateBy::create(0.2, AXRANDOM_0_1() * 10 * signalRotate),
                        MoveBy::create(0.2, Vec2(AXRANDOM_0_1() * 5 * signalX, AXRANDOM_0_1() * 5 * signalY)),
                        NULL
                    ),
                    Spawn::create(
                        EaseBounceOut::create(ScaleTo::create(0.5 + AXRANDOM_0_1() * 0.2, scale)),
                        RotateBy::create(0.2, AXRANDOM_0_1() * 10 * signalRotate),
                        MoveBy::create(0.2, Vec2(AXRANDOM_0_1() * 5 * signalX, AXRANDOM_0_1() * 5 * signalY)),
                        NULL
                    ),
                    NULL
                )
            );
            AXLOGD("RUN HERE ==========");
        }

		this->_layout->runAction(
			Sequence::create(
				DelayTime::create(0.3),
				Repeat::create(
					Sequence::create(
						MoveBy::create(0.02, Vec2(10, 0)),
						MoveBy::create(0.04, Vec2(-20, 0)),
						MoveBy::create(0.02, Vec2(10, 0)),
						NULL
					), 3
				),
				DelayTime::create(1.0),
                CallFuncN::create(AX_CALLBACK_1(BoardScene::callbackVibrate, this, 100)),
				ScaleTo::create(0.1, 1.1),
				EaseBounceOut::create(ScaleTo::create(0.2, 1.0)),
				NULL
			)
		);
	}

	this->typeGroup = typeGroup;
	
	if (isEffect) {
		runAction(Sequence::create(DelayTime::create(0.35),
                                       CallFuncN::create(AX_CALLBACK_1(BoardScene::callbackVibrate, this, 50)),
                                       DelayTime::create(0.15),
                                       CallFuncN::create(AX_CALLBACK_1(BoardScene::playEffectCard, this, typeGroup,
                                                                       Vec2(startX + sum * 0.5, startY - 40))),
                                       NULL)
		);
	}

	// Update lai card cua Player
	if (chair >= 0)
		arrayPlayer[chair]->updateCard();
	if (isEnd == false)
		TienlenGameSound::playCard();
}

void BoardScene::callbackVibrate(Node* sender, int miliseconds) {
    JNIUtils::vibrate(miliseconds);
}

void BoardScene::playEffectCard(Node* sender, char typeGroup, Vec2 pos)
{
	TienlenGameSound::playChatGroupCard();
	vector <Sprite*> arrayImage;
	if (gameMgr->isIndo == false) {
		switch (typeGroup) {
		case EG_BA_CON_HAI:
			arrayImage.push_back(Sprite::create("Game/textViet/ba.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/con1.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/hai.png"));
			//	TienlenEffectManager.effectString(TienlenEffectManager.BA_CON_HAI, MyPortal.game.loginScreen.tienlenEffectLayer);
			break;
		case EG_DOI_HAI:
			arrayImage.push_back(Sprite::create("Game/textViet/doi.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/hai.png"));
			break;
		case EG_SUPER:
			arrayImage.push_back(Sprite::create("Game/textViet/bon.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/doi.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/thong.png"));
			break;
		case EG_ULTRA:
			arrayImage.push_back(Sprite::create("Game/textViet/bon.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/doi.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/thong.png"));
			break;
		case EG_BIGGER:
			arrayImage.push_back(Sprite::create("Game/textViet/ba.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/doi.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/thong.png"));
			break;
		case EG_TU_QUY:
			arrayImage.push_back(Sprite::create("Game/textViet/tu.png"));
			arrayImage.push_back(Sprite::create("Game/textViet/quy.png"));
			break;
		}
	}
	else {
		switch (typeGroup) {
		case EG_BA_CON_HAI:
			arrayImage.push_back(Sprite::create("Game/textEffect/triplet.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/of.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/2s.png"));
			break;
		case EG_DOI_HAI:
			arrayImage.push_back(Sprite::create("Game/textEffect/pair.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/of.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/2s.png"));
			break;
		case EG_SUPER:
			arrayImage.push_back(Sprite::create("Game/textEffect/double.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/sequence.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/of.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/bon.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/pairs.png"));
			break;
		case EG_ULTRA:
			arrayImage.push_back(Sprite::create("Game/textEffect/nam.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/doi.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/thong.png"));
			break;
		case EG_BIGGER:
			arrayImage.push_back(Sprite::create("Game/textEffect/double.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/sequence.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/of.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/ba.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/pairs.png"));
			break;
		case EG_TU_QUY:
			arrayImage.push_back(Sprite::create("Game/textEffect/four.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/of.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/a.png"));
			arrayImage.push_back(Sprite::create("Game/textEffect/kind.png"));
			break;
		}
	}
	

	if (arrayImage.size() > 0) {
		float pad = 10;
		float sumWidth = 0;
		for (int i = 0; i < arrayImage.size(); i++) {
			sumWidth = sumWidth + arrayImage.at(i)->getContentSize().width;
			if (i != 0)
				sumWidth = sumWidth + pad;
		}
		float startX = pos.x - sumWidth * 0.5;

		Sprite* bgEffect = Sprite::create("Game/textEffect/bgEffect.png");
		pEffectTop->addChild(bgEffect, 10);
		bgEffect->setPosition(pos);
		float scaleX = sumWidth * 1.5 / bgEffect->getContentSize().width;
		bgEffect->setScaleX(0);
		bgEffect->setOpacity(0);
		bgEffect->runAction(
			Sequence::create(
				DelayTime::create(0.3),
				Spawn::create(
					FadeIn::create(0.5),
					EaseBounceOut::create(ScaleTo::create(0.5, scaleX, 1)),
					NULL
				),
				DelayTime::create(1.5),
				FadeOut::create(0.5),
				RemoveSelf::create(),
				NULL
			)
		);

		for (int i = 0; i < arrayImage.size(); i++) {
			pEffectTop->addChild(arrayImage[i], 10);
			if (i == 0) {
				arrayImage[i]->setPosition(startX + arrayImage[i]->getContentSize().width * 0.5, pos.y);
			}
			else {
				arrayImage[i]->setPosition(arrayImage[i - 1]->getPositionX() + arrayImage[i - 1]->getContentSize().width * 0.5 + pad + arrayImage[i]->getContentSize().width * 0.5, pos.y);
			}
			
			arrayImage[i]->setScale(5);
			arrayImage[i]->setOpacity(0);
			arrayImage[i]->runAction(
				Sequence::create(
					DelayTime::create(0.1 * i),
					Spawn::create(
						EaseBounceOut::create(ScaleTo::create(0.5, 1)),
						FadeIn::create(0.5),
						NULL
					),
					DelayTime::create(1.5),
					FadeOut::create(0.5),
					RemoveSelf::create(),
					NULL
				)
			);
		}
	}
}
//
//void BoardScene::playEffectCard(Node* sender, char typeGroup, Vec2 pos)
//{
//	switch (typeGroup)
//	{
//	case EG_BA_CON_HAI:
//	case EG_DOI_HAI:
//		if (GameLogic::getInstance()->isNewTurn) {
//			//TienlenGameSound::playDanhHai();
//		}
//		else {
//			//TienlenGameSound::playChatHai();
//		}
//		break;
//	default:
//		if (GameLogic::getInstance()->isNewTurn) {
//			//TienlenGameSound::playDanhBo();
//		}
//		else {
//			//TienlenGameSound::playChatBo();
//		}
//		break;
//	}
//	string resource = GameLogic::getInstance()->getResourcePlayCard(typeGroup);
//	DBArmatureNode *effIcon = DBFactory::getInstance()->buildArmatureNode("GroupCard");
//	if (effIcon) {
//		pGroup->addChild(effIcon);
//		//effIcon->setScale(_scale);
//		effIcon->getAnimation()->gotoAndPlay(resource.c_str(), -1, -1, 1);
//		effIcon->setPosition(pos.x, pos.y + 100);
//		effIcon->runAction(
//			Sequence::create(
//				DelayTime::create(2),
//				RemoveSelf::create(),
//				NULL
//			)
//		);
//	}
//
//	DBArmatureNode *effLight = DBFactory::getInstance()->buildArmatureNode("Light_bobai");
//	if (effLight) {
//		pLight->addChild(effLight);
//		//effIcon->setScale(_scale);
//		effLight->getAnimation()->gotoAndPlay("1", -1, -1, -1);
//		effLight->setPosition(pos.x, pos.y);
//		effLight->runAction(
//			Sequence::create(
//				DelayTime::create(2),
//				RemoveSelf::create(),
//				NULL
//			)
//		);
//	}
//}

void BoardScene::pass(char chair)
{
	arrayPlayer[chair]->showCancel(true);
	TienlenGameSound::playBoLuot();
}

void BoardScene::notifyGameResult(vector<double> moneys, vector<char> ranks, vector<bool> isCongs)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->stopTurn();
	}
	if (GameLogic::getInstance()->isSuddenWin()) {
		//	effectSuddenWin();
		vector <int> arrayId = GameLogic::getInstance()->getSuddenWinCard();
		char chair = GameLogic::getInstance()->getChair(GameLogic::getInstance()->chairSuddenWin);
		//playCard(arrayId, chair, TOI_TRANG);
        if (chair < 0 || chair >= 4)
        {
            GameLogic::getInstance()->endGame();
            return;
        }
		moveCardToiTrang(arrayId, chair);
		emitter->play(1);
		runAction(
			Sequence::create(
				DelayTime::create(1.0),
				CallFuncN::create(AX_CALLBACK_1(BoardScene::callbackToiTrang, this)),
				NULL
			)
		);
	}

	for (int i = 0; i < NUM_PLAYER; i++) {
		if (ranks[i] >= 0) {
			int convertChair = GameLogic::getInstance()->getChair(i);
			arrayPlayer[convertChair]->getRank(ranks[i], isCongs.at(i));
			arrayPlayer[convertChair]->effectGold(moneys.at(i));
			arrayPlayer[convertChair]->updateMoney();
			if (convertChair == 0) {
				if (moneys[i] > 0) {
					JNIUtils::sendEvent("win", "1");
					TienlenGameSound::playSounds_win();
					resultGroup->showMauBinh(RANK_NHAT);
				}
				else {
					JNIUtils::sendEvent("lose", "1");
					TienlenGameSound::playSounds_lose();
				}
				//TienlenGameSound::musicWin();
			}
			else {
				//TienlenGameSound::musicLose();
			}
		}
	}
}


void BoardScene::callbackToiTrang(Node* sender)
{
	char chair = GameLogic::getInstance()->getChair(GameLogic::getInstance()->chairSuddenWin);
	if (gameMgr->canPlayEffect == 0 || gameMgr->canPlayEffect == 1) {
		if (gameMgr->canPlayEffect == 0) {
			gameMgr->canPlayEffect = 2;
			UserDefault::getInstance()->setIntegerForKey("canPlayEffect", 2);
			UserDefault::getInstance()->flush();
		}
		
		TienlenGameSound::playAutoWin();
	}
	//if (chair == 0)
	resultGroup->showMauBinh(RANK_TOI_TRANG);
}

void BoardScene::jackpot(double gold)
{
	
}

void BoardScene::callbackJackpot(Node* sender)
{
	// show particle
	Size size = Director::getInstance()->getVisibleSize();
	auto particle = ParticleSystemQuad::create("Particles/BurstPipe.plist");
	particle->setLocalZOrder(5);
	pEffectAll->addChild(particle);
	particle->setPosition(size.width * 0.5, size.height);
}

void BoardScene::updateJackpot()
{
	lbJackpot->setString(StringUtility::pointNumber(GameLogic::getInstance()->jackpotNumber) + "$");
}

void BoardScene::determineInGame()
{
	sceneMgr->showOkDialogWithAction(LocalizedString::to("DETERMINE_PLAYER_IN_TABLE"), [this](int btnId) {
	//	inGameMgr->sendDetermineInGame();
	});
}

void BoardScene::regQuit(bool status)
{
	
}

void BoardScene::kickFromRoom(char chair, char reason1)
{
	if (chair != 0) {
		arrayPlayer[chair]->setVisible(false);
	}
	else {
		// kick minh ra thi phai show li do
		string reason;
		switch (reason1) {
		case 0:
			reason = LocalizedString::to("QUESTION_CHANGE_GOLD");
			break;
		case 6:
		case 12:
			reason = LocalizedString::to("KICK_CANCEL");
			break;
		case 2:
			reason = LocalizedString::to("KICK_NOT_PLAYER");
			break;
		case 10:
			reason = LocalizedString::to("KICK_NOT_PLAY");
			break;
		case 1:
			reason = LocalizedString::to("KICK_NOT_REG");
			break;

		default:
			reason = LocalizedString::to("KICK_ROOM_ERROR") + " " + reason;
			break;
		}

		if (reason1 == 0) {
			sceneMgr->showChangeGoldDialog(reason, [this](int buttonId) {
				if (buttonId == Dialog::BTN_OK) {
				}
				else {
				}
			});
		}
		else {
			sceneMgr->showOkDialogWithAction(reason, [this](int btnId) {
			});
		}
	}

}

void BoardScene::updateBigBet()
{
	
}

void BoardScene::effectBigBet(Vec2 endPos)
{

}

void BoardScene::chatEmoticon(char chair, char id, char type)
{
	arrayPlayer[chair]->chatEmoticon(id, type);
}

void BoardScene::chatMessage(char chair, string message)
{

}

void BoardScene::updateUserMoney(char chair)
{
	PlayerInfo* info = GameLogic::getInstance()->arrayPlayer[chair];
	if (info->Gold() <= 1000) {
		if (chair != 0) {
			// Thay the User
			info->renewUser();
		}
		else {
			//GameLogic::getin
		}
	}

	arrayPlayer[chair]->updateMoney();
}

void BoardScene::suddenWin()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->stopTurn();
	}
}

void BoardScene::endCard(char chair)
{
	arrayPlayer[chair]->endCard();
}

void BoardScene::fineMoney(double money, char getChair, char loseChair)
{
	arrayPlayer[getChair]->effectGold(money);
	arrayPlayer[loseChair]->effectGold(-money);
	arrayPlayer[getChair]->updateMoney();
	arrayPlayer[loseChair]->updateMoney();
	if (GameLogic::getInstance()->rate > 0) {
		effectBigBet(arrayPlayer[getChair]->getPositionAvatar());
	}
}

CardEffect * BoardScene::getCardEffect(bool isTop)
{
	vector <CardEffect*> *arrayCard;
	if (isTop) {
		arrayCard = &arrayCardEffectTop;
	}
	else {
		arrayCard = &arrayCardEffect;
	}
	CardEffect *card = NULL;
	for (int i = 0; i < (int)arrayCard->size(); i++) {
		if (!arrayCard->at(i)->isVisible()) {
			card = arrayCard->at(i);
			break;
		}
	}
	if (card == NULL) {
		card = new CardEffect(52);
		if (isTop) {
			pEffectTop->addChild(card);
		}
		else {
			pCard->addChild(card, 1);
		}
		arrayCard->push_back(card);
	}
	card->setRotation3D(Vec3(0, 0, 0));
	card->setScale(1);
	card->setVisible(true);
	card->setOpacity(255);
	card->setIdCard(52);
	card->setDark(false);
	card->setLocalZOrder(0);
	return card;
}

vector<int> BoardScene::getArrayCardSelect()
{
	return((SelfUI*)arrayPlayer[0])->getArraySelect();
}

void BoardScene::autoCard(vector <int> arrayId)
{
	((SelfUI*)arrayPlayer[0])->autoCard(arrayId);
}

void BoardScene::checkCanThrowCard()
{
	((SelfUI*)arrayPlayer[0])->checkCanThrowCard();
}


void BoardScene::onTouchBoard()
{
	showMore = false;
	showMoreButton();
}

void BoardScene::showMoreButton()
{
	
}

ax::Node* BoardScene::getNodeEffect(char chair)
{
	char convert = GameLogic::getInstance()->getChair(chair);
	return arrayPlayer[convert]->pEffect;
}

void BoardScene::onButtonRelease(ax::ui::Button* button, int id)
{
	Size size = Director::getInstance()->getVisibleSize();
	if (id != BOARD_SCENE_BTN_MORE) {
		onTouchBoard();
	}
	switch (id)
	{
	case BOARD_SCENE_BTN_START: {
		PlayerInfo* info = GameLogic::getInstance()->arrayPlayer[0];
		if (info->Gold() <= 1000 && GameLogic::getInstance()->checkGetSupport()) {
			JNIUtils::sendEvent("get_support", "1");
			return;
		}

		if (info->Gold() <= 1000) {
			string reason = LocalizedString::to("VIEW_REWARD");
			sceneMgr->showOkCancelDialog(reason, [this](int buttonId) {
				if (buttonId == Dialog::BTN_OK) {
                    if (gameMgr->useAds)
                    {
                        JNIUtils::showRewardedAds();
                        JNIUtils::sendEvent("show_reward", "1");
                    }
                    else
                    {
                        GameLogic::getInstance()->onReward(1);
                    }
				}
				else {
#if (AX_TARGET_PLATFORM != AX_PLATFORM_ANDROID)
					GameLogic::getInstance()->onReward(1);
#endif
				}
			});
		}
		else {
			btnStart->setVisible(false);
			GameLogic::getInstance()->genStartGame();
		}
		break;
	}
	
	case BOARD_SCENE_BTN_QUIT:
		backKeyPress();
		//inGameMgr->sendQuit();
		break;
	case BOARD_SCENE_BTN_SOUND: {
		//GameLogic::getInstance()->autoPlay();
		/*vector<int> arr;
		arr.push_back(23);
		arr.push_back(25);
		arr.push_back(26);
		arr.push_back(27);
		moveCardToiTrang(arr, 1);
		return;*/
	
		gameMgr->changeSound();
		loadBtnSound();
		/*cardEndGroup->setVisible(true);
		vector<int> arr;
		vector<Vec2> arr1;
		arr.push_back(23);
		arr.push_back(25);
		arr.push_back(26);
		arr.push_back(27);
		arr1.push_back(Vec2(100, 100));
		arr1.push_back(Vec2(100, 100));
		arr1.push_back(Vec2(100, 100));
		arr1.push_back(Vec2(100, 100));
		cardEndGroup->showCardEnd(arr, arr1, 1);
		this->_layout->runAction(
			Sequence::create(
				DelayTime::create(0.3),
				Repeat::create(
					Sequence::create(
						MoveBy::create(0.02, Vec2(10, 0)),
						MoveBy::create(0.04, Vec2(-20, 0)),
						MoveBy::create(0.02, Vec2(10, 0)),
						NULL
					), 3
				),
				DelayTime::create(1.3),
				ScaleTo::create(0.1, 1.1),
				EaseBounceOut::create(ScaleTo::create(0.2, 1.0)),
				NULL
			)
		);*/
		break;
	}
		break;
	case BOARD_SCENE_BTN_JACK_POT:
		break;
	case BOARD_SCENE_BTN_LANGUAGE: {
		//GameLogic::getInstance()->autoPlay();
		gameMgr->setting.isVietnam = !gameMgr->setting.isVietnam;
		StorageUtil::setBool("_game_setting_vietnam_", gameMgr->setting.isVietnam);
		loadBtnLanguage();
		if (gameMgr->setting.isVietnam) {
			languageMgr->changeLanguage(LANGUAGE_VN);
		}
		else {
			languageMgr->changeLanguage(LANGUAGE_EN);
		}
		break;
	}
	case BOARD_SCENE_BTN_TOP:
		/*if (gameMgr->showedTop == false) {
			gameMgr->showedTop = true;
			StorageUtil::setBool("showedTop", true);
			btnTop->stopAllActions();
		}*/

		
		break;
	case BOARD_SCENE_BTN_HELP: 
		sceneMgr->openGUI(GUIHelp::className, 205, 205);
		break; 
	case BOARD_SCENE_BTN_GAME:
		JNIUtils::openApp("com.bcsofts.tlk");
		break;
	default:
		break;
	}
}


void BoardScene::onReceiveChatEmotion(int index, int fromUserId) {

}

void BoardScene::onReceiveChatMessage(std::string msg, char chair) {

}

void BoardScene::updateAvatarFrame(char chairInServer)
{
	auto chairInClient = GameLogic::getInstance()->getChair(chairInServer);
	auto info = GameLogic::getInstance()->getInfo(chairInClient);
	if (info) {
		arrayPlayer[chairInClient]->updateAvatarFrame(info->ID());
	}
}

ax::Point BoardScene::getPositionAvatar(char chairInServer)
{
    auto chairInClient = GameLogic::getInstance()->getChair(chairInServer);
    if (arrayPlayer[chairInClient]) return arrayPlayer[chairInClient]->getPositionAvatar();
    else return { 0, 0 };
}

void BoardScene::setInfoCountDown() {

}

void BoardScene::updateMyInfo() {
    //listPlayers[0]->updateInfo();
}

ui::Text* BoardScene::getMyGoldLabel() {
    return nullptr;
}

Node* BoardScene::getMyAvatar() {
    return nullptr;
}


Vec2 BoardScene::getPosFromPlayer(int id) {
    return Vec2(0, 0);
}


std::vector<Vec2> BoardScene::getPlayerPosExcepted(int id) {
    std::vector<Vec2> ret;
    return ret;
}

void BoardScene::loadBtnSound()
{
    string arrayTheme[3] = { "RedTheme", "BlueTheme", "GreenTheme" };
    string path = "BlueTheme/";
    string resource = gameMgr->getSetting().sound == 1 ? (path + "btnSound.png") : (path + "btnSoundOff.png");
    btnSound->loadTextures(resource, resource, resource);
}

void BoardScene::loadBtnLanguage()
{
    string path = "Game/";
    string resource = gameMgr->getSetting().isVietnam ? (path + "flag_1.png") : (path + "flag_0.png");
    btnLanguage->loadTextures(resource, resource, resource);
    ((SelfUI*)arrayPlayer[0])->updateLanguage();
    resource = gameMgr->isIndo == false ? (path + "textViet/btnStart.png") : (path + "btnStart.png");
    btnStart->loadTextures(resource, resource, resource);
}

void BoardScene::backKeyPress()
{
    gameMgr->checkCanPlayEffect();
    if (GameLogic::getInstance()->getGameState() == GameState::GAME_WAITING) {
        if (GameLogic::getInstance()->isPosture)
            sceneMgr->openScene(GUILevel::className);
        else
            sceneMgr->openScene(LobbyScene::className);
        JNIUtils::showAdsBanner(1);
    }
    else {
        string message = LocalizedString::to("QUIT_GAME");
        int bet = 6 * 1000;
        message = StringUtility::replaceAll(message, "@gold", to_string(bet));
        sceneMgr->showOkCancelDialog(message, [this](int buttonId) {
            if (buttonId == Dialog::BTN_OK) {
                int bet = 6 * 1000;
                GameLogic::getInstance()->arrayPlayer[0]->Gold(GameLogic::getInstance()->arrayPlayer[0]->Gold() - bet);
                if (GameLogic::getInstance()->isPosture)
                    sceneMgr->openScene(GUILevel::className);
                else
                    sceneMgr->openScene(LobbyScene::className);
                JNIUtils::showAdsBanner(1);
                if (GameLogic::getInstance()->countGame >= 2) {
                    if (gameMgr->useAds)
                        JNIUtils::showAdsFull();
                    GameLogic::getInstance()->countGame = 0;
                }
            }
            else {

            }
            });
    }
}

void BoardScene::moveCardToiTrang(vector<int> arrayId, int indexPlayer)
{
    //this->arrayPlayer[indexPlayer]->hideAllCard();
    int numCard = arrayId.size();
    moveCardToiTrang1(numCard, indexPlayer);
}

void BoardScene::moveCardToiTrang1(int numCard, int indexPlayer)
{
    JNIUtils::setString("indexPlayer ", (to_string(indexPlayer) + " " + to_string(numCard) + " " + to_string(arrayCardEffectTop.size())).c_str());
    float scaleEnd         = 1.2;
    Size size              = Director::getInstance()->getVisibleSize();
    float widthCard        = arrayCardEffectTop[0]->getContentSize().width * scaleEnd;
    float padCard          = widthCard * 0.4;
    float sum              = padCard * (numCard - 1) + widthCard;
    float startX           = size.width * 0.5 - sum * 0.5;
    JNIUtils::setString("moveCardToiTrang ", " 1 ");
    PlayerInfo* playerInfo = GameLogic::getInstance()->getInfo(indexPlayer);
    JNIUtils::setString("moveCardToiTrang ", " 2 ");
    for (int i = 0; i < numCard; i++)
    {
        if (i >= playerInfo->arrayCard.size())
        {
            GameLogic::getInstance()->endGame();
            return;
        }

        CardEffect* card = getCardEffect(true);
        JNIUtils::setString("moveCardToiTrang card", to_string(i).c_str());
        card->setIdCard(playerInfo->arrayCard[i]);
        double scale  = arrayPlayer[indexPlayer]->getCardSize().width / card->getContentSize().width;
        Vec2 pos      = arrayPlayer[indexPlayer]->getCardPos(i);
        pos           = card->getParent()->convertToNodeSpace(pos);
        float targetX = startX + widthCard * 0.5;
        card->setRotation3D(Vec3(0, 0, 0));
        Vec2 posTarget = Vec2(targetX, size.height * 0.4);
        posTarget      = card->getParent()->convertToNodeSpace(posTarget);
        card->moveToiTrang(pos, posTarget, scale, scaleEnd, i, indexPlayer == 0, 0.1 * i);
        card->setLocalZOrder(i);
        startX = startX + padCard;

        runAction(Sequence::create(DelayTime::create(0.1 * i),
                CallFuncN::create(AX_CALLBACK_1(BoardScene::callbackVibrate, this, 20)), NULL));
    }
}

const std::string BoardScene::className = "BoardScene";

