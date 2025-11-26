#include "GroupBombHelp.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../Utility/GameSound.h"
#include "../Utility/GameUtility.h"
#include "../Utility/JNIUtils.h"

#define GUI_MENU_BTN_BACK  1
#define GUI_MENU_BTN_SOUND 2
#define GUI_MENU_BTN_PLAY  3
#define NUM_LEVEl 4

GroupBombHelp::GroupBombHelp(void)
{
	bg = Scale9Sprite::create("GuiGame/Bomb/bgBubble.png");
	addChild(bg);
	bg->setContentSize(Size(220, 100));
	bg->setAnchorPoint(Vec2(1, 0));
	bg->setPosition(bg->getContentSize().width * 0.5, -bg->getContentSize().height * 0.5);

	for (int i = 0; i < 3; i++) {
		touchEffect[i] = Sprite::create("GuiGame/Bomb/touchEffect.png");
		addChild(touchEffect[i]);
	}

	iconHand = Sprite::create("GuiGame/hand1.png");
	iconHand->setAnchorPoint(Vec2(0.1, 0.9));
	addChild(iconHand);

	iconRect = Sprite::create("GuiGame/Bomb/ce2ll.png");
	addChild(iconRect);

	lbHelp = Text::create("fdkj fsdkljf dklsjf lsjfsdk fsdlfj sdl", "fonts/tahomabd.ttf", 16);
	lbHelp->enableOutline(Color4B(181, 163, 10, 255), 2);
	lbHelp->setColor(Color3B(240, 240, 240));
	lbHelp->setTextAreaSize(Size(200, -1));
	lbHelp->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbHelp->setTextVerticalAlignment(TextVAlignment::CENTER);
	lbHelp->setPosition(Vec2(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.5 + 5));
	bg->addChild(lbHelp);

	string s = "GuiGame/Bomb/btnNext.png";
	btnNext = Button::create(s, s, s);
	addChild(btnNext);
	btnNext->setPositionY(-bg->getContentSize().height * 0.5 - btnNext->getContentSize().height * 0.5);
	btnNext->addClickEventListener([this](Object*) {
		GameSound::playClick();
		if (indexHelp < HELP_GUESS_THIRD_BOMB) {
			indexHelp++;
			Vec2 pos;
			PointGame p;
			if (indexHelp == HELP_GUESS_ONE_BOMB) {
				p.x = 3; p.y = 4;
			}
			else if (indexHelp == HELP_GUESS_TWO_BOMB) {
				p.x = 4; p.y = 4;
			}
			pos = GUIManager::getInstance().guiBomb->getPosCell(p.x, p.y);
			showHelp(pos, 0.5);
		}
		else {
			setVisible(false);
		}
	});
	//btnNext->setOpacity(0);
	//btnNext->setScale9Enabled(true);
	//btnNext->setContentSize(bg->getContentSize());
}


GroupBombHelp::~GroupBombHelp(void)
{

}

void GroupBombHelp::showHelp(Vec2 currentPos, float delayTime)
{
	hideHelp();
	bg->runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			EaseBackOut::create(ScaleTo::create(0.5, 1)),
			NULL
		)
	);
	iconHand->stopAllActions();
	iconHand->setVisible(false);
	iconRect->setVisible(false);
	btnNext->setVisible(false);
	for (int i = 0; i < 3; i++) {
		touchEffect[i]->setVisible(false);
	}
	this->currentPos = currentPos;
	if (indexHelp != HELP_GUESS_FOUR_BOMB && indexHelp != HELP_GUESS_THIRD_BOMB) {
		setPosition(currentPos.x - bg->getContentSize().width * 0.55, currentPos.y + bg->getContentSize().height * 0.55);
	}
	else {
		setPosition(currentPos.x + bg->getContentSize().width * 0.55, currentPos.y + bg->getContentSize().height * 0.65);
	}
	switch (indexHelp)
	{
	case HELP_TOUCH_TO_OPEN:
		lbHelp->setString("Touch cell to open");
		showHand();
		iconHand->runAction(
			RepeatForever::create(
				Sequence::create(
					DelayTime::create(delayTime + 0.2),
					Show::create(),
					EaseSineOut::create(MoveTo::create(0, Vec2(iconHand->getPositionX() + 100, iconHand->getPositionY() + 100))),
					MoveTo::create(0.2, iconHand->getPosition()), 
					DelayTime::create(0.5),
					Hide::create(),
					DelayTime::create(0.5),
					NULL
				)
			)
		);
		break;
	case HELP_ONE_BOMB:
		lbHelp->setString("There is 1 bomb surround this cell.");
		//btnNext->setVisible(true);
		showNext(delayTime);
		showRect(delayTime);
		break;
	case HELP_GUESS_ONE_BOMB:
	case HELP_GUESS_TWO_BOMB:
	case HELP_GUESS_THIRD_BOMB:
	case HELP_GUESS_FOUR_BOMB:
		if (indexHelp == HELP_GUESS_THIRD_BOMB || indexHelp == HELP_GUESS_FOUR_BOMB) {
			bg->setTexture("GuiGame/Bomb/bgBubbleLeft.png");
		}
		lbHelp->setString("Touch and hold in 0.5s to mark bomb in this cell");
		showHand();
		showHandHold(delayTime);
		break;
	case HELP_TWO_BOMB:
		lbHelp->setString("There is 2 bombs surround this cell.");
		showNext(delayTime);
		showRect(delayTime);
		break;
	
		lbHelp->setString("Touch and hold in 0.5s to mark bomb in this cell");
		showHand();
		showHandHold(delayTime);
		break;
	default:
		break;
	}
}

bool GroupBombHelp::checkCanAction(int row, int column, HelpType type)
{
	if (isVisible() == false)
		return true;
	if (type == HELP_OPEN) {
		if (indexHelp != HELP_TOUCH_TO_OPEN)
			return false;
		if (row != 3 || column != 2)
			return false;
		return true;
	}
	else if (type == HELP_GUESS) {
		if (indexHelp != HELP_GUESS_ONE_BOMB && indexHelp != HELP_GUESS_TWO_BOMB && indexHelp != HELP_GUESS_THIRD_BOMB && indexHelp != HELP_GUESS_FOUR_BOMB)
			return false;
		if (indexHelp == HELP_GUESS_ONE_BOMB) {
			if (row != 3 || column != 4)
				return false;
			return true;
			
		}
		else if (indexHelp == HELP_GUESS_TWO_BOMB) {
			if (row != 4 || column != 4)
				return false;
			return true;
		}
		else if (indexHelp == HELP_GUESS_THIRD_BOMB) {
			if (row != 2 || column != 0)
				return false;
			return true;
		}
		else if (indexHelp == HELP_GUESS_FOUR_BOMB) {
			if (row != 0 || column != 1)
				return false;
			return true;
		}
	}
}

void GroupBombHelp::showNext(float delayTime)
{
	btnNext->stopAllActions();
	btnNext->runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			CallFunc::create(AX_CALLBACK_0(GroupBombHelp::actionNext, this)),
			NULL
		)
	);
}

void GroupBombHelp::actionNext()
{
	btnNext->setVisible(true);
	btnNext->runAction(
		RepeatForever::create(
			Sequence::create(
				ScaleTo::create(0.2, 1.1),
				ScaleTo::create(0.2, 1.0),
				NULL
			)
		)
	);
}

void GroupBombHelp::showHand()
{
	iconHand->stopAllActions();
	Vec2 pos = convertToNodeSpace(currentPos);
	iconHand->setPosition(pos);
}

void GroupBombHelp::showHandHold(float delayTime)
{
	iconHand->runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			Show::create(),
			NULL
		)
	);
	Vec2 pos = convertToNodeSpace(currentPos);
	for (int i = 0; i < 3; i++) {
		touchEffect[i]->setVisible(true);
		touchEffect[i]->setPosition(pos);
		touchEffect[i]->stopAllActions();
		touchEffect[i]->setScale(0);
		touchEffect[i]->runAction(
			Sequence::create(
				DelayTime::create(0.1 * i + delayTime),
				CallFuncN::create(AX_CALLBACK_1(GroupBombHelp::effectTouch, this)),
				NULL
			)
		);
	}
}

void GroupBombHelp::showRect(float delayTime)
{
	iconRect->stopAllActions();
	Vec2 pos = convertToNodeSpace(currentPos);
	iconRect->setPosition(pos);
	iconRect->runAction(
		Sequence::create(
			DelayTime::create(delayTime),
			Show::create(),
			NULL
		)
	);
}

void GroupBombHelp::hideHelp()
{
	iconHand->stopAllActions();
	iconHand->setVisible(false);
	iconRect->setVisible(false);
	btnNext->setVisible(false);
	bg->setScale(0);
}

void GroupBombHelp::effectTouch(Node* sender)
{
	sender->runAction(
		//Sequence::create(
		//	DelayTime::create(0.1 + delayTime),
		RepeatForever::create(
			Sequence::create(
				Spawn::create(
					ScaleTo::create(0.5, 1),
					FadeOut::create(0.5),
					NULL
				),
				Spawn::create(
					ScaleTo::create(0, 0),
					FadeIn::create(0),
					NULL
				),
				NULL
			)
		)
		//	NULL
		//)
	);
}
