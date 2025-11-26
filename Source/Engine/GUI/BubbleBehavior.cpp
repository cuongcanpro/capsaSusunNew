#include "BubbleBehavior.h"
//#include "Sound/CSound.h"

BubbleBehavior::BubbleBehavior(void)
{
}


BubbleBehavior::~BubbleBehavior(void)
{
}

void BubbleBehavior::onTouchBegan(Touch*touch, BaseButton* touchButton)
{
	if(!touchButton->isEnable()) return;

	touchButton->normalImage->addEffectScaleSmaler();
}

void BubbleBehavior::onTouchEnded(Touch* touch, BaseButton* releaseButton )
{
	if(!releaseButton->isEnable()) return;

	releaseButton->normalImage->addEffectBubble();
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	//CSound::shared()->playEffectById(touchPoint,SOUND_FUNC_CLICK_BUTTON);
}
