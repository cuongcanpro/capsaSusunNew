#include "Engine.h"
#include "GlobalVar.h"

Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}

void Engine::init()
{
	// Init layers
	layerMgr = new LayerMgr();
	layerMgr->addLayers(mainScene);

	Layer* layer;
	layer = layerMgr->getLayerByIndex(LAYER_GUI);

	// Init Input

	// Init configurations
	//config = new Config();
	//config->readAllConfig();

	// Init Animations
	//animationMgr = new FlashAnimationMgr();
	//animationMgr->loadData();

	// Init Utility
	//utility = new Utility();

	// Init Effects
	//effectMgr = new EffectMgr();

	// Init GUIs
	guiMgr = new GUIMgr();
}
