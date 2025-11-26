#ifndef Dialog_h__
#define Dialog_h__

#include "BaseLayer.h"

typedef std::function<void(int btnId)> DialogListener;

class Dialog:
public BaseLayer{
public:
	CREATE_FUNC(Dialog);
	Dialog();
	~Dialog();
public:
	bool init();
	void initGUI();
	void onEnterFinish();
	void resetButton();
	void onButtonRelease(ax::ui::Button* button, int id);
	void onCloseDone();
	void setOkCancel(std::string message, const DialogListener& listener);
	void setOkWithAction(std::string message, const DialogListener& listener);
	void setOKNotify(std::string message);
	void setChangeGold(std::string message, const DialogListener& listener);
	void setAddG(std::string message, const DialogListener& listener);
	void setMessage(std::string message);
public:
	DialogListener _callback;
	ax::ui::Button* _btnOK;
	ax::ui::Button* _btnClose;
	ax::ui::Button* _btnCancel;
	
	ax::ui::Text* _lb_message;

	ax::Vec2 _pLeft;
	ax::Vec2 _pRight;
	ax::Vec2 _pCenter;

	int _btnId;
public:
	static std::string className;

	static const int BTN_OK;
	static const int BTN_CANCEL;
	static const int BTN_QUIT;

	static const int ZODER;
	static const int TAG;

	static const int SUPPORT;
};
#endif // Dialog_h__
