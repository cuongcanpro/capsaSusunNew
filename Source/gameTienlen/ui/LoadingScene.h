#ifndef LoadingScene_h__
#define LoadingScene_h__
#include "core/gui/BaseLayer.h"
#include "EffekseerForCocos2d-x.h"
class LoadingScene:
	public BaseLayer
{
public:
	CREATE_FUNC(LoadingScene);
	LoadingScene();
	~LoadingScene();
	bool init();
public:
	void initGUI();
	void onEnterFinish();

public:
	static const std::string className;

	void callbackLoading();
	vector<Sprite*> *dots;
	Sprite *light;
	int curDot = 0;
	Vec2 curPos;
	efk::EffectManager* manager;
	efk::EffectEmitter* emitter;
	void update(float delta);
};
#endif // LoadingScene_h__
