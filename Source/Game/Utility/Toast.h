#pragma once
#include "axmol.h"
#include "extensions/axmol-ext.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "ui/CocosGUI.h"
using namespace ax;
class Toast : public Node
{
public:
	Toast(void);
	~Toast(void);
	CREATE_FUNC(Toast);
	virtual bool init();
	static Toast *create(const char* _lb);
	static void makeToast(float duration,const char* msg);
	static void clearToast();
	void setMsg(const char* msg);
protected:
	ui::Scale9Sprite *_9patch;
	ui::Text *_label;
	void callbackFree(Node *sender);
};

