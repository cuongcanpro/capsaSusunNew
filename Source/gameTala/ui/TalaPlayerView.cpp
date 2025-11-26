#include "TalaPlayerView.h"
#include "TalaScene.h"
#include "app/Constant.h"
#include "gameTala/logic/TalaGameLogic.h"
#include "core/utils/TalaGameSound.h"
#include "gameTala/TalaInGameMgr.h"

TalaPlayerView * TalaPlayerView::create(TalaScene * gameScene, Layout * panel, int index)
{
	auto view = new TalaPlayerView();
	view->init(gameScene, panel, index);
	view->autorelease();
	return view;
}

TalaPlayerView::TalaPlayerView()
{
}

TalaPlayerView::~TalaPlayerView()
{
}

bool TalaPlayerView::init(TalaScene * gameScene, Layout * panel, int index)
{
	Layer::init();

	this->gameScene = gameScene;
	this->_layout = panel;
	this->index = index;

	initGUI();
	return true;
}

void TalaPlayerView::initGUI()
{
    bgScore = (ImageView*)getControl("bgScore");
    lbScore = (Text*)getControl("lbScore");
	name = (Text*)getControl("name");
	gold = (Text*)getControl("gold");
	gold->ignoreContentAdaptWithSize(true);

	nen = (Sprite*)_layout->getChildByName("nen");

	avatar = (ImageView*)_layout->getChildByName("avatar");
	
	state = _layout->getChildByName("state");
	state->setLocalZOrder(20);

	borderAvatar = (ImageView*)_layout->getChildByName("border");

	auto sprite = Sprite::create("GameTala/borderTime.png");
	sprite->setColor(Color3B::GREEN);
	timer = ProgressTimer::create(sprite);
	timer->setType(ProgressTimer::Type::RADIAL);
	timer->setReverseDirection(true);
	//timer->setPosition(mask->getContentSize().width / 2, mask->getContentSize().height / 2);
	timer->setPercentage(100);
	timer->setScale(0.9);
	_layout->addChild(timer, 1);

	moveCard = nullptr;
	card = nullptr;
	touchEnabled = false;
	touchId = -1;
	touchIndex = -1;
	cardPanel = nullptr;
	if (index == 0) {	//self
		cardPanel = (Layout*)getControl("card_panel");
		setPosition(cardPanel->getWorldPosition());
		setContentSize({ cardPanel->getContentSize().width + WIN_SIZE.width - CONSTANT_WIDTH, cardPanel->getContentSize().height });
		TalaCardView::START_Y = cardPanel->getContentSize().height / 2;
		this->cardPanel->setVisible(false);

		touchEnabled = true;
		touchId = -1;
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch* touch, ax::Event* event) { return this->onTouchBegan(touch, event); };
		listener->onTouchMoved = [this](Touch* touch, ax::Event* event) { this->onTouchMoved(touch, event); };
		listener->onTouchEnded = [this](Touch* touch, ax::Event* event) { this->onTouchEnded(touch, event); };
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		moveCard = TalaCardView::create(NUM_CARD);
		moveCard->setVisible(false);
		moveCard->setOpacity(100);
		gameScene->addChild(moveCard, 100);

		ImageView* bgProgress = (ImageView*)_layout->getChildByName("bgProgress");
		lbLevel = (Text*)bgProgress->getChildByName("lbLevel");
		progress = (LoadingBar*)bgProgress->getChildByName("progress");
	}
	else card = (ImageView*)getControl("card");

	resultGroup = new TalaResultGroup();
	this->_layout->addChild(resultGroup);
	resultGroup->setPosition(nen->getPosition());
	resultGroup->setScale(0.35);
	resultGroup->setLocalZOrder(10);
    int idAvatar = AXRANDOM_0_1() * 41.99999;
    avatar->loadTexture("images1/avatar_" + to_string(idAvatar) + ".png");
}

void TalaPlayerView::onEnter()
{
	Layer::onEnter();

	if (index == 0) {
		
	}
}

bool TalaPlayerView::onTouchBegan(Touch * touch, ax::Event * event)
{
	if (touchId == -1 && touchEnabled && index == 0) {
		for (int i = handOnCards.size() - 1; i >= 0; i--) {
			if (handOnCards.at(i)->isVisible() && handOnCards.at(i)->containTouchPoint(touch->getLocation())) {
                touchId = touch->getID();
                isTouchMoved = false;
				touchIndex = i;
				return true;
			}
		}
	}
	
	return false;
}

void TalaPlayerView::onTouchMoved(Touch * touch, ax::Event * event)
{
	if (!touchEnabled || touch->getID() != touchId) {
		if (!touchEnabled) touchId = -1;
		return;
	}
	auto startPos = touch->getStartLocation();
	auto curPos = touch->getLocation();
	Vec2 delta(curPos.x - startPos.x, curPos.y - startPos.y);
	if (!isTouchMoved) {
		if (delta.x * delta.x + delta.y * delta.y >= 10) {
			isTouchMoved = true;
			talaGameLogic->onBeginMoveCard();
		}
	}
	if (isTouchMoved) {
		if (touchIndex >= 0 && touchIndex < handOnCards.size()) {
			auto card = handOnCards.at(touchIndex);
			moveCard->setID(card->id);
			moveCard->setVisible(true);
			card->setVisible(false);
			moveCard->setPosition(convertToWorldSpace(card->getPosition()) + delta);

			if (handOnCards.size() <= 1) return;
			float distance = handOnCards.at(1)->getPositionX() - handOnCards.at(0)->getPositionX();
			for (int i = 0; i < handOnCards.size(); i++) {
				if (i == touchIndex) continue;
				auto card = handOnCards.at(i);
				float startX = convertToWorldSpace({ card->getPositionX() - card->getContentSize().width / 2, 0 }).x;
				float endX = startX + distance;
				if (i == 0) card->setDark(curPos.x < endX);
				else if (i == handOnCards.size() - 1) card->setDark(curPos.x >= startX);
				else card->setDark(curPos.x >= startX && curPos.x < endX);
			}
		}
	}
}

void TalaPlayerView::onTouchEnded(Touch * touch, ax::Event * event)
{
	if (!touchEnabled || touch->getID() != touchId) {
		if (!touchEnabled) touchId = -1;
		return;
	}

	if (!isTouchMoved) {
		for (int i = handOnCards.size() - 1; i >= 0; i--) {
			if (handOnCards.at(i)->isVisible() && handOnCards.at(i)->containTouchPoint(touch->getLocation())) {
				talaGameLogic->onSelectCard(handOnCards.at(i)->id);
				break;
			}
		}
	}
	else {
		auto curPos = touch->getLocation();
		if (touchIndex >= 0 && touchIndex < handOnCards.size()) {
			auto card = handOnCards.at(touchIndex);
			moveCard->setVisible(false);
			card->setVisible(true);

			auto newIndex = touchIndex;
			if (handOnCards.size() > 1) {
				float distance = handOnCards.at(1)->getPositionX() - handOnCards.at(0)->getPositionX();
				for (int i = 0; i < handOnCards.size(); i++) {
					if (i == touchIndex) continue;
					auto card = handOnCards.at(i);
					float startX = convertToWorldSpace({ card->getPositionX() - card->getContentSize().width / 2, 0 }).x;
					float endX = startX + distance;
					if (i == 0) {
						if (curPos.x < endX) {
							newIndex = 1;
							break;
						}
					}
					else if (i == handOnCards.size() - 1) {
						if (curPos.x >= startX) {
							newIndex = handOnCards.size();
							break;
						}
					}
					else if (curPos.x >= startX && curPos.x < endX) {
						newIndex = i + 1;
						break;
					}
				}
			}

			card->setPosition(convertToNodeSpace(moveCard->getPosition()));
			talaGameLogic->onEndMoveCard(touchIndex, newIndex);
		}
	}

	touchId = -1;
}

void TalaPlayerView::clearInfo()
{
	setVisible(false);
	setTouchEnabled(false);

	state->removeAllChildren();
	effectTime(0);

	clearAllCards();
    bgScore->setVisible(false);
}

void TalaPlayerView::updateUserInfo()
{
	auto info = talaGameLogic->players[index];
	
	//avatar->asyncExecuteWithUrl(to_string(info->uID), info->avatar);
	setLabelText(info->displayName, name);
	gold->setString(StringUtility::formatNumberSymbol(info->gold));
	
	updateLevel();
}

void TalaPlayerView::updateLevel()
{
	auto info = talaGameLogic->players[index];
    if (index == 0)
    {
        lbLevel->setString("Level " + to_string(info->getLevel() + 1));
        progress->setPercent(info->getPercentLevel());
        
    }
    borderAvatar->loadTexture(info->getAvatarLevel());
}

void TalaPlayerView::updateGameInfo()
{
	auto info = talaGameLogic->players[index];
	state->removeAllChildren();
	setVisible(info->status != TalaPlayerInfo::STATUS_NONE);
	if (index != 0) {
		card->setVisible(false);
	}

	if (info->status == TalaPlayerInfo::STATUS_NONE)
		setTouchEnabled(false);
	else {
		if (info->status == TalaPlayerInfo::STATUS_VIEWING)
			setTouchEnabled(false);
		else {
			if (card) card->setVisible(talaGameLogic->isPlaying());
			if (!talaGameLogic->isPlaying()) setTouchEnabled(false);
			switch (info->state) {
			case TalaPlayerInfo::STATE_BOCBAI:
				this->state->addChild(Sprite::create("GameTala/textBoc.png"));
				break;
			case TalaPlayerInfo::STATE_DANHBAI:
				this->state->addChild(Sprite::create("GameTala/textThrow.png"));
				break;
			case TalaPlayerInfo::STATE_HABAI:
				this->state->addChild(Sprite::create("GameTala/textHa.png"));
				break;
			case TalaPlayerInfo::STATE_GUIBAI:
				this->state->addChild(Sprite::create("GameTala/textGui.png"));
				break;
			case TalaPlayerInfo::STATE_NONE:
				break;
			}
		}
	}
}

void TalaPlayerView::setVisible(bool visible)
{
	Node::setVisible(visible);
	_layout->setVisible(visible);
}

void TalaPlayerView::setTouchEnabled(bool enabled)
{
	touchEnabled = enabled;
	if (!touchEnabled && index == 0) {
		touchId = -1;
		moveCard->setVisible(false);
		for (int i = 0; i < handOnCards.size(); i++)
			handOnCards.at(i)->setVisible(true);
	}
}

bool TalaPlayerView::isTouchEnabled()
{
    return touchEnabled && (touchId == -1);
}

Vec2 TalaPlayerView::getAvatarPosition()
{
	return _layout->convertToWorldSpace(avatar->getPosition());
}

bool TalaPlayerView::isTouchLastThrowCard(Vec2 touchPos)
{
	if (throwCards.size() > 0) {
		return throwCards.at(throwCards.size() - 1)->containTouchPoint(touchPos);
	}
	else return false;
}

char TalaPlayerView::getTouchSuitIndex(Vec2 touchPos)
{
	if (index != 2) {
		for (int i = 0; i < listPhom.size(); i++) {
			for (auto card : listPhom[i]) {
				if (card->containTouchPoint(touchPos))
					return i;
			}
		}
	}
	else {
		for (int i = listPhom.size() - 1; i >= 0; i--) {
			for (auto card : listPhom[i]) {
				if (card->containTouchPoint(touchPos))
					return i;
			}
		}
	}

	return -1;
}

void TalaPlayerView::showEffectRank(int rank, float delayTime)
{
    if (delayTime > 0)
    {
        runAction(Sequence::create(DelayTime::create(delayTime),
                                   CallFunc::create([this, rank]() { this->showEffectRank(rank); }), nullptr));
    }
    else
    {
        resultGroup->showMauBinh(rank);
    }
}

void TalaPlayerView::showScore(int score) {
    if (score > 500)
        return;
    this->lbScore->setString(StringUtility::formatNumberSymbol(score));
    bgScore->setVisible(true);
    bgScore->setOpacity(0);
    bgScore->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(2.0), FadeOut::create(0.5),
                                        CallFunc::create([this]() { bgScore->setVisible(false); }), nullptr));
}

void TalaPlayerView::effectRenew() {
    auto particle = ParticleSystemQuad::create("Particles/renew.plist");
    particle->setLocalZOrder(5);
    _layout->addChild(particle);
    particle->setPosition(avatar->getPosition());
    particle->setAutoRemoveOnFinish(true);

    int idAvatar = AXRANDOM_0_1() * 41.99999;
    avatar->loadTexture("images1/avatar_" + to_string(idAvatar) + ".png");
}

void TalaPlayerView::effectTime(char time)
{
	timer->stopAllActions();
	timer->setVisible(false);
	nen->setVisible(false);

	if (time > 0) {
		timer->setVisible(true);
		timer->setPercentage(100);
		timer->runAction(Spawn::create(
			ProgressFromTo::create(time, 100, 0),
			Sequence::create(
				DelayTime::create(MAX(0, time - 5)),
				CallFunc::create([this]() {
					if (index == 0) TalaGameSound::playRandom(TalaInGameMgr::VOICE_TIMER);
				}),
				Repeat::create(Sequence::create(
					CallFunc::create([this]() {
						if (index == 0) TalaGameSound::playEffect(TalaInGameMgr::SOUND_TIMER);
					}),
					DelayTime::create(1),
					nullptr
				), MIN(time, 5)),
				nullptr
			),
			nullptr
		));
	}
}

void TalaPlayerView::effectDarkAllCards()
{
	for (auto card : throwCards) {
		card->setDark(true, true);
		card->showArrow(false);
		card->showEatable(false);
		card->showEaten(false);
	}

	for (auto card : eatenCards) {
		card->setDark(true, true);
		card->showArrow(false);
		card->showEatable(false);
		card->showEaten(false);
	}

	if (index == 0) {
		updateHandOnCards(0);
		for (auto card : handOnCards) {
			card->setDark(true, true);
			card->showArrow(false);
			card->showEatable(false);
			card->showEaten(false);
		}
	}

	for (auto phom : listPhom) {
		for (auto card : phom) {
			card->showArrow(false);
			card->showEatable(false);
		}
	}
}

void TalaPlayerView::clearAllCards()
{
	handOnCards.clear();
	eatenCards.clear();
	throwCards.clear();
	listPhom.clear();
	removeAllChildren();
	if (index != 0) {
		panel_eat->removeAllChildren();
		panel_card->removeAllChildren();
	}
	panel_throw->removeAllChildren();
	panel_haphom->removeAllChildren();
}

void TalaPlayerView::updateHandOnCards(float duration, bool resetTouch)
{
	auto numCard = handOnCards.size();
	if (index == 0) {
		auto selectedCards = talaGameLogic->players[0]->selectedCards;
		if (numCard > 0) {
			auto cardSize = handOnCards.at(0)->getContentSize();
			auto maxWidth = (cardSize.width) * (2 * numCard + 1) / 3;
			float offset, delta;
			if (maxWidth > getContentSize().width && numCard > 1) {
				offset = 0;
				delta = (getContentSize().width - cardSize.width) / (numCard - 1);
			}
			else {
				offset = (getContentSize().width - maxWidth) / 2;
				delta = 2 * cardSize.width / 3;
			}

            if (resetTouch) setTouchEnabled(false);
			for (int i = 0; i < numCard; i++) {
				auto card = handOnCards.at(i);
				card->isUp = find(selectedCards.begin(), selectedCards.end(), card->id) != selectedCards.end();
				card->setLocalZOrder(i);
				card->setVisible(true);
				card->setDark(false);
				float endScale = 1;
				Vec2 endPos(offset + cardSize.width / 2 + i * delta, TalaCardView::START_Y + (card->isUp ? TalaCardView::OFFSET_Y : 0));
                card->stopAllActions();
                if (duration > 0) {
                    card->runAction(Sequence::create(
                        Spawn::create(
                            EaseSineInOut::create(MoveTo::create(duration, endPos)),
                            EaseSineInOut::create(ScaleTo::create(duration, endScale)),
                            nullptr
                        ),
                        CallFunc::create([this, i, numCard]() { if (i == numCard - 1) setTouchEnabled(true); }),
                        nullptr
                    ));
                }
                else {
                    card->setScale(endScale);
                    card->setPosition(endPos);
                    if (i == numCard - 1) setTouchEnabled(true);
                }
			}
		}
	}
	else {
		for (int i = 0; i < numCard; i++) {
			auto card = handOnCards.at(i);
			auto endScale = TalaCardView::SMALL_SCALE;
			Vec2 endPos;
			auto cardSize = card->getContentSize() * TalaCardView::SMALL_SCALE;
			if (index == 2) {
				card->setLocalZOrder(numCard - i);
				endPos = { -cardSize.width / 3 * i, panel_card->getContentSize().height / 2 };
			}
			else {
				card->setLocalZOrder(i);
				endPos = { panel_card->getContentSize().width / 2, cardSize.height / 4 * ((numCard - 1) / 2.f - i) };
			}
			if (card->getScale() != endScale || card->getPosition() != endPos) {
				card->stopAllActions();
				if (duration > 0) {
					card->runAction(Spawn::create(
						EaseSineInOut::create(MoveTo::create(duration, endPos)),
						EaseSineInOut::create(ScaleTo::create(duration, endScale)),
						nullptr
					));
				}
				else {
					card->setScale(endScale);
					card->setPosition(endPos);
				}
			}
		}
	}
}

void TalaPlayerView::updateThrowCards(float duration)
{
	for (int i = 0; i < throwCards.size(); i++) {
		auto card = throwCards.at(i);
		card->setLocalZOrder(i);
		auto endScale = TalaCardView::SMALL_SCALE;
		Vec2 endPos((card->getContentSize().width * TalaCardView::SMALL_SCALE) / 3 * i, panel_throw->getContentSize().height / 2);
		if (card->getScale() != endScale || card->getPosition() != endPos) {
			card->stopAllActions();
			if (duration > 0) {
				card->runAction(Spawn::create(
					EaseSineInOut::create(MoveTo::create(duration, endPos)),
					EaseSineInOut::create(ScaleTo::create(duration, endScale)),
					nullptr
				));
			}
			else {
				card->setScale(endScale);
				card->setPosition(endPos);
			}
		}
	}
}

void TalaPlayerView::updateEatenCards(float duration)
{
	for (int i = 0; i < eatenCards.size(); i++) {
		auto card = eatenCards.at(i);
		if (index == 2) card->setLocalZOrder(eatenCards.size() - i);
		else card->setLocalZOrder(i);
		auto endScale = TalaCardView::SMALL_SCALE;
		Vec2 endPos;
		auto cardSize = card->getContentSize() * TalaCardView::SMALL_SCALE;
		if (index == 2)
			endPos = { - cardSize.width * (i + 1) / 2, panel_eat->getContentSize().height / 2 };
		else
			endPos = { panel_eat->getContentSize().width / 2, -(cardSize.height / 2 + i * cardSize.height / 3) };
		if (card->getScale() != endScale || card->getPosition() != endPos) {
			card->stopAllActions();
			if (duration > 0) {
				card->runAction(Spawn::create(
					EaseSineInOut::create(MoveTo::create(duration, endPos)),
					EaseSineInOut::create(ScaleTo::create(duration, endScale)),
					nullptr
				));
			}
			else {
				card->setScale(endScale);
				card->setPosition(endPos);
			}
		}
	}
}

void TalaPlayerView::updatePhomCards(float duration)
{
	int sum = 0;
	for (int i = 0; i < listPhom.size(); i++) {
		sum += listPhom[i].size();
		for (int j = 0; j < listPhom[i].size(); j++) {
			auto card = listPhom[i].at(j);
			auto cardSize = card->getContentSize() * TalaCardView::SMALL_SCALE;
			float endScale = TalaCardView::SMALL_SCALE;
			Vec2 endPos;
			switch (index) {
			case 0:
			case 1:
				endPos = { cardSize.width / 2 * j, cardSize.height / 3 * i + panel_haphom->getContentSize().height / 2 };
				card->setLocalZOrder(-sum + j);
				break;
			case 2:
				endPos = { -cardSize.width / 2 * j, -cardSize.height / 3 * i + panel_haphom->getContentSize().height / 2 };
				card->setLocalZOrder(sum - j);
				break;
			case 3:
				endPos = { -cardSize.width / 2 * j, cardSize.height / 3 * i + panel_haphom->getContentSize().height / 2 };
				card->setLocalZOrder(-sum + listPhom[i].size() - j);
				break;
			}
			if (card->getScale() != endScale || card->getPosition() != endPos) {
				card->stopAllActions();
				if (duration > 0) {
					card->runAction(Spawn::create(
						EaseSineInOut::create(MoveTo::create(0.25, endPos)),
						EaseSineInOut::create(ScaleTo::create(0.25, endScale)),
						nullptr
					));
				}
				else {
					card->setScale(endScale);
					card->setPosition(endPos);
				}
			}
		}
	}
}

void TalaPlayerView::updatePhomCardsU(float duration)
{
    float rate     = 1.7;
    float sumWidth = 0;
    float wCard    = listPhom[0][0]->getContentSize().width * TalaCardView::SMALL_SCALE * 1.7;
    float padPhom  = wCard * 0.2;
    for (int i = 0; i < listPhom.size(); i++)
    {
        sumWidth += (listPhom[i].size() - 1) * wCard * 0.5 + wCard;
    }
    sumWidth = sumWidth + padPhom * (listPhom.size() - 1);
    float startX = WIN_SIZE.width * 0.5 - sumWidth * 0.5;
    
    int sum = 0;
    int count = 0;
    for (int i = 0; i < listPhom.size(); i++)
    {
        sum += listPhom[i].size();
        for (int j = 0; j < listPhom[i].size(); j++)
        {
            auto card      = listPhom[i].at(j);
            auto cardSize  = card->getContentSize() * TalaCardView::SMALL_SCALE;
            int zOrder      = 0;
            float endScale = TalaCardView::SMALL_SCALE;
            float endScale1 = TalaCardView::SMALL_SCALE * 1.7;
            startX     = startX + wCard * 0.5;
            Vec2 endPos1  = Vec2(startX, 100);
            endPos1         = panel_haphom->convertToNodeSpace(endPos1);
            Vec2 endPos;
            switch (index)
            {
            case 0:
            case 1:
                endPos = {cardSize.width / 2 * j, cardSize.height / 3 * i + panel_haphom->getContentSize().height / 2};
                zOrder = (-sum + j);
                break;
            case 2:
                endPos = {-cardSize.width / 2 * j,
                          -cardSize.height / 3 * i + panel_haphom->getContentSize().height / 2};
                zOrder = (sum - j);
                break;
            case 3:
                endPos = {-cardSize.width / 2 * j, cardSize.height / 3 * i + panel_haphom->getContentSize().height / 2};
                zOrder = (-sum + listPhom[i].size() - j);
                break;
            }
            card->setLocalZOrder(zOrder);
            if (card->getScale() != endScale || card->getPosition() != endPos)
            {
                card->setLocalZOrder(j);
                card->stopAllActions();
                if (duration > 0)
                {
                    card->runAction(
                        Sequence::create(
                            DelayTime::create(0.03 * count),
                            Spawn::create(
                                EaseSineInOut::create(MoveTo::create(0.5, endPos1)),
                                EaseBounceOut::create(ScaleTo::create(0.6, endScale1)),
                                nullptr
                            ),
                            DelayTime::create(3.0),
                            Spawn::create(
                                EaseSineInOut::create(MoveTo::create(0.25, endPos)),
                                EaseSineInOut::create(ScaleTo::create(0.25, endScale)),
                                CallFunc::create([card, zOrder]() {
                                    card->setLocalZOrder(zOrder);
                                }),
                                nullptr
                            ),
                            NULL
                        )
                    );
                }
                else
                {
                    card->setScale(endScale);
                    card->setPosition(endPos);
                }
            }
            count++;
        }
        startX = startX + padPhom + wCard * 0.5;
    }
}
