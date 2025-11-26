#include "CardEndGroup.h"
#include "string"
#include "core/utils/TienlenGameSound.h"
#include <ctime>
#include <chrono>
#include "app/Constant.h"
#include "../logic/GameLogic.h"
#include "app/GameMgr.h"
#include <Game/Utility/JNIUtils.h>
using namespace std::chrono;
#define NUMBER_RES "table/start_"

using namespace std;

CardEndGroup::CardEndGroup(void)
{
//	CCSize size = CCDirector::sharedDirector()->getWinSize();

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	
	bg = Sprite::create("Game/bgDark.png");
	bg->setScaleX(size.width / bg->getContentSize().width);
	bg->setScaleY(size.height / bg->getContentSize().height);
	bg->setOpacity(150);
	addChild(bg);

	//starFly = new StarFly(size.width, size.height);
	//addChild(starFly);
	//starFly->setPosition(-size.width * 0.5, -size.height * 0.5);


	manager = EffectManager::create(Size(size.width * 0.5, size.height * 0.5));

	Effect* effect1 = Effect::create("lightExplore.efk", 10);
	lightExplore = EffectEmitter::create(manager);
	lightExplore->setEffect(effect1);
	lightExplore->setPlayOnEnter(false);
	lightExplore->setPosition(-size.width * 0.25, -size.height * 0.25);
	addChild(lightExplore);
	lightExplore->setRemoveOnStop(false);
	lightExplore->stop();

	getCardEffect();

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
	setVisible(false);
}

CardEndGroup::~CardEndGroup(void)
{
}

void CardEndGroup::showCardEnd(vector<int> ids, vector <Vec2> startPos, float startScale)
{
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	TienlenGameSound::playAutoWin();
	lightExplore->setVisible(false);
	if (isVisible() && false)
		return;
	bg->setOpacity(0);
	bg->runAction(
		Sequence::create(
			EaseExponentialOut::create(FadeTo::create(0.5, 150)),
			DelayTime::create(1.5),
			FadeOut::create(0.5),
			NULL
		)
	);
	for (int i = 0; i < cards.size(); i++)
		cards[i]->setVisible(false);
	float scaleEnd = 2;
	float scaleEnd2 = 0.9;
	float widthCard = cards[0]->getContentSize().width * scaleEnd;
	float widthCard2 = cards[0]->getContentSize().width * scaleEnd2;
	float padX = widthCard * 0.4;
	float padX2 = widthCard2 * 0.4;
	float sumWidth = widthCard + padX * (ids.size() - 1);
	float sumWidth2 = widthCard2 + padX2 * (ids.size() - 1);
	float startX = size.width * 0.5 - sumWidth * 0.5;
	float startX2 = size.width * 0.5 - sumWidth2 * 0.5;
	
	for (int i = 0; i < ids.size(); i++) {
		CardEffect* card = getCardEffect();
		Vec2 endPos = Vec2(startX + widthCard * 0.5 + padX * i, size.height * 0.5);
		Vec2 endPos2 = Vec2(startX2 + widthCard2 * 0.5 + padX2 * i, size.height * 0.5);
		Vec2 startPos1 = convertToNodeSpace(startPos[i]);
		endPos = convertToNodeSpace(endPos);
		endPos2 = convertToNodeSpace(endPos2);
		card->setIdCard(ids[i]);
		card->setLocalZOrder(i + 1);
		card->moveEnd(startPos1, endPos, endPos2, startScale, scaleEnd, scaleEnd2, 0.05 * i);

        runAction(Sequence::create(DelayTime::create(0.05 * i),
                                           CallFunc::create(AX_CALLBACK_0(CardEndGroup::callbackVibrate, this)), NULL));
	}

	runAction(
		Sequence::create(
			DelayTime::create(0.4),
			CallFunc::create(AX_CALLBACK_0(CardEndGroup::showLight, this)),
			DelayTime::create(0.5),
			CallFunc::create(AX_CALLBACK_0(CardEndGroup::playSound, this)),
			NULL
		)
	);

	setOpacity(255);
	setVisible(true);
}

void CardEndGroup::update(float delta)
{
	manager->update(delta);
}

void CardEndGroup::showLight()
{
	lightExplore->setVisible(true);
	lightExplore->play(1);
}

void CardEndGroup::playSound()
{
	TienlenGameSound::playEndCard();
}

CardEffect* CardEndGroup::getCardEffect()
{
	CardEffect *card = NULL;
	for (int i = 0; i < (int)cards.size(); i++) {
		if (!cards.at(i)->isVisible()) {
			card = cards.at(i);
			break;
		}
	}
	if (card == NULL) {
		card = new CardEffect(52);
		
			addChild(card, 1);
			cards.push_back(card);
	}
	card->setRotation3D(Vec3(0, 0, 0));
	card->setScale(1);
	card->setVisible(true);
	card->setOpacity(255);
	card->setIdCard(52);
	card->setDark(false);
	return card;
}


void CardEndGroup::callbackVibrate()
{
    JNIUtils::vibrate(20);
}
