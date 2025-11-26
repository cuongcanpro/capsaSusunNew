#ifndef GUI_DIALOG_H
#define GUI_DIALOG_H

#include "../../Engine/GUI/BaseGUI.h"

using namespace ax::ui;
class GUIDialog : public BaseGUI
{
private:
	Label* labelMessage;
	void (*okFunction)();
	void (*cancelFunction)();
	BaseButton* btnOk;
	BaseButton* btnCancel;
	Node* groupAll;

	
public:
	void initGUI();
	void onButtonRelease(int buttonId, Touch* event);
	void showGUI(const char* message, void (*okFunction)() = NULL, bool onlyOk = false, void (*cancelFunction)() = NULL, const char* sourceOk = NULL, const char* sourceCancel = NULL);
	void onHideGUI();

    public:
        static std::string className;
};
#endif
