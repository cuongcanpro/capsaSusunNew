#include "SceneMgr.h"
#include "Waiting.h"
#include "app/Constant.h"
#include "app/Config.h"
#include "app/GameMgr.h"
#include "../utils/StringUtility.h"
#include "app/GUIFactory.h"

using namespace ax::ui;
const int LOADING_TAG = 999999998;
const int WAITING_TAG = 99999997;

const int TOAST_FLOAT_TAG = 99999998;
const int LOADING_FLOAT_TAG = 99999999;


SceneMgr::SceneMgr()
{
	ccWhite = Color3B(203, 204, 206);
	ccYellow = Color3B(251, 212, 93);
	ccGreen = Color3B(9, 212, 9);
	ccBlue = Color3B(132, 140, 220);

	curGui = "";

	layerGUI = nullptr;
	layerSystem = nullptr;

	ignoreGuis.push_back("ChatScene");  // default scene not cache
}

SceneMgr::~SceneMgr()
{

}

SceneMgr* SceneMgr::getInstance()
{
	if (!_instance) {
		_instance = new SceneMgr();
	}
	return _instance;
}

BaseScene* SceneMgr::getRunningScene()
{
	Scene* currentScene = Director::getInstance()->getRunningScene();
	return (BaseScene*)currentScene;
}

ax::Node* SceneMgr::getMainLayer()
{
	BaseScene* curScene = getRunningScene();
	if (!curScene) return nullptr;
	if (!curScene->getMainLayer()) return nullptr;
	return curScene->getMainLayer();
}

LoadingGui* SceneMgr::addLoading(std::string text, bool fog)
{
	Node* oldLoading = layerGUI->getChildByTag(LOADING_TAG);
	if (oldLoading) {
		oldLoading->stopAllActions();
		oldLoading->removeFromParent();
	}

	LoadingGui* loading = LoadingGui::create(text, fog);
	layerGUI->addChild(loading);

	loading->setLocalZOrder(LOADING_TAG);
	loading->setTag(LOADING_TAG);
	return loading;
}

void SceneMgr::clearLoading()
{
	Node* loading = layerGUI->getChildByTag(LOADING_TAG);
	if (loading) {
		loading->stopAllActions();
		loading->removeFromParent();
	}
}

void SceneMgr::addWaiting()
{
	Node* oldLoading = layerGUI->getChildByTag(WAITING_TAG);
	if (oldLoading) {
		oldLoading->stopAllActions();
		oldLoading->removeFromParent();
	}

	Waiting* loading = Waiting::create();
	layerGUI->addChild(loading);

	loading->setLocalZOrder(WAITING_TAG);
	loading->setTag(WAITING_TAG);
	loading->timeout(15);
}

void SceneMgr::clearWaiting()
{
	Node* loading = layerGUI->getChildByTag(WAITING_TAG);
	if (loading) {
		loading->stopAllActions();
		loading->removeFromParent();
	}
}

void SceneMgr::updateCurrentGUI()
{
	BaseLayer* gui = (BaseLayer*)getRunningScene()->getMainLayer();
	if (gui) {
		gui->onUpdateGUI();
	}
}

void SceneMgr::addQueueScene(std::string layer)
{
	for (int i = 0, size = backScenes.size(); i < size; i++) {
		if (backScenes[i] == layer) return;
	}

	backScenes.push_back(layer);
}

std::string SceneMgr::getQueueScene(bool direct /*= false*/)
{
	if (direct) {
		backScenes.clear();
	}

	if (backScenes.size() <= 0)
		return "";

	int sIdx = backScenes.size() - 1;
	std::string sLayer = backScenes[sIdx];
	backScenes.pop_back();

	return sLayer;
}

BaseLayer* SceneMgr::openScene(std::string layerName, std::string callback /*= ""*/, bool direct /*= false*/, bool cache /*= false*/)
{
	AXLOGD("openScene %s", layerName.c_str());

	bool isCallback = true;
	

	if (layerName.compare(curGui) == 0) {
		return nullptr;
	}

	if (layerGUI && layerGUI->getParent()) {
		layerGUI->removeAllChildren();
		layerGUI->retain();
	}

	if (layerSystem && layerSystem->getParent()) {
		layerSystem->removeAllChildren();
		layerSystem->retain();
	}


	if (isCallback) {
		std::string backLayer = getQueueScene(direct);
		if (!backLayer.empty()) {
			layerName = backLayer;
		}

		if (!callback.empty()) {
			addQueueScene(callback);
		}
	}
	else {
		backScenes.clear();
	}

	BaseLayer* curLayer = nullptr;
	if (arGuis.find(curGui) != arGuis.end()) {
		arGuis[curGui]->retain();
	}

	curGui = layerName;
	bool isCache = false;
	if (cache)
		isCache = true;
	for (int i = 0; i < (int)ignoreGuis.size(); i++) {
		if (ignoreGuis[i].compare(layerName) == 0) {
			isCache = false;
			break;
		}
	}
	if (cache == false) isCache = false;

	if (isCache) {
		if (arGuis.find(layerName) != arGuis.end()) {
			curLayer = arGuis[layerName];
		}
		else {
			curLayer = GUIFactory::createGUI(layerName);
			arGuis[layerName] = curLayer;
            curLayer->retain();
		}
	}
	else {
		curLayer = GUIFactory::createGUI(layerName);
		arGuis[layerName] = curLayer;
	}

	BaseScene* scene = BaseScene::createWithLayer(curLayer);

	Director::getInstance()->replaceScene(scene);

	return curLayer;
}

BaseLayer* SceneMgr::openGUI(std::string slayer, int zoder, int tag, bool isCache)
{
	BaseLayer* layer = nullptr;

	if (isCache) {
		if (arPopups.find(slayer) != arPopups.end()) {
			layer = arPopups[slayer];
		}
		else {
			std::string _class = getClassGUI(slayer);
			layer = GUIFactory::createGUI(slayer);
			arPopups[slayer] = layer;
		}
	}
	else {
		std::string _class = getClassGUI(slayer);
		layer = GUIFactory::createGUI(slayer);
	}

	if (layer != nullptr) {
		if (layer->getParent()) {
			layer->removeFromParent();
		}
	}

	if (layer) {
		layer->setAsPopup(true, isCache);
		layerGUI->addChild(layer, zoder, tag);
	}
	return layer;
}
std::string SceneMgr::getClassGUI(std::string cName) {
	if (cName.empty())
		return cName;

	int cIdx = cName.find("_");
	if (cIdx != std::string::npos) {
		cName = cName.substr(0, cIdx);
	}

	return cName;
}
void SceneMgr::preloadScene(std::string layer)
{
	if (arGuis.find(layer) == arGuis.end()) {
		BaseLayer* ll = GUIFactory::createGUI(layer);
		ll->retain();
		arGuis[layer] = ll;
	}
}

ax::Node* SceneMgr::getGUI(int tag)
{
	return layerGUI->getChildByTag(tag);
}

ax::Node * SceneMgr::getGUIByClassName(string className)
{
	if (className == "" || arPopups.count(className) == 0) return nullptr;
	else return arPopups[className];
}

void SceneMgr::initialLayer()
{
	numDialog = 0;

	if (layerGUI == nullptr) {
		layerGUI = Layer::create();
	}
	else {
		if (layerGUI->getParent()) {
			layerGUI->removeFromParent();
		}
	}

	if (layerSystem == nullptr) {
		layerSystem = Layer::create();
	}
	else {
		if (layerSystem->getParent()) {
			layerSystem->removeFromParent();
		}
	}

	getRunningScene()->addChild(layerGUI, BaseScene::TAG_GUI, BaseScene::TAG_GUI);
	getRunningScene()->addChild(layerSystem, BaseScene::TAG_GUI + 1, BaseScene::TAG_GUI + 1);

	gameMgr->onEnterScene();
}

void SceneMgr::addLayerGUI(Node *x) {
	if(layerGUI)
		layerGUI->addChild(x);
}

void SceneMgr::addLayerSystem(Node *x) {
	if (layerSystem)
		layerSystem->addChild(x);
}

void SceneMgr::updateScene(float dt)
{
	effectMgr->updateEffect(dt);
	GameMgr::getInstance()->onUpdateScene(dt);
}

bool SceneMgr::checkBackAvailable(std::vector<std::string> ignores /*= {}*/)
{
	for (const auto& kv : arPopups) {
		bool check = true;
		for (int i = 0; i < (int)ignores.size(); i++) {
			if (kv.first == ignores[i]) {
				check = false;
				break;
			}
		}

		if (check) {
			BaseLayer* g = kv.second;
			if (g && g->getParent() && g->_enableBack ) {
				return true;
			}
		}
	}

	return false;
}

void SceneMgr::showAddGDialog(std::string message, const DialogListener& callback)
{
	AXLOGD("#showAddGDialog : %s", message.c_str());

	Dialog* dlg = (Dialog*)openGUI(Dialog::className, Dialog::ZODER, Dialog::TAG, false);
	dlg->setAddG(message, callback);
}

void SceneMgr::showOkCancelDialog(std::string message, const DialogListener& callback)
{
	AXLOGD("#showOkCancelDialog : %s", message.c_str());

	Dialog* dlg = (Dialog*)openGUI(Dialog::className, Dialog::ZODER, Dialog::TAG, false);
	dlg->setOkCancel(message, callback);
}

void SceneMgr::showOkDialogWithAction(std::string message, const DialogListener& callback)
{
	Dialog* dlg = (Dialog*)openGUI(Dialog::className, Dialog::ZODER, Dialog::TAG, false);
	dlg->setOkWithAction(message, callback);
}

void SceneMgr::showOKDialog(std::string message)
{
	Dialog* dlg = (Dialog*)openGUI(Dialog::className, Dialog::ZODER, Dialog::TAG, false);
	dlg->setOKNotify(message);
}

void SceneMgr::showChangeGoldDialog(std::string message, const DialogListener& callback)
{
	Dialog* dlg = (Dialog*)openGUI(Dialog::className, Dialog::ZODER, Dialog::TAG, false);
	dlg->setChangeGold(message, callback);
}


void SceneMgr::restartCacheGui()
{
	arGuis.clear();
	arPopups.clear();
}

SceneMgr* SceneMgr::_instance = nullptr;

const int SceneMgr::FONT_SIZE_DEFAULT = 15;

ToastFloat::ToastFloat()
{

}

ToastFloat::~ToastFloat()
{

}

bool ToastFloat::init()
{
	Node::init();

	timeDelay = -1;
	isRunningDelay = false;

	lb = nullptr;
	bg = nullptr;

	bg = ui::Scale9Sprite::create("Game/bgBubble.png");
	addChild(bg);

	_scale = Director::getInstance()->getVisibleSize().width / CONSTANT_WIDTH;
	_scale = (_scale > 1) ? 1 : _scale;
	setScale(_scale);

	return true;
}

void ToastFloat::onEnter()
{
	Node::onEnter();

	bg->setOpacity(0);
	lb->setOpacity(0);

	bg->runAction(FadeIn::create(0.5f));
	lb->runAction(FadeIn::create(0.5f));

	runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(AX_CALLBACK_0(ToastFloat::finishEffect, this)), nullptr));
}

void ToastFloat::finishEffect()
{
	isRunningDelay = true;
}

void ToastFloat::setToast(std::string txt, float time /*= 1.0f*/)
{
	if (!txt.empty()) {
		lb = BaseLayer::createLabelText(txt);
		lb->setTextHorizontalAlignment(TextHAlignment::CENTER);
		lb->setTextVerticalAlignment(TextVAlignment::CENTER);
		lb->ignoreContentAdaptWithSize(true);
		addChild(lb);
		Size winSize = Director::getInstance()->getVisibleSize();

		Size lbSize = lb->getContentSize();
		float deltaWidth = winSize.width * ToastFloat::DELTA_WIDTH;
		if (lbSize.width > deltaWidth) {

			lb->setContentSize(Size(deltaWidth, lbSize.height * 2));
		}

		bg->setContentSize(Size(lb->getContentSize().width + ToastFloat::PAD_SIZE, lb->getContentSize().height + ToastFloat::PAD_SIZE));
	}
	timeDelay = time;
	scheduleUpdate();
}

void ToastFloat::clearToast()
{
	bg->runAction(FadeOut::create(0.5f));
	lb->runAction(FadeOut::create(0.5f));

	runAction(Sequence::create(
		DelayTime::create(0.5),
		CallFunc::create(
			AX_CALLBACK_0(ToastFloat::removeFromParent, this)
		),
		nullptr
	));
}

void ToastFloat::update(float dt)
{
	if (timeDelay > 0 && isRunningDelay) {
		timeDelay -= dt;
		if (timeDelay <= 0) {
			clearToast();
		}
	}
}

void ToastFloat::makeToast(float time, std::string text)
{
	ToastFloat* toast = ToastFloat::create();
	toast->setToast(text, time);
	Size winSize = Director::getInstance()->getVisibleSize();
	toast->setPosition(Vec2(winSize.width / 2, winSize.height * ToastFloat::POSITION_Y));

	sceneMgr->layerGUI->addChild(toast);
	toast->setLocalZOrder(TOAST_FLOAT_TAG);
}

const float ToastFloat::SHORT = 1.0f;

const float ToastFloat::LONG = 3.0f;

const float ToastFloat::MEDIUM = 2.0f;

const float ToastFloat::POSITION_Y = 1.0f / 3;

const float ToastFloat::DELTA_WIDTH = 1.0f;

const int ToastFloat::PAD_SIZE = 35;

EffectMgr::EffectMgr()
{

}

EffectMgr::~EffectMgr()
{

}

EffectMgr* EffectMgr::getInstance()
{
	if (!_instance) {
		_instance = new EffectMgr();
	}
	return _instance;
}

void EffectMgr::runLabelPoint(ax::ui::Text* label, long long cur, long long des, float delayTime /*= 0*/, int numChange /*= 50*/, int type /*= 1*/)
{
	LabelPoint* lb = nullptr;
	bool isNew = true;
	for (int i = 0, size = arLbPoints.size(); i < size; i++) {
		if (arLbPoints[i]->label == label) {
			lb = arLbPoints[i];
			isNew = false;
			break;
		}
	}

	if (isNew) {
		lb = new LabelPoint();
		lb->label = label;
	}

	lb->cur = cur;
	lb->des = des;
	lb->delta = (des - cur) / numChange;
	lb->delay = delayTime;
	lb->type = type; //type: 0 - formatNumberSymbol - use in table / 1 - pointNumber
	if (lb->type == 0) {
		lb->label->setString(StringUtility::formatNumberSymbol(lb->cur));
	}
	else {
		lb->label->setString(StringUtility::pointNumber(lb->cur));
	}

	if (isNew)
		arLbPoints.push_back(lb);
}

void EffectMgr::runLabelPoint(ax::ui::TextBMFont* label, long long cur, long long des, float delayTime /*= 0*/, int numChange /*= 50*/, int type /*= 1*/)
{
	LabelPoint* lb = nullptr;
	bool isNew = true;
	for (int i = 0, size = arLbPoints.size(); i < size; i++) {
		if (arLbPoints[i]->labelBM == label) {
			lb = arLbPoints[i];
			isNew = false;
			break;
		}
	}

	if (isNew) {
		lb = new LabelPoint();
		lb->labelBM = label;
	}

	lb->cur = cur;
	lb->des = des;
	lb->delta = (des - cur) / numChange;
	lb->delay = delayTime;
	lb->type = type; //type: 0 - formatNumberSymbol - use in table / 1 - pointNumber
	if (lb->type == 0) {
		lb->labelBM->setString(StringUtility::formatNumberSymbol(lb->cur));
	}
	else {
		lb->labelBM->setString(StringUtility::pointNumber(lb->cur));
	}

	if (isNew)
		arLbPoints.push_back(lb);
}


void EffectMgr::updateEffect(float dt)
{
	for (int i = arLbPoints.size() - 1; i >= 0; i--) {
		LabelPoint* lb = arLbPoints[i];
		if (lb->delay > 0) {
			lb->delay -= dt;
			continue;
		}

		lb->cur += lb->delta;
		if (lb->type == 0) {
			if(lb->label)
				lb->label->setString(StringUtility::formatNumberSymbol(lb->cur));
			if(lb->labelBM)
				lb->labelBM->setString(StringUtility::formatNumberSymbol(lb->cur));
		}
		else {
			if (lb->label)
				lb->label->setString(StringUtility::pointNumber(lb->cur));
			if (lb->labelBM)
				lb->labelBM->setString(StringUtility::pointNumber(lb->cur));
		}

		if ((lb->delta >= 0 && lb->cur >= lb->des) || (lb->delta <= 0 && lb->cur <= lb->des)) {
			if (lb->type == 0) {
				if (lb->label)
					lb->label->setString(StringUtility::formatNumberSymbol(lb->des));
				if (lb->labelBM)
					lb->labelBM->setString(StringUtility::formatNumberSymbol(lb->des));
			}
			else {
				if (lb->label)
					lb->label->setString(StringUtility::pointNumber(lb->des));
				if (lb->labelBM)
					lb->labelBM->setString(StringUtility::pointNumber(lb->des));
			}
			//lb.setString(StringUtility.pointNumber(lb.des));
			arLbPoints.erase(arLbPoints.begin() + i);
		}
	}
}

float EffectMgr::flyCoinEffect(ax::Node* parent, long long gold, float ratio, Vec2 pStart, Vec2 pEnd) {
	if (!parent) return 0.0f;

	ratio = ratio || 100000; // default 100K gold
	float num = floor((float)gold / ratio);
	if (num == NULL) num = 15;
	if (num < 1) num = 1;
	float goldReturn = floor(gold / num);

	float timeMove = 1.5f;
	float dTime = 0.5f;
	float timeHide = 0.25f;
	float timeShow = 0.15f;

	Size winSize = Director::getInstance()->getVisibleSize();
	std::vector<float> rangeX = { -50, 50 };
	std::vector<float> rangeY = { -50, 50 };

	num = (num < 10) ? num : (10 + (num / 5));
	num = (num < 30) ? num : (30 + (num / 30));
	num = (num < 50) ? num : 50;


	for (auto i = 0; i < num; i++) {
		auto sp = CoinSlowEffect::create();
		sp->start();

		// random pos start
		auto rndX = AXRANDOM_0_1() * (rangeX[1] - rangeX[0]) + rangeX[0];
		auto rndY = AXRANDOM_0_1() * (rangeY[1] - rangeY[0]) + rangeY[0];

		auto rndRotate = -(AXRANDOM_0_1() * 360);

		auto pCX = AXRANDOM_0_1() *winSize.width;
		auto pCY = AXRANDOM_0_1() *winSize.height;

		auto posStart = Vec2(pStart.x + rndX, pStart.y + rndY);
		auto posCenter = Vec2(pCX, pCY);

		ccBezierConfig config;
		config.controlPoint_1 = posStart;
		config.controlPoint_1 = posCenter;
		config.endPosition = pEnd;
		auto actShow = EaseBackOut::create(ScaleTo::create(timeShow, 0.35f));
		auto actMove = EaseSineOut::create(BezierTo::create(timeMove, config));
		auto actHide = Spawn::create(EaseBackIn::create(ScaleTo::create(timeHide, 0)), FadeOut::create(timeHide), nullptr);
		sp->setPosition(posStart);
		sp->setRotation(rndRotate);
		parent->addChild(sp);
		sp->setScale(0);

		sp->runAction(Sequence::create(DelayTime::create(AXRANDOM_0_1() * dTime),
			actShow,
			Spawn::create(actMove,
				Sequence::create(
					DelayTime::create(1.5 * AXRANDOM_0_1()),
					CallFunc::create([sp]() {
						/*if (gamedata.sound) {
							auto rnd = (AXRANDOM_0_1() * 10) % 3 + 1;
							cc.audioEngine.playEffect(lobby_sounds["coin" + rnd], false);
						}*/
						}),
					nullptr),
				nullptr
							),
			CallFunc::create([sp, goldReturn]() {
				}),
							actHide
					, nullptr));
	}

	return (timeMove + timeHide + dTime + timeShow);
}

float EffectMgr::throwCoin(ax::Node* parent, int number, Vec2 start, Vec2 end, float delay, Vec2 realEnd) {
	if (!parent) return 0;
	start = parent->convertToNodeSpace(start);
	end = parent->convertToNodeSpace(end);
	number = std::min(25, std::max(number / 1000, 10));
	AXLOGD("NUMBER COIN %d", number);
	parent->runAction(Sequence::create(
		DelayTime::create(delay),
		CallFunc::create([number, start, end, realEnd, parent]() {
			std::vector< CoinSlowEffect*> listChip;
			for (auto i = 0; i < number; i++) {
				CoinSlowEffect* chip = CoinSlowEffect::create();
				listChip.push_back(chip);
				chip->setPosition(start);
				parent->addChild(chip);
			}
			for (auto i = 0; i < (int)listChip.size(); i++) {
				auto chip = listChip[i];
				chip->initState();
				auto chipPos = chip->getPosition();
				auto newPos = Vec2(end.x + 120 - AXRANDOM_0_1() * 240, end.y + 65 - AXRANDOM_0_1() * 130);
				auto rate = 1 - AXRANDOM_0_1() * 0.05 * listChip.size() / 10;
				auto distance = (newPos.x - chipPos.x) * (1 - rate);
				auto angle = AXRANDOM_0_1() * 360;
				auto deltaX = distance * cos(angle);
				auto deltaY = distance * sin(angle);
				auto pos1 = chipPos;
				auto pos3 = Vec2(chipPos.x + (newPos.x - chipPos.x) * rate, chipPos.y + (newPos.y - chipPos.y) * rate);
				auto ratePos = (2 / 3 - AXRANDOM_0_1() * 0.1);
				float timeMove = 0.4 - AXRANDOM_0_1() * 0.05;
				auto bezier = EaseIn::create(JumpTo::create(timeMove, pos3, 30 + AXRANDOM_0_1() * 30, 1), 1);
				auto jump = EaseOut::create(JumpBy::create(timeMove / 2, Vec2(deltaX, deltaY), AXRANDOM_0_1() * 10, 1 + std::round(AXRANDOM_0_1() * 3)), 1);
				auto rateRotate = std::round(1 - AXRANDOM_0_1()) * 360;
				auto rotate = EaseInOut::create(RotateBy::create(timeMove / 5, rateRotate), 3);
				auto scale = Repeat::create(Sequence::create(
					ScaleTo::create(timeMove / 20, CoinSlowEffect::SCALE_CHIP_RATE - 0.01 * AXRANDOM_0_1(), CoinSlowEffect::SCALE_CHIP_RATE),
					ScaleTo::create(timeMove / 20, CoinSlowEffect::SCALE_CHIP_RATE, CoinSlowEffect::SCALE_CHIP_RATE),
					ScaleTo::create(timeMove / 20, CoinSlowEffect::SCALE_CHIP_RATE, CoinSlowEffect::SCALE_CHIP_RATE - 0.01 * AXRANDOM_0_1()),
					ScaleTo::create(timeMove / 20, CoinSlowEffect::SCALE_CHIP_RATE, CoinSlowEffect::SCALE_CHIP_RATE),
					nullptr
				), std::round(AXRANDOM_0_1() * 4));
				if (realEnd.x == NULL || realEnd.y == NULL) {
					chip->runAction(Sequence::create(
						DelayTime::create(0),
						Spawn::create(
							Sequence::create(bezier, Spawn::create(jump, scale)),
							rotate,
							nullptr
						),
						DelayTime::create(0.2 + 0.5 * AXRANDOM_0_1()),
						Spawn::create(
							CallFunc::create([chip]() {
								chip->start();
								}),
							MoveBy::create(0.25, Vec2(0, 50)),
									FadeOut::create(0.25),
									nullptr
									),
						RemoveSelf::create(),
									nullptr
									)
					);
				}
				else {
					Vec2 realEndPos = parent->convertToNodeSpace(realEnd);
					auto pos4 = Vec2(realEndPos.x / 2 + end.x / 2 + 400 - AXRANDOM_0_1() * 800,
						(abs(realEndPos.x - end.x) > 300 ? 200 : 0) + realEndPos.y / 2 + end.y / 2);
					ccBezierConfig config;
					config.controlPoint_1 = end;
					config.controlPoint_1 = pos4;
					config.endPosition = realEndPos;
					auto move = EaseOut::create(BezierTo::create(timeMove * 1.5, config), 1);

					chip->runAction(Sequence::create(
						DelayTime::create(0.2 * AXRANDOM_0_1()),
						Spawn::create(
							Sequence::create(bezier, Spawn::create(jump, scale)),
							rotate,
							nullptr
						),
						DelayTime::create(1 - timeMove * 2 + 0.1 * i * AXRANDOM_0_1() * 0.2),
						Spawn::create(
							CallFunc::create([chip]() {
								chip->start();
								}),
							move,
									nullptr
									),
						Hide::create(),
									RemoveSelf::create(),
									nullptr
									));
				}
			}
			}),
		nullptr
				)
	);
	return 1.5 + delay;
}

float EffectMgr::flyCoinEffectAutoDestroy(ax::Node* parent, long long gold, float ratio, Vec2 pStart, Vec2 pEnd, const EffectListener& fGoldDone, bool checkTime) {
	if (!parent) return 0;

	ratio = ratio || 100000; // default 100K gold
	float num = floor(gold / ratio);
	if (num == NULL) num = 15;
	if (num < 1) num = 1;
	float goldReturn = floor(gold / num);

	float timeMove = 1.5;
	auto dTime = 0.5;
	auto timeHide = 0.25;
	auto timeShow = 0.15;

	if (checkTime) {
		return timeMove + timeHide + dTime + timeShow;
	}

	Size winSize = Director::getInstance()->getVisibleSize();
	std::vector<float> rangeX = { -50, 50 };
	std::vector<float> rangeY = { -50, 50 };

	num = (num < 10) ? num : (10 + (num / 5));
	num = (num < 30) ? num : (30 + (num / 30));
	num = (num < 50) ? num : 50;


	for (auto i = 0; i < num; i++) {
		auto sp = CoinSlowEffect::create();
		sp->start();

		// random pos start
		auto rndX = AXRANDOM_0_1() * (rangeX[1] - rangeX[0]) + rangeX[0];
		auto rndY = AXRANDOM_0_1() * (rangeY[1] - rangeY[0]) + rangeY[0];

		auto rndRotate = -(AXRANDOM_0_1() * 360);

		auto pCX = AXRANDOM_0_1() *winSize.width;
		auto pCY = AXRANDOM_0_1() *winSize.height;

		auto posStart = Vec2(pStart.x + rndX, pStart.y + rndY);
		auto posCenter = Vec2(pCX, pCY);

		auto actShow = EaseBackOut::create(ScaleTo::create(timeShow, 0.35f));
		ccBezierConfig config;
		config.controlPoint_1 = posStart;
		config.controlPoint_1 = posCenter;
		config.endPosition = pEnd;
		auto actMove = EaseSineOut::create(BezierTo::create(timeMove, config));
		auto actHide = Spawn::create(EaseBackIn::create(ScaleTo::create(timeHide, 0)), FadeOut::create(timeHide), nullptr);
		sp->setPosition(posStart);
		sp->setRotation(rndRotate);
		parent->addChild(sp);
		sp->setScale(0);

		sp->runAction(
			Sequence::create(
				DelayTime::create(AXRANDOM_0_1() * dTime),
				actShow,
				Spawn::create(actMove,
					Sequence::create(
						DelayTime::create(1.5 * AXRANDOM_0_1()),
						CallFunc::create([this]() {
							/*if (gamedata.sound) {
								auto rnd = (AXRANDOM_0_1() * 10) % 3 + 1;
								cc.audioEngine.playEffect(lobby_sounds["coin" + rnd], false);
							}*/
							}),
						nullptr),
					nullptr
								),
				CallFunc::create([fGoldDone]() {
								if (fGoldDone != nullptr) fGoldDone();
					}
				),
								actHide,
						nullptr));

		// mac dinh sau 2s disappear
		sp->runAction(
			Sequence::create(
				DelayTime::create(2),
				CallFunc::create([sp]() {
					sp->stopAllActions();
					sp->removeFromParent();
					}
				),
				nullptr));
	}

	return (timeMove + timeHide + dTime + timeShow);
}

float EffectMgr::flyCoinEffect2(ax::Node* parent, long long gold, Vec2 pStart, Vec2 pEnd, float timeDelay, bool checkTime) {
	if (!parent) return 0;

	auto num = 10 + (int)floor(AXRANDOM_0_1() * (gold / 100000));
	if (gold > 1000000) num = 15 + (int)floor(AXRANDOM_0_1() * (gold / 1000000));
	if (gold > 10000000) num = 20 + (int)floor(AXRANDOM_0_1() * (gold / 10000000));
	if (gold > 100000000) num = 25 + (int)floor(AXRANDOM_0_1() * (gold / 10000000));
	if (gold > 1000000000) num = 30 + (int)floor(AXRANDOM_0_1() * (gold / 10000000));

	auto timeMove = 1.5;
	auto dTime = 0.25;
	auto timeHide = 0.25;
	auto timeShow = 0.15;

	if (checkTime) {
		return (timeMove + timeHide + dTime + timeShow);
	}

	std::vector<float> rangeX = { -20, 20 };
	std::vector<float> rangeY = { -20, 20 };
	Size winSize = Director::getInstance()->getVisibleSize();
	for (auto i = 0; i < num; i++) {
		auto sp = CoinSlowEffect::create();
		sp->start();

		// random pos start
		auto rndX = AXRANDOM_0_1() * (rangeX[1] - rangeX[0]) + rangeX[0];
		auto rndY = AXRANDOM_0_1() * (rangeY[1] - rangeY[0]) + rangeY[0];

		auto rndRotate = -(AXRANDOM_0_1() * 360);

		auto pCX = AXRANDOM_0_1() * winSize.width;
		auto pCY = AXRANDOM_0_1() * winSize.height;

		auto posStart = Vec2(pStart.x + rndX, pStart.y + rndY);
		auto posCenter = Vec2(pCX, pCY);

		ccBezierConfig config;
		config.controlPoint_1 = pStart;
		config.controlPoint_2 = posCenter;
		config.endPosition = pEnd;
		auto actShow = EaseBackOut::create(ScaleTo::create(timeShow, 0.35f));
		auto actMove = EaseSineOut::create(BezierTo::create(timeMove, config));
		auto actHide = Spawn::create(EaseBackIn::create(ScaleTo::create(timeHide, 0)), FadeOut::create(timeHide), nullptr);
		sp->setPosition(posStart);
		sp->setRotation(rndRotate);
		parent->addChild(sp, 10);
		sp->setScale(0);

		sp->runAction(Sequence::create(
			DelayTime::create(AXRANDOM_0_1() * dTime),
			actShow,
			Spawn::create(
				actMove,
				Sequence::create(
					DelayTime::create(1.5 * AXRANDOM_0_1()),
					CallFunc::create([this]() {
						/*if (gamedata.sound) {
							if (AXRANDOM_0_1() < 0.7) return;
							;
							auto rnd = parseInt(AXRANDOM_0_1() * 10) % 3 + 1;
							cc.audioEngine.playEffect(lobby_sounds["coin" + rnd], false);
						}*/
						}),
					nullptr),
				nullptr
							),
			actHide,
							nullptr
							));
	}
	return (timeMove);
	// return (timeMove + timeHide + dTime * num - 0.5 + timeShow);
}

float EffectMgr::flyItemEffect(ax::Node* parent, std::string spriteName, long long itemCount, ax::Vec2 pStart, ax::Vec2 pEnd, float delay, bool isVpoint, bool checkTime) {
	if (parent == nullptr) return 0;

	int num = 2 + (int)floor(AXRANDOM_0_1() * 2);
	if (itemCount > 10000000) num = 3 + (int)floor(AXRANDOM_0_1() * 2);
	if (itemCount > 100000000) num = 4 + (int)floor(AXRANDOM_0_1() * 2);
	if (itemCount > 1000000000) num = 5 + (int)floor(AXRANDOM_0_1() * 2);
	if (!isVpoint) num = 1;

	float timeMove = 0.7f;
	float dTime = 0.25f;
	float timeHide = 0.25f;
	float timeShow = 0.15f;

	if (checkTime) {
		return (timeShow + timeMove);
	}

	// cc.log("flyCoinEffect2: ", gold, num, JSON.stringify(pStart));
	for (auto i = 0; i < num; i++) {
		auto sp = Sprite::create(spriteName);
		auto posCenter = Vec2((pStart.x + pEnd.x) / 2 + 100, (pStart.y + pEnd.y) / 2);

		auto actShow = EaseBackOut::create(ScaleTo::create(timeShow, 1));
		ccBezierConfig config;
		config.controlPoint_1 = pStart;
		config.controlPoint_2 = posCenter;
		config.endPosition = pEnd;
		auto actMove = EaseIn::create(BezierTo::create(timeMove, config), 2);
		auto actRotate = EaseIn::create(RotateBy::create(timeMove, AXRANDOM_0_1() * 180 + 180), 2);
		auto actHide = Spawn::create(EaseBackIn::create(ScaleTo::create(timeHide, 0)), FadeOut::create(timeHide), nullptr);
		sp->setPosition(pStart);
		sp->setVisible(false);
		parent->addChild(sp, 102);
		auto actHightlight = CallFunc::create([parent, i, isVpoint, pEnd]() {
			if (isVpoint && i == 0) {
				/*auto effect = DBCCFactory::getInstance()->buildArmatureNode("HighlightBig");
				if (effect != nullptr) {
					parent->addChild(effect, 102);
					effect->gotoAndPlay("1", 0, -1, 1);
					effect->setScale(0.3f);
					effect->setPosition(pEnd);
				}*/
			}
			});

		sp->runAction(
			Sequence::create(
				DelayTime::create(delay + dTime * i),
				Show::create(), actShow,
				Spawn::create(
					Sequence::create(Spawn::create(actMove, actRotate, nullptr), actHightlight, actHide, nullptr),
					Sequence::create(DelayTime::create(1.5 * AXRANDOM_0_1()), CallFunc::create([this]() {
						//if (gamedata.sound) {
						//	/*auto rnd = parseInt(AXRANDOM_0_1() * 10) % 3 + 1;
						//	cc.audioEngine.playEffect(lobby_sounds["coin" + rnd], false);*/
						//}
						}),
						nullptr
							), nullptr),
				nullptr));
	}
	return (timeShow + timeMove);
}

EffectMgr* EffectMgr::_instance = nullptr;

Confetti::Confetti() {
	initChild();
}

Confetti::~Confetti() {

}

bool Confetti::init()
{
	Node::init();
	return true;
}

void Confetti::initChild() {
	std::string file = "Board/Particles/confetti_" + std::to_string(std::rand() % 4) + ".png";
	AXLOGD("Confetti %s", file.c_str());
	spriteImg = Sprite::create(file);
	addChild(spriteImg);
	spriteImg->setRotation(std::rand() % 360);
	spriteImg->setOpacity((std::rand() % 50) + 205);
}

void Confetti::startEffect() {
	Vec2 p1 = getPosition();
	Vec2 p2 = Vec2(p1.x + std::rand() % 500 - std::rand() % 500, p1.y - std::rand() % 200 - 400);
	Vec2 p3 = Vec2(p1.x + (p2.x - p1.x) / 3, p1.y / 3 + p2.y / 3 + std::rand() % 300 + 750);
	int rTime = 3 + std::rand() % 3;

	Sequence* act = Sequence::create(
		DelayTime::create(rTime / 5),
		CallFunc::create([this]() {
			int r1 = std::rand() % 2;
			int r2 = std::rand() % 2;
			if (r1 == r2 && r1 == 0) {
				r1 = 1;
			}

			float rSpin = (float)(std::rand() / 100) + 0.05;
			spriteImg->runAction(Sequence::create(
				ScaleTo::create(rSpin, r1, r2),
				ScaleTo::create(rSpin, 1, 1),
				NULL
			));
			}),
		NULL
				);
	if (spriteImg) spriteImg->runAction(act);

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = p1;
	bezier2.controlPoint_2 = p3;
	bezier2.endPosition = p2;
	auto bezierTo1 = BezierTo::create(rTime, bezier2);
	auto bezierEaseTo1 = EaseElasticOut::create(bezierTo1);
	Sequence* act2 = Sequence::create(DelayTime::create(rTime / 5 * 3), RemoveSelf::create(), NULL);
	runAction(Spawn::create(bezierEaseTo1, act2, NULL));
}


CoinSlowEffect::CoinSlowEffect()
{
}

CoinSlowEffect::~CoinSlowEffect()
{
}

CoinSlowEffect * CoinSlowEffect::create()
{
	CoinSlowEffect* coin = new CoinSlowEffect();
	coin->initAnim();
	//coin->autorelease();
	return coin;
}

void CoinSlowEffect::initAnim() {
	//loadTexture("common/coinFake.png");
	initWithFile("common/coinFake.png");
	auto cache = SpriteFrameCache::getInstance();
	amoutLoop = 0;
	ax::Animation* animation = AnimationCache::getInstance()->getAnimation(CoinSlowEffect::NAME_ANIMATION_COIN);
	if (animation == nullptr) {
		animation = ax::Animation::create();
		std::vector<ax::SpriteFrame*> arr;
		SpriteFrame* aniFrame;
		for (auto i = 0; i < CoinSlowEffect::NUM_SPRITE_ANIMATION_COIN; i++) {
			aniFrame = cache->getSpriteFrameByName(CoinSlowEffect::NAME_ANIMATION_COIN + std::to_string(i) + ".png");
			arr.push_back(aniFrame);
			animation->addSpriteFrame(aniFrame);
		}
		aniFrame = cache->getSpriteFrameByName(CoinSlowEffect::NAME_ANIMATION_COIN + "0" + ".png");
		arr.push_back(aniFrame);
		animation->setDelayPerUnit(CoinSlowEffect::TIME_ANIMATION_COIN);
		//animation = ax::Animation::createWithSpriteFrames(arr, CoinSlowEffect::TIME_ANIMATION_COIN);
		AnimationCache::getInstance()->addAnimation(animation, CoinSlowEffect::NAME_ANIMATION_COIN);
	}
	anim = animation;
	setScale(CoinSlowEffect::SCALE_CHIP_RATE);
	setVisible(false);
}

void CoinSlowEffect::initState() {
	setVisible(true);
}

void CoinSlowEffect::initCoin(int type, int amoutLoopRun) {
	isCollided = false; //kiem tra da cham dat 1 lan chua
	opacity = 0;
	amoutLoop = amoutLoopRun;
	float valueRan;
	if (type == CoinSlowEffect::TYPE_FLOW) {
		speedX = 2 * AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_X - CoinSlowEffect::RATE_SPEED_X;
		//speedY = AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_Y + CoinSlowEffect::DEFAULT_SPEED_Y;
		auto def = AXRANDOM_0_1() * 800 + 800;
		speedY = sqrt(def * def - speedX * speedX);
		speedR = 2 * AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_R - CoinSlowEffect::RATE_SPEED_R;
		valueRan = AXRANDOM_0_1() * (CoinSlowEffect::MAX_SCALE - CoinSlowEffect::MIN_SCALE) + CoinSlowEffect::MIN_SCALE;
		this->setScale(valueRan, valueRan);
		setRotation(AXRANDOM_0_1() * 360);
		auto p = Vec2(((CoinEffectLayer*)getParent())->positionCoin.x + (AXRANDOM_0_1() - 0.5) * CoinSlowEffect::RATE_Position_X,
			((CoinEffectLayer*)getParent())->positionCoin.y + (AXRANDOM_0_1() - 0.5) * CoinSlowEffect::RATE_Position_Y);
		this->setPosition(p);
	}
	else if (type == CoinSlowEffect::TYPE_RAIN) {
		speedX = 0;
		speedY = AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_X;
		speedR = 2 * AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_R - CoinSlowEffect::RATE_SPEED_R;
		valueRan = AXRANDOM_0_1() * (CoinSlowEffect::MAX_SCALE - CoinSlowEffect::MIN_SCALE) + CoinSlowEffect::MIN_SCALE;
		this->setScale(valueRan, valueRan);
		setRotation(AXRANDOM_0_1() * 360);
		auto parent = getParent();
		this->setPosition(Vec2(AXRANDOM_0_1() * parent->getContentSize().width, parent->getContentSize().height + getContentSize().height + AXRANDOM_0_1() * CoinSlowEffect::RATE_Position_Y));
	}
	this->setVisible(false);
}

void CoinSlowEffect::start() {
	setVisible(true);
	Animate* ani = nullptr;
	if (anim != nullptr) {
		ani = Animate::create(anim);
	}
	//ani.setSpeed(AXRANDOM_0_1() * 0.5 + 0.5);
	if (ani != nullptr) {
		runAction(RepeatForever::create(ani));
	}
}

void CoinSlowEffect::stop() {
	setVisible(false);
	stopAllActions();
}

void CoinSlowEffect::repeat() {
	if (amoutLoop <= 0) {
		stop();
	}
	else {
		amoutLoop -= 1;
		isCollided = false;
		speedX = 0;
		speedY = AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_X;
		speedR = 2 * AXRANDOM_0_1() * CoinSlowEffect::RATE_SPEED_R - CoinSlowEffect::RATE_SPEED_R;
		valueRan = AXRANDOM_0_1() * (CoinSlowEffect::MAX_SCALE - CoinSlowEffect::MIN_SCALE) + CoinSlowEffect::MIN_SCALE;
		this->setScale(valueRan, valueRan);
		setRotation(AXRANDOM_0_1() * 360);
		auto parent = getParent();
		this->setPosition(Vec2(AXRANDOM_0_1() * parent->getContentSize().width, parent->getContentSize().height + getContentSize().height + AXRANDOM_0_1() * CoinSlowEffect::RATE_Position_Y));
	}
}

void CoinSlowEffect::updateCoin(float dt) {
	auto opa = opacity;
	opa += 1500 * dt;
	if (opa > 255) opacity = 255;
	else opacity = opa;
	setPositionX(getPositionX() + speedX * dt);
	setPositionY(getPositionY() + speedY * dt);
	speedY -= CoinSlowEffect::GRAVITY * dt;
	setRotation(getRotation() + speedR);
	//cham dat thi cho nhay len 1 lan roi roi tiep
	if (getPositionY() < getContentSize().height / 2 && !isCollided) {
		isCollided = true;
		speedY = -speedY * (AXRANDOM_0_1() * CoinSlowEffect::RATE_JUMP_BACK);
		speedX = 0;
	}
	else if (getPositionY() + (getContentSize().height * getScale()) < 0 && isCollided) {
		repeat();
	}
}

const float CoinSlowEffect::SCALE_CHIP_RATE = 0.35f;
const int CoinSlowEffect::NUM_SPRITE_ANIMATION_COIN = 5;
const std::string CoinSlowEffect::NAME_ANIMATION_COIN = "gold";
const float CoinSlowEffect::TIME_ANIMATION_COIN = 0.3f;
const float CoinSlowEffect::TYPE_FLOW = 0;
const float CoinSlowEffect::TYPE_RAIN = 0;

const float CoinSlowEffect::RATE_SPEED_Y = 600;
const float CoinSlowEffect::DEFAULT_SPEED_Y = 850;
const float CoinSlowEffect::RATE_SPEED_X = 350;
const float CoinSlowEffect::RATE_SPEED_R = 10;
const float CoinSlowEffect::RATE_Position_X = 100;
const float CoinSlowEffect::RATE_Position_Y = 1000;
const float CoinSlowEffect::MIN_SCALE = 0.32f;
const float CoinSlowEffect::MAX_SCALE = 0.42f;
const float CoinSlowEffect::RATE_JUMP_BACK = 0.5f;
const float CoinSlowEffect::GRAVITY = 2300;
const float CoinSlowEffect::POSI = 90;
const float CoinSlowEffect::NUM_COIN_EACH_TIME = 100;
const float CoinSlowEffect::NUM_COIN_RATE_RAIN = 100;
const float CoinSlowEffect::TIME_OUT_COIN = 0.05f;
const float CoinSlowEffect::DELAY_PLAY_SOUND = 0.3f;


CoinEffectLayer::CoinEffectLayer()
{
}

CoinEffectLayer::~CoinEffectLayer()
{
}

void CoinEffectLayer::initLayer() {
	numEffect = 0;
	numCoinNow = 0;
	//callBack = null;
	timeCount = 0;
	positionCoin = Vec2(0, 0);
	isRun = false;
	typeEffect = 0;
	isAutoRemove = false;
}


void CoinEffectLayer::setPositionCoin(Vec2 p) {
	positionCoin = p;
}


void CoinEffectLayer::setAutoRemove(bool b) {
	isAutoRemove = b;
}

void CoinEffectLayer::update(float dt) {
	if (listCoin.size() == 0) return;
	CoinSlowEffect* coin;
	auto isFinish = false;
	for (auto i = numCoinNow; i < numEffect; i++) {
		coin = listCoin[i];
		if (coin->isVisible()) {
			coin->updateCoin(dt);
			isFinish = true;
		}
	}
	if (numCoinNow > 0) {
		timeCount += dt;
		if (timeCount >= CoinSlowEffect::TIME_OUT_COIN) {
			auto num = 10;
			if (typeEffect == CoinSlowEffect::TYPE_FLOW) {
				num = CoinSlowEffect::NUM_COIN_EACH_TIME * timeCount;
				timeCount = 0;
			}
			else if (typeEffect == CoinSlowEffect::TYPE_RAIN) {
				num = CoinSlowEffect::NUM_COIN_RATE_RAIN * 0.05;
				timeCount = CoinSlowEffect::TIME_OUT_COIN - 0.05f;
			}
			for (int i = 0; i < num; i++) {
				coin = listCoin[numCoinNow--];
				coin->start();
				if (numCoinNow == 0) break;
			}
		}
	}
	else {
		if (!isFinish) {
			unscheduleUpdate();
			/*if (callBack) {
				callBack.call();
			}*/
			isRun = false;
			if (isAutoRemove) {
				removeEffect();
			}
		}
	}
}

void CoinEffectLayer::startEffect(int numEffectCoin, int type, int amoutRain, bool isSound) {
	if (isRun) stopEffect();
	CoinSlowEffect* coin;
	typeEffect = type;
	if (numEffectCoin == NULL) numEffectCoin = 100;
	numEffect = numEffectCoin;
	if (numEffect > (int)listCoin.size()) {
		int i = 0;
		int len = numEffect - listCoin.size();
		while (i < len) {
			coin = getCoinItem();
			listCoin.push_back(coin);
			addChild(coin);
			i++;
		}
	}
	for (auto i = 0; i < numEffect; i++) {
		coin = listCoin[i];
		coin->stop();
		coin->initCoin(type, amoutRain);
	}
	numCoinNow = numEffect - 1;
	timeCount = 0;
	scheduleUpdate();
	setVisible(true);
	isRun = true;
	if (!isSound) {
		return;
	}
	runAction(Sequence::create(DelayTime::create(CoinSlowEffect::DELAY_PLAY_SOUND), CallFunc::create([]() {
		/*if (gamedata.sound) {
			cc.audioEngine.playEffect(lobby_sounds.coinFall, false);
		}*/
		}), nullptr));
}

void CoinEffectLayer::stopEffect() {
	for (auto i = 0; i < (int)listCoin.size(); i++) {
		listCoin[i]->setVisible(false);
	}
}

void CoinEffectLayer::removeEffect() {
	stopEffect();
	listCoin.clear();
	removeFromParent();
}

CoinSlowEffect* CoinEffectLayer::getCoinItem() {
	CoinSlowEffect* coin = CoinSlowEffect::create();
	//coin->initAnim();
	return coin;
}
