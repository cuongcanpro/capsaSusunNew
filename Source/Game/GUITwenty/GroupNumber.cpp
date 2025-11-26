#include "GroupNumber.h"
#include <cmath>  
#include <string>
#include "Game/Utility/GameUtility.h"


GroupNumber::GroupNumber(void)
{
	ball = new GameImage("Merge/1.png");
	addChild(ball);
	setContentSize(ball->getImg()->getContentSize());

	label = Text::create("SCORE: 0", "fonts/tahomabd.ttf", 45);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(label);

	ball->setLocalZOrder(2);
	label->setLocalZOrder(2);

	setNumber(0);

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
}

void GroupNumber::setNumber(int number)
{
	this->number = number;
	label->setString(GameUtility::toString(number).c_str());
	std::string s = "GuiGame/Merge/" + GameUtility::toString(number % 25) + ".png";
	ball->getImg()->setTexture(s.c_str());
}


void GroupNumber::increaseNumber()
{
	number = number + 1;

	for (int i = 0; i < 3; i++) {
		GameImage *ball = new GameImage("bgNumber.png");
		addChild(ball);
		ball->setColor(this->ball->getImg()->getColor());
		ball->getImg()->setVisible(false);
		ball->runAction(
			Sequence::create(
				DelayTime::create(0.1 * i),
				Show::create(),
				Spawn::create(
					ScaleTo::create(0.5, 10),
					FadeOut::create(0.5),
					NULL
				),
				RemoveSelf::create(),
				NULL
			)
		);
	}

	runAction(
		Sequence::create(
			DelayTime::create(0.2),
			CallFunc::create(AX_CALLBACK_0(GroupNumber::callback1, this)),
			NULL
		)
	);
}

void GroupNumber::callback1()
{
	label->runAction(
		Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.4, 0)),
			CallFunc::create(AX_CALLBACK_0(GroupNumber::callback2, this)),
			NULL
		)
	);
}

void GroupNumber::callback2()
{
	setNumber(number);
	label->runAction(
		Sequence::create(
			EaseBounceOut::create(ScaleTo::create(0.5, 2)),
			//CallFunc::create(this, callfunc_selector(Number::effectEndGame)),
			NULL
		)
	);
}

GroupNumber::~GroupNumber(void)
{
}
