#include "UserInfoGUI.h"
#include "core/gui/SceneMgr.h"
#include "app/GameMgr.h"
#include "gameTienlen/logic/PlayerInfo.h"
#include "gameTienlen/logic/GameLogic.h"
#include "gameTienlen/ui/BoardScene.h"
#include "gameTala/logic/TalaPlayerInfo.h"
#include "gameTala/logic/TalaGameLogic.h"
#include "gameBinh/logic/BinhGameLogic.h"
#include "gameBinh/ui/BinhBoardScene.h"


using namespace ax::ui;

UserInfoGUI::UserInfoGUI()
{
	
}

UserInfoGUI::~UserInfoGUI()
{

}

bool UserInfoGUI::init()
{
	BaseLayer::init(UserInfoGUI::className);
	initWithBinaryFile("UserInfoGUI.csb");
	return true;
}

void UserInfoGUI::initGUI()
{
	Node* bg = getControl("bg");
	_bg = bg;

	lbNumWin = (Text*)getControl("lbNumWin", bg);
	lbLevel = (Text*)getControl("lbLevel", bg);
	lbGold = (Text*)getControl("lbGold", bg);
	borderAvatar = (ImageView*)getControl("borderAvatar", bg);
	

	Node* pListAvatar = (Node*)getControl("pListAvatar", bg);
	listBorderAvatar = TableView::create(this, pListAvatar->getContentSize());
	listBorderAvatar->setDirection(ax::extension::ScrollView::Direction::HORIZONTAL);
	//listBorderAvatar->setPosition(Vec2(pListAvatar->getContentSize().width * 0.5, pListAvatar->getContentSize().height * 0.5));
	listBorderAvatar->setDelegate(this);
	pListAvatar->addChild(listBorderAvatar);

	btnClose = customButton("btnClose", UserInfoGUI::BTN_CLOSE, bg);
}

void UserInfoGUI::onEnterFinish()
{
	
	setShowHideAnimate(_bg, true);
	setFog(true);
}

void UserInfoGUI::onButtonRelease(ax::ui::Button* button, int id)
{
	_btnId = id;
	onClose();
}

void UserInfoGUI::onCloseDone()
{
	BaseLayer::onCloseDone();
}


void UserInfoGUI::showInfo(int idGame)
{
	currentGame = idGame;
	if (currentGame == TypeGame::TIEN_LEN) {
		PlayerInfo* info = GameLogic::getInstance()->arrayPlayer[0];
		int idAvatar = info->IdAvatar();
		borderAvatar->loadTexture("avatar/level" + to_string(idAvatar) + ".png");
		listBorderAvatar->reloadData();
		lbGold->setString("Gold: " + StringUtility::pointNumber(info->Gold()));
		lbNumWin->setString("Num Win: " + StringUtility::pointNumber(info->WinCount()));
		lbLevel->setString("Level: " + to_string(info->getLevel() + 1));
	}
	else if (currentGame == TypeGame::BINH) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->arrayPlayer[0];
		int idAvatar = info->IdAvatar();
		borderAvatar->loadTexture("avatar/level" + to_string(idAvatar) + ".png");
		listBorderAvatar->reloadData();
		lbGold->setString("Gold: " + StringUtility::pointNumber(info->Gold()));
		lbNumWin->setString("Num Win: " + StringUtility::pointNumber(info->WinCount()));
		lbLevel->setString("Level: " + to_string(info->getLevel() + 1));
	}
	else {
		TalaPlayerInfo* info = TalaGameLogic::getInstance()->players[0];
		int idAvatar = info->idAvatar;
		borderAvatar->loadTexture("avatar/level" + to_string(idAvatar) + ".png");
		listBorderAvatar->reloadData();
		lbGold->setString("Gold: " + StringUtility::pointNumber(info->gold));
		lbNumWin->setString("Num Win: " + StringUtility::pointNumber(info->winCount));
		lbLevel->setString("Level: " + to_string(info->getLevel() + 1));
	}
	
}

void UserInfoGUI::tableCellTouched(TableView* table, TableViewCell* cell)
{
	AXLOGD("cell touched at index: %ld", static_cast<long>(cell->getIdx()));
	if (currentGame == TypeGame::TIEN_LEN) {
		PlayerInfo* info = GameLogic::getInstance()->arrayPlayer[0];
		int idAvatar = cell->getIdx();
		if (idAvatar > info->getLevel()) {
			ToastFloat::makeToast(ToastFloat::SHORT, "You can select this Avatar at level " + to_string(idAvatar + 1));
			return;
		}
		GameLogic::getInstance()->arrayPlayer[0]->IdAvatar(idAvatar);
		for (int i = 0; i < arraySelect.size(); i++) {
			arraySelect[i]->setVisible(false);
		}
		auto iconSelect = (Sprite*)cell->getChildByTag(11);
		iconSelect->setVisible(true);
		info->IdAvatar(idAvatar);
		borderAvatar->loadTexture(info->getAvatarLevel());
		BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->arrayPlayer[0]->updateAvatarFrame(0);
	}
	else if (currentGame == TypeGame::BINH) {
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->arrayPlayer[0];
		int idAvatar = cell->getIdx();
		if (idAvatar > info->getLevel()) {
			ToastFloat::makeToast(ToastFloat::SHORT, "You can select this Avatar at level " + to_string(idAvatar + 1));
			return;
		}
		BinhGameLogic::getInstance()->arrayPlayer[0]->IdAvatar(idAvatar);
		for (int i = 0; i < arraySelect.size(); i++) {
			arraySelect[i]->setVisible(false);
		}
		auto iconSelect = (Sprite*)cell->getChildByTag(11);
		iconSelect->setVisible(true);
		info->IdAvatar(idAvatar);
		borderAvatar->loadTexture(info->getAvatarLevel());
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->arrayPlayer[0]->updateAvatarFrame();
	}
	else {
		TalaPlayerInfo* info = TalaGameLogic::getInstance()->players[0];
		int idAvatar = cell->getIdx();
		if (idAvatar > info->getLevel()) {
			ToastFloat::makeToast(ToastFloat::SHORT, "You can select this Avatar at level " + to_string(idAvatar + 1));
			return;
		}
		TalaGameLogic::getInstance()->players[0]->setAvatar(idAvatar);
		for (int i = 0; i < arraySelect.size(); i++) {
			arraySelect[i]->setVisible(false);
		}
		auto iconSelect = (Sprite*)cell->getChildByTag(11);
		iconSelect->setVisible(true);
		info->setAvatar(idAvatar);
		borderAvatar->loadTexture(info->getAvatarLevel());
		TalaScene *gui = (TalaScene *)SceneMgr::getInstance()->getMainLayer();
		gui->players[0]->updateLevel();
	}
}

Size UserInfoGUI::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(115, 115);
}

TableViewCell* UserInfoGUI::tableCellAtIndex(TableView *table, ssize_t idx)
{
	//auto string = StringUtils::format("%ld", static_cast<long>(idx));
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();
		auto sprite = Sprite::create("avatar/level0.png");
		//sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(55.5, 55.5));
		cell->addChild(sprite);
		sprite->setTag(10);

		auto iconSelect = Sprite::create("Game/iconSelect.png");
		cell->addChild(iconSelect);
		arraySelect.push_back(iconSelect);
		iconSelect->setPosition(55.5, 55.5);
		iconSelect->setTag(11);
	}

	int level;
	int idAvatar;
	if (currentGame == TypeGame::TIEN_LEN) {
		level = GameLogic::getInstance()->arrayPlayer[0]->getLevel();
		idAvatar = GameLogic::getInstance()->arrayPlayer[0]->IdAvatar();
	}
	else if (currentGame == TypeGame::BINH) {
		level = BinhGameLogic::getInstance()->arrayPlayer[0]->getLevel();
		idAvatar = BinhGameLogic::getInstance()->arrayPlayer[0]->IdAvatar();
	}
	else {
		level = TalaGameLogic::getInstance()->players[0]->getLevel();
		idAvatar = TalaGameLogic::getInstance()->players[0]->idAvatar;
	}

	auto border = (Sprite*)cell->getChildByTag(10);
	auto iconSelect = (Sprite*)cell->getChildByTag(11);
	border->setTexture("avatar/level" + to_string(idx) + ".png");
	if (idx <= level) {
		border->setColor(Color3B(255, 255, 255));
	}
	else {
		border->setColor(Color3B(100, 100, 100));
	}
	iconSelect->setVisible(idAvatar == idx);
	
	return cell;
}

ssize_t UserInfoGUI::numberOfCellsInTableView(TableView *table)
{
	return 20;
}

std::string UserInfoGUI::className = "UserInfoGUI";

const int UserInfoGUI::BTN_CLOSE = 0;


const int UserInfoGUI::ZODER = 10000;

const int UserInfoGUI::TAG = 10000;

const int UserInfoGUI::SUPPORT = 800;

