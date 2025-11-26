#ifndef _GUI_MGR_H_
#define _GUI_MGR_H_
#include "axmol.h"
#include "BaseGUI.h"

using namespace ax;

class GUIMgr
{
private:
	LayerColor* fog;
	void creatFog();
	std::map<int, BaseGUI*> GUIList;

public:
	GUIMgr(void);
	~GUIMgr(void);
public:
	void showFog();
	void hideFog();

public:
	void onUpdate(float delta);
	//static CCRenderTexture* creatStroke(CCSprite* sprite,int size,ccColor4B color, GLubyte opacity);
	void hideAll();
	void clean();

public:
	void addGUI(int guiID, BaseGUI* gui);
	void addGUI(int guiID, BaseGUI* gui, int LayerID);
	BaseGUI* getGUI(int guiID);
};
#endif
