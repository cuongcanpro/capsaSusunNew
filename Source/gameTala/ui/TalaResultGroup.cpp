#include "TalaResultGroup.h"
#include "string"
#include <ctime>
#include <chrono>
#include "app/Constant.h"
#include "../logic/TalaGameLogic.h"
#include "app/GameMgr.h"
using namespace std::chrono;
#define NUMBER_RES "table/start_"

using namespace std;

TalaResultGroup::TalaResultGroup(void) : ResultGroup()
{

}

TalaResultGroup::~TalaResultGroup(void)
{
}

void TalaResultGroup::showMauBinh(int type)
{
	if (isVisible())
		return;
	string resource = "CommonEffect/nhat.png";

	if (type == TalaGameLogic::RANK_NHAT || type == TalaGameLogic::U_KHAN || type == TalaGameLogic::U_TRON || type == TalaGameLogic::U_NORMAL || type == TalaGameLogic::AN_CHOT) {
		resource = "CommonEffect/nhat.png";
		switch (type)
		{
		case TalaGameLogic::RANK_NHAT:
			resource = "CommonEffect/nhat.png";
			break;
		case TalaGameLogic::U_KHAN:
			resource = "CommonEffect/uKhan.png";
			break;
		case TalaGameLogic::U_TRON:
			resource = "CommonEffect/uTron.png";
			break;
		case TalaGameLogic::U_NORMAL:
			resource = "CommonEffect/u.png";
			break;
		case TalaGameLogic::AN_CHOT:
			resource = "CommonEffect/anChot.png";
			break;
		default:
			break;
		}
		showEffectWin();
	}
	else {
		resource = "CommonEffect/bet.png";
		switch (type)
		{
		case TalaGameLogic::RANK_MOM:
			resource = "CommonEffect/mom.png";
			break;
		case TalaGameLogic::RANK_BET:
			resource = "CommonEffect/bet.png";
			break;
		case TalaGameLogic::RANK_BA:
			resource = "CommonEffect/ba.png";
			break;
		case TalaGameLogic::RANK_NHI:
			resource = "CommonEffect/nhi.png";
			break;
		default:
			break;
		}
        showEffectLose();
	}
	title->setTexture(resource);
    showTitle();
    runAction(Sequence::create(DelayTime::create(5.0), Hide::create(), NULL));
}

