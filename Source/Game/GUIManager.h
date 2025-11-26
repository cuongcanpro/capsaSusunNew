#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H
#include "GUIs/GUILoading.h"
#include "GUIs/GUIDialog.h"
#include "GUIs/GUIResult.h"
#include "GUILine/GUILine.h"
#include "GUIs/GUIChoose.h"
#include "GUIEgg/GUIGame.h"
#include "GUIMerge/GUIMerge.h"
#include "GUITwenty/GUITwenty.h"
#include "GUIBomb/GUIBomb.h"
#include "GUIBomb/GUIMenuBomb.h"
#include "GUIBubble/GUIBubble.h"
#include "GUIPop/GUIPop.h"
#include "GUIPika/GUIPika.h"
#include "GUIBlock/GUIBlock.h"
#include "GUIs/GUIMinigames.h"
#include "GUIBrick/GUIBrick.h"
#include "GUISudoku/GUISudoku.h"
#include "GUISudoku/GUIMenuSudoku.h"
#include "GUI2048/GUI2048.h"
#include "GUIaa/GUIaa.h"
#include "GUISwing/GUISwing.h"
#include "GUIs/GUILoadingGame.h"

using namespace std;
class GUIManager 
{
public:
	GUIManager(void);
	~GUIManager(void);
	void update();
	static GUIManager& getInstance();

	//guis
	GUILoading* guiLoading;
    GUIDialog* guiDialog;
    GUIResult* guiResult;
    GUILine* guiLine;
    GUIChoose* guiChoose;
    GUIGame* guiGame;
    GUIMerge* guiMerge;
    GUITwenty* guiTwenty;
    GUIBomb* guiBomb;
    GUIMenuBomb* guiMenuBomb;
    GUIBubble* guiBubble;
    GUIPop* guiPop;
    GUIPika* guiPika;
    GUIBlock* guiBlock;
    GUIMinigames* guiMinigames;
    GUIBrick* guiBrick;
    GUISudoku* guiSudoku;
    GUIMenuSudoku* guiMenuSudoku;
    GUI2048* gui2048;
    GUIaa* guiAa;
    GUISwing* guiSwing;
    GUILoadingGame* guiLoadingGame;
	
	bool isCallBackPress;
	std::vector <BaseGUI*> *GUIList;
	void addToListGui(BaseGUI* gui);
	void removeFromListGui();
	void showGui(BaseGUI* gui, Node *parent = NULL, bool fog = true);
    BaseGUI* showGuiWithName(std::string className, Node* parent = NULL, bool fog = true);
	void removeAllGui();
	BaseGUI* getLastGui();
	void setVisibleWaiting(bool visible);
    static BaseGUI* createGUI(std::string className);
};
#endif
