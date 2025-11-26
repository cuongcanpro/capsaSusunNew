#ifndef BaseScene_h__
#define BaseScene_h__

#include "axmol.h"

class BaseScene:
	public ax::Scene
{
public:
	BaseScene();
	~BaseScene();
	static BaseScene* createWithLayer(ax::Node* layer);
	static BaseScene* makeScene(ax::Node* layer);
	bool init();
	void onEnter();
public:
	void addChild(ax::Node* child, int tag = 101, int order = 101);
	ax::Node* getMainLayer();
	ax::Node* getLayerGUI();
	void update(float dt);
public:
	static const int TAG_LAYER;
	static const int TAG_GUI;
};

#endif // BaseScene_h__
