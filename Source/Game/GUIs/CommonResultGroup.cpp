#include "CommonResultGroup.h"
#include "string"
#include <ctime>
#include <chrono>
using namespace std::chrono;
#define NUMBER_RES "table/start_"

using namespace std;

CommonResultGroup::CommonResultGroup(void)
{
//	Size size = Director::sharedDirector()->getWinSize();

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	
	bg = Sprite::create("CommonEffect/blackCircle.png");
	addChild(bg);

    bgLightBottom = Sprite::create("CommonEffect/bgLightBottom.png");
    addChild(bgLightBottom);
    bgLightBottom->setPosition(0, 60);

    bgLightTop = Sprite::create("CommonEffect/bgLightTop.png");
    addChild(bgLightTop);
    bgLightTop->setPosition(0, 60);

    iconLeafLeft = Sprite::create("CommonEffect/iconLeafLeft.png");
    iconLeafLeft->setAnchorPoint(Vec2(1, 0));
    iconLeafLeft->setPosition(-60, 50);
    this->addChild(iconLeafLeft);

    iconLeafRight = Sprite::create("CommonEffect/iconLeafRight.png");
    iconLeafRight->setAnchorPoint(Vec2(0, 0));
    iconLeafRight->setPosition(60, 50);
    this->addChild(iconLeafRight);

    iconCrown = Sprite::create("CommonEffect/iconCrown.png");
    iconCrown->setAnchorPoint(Vec2(0.5, 0));
    iconCrown->setPosition(0, 28);
    addChild(iconCrown);

    iconLeft = Sprite::create("CommonEffect/iconBgLeft.png");
    iconLeft->setAnchorPoint(Vec2(1, -0.5));
    iconLeft->setPosition(-120, -150);
    addChild(iconLeft);

    iconRight = Sprite::create("CommonEffect/iconBgRight.png");
    iconRight->setAnchorPoint(Vec2(0, -0.5));
    iconRight->setPosition(120, -150);
    addChild(iconRight);

    bgTitle = Sprite::create("CommonEffect/bgTitle.png");
    addChild(bgTitle);

    title = Sprite::create("CommonEffect/win.png");
    addChild(title);
    title->setAnchorPoint(Vec2(0.5, 1.0));

	//starFly = new StarFly(size.width, size.height);
	//addChild(starFly);
	//starFly->setPosition(-size.width * 0.5, -size.height * 0.5);

	paperLeft = new Paper(500, 300, 1, 1);
	addChild(paperLeft);
	paperLeft->setPosition(-300, -150);
	//paperLeft->startEffect();
	paperLeft->setLocalZOrder(4);

	paperRight = new Paper(500, 300, -1, 1);
	addChild(paperRight);
	paperRight->setPosition(300, -150);
	//paperRight->startEffect();
	paperRight->setLocalZOrder(4);

    particle = ParticleSystemQuad::create("CommonEffect/randomStar.plist");
	particle->setLocalZOrder(5);
	addChild(particle);
	//particle->setPosition(size.width * 0.5, size.height);

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
	setVisible(false);
}

CommonResultGroup::~CommonResultGroup(void)
{
}

void CommonResultGroup::showMauBinh(int type)
{
	if (isVisible())
		return;
	string resource = "CommonEffect/win.png";
	
		showEffectWin();
	
  //  resource = "CommonEffect/win.png";
	title->setTexture(resource);
    showTitle();
}

void CommonResultGroup::showEffectWin() {
    paperRight->startEffect();
    paperLeft->startEffect();

    float timeDelay = 0.3;
    bgLightBottom->setVisible(true);
    bgLightBottom->stopAllActions();
    bgLightBottom->setOpacity(0);
    bgLightBottom->runAction(Sequence::create(DelayTime::create(timeDelay + 0.5), FadeIn::create(0.5), NULL));

    bgLightTop->setVisible(true);
    bgLightTop->stopAllActions();
    bgLightTop->setOpacity(0);
    bgLightTop->runAction(Sequence::create(DelayTime::create(timeDelay + 0.5), FadeIn::create(0.5),
                                           Repeat::create(RotateBy::create(0.3, 30), 100), NULL));

    iconLeafLeft->setVisible(true);
    iconLeafLeft->stopAllActions();
    iconLeafLeft->setScale(0);
    iconLeafLeft->runAction(Sequence::create(
        DelayTime::create(timeDelay + 0.7), EaseBackOut::create(ScaleTo::create(0.5, 1)),
        Repeat::create(
            Sequence::create(EaseSineOut::create(RotateTo::create(0.5, -15)), RotateTo::create(0.5, 0), NULL), 100),
        NULL));

    iconLeafRight->setVisible(true);
    iconLeafRight->stopAllActions();
    iconLeafRight->setScale(0);
    iconLeafRight->runAction(Sequence::create(
        DelayTime::create(timeDelay + 0.7), EaseBackOut::create(ScaleTo::create(0.5, 1)),
        Repeat::create(Sequence::create(EaseSineOut::create(RotateTo::create(0.5, 15)), RotateTo::create(0.5, 0), NULL),
                       100),
        NULL));

    iconCrown->setVisible(true);
    iconCrown->stopAllActions();
    iconCrown->setScale(0);
    iconCrown->runAction(Sequence::create(
        DelayTime::create(timeDelay + 0.5),
        Spawn::create(EaseBounceOut::create(ScaleTo::create(0.6, 1)), FadeIn::create(0.5), NULL), NULL));

   

    
    // starFly->setVisible(true);
    // starFly->startEffect();
    iconLeft->setTexture("CommonEffect/iconBgLeft.png");
    iconRight->setTexture("CommonEffect/iconBgRight.png");
    bgTitle->setTexture("CommonEffect/bgTitle.png");
    particle->setVisible(true);

    runAction(Sequence::create(DelayTime::create(5.0), FadeOut::create(0.5), Hide::create(), NULL));
}

void CommonResultGroup::showEffectLose() {
    iconLeft->setTexture("CommonEffect/iconBgLoseLeft.png");
    iconRight->setTexture("CommonEffect/iconBgLoseRight.png");
    bgTitle->setTexture("CommonEffect/bgTitleLose.png");
    title->setPosition(0, 10);

    paperLeft->setVisible(false);
    paperRight->setVisible(false);
    bgLightTop->setVisible(false);
    bgLightBottom->setVisible(false);
    iconLeafLeft->setVisible(false);
    iconLeafRight->setVisible(false);
    iconCrown->setVisible(false);
    particle->setVisible(false);
}

void CommonResultGroup::showTitle() {
    setVisible(true);
    float saveScale = getScale();
    setScale(5 * saveScale, saveScale);
    setOpacity(0);
    float timeShow = 0.3;
    runAction(Spawn::create(ScaleTo::create(timeShow, saveScale), FadeIn::create(timeShow), NULL));
  

    title->setVisible(true);
    title->stopAllActions();
    title->setPosition(0, 250);
    title->setScaleY(3);
    title->runAction(Sequence::create(
        DelayTime::create(timeShow),
        Spawn::create(EaseExponentialOut::create(MoveTo::create(0.4, Vec2(0, 55))), FadeIn::create(0.4),
                      EaseBackOut::create(ScaleTo::create(0.4, 1)), NULL),
        Repeat::create(Sequence::create(ScaleTo::create(0.4, 1.2), ScaleTo::create(0.4, 1.0), NULL), 90), NULL));

    iconLeft->setVisible(true);
    iconLeft->stopAllActions();
    iconLeft->runAction(Repeat::create(
        Sequence::create(EaseSineOut::create(RotateTo::create(0.35, -5)), RotateTo::create(0.35, 0), NULL), 100));

    iconRight->setVisible(true);
    iconRight->stopAllActions();
    iconRight->runAction(Repeat::create(
        Sequence::create(EaseSineOut::create(RotateTo::create(0.35, 5)), RotateTo::create(0.35, 0), NULL), 100));
}
