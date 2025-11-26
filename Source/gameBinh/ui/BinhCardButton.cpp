#include "BinhCardButton.h"
#include "core/utils/StringUtility.h"
#include "core/gui/SceneMgr.h"

BinhCardButton::BinhCardButton(void)
{
	this->id = 52;
	string s = getResource();
	Button::init(s, s, s);
	isSelect = false;
}


BinhCardButton::BinhCardButton(int id)
{
	this->id = id;
	string s = getResource();
	Button::init(s, s, s);
}

BinhCardButton::BinhCardButton(int index, int id, BinhTruyenThong* myPlayer) : BinhCardButton(id)
{
	this->index = index;
	addTouchEventListener(AX_CALLBACK_2(BinhTruyenThong::touchEvent, myPlayer));
	isSelect = false;
}

BinhCardButton::BinhCardButton(int index, int id, BinhCardButtonType type, BinhTinhAt* binh) : BinhCardButton(id)
{
	this->index = index;
	this->type = type;
	addTouchEventListener(AX_CALLBACK_2(BinhTinhAt::touchEvent, binh));
	isSelect = false;
}


BinhCardButton::~BinhCardButton(void)
{

}

void BinhCardButton::setIdCard(int id)
{
	this->id = id;
	string s = getResource();
	loadTextures(s.c_str(), s, s);
}

string BinhCardButton::getResource()
{
	if (id > 52)
		return "";

	std::string s;
	if (id == 52)
		s = "table/Cards/labai_52.png";
	else
	{
		s = "table/Cards/labai_%id.png";
		s = StringUtility::replaceAll(s, "%id", id);
	}
	return s;
}

void BinhCardButton::setDark( bool isDark )
{
	if(isDark)
	{
		Color3B color = {120, 120, 120};
		setColor(color);
	}
	else
	{
		Color3B color = {255, 255, 255};
		setColor(color);
	}
}


void BinhCardButton::touchEvent(Object *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		AXLOGD("TOUCH BEGAN ");
		break;

	case Widget::TouchEventType::MOVED:
		AXLOGD("TOUCH MOVE ");
		break;

	case Widget::TouchEventType::ENDED:
	{
		
	}
	break;

	case Widget::TouchEventType::CANCELED:
		
		break;

	default:
		break;
	}
}

void BinhCardButton::setCardSize(float scale)
{

}

float BinhCardButton::getCardWidth()
{
	return getContentSize().width * getScaleX();
}

float BinhCardButton::getCardHeight()
{
	return getContentSize().height * getScaleY();
}

void BinhCardButton::setPosDefaultY(float pos)
{
	posDefaultY = pos;
}

void BinhCardButton::setPosDefaultX(float pos)
{
	posDefaultX = pos;
}

void BinhCardButton::setDefaultPos()
{
	stopAllActions();
	setPosition(Vec2(posDefaultX, posDefaultY));
	isSelect = false;
}

void BinhCardButton::saveDefaultPos()
{
	setPosDefaultX(getPositionX());
	setPosDefaultY(getPositionY());
	rootScale = getScale();
	rootZOrder = getLocalZOrder();
	rotateDefault = getRotation();
}

void BinhCardButton::saveScale()
{
	rootScale = getScale();
}

void BinhCardButton::saveZOrder()
{
	rootZOrder = getLocalZOrder();
}

ax::Vec2 BinhCardButton::getDefaultPos()
{
	return Vec2(posDefaultX, posDefaultY);
}

void BinhCardButton::moveCard(bool up)
{
	float posY = up ? (posDefaultY + 10) : posDefaultY;
	runAction(MoveTo::create(0.1, Vec2(getPositionX(), posY)));
}

void BinhCardButton::moveToDefault(float time, float delayTime)
{
	stopAllActions();
	setDark(false);
	if (time == 0) {
		setPosition(getDefaultPos());
		setScale(rootScale);
		setLocalZOrder(rootZOrder);
	}
	else {
		runAction(Sequence::create(
			DelayTime::create(delayTime),
			EaseExponentialOut::create(MoveTo::create(time, getDefaultPos())),
			CallFuncN::create(AX_CALLBACK_1(BinhCardButton::callbackMoveCard, this)),
			NULL
		));
		runAction(ScaleTo::create(time, rootScale));
	}
	
}

void BinhCardButton::callbackMoveCard(Node* pSender)
{
	setLocalZOrder(rootZOrder);
}

bool BinhCardButton::IsSelect()
{
	return isSelect && isVisible();
}

void BinhCardButton::setSelect(bool select)
{
	isSelect = select;
	if (isSelect)
		setColor(Color3B(240, 240, 100));
	else
		setColor(Color3B(255, 255, 255));
}

void BinhCardButton::saveInfoCard()
{
	saveDefaultPos();
	saveScale();
	saveZOrder();
}

void BinhCardButton::showCard(Vec2 posCenter)
{
	saveIdCard = id;
	setIdCard(52);

	runAction(Sequence::create(
		Spawn::create(
			MoveTo::create(0.2, posCenter),
			RotateTo::create(0.2, 0),
			NULL
		),
		//ScaleTo::create(0.2, 0, getScaleY()),
		CallFuncN::create(AX_CALLBACK_1(BinhCardButton::callbackShowCard, this)),
		NULL
	));

	/*runAction(Sequence::create(
		ScaleTo::create(0.2, 0, getScaleY()),
		CallFuncN::create(AX_CALLBACK_1(BinhCardButton::callbackShowCard, this)),
		NULL
	));*/
}

void BinhCardButton::callbackShowCard(Node* pSender)
{
	setIdCard(saveIdCard);
	runAction(
		Spawn::create(
			EaseBackOut::create(MoveTo::create(0.5, getDefaultPos())),
			EaseBackOut::create(RotateTo::create(0.5, rotateDefault)),
			NULL
		)
	);
	//runAction(ScaleTo::create(0.2, rootScale));
}

void BinhCardButton::showAt()
{
	runAction(Sequence::create(
		EaseBackOut::create(ScaleTo::create(0.5, rootScale * 1.3)),
		DelayTime::create(2.0),
		EaseBackIn::create(ScaleTo::create(0.5, rootScale)),
		NULL
	));
}
