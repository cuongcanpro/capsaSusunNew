#include "Toast.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"


Toast::Toast(void)
{
	
}


Toast::~Toast(void)
{
}

bool Toast::init(){
	if (!Node::init())
	{
		return false;
	}

	return true;
}

Toast *Toast::create(const char* _lb){
	Toast *_toast = Toast::create();
	Size size1 = Director::getInstance()->getRenderView()->getVisibleSize();
	_toast->_label = ui::Text::create(_lb, "fonts/tahomabd.ttf", 20 * size1.width / 480);
        _toast->_label->setTextHorizontalAlignment(TextHAlignment::CENTER);
        _toast->_label->setTextVerticalAlignment(TextVAlignment::CENTER);
      //  _toast->_label->setTextAreaSize(Size(400, 100));
        
        _toast->_label->setTextAreaSize(Size(-1, -1));
        _toast->_label->ignoreContentAdaptWithSize(true);
    //_toast->_label->setWidt(size.width * 0.9f);
	//_toast->_label->setDimensions(Size(100,300));

	Size size = _toast->_label->getContentSize();

	_toast->_9patch = ui::Scale9Sprite::create(ScreenUtils::fileFull("9patch.png").c_str());
	_toast->_9patch->setPreferredSize(Size(size.width + 16, size.height + 30));

	_toast->_9patch->setColor(Color3B::WHITE);
	_toast->addChild(_toast->_9patch);
	_toast->addChild(_toast->_label);

	_toast->setContentSize(Size(size.width,size.height));
	return _toast;
}

void Toast::setMsg(const char* msg)
{
    Size size1 = Director::getInstance()->getRenderView()->getVisibleSize();
    _label->setTextAreaSize(Size(-1, -1));
	_label->setString(msg);
    if (_label->getContentSize().width > size1.width * 0.9)
    {
        _label->setTextAreaSize(Size(size1.width * 0.9, -1));
    }

    Size _size = _label->getContentSize();
        
	_9patch->setPreferredSize(Size(_size.width + 16,_size.height +12));

	setContentSize(Size(_size.width + 16,_size.height + 12));
}
void Toast::clearToast()
{
	Toast *_toast = (Toast *)layerMgr->getLayerByIndex(LAYER_CURSOR)->getChildByTag(11);
	if (_toast)
	{
		_toast->_9patch->stopAllActions();
		_toast->_label->stopAllActions();
		_toast->stopAllActions();
		_toast->setVisible(false);	
	}
}

void Toast::makeToast(float duration,const char* msg){

	Toast *_toast = (Toast *)layerMgr->getLayerByIndex(LAYER_CURSOR)->getChildByTag(11);

	if (_toast == NULL)
	{
		_toast = Toast::create(msg);
		layerMgr->getLayerByIndex(LAYER_CURSOR)->addChild(_toast);
		_toast->setTag(11);
	}
	else
	{
		_toast->_9patch->stopAllActions();
		_toast->_label->stopAllActions();
		_toast->stopAllActions();
		_toast->setMsg(msg);
		_toast->setVisible(false);	
	}
	Size winSize = Director::getInstance()->getWinSize();
	_toast->setPosition(winSize.width/2, winSize.height * 0.2f);
	_toast->_9patch->setOpacity(0);
	_toast->_label->setOpacity(0);
	_toast->_9patch->runAction(Sequence::create(FadeIn::create(.15f),DelayTime::create(duration),FadeOut::create(.15f),NULL));
	_toast->_label->runAction(Sequence::create(FadeIn::create(.15f),DelayTime::create(duration),FadeOut::create(.15f),NULL));
	_toast->runAction(Sequence::create(Show::create(),DelayTime::create(duration + .3f),Hide::create(),NULL));
	
}

void Toast::callbackFree(Node *sender){
	sender->removeFromParentAndCleanup(true);
}
