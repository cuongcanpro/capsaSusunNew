#include "GUILevel.h"
#include "core/utils/LanguageMgr.h"
#include "../InGameMgr.h"
#include "Game/Utility/JNIUtils.h"
#include "LobbyScene.h"
#include "../logic/GameLogic.h"

#define NUM_DOT  42

#define WIDTH_ROW 230
#define HEIGHT_ROW 300
GUILevel::GUILevel()
{
}

GUILevel::~GUILevel()
{

}

bool GUILevel::init()
{
	BaseLayer::init();
//	setKeyboardEnabled(true);
	initGUI();

	return true;
}

void GUILevel::initGUI()
{
	Size size = Director::getInstance()->getVisibleSize();

	// BG LOADING
	auto bg = Sprite::create("Game/bg.jpg");
	bg->setScaleX(size.width / bg->getContentSize().width);
	bg->setScaleY(size.height / bg->getContentSize().height);
	//bg->setScale(_scale);
	addChild(bg);
	bg->setPosition(size.width / 2, size.height / 2);
	bg->setOpacity(10);
	bg->runAction(
		Sequence::create(
			FadeIn::create(0.5),
			NULL
		)
	);

	Text* labelStt = Text::create(LocalizedString::to("HELP_LEVEL"), "Font/tahomabd.ttf", 20);
	labelStt->enableOutline(Color4B(0, 0, 0, 255), 1);
	labelStt->setTextHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(labelStt);
	labelStt->setAnchorPoint(Vec2(0.5, 0.5f));
	labelStt->setPosition(Vec2(size.width * 0.5, size.height * 0.9));

	

	string resource = "Board/BlueTheme/btnBack.png";
	Button* btnClose = Button::create(resource, resource, resource);
	btnClose->setPosition(Vec2(size.width - btnClose->getContentSize().width * 0.8, size.height - btnClose->getContentSize().height * 0.8));
	addChild(btnClose);

	btnClose->addClickEventListener([this](Object*) {
		backKeyPress();
	});

	ui::Scale9Sprite *bgList = ui::Scale9Sprite::create("Board/Game/popup.png");
	bgList->setContentSize(Size(size.width * 0.95, HEIGHT_ROW));
	bgList->setPosition(Vec2(size.width * 0.5, size.height * 0.5));
	bgList->setOpacity(120);
	this->addChild(bgList);

	float pad = 15;
	listTop = TableView::create(this, Size(bgList->getContentSize().width - pad, bgList->getContentSize().height - pad));
	listTop->setDirection(TableView::Direction::HORIZONTAL);
	listTop->setAnchorPoint(Vec2(0.0f, 0));
	//listTop->setContentOffset(ccp(0,0));
	listTop->setPosition(Vec2(pad * 0.5, pad * 0.5));
	listTop->setDelegate(this);
	listTop->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	bgList->addChild(listTop);

	/*resource = "btnContact.png";
	Button* btnContact = Button::create(resource, resource, resource);
	btnContact->setPosition(Vec2(size.width * 0.5, btnContact->getContentSize().height * 0.8));
	addChild(btnContact);

	btnContact->addClickEventListener([this](Object*) {
		JNIUtils::openUrl("fb://facewebmodal/f?href=https://www.facebook.com/gamecotuongonline");
	});
	btnContact->setVisible(false);*/

	/*Text* labelStt1 = Text::create(LocalizedString::to("NOTE_LEVEL"), "Font/tahomabd.ttf", 20);
	labelStt1->enableOutline(Color4B(0, 0, 0, 255), 1);
	labelStt1->setTextHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(labelStt1);
	labelStt1->setAnchorPoint(Vec2(0.5, 0.5f));
	labelStt1->setPosition(Vec2(size.width * 0.5, btnContact->getPositionY() + 40));
	labelStt1->setVisible(false);*/
}

void GUILevel::onEnterFinish()
{
	listTop->reloadData();
}

void GUILevel::backKeyPress() {
	sceneMgr->openScene(LobbyScene::className);
}

void GUILevel::tableCellTouched(ax::extension::TableView* table, ax::extension::TableViewCell* cell)
{
	AXLOGD("cell touched at index: %i", cell->getIdx());
	if (cell->getIdx() <= gameMgr->currentPosture) {
		GameLogic::getInstance()->startPosture(cell->getIdx());
		JNIUtils::sendEvent(("play_level_" + to_string(cell->getIdx())).c_str(), "1");
		inGameMgr->openBoardScene(true);
	}
	else {
		ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("PREVIOUS_LEVEL"));
	}

}
ax::Size GUILevel::tableCellSizeForIndex(ax::extension::TableView *table, ssize_t idx)
{
	return Size(WIDTH_ROW, HEIGHT_ROW);
}
ax::extension::TableViewCell* GUILevel::tableCellAtIndex(ax::extension::TableView *table, ssize_t idx)
{
	TableViewCell *cell = (TableViewCell*)table->dequeueCell();
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	int index = idx;
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();

		ImageView* img = ImageView::create("iconLevel.png");
		cell->addChild(img, 1, 1);
		img->setPosition(Vec2(WIDTH_ROW * 0.5, HEIGHT_ROW * 0.6));

		Label* lb = Label::create();
		lb->setSystemFontSize(30);
		lb->setString("Level " + to_string(index + 1));
		lb->enableBold();
		cell->addChild(lb, 2, 2);
		lb->setPosition(WIDTH_ROW * 0.5, 70);
		//lb->setLocalZOrder(2);
		lb->enableOutline(Color4B(100, 20, 20, 255), 2);
	}
	ImageView* img = (ImageView*) cell->getChildByTag(1);
	Label* lb = (Label*) cell->getChildByTag(2);
	if (index > gameMgr->currentPosture) {
		((Scale9Sprite*)img->getVirtualRenderer())->setState(Scale9Sprite::State::GRAY);
		//img->setOpacity(100);
		lb->setString("Lock");
		lb->setColor(Color3B(100, 100, 100));
	}
	else {
		((Scale9Sprite*)img->getVirtualRenderer())->setState(Scale9Sprite::State::NORMAL);
		//img->setOpacity(255);
		lb->setString("Level " + to_string(index + 1));
                lb->setColor(Color3B(255, 255, 255));
	}
	return cell;
}

ssize_t GUILevel::numberOfCellsInTableView(ax::extension::TableView *table)
{
	return 13;
}
const std::string GUILevel::className = "GUILevel";
