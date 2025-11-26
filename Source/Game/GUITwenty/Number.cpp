#include "Number.h"
#include "Game/Data/GlobalData.h"
#include "Game/Utility/GameUtility.h"
#include <Game/Logic/Constant.h>


Number::Number(void)
{
	//ball = new GameImage("brickWhite.png");
	ball = new GameImage("Merge/2.png");
	ball->setWidth(WIDTH_BALL_TWENTY);
	ball->setHeight(WIDTH_BALL_TWENTY);
	//ball->getImg()->setAnchorPoint(ccp(0, 0));
	ball->setPos(WIDTH_BALL_TWENTY * 0.5, WIDTH_BALL_TWENTY * 0.5);

	label = Text::create("SCORE: 0", "fonts/tahomabd.ttf", 30);
    label->enableOutline(Color4B(115, 37, 31, 255), 1);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	width = WIDTH_BALL_TWENTY;
	height = WIDTH_BALL_TWENTY;
	x = 0;
	y = 0;
	visible = false;
	ball->addChild(label);
	//label->setPositionY(-10);
//	label->setScale(label->getDefaultScale() * 1.6);


	//eff = DBFactory::getInstance()->buildArmatureNode("Oqua");
	//eff->setScale(1.35);
	//if (eff) {
	//	ball->addChild(eff);
	//	eff->setLocalZOrder(20);
	//	eff->setPositionY(-10);
	//	eff->gotoAndPlay("1", 0.5, -1, -1);
	//	//eff->setScale(5);
	//	/*eff->setCompleteListener([](dragonBones::DBArmatureNode* armature) {
	//		armature->removeFromParent();
	//	});*/
	//}
}


Number::~Number(void)
{

}


bool Number::isVisible()
{
	return visible;
}

void Number::setVisible(bool visible)
{
	this->visible = visible;
	ball->setVisible(visible);
}
void Number::addToParent(Node* layer)
{
	layer->addChild(ball);
}

void Number::setX(float x)
{
	float dx = x - this->x;
	this->x = x;
	ball->setPositionX(ball->getPositionX() + dx);
}

void Number::setY(float y)
{
	float dy = y - this->y;
	this->y = y;
	ball->setPositionY(ball->getPositionY() + dy);
}

void Number::setPosition(float x, float y)
{
	setX(x);
	setY(y);
}
float Number::getWidth()
{
	return WIDTH_BALL_TWENTY;
}
float Number::getHeight()
{
	return height;
}
float Number::getX()
{
	return x;
}
float Number::getY()
{
	return y;
}
void Number::setNumber(int _id) {
	id = _id;
	label->setString(GameUtility::toString(id).c_str());
	std::string s = "GuiGame/Merge/" + GameUtility::toString(id % 25) + ".png";
	//	ball->setColor(GameUtility::getColorTwenty(id));
	ball->getImg()->setTexture(s.c_str());
    if (id < 10)
        label->setFontSize(40);
	else
		label->setScale(35);
	/*if (id > 10) {
		if (eff) {
			eff->gotoAndPlay("1", 0.0, -1, -1);
			eff->setVisible(true);
		}
	}
	else {
		if (eff) {
			eff->setVisible(false);
		}
	}*/

	//switch (id % 20) {
	//case 1:
	//	
	//	ball->setColor(ccc3(0.97f * 255, 0.97f * 255, 0));
	//	//label->setColor(ccc3(0.4f * 255, 0.4f * 255, 0.4f * 255));
	//	break;
	//case 2:
	//	ball->setColor(ccc3(0.97f * 255, 0.05f * 255, 0.05f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 3:
	//	ball->setColor(ccc3(0.05f * 255, 0.75f * 255, 0.9f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 4:
	//	ball->setColor(ccc3(0.00f * 255, 1.00f * 255, 0));
	//	//label->setColor(ccc3(0.3f * 255, 0.3f * 255, 0.3f * 255));
	//	break;
	//case 5:
	//	ball->setColor(ccc3(0.8f * 255, 0.00f * 255, 0.7f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 6:
	//	ball->setColor(ccc3(0.99f * 255, 0.6f * 255, 0.04f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 7:
	//	ball->setColor(ccc3(0.5f * 255, 0.0f * 255, 0.4f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 8:
	//	ball->setColor(ccc3(0.75f * 255, 1.0f * 255, 0.0f * 255));
	//	//label->setColor(ccc3(0.3f * 255, 0.3f * 255, 0.3f * 255));
	//	break;
	//case 9:
	//	ball->setColor(ccc3(0.4f * 255, 0.93f * 255, 0.55f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 10:
	//	ball->setColor(ccc3(0.2f * 255, 0.6f * 255, 0.74f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 11:
	//	ball->setColor(ccc3(0.0f * 255, 0.11f * 255, 0.4f * 255));
	//	//label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
	//	break;
	//case 12:
	//	ball->setColor(ccc3(1.0f * 255, 0.6f * 255, 0.78f * 255));
	//	//label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
	//	break;
	//case 13:
	//	ball->setColor(ccc3(0.5f * 255, 0.0f * 255, 0.1f * 255));
	//	//label->setColor(ccc3(0.9f * 255, 0.9f * 255, 0.9f * 255));
	//	break;
	//case 14:
	//	ball->setColor(ccc3(0.6f * 255, 0.7f * 255, 0.9f * 255));
	//	//label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
	//	break;
	//case 15:
	//	ball->setColor(ccc3(0.9f * 255, 0.84f * 255, 0.76f * 255));
	//	//label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
	//	break;
	//case 16:
	//	ball->setColor(ccc3(0.77f * 255, 0.59f * 255, 0.31f * 255));
	//	//label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
	//	break;
	//case 17:
	//	ball->setColor(ccc3(0.7f * 255, 0.0f * 255, 0.15f * 255));
	//	//label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
	//	break;
	//case 18:
	//	ball->setColor(ccc3(0.44f * 255, 0.34f * 255, 0.99f * 255));
	//	//label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
	//	break;
	//case 19:
	//	ball->setColor(ccc3(0.0f * 255, 0.39f * 255, 0.19f * 255));
	//	//label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
	//	break;
	//case 0:
	//	ball->setColor(ccc3(0.96f * 255, 0.53f * 255, 0.47f * 255));
	//	//label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
	//	break;
	//}
	//label->setColor(ccc3(20, 20, 20));
	//label->setPosition(getWidth() * 0.5f, getHeight() * 0.5f);
	//label->setPosition(getWidth() * 0.5f - label->getWidth() * 0.5f + ball->getPositionX() - WIDTH_BALL_TWENTY * 0.5,
		//getHeight() * 0.5f - label->getHeight() * 0.5f + ball->getPositionY() - WIDTH_BALL_TWENTY * 0.5);
}

void Number::effectNewGame()
{
	float sX = ball->getScaleX();
	float sY = ball->getScaleY();
	ball->setScale(0);
	float delay = GameUtility::getRandom() * 0.3;
	ball->runAction(
		Sequence::create(
			DelayTime::create(delay),
			EaseExponentialOut::create(ScaleTo::create(0.5, sX, sY)),
			NULL
		)
	);
	float s = 1.1;

	/*label->setScale(0);

	label->runAction(
		Sequence::create(
			DelayTime::create(delay + 0.2),
			EaseBounceOut::create(ScaleTo::create(0.5, 1.1, 1.1)),
			NULL
		)
	);*/
}


void Number::effectEndGame()
{
	float pX = WIDTH_BALL_TWENTY * 0.5 + 5 * (0.5 - GameUtility::getRandom()) + this->x;
	float pY = WIDTH_BALL_TWENTY * 0.5 + 5 * (0.5 - GameUtility::getRandom()) + this->y;
	ball->runAction(Sequence::create(
		MoveTo::create(0.02 + GameUtility::getRandom() * 0.08, Vec2(pX, pY)),
		CallFunc::create(AX_CALLBACK_0(Number::effectEndGame, this)),
		NULL
	));

}

void Number::effectEat()
{
	countEffect = 4;
	ball->stopAllActions();
	doEffectEat();
	ball->runAction(Sequence::create(
		ScaleTo::create(0.1, ball->getScaleX() * 1.1, ball->getScaleY() * 1.1),
		ScaleTo::create(0.1, ball->getScaleX() * 1.0, ball->getScaleY() * 1.0),
		NULL
	));
}

void Number::doEffectEat()
{
	if (countEffect <= 0) {
		ball->setPosition(WIDTH_BALL_TWENTY * 0.5 + this->x, WIDTH_BALL_TWENTY * 0.5 + this->y);
		ball->setWidth(WIDTH_BALL_TWENTY);
		ball->setHeight(WIDTH_BALL_TWENTY);
		return;
	}
	float pX = WIDTH_BALL_TWENTY * 0.5 + 4 * (0.5 - GameUtility::getRandom()) + this->x;
	float pY = WIDTH_BALL_TWENTY * 0.5 + 4 * (0.5 - GameUtility::getRandom()) + this->y;

	ball->runAction(Sequence::create(
		MoveTo::create(0.05, Vec2(pX, pY)),
		CallFunc::create(AX_CALLBACK_0(Number::doEffectEat, this)),
		NULL
	));
	countEffect--;
}

void Number::stopAllActions()
{
	ball->stopAllActions();
	ball->setPosition(WIDTH_BALL_TWENTY * 0.5 + this->x, WIDTH_BALL_TWENTY * 0.5 + this->y);
}

void Number::updateSize()
{
	ball->setWidth(WIDTH_BALL_TWENTY);
	ball->setHeight(WIDTH_BALL_TWENTY);
	ball->setPos(WIDTH_BALL_TWENTY * 0.5, WIDTH_BALL_TWENTY * 0.5);

	width = WIDTH_BALL_TWENTY;
	height = WIDTH_BALL_TWENTY;
	x = 0;
	y = 0;
}

void Number::remove()
{
	ball->removeFromParent();
}
