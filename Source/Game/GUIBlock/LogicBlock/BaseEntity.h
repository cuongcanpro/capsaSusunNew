#pragma once
#ifndef BaseEntity_h__
#define BaseEntity_h__
#include <vector>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/BaseGUI.h"
#include "ConfigData.h"
#include "../../Logic/PointGame.h"
using namespace std;
class BaseEntity : public Node
{
public:
	BaseEntity(void);
	~BaseEntity(void);
	void initCell();
	int state;
	int idBlock;
	vector <PointGame*> data;
	vector <GameImage*> arrayImage;
	void saveRoot();
	virtual void changeMap();
	PointGame getPointInMap();
	bool validInMap();
	void changeNextMap();
	void changeCurrentMap();
	bool canPut();
	bool validPointInMap(PointGame p);
	virtual int getWidth();
	virtual int getHeight();
	float getRealWidth();
	float getRealHeight();
	bool isTouch(Point point);
	bool isNext;
	void setIsNext(bool _isNext);
	void endGame();
	int getNumCell();
	Point arrangePoint;
	Size arrangeSize;
	int idArray;

	float rootX, rootY;
};
#endif // BaseEntity_h__

