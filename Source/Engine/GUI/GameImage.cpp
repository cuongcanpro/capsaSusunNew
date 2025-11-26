#include "GameImage.h"

using namespace ax;



GameImage::GameImage(void)
{ 
	_scaleRootX=1.0f;
	_scaleRootY=1.0f;
	_enable=true;
}


GameImage::~GameImage(void)
{
	clear();
}

GameImage::GameImage(const char* imageName, bool frame)
{
	_img = CScaleSprite::create(imageName, frame);
	this->addChild(_img);
	_scaleRootX=1.0f;
	_scaleRootY=1.0f;
	_enable=true;
	setCascadeOpacityEnabled(true);
	setCascadeColorEnabled(true);
}

GameImage::GameImage(Node* parent, const char * imageName, float x, float y) :Node()
{
	_img = CScaleSprite::create(imageName);
	this->addChild(_img);

	if(parent)
	{
		parent->addChild(this);
	}
	if(imageName==NULL)
	{
		autorelease();
	}
	setPos(x,y);
	_scaleRootX=1.0f;
	_scaleRootY=1.0f;
	_enable=true;
}

void GameImage::setPos(float x,float y)
{
	setPosition(Vec2(x,y));
}

void GameImage::setVisible(bool visible)
{
	Node::setVisible(visible);
	_img->setVisible(visible);
}
bool GameImage::getVisible()
{
	return _img->isVisible()&&isVisible();
}

float GameImage::getWidth()
{
	int asd = _img->getWidth();
	int asdd = _img->getScaleX();
	return _img->getWidth()*_scaleRootX;
}

void GameImage::setWidth(float widthValue)
{
	float scale = widthValue/getWidth();
	this->setScaleX(scale);
}

void GameImage::setHeight(float heightValue)
{
	float scale = heightValue/getHeight();
	this->setScaleY(scale);
}

float GameImage::getHeight()
{
	return _img->getHeight()*_scaleRootY;
}

Rect GameImage::rect()	
{
	Size s = Size(_img->getWidth(),_img->getHeight());
	Point p;
	p=_img->getPosition();
	return Rect(p.x-s.width*_img->getAnchorPoint().x,p.y-s.height*_img->getAnchorPoint().y, s.width, s.height);
};

bool GameImage::containsTouchLocation(Touch* touch)
{
	Point pos=convertTouchToNodeSpaceAR(touch);
	return  rect().containsPoint(pos);
}

void GameImage::setImage(const char*namImg, bool isFrame)
{
	removeAllChildren();
	_img = CScaleSprite::create(namImg, isFrame);
	addChild(_img);
	//_img->setTexture(ResMgr::getTexture2D(namImg));
}

void GameImage::setOnlyImage( const char* namImg)
{
	removeChild(_img);
	_img = CScaleSprite::create(namImg);
	addChild(_img);
}
void GameImage::registerTouch()
{
	Director* pDirector = Director::getInstance();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	Node::onEnter();
}

void GameImage::clear()
{
	if (this->getParent())
	{
		_img->stopAllActions();
		onExit();
		this->removeAllChildren();
		this->removeFromParentAndCleanup(true);
	}
}


void GameImage::addMoveEffect(float x, float y)
{
	// TODO: Add movement time based on speed
	MoveTo *actionMove = MoveTo::create(0.2f, Point(x, y));
	stopAllActions();
	this->runAction(actionMove);
}

void GameImage::setFlipX( bool flip )
{
	_img->setFlippedX(flip);
}

void GameImage::setAnchorPointImage( const Point &anchorPoint )
{
	_img->setAnchorPoint(anchorPoint);
}
const Point& GameImage::getAnchorPointImage()
{
	return _img->getAnchorPoint();
}
void GameImage::removeTouch()
{
	Director* pDirector = Director::getInstance();
	//pDirector->getTouchDispatcher()->removeDelegate(this);
}

void GameImage::addEffectScaleSmaler()
{
	// Actions presets
	float scX=0.9f*_scaleRootX;
	float scY=0.9f*_scaleRootY;
	ActionInterval*  actionBy = ScaleBy::create(0.1f,scX , scY);


	// TODO: restore original scale
	this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);

	// Run action
	this->runAction(actionBy);

}

void GameImage::addEffectScaleLager()
{
	// Actions presets
	ActionInterval*  actionBy = ScaleBy::create(0.1f,1.15f ,1.15f);


	// TODO: restore original scale
	//this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);

	// Run action
	this->runAction( actionBy);

}

void GameImage::addEffectSweep()
{
	
}

void GameImage::setScaleRoot( float scale )
{
	_scaleRootX=scale;
	_scaleRootY = scale;

}

void GameImage::setScaleRootX( float scaleX)
{
	_scaleRootX=scaleX;
}

void GameImage::setScaleRootY( float scaleY)
{
	_scaleRootY=scaleY;
}

CScaleSprite* GameImage::getSprite()
{
	return _img;
}
void GameImage::addEffScaleRoot()
{
	//this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);
}

void GameImage::addEffectBubble()
{
	// Actions presets
	ActionInterval*  actionBy = ScaleBy::create(0.1f, 1.17f*_scaleRootX, 1.17f*_scaleRootY);


	// TODO: restore original scale
	this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);

	// Run action
	this->runAction( Sequence::create(actionBy, actionBy->reverse(), NULL));
}

void GameImage::setEnable(bool enable)
{
	_enable=enable;
	if(enable)
	{
 #if AX_TARGET_PLATFORM == AX_PLATFORM_WP8
 		_img->setColor(Vec3(255, 255, 255));
 #else
		_img->setColor(Color3B(255, 255, 255));
	//	_img->setShaderProgram(ShaderCache::sharedShaderCache()->programForKey(kShaderNormal));
		//_img
#endif
	}
	else
	{
		setDisable();
	}
}

void GameImage::setDisable()
{
 #if AX_TARGET_PLATFORM == AX_PLATFORM_WP8
 	_img->setColor(Vec3(100, 100, 100));
 #else
    _img->setColor(Color3B(100, 100, 100));
	//_img->setShaderProgram(ShaderCache::sharedShaderCache()->programForKey(kShaderGrayProgram));
#endif
	_enable=false;
}
void GameImage::addEffFadeIn(float time, SEL_CallFuncN callBack )
{
	
}


void GameImage::addEffFadeOut( float time,float delay,SEL_CallFuncN callBack )
{
	
}

void GameImage::setOpacity( GLubyte alpha )
{
	_img->setOpacity(alpha);
}

bool GameImage::isEnable()
{
	return _enable;

}

void GameImage::addEffTint()
{
	// Create actions
	ActionInterval* action1		= TintBy::create(0.75f, -150, -150, -150);
	ActionInterval* action1Back	= action1->reverse();
	ActionInterval* actionScale=ScaleTo::create(0.75f,0.95f,0.95f);
	ActionInterval* actionScaleBack=ScaleTo::create(0.75f,1.1f,1.1f);
	ActionInterval* action11=Sequence::create(action1, 
		action1Back, 
		NULL );
	ActionInterval* action21=Sequence::create(actionScale, 
		actionScaleBack, 
		NULL );

	FiniteTimeAction* actionSpaw=Spawn::create(
			action11,
			action21,
			NULL);
	

	RepeatForever *repeatAction = RepeatForever::create((ActionInterval*)action21);

	// Run action
	_img->stopAllActions();
	_img->setColor(Color3B::WHITE);
	_img->runAction( repeatAction);
}

void GameImage::addEffArrowVertical()
{
	

}

void GameImage::removeEffTint()
{
	if(_img)
	{
		_img->stopAllActions();
		_img->setScale(1);
	}

}

void GameImage::setLighter( bool light )
{

}

void GameImage::setColor(Color3B color )
{
	_img->setColor(color);
}

void GameImage::setImgContentSize(Size size)
{
	_img->setContentSize(size);
}

Sprite* GameImage::getImg()
{
	return _img;
}

float GameImage::getRealWidth()
{
	return _img->getWidth() * getScaleX();
}

float GameImage::getRealHeight()
{
	return _img->getHeight() * getScaleY();
}
