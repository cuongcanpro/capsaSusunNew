#include "CardEffect.h"
#include "app/GameMgr.h"
#include "core/utils/TienlenGameSound.h"

CardEffect::CardEffect(void)
{
	isConvert = true;
}


CardEffect::CardEffect(int id): CardImage(id)
{
	isConvert = true;
}

CardEffect::~CardEffect(void)
{
}

void CardEffect::setListener(const CardEffectListener& listener)
{
	_callback = listener;
}

void CardEffect::callbackEffectCard()
{
	if (_callback)
		_callback(index, indexPlayer);
}

void CardEffect::setInfoCard(int _index, int _indexPlayer)
{
	this->indexPlayer = _indexPlayer;
	this->index = _index;
    this->zOrder      = index;
	setLocalZOrder(100 - index);
}

void CardEffect::moveToOpen(Vec2 posStart, Vec2 posEnd, float scaleStart, float scaleEnd, float delayTime)
{
	
	this->scaleEnd = scaleEnd;
	string s = "cards/labai_52.png";
		s = "cards/labai_52.png";
	
	setTexture(s);
	isConvert = false;
	lastDiff = 0;
	setPosition(posStart);
	setScale(scaleStart);
	setRotation3D(Vec3(10, 0, 0));
	float time = 0.2;
	delayTime = delayTime + time * index * 0.2;
	runAction(
		Sequence::create(
			DelayTime::create(delayTime + time),
			RotateTo::create(time, Vec3(-10, -90, 6)),
			RotateTo::create(time, Vec3(-0, -180, 0)),
			NULL
		)
	);
	Vec2 center = Vec2((getPositionX() + posEnd.x) * 0.5, 300);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = getPosition();
	bezier.controlPoint_2 = center;
	bezier.endPosition = posEnd;
	runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			//BezierTo::create(time * 2, bezier),
			EaseExponentialOut::create(MoveTo::create(time * 2, posEnd)),
			CallFunc::create(AX_CALLBACK_0(CardEffect::callbackEffectCard, this)),
			NULL
		)
	);
	/*runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			ScaleTo::create(time * 0.3, scaleEnd),
			NULL
		)
	);*/
	ActionInterval* actionScale = Sequence::create(
		DelayTime::create(delayTime),
		ScaleTo::create(time * 0.5, scaleEnd),
		NULL
	);
	actionScale->setTag(10);
	runAction(actionScale);
}

void CardEffect::moveTo(Vec2 posStart, Vec2 posEnd, float scaleStart, float scaleEnd, float delayTime)
{
	setPosition(posStart);
	setScale(scaleStart);
	float time = 0.4;
	isConvert = true;
	runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			Spawn::create(
				MoveTo::create(time, posEnd),
				ScaleTo::create(time, scaleEnd),
				NULL
			),
			NULL
		)
	);
}

void CardEffect::moveEnd(Vec2 posStart, Vec2 posEnd, Vec2 posEnd2, float scaleStart, float scaleEnd, float scaleEnd2, float delayTime)
{
	setPosition(posStart);
	setScale(scaleStart);
	float time = 0.6;
	isConvert = true;
    float rotate = -AXRANDOM_0_1() * 30 + 15;
    float dx     = 10 - AXRANDOM_0_1() * 20;
    float dy     = 10 - AXRANDOM_0_1() * 20;
	runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			Spawn::create(
				EaseExponentialOut::create(MoveTo::create(time, posEnd)),
				EaseExponentialOut::create(ScaleTo::create(time, scaleEnd)),
				RotateTo::create(time, Vec3(30, 10, 0)),
				NULL
			),
			DelayTime::create(0.5),
			Spawn::create(
				EaseBounceOut::create(ScaleTo::create(time, scaleEnd2)), RotateTo::create(time, Vec3(0, 0, rotate)),
				MoveTo::create(time, Vec2(posEnd2.x + dx, posEnd2.y + dy)),
				NULL
			),
			NULL
		)
	);
}

void CardEffect::moveToiTrang(Vec2 posStart, Vec2 posEnd, float scaleStart, float scaleEnd, int index, bool isConvert, float delayTime)
{
	this->scaleEnd = scaleEnd;
	if (isConvert == false) {
		string s = "cards/labai_52.png";
			s = "cards/labai_52.png";
		
		setTexture(s);
	}

	this->isConvert = isConvert;
	this->zOrder = index;
	lastDiff = 0;
	this->index = index;
	//setRotation3D(Vec3(0, 0, 0));
	setPosition(posStart);
	setScale(scaleStart);
	float time = 0.8;
    float scaleXEnd;
	if (isConvert == false) {
		runAction(
			Sequence::create(
				DelayTime::create(delayTime),
				RotateTo::create(time * 0.5, Vec3(0, -90, 0)),
				RotateTo::create(time * 0.5, Vec3(0, -180, 0)),
				NULL
			)
		);
        scaleXEnd = -scaleEnd;
	}
    else {
        scaleXEnd = scaleEnd;
    }

	ActionInterval* actionScale = Sequence::create(
		DelayTime::create(delayTime),
		ScaleTo::create(time * 0.5, scaleEnd),
		NULL
	);
	actionScale->setTag(10);
	runAction(actionScale);

	Vec2 center = Vec2(posEnd.x, 1000);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = posStart;
	bezier.controlPoint_2 = center;
	bezier.endPosition = posEnd;
	runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			CallFunc::create(AX_CALLBACK_0(CardEffect::playCardFly, this)),
			BezierTo::create(time * 1.0, bezier),
			ScaleTo::create(time * 0.1, scaleXEnd, scaleEnd * 0.8),
            EaseBounceOut::create(ScaleTo::create(time * 0.3, scaleXEnd, scaleEnd * 1.0)),
			CallFunc::create(AX_CALLBACK_0(CardEffect::playCardDown, this)),
			DelayTime::create(6.0),
			FadeOut::create(0.5),
			NULL
		)
	);
}


void CardEffect::playCardFly()
{
	TienlenGameSound::playChipFly();
}

void CardEffect::playCardDown()
{
	TienlenGameSound::playCardDown();
}

void CardEffect::update()
{
	Size size = Director::getInstance()->getVisibleSize();
	if (isVisible()) {
		if (isConvert == false) {
			float posX = getParent()->convertToWorldSpace(getPosition()).x;
			float targetRotate = -90 - (posX - size.width * 0.5) / size.width * 90;
			float curDiff = getRotation3D().y - targetRotate;
			if (index == 0) {
				AXLOGD("Cur %f last %f target %f ", curDiff, lastDiff, targetRotate);
			}
			if (lastDiff != 0 && (curDiff * lastDiff < 0 || abs(curDiff) < 1)) {
				//AXLOGD("Run here %s ", getResource());
				stopActionByTag(10);
				setTexture(getResource());
				setScaleX(-1 * getScaleX());
				runAction(
					ScaleTo::create(0.3, scaleEnd * -1, scaleEnd)
				);
				setLocalZOrder(zOrder);
				isConvert = true;
			}
			else {
				lastDiff = getRotation3D().y - targetRotate;
			}
		}
		else {
			//AXLOGD("Rotation %f %f ", getRotation3D().y, getScaleX());
		}
	}
}
