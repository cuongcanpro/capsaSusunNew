#include "CardButton.h"
#include "core/utils/StringUtility.h"
#include "../logic/GameLogic.h"
#include "BoardScene.h"
#include "core/gui/SceneMgr.h"
#include "core/utils/TienlenGameSound.h"

CardButton::CardButton(void)
{
}

CardButton::CardButton(int id, SelfUI* myPlayer)
{
	this->id = id;
	string s = getResource();
	init(s, s, s);
	addTouchEventListener(AX_CALLBACK_2(CardButton::touchEvent, this));
	this->myPlayer = myPlayer;
	isSelect = false;
}

CardButton::~CardButton(void)
{

}

void CardButton::setIdCard(int id)
{
	this->id = id;
	string s = getResource();
	loadTextures(s.c_str(), s, s);
}

string CardButton::getResource()
{
	if (gameMgr->fakeApp == 1) {
		return "ca/ca_" + to_string(id) + ".png";
	}
	if (id > 52)
		return "";

	std::string s;
	if (id == 52)
	{
		s = "cards/labai_52.png";
			return "cards/labai_52.png";
		
	}
	else
	{
		int convertId;
		if (id < 48)
			convertId = id + 4;
		else if (id >= 48) {
			convertId = id - 48;
		}
			s = "cards/labai_%id.png";
		
		s = StringUtility::replaceAll(s, "%id", convertId);
	}
	return s;
}

void CardButton::setDark( bool isDark )
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


void CardButton::touchEvent(Object *pSender, Widget::TouchEventType type)
{
	if (gameMgr->fakeApp == 1) {
		switch (type)
		{
		case Widget::TouchEventType::BEGAN: {
			break;
		}
		case Widget::TouchEventType::MOVED: {
			
			break;
		}
		case Widget::TouchEventType::ENDED:
		{
			TienlenGameSound::playClickCard();
		}
		break;

		case Widget::TouchEventType::CANCELED:
			
			break;
		default:
			break;
		}
	}
	else {
		switch (type)
		{
		case Widget::TouchEventType::BEGAN: {
			AXLOGD("TOUCH BEGAN ");
			isTouchMove = false;
			lastPos = this->getTouchBeganPosition();
			break;
		}
		case Widget::TouchEventType::MOVED: {
			float distance = lastPos.getDistance(this->getTouchMovePosition());
			if (distance > 3) {
				isTouchMove = true;
				//AXLOGD("TOUCH MOVE ");
				if (!isSelect) {
					setSelect(true);

					//	myPlayer->moveCard();
				}
				myPlayer->onMoveCard(this->getTouchMovePosition(), this->getTouchBeganPosition(), id);
			}

			lastPos = this->getTouchBeganPosition();
			break;
		}
		case Widget::TouchEventType::ENDED:
		{
			if (isTouchMove) {
				isTouchMove = false;
				BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
				gui->checkCanThrowCard();
				return;
			}
			AXLOGD("TOUCH END ");
			if (!isSelect) {
				setSelect(true);
				GameLogic::getInstance()->checkAutoCard();
			}
			else {
				setSelect(false);
			}
			stopAllActions();
			moveCard(isSelect);
			BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
			gui->checkCanThrowCard();
			TienlenGameSound::playClickCard();
		}
		break;

		case Widget::TouchEventType::CANCELED:
			AXLOGD("TOUCH CANCEL ");
			if (isTouchMove) {
				isTouchMove = false;
				BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
				gui->checkCanThrowCard();
				return;
			}
			break;
		default:
			break;
		}
	}
}

void CardButton::setCardSize(float scale)
{

}

float CardButton::getCardWidth()
{
	return this->getContentSize().width * this->getScale();
}

float CardButton::getCardHeight()
{
	return this->getContentSize().height * this->getScale();
}

void CardButton::setPosDefaultY(float pos)
{
	posDefaultY = pos;
}

void CardButton::setPosDefaultX(float pos)
{
	posDefaultX = pos;
}

void CardButton::setDefaultPos()
{
	stopAllActions();
	setPosition(Vec2(posDefaultX, posDefaultY));
	isSelect = false;
}

void CardButton::moveCard(bool up)
{
	float posY = up ? (posDefaultY + 10) : posDefaultY;
	runAction(MoveTo::create(0.1f, Vec2(getPositionX(), posY)));
}

bool CardButton::IsSelect()
{
	return isSelect && isVisible();
}

void CardButton::setSelect(bool select)
{
	isSelect = select;
	stopAllActions();
	moveCard(isSelect);
}

void CardButton::hideCard()
{
	runAction(
		Sequence::create(
			ScaleTo::create(0.3, 0, getScaleY()),
			CallFuncN::create(AX_CALLBACK_0(CardButton::callbackHideCard, this)),
			NULL
		)
	);
}

void CardButton::callbackHideCard()
{
	string s = "ca/ca_52.png";
	loadTextures(s.c_str(), s, s);
	runAction(
		ScaleTo::create(0.2, getScaleY(), getScaleY())
	);
}


void CardButton::resetCard()
{
	string s = "ca/ca_52.png";
	loadTextures(s.c_str(), s, s);
}

void CardButton::openCard()
{
	AXLOGD("ID Card %i ", id);
	runAction(
		Sequence::create(
			ScaleTo::create(0.2, 0, getScaleY()),
			CallFuncN::create(AX_CALLBACK_0(CardButton::callbackOpenCard, this)),
			NULL
		)
	);
}

void CardButton::callbackOpenCard()
{
	string s = getResource();
	loadTextures(s.c_str(), s, s);
	runAction(
		ScaleTo::create(0.2, getScaleY(), getScaleY())
	);
}

void CardButton::eatCard()
{
	runAction(
		Sequence::create(
			ScaleTo::create(0.2, 0, 0),
			Hide::create(),
			//CallFuncN::create(AX_CALLBACK_0(CardButton::callbackHideCard, this)),
			NULL
		)
	);
}
