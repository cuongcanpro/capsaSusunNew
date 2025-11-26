#ifndef _MoneyGroup_h__
#define _MoneyGroup_h__
#include "axmol.h"

using namespace ax;
class MoneyGroup : public Node
{
public:

	MoneyGroup(void);
	MoneyGroup(long money);
	~MoneyGroup(void);
	void setMoney(double money);
};
#endif
