#include "MauBinhGroup.h"
#include "string"
#include "core/utils/TienlenGameSound.h"
#include <ctime>
#include <chrono>
#include "app/Constant.h"
#include "../logic/gamePlay/MaubinhPlayerCard.h"
#include "../logic/BinhGameLogic.h"
using namespace std::chrono;
#define NUMBER_RES "table/start_"

using namespace std;

MauBinhGroup::MauBinhGroup(void) : ResultGroup() {
    
}

MauBinhGroup::~MauBinhGroup(void)
{
}

void MauBinhGroup::showMauBinh(int type)
{
	if (isVisible())
		return;
	string resource = BinhGameLogic::getInstance()->getResourceBinh(type);
	title->setTexture(resource);
    showTitle();
	showEffectWin();
}

