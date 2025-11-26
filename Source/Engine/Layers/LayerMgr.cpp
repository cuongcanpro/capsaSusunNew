#include "LayerMgr.h"
#include "GameLayer.h"
#include "../GlobalVar.h"

LayerMgr::LayerMgr(void)
{
	layerList = new std::vector<GameLayer*>();
}


LayerMgr::~LayerMgr(void)
{
	layerList->clear();
	layerList=NULL;
}

void LayerMgr::addLayers(ax::Scene* scene)
{
	int i=0;
	GameLayer* layer;
	for ( i = 0; i < MAX_LAYER; i++)
	{
		layer = new GameLayer(i);
		layer->autorelease();
		scene->addChild(layer, i);
		layerList->push_back(layer);
	}

}

GameLayer* LayerMgr::getLayerByIndex(int index)
{
	if(index<0||index>MAX_LAYER)
	{
		return NULL;
	}
	return layerList->at(index);
}

