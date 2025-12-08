#include "BinhBoardScene.h"
#include "core/utils/StringUtility.h"
#include "../logic/BinhGameLogic.h"
#include "core/gui/SceneMgr.h"
#include "../BinhInGameMgr.h"
#include "BinhOtherUI.h"
#include "BinhSelfUI.h"
#include "core/utils/TienlenGameSound.h"
#include "Game/Utility/JNIUtils.h"
#include "app/GameMgr.h"
#include "MauBinhGroup.h"
#include "BinhLobbyScene.h"
#include "BinhHelpGUI.h"
#include <Game/Utility/Toast.h>
#include <Engine/GlobalVar.h>

using namespace ax::ui;
#define BOARD_SCENE_BTN_JACK_POT 0
#define BOARD_SCENE_BTN_MORE 1
#define BOARD_SCENE_BTN_CAMERA 2
#define BOARD_SCENE_BTN_QUIT 3
#define BOARD_SCENE_BTN_SOUND 4
#define BOARD_SCENE_BTN_HELP 5
#define BOARD_SCENE_BTN_START 6
#define BOARD_SCENE_BTN_ARRANGE 7 
#define BOARD_SCENE_BTN_THEME 8 
#define BOARD_SCENE_BTN_TOP 9
#define BOARD_SCENE_BTN_LANGUAGE      10

BinhBoardScene::BinhBoardScene()
{
}
BinhBoardScene::~BinhBoardScene()
{

}

void BinhBoardScene::onEnter()
{
	BaseLayer::onEnter();
}


bool BinhBoardScene::init()
{
	BaseLayer::init();
	initWithBinaryFile("Board/GUIGame.csb");
	//setKeyboardEnabled(true);
	return true;
}


void BinhBoardScene::initGUI()
{
    countFireworkTime = -1;
    dragon = NULL;
	idTheme = UserDefault::getInstance()->getIntegerForKey("idTheme", 0);
	JNIUtils::sendEvent(("table_" + to_string(idTheme)).c_str(), "1");
	srand((unsigned int)time(NULL));
	Size size = Director::getInstance()->getVisibleSize();

	bgBoard = (ImageView *)getControl("bg");
	//bgBoard->loadTexture("table/bgTable1.jpg");
	//bgBoard->setVisible(false);
	bgDark = getControl("bgDark");

	Node *panelBack = getControl("panelBack");
	Node *panelBtn = getControl("panelBtn");
	Node *panelRight = getControl("panelRight");
	Node *panelCenter = getControl("panelCenter");
	Node *pTopRight = getControl("panelUpRight");

	labelBet = (Text*)getControl("bet", panelBack);

	btnStart = customButton("btnStart", BOARD_SCENE_BTN_START, panelCenter);
	
	clockGame = new ClockGame();
	panelCenter->addChild(clockGame);
	clockGame->setPosition(panelCenter->getContentSize().width * 0.5, panelCenter->getContentSize().height * 0.55);

	imgChi = (ImageView*)getControl("imageChi", panelCenter);
	imgChi->ignoreContentAdaptWithSize(true);
	imgFinish = (ImageView*)getControl("finishImage", panelRight);

	pEffectAll = Node::create();
	_layout->addChild(pEffectAll);
	
	btnQuit = customButton("btnBack", BOARD_SCENE_BTN_QUIT, panelBack);
	btnArrange = customButton("btnArrange", BOARD_SCENE_BTN_ARRANGE, panelRight);
	btnSound = customButton("btnSound", BOARD_SCENE_BTN_SOUND, pTopRight);
	btnHelp = customButton("btnHelp", BOARD_SCENE_BTN_HELP, pTopRight);
    btnLanguage    = customButton("btnLanguage", BOARD_SCENE_BTN_LANGUAGE, pTopRight);
    string res;
    if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
    {
        //languageMgr->changeLanguage("en");
        res = "Board/table/flag_0.png";
    }
    else
    {
       // languageMgr->changeLanguage("vn");
        res = "Board/table/flag_1.png";
    }
    btnLanguage->loadTextures(res, res, res);

	manager        = EffectManager::create(size);
	Effect* effect = Effect::create("flame.efk", 40);
	emitter = EffectEmitter::create(manager);
	emitter->setEffect(effect);
	emitter->setPlayOnEnter(false);
	emitter->setPosition(size.width * 0.5, size.height * 0.5 - 50);
	addChild(emitter);
	emitter->setRemoveOnStop(false);
	emitter->stop();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, ax::Event* event) {
		char buf[100] = { 0 };

		sprintf(buf, "Key %d was pressed!", (int)keyCode);
		//	auto label = static_cast<BinhBoardScene*>(event->getCurrentTarget());
		int code = (int)keyCode;
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
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
		
		BinhGameLogic::getInstance()->myChair = 0;

		if (keyCode == EventKeyboard::KeyCode::KEY_1) {

			BinhGameLogic::getInstance()->arrayPlayer[0]->setArrayCard(arrayId);
			gui->dealStartGame();
			//gui->arrayPlayer[0]->endDealCard();

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_2) {
			gui->arrayPlayer[0]->summary(-1000);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_3) {

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_4) {
			//gui->arrayPlayer[0]->showCancel(true);
		
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_5) {
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_6) {
			arrayId.at(0) = 50;
			arrayId.at(1) = 51;
			BinhGameLogic::getInstance()->arrayPlayer[0]->setArrayCard(arrayId);
			gui->arrayPlayer[0]->endDealCard();

			vector <int> ar;
			ar.push_back(50);
			ar.push_back(51);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_7) {
			//gui->jackpot(100000);
			//gui->dealStartGame();
			//BinhGameLogic::getInstance()->rate = 3;
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
			//BinhGameLogic::getInstance()->endCard(2, ar, 7);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_9) {
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, pEffectAll);
	initPlayer();
	loadTheme();
}

void BinhBoardScene::initPlayer()
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		Node* panel = (Node*)getControl("Panel_" + to_string(i), _layout);
		if (i != 0)
			arrayPlayer[i] = new BinhOtherUI(i, panel, manager);
		else
			arrayPlayer[i] = new BinhSelfUI(panel, manager);
	}
}

void BinhBoardScene::onEnterFinish()
{
	//TODO
	// stop music
	///audioEngine.stopMusic();
    joinRoomSuccess();
	Size size = Director::getInstance()->getVisibleSize();
	pEffectAll->removeAllChildren();
	btnQuit->setVisible(true);
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->onEnterFinish();
	}
	//effBtnStart->getSlot("Layer 5")->getChildArmature()->getAnimation()->gotoAndPlay("5");
	
	//updateJackpot();
	scheduleUpdate();
    for (int i = 1; i < NUM_PLAYER; i++) {
        BinhPlayerInfo* info = new BinhPlayerInfo(i);
        BinhGameLogic::getInstance()->newUserJoinRoom(info);
    }
    BinhGameLogic::getInstance()->autoStart(5, true);
    autoState = AUTO_START_STATE;
    BinhGameLogic::getInstance()->timeAuto = -5;
    BinhGameLogic::getInstance()->isOffline = true;
    
}

void BinhBoardScene::update(float delta)
{
	
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->update(delta);
	}

	if (BinhGameLogic::getInstance()->timeAuto >= 0) {
		BinhGameLogic::getInstance()->timeAuto = BinhGameLogic::getInstance()->timeAuto - delta;
		if (BinhGameLogic::getInstance()->timeAuto <= 0) {
			switch (autoState)
			{
			case AUTO_START_STATE:
			{
				// bat dau Game
				vector<char> arrayId;
				for (int i = 0; i < 52; i++) {
					arrayId.push_back(i);
				}
				for (int i = 0; i < NUM_PLAYER; i++)
					arrayAutoCard[i].clear();

                if (gameMgr->winCountBinh + gameMgr->lostCountBinh == 1 || false) {
                    for (int i = 0; i < 13; i++) {
                        int id = i * 4 + AXRANDOM_0_1() * 3.9999;
                        arrayAutoCard[0].push_back(id);
                        int index = 0;
                        for (int j = 0; j < arrayId.size(); j++) {
                            if (arrayId[j] == id) {
                                arrayId.erase(arrayId.begin() + j);
                                break;
                            }
                        }
                    }
                    for (int i = 0; i < 39; i++)
                    {
                        int value = AXRANDOM_0_1() * arrayId.size() * 0.999f;
                        arrayAutoCard[1 + i % 3].push_back(arrayId[value]);
                        arrayId.erase(arrayId.begin() + value);
                    }
                }
                else {
                    for (int i = 0; i < 52; i++)
                    {
                        int value = AXRANDOM_0_1() * arrayId.size() * 0.999f;
                        arrayAutoCard[i % 4].push_back(arrayId[value]);
                        arrayId.erase(arrayId.begin() + value);
                    }
                    arrayAutoCard[0].clear();
                    ////	int arr[13] = { 0, 4, 9, 13, 17, 36, 40, 45, 49, 32, 7, 11, 15 };
                   // int arr[13] = {0, 4, 9, 13, 18, 21, 26, 30, 34, 36, 41, 46, 50};
                     int arr[13] = { 0, 1, 2, 3, 16, 17, 18, 19, 34, 35, 41, 42, 50 };
                    for (int i = 0; i < 13; i++)
                    {
                        arrayAutoCard[0].push_back(arr[i]);
                    }
                    /*arrayAutoCard[1].clear();
                            int arr1[13] = { 0, 4, 9, 13, 17, 36, 40, 45, 49, 32, 7, 11, 15 };
                            int arr[13] = { 0, 4, 9, 13, 18, 21, 26, 30, 34, 36, 41, 46, 50 };
                            int arr1[13] = { 0, 4, 20, 28, 44, 45, 37, 33, 25, 21, 7, 12, 15 };
                            int arr1[13] = { 45, 37, 33, 25, 21,  0, 4, 20, 28, 48, 7, 12, 15 };
                            int arr1[13] = { 5, 9, 14, 16, 20, 27, 26, 36, 37, 44, 46, 29, 50 };
                            for (int j = 0; j < 13; j++) {
                                    arrayAutoCard[1].push_back(arr1[j]);
                            }*/
                     arrayAutoCard[2].clear();
                    int arr2[13] = {0, 1, 9, 10, 18, 19, 31, 30, 34, 35, 41, 42, 50};  // luc phe bon
                    // int arr[13] = { 0, 4, 9, 13, 18, 21, 26, 30, 34, 36, 41, 46, 50 };
                    for (int j = 0; j < 13; j++)
                    {
                         arrayAutoCard[2].push_back(arr2[j]);
                    }

                    // arrayAutoCard[3].clear();
                    ////int arr3[13] = { 37, 33, 21, 13, 5, 48, 44, 28, 4, 0, 43, 26, 23 };
                    ////int arr3[13] = { 0, 1, 2, 4, 5, 8, 13, 17, 21, 30, 31, 26, 23 };
                    ////int arr3[13] = { 0, 1, 9, 10, 18, 19, 31, 30, 34, 35, 41, 42, 50 };  // luc phe bon
                    // int arr3[13] = { 0, 8, 12, 20, 24, 1, 9, 25, 29, 37, 2, 10, 14 }; // 3 cai thung
                    ////int arr3[13] = { 0, 4, 8, 12, 16, 1, 5, 9, 13, 17, 22, 11, 14 }; // 3 cai thung
                    // for (int j = 0; j < 13; j++) {
                    //	arrayAutoCard[3].push_back(arr3[j]);
                    // }

                }
				
				BinhGameLogic::getInstance()->notifyStart(arrayAutoCard[0], 1, 48);
				autoState = ARRANGE_CARD_STATE;
				BinhGameLogic::getInstance()->timeAuto = 50;
				//arrayPlayer[2]->setVisible(false);
				//arrayPlayer[3]->setVisible(false);
				break;
			}
			case ARRANGE_CARD_STATE:
			{
				int i, j, num;
				
				for (int i = 0; i < NUM_PLAYER; i++) {
					vector<char> arrayAutoId;
					if (i == 0) {
						BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(BinhGameLogic::getInstance()->myChair);
						for (j = 0; j < NUM_CARD; j++)
							arrayAutoId.push_back(info->PlayerCard()->GroupCards.at(j)->Cards.at(0)->ID);
					}
					else {
						MaubinhPlayerCard playerCard;
						for (j = NUM_CARD - 1; j >= 0; j--) {
							MaubinhGroupCardLogic* group = new MaubinhGroupCardLogic();
							group->AddCardByID(arrayAutoCard[i][j]);
							playerCard.AddGroupCard(group);
						}
						int* arrayId;
						arrayId = playerCard.getAutoArrangeCard();
						for (int j = 0; j < NUM_CARD; j++)
							arrayAutoId.push_back(arrayId[NUM_CARD - j - 1]);
						//arrayAutoId.push_back(arrayAutoCard[i][j]);
					}
					
					BinhGameLogic::getInstance()->endCard(i, arrayAutoId);
				}
				autoState = START_COMPARE_STATE;
				BinhGameLogic::getInstance()->timeAuto = 2.0;
				
				break;
			}
			case START_COMPARE_STATE: {
				// kiem tra xem co ai mau binh khong
				if (BinhGameLogic::getInstance()->autoCheckMauBinh() == false) {
					autoState = MAUBINH_STATE;
					BinhGameLogic::getInstance()->timeAuto = 0.1;
				}
				break;
			}
			case MAUBINH_STATE: {
				if (BinhGameLogic::getInstance()->autoCheckBinhLung() == false) {
					autoState = BINHLUNG_STATE;
					BinhGameLogic::getInstance()->timeAuto = 0.1;
				}
				break;
			}
			case BINHLUNG_STATE: {
				if (BinhGameLogic::getInstance()->isShowAll()) {
					autoState = INDEX_CHI_4_STATE;
					BinhGameLogic::getInstance()->timeAuto = 0.1;
				}
				else {
					autoState = INDEX_CHI_0_STATE;
					BinhGameLogic::getInstance()->timeAuto = 0.1;
				}
				break;
			}
			case INDEX_CHI_0_STATE:
			{
				imgFinish->runAction(
					Sequence::create(
						EaseBackIn::create(MoveBy::create(0.5, Vec2(100, 0))),
						Hide::create(),
						NULL
					)
				);
				// so bai chi 1
				BinhGameLogic::getInstance()->chiIndex(CHI_1);
				autoState = INDEX_CHI_1_STATE;
				BinhGameLogic::getInstance()->timeAuto = 1;
				break;
			}
			case INDEX_CHI_1_STATE:
			{
				arrayMoneySummary.clear();
				for (int i = 0; i < 4; i++) {
					arrayMoneySummary.push_back(0);
				}
				BinhGameLogic::getInstance()->autoCompareChi(CHI_1);
				autoState = COMPARE_CHI_1_STATE;
				BinhGameLogic::getInstance()->timeAuto = 4.5;

				break;
			}
			case COMPARE_CHI_1_STATE:
			{
				BinhGameLogic::getInstance()->chiIndex(CHI_2);
				autoState = INDEX_CHI_2_STATE;
				BinhGameLogic::getInstance()->timeAuto = 1;
				break;
			}
			case INDEX_CHI_2_STATE:
			{
				BinhGameLogic::getInstance()->autoCompareChi(CHI_2);
				autoState = COMPARE_CHI_2_STATE;
				BinhGameLogic::getInstance()->timeAuto = 4.5;
				break;
			}
			case COMPARE_CHI_2_STATE:
			{
				BinhGameLogic::getInstance()->chiIndex(CHI_3);
				autoState = INDEX_CHI_3_STATE;
				BinhGameLogic::getInstance()->timeAuto = 1;
				break;
			}
			case INDEX_CHI_3_STATE:
			{
				BinhGameLogic::getInstance()->autoCompareChi(CHI_3);
				autoState = COMPARE_CHI_3_STATE;
				BinhGameLogic::getInstance()->timeAuto = 4.5;
				break;
			}
			case COMPARE_CHI_3_STATE:
			{
				BinhGameLogic::getInstance()->chiIndex(4);
				autoState = INDEX_CHI_4_STATE;
				BinhGameLogic::getInstance()->timeAuto = 1;
				break;
			}
			case INDEX_CHI_4_STATE:
			{
				if (BinhGameLogic::getInstance()->autoCheckBiSap() == false) {
					autoState = BI_SAP_BAI_STATE;
					BinhGameLogic::getInstance()->timeAuto = 0.1;
				}
				break;
			}
			case BI_SAP_BAI_STATE:
			{
				if (BinhGameLogic::getInstance()->autoCheckBatSap() == false) {
					autoState = BAT_SAP_BAI_STATE;
					BinhGameLogic::getInstance()->timeAuto = 0.1;
				}
				break;
			}
			case BAT_SAP_BAI_STATE:
			{
				vector<double> arr;
				for (int i = 0; i < NUM_PLAYER; i++) {
					arr.push_back(BinhGameLogic::getInstance()->arrayMoneySummary[i]);
				}
				BinhGameLogic::getInstance()->summary(arr);
				for (int i = 0; i < NUM_PLAYER; i++) {
					BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
					info->Gold(info->Gold() + BinhGameLogic::getInstance()->arrayMoneySummary[i]);
					if (i == 0) {
						if (BinhGameLogic::getInstance()->arrayMoneySummary[i] > 0)
							info->WinCount(info->WinCount() + 1);
						else if (BinhGameLogic::getInstance()->arrayMoneySummary[i] < 0)
							info->LostCount(info->LostCount() + 1);
					}
					updateUserMoney(i);
				}
				autoState = SUMMARY_STATE;
				BinhGameLogic::getInstance()->timeAuto = 4;
				break;
			}
			case SUMMARY_STATE:
			{
				BinhGameLogic::getInstance()->endGame();
				autoState = WAIT_NEXT_GAME_STATE;
				BinhGameLogic::getInstance()->timeAuto = 2;
				break;
			}
			case WAIT_NEXT_GAME_STATE:
			{
                for (int i = 0; i < 4; i++)
                {
                    BinhPlayerInfo* info = BinhGameLogic::getInstance()->arrayPlayer[i];
                    if (info->Gold() <= 1000)
                    {
                        if (i != MY_INDEX)
                        {
                            // Thay the User
                            info->renewUser();
                            updateUserMoney(i);
                            arrayPlayer[i]->effectRenew();
                        }
                    }
                }

				BinhGameLogic::getInstance()->autoStart(5, true);
				autoState = AUTO_START_STATE;
				BinhGameLogic::getInstance()->timeAuto = -1;
				if (BinhGameLogic::getInstance()->countGame > AXRANDOM_0_1() * 3 + 2) {
					if (gameMgr->useAds)
					    JNIUtils::showAdsFull();
					BinhGameLogic::getInstance()->countGame = 0;
				}
				break;
			}
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
					BinhGameLogic::getInstance()->arrayPlayer[0]->Gold(30000);
					BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
                    if (gui)
					    gui->updateUserMoney(0);
				});
				JNIUtils::sendEvent("get_reward_success", "1");
				break;
			}
			default:
				break;
			}
		}
	}
	manager->update(delta);

    Size size = Director::getInstance()->getVisibleSize();
    if (countFireworkTime >= 0)
    {
        countFireworkTime = countFireworkTime + delta;
        if (countFireworkTime >= 0.5)
        {
            countFireworkTime = 0;
            spine::SkeletonAnimation* firework = getFirework();
            firework->setVisible(true);
            firework->setPosition(ax::Vec2((0.2 + AXRANDOM_0_1() * 0.6) * size.width, (0.4 + AXRANDOM_0_1() * 0.5) * size.height));
            int index = floor(AXRANDOM_0_1() * 4);
            firework->setAnimation(0, to_string(index), false);
            firework->runAction(
                Sequence::create(
                    DelayTime::create(2.0f),
                    Hide::create(),
                    NULL
                )
            );
        }
    }
}

void BinhBoardScene::updateMyCard(vector<int> arrayId, vector<Vec2> arrayPos, vector<float> arraySize)
{
	arrayPlayer[MY_INDEX]->updateCard();
	for (int i = 0; i < NUM_CARD; i++) {
		BinhCardImage* card = getCardEffect();
		card->setPosition(arrayPos[i]);
		float scale = arraySize[i] / card->getContentSize().width;
		card->setScale(scale);
		card->setIdCard(arrayId[i]);
		Vec2 targetPos = arrayPlayer[MY_INDEX]->getCardPosById(arrayId[i]);
		float targetScale = arrayPlayer[MY_INDEX]->getCardSize().width / card->getContentSize().width;
		int index = arrayPlayer[MY_INDEX]->getIndexById(arrayId[i]);
		card->runAction(Sequence::create(
			DelayTime::create(0.02* i),
			//Spawn::create(
				EaseExponentialOut::create(MoveTo::create(0.3, targetPos)),
				//ScaleTo::create(0.3, targetScale)
			//),
			CallFuncN::create(AX_CALLBACK_1(BinhBoardScene::callbackUpdateMyCard, this, index)),
			NULL
		));
		card->runAction(Sequence::create(DelayTime::create(0.02 * i), ScaleTo::create(0.3, targetScale), NULL));
	}
}

void BinhBoardScene::callbackUpdateMyCard(Node* pSender, int index)
{
	pSender->setVisible(false);
	arrayPlayer[MY_INDEX]->updateDealCard(index);
}

void BinhBoardScene::newGame()
{
	btnStart->setVisible(false);
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->newGame();
	}
	for (int i = 0; i < arrayCardEffect.size(); i++) {
		arrayCardEffect.at(i)->setVisible(false);
	}
	btnArrange->setVisible(false);
	imgChi->setVisible(false);
	imgFinish->setVisible(false);
	clockGame->setVisible(false);
	bgDark->setVisible(false);
}

void BinhBoardScene::joinRoomSuccess()
{
	//return;
	// cap nhat nguoi choi
	newGame();

	//vector <long long> bets = channelMgr->getCurrentListBet();
	//labelBet->setString(StringUtility::formatNumberSymbol(bets[BinhGameLogic::getInstance()->roomBet]));
	labelBet->setString("1.000");

	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerUI *p = arrayPlayer[BinhGameLogic::getInstance()->getChair(i)];
		BinhPlayerInfo *pInfo = BinhGameLogic::getInstance()->arrayPlayer[i];
		if (pInfo->Status() > 0) {
			p->setInfo(pInfo);
			p->setVisible(true);
		}
		else {
			p->setVisible(false);
		}
	}
	updateRoomOwner();
	updateJackpot();
	//updateWaitOther();
	
}

void BinhBoardScene::setViewInfo(char gameState, int gameTime, vector<bool> isPlayings, vector<bool> playerStates)
{
	if (gameState == 1) {
		// van dang trong qua trinh xep bai
		clockGame->setTime(gameTime);
		for (int i = 0; i < NUM_PLAYER; i++) {
			if (isPlayings[i]) {
				int chair = BinhGameLogic::getInstance()->getChair(i);
				arrayPlayer[chair]->showArrayCard1(true);
				if (playerStates[i]) {
					arrayPlayer[chair]->ready();
				}
				else {
					arrayPlayer[chair]->unReady();
				}
			}
		}
	}
	else {
	}
}

void BinhBoardScene::updateStateReady(vector<char> playerStates)
{
	clockGame->setTime(BinhGameLogic::getInstance()->gameTime - 1);
	for (int i = 0; i < NUM_PLAYER; i++) {
		int chair = BinhGameLogic::getInstance()->getChair(i);
		arrayPlayer[chair]->showArrayCard1(true);
		if (playerStates[i]) {
			arrayPlayer[chair]->ready();
		}
		else {
			arrayPlayer[chair]->unReady();
		}
	}
	if (!BinhGameLogic::getInstance()->isTinhAt()) {
		btnArrange->setVisible(true);
	}
}

void BinhBoardScene::updateRoomOwner()
{
	char owner = BinhGameLogic::getInstance()->roomOwner;
	owner = BinhGameLogic::getInstance()->getChair(owner);
	for (int i = 0; i < NUM_PLAYER; i++) {
		arrayPlayer[i]->setRoomOwner(i == owner);
	}
	//myPlayer->setRoomOwner(owner == 0);
}

void BinhBoardScene::updateWaitOther()
{
	if (BinhGameLogic::getInstance()->getGameState() == BinhGameState::BINH_GAME_WAITING) {

	}
	else {
	}
}

void BinhBoardScene::newUserJoinRoom(char chair, BinhPlayerInfo *info)
{
	arrayPlayer[chair]->setVisible(true);
	arrayPlayer[chair]->newGame();
	arrayPlayer[chair]->setInfo(info);
}

void BinhBoardScene::userLeave(char chair)
{
	arrayPlayer[chair]->setVisible(false);
}

void BinhBoardScene::autoStart(int time, bool isAutoStart) {
	if (isAutoStart) {
		if (BinhGameLogic::getInstance()->isShowBtnStart()) {
            string res = "Board/table/" + BinhGameLogic::getInstance()->getRes() + "btnStart.png";

            btnStart->loadTextures(res, res, res);
			btnStart->setVisible(true);
			btnStart->runAction(
				RepeatForever::create(
					Sequence::create(
						ScaleTo::create(0.3, 1.1),
						ScaleTo::create(0.3, 1.0),
						NULL
					)
				)
			);
		}
		else {
		}
	}
	else {
		btnStart->setVisible(false);
		timeWaitOther = -1;
	}
}

void BinhBoardScene::notifyStart()
{
	btnStart->setVisible(false);
	//arrayPlayer[MY_INDEX]->updateCard();
	dealStartGame();
	TienlenGameSound::startGame();
}

void BinhBoardScene::dealStartGame()
{
	JNIUtils::sendEvent("new_game", "1");
	int count = 0;
	float timeDelay;
	float timeDeal = 0.02;
	for (int i = 0; i < NUM_CARD; i++) {
		for (int j = 0; j < NUM_PLAYER; j++) {
			BinhPlayerInfo* player = BinhGameLogic::getInstance()->arrayPlayer[BinhGameLogic::getInstance()->getChairInServer(j)];
			if (player->isPlaying()) {
				timeDelay = timeDeal * count;
				count++;
				/*runAction(
					Sequence::create(
						DelayTime::create(timeDelay),
						CallFuncN::create(AX_CALLBACK_1(BinhBoardScene::callbackDealCard, this, i, j)),
						NULL
					)
				);*/
				callbackDealCard(this, i, j);
			}
		}
	}
	timeDelay = timeDeal * count;
	runAction(
		Sequence::create(
			DelayTime::create(timeDelay + 0.5),
			CallFuncN::create(AX_CALLBACK_0(BinhBoardScene::callbackEndDealCard, this, true)),
			NULL
		)
	);
	TienlenGameSound::playSoundChiaBai();
	//TienlenGameSound::playSoundstart_1();
}

void BinhBoardScene::callbackDealCard(Node* sender, int num, int indexPlayer)
{
	int numConvert = (3 - floor(num / 5)) * 5 + num % 5;
	Size size = Director::getInstance()->getVisibleSize();
	BinhCardImage *card = getCardEffect();
	float padY = 0.3;
	int index = num * 4 + indexPlayer;
	card->setPosition(size.width * 0.5, size.height * 0.5 + padY * (52 - index));
	card->setRotation(0);
	card->setLocalZOrder(numConvert);
	card->setScale(0.55);
	double scale = arrayPlayer[indexPlayer]->getCardSize().width / card->getContentSize().width;
	Vec2 pos = arrayPlayer[indexPlayer]->getCardPos(num);
	float rotate = arrayPlayer[indexPlayer]->getCardRotation(num);
	float timeDelay;
	float timeDeal = 0.02;
	timeDelay = timeDeal * index;
	if (indexPlayer == 0) {
	//	TienlenGameSound::playSoundChiaBai();
	}
	/*if (indexPlayer == MY_INDEX) {
		Vec2 newPos;
		newPos.x = (pos.x + card->getPositionX()) * 0.5;
		newPos.y = (pos.y + card->getPositionY()) * 0.5;
		card->runAction(
			Sequence::create(
				Spawn::create(
					MoveTo::create(0.2, newPos),
					ScaleTo::create(0.2, 0, scale),
					RotateTo::create(0.2, 45),
					NULL
				),
				CallFuncN::create(AX_CALLBACK_1(BinhBoardScene::callbackDealMyCard, this, num, pos)),
				NULL
			)
		);
	}
	else {*/
		card->runAction(
			Sequence::create(
				DelayTime::create(timeDelay),
				Spawn::create(
					EaseExponentialOut::create(MoveTo::create(0.3, pos)),
					ScaleTo::create(0.3, scale),
					RotateTo::create(0.3, rotate),
					NULL
				),
				//Hide::create(),
				CallFuncN::create(AX_CALLBACK_1(BinhBoardScene::callbackDealCard1, this, num, indexPlayer)),
				NULL
			)
		);
	//}
}

void BinhBoardScene::callbackDealCard1(Node* sender, int num, int indexPlayer)
{
	int numConvert = NUM_CARD - 1 - num;
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(indexPlayer);
	//arrayPlayer[indexPlayer]->updateDealCard(numConvert);
}

void BinhBoardScene::callbackDealMyCard(Node* sender, int num, Vec2 pos)
{
	//BinhCardImage* card = (BinhCardImage*)sender;
	//BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo()
	//sender->setId
	//sender->runAction(
	//	Sequence::create(
	//		Spawn::create(
	//			MoveTo::create(0.2, pos),
	//			ScaleTo::create(0.2, sender->getScaleY(), sender->getScaleY()),
	//			RotateTo::create(0.2, 0),
	//			NULL
	//		),
	//		CallFuncN::create(AX_CALLBACK_1(BinhBoardScene::callbackDealCard1, this, num, MY_INDEX)),
	//		NULL
	//	)
	//);
}

void BinhBoardScene::callbackEndDealCard(bool effectGUI)
{
	BinhGameLogic::getInstance()->setGameState(BinhGameState::BINH_GAME_PLAYING);
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying()) {
			info->NumCard(NUM_CARD);
			arrayPlayer[i]->endDealCard();
		}
	}
	showGUIArrange(effectGUI);

	for (int i = 0; i < arrayCardEffect.size(); i++) {
		arrayCardEffect[i]->setVisible(false);
	}
	//if (BinhGameLogic::getInstance()->isTinhAt()) {
	//	showGUIArrange(effectGUI);
	//}
	//else {
	//	//if 
	//}
	clockGame->setTime(BinhGameLogic::getInstance()->gameTime -1);
}

void BinhBoardScene::showGUIArrange(bool effectGUI)
{
	Vec2 arrayPos[NUM_CARD];
	float widthCard = arrayPlayer[MY_INDEX]->getCardSize().width;
	for (int i = 0; i < NUM_CARD; i++) {
		arrayPos[i] = arrayPlayer[MY_INDEX]->getCardPos(i);
	}
	if (gameMgr->useGuiAt) {
		BinhTinhAt* gui = (BinhTinhAt*)sceneMgr->openGUI(BinhTinhAt::className, BinhTinhAt::TAG, BinhTinhAt::TAG);
		gui->showEffect(arrayPos, widthCard, effectGUI);
		gui->setGameTime(BinhGameLogic::getInstance()->getRemainTime());
	}
	else {
		BinhTruyenThong* gui = (BinhTruyenThong*)sceneMgr->openGUI(BinhTruyenThong::className, BinhTruyenThong::TAG, BinhTruyenThong::TAG);
		gui->showEffect(arrayPos, widthCard, effectGUI);
		gui->setGameTime(BinhGameLogic::getInstance()->getRemainTime());
	}
}

void BinhBoardScene::ready(char chair)
{
	arrayPlayer[chair]->ready();
	if (chair == MY_INDEX) {
        JNIUtils::vibrate(10);
		clockGame->setVisible(true);
		clockGame->onEnterFinish();
		if (!BinhGameLogic::getInstance()->isTinhAt())
			btnArrange->setVisible(true);
	}
}

void BinhBoardScene::unReady(char chair)
{
	arrayPlayer[chair]->unReady();
}

void BinhBoardScene::endCard(char chair)
{
	btnArrange->setVisible(false);
	arrayPlayer[chair]->endCard();
	clockGame->setVisible(false);
}

/**
 * Update quan card khi nguoi choi Reconnect vao ban choi da sang qua trinh so bai, chi doi sang van moi
 */
void BinhBoardScene::updateCardEnd(char chair)
{
	btnArrange->setVisible(false);
	arrayPlayer[chair]->updateCardEnd();
	clockGame->setVisible(false);
}

void BinhBoardScene::chiIndex(char chi)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying()) {
			arrayPlayer[i]->chiIndex(chi);
		}
	}
    JNIUtils::vibrate(10);
	if (chi <= CHI_3) {
		TienlenGameSound::playSoundChi();
		imgChi->setVisible(true);
		//imgChi->loadTexture("table/chi_" + to_string(chi) + ".png");
		if (chi == CHI_1) {
			imgChi->setVisible(false);
		}
//		else {
			imgChi->runAction(
				Sequence::create(
					EaseBackIn::create(MoveBy::create(0.5, Vec2(100, 0))),
					CallFunc::create(AX_CALLBACK_0(BinhBoardScene::callbackChiIndex, this)),
					NULL
				)
			);
		//}
	}
	else {
		imgChi->runAction(
			Sequence::create(
				EaseBackIn::create(MoveBy::create(0.5, Vec2(100, 0))),
				Hide::create(),
				NULL
			)
		);
	}
}

void BinhBoardScene::callbackChiIndex()
{
	imgChi->setVisible(true);
    string res = BinhGameLogic::getInstance()->getRes();
    imgChi->loadTexture("table/" + res + "chi_" + to_string(BinhGameLogic::getInstance()->currentChi) + ".png");
	imgChi->runAction(
		Sequence::create(
			EaseBackOut::create(MoveTo::create(0.5, _defaultPos[imgChi])),
			NULL
		)
	);
}

void BinhBoardScene::compareChi(char chi, vector<double> arrayMoney, vector<int> arrayResult)
{
    JNIUtils::vibrate(10);
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		int convert = BinhGameLogic::getInstance()->getChairInServer(i);
		if (info->isPlaying() && !info->IsCompareBai()) {
			if (i == MY_INDEX)
				arrayPlayer[i]->compareChi(chi, arrayMoney[convert], arrayResult[convert]);
			else
				// day la ket qua cua minh so voi ho, de the hien ket qua cua ho thi dao nguoc lai ket qua
				arrayPlayer[i]->compareChi(chi, arrayMoney[convert], -arrayResult[convert]);
		}
	}
	TienlenGameSound::playSoBai();
}

void BinhBoardScene::sapBai(vector<double> arrayMoney)
{
    JNIUtils::vibrate(30);
	imgChi->setVisible(false);
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying() && !info->IsCompareBai()) {
			// dua bai ve trang thai binh thuong
			arrayPlayer[i]->setNormalZOrder();
		}
		if (info->SapType() != SapBaiType::NOT_SAP) {
			int convert = BinhGameLogic::getInstance()->getChairInServer(i);
			arrayPlayer[i]->sapBai(arrayMoney[convert], info->SapType());
			if (i != 0) {
				Vec2 posStart, posEnd, posMedium;
				if (info->SapType() == SapBaiType::BI_SAP) {
					autoState = BAT_SAP_BAI_STATE;
					posStart = arrayPlayer[0]->getPositionAvatar();
					posEnd = arrayPlayer[i]->getCardPos2(7);
				}
				else {
					autoState = BI_SAP_BAI_STATE;
					posEnd = arrayPlayer[0]->getCardPos2(7);
					posStart = arrayPlayer[i]->getPositionAvatar();
				}
				posMedium = Vec2(posStart.x * 0.5 + posEnd.y * 0.5, posStart.y * 0.5 + posEnd.y * 0.5);
				posMedium.y = posMedium.y + 100 - 200 * AXRANDOM_0_1();
				posMedium.x = posMedium.x + 200 - 400 * AXRANDOM_0_1();
				ccBezierConfig config;
				config.controlPoint_1 = posStart;
				config.controlPoint_2 = posMedium;
				config.endPosition = posEnd;
				auto move = EaseOut::create(BezierTo::create(0.6, config), 1);

				Sprite* imgBomb = Sprite::create("table/iconBomb.png");
				imgBomb->setPosition(posStart);
				pEffectAll->addChild(imgBomb);
				imgBomb->runAction(
					Sequence::create(
						Spawn::create(
							move,
							RotateBy::create(0.6, 150),
							NULL
						),
						RemoveSelf::create(),
						NULL
					)
				);
			}
		}
	}
	
	BinhGameLogic::getInstance()->timeAuto = 3;
}

void BinhBoardScene::soBai(bool isMauBinh, vector<double> arrayMoney)
{
	if (isMauBinh) {
		// hien thi Effect cho Mau Binh, lam toi man hinh
		bgDark->setVisible(true);
		bgDark->setOpacity(0);
		bgDark->runAction(FadeIn::create(0.5));

		// show imgFinish
        string res = "Board/table/" + BinhGameLogic::getInstance()->getRes() + "finish.png";
        imgFinish->loadTexture(res);
		imgFinish->setVisible(true);
		imgFinish->setOpacity(0);
		imgFinish->runAction(Sequence::create(
			FadeIn::create(0.5),
			DelayTime::create(2.0),
			CallFuncN::create(AX_CALLBACK_1(BinhBoardScene::callbackSoBai, this)),
			NULL
		));
		if (gameMgr->canPlayEffect == 0 || gameMgr->canPlayEffect == 1) {
			if (gameMgr->canPlayEffect == 0) {
				gameMgr->canPlayEffect = 2;
				UserDefault::getInstance()->setIntegerForKey("canPlayEffect", 2);
				UserDefault::getInstance()->flush();
			}
		//	emitter->play(1);
			TienlenGameSound::playAutoWin();
		}

        if (BinhGameLogic::getInstance()->getNumMauBinh() == 1)
        {
            countFireworkTime = 0.5;
            Size size      = Director::getInstance()->getVisibleSize();
            float sumWidth = 0;
            float wCard    = size.width / 8.5;
            float padPhom  = wCard * 0.2;
            sumWidth       = wCard * 2.0 + padPhom * 2 + wCard * 6.0;
            float startX   = WIN_SIZE.width * 0.5 - sumWidth * 0.5;

            int chairIndex = 0;
            for (int i = 0; i < NUM_PLAYER; i++)
            {
                BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
                if (info->isPlaying())
                {
                    int convert = BinhGameLogic::getInstance()->getChairInServer(i);
                    if (info->IsMauBinh())
                    {
                        // user nay mau binh
                        chairIndex = i;
                        break;
                    }
                }
            }

            BinhPlayerInfo* info          = BinhGameLogic::getInstance()->getInfo(chairIndex);
            MaubinhPlayerCard* playerCard = info->PlayerCard();
            playerCard->SapXepTruocSoBai();
            int count     = 0;
            float targetX = startX;
            for (int i = 1; i <= 3; i++)
            {
                vector<MaubinhCardLogic*> arrCard;
                if (i == 1)
                {
                    arrCard = playerCard->ChiCuoi->Cards;
                }
                else if (i == 2)
                {
                    arrCard = playerCard->ChiGiua->Cards;
                }
                else
                {
                    arrCard = playerCard->ChiDau->Cards;
                }
                for (int j = 0; j < arrCard.size(); j++)
                {
                    BinhCardImage* card = getCardEffect();
                    card->setIdCard(arrCard[j]->ID);
                    BinhCardButton* tempCard = arrayPlayer[chairIndex]->arrayCard2[count];
                    tempCard->setVisible(false);

                    Vec2 pos     = arrayPlayer[chairIndex]->getCardPos(count);
                    float rotate = arrayPlayer[chairIndex]->getCardRotation(count);
                    double scale = arrayPlayer[chairIndex]->getCardSize().width / card->getContentSize().width;
                    float timeDelay;
                    float timeDeal     = 0.02;
                    timeDelay          = timeDeal * count;
                    targetX            = targetX + wCard * 0.5;
                    float targetScale  = wCard / card->getContentSize().width;
                    float targetRotate = 0;
                    card->setPosition(pos);
                    card->setScale(0.1);
                    card->setRotation(rotate);
                    card->setLocalZOrder(100 + count);
                    // card->setOpacity(0);
                    float timeMove = 0.6;
                    card->runAction(Sequence::create(
                        DelayTime::create(timeDelay), FadeIn::create(0),
                        Spawn::create(EaseExponentialOut::create(
                                            MoveTo::create(timeMove, Vec2(targetX, size.height * 0.3))),
                                        ScaleTo::create(timeMove, targetScale),
                                        RotateTo::create(timeMove, targetRotate), NULL),
                        DelayTime::create(3.0),
                        Spawn::create(EaseExponentialOut::create(MoveTo::create(timeMove, pos)),
                                        ScaleTo::create(timeMove, scale), RotateTo::create(timeMove, rotate),
                                        NULL),
                        Hide::create(), CallFunc::create([tempCard]() { tempCard->setVisible(true); }), NULL));
                    count++;
                }
                targetX = targetX + padPhom + wCard * 0.5;
            }
            int kind = BinhGameLogic::getInstance()->getEffectMaubinh(-1);
            if (kind == EM_SANHRONG) {
                if (dragon == NULL)
                {
                    dragon =
                        spine::SkeletonAnimation::createWithJsonFile("dragon_fire.json", "dragon_fire.atlas", 0.5f);
                    dragon->setAnimation(0, "idle", true);
                    // skeletonNode->setSkin("idle");
                    addChild(dragon);
                    dragon->setRotation(90);
                }
                dragon->setVisible(true);
                dragon->setPosition(Vec2(-400, size.height * 0.3));
                dragon->runAction(
                    Sequence::create(MoveBy::create(5.0, Vec2(size.width * 1.3 + 400, 0)), Hide::create(), NULL));
            }
        }
	}
	else {
		// Binh Lung
		for (int i = 0; i < NUM_PLAYER; i++) {
			BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
			if (info->isPlaying()) {
				int convert = BinhGameLogic::getInstance()->getChairInServer(i);
				if (BinhGameLogic::getInstance()->isShowAll()) {
					arrayPlayer[i]->updateCard();
				}
				arrayPlayer[i]->soBaiBinhLung(arrayMoney[convert]);
			}
		}
	}
	
	if (isMauBinh) {
		autoState = MAUBINH_STATE;
		BinhGameLogic::getInstance()->timeAuto = 8;
	}
	else {
		autoState = BINHLUNG_STATE;
		BinhGameLogic::getInstance()->timeAuto = 4;
	}
}

void BinhBoardScene::callbackSoBai(Node* pSender)
{
    JNIUtils::vibrate(100);
	TienlenGameSound::playSoundMauBinh();
	if (BinhGameLogic::getInstance()->getNumMauBinh() == 1) {
		int kind = BinhGameLogic::getInstance()->getEffectMaubinh(-1);
		Size size = Director::getInstance()->getVisibleSize();
		MauBinhGroup* group = new MauBinhGroup();
            group->setScale(0.8);
		pEffectAll->addChild(group);
		group->showMauBinh(kind);
		group->setPosition(size.width * 0.5, size.height * 0.55);
		group->runAction(
			Sequence::create(
				DelayTime::create(5.0),
				FadeOut::create(0.5),
				RemoveSelf::create(),
				NULL
			)
		);
        
	}
	else {

	}
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying()) {
			int convert = BinhGameLogic::getInstance()->getChairInServer(i);
			if (BinhGameLogic::getInstance()->isShowAll()) {
				arrayPlayer[i]->updateCard();
			}
			arrayPlayer[i]->soBaiMauBinh(BinhGameLogic::getInstance()->arrayMoneyMauBinh[convert]);
		}
	}
	bgDark->runAction(Sequence::create(
		DelayTime::create(6.0),
		FadeOut::create(0.5), CallFunc::create([this]() {
            countFireworkTime = -1;
        }),
		NULL
	));
}

void BinhBoardScene::sapLang(char chair, vector<double> arrayMoney)
{
	if (chair == MY_INDEX) {
		/*DBArmatureNode *effIcon = DBFactory::getInstance()->buildArmatureNode("batsaplang");
		if (effIcon) {
			pEffectAll->addChild(effIcon);
			effIcon->setScale(0.6);
			effIcon->getAnimation()->gotoAndPlay("1", -1, -1, 1);
			effIcon->runAction(
				Sequence::create(
					DelayTime::create(3.0),
					RemoveSelf::create(),
					NULL
				)
			);
		}*/
	}
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying()) {
			int convert = BinhGameLogic::getInstance()->getChairInServer(i);
			arrayPlayer[i]->sapLang(chair, arrayMoney[convert]);
		}
	}
}

void BinhBoardScene::binhAt(vector<double> arrayMoney)
{
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying()) {
			int convert = BinhGameLogic::getInstance()->getChairInServer(i);
			arrayPlayer[i]->binhAt(arrayMoney[convert]);
		}
	}
}

void BinhBoardScene::summary(vector<double> arrayMoney)
{
    JNIUtils::vibrate(20);
	gameMgr->checkCanPlayEffect();
	imgChi->setVisible(false);
    string res = "Board/table/" + BinhGameLogic::getInstance()->getRes() + "finish.png";
    imgFinish->loadTexture(res);
	imgFinish->setVisible(true);
	//imgFinish->setOpacity(0);
	imgFinish->runAction(
		EaseBackOut::create(MoveTo::create(0.5, _defaultPos[imgFinish]))
	);
	for (int i = 0; i < NUM_PLAYER; i++) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(i);
		if (info->isPlaying()) {
			int convert = BinhGameLogic::getInstance()->getChairInServer(i);
			arrayPlayer[i]->summary(arrayMoney[convert]);
		}
	}
}

void BinhBoardScene::jackpot(double gold)
{
	
}

void BinhBoardScene::callbackJackpot(Node* sender)
{
	// show particle
	Size size = Director::getInstance()->getVisibleSize();
	auto particle = ParticleSystemQuad::create("Particles/BurstPipe.plist");
	particle->setLocalZOrder(5);
	pEffectAll->addChild(particle);
	particle->setPosition(size.width * 0.5, size.height);
}

void BinhBoardScene::updateJackpot()
{
}

void BinhBoardScene::regQuit(bool status)
{
	if (status) {
		Toast::makeToast(2.0, LocalizedString::to("REG_QUIT").c_str());
	}
	else {
		Toast::makeToast(2.0, LocalizedString::to("CANCEL_REG_QUIT").c_str());
	}

	//btnQuit->setVisible(!status);
	TienlenGameSound::regQuit(status);
}

void BinhBoardScene::kickFromRoom(char chair, char reason1)
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


void BinhBoardScene::chatEmoticon(char chair, char id, char type)
{
	arrayPlayer[chair]->chatEmoticon(id, type);
}

void BinhBoardScene::chatMessage(char chair, string message)
{

}

void BinhBoardScene::updateUserMoney(char chair)
{
	arrayPlayer[chair]->updateMoney();
}

BinhCardImage * BinhBoardScene::getCardEffect()
{
	BinhCardImage *card = NULL;
	for (int i = 0; i < arrayCardEffect.size(); i++) {
		if (!arrayCardEffect[i]->isVisible()) {
			card = arrayCardEffect[i];
			break;
		}
	}
	if (card == NULL) {
		card = new BinhCardImage(52);
		_layout->addChild(card);
		arrayCardEffect.push_back(card);
	}
	card->setVisible(true);
	card->setOpacity(255);
	card->setIdCard(52);
	card->setDark(false);
	return card;
}

ax::Node* BinhBoardScene::getNodeEffect(char chair)
{
	char convert = BinhGameLogic::getInstance()->getChair(chair);
	return arrayPlayer[convert]->pEffect;
}

void BinhBoardScene::onButtonRelease(ax::ui::Button* button, int id)
{
	Size size = Director::getInstance()->getVisibleSize();
	
	switch (id)
	{
	case BOARD_SCENE_BTN_START: {
		/*sceneMgr->showOkDialogWithAction("lfdjfld fdljf ", [this](int btnId) {
		});
		return;*/
        //arrayPlayer[0]->showGun(0);
		UserInfo* info = BinhGameLogic::getInstance()->arrayPlayer[0]->getUserInfo();
		if (info->bean <= 1000 && BinhGameLogic::getInstance()->checkGetSupport()) {
			JNIUtils::sendEvent("get_support", "1");
			return;
		}
		
		if (info->bean <= 1000) {
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
                        BinhGameLogic::getInstance()->onReward(1);
                    }
				}
				else {
					#if (AX_TARGET_PLATFORM != AX_PLATFORM_ANDROID)
					BinhGameLogic::getInstance()->onReward(1);
					#endif
				}
			});
		}
		else {
			btnStart->setVisible(false);
			autoState = AUTO_START_STATE;
			BinhGameLogic::getInstance()->timeAuto = 0;
			/*if (BinhGameLogic::getInstance()->isOffline)
				BinhGameLogic::getInstance()->timeAuto = 0;
			else
				inGameMgr->sendStart();*/
		}

		break;
	}
	case BOARD_SCENE_BTN_QUIT:
		//TienlenGameSound::playSoundmaubinh_3caisanh();
		backKeyPress();
        /*if (BinhGameLogic::getInstance()->isOffline)
            exit(1);
        else
            inGameMgr->sendQuit();*/
		break;
	case BOARD_SCENE_BTN_HELP:
		sceneMgr->openGUI(BinhHelpGUI::className);
		break;
    case BOARD_SCENE_BTN_LANGUAGE:
        {
            //gameMgr->isIndo = !gameMgr->isIndo;
            //StorageUtil::setBool("isIndo", gameMgr->isIndo);
            if (languageMgr->checkCurrentLanguage(LANGUAGE_EN)) {
                languageMgr->changeLanguage(LANGUAGE_VN);
            }
            else {
                languageMgr->changeLanguage(LANGUAGE_EN);
            }
            string res = "";
            if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
            {
                res = "Board/table/flag_0.png";
            }
            else
            {
                res = "Board/table/flag_1.png";
            }
            btnLanguage->loadTextures(res, res, res);
            break;
        }
	case BOARD_SCENE_BTN_SOUND: {
		gameMgr->changeSound();
		loadBtnSound();
		break;
	}
	case BOARD_SCENE_BTN_THEME: {
		idTheme = idTheme + 1;
		if (idTheme >= 3)
			idTheme = 0;
		UserDefault::getInstance()->setIntegerForKey("idTheme", idTheme);
		UserDefault::getInstance()->flush();
		loadTheme();
		break;
	}
	
	case BOARD_SCENE_BTN_ARRANGE:
		showGUIArrange(true);
		btnArrange->setVisible(false);
		binhInGameMgr->sendUnReady();
		break;
	default:
		break;
	}
}


void BinhBoardScene::backKeyPress()
{
	gameMgr->checkCanPlayEffect();
	if (BinhGameLogic::getInstance()->getGameState() == BinhGameState::BINH_GAME_WAITING) {
	//	sceneMgr->openScene(BinhLobbyScene::className);
            JNIUtils::showAdsBanner(1);
                sceneMgr->layerGUI    = nullptr;
                sceneMgr->layerSystem = nullptr;
                Director::getInstance()->replaceScene(mainScene);
                sceneMgr->curGui = "";
	}
	else {
		string message = LocalizedString::to("QUIT_GAME");
		int bet = 6 * BinhGameLogic::getInstance()->goldBet;
		message = StringUtility::replaceAll(message, "@gold", to_string(bet));
		sceneMgr->showOkCancelDialog(message, [this](int buttonId) {
			if (buttonId == Dialog::BTN_OK) {
				int bet = 6 * BinhGameLogic::getInstance()->goldBet;
				BinhGameLogic::getInstance()->arrayPlayer[0]->Gold(BinhGameLogic::getInstance()->arrayPlayer[0]->Gold() - bet);
				//sceneMgr->openScene(BinhLobbyScene::className);
                JNIUtils::showAdsBanner(1);
                sceneMgr->layerGUI    = nullptr;
                sceneMgr->layerSystem = nullptr;
                Director::getInstance()->replaceScene(mainScene);
                sceneMgr->curGui = "";
                if (BinhGameLogic::getInstance()->countGame >= 2) {
                    if (gameMgr->useAds)
                        JNIUtils::showAdsFull();
                    BinhGameLogic::getInstance()->countGame = 0;
                }
			}
			else {

			}
		});
	}
}

void BinhBoardScene::onReceiveChatEmotion(int index, int fromUserId) {

}

void BinhBoardScene::onReceiveChatMessage(std::string msg, char chair) {

}

void BinhBoardScene::setInfoCountDown() {

}

void BinhBoardScene::updateMyInfo() {
	//listPlayers[0]->updateInfo();
}

ui::Text *BinhBoardScene::getMyGoldLabel() {
	return nullptr;
}

Node *BinhBoardScene::getMyAvatar() {
	return nullptr;
}


Vec2 BinhBoardScene::getPosFromPlayer(int id) {
	return Vec2(0, 0);
}


std::vector<Vec2> BinhBoardScene::getPlayerPosExcepted(int id) {
	std::vector<Vec2> ret;
	return ret;
}


ax::Point BinhBoardScene::getPositionAvatar(char chairInServer)
{
	auto chairInClient = BinhGameLogic::getInstance()->getChair(chairInServer);
	if (arrayPlayer[chairInClient]) return arrayPlayer[chairInClient]->getPositionAvatar();
	else return { 0, 0 };
}


void BinhBoardScene::updateAvatarFrame(char chairInServer)
{
	
}

void BinhBoardScene::loadTheme()
{
	
}

void BinhBoardScene::loadBtnSound()
{
	string arrayTheme[3] = { "RedTheme", "BlueTheme", "GreenTheme" };
	string path = "BlueTheme/";
	string resource = gameMgr->getSetting().sound == 1 ? (path + "btnSound.png") : (path + "btnSoundOff.png");
	btnSound->loadTextures(resource, resource, resource);
}

void BinhBoardScene::updateMyAvatar()
{
	arrayPlayer[0]->updateAvatarFrame();
}

void BinhBoardScene::loadLanguage() {
    if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
    {

    }
}

spine::SkeletonAnimation* BinhBoardScene::getFirework()
{
    for (int i = 0; i < arrayFirework.size(); i++) {
        if (!arrayFirework[i]->isVisible())
        {
            return arrayFirework[i];
        }
    }
    spine::SkeletonAnimation* firework = spine::SkeletonAnimation::createWithJsonFile(
        "spine/firework.json", "spine/firework.atlas", 0.7f);
    arrayFirework.push_back(firework);
    addChild(firework);
    return firework;
}

const std::string BinhBoardScene::className = "BinhBoardScene";


/*****************************  Native Callback method  *****************************/
