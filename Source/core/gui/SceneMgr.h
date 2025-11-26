#ifndef SceneMgr_h__
#define SceneMgr_h__

#include "BaseScene.h"
#include "Dialog.h"
#include "LoadingGui.h"
//#include "renderer/DBCCArmatureNode.h"
//#include "renderer/DBCCFactory.h"

#define sceneMgr SceneMgr::getInstance()

class SceneMgr {
public:
	SceneMgr();
	~SceneMgr();
	static SceneMgr* getInstance();
public:
	BaseScene* getRunningScene();
	ax::Node* getMainLayer();
	template <class T>
	bool checkMainLayer()
	{
		ax::Node* node = getMainLayer();
		return (dynamic_cast<T*>(node) != nullptr);
	}
	LoadingGui* addLoading(std::string text = "", bool fog = true);
	void clearLoading();
	void addWaiting();
	void clearWaiting();
	void updateCurrentGUI();
	void addQueueScene(std::string layer);
	std::string getQueueScene(bool direct = false);
	BaseLayer* openScene(std::string layerName, std::string callback = "", bool direct = false, bool cache = true);
	BaseLayer* openGUI(std::string slayer, int zoder = 1, int tag = 1, bool isCache = true);
	std::string getClassGUI(std::string cName = "");
	void preloadScene(std::string layer);
	ax::Node* getGUI(int tag);
	ax::Node* getGUIByClassName(string className);
	
	void initialLayer();
	void addLayerGUI(Node *x);
	void addLayerSystem(Node *x);

	void updateScene(float dt);
	bool checkBackAvailable(std::vector<std::string> ignores = {});
	void showAddGDialog(std::string message, const DialogListener& callback);
	void showOkCancelDialog(std::string message, const DialogListener& callback);
	void showOkDialogWithAction(std::string message, const DialogListener& callback);
	void showOKDialog(std::string message);
	void showChangeGoldDialog(std::string message, const DialogListener& callback);

	void restartCacheGui();

public:
	static SceneMgr* _instance;

	ax::Color3B ccWhite;
	ax::Color3B ccYellow;
	ax::Color3B ccGreen;
	ax::Color3B ccBlue;

	std::string curGui;
	std::map<std::string, BaseLayer*> arGuis;
	std::map<std::string, BaseLayer*> arPopups;

	ax::Node* layerGUI;
	ax::Node* layerSystem;
	std::vector<std::string> backScenes;
	std::vector<std::string> ignoreGuis;

	int numDialog = 0;
public:
	static const int FONT_SIZE_DEFAULT;
};


class ToastFloat :
	public ax::Node {
public:
	CREATE_FUNC(ToastFloat);
	ToastFloat();
	~ToastFloat();
public:
	bool init();
	void onEnter();
	void finishEffect();
	void setToast(std::string txt, float time = 1.0f);
	void clearToast();
	void update(float dt);
	static void makeToast(float time, std::string text);

public:
	float timeDelay;
	bool isRunningDelay;
	ax::ui::Text* lb;
	ax::ui::Scale9Sprite* bg;
	float _scale;

	static const float SHORT;
	static const float LONG;
	static const float MEDIUM;

	static const float POSITION_Y;
	static const float DELTA_WIDTH;
	static const int PAD_SIZE;
};

#define effectMgr EffectMgr::getInstance()
typedef std::function<void()> EffectListener;

class EffectMgr {
public:
	struct LabelPoint {
		ax::ui::Text* label;
		ax::ui::TextBMFont* labelBM;
		long long cur;
		long long des;
		int delta;
		int type;
		float delay;
	};
public:
	EffectMgr();
	~EffectMgr();
	static EffectMgr* getInstance();
public:
	void runLabelPoint(ax::ui::Text* label, long long cur, long long des, float delayTime = 0, int numChange = 50, int type = 1);
	void runLabelPoint(ax::ui::TextBMFont* label, long long cur, long long des, float delayTime = 0, int numChange = 50, int type = 1);
	void updateEffect(float dt);
	float flyCoinEffect(ax::Node * parent, long long gold, float ratio, ax::Vec2 pStart, ax::Vec2 pEnd);

	float throwCoin(ax::Node * parent, int number, ax::Vec2 start, ax::Vec2 end, float delay, ax::Vec2 realEnd = ax::Vec2(NULL, NULL));

	float flyCoinEffectAutoDestroy(ax::Node * parent, long long gold, float ratio, ax::Vec2 pStart, ax::Vec2 pEnd, const EffectListener & fGoldDone, bool checkTime = false);

	float flyCoinEffect2(ax::Node * parent, long long gold, Vec2 pStart, Vec2 pEnd, float timeDelay, bool checkTime = false);

	float flyItemEffect(ax::Node * parent, std::string spriteName, long long itemCount, ax::Vec2 pStart, ax::Vec2 pEnd, float delay, bool isVpoint, bool checkTime = false);

public:
	std::vector<LabelPoint*> arLbPoints;
	static EffectMgr* _instance;
};

class Confetti : public ax::Node {
public:
	CREATE_FUNC(Confetti);
	Confetti();
	~Confetti();

	ax::Sprite* spriteImg;
public:
	bool init();
	void initChild();
	void startEffect();
};

class CoinSlowEffect :
	public ax::Sprite {
public:
	CoinSlowEffect();
	~CoinSlowEffect();
	static CoinSlowEffect* create();
	void initAnim();

	void initState();

	void initCoin(int type, int amoutLoop);

	void start();

	void stop();

	void repeat();

	void updateCoin(float dt);

public:
	int amoutLoop;
	ax::Animation* anim;
	bool isCollided;
	float opacity;
	float speedX;
	float speedY;
	float speedR;
	float valueRan;
	float rotation;

public:

	static const float SCALE_CHIP_RATE;
	static const int NUM_SPRITE_ANIMATION_COIN;
	static const std::string NAME_ANIMATION_COIN;
	static const float TIME_ANIMATION_COIN;
	static const float TYPE_FLOW;
	static const float TYPE_RAIN;

	static const float RATE_SPEED_Y;
	static const float DEFAULT_SPEED_Y;
	static const float RATE_SPEED_X;
	static const float RATE_SPEED_R;
	static const float RATE_Position_X;
	static const float RATE_Position_Y;
	static const float MIN_SCALE;
	static const float MAX_SCALE;
	static const float RATE_JUMP_BACK;
    static const float GRAVITY;
	static const float POSI;
	static const float NUM_COIN_EACH_TIME;
	static const float NUM_COIN_RATE_RAIN;
	static const float TIME_OUT_COIN;
	static const float DELAY_PLAY_SOUND;
};

class CoinEffectLayer : public ax::Layer {
public:
	CoinEffectLayer();
	~CoinEffectLayer();
	CREATE_FUNC(CoinEffectLayer);

public:
	std::vector<CoinSlowEffect*> listCoin;
	int numEffect;
	int numCoinNow;
	float timeCount;
	ax::Vec2 positionCoin;
	bool isRun;
	int typeEffect;
	bool isAutoRemove = false;
	void initLayer();
	void setPositionCoin(ax::Vec2 p);
	void setAutoRemove(bool b);
	void update(float dt);
	void startEffect(int numEffect, int type, int amoutRain = 0, bool isSound = false);
	void stopEffect();
	void removeEffect();
	CoinSlowEffect * getCoinItem();
};


#endif // SceneMgr_h__
