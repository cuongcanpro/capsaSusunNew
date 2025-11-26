#ifndef _ScoreGroup_h__
#define _ScoreGroup_h__
#include "axmol.h"

using namespace ax;
class ScoreGroup : public Node
{
public:
	int max;
	ScoreGroup(void);
	ScoreGroup(long money, int max = 8);
	~ScoreGroup(void);
	void setMoney(double money);
};
#endif
