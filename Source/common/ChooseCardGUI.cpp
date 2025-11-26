#include "ChooseCardGUI.h"
#include "app/GameMgr.h"
#include "core/gui/SceneMgr.h"

#define BTN_OK 0
#define BTN_CARD_0 1
#define BTN_CARD_1 2

ChooseCardGUI::ChooseCardGUI(void) : BaseLayer()
{
	//setKeypadEnabled(true);
}

ChooseCardGUI::~ChooseCardGUI(void)
{

}

bool ChooseCardGUI::init()
{
	BaseLayer::init(ChooseCardGUI::className);
	//setKeyboardEnabled(true);
	initWithBinaryFile("ChooseCardGUI.csb");
	return true;
}

void ChooseCardGUI::initGUI() {
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = (ImageView*)getControl("bg");
	Button* btnOk = customButton("btnOk", BTN_OK, bg);
	btnCard0 = customButton("btnCard_0", BTN_CARD_0, bg);
	btnCard1 = customButton("btnCard_1", BTN_CARD_1, bg);
	Text* lbHelp = (Text*)getControl("lbHelp", bg);
	lbHelp->setString(LocalizedString::to("CHOOSE_CARD"));
	iconSelect = (ImageView*)getControl("iconSelect", bg);
}

void ChooseCardGUI::onEnterFinish()
{
	setShowHideAnimate(bg, true);
	setFog(true);
	this->selectCard(gameMgr->typeCard);
}

void ChooseCardGUI::selectCard(int select)
{
	if (select < 0)
		select = AXRANDOM_0_1() > 0.5 ? 0 : 1;
	gameMgr->typeCard = select;
	iconSelect->setVisible(true);
	if (select == 0) {
		iconSelect->setPositionX(btnCard0->getPositionX());
	}
	else {
		iconSelect->setPositionX(btnCard1->getPositionX());
	}
}

void ChooseCardGUI::onButtonRelease(ax::ui::Button* button, int id)
{
	switch (id)
	{
	case BTN_OK:
		UserDefault::getInstance()->setIntegerForKey("typeCard", gameMgr->typeCard);
		UserDefault::getInstance()->flush();
		backKeyPress();
		break;
	case BTN_CARD_0:
		this->selectCard(0);
		break;
	case BTN_CARD_1:
		this->selectCard(1);
		break;
	default:
		break;
	}
	
}

void ChooseCardGUI::backKeyPress() {
	onClose();
}

std::string ChooseCardGUI::className = "ChooseCardGUI";




