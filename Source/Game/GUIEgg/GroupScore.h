#ifndef _GroupScore_h__
#define _GroupScore_h__
#include "axmol.h"

using namespace ax;
class GroupScore : public Node
{
public:

	GroupScore(void);
	~GroupScore(void);
	void createNormalScore(int numBall, int numDrop, int mul);
	void createBonusScore(int bonus);
	void createNormalBonusScore(int numBall, int numDrop, int mul, int bonus);
	static int getNormalBonusScore(int numBall, int numDrop, int mul, int bonus);
	
};
#endif
