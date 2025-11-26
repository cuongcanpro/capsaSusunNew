#ifndef Waiting_h__
#define Waiting_h__

#include "axmol.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
using namespace ax;

class Waiting:
	public ax::Layer {
public:
	CREATE_FUNC(Waiting);
	Waiting();
	~Waiting();
	bool init();
public:
	void timeout(float time);
	void onEnter();
	void remove();
public:
	ax::LayerColor* _layerColor;
	std::string _message;
	bool _fog;
	ax::Sprite* _sprite;
};
#endif // Waiting_h__
