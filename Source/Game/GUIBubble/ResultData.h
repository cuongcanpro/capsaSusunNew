#pragma once
#include "Game/Logic/PointGame.h"
#include "axmol.h"
#include <vector>
#ifndef ResultData_h__
#define ResultData_h__
using namespace std;
class ResultData
{
public:
	ResultData();
	~ResultData();

	vector<PointGame*> arrayPoint;
	int idBall;
};
#endif // ResultData_h__

