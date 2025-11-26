#include "GUIMgr.h"
#include "../Layers/GameLayer.h"
#include "../GlobalVar.h"

GUIMgr::GUIMgr(void)
{
	// Get GUI layer

	creatFog();
}


GUIMgr::~GUIMgr(void)
{
}

void GUIMgr::onUpdate(float delta)
{
	for (std::map<int, BaseGUI*>::iterator it = GUIList.begin();it!=GUIList.end();++it)
	{
		it->second->onUpdate(delta);
	}
}

//CCRenderTexture* GUIMgr::creatStroke( CCSprite* sprite,int size,ccColor4B color, GLubyte opacity )
//{
//	float width=sprite->getTexture()->getContentSize().width;
//	float height=sprite->getTexture()->getContentSize().height;
//	CCRenderTexture* rt=CCRenderTexture::create(
//		width+size*2,
//		height+size*2);
//	CCPoint originalPos=sprite->getPosition();
//	ccColor4B originalColor= sprite->getColor();
//	GLubyte originalOpacity=sprite->getOpacity();
//	bool originalVisibility= sprite->isVisible();
//	sprite->setColor(color);
//	sprite->setOpacity(opacity);
//
//	sprite->setVisible(true);
//	ccBlendFunc originalBlend= sprite->getBlendFunc();
//	ccBlendFunc bf={GL_SRC_ALPHA,GL_ONE};
//	sprite->setBlendFunc(bf);
//	CCPoint bottomLeft=ccp(width*sprite->getAnchorPoint().x+size,height*sprite->getAnchorPoint().y+size);
//	CCPoint posOffset=ccp(width*sprite->getAnchorPoint().x-width/2,height*sprite->getAnchorPoint().y-height/2);
//	CCPoint pos=ccpSub(originalPos,posOffset);
//	rt->begin();
//	int degree=360;
//	for (int i = 0; i < degree; i+=15)
//	{
//		sprite->setPosition(ccp(bottomLeft.x+sin(AX_DEGREES_TO_RADIANS(i))*size
//			,bottomLeft.y+cos(AX_DEGREES_TO_RADIANS(i))*size));
//		sprite->visit();
//	}
//
//	rt->end();
//	sprite->setPosition(originalPos);
//	sprite->setColor(originalColor);
//	sprite->setBlendFunc(originalBlend);
//	sprite->setVisible(originalVisibility);
//	sprite->setOpacity(originalOpacity);
//	rt->setPosition(pos);
//	rt->getSprite()->getTexture()->setAntiAliasTexParameters();
//
//	return rt;
//
//}



void GUIMgr::hideFog()
{
	fog->setVisible(false);
}

void GUIMgr::showFog()
{
	fog->setVisible(true);
	fog->setOpacity(0);
	fog->stopAllActions();
	ActionInterval*  action1 = FadeTo::create(0.5f,255*0.7);
	fog->runAction(action1);
}

void GUIMgr::creatFog()
{
	Layer* layer;
	fog= LayerColor::create( Color4B(0, 0, 0, 100) );
	layer = layerMgr->getLayerByIndex(LAYER_GUI);
	layer->addChild(fog);
	fog->setVisible(false);
}

void GUIMgr::hideAll()
{

}

void GUIMgr::clean()
{


}

void GUIMgr::addGUI(int guiID, BaseGUI* gui)
{
	addGUI(guiID, gui, LAYER_GUI);
}

void GUIMgr::addGUI(int guiID, BaseGUI* gui, int LayerID)
{
	// Add in GUI list
	GUIList.insert(std::pair<int, BaseGUI*>(guiID, gui));

	// Add in render layer
	gui->initWithParent(LayerID);
	gui->setPos(0, 0);
}

BaseGUI* GUIMgr::getGUI(int guiID)
{
	if (GUIList.find(guiID) != GUIList.end())
		return (BaseGUI*) GUIList.at(guiID);

	return NULL;
}
