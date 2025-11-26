#include "axmol.h"

#ifndef CardImage_h__
#define CardImage_h__

using namespace std;
using namespace ax;
class CardImage : public Sprite
{
public:
	CardImage(void);
	CardImage( int id );
	~CardImage(void);
	
	void setIdCard(int id);
	string getResource();
	void setDark(bool isDark);
	float getRealWidth();
	float getRealHeight();
private:
	int id;
};
#endif // CardImage_h__

