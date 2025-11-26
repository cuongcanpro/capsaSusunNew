#ifndef _PopNumberGroup_h__
#define _PopNumberGroup_h__
#include "axmol.h"

using namespace ax;
class PopNumberGroup : public Node
{
public:

	PopNumberGroup(void);
	PopNumberGroup(long money);
	~PopNumberGroup(void);
	void setMoney(double money);
};
#endif
