#ifndef _LAYER_MGR_H_
#define _LAYER_MGR_H_
#include "GameLayer.h"

class LayerMgr
{
private:
	std::vector<GameLayer*>* layerList;
public:
	LayerMgr(void);
	~LayerMgr(void);
	void addLayers(Scene*);
	GameLayer* getLayerByIndex(int);
};

#endif 
