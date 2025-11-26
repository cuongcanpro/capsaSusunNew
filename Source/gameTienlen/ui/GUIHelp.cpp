#include "GUIHelp.h"
#include "app/GameMgr.h"
#include "core/gui/SceneMgr.h"

#define BTN_OK 11

GUIHelp::GUIHelp(void) : BaseLayer()
{
	//setKeypadEnabled(true);
}

GUIHelp::~GUIHelp(void)
{

}

bool GUIHelp::init()
{
	BaseLayer::init(GUIHelp::className);
	//setKeyboardEnabled(true);
	initWithBinaryFile("LayerHelp.csb");
	return true;
}

void GUIHelp::initGUI(){
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();

	bg = (ImageView*) getControl("bg");
	Button* btnOk = customButton("btnOk", 1, bg);
	Text* lbHelp = (Text*)getControl("lbHelp", bg);
	lbHelp->setString(LocalizedString::to("HELP_MOVE"));
	iconHand = (ImageView*)getControl("iconHand", bg);
}

void GUIHelp::onEnterFinish()
{
	setShowHideAnimate(bg, true);
	setFog(true);

	iconHand->stopAllActions();
	iconHand->runAction(
		RepeatForever::create(
			Sequence::create(
				EaseSineOut::create(MoveTo::create(0.5, Vec2(150, 100))),
				DelayTime::create(0.5),
				MoveTo::create(0.0, Vec2(60, 100)),
				NULL
			)
		)
	);
}

void GUIHelp::onButtonRelease(ax::ui::Button* button, int id)
{
	backKeyPress();
}

void GUIHelp::backKeyPress(){
	onClose();
}


std::string GUIHelp::className = "GUIHelp";




