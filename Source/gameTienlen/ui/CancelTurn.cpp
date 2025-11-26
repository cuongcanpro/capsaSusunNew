#include "CancelTurn.h"
#include <cmath>  
#include <string>
#include "core/utils/StringUtility.h"
#include "app/GameMgr.h"
CancelTurn::CancelTurn(void)
{
	if (gameMgr->setting.isVietnam) {
		imgCancel = Sprite::create("Game/textViet/cancel.png");
	}
	else {
		imgCancel = Sprite::create("Game/cancelTurn.png");
	}
	
	addChild(imgCancel);

}

CancelTurn::~CancelTurn(void)
{
}

void CancelTurn::startEffect()
{
	setVisible(true);
	//schedule(schedule_selector(CancelTurn::update), 0.1);
	count = 0;
	imgCancel->stopAllActions();
	imgCancel->runAction(
		RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.3, Vec2(20, 0)),
				MoveTo::create(0.3, Vec2(0, 0)),
				NULL
			)
		)
	);
}

void CancelTurn::stopEffect()
{
	setVisible(false);
}

void CancelTurn::update(float dt)
{
	for (int i = 0; i < 5; i++) {
		if (i <= count)
			arrayArrow[i]->setTexture("Game/viewArrow.png");
		else
			arrayArrow[i]->setTexture("Game/viewBar.png");
	}
	count++;
	if (count == 5)
		count = 0;
}
