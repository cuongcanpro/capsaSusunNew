#ifndef NewLevelGUI_h__
#define NewLevelGUI_h__

#include "core/gui/BaseLayer.h"

#include "extensions/cocos-ext.h"

using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class NewLevelGUI:
public BaseLayer {
public:
	CREATE_FUNC(NewLevelGUI);
	NewLevelGUI();
	~NewLevelGUI();
public:
	bool init();
	void initGUI();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	void onCloseDone();
	void showInfo(int idGame);
	int currentGame;
public:
	int _btnId;
	Text* lbCongrat;
	ImageView* borderAvatar;
	Button* btnClose;
public:
	static std::string className;

	static const int BTN_CLOSE;

	static const int ZODER;
	static const int TAG;

	static const int SUPPORT;
};
#endif // NewLevelGUI_h__
