#ifndef BaseLayer_h__
#define BaseLayer_h__
#include "axmol.h"
#include "extensions/axmol-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "core/utils/TimeUtil.h"
#include "core/utils/StringUtility.h"
#include "core/utils/StorageUtil.h"
#include "core/utils/LanguageMgr.h"
#include <vector>
#include <string>
#include "app/Constant.h"

using namespace ax;
using namespace ax::ui;
using namespace cocostudio;
using namespace std;

#define WIN_SIZE Director::getInstance()->getVisibleSize()

class BaseLayer:
	public Layer
{
public:
	BaseLayer();
	~BaseLayer();
	virtual bool init(std::string id = "");
	bool isShow;
public:
	virtual void onEnter();
	virtual void onExit();
	virtual void initWithJsonFile(std::string json);
	virtual void doEffect() {};
	virtual void initWithBinaryFile(std::string json);
	virtual void setAsPopup(bool value, bool isCache);

	virtual ax::ui::Button* customizeButton(std::string name, int tag, ax::Node* parent = nullptr);
	virtual ax::ui::Button* customButton(std::string name, int tag, ax::Node* parent = nullptr, bool action = true);
	virtual void setLabelWithLength(std::string text, ax::ui::Text* label);
	virtual void setLabelText(std::string text, ax::ui::Text* control);
	virtual ax::Node* getControl(std::string cName, ax::Node* parent = nullptr, std::string sParent = "object");
	virtual ax::Node* getControl(std::string cName, std::string parent);
	virtual void processScaleControl(ax::Node* control, int direct = -1);
	virtual void analyzeCustomControl(ax::Node* control);
	virtual void processListControl(std::string name, int num);
	virtual void setFog(bool isVisible, float alpha = 150);
	virtual void removeFog();
	virtual void enableFog();
	virtual void setDelayInit(float time = 0.35f);
	virtual void setShowHideAnimate(ax::Node* parent = nullptr, bool customScale = false);
	virtual void onClose();
	virtual void onCloseDone();
	virtual void setBackEnable(bool enable);
	virtual void backKeyPress();
	virtual void resetDefaultPosition(ax::Node* control);
	virtual void onTouchEventHandler(ax::Object *pSender, ax::ui::Widget::TouchEventType type);
	virtual void customizeGUI() {};
	virtual void onEnterFinish() {};
	virtual void onButtonRelease(ax::ui::Button* button, int id) {};
	virtual void onButtonCanceled(ax::ui::Button* button, int id) {};
	virtual void onButtonTouched(ax::ui::Button* button, int id) {};
	virtual void onUpdateGUI() {};
	virtual void initGUI()=0;
	virtual void functionDelayInit() {};
	virtual void finishAnimate() {};
	virtual void onBack() {};

    void moveHorizontal(Node* btn, float sX, float dX, float delay);
    void moveVertical(Node* btn, float sY, float dY, float delay);
    void moveEffect(Node* node, float dx, float dy, float delay);
    void moveEffectSineOut(Node* node, float dx, float dy, float delay);
    void moveOutEffect(Node* node, float dx, float dy, float delay);
	ax::Vec2 getDefaultPos(ax::Node* control);
	void localizedText(ax::Node* node);
	//void playSoundButton();
	bool compare(BaseLayer *a);
public:
	static ax::ui::Text* createLabelText(std::string txt = "", ax::Color3B color = ax::Color3B::WHITE);
	static ax::ui::EditBox* createEditBox(ax::ui::TextField* tf);
	static void subLabelText(ax::ui::Text* lb, std::string txt, std::string defaultString = "");
	static ax::Vec2 outsidePostion(ax::Vec2 point);
	void effectInOutside(ax::Node* control, float time = 0);
	static float TIME_APPEAR_GUI;
public:
	bool _hasInit;
	std::string _id;
	ax::Node* _layout;
	ax::Node* _bg;
	std::string _layoutPath;
	float _scale;
	float _scaleRealX;
	float _scaleRealY;
	//ax::Node* _layerGUI;
	bool _aaPopup;
	bool _showHideAnimate;
	ax::Node* _bgShowHideAnimate;
	float _currentScaleBg;
	bool _enableBack;

	ax::ui::Layout* _layerColor;
	ax::Layer* _layerGUI;
	ax::EventListenerKeyboard* _keyboardEvent;
	ax::EventListenerTouchOneByOne* _listener;

	bool _cachePopup;

	std::map<ax::Node*, int> _subText;
	std::map<ax::Node*, int> _wrapText;
	std::map<ax::Node*, ax::Vec2> _defaultPos;
	float _layerAlpha;

	ax::LayerColor* _fog;
	std::string lastGUI;

};

struct RichTextInfo 
{
	std::string font;
	float size;
	Color3B color;
	std::string text;
};

class RichLabelText : public Node {

public:
	std::vector<ui::Text*> listText;
	std::vector<RichTextInfo> listInfo;
	RichLabelText() {

	}

	~RichLabelText() {

	}

	void setText(vector<RichTextInfo> txts) {
		if (txts.size() == 0) return;

		removeAllChildren();

		listText.clear();
		listInfo.clear();

		listInfo = txts;
		for (int i = 0, size = txts.size(); i < size; i++)
		{
			RichTextInfo info = txts[i];
			ui::Text* lb = BaseLayer::createLabelText();

			if (!info.font.empty()) lb->setFontName(info.font);
			else lb->setFontName("fonts/tahomba.ttf");

			if (info.size > 0) lb->setFontSize(info.size);
			else lb->setFontSize(26);

			lb->setColor(info.color);

			if (!info.text.empty()) lb->setString(info.text);

			lb->setAnchorPoint(Vec2(0, 0));
			addChild(lb);

			listText.push_back(lb);
		}

		updatePosition();
	}

	void updateText(int idx,std::string txt) {
		listInfo[idx].text = txt;

		updatePosition();
	}

	void updatePosition() {
		float nextWidth = 0;
		for (int i = 0, size = listText.size(); i < size; i++)
		{
			ui::Text* lb = listText[i];
			lb->setString(listInfo[i].text);
			lb->setPositionX(nextWidth);

			nextWidth = lb->getContentSize().width + lb->getPositionX();
		}
	}

	float getWidth() {
		float retVal = 0;
		for (int i = 0, size = listText.size(); i < size; i++)
		{
			retVal += listText[i]->getContentSize().width;
		}

		return retVal;
	}

	float getHeight () {
		float maxHeight = 0;
		for (int i = 0, size = listText.size(); i < size; i++)
		{
			if (maxHeight < listText[i]->getContentSize().height)
				maxHeight = listText[i]->getContentSize().height;
		}

		return maxHeight;
	}
};
#endif // BaseLayer_h__
