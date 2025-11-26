#include "ParticleEffect.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"

ParticleEffect::ParticleEffect(void)
{
}


ParticleEffect::~ParticleEffect(void)
{
}

void ParticleEffect::create(std::string particlePath, Node* parent)
{

	particle = new ParticleSystemQuad();
	//xuannd: from now ,use 1 particle for all resolution
	//std::string filename = ScreenUtils::fileFull(particlePath.c_str());
	particle->initWithFile(particlePath.c_str());

	Layer* layer;
	layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);

	if (parent != NULL)
		parent->addChild(particle);
	else
		layer->addChild(particle);

	// TODO: CHANGE this magic number
	particle->setTag(42);
	particle->setPosition(0, 0);
	particle->setAutoRemoveOnFinish(true);
	particle->setBlendAdditive(true);
	//particle->setPositionType(kCCPositionTypeFree);
}

