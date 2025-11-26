#ifndef GUILevel_h__
#define GUILevel_h__
#include "core/gui/BaseLayer.h"
using namespace ax::extension;
class GUILevel :
	public BaseLayer, public TableViewDataSource, public TableViewDelegate
{
public:
	CREATE_FUNC(GUILevel);
	GUILevel();
	~GUILevel();
	bool init();
public:
	void initGUI();
	void onEnterFinish();
	void backKeyPress();
	Button* arrayBtn[118];
	TableView* listTop;
public:
	static const std::string className;

	virtual void scrollViewDidScroll(ax::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(ax::extension::ScrollView* view) {};
	virtual void tableCellTouched(ax::extension::TableView* table, ax::extension::TableViewCell* cell) override;
	virtual ax::Size tableCellSizeForIndex(ax::extension::TableView *table, ssize_t idx) override;
	virtual ax::extension::TableViewCell* tableCellAtIndex(ax::extension::TableView *table, ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(ax::extension::TableView *table) override;
};

#endif
