#include "GUIManager.h"
using namespace ax;

GUIManager::GUIManager(void)
{
	GUIList = new std::vector<BaseGUI *>();
	isCallBackPress = false;
    guiLoading      = NULL;
    guiDialog       = new GUIDialog();
    guiResult       = new GUIResult();
    guiLoadingGame           = new GUILoadingGame();
    
    guiLine         = NULL;
    guiGame             = NULL;
    guiMerge        = NULL;
    guiTwenty           = NULL;
    guiBomb         = NULL;
    guiMenuBomb         = NULL;
    guiBubble       = NULL;
    guiPop              = NULL;
    guiPika         = NULL;
    guiBlock            = NULL;
    guiMinigames    = NULL;
    guiBrick            = NULL;
    guiSudoku       = NULL;
    guiMenuSudoku       = NULL;
    gui2048         = NULL;
    guiAa               = NULL;
    guiSwing        = NULL;
}

GUIManager::~GUIManager(void)
{}

GUIManager& GUIManager::getInstance()
{
	static GUIManager instance;
	
	return instance;
}

void GUIManager::update()
{
	
}

void GUIManager::addToListGui(BaseGUI *gui)
{
	GUIList->push_back(gui);
	if(gui->isInitted())
		gui->enableGUI();
	int size = GUIList->size() - 1;
	for(int i = 0; i< size; i++)
	{

		GUIList->at(i)->disableGUI();
	}

}


void GUIManager::removeFromListGui()
{
	if(GUIList->size() == 0)
		return;
	
	BaseGUI *gui = GUIList->at(GUIList->size() - 1);
	gui->hideGUI();
	GUIList->pop_back();
	
	if(GUIList->size() == 0)
		return;

	GUIList->at(GUIList->size() - 1)->enableGUI();
}

void GUIManager::showGui( BaseGUI *gui, Node *parent /*= NULL*/, bool fog /*= true*/ )
{
	addToListGui(gui);
	gui->showGUI(parent, fog);
}

BaseGUI* GUIManager::showGuiWithName(std::string className, Node* parent, bool fog)
{
    BaseGUI* gui = GUIManager::createGUI(className);
    showGui(gui, parent, fog);
    return gui;
}

void GUIManager::removeAllGui()
	{
		while (GUIList->size() > 0)
		{
			GUIList->at(GUIList->size() - 1)->hideGUI();
			GUIList->pop_back();

		}
	}

BaseGUI* GUIManager::getLastGui()
{
	return GUIList->at(GUIList->size() - 1);
}


void GUIManager::setVisibleWaiting( bool visible )
{
	
	
}

BaseGUI* GUIManager::createGUI(std::string className)
{
    if (className.compare(GUIDialog::className) == 0)
    {
        if (GUIManager::getInstance().guiDialog == NULL)
        {
            GUIManager::getInstance().guiDialog = new GUIDialog();
        }
        return GUIManager::getInstance().guiDialog;
    }
    if (className.compare(GUI2048::className) == 0)
    {
        if (GUIManager::getInstance().gui2048 == NULL)
        {
            GUIManager::getInstance().gui2048 = new GUI2048();
        }
        return GUIManager::getInstance().gui2048;
    }
    if (className.compare(GUIaa::className) == 0)
    {
        if (GUIManager::getInstance().guiAa == NULL)
        {
            GUIManager::getInstance().guiAa = new GUIaa();
        }
        return GUIManager::getInstance().guiAa;
    }

    if (className.compare(GUIBlock::className) == 0)
    {
        if (GUIManager::getInstance().guiBlock == NULL)
        {
            GUIManager::getInstance().guiBlock = new GUIBlock();
        }
        return GUIManager::getInstance().guiBlock;
    }
    if (className.compare(GUIBomb::className) == 0)
    {
        if (GUIManager::getInstance().guiBomb == NULL)
        {
            GUIManager::getInstance().guiBomb = new GUIBomb();
        }
        return GUIManager::getInstance().guiBomb;
    }
    if (className.compare(GUIMenuBomb::className) == 0)
    {
        if (GUIManager::getInstance().guiMenuBomb == NULL)
        {
            GUIManager::getInstance().guiMenuBomb = new GUIMenuBomb();
        }
        return GUIManager::getInstance().guiMenuBomb;
    }
    if (className.compare(GUIBrick::className) == 0)
    {
        if (GUIManager::getInstance().guiBrick == NULL)
        {
            GUIManager::getInstance().guiBrick = new GUIBrick();
        }
        return GUIManager::getInstance().guiBrick;
    }
    if (className.compare(GUIBubble::className) == 0)
    {
        if (GUIManager::getInstance().guiBubble == NULL)
        {
            GUIManager::getInstance().guiBubble = new GUIBubble();
        }
        return GUIManager::getInstance().guiBubble;
    }
    if (className.compare(GUIGame::className) == 0)
    {
        if (GUIManager::getInstance().guiGame == NULL)
        {
            GUIManager::getInstance().guiGame = new GUIGame();
        }
        return GUIManager::getInstance().guiGame;
    }
    if (className.compare(GUILine::className) == 0)
    {
        if (GUIManager::getInstance().guiLine == NULL)
        {
            GUIManager::getInstance().guiLine = new GUILine();
        }
        return GUIManager::getInstance().guiLine;
    }
    if (className.compare(GUIMerge::className) == 0)
    {
        if (GUIManager::getInstance().guiMerge == NULL)
        {
            GUIManager::getInstance().guiMerge = new GUIMerge();
        }
        return GUIManager::getInstance().guiMerge;
    }
    if (className.compare(GUIPika::className) == 0)
    {
        if (GUIManager::getInstance().guiPika == NULL)
        {
            GUIManager::getInstance().guiPika = new GUIPika();
        }
        return GUIManager::getInstance().guiPika;
    }
    if (className.compare(GUIPop::className) == 0)
    {
        if (GUIManager::getInstance().guiPop == NULL)
        {
            GUIManager::getInstance().guiPop = new GUIPop();
        }
        return GUIManager::getInstance().guiPop;
    }
    if (className.compare(GUILoading::className) == 0)
    {
        if (GUIManager::getInstance().guiLoading == NULL)
        {
            GUIManager::getInstance().guiLoading = new GUILoading();
        }
        return GUIManager::getInstance().guiLoading;
    }
    if (className.compare(GUIMinigames::className) == 0)
    {
        if (GUIManager::getInstance().guiMinigames == NULL)
        {
            GUIManager::getInstance().guiMinigames = new GUIMinigames();
        }
        return GUIManager::getInstance().guiMinigames;
    }
    if (className.compare(GUIResult::className) == 0)
    {
        if (GUIManager::getInstance().guiResult == NULL)
        {
            GUIManager::getInstance().guiResult = new GUIResult();
        }
        return GUIManager::getInstance().guiResult;
    }
    if (className.compare(GUIMenuSudoku::className) == 0)
    {
        if (GUIManager::getInstance().guiMenuSudoku == NULL)
        {
            GUIManager::getInstance().guiMenuSudoku = new GUIMenuSudoku();
        }
        return GUIManager::getInstance().guiMenuSudoku;
    }
    if (className.compare(GUISudoku::className) == 0)
    {
        if (GUIManager::getInstance().guiSudoku == NULL)
        {
            GUIManager::getInstance().guiSudoku = new GUISudoku();
        }
        return GUIManager::getInstance().guiSudoku;
    }
    if (className.compare(GUISwing::className) == 0)
    {
        if (GUIManager::getInstance().guiSwing == NULL)
        {
            GUIManager::getInstance().guiSwing = new GUISwing();
        }
        return GUIManager::getInstance().guiSwing;
    }
    if (className.compare(GUITwenty::className) == 0)
    {
        if (GUIManager::getInstance().guiTwenty == NULL)
        {
            GUIManager::getInstance().guiTwenty = new GUITwenty();
        }
        return GUIManager::getInstance().guiTwenty;
    }
    if (className.compare(GUILoadingGame::className) == 0)
    {
        if (GUIManager::getInstance().guiLoadingGame == NULL)
        {
            GUIManager::getInstance().guiLoadingGame = new GUILoadingGame();
        }
        return GUIManager::getInstance().guiLoadingGame;
    }

}
