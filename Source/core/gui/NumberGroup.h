#ifndef _NumberGroup_h__
#define _NumberGroup_h__
#include "axmol.h"

using namespace ax;
class NumberGroup : public Node
{
public:

	NumberGroup(void);
	NumberGroup(long money);
	~NumberGroup(void);
	void setMoney(double money);
};
#endif
