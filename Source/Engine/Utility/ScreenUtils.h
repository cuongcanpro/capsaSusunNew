#ifndef _SCREEN_UTILS__
#define _SCREEN_UTILS__

#include "axmol.h"
#include <sstream>
#include <fstream>
#include <map>
 #include <vector>  
USING_NS_AX;
struct ScreenProperty
{
	float width;
	float height;
	float textureRatio;
};
class ScreenUtils: public Object{
	AX_SYNTHESIZE_READONLY(float, m_Scale, Scale);
	AX_SYNTHESIZE_READONLY(float, m_ImageScale, ImageScale);
	AX_SYNTHESIZE_READONLY(Size, m_spriteSize, SpriteSize);
private:
	std::vector<ScreenProperty> list;
	//float scale;
	void findSize();
	//
	float selectScale;
	float limitZoom;
	float _texture_Ratio;
protected:
	bool init ();
public:
	static ScreenUtils* share();
	static float textureRatio();
	static float imageScale();
	static float defaultScale();
	static std::string fileFull(const char* fileName);
	static std::string  fileCommon(const char* fileName);
	
};
#endif
