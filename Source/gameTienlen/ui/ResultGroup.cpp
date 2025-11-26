#include "ResultGroup.h"
#include "string"
#include <ctime>
#include <chrono>
#include "app/Constant.h"
#include "../logic/GameLogic.h"
#include "app/GameMgr.h"
using namespace std::chrono;
#define NUMBER_RES "table/start_"

using namespace std;

ResultGroup::ResultGroup(void)
{
//	Size size = Director::sharedDirector()->getWinSize();

	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	
	bg = Sprite::create("Game/blackCircle.png");
	addChild(bg);

    bgLightBottom = Sprite::create("CommonEffect/bgLightBottom.png");
    addChild(bgLightBottom);
    bgLightBottom->setPosition(0, 50);

    bgLightTop = Sprite::create("CommonEffect/bgLightTop.png");
    addChild(bgLightTop);
    bgLightTop->setPosition(0, 50);

    iconLeafLeft = Sprite::create("CommonEffect/iconLeafLeft.png");
    iconLeafLeft->setAnchorPoint(Vec2(1, 0));
    iconLeafLeft->setPosition(-42, 35);
    this->addChild(iconLeafLeft);

    iconLeafRight = Sprite::create("CommonEffect/iconLeafRight.png");
    iconLeafRight->setAnchorPoint(Vec2(0, 0));
    iconLeafRight->setPosition(42, 35);
    this->addChild(iconLeafRight);

    iconCrown = Sprite::create("CommonEffect/iconCrown.png");
    iconCrown->setAnchorPoint(Vec2(0.5, 0));
    iconCrown->setPosition(0, 28);
    addChild(iconCrown);

    iconLeft = Sprite::create("CommonEffect/iconBgLeft.png");
    iconLeft->setAnchorPoint(Vec2(1, -0.5));
    iconLeft->setPosition(-86, -112);
    addChild(iconLeft);

    iconRight = Sprite::create("CommonEffect/iconBgRight.png");
    iconRight->setAnchorPoint(Vec2(0, -0.5));
    iconRight->setPosition(86, -112);
    addChild(iconRight);

    bgTitle = Sprite::create("CommonEffect/bgTitle.png");
    addChild(bgTitle);

    title = Sprite::create("CommonEffect/nhat.png");
    addChild(title);
    title->setAnchorPoint(Vec2(0.5, 1.0));

	//starFly = new StarFly(size.width, size.height);
	//addChild(starFly);
	//starFly->setPosition(-size.width * 0.5, -size.height * 0.5);

	paperLeft = new Paper(500, 300, 1, 1);
	addChild(paperLeft);
	paperLeft->setPosition(-250, -150);
	//paperLeft->startEffect();
	paperLeft->setLocalZOrder(4);

	paperRight = new Paper(500, 300, -1, 1);
	addChild(paperRight);
	paperRight->setPosition(250, -150);
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

ResultGroup::~ResultGroup(void)
{
}

void ResultGroup::showMauBinh(int type)
{
	if (isVisible())
		return;
    
	string resource = "CommonEffect/thang.png";
	if (gameMgr->setting.isVietnam) {
		resource = "CommonEffect/thang.png";
	}
	if (type == RANK_NHAT || type == RANK_TOI_TRANG) {
		if (type == RANK_NHAT) {
			resource = "CommonEffect/thang.png";
			if (gameMgr->isIndo) {
				resource = "CommonEffect/thang.png";
			}
		}
		else {
			int typeSuddenWin = GameLogic::getInstance()->typeSuddenWin;
			resource = "CommonEffect/autoWin.png";
			if (gameMgr->isIndo == false) {
				resource = "CommonEffect/autoWin.png";
				//typeSuddenWin = ST_STRAIGHT;
				switch (typeSuddenWin)
				{
				case ST_STRAIGHT:
					resource = "CommonEffect/sanhRong.png";
					break;
				case ST_SIXPAIR:
					resource = "CommonEffect/sauDoi.png";
					break;
				case ST_FOUR_2:
					resource = "CommonEffect/tuQuy2.png";
					break;
				case ST_ULTRA:
					resource = "CommonEffect/5DoiThong.png";
					break;
				default:
					break;
				}
			}
			else {
                resource = "Game/textEffect/autoWin.png";
				switch (typeSuddenWin)
				{
				case ST_STRAIGHT:
					resource = "Game/textEffect/dragon.png";
					break;
				case ST_SIXPAIR:
					resource = "Game/textEffect/sixPairs.png";
					break;
				case ST_FOUR_2:
					resource = "Game/textEffect/fourOf2.png";
					break;
				case ST_ULTRA:
					resource = "Game/textEffect/5SequencePairs.png";
					break;
				default:
					break;
				}
			}
		}
		showEffectWin();
	}
	else {
		if (type == RANK_CONG) {
			resource = "CommonEffect/cong.png";
			if (gameMgr->isIndo) {
				resource = "Game/textEffect/noPlay.png";
			}
		}
		else {
			resource = "CommonEffect/lose.png";
			if (gameMgr->isIndo) {
				resource = "Game/textEffect/lose.png";
			}
		}
        showEffectLose();
	}
  //  resource = "CommonEffect/win.png";
	title->setTexture(resource);
    showTitle();
}

void ResultGroup::showEffectWin() {
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
}

void ResultGroup::showEffectLose() {
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

void ResultGroup::showTitle() {
    setVisible(true);
    float saveScale = getScaleY();
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
        Spawn::create(EaseExponentialOut::create(MoveTo::create(0.4, Vec2(0, 45))), FadeIn::create(0.4),
                      EaseBackOut::create(ScaleTo::create(0.4, 1)), NULL),
        Repeat::create(Sequence::create(ScaleTo::create(0.4, 1.2), ScaleTo::create(0.4, 1.0), NULL), 100), NULL));

    iconLeft->setVisible(true);
    iconLeft->stopAllActions();
    iconLeft->runAction(Repeat::create(
        Sequence::create(EaseSineOut::create(RotateTo::create(0.35, -5)), RotateTo::create(0.35, 0), NULL), 100));

    iconRight->setVisible(true);
    iconRight->stopAllActions();
    iconRight->runAction(Repeat::create(
        Sequence::create(EaseSineOut::create(RotateTo::create(0.35, 5)), RotateTo::create(0.35, 0), NULL), 100));
}
