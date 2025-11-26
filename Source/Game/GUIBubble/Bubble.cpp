#include "Bubble.h"
#include "../Utility/GameUtility.h"
#include "../../Engine/GlobalVar.h"
#include "Game/GUIManager.h"


Bubble::Bubble(void):Node()
{
}

Bubble::Bubble( const char *nameImg, bool frame ):Node()
{
	countTime = 0;
	frameTime = 0.1f;
	currentFrame = 0;

	bg = new GameImage("bubble/cell.png");
	this->addChild(bg);

	label = ui::Text::create("20", "fonts/tahomabd.ttf", 40);
	//label->setAnchorPoint(Vec2(0.6f, 0.68f));
	this->addChild(label);
}


Bubble::~Bubble(void)
{
}

void Bubble::update()
{

}

void Bubble::setState( BubbleState _state )
{
    Size size    = Director::getInstance()->getRenderView()->getVisibleSize();
	float dy = size.height * 0.007f;
	state = _state;
	currentFrame = 0;
	setScaleX(1);
	setScaleY(1);
	setPos(rootX, rootY);
	switch (state)
	{
	case JUMP_BUBBLE:
		cleanup();
		runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, rootScaleX * 0.8f), 
			ScaleTo::create(0.5f, rootScaleX), NULL)));
		break;
	case NORMAL_BUBBLE:
		cleanup();
		
		setVisible(true);
		break;
	case DISAPPEAR_BUBBLE:
		cleanup();
		setVisible(false);
		break;
	case SMALL_BUBBLE:
		cleanup();
		setPos(rootX, rootY);
		setScaleX(0.4f * 1);
		setScaleY(1 * 0.4f);
		break;
	case BIGGER_BUBBLE:
	{
		cleanup();
		//setScale(rootScaleX * 0.4f);
		setVisible(true);

		Color3B temp = bg->getImg()->getColor();
		//bg->setColor(ccc3(255, 255, 255));
		bg->getImg()->runAction(TintTo::create(0.1f, temp.r, temp.g, temp.b));
		//runAction(ScaleTo::create(0.035f, rootScaleX, rootScaleY));
	}
		break;
	case AUTO_SCORE_BUBBLE:
	{
		currentScore = id;
		nextScore = id * 4;
		deltaScore = (nextScore - currentScore) / 10;
		updateNumber();
	}
		break;
	default:
		break;
	}
}

void Bubble::setImage( const char* nameImg )
{
// 	if(strcmp(nameImg, nameImage.c_str()) == 0)
// 	{
// 
// 	}
// 	else
// 	{
// 		string s(nameImg);
// 		nameImage = s;
// 		Image::setImage((s + ".png").c_str());
		
//	}
	
}

void Bubble::setPos( float x, float y )
{
	Node::setPosition(x, y);
	rootX = x;
	rootY = y;
}

void Bubble::setNumber(int _id) {
	//_id = 1024;
	id = _id;
	int color = 0;
	//int color = sqrt(id);
	//bg->setImage("bubble/bgBubble3.png");
    int _id1   = id;
    while (_id1 / 2 != 0)
    {
        color++;
        _id1 = _id1 / 2;
    }
    color = color + 1;
	//bg->setColor(GameUtility::getColor(_id));
    bg->setImage(("bubble/cell_" + to_string(color % 10) + ".png").c_str());
	
	float sizeReal = label->getContentSize().width;
	float sizeWish;
	if(_id < 10)
	{
		label->setString("0");
		sizeWish = getContentSize().width * 0.3f;
	}
	else if(_id < 100)
	{
            label->setString("00");
		sizeWish = getContentSize().width * 0.6f;
	}
	else if(_id < 1000)
	{
            label->setString("000");
		sizeWish = getContentSize().width * 0.7f;
	}
	else
	{
            label->setString("0000");
		sizeWish = getContentSize().width * 0.8f;
	}
    sizeReal    = label->getContentSize().width;
	float scale = sizeWish / sizeReal;
	label->setScale(scale);
    label->setString(GameUtility::toString(id).c_str());
        // 	switch (color % 20) {
// 	case 1:
// 
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.4f * 255, 0.4f * 255, 0.4f * 255));
// 		break;
// 	case 2:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 3:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 4:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.3f * 255, 0.3f * 255, 0.3f * 255));
// 		break;
// 	case 5:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 6:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 7:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 8:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.3f * 255, 0.3f * 255, 0.3f * 255));
// 		break;
// 	case 9:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 10:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 11:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(1.0f * 255, 1.0f * 255, 1.0f * 255));
// 		break;
// 	case 12:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 13:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.9f * 255, 0.9f * 255, 0.9f * 255));
// 		break;
// 	case 14:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 15:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 16:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.2f * 255, 0.2f * 255, 0.2f * 255));
// 		break;
// 	case 17:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	case 18:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	case 19:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	case 0:
// 		setColor(GameUtility::getColor(_id));
// 		label->setColor(ccc3(0.99f * 255, 0.99f * 255, 0.99f * 255));
// 		break;
// 	}
	//label->setColor(ccc3(20, 20, 20));
	//label->setPosition(getWidth() * 0.5f, getHeight() * 0.5f);
// 	label->setPosition(getWidth() * 0.5f - label->getWidth() * 0.5f + getPositionX(),
// 		getHeight() * 0.5f - label->getHeight() * 0.5f + getPositionY());
}

void Bubble::setHeight( float height )
{
	setContentSize(Size(getContentSize().width, height));
	rootScaleX = getScaleX();
	bg->setHeight(height);
}

void Bubble::setWidth( float width )
{
    setContentSize(Size(width, getContentSize().height));
	rootScaleX = getScaleX();
	bg->setWidth(width);
	float sizeReal = label->getContentSize().height * rootScaleX;
	float sizeWish = width * 0.6f;
	float scale = sizeWish / sizeReal;
	//label->setScale(scale);
	//label->set
}

float Bubble::getRealHeight()
{
	return getContentSize().height;
}

float Bubble::getRealWidth()
{
	return getContentSize().width;
}

void Bubble::updateNumber()
{
	currentScore = currentScore + deltaScore;
	if (abs(nextScore - currentScore) < 2 * deltaScore)
	{
		setNumber(nextScore);
	}
	else
	{
		label->setString(GameUtility::toString(currentScore).c_str());
        label->runAction(Sequence::create(DelayTime::create(0.05f),
                                              CallFunc::create(AX_CALLBACK_0(Bubble::updateNumber, this)), NULL));
	}
}

void Bubble::doVibrate()
{
    if (numVibrate > 3)
    {
        stopAllActions();
        setPosition(rootX, rootY);
        return;
    }
    numVibrate++;
    float pX = rootX + 5 * (0.5 - GameUtility::getRandom());
    float pY = rootY + 5 * (0.5 - GameUtility::getRandom());
    runAction(Sequence::create(MoveTo::create(0.01 + GameUtility::getRandom() * 0.004, Vec2(pX, pY)),
                               CallFunc::create(AX_CALLBACK_0(Bubble::doVibrate, this)), NULL));
}

