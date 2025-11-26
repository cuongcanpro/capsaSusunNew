#ifndef CustomLabel_h__
#define CustomLabel_h__

#include "axmol.h"
#include "extensions/axmol-ext.h"
//#include "cocos/ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ax;

static const int CUSTOM_LABEL_ALIGN_LEFT = 0;
static const int CUSTOM_LABEL_ALIGN_RIGHT = 1;
static const int CUSTOM_LABEL_ALIGN_CENTER = 2;
static const int CUSTOM_LABEL_ALIGN_JUSTIFIED = 3;
static const int CUSTOM_LABEL_ALIGN_TOP = 4;
static const int CUSTOM_LABEL_ALIGN_MIDDLE = 5;
static const int CUSTOM_LABEL_ALIGN_BOTTOM = 6;

struct CustomLabelObject {
	std::string text;
	std::string font;
	int size;
	ax::Color3B color;
	int opacity;
};

class CustomLabel : public ax::Layer {
public:
	int _curId;
	std::string _font;
	int _size;
	Color3B _color;
	ui::RichText *_richText;

public:
	CustomLabel(Size s);
	~CustomLabel();

	bool init();

	void setIgnoreSize(bool val);
	void setTextContentSize(Size size);
	Size getTextContentSize();
	void setDefaultFont(std::string font);
	void setDefaultSize(int size);
	void setDefaultColor(Color3B color);
	//ui::RichText::Align convertAlign(int align);
	///void setDefaultAlignHorizontal(int id);
	//void setDefaultAlignVertical(int id);
	void appendText(std::string text, std::string font, int size, Color3B color, int opacity, bool enableTouch);
	void clearText();
	int getAutoId();
	void setString(std::string text);

	ax::Color3B parseColor(std::string text);
};

#endif // CustomLabel_h__
