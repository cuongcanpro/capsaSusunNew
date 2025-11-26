#ifndef _GLOBAL_VAR_H_
#define _GLOBAL_VAR_H_

#include "../Game/GameClient.h"
#include "axmol.h"
#include "Layers/LayerMgr.h"
#include "Utility/Utility.h"
#include "GUI/GUIMgr.h"

// The only one scence
extern ax::Scene* mainScene; 

// The general game
extern GameClient* game;

// General managers
extern LayerMgr*			layerMgr;
extern Utility*				utility;
extern GUIMgr*				guiMgr;

#define LAYER_BG_GAME		0
#define LAYER_GAME			1
#define LAYER_GUI			2
#define LAYER_EFFECT_GAME	3
#define LAYER_POPUP			4
#define LAYER_CURSOR		5
#define LAYER_LOADING		6

#define kShaderGrayProgram	"kShaderGrayProgram"
#define kShaderNormal		"kShaderNormal"
#define kShaderLighter		"kShaderLighter" 

#define MAX_LAYER 7

#define DEFAULT_SCREEN_WIDTH  800
#define DEFAULT_SCREEN_HEIGHT 480
#endif

