#pragma once
#include "axmol.h"
#include <vector>

using namespace ax;
using namespace std;
enum SparkleType {
    SPARKLE_BLOOM,
    SPARKLE_RIGHT
};
class Sparkle : public Node {
public:
	Sparkle(float width, float height);
	vector<Sprite*> arrayStar;
	float width, height;
	float countGen;
    float emitTime;
	float lifeTime;
    SparkleType type;
	void startEffect(float _lifeTime = 100);
	void effectStarBloom(Sprite* sprite);
    void effectStarRight(Sprite* sprite);
	void updateEffect(float dt);
	Sprite* getStar();
};

