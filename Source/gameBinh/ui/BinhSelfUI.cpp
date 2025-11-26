#include "BinhSelfUI.h"
#include "../logic/BinhGameLogic.h"
#include "BinhBoardScene.h"
#include "core/gui/SceneMgr.h"
#include "core/utils/TienlenGameSound.h"
#define BTN_SELF_UI_ARRANGE 6
#define BTN_SELF_UI_CHOOSE 2
#define BTN_SELF_UI_CANCEL 3
#define BTN_SELF_UI_EMO 4
#define BTN_SELF_UI_CHAT 5

#define PADX_CARD 0.4
//#define BTN_ARRANGE 4
BinhSelfUI::BinhSelfUI(Node* panel, efk::EffectManager* manager) : BinhPlayerUI()
{
    this->manager = manager;
	layout = panel;
	initGUI();
}

BinhSelfUI::~BinhSelfUI()
{

}

void BinhSelfUI::initGUI()
{
	BinhPlayerUI::initGUI();
	initMyUI();
}

void BinhSelfUI::initMyUI()
{
	for (int i = 0; i < NUM_CHI; i++) {
		arrayImgChi[i] = (ImageView*)layout->getChildByName("chi" + to_string(i + 1));
	}
	ImageView* bgProgress = (ImageView*)layout->getChildByName("bgProgress");
	lbLevel = (Text*)bgProgress->getChildByName("lbLevel");
	progress = (LoadingBar*)bgProgress->getChildByName("progress");
}

void BinhSelfUI::initGroupCard()
{
	BinhPlayerUI::initGroupCard();
}

void BinhSelfUI::newGame()
{
	BinhPlayerUI::newGame();
	disableAllChi();
}

void BinhSelfUI::updateDealCard(int num)
{
	if (arrayCard2[num]->isVisible())
		arrayCard1[num]->setVisible(false);
	else
		arrayCard1[num]->setVisible(true);
	//arrayCard1[num]->showCard();
}

void BinhSelfUI::endDealCard()
{
	BinhPlayerUI::endDealCard();
}

void BinhSelfUI::updateCard()
{
	BinhPlayerUI::updateCard();
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(MY_INDEX);
	int cardKind = info->PlayerCard()->GetPlayerCardsKind(false);
	BinhGameLogic::getInstance()->showDarkCard(*info->PlayerCard(), cardKind, false, arrayCard1);
}

void BinhSelfUI::ready()
{
	BinhPlayerUI::ready();
	updateCard();
	string resource = BinhGameLogic::getInstance()->getResourceBinh(BinhGameLogic::getInstance()->getCardKindReady());
	if (resource.compare("") != 0) {
		imgEffectChi->setTexture(resource);
		imgEffectChi->setVisible(true);
		imgEffectChi->setPositionX(arrayCard1[2]->getDefaultPos().x);
		imgEffectChi->setPositionY(arrayCard1[2]->getDefaultPos().y - arrayCard1[2]->getCardHeight() * 0.4 + imgEffectChi->getContentSize().height * 0.5);
	}
}

void BinhSelfUI::endCard()
{
	BinhPlayerUI::endCard();
	updateCard();
}

void BinhSelfUI::chiIndex(char chi)
{
	BinhPlayerUI::chiIndex(chi);
	if (chi <= CHI_3) {
		disableAllChi();
		arrayImgChi[chi - 1]->loadTexture("table/numChi" + to_string(chi) + "Big.png");
	}
	else {
		// ket thuc viec so chi
		disableAllChi();
	}
}

void BinhSelfUI::compareChi(char chi, double money, int result)
{
	BinhPlayerUI::compareChi(chi, money, result);
	if (money > 0) {
		TienlenGameSound::playChiWin();

	}
	else {
		TienlenGameSound::playChiLose();
	}
}

void BinhSelfUI::summary(double money)
{
	BinhPlayerUI::summary(money);
	disableAllChi();
	if (money >= 0)
	{
		TienlenGameSound::playSounds_win();
		int randValue = AXRANDOM_0_1() * 3;
		/*switch (randValue)
		{
		case 0:
			TienlenGameSound::playSoundwin_1();
			break;
		case 1:
			TienlenGameSound::playSoundwin_2();
			break;
		case 2:
			TienlenGameSound::playSoundwin_3();
			break;
		default:
			break;
		}*/
	}
	else
	{
		TienlenGameSound::playSounds_lose();
		//TienlenGameSound::playSoundThua();
	}
}

void BinhSelfUI::sapBai(double money, SapBaiType sapTye)
{
	BinhPlayerUI::sapBai(money, sapTye);
	if (sapTye == SapBaiType::BAT_SAP) {
		TienlenGameSound::playSoundbatsapnay();
	}
	else {
		TienlenGameSound::playSoundsaproi();
	}
}

void BinhSelfUI::updateLevel()
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	lbLevel->setString("Level " + to_string(info->getLevel() + 1));
	progress->setPercent(info->getPercentLevel());
	borderAvatar->loadTexture(info->getAvatarLevel());
}

void BinhSelfUI::updateMoney()
{
	BinhPlayerUI::updateMoney();
	updateLevel();
}

void BinhSelfUI::disableAllChi()
{
	for (int i = 0; i < NUM_CHI; i++) {
		arrayImgChi[i]->loadTexture("table/numChi" + to_string(i + 1) + "Dis.png");
	}
}
