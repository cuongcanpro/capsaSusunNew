#ifndef UserInfoGUI_h__
#define UserInfoGUI_h__

#include "core/gui/BaseLayer.h"

#include "extensions/cocos-ext.h"

using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class UserInfoGUI:
public BaseLayer, public ax::extension::TableViewDataSource, public ax::extension::TableViewDelegate {
public:
	CREATE_FUNC(UserInfoGUI);
	UserInfoGUI();
	~UserInfoGUI();
public:
	bool init();
	void initGUI();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	void onCloseDone();
public:
	int _btnId;
	Text* lbNumWin;
	Text* lbLevel;
	Text* lbGold;
	ImageView* borderAvatar;
	TableView* listBorderAvatar;
	Button* btnClose;
	vector<Sprite*> arraySelect;
	int currentGame;
	void showInfo(int idGame);
	virtual void tableCellTouched(ax::extension::TableView* table, ax::extension::TableViewCell* cell)override;
	virtual ax::Size tableCellSizeForIndex(ax::extension::TableView *table, ssize_t idx)override;
	virtual ax::extension::TableViewCell* tableCellAtIndex(ax::extension::TableView *table, ssize_t idx)override;
	virtual ssize_t numberOfCellsInTableView(ax::extension::TableView *table)override;
public:
	static std::string className;

	static const int BTN_CLOSE;

	static const int ZODER;
	static const int TAG;

	static const int SUPPORT;
};
#endif // UserInfoGUI_h__
