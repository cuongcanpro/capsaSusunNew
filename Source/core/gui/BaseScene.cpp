#include "BaseScene.h"
#include "SceneMgr.h"


BaseScene::BaseScene()
{
    init();
}

BaseScene::~BaseScene()
{

}

BaseScene* BaseScene::createWithLayer(ax::Node* layer)
{
    Size size        = Director::getInstance()->getVisibleSize();
	BaseScene* scene = new BaseScene();
	scene->autorelease();
	scene->addChild(layer);
        layer->setAnchorPoint(Vec2(0, 0));
	scene->scheduleUpdate();
   // layer->setPosition(size.width * 0.5, size.height * 0.5);
	return scene;
}

BaseScene* BaseScene::makeScene(ax::Node* layer)
{
	BaseScene* scene = new BaseScene();
	scene->addChild(layer);
	scene->autorelease();
	scene->scheduleUpdate();
	return scene;
}

bool BaseScene::init()
{
	Scene::init();
	return true;
}

void BaseScene::onEnter()
{
	Scene::onEnter();
	sceneMgr->initialLayer();
}

void BaseScene::addChild(ax::Node* child, int tag, int order)
{
	Scene::addChild(child);
	child->setTag(tag);
	child->setLocalZOrder(order);
	//setContentSize(Director::getInstance()->getVisibleSize());
	//setAnchorPoint(Vec2(0.5, 0.5));

	//layer Touch
	/*EffectTouchLayer* effLayer = EffectTouchLayer::getInstance();
	effLayer->removeFromParent();
	effLayer->setTag(EffectTouchLayer::TAG);
	effLayer->setLocalZOrder(EffectTouchLayer::TAG);
	Scene::addChild(effLayer);
	effLayer->startEffect();*/
	//effLayer->startEffectVip();
}

ax::Node* BaseScene::getMainLayer()
{
	return getChildByTag(BaseScene::TAG_LAYER);
}

ax::Node* BaseScene::getLayerGUI()
{
	return getChildByTag(BaseScene::TAG_GUI);
}

void BaseScene::update(float dt)
{
	sceneMgr->updateScene(dt);
}

const int BaseScene::TAG_LAYER = 101;

const int BaseScene::TAG_GUI = 102;

