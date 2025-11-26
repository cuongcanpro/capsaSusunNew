#include "BombEffect.h"
#include <cmath>  
#include "Engine/GUI/GameImage.h"
#include "Engine/Utility/CStringUtils.h"
#include <string>
#include "../../Utility/GameUtility.h"
#include <Game/Utility/JNIUtils.h>
#include <Game/Utility/GameSound.h>

BombEffect::BombEffect(): Node()
{
    imgBomb = Sprite::create("particles/effectBom.png");
    addChild(imgBomb);

    std::string s = "particles/smoke.plist";
    //	s = "particles/vip.plist";
    effect = new ParticleEffect();
    effect->create(s.c_str(), this);
    effect->particle->setBlendAdditive(true);
    effect->particle->setAutoRemoveOnFinish(false);
    effect->particle->setVisible(false);

    setScale(0.6);
}

BombEffect::~BombEffect(void)
{

}

void BombEffect::showBomb(float timeDelay) {
    setVisible(true);
    imgBomb->setScale(0);
    effect->particle->setVisible(false);
    runAction(
        Sequence::create(
            DelayTime::create(timeDelay),
            CallFunc::create(AX_CALLBACK_0(BombEffect::callbackShow, this)),
            DelayTime::create(1.5),
            Hide::create(),
            NULL
        )
    );
}

void BombEffect::callbackShow() {
    GameSound::playJump();
    JNIUtils::vibrate(10);
    effect->particle->setVisible(true);
    imgBomb->setOpacity(255);
    imgBomb->runAction(
        Sequence::create(
            ScaleTo::create(0.1, 1.2),
            ScaleTo::create(0.3, 1.0),
            DelayTime::create(0.5),
            FadeOut::create(0.5),
            NULL
        )
    );
    effect->particle->resetSystem();
    if (AXRANDOM_0_1() < 0.2)
        GameSound::playHit();

}
