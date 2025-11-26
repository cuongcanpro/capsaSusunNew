#ifndef ChooseGameScene_h__
#define ChooseGameScene_h__
#include "core/gui/BaseLayer.h"
class ChooseGameScene:
	public BaseLayer
{
public:
	CREATE_FUNC(ChooseGameScene);
	ChooseGameScene();
	~ChooseGameScene();
	bool init();
public:
	void initGUI();
	void onEnterFinish();

public:
	static const std::string className;
	void backKeyPress();
	void callbackLoading();
	vector<Sprite*> *dots;
	Sprite *light;
    Button* btnTienLen, *btnBinh, *btnTala, *btnBack;
	int curDot = 0;
	Vec2 curPos;

};
#endif // ChooseGameScene_h__
