#ifndef _CSCALE_SPRITE_H_
#define _CSCALE_SPRITE_H_
#include "axmol.h"

USING_NS_AX;

class CScaleSprite:
public Sprite{
public:
	///static CScaleSprite* create();
	static CScaleSprite* create(const char *pszFileName, bool frame = false);
	float getWidth();
	float getHeight();
	virtual void setScale(float scale);
	virtual void setScaleX(float scale);
	virtual void setScaleY(float scale);
	virtual float getScaleX();
	virtual float getScaleY();
	virtual float getScale();
private:
	Size newSize;
	void updateSize();
};
#endif
