#pragma once
#include "axmol.h"
#include <vector>

using namespace ax;
using namespace std;
class StarFly : public Node {
public:
	StarFly(float width, float height);
	vector<Sprite*> arrayStar;
	float width, height;
	float countGen;
	float lifeTime;
	void startEffect();
	void effectStar(Sprite* sprite);
	void updateEffect(float dt);
	Sprite* getStar();
};

