#include "BonusEffect.h"
#include "math.h"
#include "Game/Utility/GameUtility.h"

BonusEffect::BonusEffect(void)
{
	setIdBonus(0);
	countTime = 0;
}


BonusEffect::~BonusEffect(void)
{
}

void BonusEffect::act( float delta )
{
	countTime = countTime + delta;

	double angle = countTime / maxTime * 2 * 3.14f;

	float posX = (float)(cos(angle) * radius + rootX);
	float posY = (float)(sin(angle) * radius + rootY);
	setPosition(posX, posY);

	countTimeBonus = countTimeBonus + delta;
	if(countTimeBonus > maxTimeBonus)
	{
		setVisible(false);
	}
	else if(maxTimeBonus - countTimeBonus < 5)
	{
		countTimeAppear = countTimeAppear + delta;
		if(countTimeAppear > 0.1f)
		{
			countTimeAppear = 0;
			getImg()->setOpacity(255 - getImg()->getOpacity());
		}
	}
}

void BonusEffect::setIdBonus( int _id )
{
	idBonus = _id;
	setImage(("Egg/x_" + GameUtility::toString(_id + 2) + ".png").c_str());
	setVisible(true);
	countTime = 0;
	countTimeAppear = 0;
	countTimeBonus = 0;
	setOpacity(255);

	if(_id < 4)
	{
		maxTimeBonus = 17;
	}
	else
	{
		maxTimeBonus = 5;
	}
}

int BonusEffect::getMul()
{
	if(!isVisible())
		return 1;
	switch (idBonus) {
	case 0:
		return 2;
	case 1:
		return 3;
	case 2:
		return 4;
	case 3:
		return 5;
	default:
		return 1;
	}
}
void BonusEffect::setImage( const char* url )
{
	GameImage::setImage(url);
	getImg()->setAnchorPoint(Vec2(0, 0));
}
