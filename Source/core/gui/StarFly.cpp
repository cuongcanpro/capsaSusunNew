#include "StarFly.h"

StarFly::StarFly(float width, float height): Node()
{
	this->width = width;
	this->height = height;
	countGen = 0.2;
}

void StarFly::startEffect()
{
	setVisible(true);
    schedule(AX_SCHEDULE_SELECTOR(StarFly::updateEffect), 0.02);
	for (int i = 0; i < 10; i++) {
		Sprite* sprite = getStar();
		effectStar(sprite);
	}
	countGen = 0.1;
	lifeTime = 100;
}

void StarFly::effectStar(Sprite* sprite)
{
	//sprite->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ONE });
	
	sprite->setPosition(width * AXRANDOM_0_1(), height * (AXRANDOM_0_1() * 0.2));
	float randomTime = AXRANDOM_0_1() * 2 + 4;
	float rAction1 = AXRANDOM_0_1();
	float rAction2 = AXRANDOM_0_1();
	float rScale = AXRANDOM_0_1() * 0.6 + 0.6;
	float rOpacity = AXRANDOM_0_1() * 100 + 155;

	float rTimeOpacity = AXRANDOM_0_1();
	float rTimeBlink = AXRANDOM_0_1() + 0.1;
	Vec2 pos = sprite->getPosition();
	sprite->setScale(rScale);
	//sprite->setOpacity(rOpacity);
	sprite->setOpacity(255);
	sprite->setPosition(pos);
	Vec2 p1 = pos;
	Vec2 p2 = Vec2(AXRANDOM_0_1() * width, (AXRANDOM_0_1() * 0.2 + 0.8) * height);
	Vec2 p3 = Vec2(p1.x / 2 + p2.x / 2 + (AXRANDOM_0_1() - 0.5) * width, p1.y / 2 + p2.y / 2 + (AXRANDOM_0_1() - 0.5) * height);
	Vec2 p4 = Vec2(p1.x / 2 + p2.x / 2 + (AXRANDOM_0_1() - 0.5) * width, p1.y / 2 + p2.y / 2 + (AXRANDOM_0_1() - 0.5) * height);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = p2;
	bezier.controlPoint_2 = p3;
	bezier.endPosition = p4;
	sprite->runAction(
		Sequence::create(
			Spawn::create(
				BezierTo::create(randomTime, bezier),
				Sequence::create(
					FadeOut::create(randomTime),
					NULL
				),
				NULL
			),
			Hide::create(),
			NULL
		)
	);
	sprite->runAction(
		RepeatForever::create(
			Sequence::create(
				Spawn::create(
					Sequence::create(
						FadeIn::create(rTimeBlink),
						FadeOut::create(rTimeBlink),
						NULL
					),
					NULL
				),
				NULL
			)
		)
	);
}

void StarFly::updateEffect(float dt) {
	if (lifeTime > 0) {
		countGen = countGen - dt;
		if (countGen <= 0) {
			for (int i = 0; i < 3; i++) {
				Sprite* sprite = getStar();
				effectStar(sprite);
			}
			
			countGen = 0.2;
		}
		lifeTime = lifeTime - dt;
		if (lifeTime <= 0) {
			runAction(
				Sequence::create(
					DelayTime::create(2.0),
					Hide::create(),
					NULL
				)
			);
		};
	}
}

ax::Sprite* StarFly::getStar()
{
	Sprite* image = NULL;
	for (int i = 0; i < arrayStar.size(); i++) {
		if (!arrayStar.at(i)->isVisible()) {
			image = arrayStar.at(i);
			break;
		}
	}
	if (image == NULL) {
		image = Sprite::create("Board/Particles/lights.png");
		this->addChild(image);
		arrayStar.push_back(image);
	}
	image->setVisible(true);
	return image;
}
