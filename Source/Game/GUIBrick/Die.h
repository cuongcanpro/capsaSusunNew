#pragma once
#ifndef Die_h__
#define Die_h__

class Die
{
public:
	Die(void);
	~Die(void);

	float frame ;
	float countTime;

	bool visible;

	int x, y;
	int state;

	void update();
	void changeMap();
	void setPos(int x, int y);
};
#endif // Die_h__

