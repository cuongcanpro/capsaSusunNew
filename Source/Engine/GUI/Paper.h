#pragma once
#include "axmol.h"
#include <vector>

using namespace std;
using namespace ax;
class Paper : public Node {
public:
	Paper(float width, float height, int directionX = 1, int directionY = 1);
	vector<Sprite*> arrayStar;
	float width, height;
	int directionX, directionY;
	float countGen;
	float lifeTime;
	void startEffect();
	void effectStar(Sprite* sprite);
	void updateEffect(float dt);
	Sprite* getStar();
	void callbackEffectStar(Node* sender);
};

