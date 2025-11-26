#ifndef LoadingGui_h__
#define LoadingGui_h__

#include "axmol.h"
#include "extensions/cocos-ext.h"
#include "extensions/axmol-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ax;
class LoadingGui:
	public ax::Layer{
public:
	LoadingGui();
	~LoadingGui();
	static LoadingGui* create(std::string text = "", bool fog = true);
	bool init(std::string text = "", bool fog = true);
public:
	void timeout(float time);
	void onEnter();
	void remove();
public:
	ax::LayerColor* _layerColor;
	ax::ui::Text* _label;
	std::string _message;
	bool _fog;
	ax::Sprite* commonbg;
	ax::Sprite* commoncircel;

};
#endif // LoadingGui_h__
