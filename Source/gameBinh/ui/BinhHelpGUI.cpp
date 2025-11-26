#include "BinhHelpGUI.h"
#include "app/GameMgr.h"
#include "core/gui/SceneMgr.h"
using namespace ax::ui;
#define BTN_OK 11

BinhHelpGUI::BinhHelpGUI(void) : BaseLayer()
{
	//setKeypadEnabled(true);
}

BinhHelpGUI::~BinhHelpGUI(void)
{

}

bool BinhHelpGUI::init()
{
	BaseLayer::init(BinhHelpGUI::className);
	//setKeyboardEnabled(true);
	initWithBinaryFile("BinhHelpGUI.csb");
	return true;
}

void BinhHelpGUI::initGUI(){
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = (ImageView*) getControl("bg");
	Button* btnOk = customButton("btnClose", 1, bg);
	ui::ScrollView *scrollView = (ax::ui::ScrollView*)getControl("scrollView");
	Sprite* sprite = Sprite::create("table/help.jpg");
	sprite->setAnchorPoint(Vec2(0, 0));
	scrollView->addChild(sprite);
	//Text* lbHelp = (Text*)getControl("lbHelp", bg);
	//lbHelp->setString(LocalizedString::to("HELP_MOVE"));
}

void BinhHelpGUI::onEnterFinish()
{
	setShowHideAnimate(bg, true);
	setFog(true);


}

void BinhHelpGUI::onButtonRelease(ax::ui::Button* button, int id)
{
	backKeyPress();
}

void BinhHelpGUI::backKeyPress(){
	onClose();
}


std::string BinhHelpGUI::className = "BinhHelpGUI";




