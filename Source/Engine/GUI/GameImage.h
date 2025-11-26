#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "axmol.h"
#include "CScaleSprite.h"

using namespace ax;
class GameImage :public ax::Node
{
public:
	CScaleSprite* _img;
	float _scaleRootX;
	float _scaleRootY;
	bool _enable;
public:
	GameImage(void);
	~GameImage(void);
	GameImage(const char* imageName, bool frame = false);
	GameImage(ax::Node* parent,const char* imageName,float x,float y);
	int id;
	void setPos(float,float);
	virtual void setVisible(bool visible);
	bool getVisible();
	void setWidth(float width);
	void setHeight(float height);
	float getWidth();
	float getHeight();
	void setFlipX(bool flip);
	void setColor(Color3B color);
    
	//virtual void onEnter();
	//virtual void onExit();
	//virtual bool ccTouchBegan(Touch*touch,Event* event);
	//virtual void ccTouchMoved(Touch*touch,Event* event);
	//virtual void ccTouchEnded(Touch*touch,Event* event);
	Rect rect();
	bool containsTouchLocation(Touch* touch);
	void setImage(const char*, bool isFrame = false);
	void setOnlyImage(const char*);
	void registerTouch();
	void removeTouch();
	void clear();
	void setAnchorPointImage(const Vec2 &anchorPoint);
	const Vec2 & getAnchorPointImage();
	void setScaleRoot(float scale);
	void setScaleRootX(float scaleX);
	void setScaleRootY(float scaleY);
	CScaleSprite* getSprite();

	float getRealWidth();
	float getRealHeight();
public:
	void addEffectScaleSmaler();
	void addEffectScaleLager();
	void addEffectBubble();
	void addMoveEffect(float x, float y);
	void addEffectSweep();
	void addEffScaleRoot();
	void addEffFadeIn(float time,SEL_CallFuncN callBack);
	void addEffFadeOut(float time,float delay,SEL_CallFuncN callBack);
	void addEffTint();
	void removeEffTint();
	void addEffArrowVertical();
public: 
	void setLighter(bool light);
	void setEnable(bool enable=true);
	void setDisable();
	void setOpacity(GLubyte	alpha);
	//void addLabel(LabelBM* text);
	bool isEnable();
	void setImgContentSize(Size size);
	Sprite* getImg();
};

#endif
