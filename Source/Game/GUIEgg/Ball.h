#pragma once
#ifndef Ball_h__
#define Ball_h__
#include "Engine/GUI/GameImage.h"


class Ball : public GameImage
{
public:
	Ball(void);
	~Ball(void);

	int typeRow;
	int idRow, idColumn, idBall;

	float rootX, rootY;

	bool isCheckConnect;
	bool isVibrate;
	int countVibrate;

	Ball(int _idBall, int _idRow, int _idColumn, int _typeRow);
	void removeBall(); 
	bool isConnect();
	void copy(Ball* ball);
	void renew(int _typeRow);
	void checkRemoveNearBall(int idRow, int idColumn);
	bool checkIsConnectNearBall(int idRow, int idColumn);
	void newRow(int typeRow2);
	bool checkEatBall();
	int countNearBall();
	int getCountNearBall(int idRow, int idColumn);
	void runActionVibrate();
	void setId(int i);
	void setImage(const char* url);
	GameImage* bonusImage;
	int idBonus;
	void setIdBonus(int id);
	bool isBonus();
	void moveUp(int countUp);
	void setIdRow(int idRow);
	float rScaleX, rScaleY;
	
};
#endif // Ball_h__

