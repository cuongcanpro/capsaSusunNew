#ifndef ReceiveGUI_h__
#define ReceiveGUI_h__

#include "core/gui/BaseLayer.h"
#include "spine/spine.h"
#include "extensions/cocos-ext.h"
#include <spine/spine-cocos2dx.h>
using namespace ax;
using namespace ax::ui;
using namespace ax::extension;
class ReceiveGUI:
public BaseLayer {
public:
	CREATE_FUNC(ReceiveGUI);
	ReceiveGUI();
	~ReceiveGUI();
public:
	bool init();
	void initGUI();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	void onCloseDone();
    void onCloseShowEffect();
	void showMessage(string message);
	int currentGame;
public:
	int _btnId;
	Text* lbCongrat;
	Button* btnClose;
    spine::SkeletonAnimation* effectGift;
public:
	static std::string className;

	static const int BTN_CLOSE;

	static const int ZODER;
	static const int TAG;

	static const int SUPPORT;
};
#endif // ReceiveGUI_h__
