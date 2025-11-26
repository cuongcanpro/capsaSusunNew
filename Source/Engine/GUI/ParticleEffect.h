#ifndef ParticleEffect_h__
#define ParticleEffect_h__

#include "axmol.h"

#include <string>
using namespace ax;

class ParticleEffect
{
public:
	ParticleEffect(void);
	~ParticleEffect(void);

	void create(std::string particlePath, Node* parent = NULL);

public:
	ParticleSystem* particle;
};
#endif // ParticleEffect_h__

