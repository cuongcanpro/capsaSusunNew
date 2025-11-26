#include "TalaScene.h"
#include "core/utils/StringUtility.h"
#include "../logic/TalaGameLogic.h"
#include "core/gui/SceneMgr.h"
#include "../TalaInGameMgr.h"
#include "core/utils/TienlenGameSound.h"
#include "../logic/TalaGameRule.h"
#include "Game/Utility/JNIUtils.h"
#include "TalaLobbyScene.h"
#include <core/utils/TalaGameSound.h>


using namespace ax::ui;

TalaScene::TalaScene()
{
}
TalaScene::~TalaScene()
{

}

bool TalaScene::init()
{
	BaseLayer::init();
	initWithBinaryFile("Board/TalaGameGUI.csb");
	return true;
}


void TalaScene::initGUI()
{
	srand((unsigned int)time(NULL));
	Button* btnXepBai = customButton("btnQuit", BTN_QUIT);
	btnSound = customButton("btnSound", BTN_SOUND);
	btnXepBai = customButton("btnXepbai", BTN_XEPBAI);
	btnDanh = customButton("btnDanh", BTN_DANH);
	btnHaBai = customButton("btnHaBai", BTN_HABAI);
	btnGuiBai = customButton("btnGuiBai", BTN_GUIBAI);
	btnStart = customButton("btnStart", BTN_START);
	btnGroup = customButton("btnGroup", BTN_GROUP);
	btnGroup->setPressedActionEnabled(false);
	customButton("btnEmo", BTN_EMO);
	customButton("btnPanelChat", BTN_CHAT);

	deckCard = (ImageView*)getControl("card", btnGroup);
	deckCard->setVisible(false);
    ((Layout*)getControl("pCard"))->setLocalZOrder(0);
	TalaCardView::SMALL_SCALE = deckCard->getScale();
	for (int i = 0; i < NUM_PLAYER; i++) {
		Layout* panel = (Layout*)getControl("panel" + to_string(i));
		Button* btn = (Button*)getControl("btn", panel);
		btn->setPressedActionEnabled(false);
		btn->addClickEventListener([this, i](Object*) { talaGameLogic->onSelectPlayer(i); });

		TalaPlayerView* player = TalaPlayerView::create(this, panel, i);
        this->_layout->addChild(player, 1);
		
		players.push_back(player);
		
		player->panel_throw = (Layout*)getControl("panel_throw_" + to_string(i));
		player->panel_haphom = (Layout*)getControl("panel_haphom_" + to_string(i));
		if (i == 2) player->panel_haphom->setPositionX(player->card->getWorldPosition().x);
		if (i == 1 || i == 3) player->panel_haphom->setPositionY(player->card->getWorldPosition().y - player->panel_haphom->getContentSize().height / 2);
		player->panel_eat = (Layout*)getControl("panel_eat_" + to_string(i));
		if (i == 2) player->panel_eat->setPositionX(player->card->getWorldPosition().x);
		if (i == 1 || i == 3) player->panel_eat->setPositionY(player->card->getWorldPosition().y + deckCard->getContentSize().height * TalaCardView::SMALL_SCALE / 6);
		player->panel_card = (Layout*)getControl("panel_card_" + to_string(i));
		if (i == 2) player->panel_card->setPositionX(player->card->getWorldPosition().x);
		if (i == 1 || i == 3) player->panel_card->setPositionY(player->card->getWorldPosition().y);
	}

	auto bgInfo = getControl("bgInfo");
	roomBet = (Text*)getControl("muccuoc", bgInfo);
	roomBet->ignoreContentAdaptWithSize(true);

	actionArrow = (ImageView*)getControl("arrow", getControl("pAction"));
	drawArrow = (ImageView*)getControl("arrow", btnGroup);

	nDeck = (Text*)getControl("number", btnGroup);
	nDeck->ignoreContentAdaptWithSize(true);

	pAction = (Layout*)getControl("pAction");

	pStart = (Layout*)getControl("pStart");

	touchEnabled = true;
	touchId = -1;
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, ax::Event* event) { return this->onTouchBegan(touch, event); };
	listener->onTouchMoved = [this](Touch* touch, ax::Event* event) { this->onTouchMoved(touch, event); };
	listener->onTouchEnded = [this](Touch* touch, ax::Event* event) { this->onTouchEnded(touch, event); };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	pEffect = Layout::create();
	pEffect->setTouchEnabled(false);
	addChild(pEffect, 100);
	pClearCards = (Layout*)getControl("pClearCards");

	Size size = Director::getInstance()->getVisibleSize();
	resultGroup = new TalaResultGroup();
    resultGroup->setScale(0.8);
	this->_layout->addChild(resultGroup);
	resultGroup->setPosition(size.width * 0.5, size.height * 0.5);
	resultGroup->setLocalZOrder(10);
	loadBtnSound();
	setBackEnable(true);
}

void TalaScene::onEnterFinish()
{
	drawArrow->setPosition(_defaultPos[drawArrow]);
	drawArrow->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(0.2, { 0, 15 }),
		MoveBy::create(0.2, { 0, -15 }),
		nullptr
	)));

	actionArrow->setPosition(_defaultPos[actionArrow]);
	actionArrow->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(0.2, { 0, 15 }),
		MoveBy::create(0.2, { 0, -15 }),
		nullptr
	)));

	pEffect->removeAllChildren();
	for (auto effectCard : effectCards) {
		if (effectCard->getParent()) 
			effectCard->removeFromParent();
	}
	effectCards.clear();
	pClearCards->removeAllChildren();

	talaGameLogic->onEnterBoard();
	scheduleUpdate();
	//scheduleUpdate();
	
}

void TalaScene::onButtonRelease(ax::ui::Button * button, int id)
{
	switch (id) {
	case BTN_QUIT:
		backKeyPress();
		break;
	case BTN_XEPBAI:
		if (players[0]->isTouchEnabled())
			talaGameLogic->onArrangeCard();
            //effectRenew(2);
		break;
	case BTN_DANH: {
		if (players[0]->isTouchEnabled())
			talaGameLogic->onThrowCard();
		break;
	}
	case BTN_HABAI: {
		if (players[0]->isTouchEnabled())
			talaGameLogic->onShowSuits();
		break;
	}
	case BTN_GUIBAI:
		if (players[0]->isTouchEnabled())
			talaGameLogic->onSendCard();
		break;
	case BTN_GROUP:
		if (players[0]->isTouchEnabled())
			talaGameLogic->autoGetFromDeck();
		break;
	case BTN_START: {
		TalaPlayerInfo* info = TalaGameLogic::getInstance()->players[0];
		if (info->gold <= 3000 && TalaGameLogic::getInstance()->checkGetSupport()) {
			JNIUtils::sendEvent("get_support", "1");
			return;
		}

		if (info->gold <= 3000) {
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
                        TalaGameLogic::getInstance()->onReward(1);
                    }
				}
				else {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
					TalaGameLogic::getInstance()->onReward(1);
#endif
				}
			});
		}
		else {
			talaGameLogic->onStart();
			btnStart->setTouchEnabled(false);
			talaGameLogic->autoGenCard();
		}
		break;
	}
	case BTN_EMO:
		break;
	case BTN_SOUND:
		gameMgr->changeSound();
		loadBtnSound();
		break;
	case BTN_ADD_BOT:
		talaGameLogic->onAddBot();
		break;
	
	}
}

void TalaScene::loadBtnSound()
{
	string path = "GameTala/";
	string resource = gameMgr->getSetting().sound == 1 ? (path + "btnSound.png") : (path + "btnSoundOff.png");
	btnSound->loadTextures(resource, resource, resource);
}

void TalaScene::onExit()
{
	BaseLayer::onExit();
	talaGameLogic->onExitBoard();
}

void TalaScene::backKeyPress()
{
	
	if (!talaGameLogic->isPlaying()) {
		sceneMgr->openScene(TalaLobbyScene::className);
        JNIUtils::showAds(1);
	}
	else {
		string message = LocalizedString::to("QUIT_GAME");
		int bet = 6 * 1000;
		message = StringUtility::replaceAll(message, "@gold", to_string(bet));
		sceneMgr->showOkCancelDialog(message, [this](int buttonId) {
			if (buttonId == Dialog::BTN_OK) {
				int bet = 6 * 1000;
				TalaGameLogic::getInstance()->players[0]->setGold(TalaGameLogic::getInstance()->players[0]->gold - bet);
				sceneMgr->openScene(TalaLobbyScene::className);
                JNIUtils::showAds(1);
				if (TalaGameLogic::getInstance()->countGame >= 2) {
                    if (gameMgr->useAds)
					    JNIUtils::showAdsFull();
					TalaGameLogic::getInstance()->countGame = 0;
				}
			}
			else {

			}
		});
	}
}


void TalaScene::clearRoomInfo()
{
	updateJackpot();
	updateBigBet();
	updateQuitReg();
	setTouchEnabled(false);
	updateStart(false);
	updateAction();
	updateWait();
	pEffect->removeAllChildren();
	pClearCards->removeAllChildren();
	resultGroup->setVisible(false);
	for (auto player : players)
		player->clearInfo();
}


void TalaScene::updateRoomInfo()
{
	//roomBet->setString(StringUtility::formatNumberSymbol(talaGameLogic->roomBet));
}

void TalaScene::updateRoomOwner()
{
}

void TalaScene::updateQuitReg()
{
}

void TalaScene::updateJackpot()
{
}

void TalaScene::updateDeckCard()
{
	nDeck->setString((talaGameLogic->nDeckCard < 10 ? "0" : "") + to_string(talaGameLogic->nDeckCard));
	if (talaGameLogic->nDeckCard <= 0) {
		btnGroup->setVisible(false);
	}
}

void TalaScene::updateAction()
{
	if (!talaGameLogic->isPlaying()) {
		pAction->setVisible(false);
		btnGroup->setVisible(false);
		return;
	}

	pAction->setVisible(talaGameLogic->players[0]->status == TalaPlayerInfo::STATUS_PLAYING);
	btnDanh->setVisible(talaGameLogic->players[0]->state == TalaPlayerInfo::STATE_DANHBAI);
	btnHaBai->setVisible(talaGameLogic->players[0]->state == TalaPlayerInfo::STATE_HABAI);
	btnGuiBai->setVisible(talaGameLogic->players[0]->state == TalaPlayerInfo::STATE_GUIBAI);

	actionArrow->stopAllActions();
	if (btnDanh->isVisible() || btnHaBai->isVisible() || btnGuiBai->isVisible()) {
		actionArrow->setVisible(true);
		actionArrow->setPosition(_defaultPos[actionArrow]);
		actionArrow->runAction(RepeatForever::create(Sequence::create(
			MoveBy::create(0.2, { 0, 15 }),
			MoveBy::create(0.2, { 0, -15 }),
			nullptr
		)));
	}
	else actionArrow->setVisible(false);

	if (talaGameLogic->nDeckCard > 0) {
		btnGroup->setVisible(true);
		btnGroup->setTouchEnabled(talaGameLogic->players[0]->status == TalaPlayerInfo::STATUS_PLAYING && talaGameLogic->players[0]->state == TalaPlayerInfo::STATE_BOCBAI);
		btnGroup->stopAllActions();
		drawArrow->stopAllActions();
		if (btnGroup->isTouchEnabled()) {
			drawArrow->setVisible(true);
			drawArrow->setPosition(_defaultPos[drawArrow]);
			drawArrow->runAction(RepeatForever::create(Sequence::create(
				MoveBy::create(0.2, { 0, 15 }),
				MoveBy::create(0.2, { 0, -15 }),
				nullptr
			)));
		}
		else drawArrow->setVisible(false);

		auto opacity = 150;
		for (auto player : talaGameLogic->players)
			if (player->status == TalaPlayerInfo::STATUS_PLAYING && player->state == TalaPlayerInfo::STATE_BOCBAI) {
				opacity = 255;
				break;
			}
		btnGroup->runAction(FadeTo::create(0.25, opacity));
	}
}

void TalaScene::updateStart(bool countdown, char time)
{
	pStart->setVisible(countdown);
	pStart->stopAllActions();
	if (pStart->getUserData()) {
		delete pStart->getUserData();
		pStart->setUserData(nullptr);
	}
}

void TalaScene::updateWait()
{
	
}

void TalaScene::updateBigBet(bool animate)
{
	
}

void TalaScene::updateUserInfo(char chair)
{
	if (chair >= 0 && chair < players.size())
	{
		players[chair]->updateUserInfo();
	}
}

void TalaScene::updateGameInfo(char chair)
{
	if (chair >= 0 && chair < players.size())
		players[chair]->updateGameInfo();
}

void TalaScene::updateIP()
{
}

void TalaScene::updateTimer(char chair, char time)
{
	if (chair >= 0 && chair < players.size())
		players[chair]->effectTime(time);
}

void TalaScene::effectRenew(char chair) {
    if (chair >= 0 && chair < players.size())
        players[chair]->effectRenew();
}

void TalaScene::effectMoreTurn(char chair)
{
	auto name = "rank" + to_string(chair);
	if (pEffect->getChildByName(name))
		pEffect->removeChildByName(name);

	auto node = Node::create();
	node->setCascadeOpacityEnabled(true);
	node->setScale(0.5);
	node->setOpacity(0);
	node->setPosition(players[chair]->getAvatarPosition());
	pEffect->addChild(node, 0, name);
	node->runAction(Sequence::create(
		Spawn::create(
			EaseBackOut::create(ScaleTo::create(0.5, 1)),
			FadeIn::create(0.5), nullptr
		),
		DelayTime::create(2),
		Spawn::create(
			EaseBackIn::create(ScaleTo::create(0.5, 0.5)),
			FadeOut::create(0.5), nullptr
		),
		RemoveSelf::create(),
		nullptr
	));

	auto light = Sprite::create("common/rank/nenThang.png");
	light->setScale(0.55);
	node->addChild(light);
	light->runAction(RepeatForever::create(RotateBy::create(3, 360)));

	auto bg = Sprite::create("common/rank/bgU.png");
	bg->setScale(0.325);
	node->addChild(bg);

	auto img = Sprite::create("common/rank/tailuot.png");
	img->setScale(0.8);
	node->addChild(img);
}

void TalaScene::effectRank(char chair, char rank, float time)
{
    runAction(Sequence::create(
        DelayTime::create(time),
        CallFunc::create([this, chair, rank]() {
            players[chair]->showEffectRank(rank);
        }),
        nullptr));
	
}

void TalaScene::effectMyRank(char rank, float time)
{
    runAction(Sequence::create(
        DelayTime::create(time),
        CallFunc::create([this, rank]() {
            JNIUtils::vibrate(50);
            resultGroup->showMauBinh(rank);
            TalaGameSound::playEffect(rank == TalaGameLogic::Rank::RANK_NHAT ? TalaInGameMgr::SOUND_RANK_WIN : TalaInGameMgr::SOUND_RANK_LOSE);
        }),
        nullptr));
}

void TalaScene::effectMoney(char chair, long long money, float delayTime)
{
	auto name = "money" + to_string(chair);
	if (pEffect->getChildByName(name))
		pEffect->removeChildByName(name);

	auto node = Node::create();
	pEffect->addChild(node, 10, name);

	string str = to_string(abs(money));
	string path = money >= 0 ? "bosothang/" : "bosothua/";
	float width = 0, height = 0;
	auto sign = Sprite::create(path + "sign.png");
	sign->setPositionX(width + sign->getContentSize().width / 2);
	sign->setAnchorPoint({ 0.5, 0.5 });
	node->addChild(sign);
	width += sign->getContentSize().width + 2;
	for (int i = 0; i < str.length(); i++) {
		if (i != 0 && (str.length() - i) % 3 == 0) {
			auto dot = Sprite::create(path + "dot.png");
			dot->setPosition(width + dot->getContentSize().width / 2, -height / 2 + dot->getContentSize().height / 2);
			dot->setAnchorPoint({ 0.5, 0.5 });
			node->addChild(dot);
			width += dot->getContentSize().width + 1;
		}

		auto num = Sprite::create(path + "so" + str[i] + ".png");
		num->setPositionX(width + num->getContentSize().width / 2);
		num->setAnchorPoint({ 0.5, 0.5 });
		node->addChild(num);
		width += num->getContentSize().width;
		height = num->getContentSize().height;
		if (i != str.length() - 1) width += 1;
	}

	Vec2 pos;
	float scale = 1;
	Vec2 avatarPos = players[chair]->getAvatarPosition();
	switch (chair) {
	case 0:
	case 1:
		pos = { avatarPos.x + 75, avatarPos.y - 30 };
		break;
	case 2:
	case 3:
		pos = { avatarPos.x - 75 - width * scale , avatarPos.y - 30 };
		break;
	}

	node->setPosition(pos);
	node->setCascadeOpacityEnabled(true);
	node->setOpacity(0);
	node->setScale(scale);
	node->runAction(Sequence::create(
        DelayTime::create(delayTime),
		Spawn::create(
			EaseSineOut::create(MoveBy::create(0.5, { 0, 30 })),
			FadeIn::create(0.5),
			nullptr
		),
		DelayTime::create(3),
		Spawn::create(
			EaseSineOut::create(MoveBy::create(0.5, { 0, 30 })),
			FadeOut::create(0.5),
			nullptr
		),
		RemoveSelf::create(),
		nullptr
	));
	updateUserInfo(chair);
}

void TalaScene::effectDenTien(char chair)
{
	auto name = "rank" + to_string(chair);
	if (pEffect->getChildByName(name))
		pEffect->removeChildByName(name);

	auto node = Node::create();
	node->setCascadeOpacityEnabled(true);
	node->setPosition(players[chair]->getAvatarPosition());
	pEffect->addChild(node, 0, name);

	/*auto anim = DBCCFactory::getInstance()->buildArmatureNode("Bet");
	if (anim) {
		node->addChild(anim);
		anim->getAnimation()->gotoAndPlay("2", -1, -1, 1);
	}*/
}

void TalaScene::effectAnChot()
{
	
}

void TalaScene::effectJackpot()
{
	
}

void TalaScene::effectBigBet(char chair)
{

}

void TalaScene::clearEffectRank()
{
    ((Layout*)getControl("pCard"))->setLocalZOrder(0);
	if (pEffect->getChildByName("myrank")) {
		auto node = pEffect->getChildByName("myrank");
		node->stopAllActions();
		node->runAction(Sequence::create(
			Spawn::create(
				EaseBackIn::create(ScaleTo::create(0.5, node->getScale() / 2)),
				FadeOut::create(0.5),
				nullptr
			),
			RemoveSelf::create(),
			nullptr
		));
	}

	for (int i = 0; i < players.size(); i++) {
        players[i]->bgScore->setVisible(false);
		if (pEffect->getChildByName("rank" + to_string(i))) {
			auto node = pEffect->getChildByName("rank" + to_string(i));
			node->stopAllActions();
			node->runAction(Sequence::create(
				Spawn::create(
					EaseBackIn::create(ScaleTo::create(0.5, node->getScale() / 2)),
					FadeOut::create(0.5),
					nullptr
				),
				RemoveSelf::create(),
				nullptr
			));
		}
	}
}

void TalaScene::effectDealCards(bool isFirstTurn)
{
	int numCards = isFirstTurn ? CARDS_FIRST_TURN : CARDS_PER_PLAYER;
	auto cardPanelSize = players[0]->getContentSize();
	auto cardSize = deckCard->getContentSize();

	float maxWidth = (2 * numCards + 1) * cardSize.width / 3;
	float offset = maxWidth > cardPanelSize.width ? 0 : (cardPanelSize.width - maxWidth) / 2;
	float delta = maxWidth > cardPanelSize.width ? (cardPanelSize.width - cardSize.width) / (numCards - 1) : 2 * cardSize.width / 3;

	for (int i = 0; i < players.size(); i++) {
		if (talaGameLogic->players[i]->status == TalaPlayerInfo::STATUS_PLAYING) {
			for (int j = 0; j < numCards; j++) {
				string s = gameMgr->typeCard == 0 ? "cards/labai_52.png" : "cards/labai1_52.png";
				auto effectCard = Sprite::create(s);
				effectCard->setPosition(btnGroup->getPositionX(), btnGroup->getPositionY() - j * 1.5);
				effectCard->setRotation(90);
				effectCard->setOpacity(150);
				effectCard->setScale(TalaCardView::SMALL_SCALE);
				effectCard->setVisible(false);

				if (i == 0) {
					effectCard->setPosition(players[0]->convertToNodeSpace(effectCard->getPosition()));
					effectCards.push_back(effectCard);
					players[0]->addChild(effectCard);

					effectCard->runAction(Sequence::create(
						DelayTime::create(j * 0.1),
						Show::create(),
						Spawn::create(
							MoveTo::create(0.25, { offset + delta * j + cardSize.width / 2, cardPanelSize.height / 2 }),
							RotateTo::create(0.25, 0),
							FadeIn::create(0.25),
							ScaleTo::create(0.25, 1),
							nullptr
						),
						nullptr
					));
				}
				else {
					pEffect->addChild(effectCard);
					effectCard->runAction(Sequence::create(
						DelayTime::create(j * 0.1),
						Show::create(),
						Spawn::create(
							MoveTo::create(0.25, players[i]->card->getWorldPosition()),
							RotateTo::create(0.25, 0),
							FadeIn::create(0.25),
							nullptr
						),
						RemoveSelf::create(),
						nullptr
					));
				}
			}
		}
	}
	runAction(
		Sequence::create(
			DelayTime::create(1.0),
			CallFunc::create(AX_CALLBACK_0(TalaScene::effectShowCards, this)),
			NULL
		)
	);
}

void TalaScene::effectShowCards()
{
	for (auto cardId : talaGameLogic->players[0]->handOnCards) {
		auto card = TalaCardView::create(cardId);
		players[0]->addChild(card);
		players[0]->handOnCards.pushBack(card);
	}
	players[0]->updateHandOnCards(0);
	players[0]->setTouchEnabled(false);

	for (int i = 0; i < effectCards.size(); i++) {
		auto effectCard = effectCards[i];
		effectCard->runAction(Sequence::create(
			DelayTime::create(i * 0.05),
			ScaleTo::create(0.1, 0, 1),
			RemoveSelf::create(),
			nullptr
		));

		auto card = players[0]->handOnCards.at(i);
		card->setScaleX(0);
		card->runAction(Sequence::create(
			DelayTime::create(0.1 + i * 0.05),
			CallFunc::create([this, i]() {
				
			}),
			ScaleTo::create(0.1, 1, 1),
			CallFunc::create([this, i]() {
				if (i == players[0]->handOnCards.size() - 1) players[0]->setTouchEnabled(true);
			}),
			nullptr
		));
	}

	effectCards.clear();
}

void TalaScene::effectThrowCard(char chair, char cardId)
{
	TalaCardView *throwCard;
	if (chair == 0) {
		for (int i = 0; i < players[0]->handOnCards.size(); i++) {
			throwCard = players[0]->handOnCards.at(i);
			if (throwCard->id == cardId) {
				players[0]->handOnCards.eraseObject(throwCard);
				switchParent(throwCard, players[0], players[0]->panel_throw);
				break;
			}
		}
		players[0]->updateHandOnCards();
	}
	else {
		throwCard = TalaCardView::create(cardId);
		throwCard->setScale(TalaCardView::SMALL_SCALE);
		throwCard->setPosition(players[chair]->panel_throw->convertToNodeSpace(players[chair]->card->getWorldPosition()));
		players[chair]->panel_throw->addChild(throwCard);
	}

	players[chair]->throwCards.pushBack(throwCard);
	players[chair]->updateThrowCards();
}

void TalaScene::effectReceiveCardFromDeck(char chair, char cardId)
{
	if (chair == 0) {
		auto card = TalaCardView::create(cardId);
		card->setScale(TalaCardView::SMALL_SCALE);
		card->setPosition(players[0]->convertToNodeSpace(btnGroup->convertToWorldSpace(_defaultPos[deckCard])));
		players[0]->addChild(card);
		players[0]->handOnCards.pushBack(card);
		players[0]->updateHandOnCards();
	}
	else {
		string s = gameMgr->typeCard == 0 ? "cards/labai_52.png" : "cards/labai1_52.png";
		auto effectCard = Sprite::create(s);
		effectCard->setScale(TalaCardView::SMALL_SCALE);
		effectCard->setPosition(btnGroup->convertToWorldSpace(_defaultPos[deckCard]));
		effectCard->setOpacity(150);
		pEffect->addChild(effectCard);

		effectCard->runAction(Sequence::create(
			Spawn::create(
				EaseSineInOut::create(MoveTo::create(0.25, players[chair]->card->getWorldPosition())),
				FadeIn::create(0.25),
				nullptr
			),
			RemoveSelf::create(),
			nullptr
		));
	}
}

void TalaScene::effectReceiveCardFromOther(char srcChair, char desChair)
{
	auto srcPlayer = players[srcChair];
	auto desPlayer = players[desChair];
	auto throwCard = srcPlayer->throwCards.at(srcPlayer->throwCards.size() - 1);
	srcPlayer->throwCards.eraseObject(throwCard);
	throwCard->showEaten(true);
	throwCard->setDark(false);
	throwCard->showArrow(false);
	throwCard->showEatable(false);

	if (desChair == 0) {
		switchParent(throwCard, srcPlayer->panel_throw, desPlayer);
		desPlayer->handOnCards.pushBack(throwCard);
		effectArrangeCard();
        JNIUtils::vibrate(20);
	}
	else {
		switchParent(throwCard, srcPlayer->panel_throw, desPlayer->panel_eat);
		desPlayer->eatenCards.pushBack(throwCard);
		desPlayer->updateEatenCards();
	}
}

void TalaScene::effectMoveThrowCard(char srcChair, char desChair)
{
	auto throwCard = players[srcChair]->throwCards.at(players[srcChair]->throwCards.size() - 1);
	players[srcChair]->throwCards.eraseObject(throwCard);
	switchParent(throwCard, players[srcChair]->panel_throw, players[desChair]->panel_throw);
	players[desChair]->throwCards.pushBack(throwCard);

	players[srcChair]->updateThrowCards();
	players[desChair]->updateThrowCards();
}

void TalaScene::effectShowPhom(char chair, bool isU)
{
    if (isU)
    {
        ((Layout*)getControl("pCard"))->setLocalZOrder(2);
    }
	vector<char> phoms;
    JNIUtils::vibrate(20);
    JNIUtils::setString("effectShowPhom ", to_string(chair).c_str());
	if (chair == 0) {
		for (int i = 0; i < talaGameLogic->players[0]->listPhom.size(); i++) {
			if (i < players[0]->listPhom.size()) continue;
			players[0]->listPhom.push_back({});
			phoms.push_back(i);
			auto phom = talaGameLogic->players[0]->listPhom[i];
			for (int j = 0; j < phom.size(); j++) {
				TalaCardView *card = nullptr;
				for (int k = 0; k < players[chair]->handOnCards.size(); k++) {
					if (phom[j] == players[chair]->handOnCards.at(k)->id) {
						card = players[chair]->handOnCards.at(k);
						players[chair]->handOnCards.erase(k);
						switchParent(card, players[0], players[0]->panel_haphom);
						break;
					}
				}
                if (!card) {
                    JNIUtils::setString("effectShowPhom Card", "null");
                }
                
				players[0]->listPhom[i].pushBack(card);
			}
		}
        JNIUtils::setString("effectShowPhom state 2", "1");
		players[0]->updateHandOnCards();
	}
	else {
		for (int i = 0; i < talaGameLogic->players[chair]->listPhom.size(); i++) {
			if (i < players[chair]->listPhom.size()) continue;
			players[chair]->listPhom.push_back({});
			phoms.push_back(i);
			auto phom = talaGameLogic->players[chair]->listPhom[i];
			for (int j = 0; j < phom.size(); j++) {
				TalaCardView *card = nullptr;
				for (int k = 0; k < players[chair]->eatenCards.size(); k++) {
					if (phom[j] == players[chair]->eatenCards.at(k)->id) {
						card = players[chair]->eatenCards.at(k);
						players[chair]->eatenCards.erase(k);
						switchParent(card, players[chair]->panel_eat, players[chair]->panel_haphom);
						break;
					}
				}
				if (!card) {
					card = TalaCardView::create(phom[j]);
					card->setPosition(players[chair]->panel_haphom->convertToNodeSpace(players[chair]->card->getWorldPosition()));
					players[chair]->panel_haphom->addChild(card);
				}
				players[chair]->listPhom[i].pushBack(card);
			}
		}
        JNIUtils::setString("effectShowPhom state 3", "1");
		players[chair]->updateEatenCards();
	}
    JNIUtils::setString("effectShowPhom state 4", "1");
    if (isU)
		players[chair]->updatePhomCardsU();
	else
		players[chair]->updatePhomCards();
    JNIUtils::setString("effectShowPhom state 5", "1");
	//effect star when show new phom
	/*for (auto phomIdx : phoms) {
		auto node = Node::create();
		pEffect->addChild(node);

		node->runAction(Sequence::create(
			DelayTime::create(0.25),
			CallFunc::create([this, node, chair, phomIdx]() {
				auto phom = players[chair]->listPhom[phomIdx];
				auto posA = players[chair]->panel_haphom->convertToWorldSpace(phom.at(0)->getPosition());
				auto posB = players[chair]->panel_haphom->convertToWorldSpace(phom.at(phom.size() - 1)->getPosition());
				auto pos = (posA + posB) / 2;

				node->setPosition(pos);
			}),
			DelayTime::create(3),
			nullptr
		));
	}*/
}

void TalaScene::effectSendCard(char srcChair, char desChair, char cardId)
{
    JNIUtils::vibrate(10);
	TalaCardView *card;
	if (srcChair == 0) {
		auto selectedCards = talaGameLogic->players[0]->selectedCards;
		for (int i = 0; i < players[0]->handOnCards.size(); i++) {
			card = players[0]->handOnCards.at(i);
			if (card->id == cardId) {
				card->showArrow(false);
				players[0]->handOnCards.erase(i);
				switchParent(card, players[0], players[desChair]->panel_haphom);
				break;
			}
			else card->showArrow(find(selectedCards.begin(), selectedCards.end(), card->id) != selectedCards.end());
		}
		players[0]->updateHandOnCards();
	}
	else {
		card = TalaCardView::create(cardId);
		card->setScale(TalaCardView::SMALL_SCALE);
		card->setPosition(players[desChair]->panel_haphom->convertToNodeSpace(players[srcChair]->card->getWorldPosition()));
		players[desChair]->panel_haphom->addChild(card);
	}

	for (int i = 0; i < talaGameLogic->players[desChair]->listPhom.size(); i++) {
		auto phom = talaGameLogic->players[desChair]->listPhom[i];
		int index = -1;
		for (int j = 0; j < phom.size(); j++) {
			if (phom[j] == cardId) {
				index = j;
				break;
			}
		}
		if (index != -1) {
			players[desChair]->listPhom[i].insert(index, card);
			break;
		}
	}
	players[desChair]->updatePhomCards();
}

void TalaScene::effectArrangeCard()
{
	for (auto cardId : talaGameLogic->players[0]->handOnCards) {
		for (auto card : players[0]->handOnCards) {
			if (card->id == cardId) {
				players[0]->handOnCards.eraseObject(card);
				players[0]->handOnCards.pushBack(card);
				break;
			}
		}
	}
	players[0]->updateHandOnCards();
}

void TalaScene::effectHintSendCard()
{
    JNIUtils::vibrate(5);
	auto selectedCards = talaGameLogic->players[0]->selectedCards;
	for (auto card : players[0]->handOnCards)
		card->showArrow(find(selectedCards.begin(), selectedCards.end(), card->id) != selectedCards.end());
}

void TalaScene::effectShowCardsOther(char chair, bool dark, float delayTime)
{
   
    runAction(Sequence::create(
        DelayTime::create(delayTime),
        CallFunc::create([this, chair, dark]() {
            TalaGameSound::playEffect(TalaInGameMgr::SOUND_SHOW_SUIT);
            players[chair]->showScore(talaGameLogic->players[chair]->score);
            if (chair == 0)
            {
                return;
            }
            for (auto cardId : talaGameLogic->players[chair]->handOnCards)
            {
                auto card = TalaCardView::create(cardId);
                card->setPosition(players[chair]->panel_card->convertToNodeSpace(players[chair]->card->getWorldPosition()));
                card->setScale(TalaCardView::SMALL_SCALE);
                card->setDark(dark);
                players[chair]->panel_card->addChild(card);
                players[chair]->handOnCards.pushBack(card);
            }
            players[chair]->updateHandOnCards();
            
        }),
        nullptr));
}

void TalaScene::effectMoveCard(char oldIdx, char newIdx)
{
	if (oldIdx != newIdx) {
		auto card = players[0]->handOnCards.at(oldIdx);
		players[0]->handOnCards.eraseObject(card);
		players[0]->handOnCards.insert((oldIdx < newIdx ? newIdx - 1 : newIdx), card);
	}
	players[0]->updateHandOnCards(0.05);
}

void TalaScene::updateHandOnCards(float duration, bool resetTouch)
{
	players[0]->updateHandOnCards(duration, resetTouch);
}

void TalaScene::effectEatableCard(char chair, bool show)
{
	if (players[chair]->throwCards.size() > 0) {
		auto card = players[chair]->throwCards.at(players[chair]->throwCards.size() - 1);
		card->showArrow(show);
		card->showEatable(show);
		if (show) card->setDark(false);
	}
}

void TalaScene::effectDarkThrowCards(char chair)
{
	for (auto card : players[chair]->throwCards)
		card->setDark(true, true);
}

void TalaScene::effectHintSuit(char chair, char suitIndex)
{
	if (suitIndex < 0 || suitIndex >= players[chair]->listPhom.size()) {
		for (auto &suit : players[chair]->listPhom)
			suit.at((suit.size() - 1) / 2)->showArrow(false);
	}
	else {
		auto suit = players[chair]->listPhom[suitIndex];
		suit.at((suit.size() - 1) / 2)->showArrow(true);
	}
}

void TalaScene::effectDarkAllCards()
{
	for (auto player : players)
		player->effectDarkAllCards();
}

void TalaScene::effectClearAllCards()
{
	vector<TalaCardView*> allCards;
	for (auto player : players) {
		for (auto card : player->handOnCards) {
			switchParent(card, card->getParent(), pClearCards);
			allCards.push_back(card);
		}
		for (auto card : player->eatenCards) {
			switchParent(card, card->getParent(), pClearCards);
			allCards.push_back(card);
		}
		for (auto card : player->throwCards) {
			switchParent(card, card->getParent(), pClearCards);
			allCards.push_back(card);
		}
		for (auto phom : player->listPhom) {
			for (auto card : phom) {
				switchParent(card, card->getParent(), pClearCards);
				allCards.push_back(card);
			}
		}

		player->clearAllCards();
	}
	for (auto card : allCards)
		card->effectClear();
}

void TalaScene::updateAllCards()
{
	for (auto player : players) {
		auto info = talaGameLogic->players[player->index];
		if (info->status != TalaPlayerInfo::STATUS_PLAYING) continue;

		//update throw cards
		for (auto cardId : info->throwCards) {
			auto card = TalaCardView::create(cardId);
			card->setDark(true);
			player->panel_throw->addChild(card);
			player->throwCards.pushBack(card);
		}
		player->updateThrowCards(0);

		//update eaten cards
		if (player->index == 0) {
			for (auto cardId : info->handOnCards) {
				auto card = TalaCardView::create(cardId);
				card->showEaten(find(info->eatenCards.begin(), info->eatenCards.end(), cardId) != info->eatenCards.end());
				player->addChild(card);
				player->handOnCards.pushBack(card);
			}
			player->updateHandOnCards(0);
		}
		else {
			for (auto cardId : info->eatenCards) {
				auto card = TalaCardView::create(cardId);
				card->showEaten(true);
				player->panel_eat->addChild(card);
				player->eatenCards.pushBack(card);
			}
			player->updateEatenCards(0);
		}

		//update list phom
		auto listPhom = info->listPhom;
		for (auto phom : info->listPhom) {
			ax::Vector<TalaCardView*> cards;
			for (auto cardId : phom) {
				auto card = TalaCardView::create(cardId);
				player->panel_haphom->addChild(card);
				cards.pushBack(card);
			}
			player->listPhom.push_back(cards);
		}
		player->updatePhomCards(0);
	}
}

bool TalaScene::onTouchBegan(Touch * touch, ax::Event * event)
{
	if (touchId == -1 && touchEnabled) {
		touchId = touch->getID();
		isTouchMoved = false;
		return true;
	}

	touchId = -1;
	return false;
}

void TalaScene::onTouchMoved(Touch * touch, ax::Event * event)
{
	if (!touchEnabled || touch->getID() != touchId) {
		if (!touchEnabled) touchId = -1;
		return;
	}
	if (!isTouchMoved) {
		auto startPos = touch->getStartLocation();
		auto curPos = touch->getLocation();
		if ((curPos.x - startPos.x) * (curPos.x - startPos.x) + (curPos.y - startPos.y) * (curPos.y - startPos.y) >= 10)
			isTouchMoved = true;
	}
}

void TalaScene::onTouchEnded(Touch * touch, ax::Event * event)
{
	if (!touchEnabled || touch->getID() != touchId) {
		if (!touchEnabled) touchId = -1;
		return;
	}

	if (!isTouchMoved) {
		for (auto player : players) {
			if (player->isTouchLastThrowCard(touch->getLocation()))
				talaGameLogic->onTouchLastThrowCard(player->index);
			auto touchSuitIndex = player->getTouchSuitIndex(touch->getLocation());
			if (touchSuitIndex >= 0) 
				talaGameLogic->onTouchSuit(player->index, touchSuitIndex);
			
		}
	}
	
	touchId = -1;
}

void TalaScene::setTouchEnabled(bool enabled)
{
	touchEnabled = enabled;
	if (!touchEnabled) touchId = -1;
}

void TalaScene::switchParent(Node * child, Node * oldParent, Node * newParent)
{
	child->setPosition(newParent->convertToNodeSpace(oldParent->convertToWorldSpace(child->getPosition())));
	child->retain();
	oldParent->removeChild(child);
	newParent->addChild(child);
	child->release();
}


void TalaScene::update(float delta)
{
	TalaGameLogic::getInstance()->update(delta);
}

void TalaScene::updateAvatar()
{
	players[0]->updateLevel();
}

const std::string TalaScene::className = "TalaScene";
