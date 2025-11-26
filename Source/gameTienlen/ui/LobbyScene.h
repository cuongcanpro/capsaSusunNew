#ifndef LobbyScene_h__
#define LobbyScene_h__
#include "core/gui/BaseLayer.h"
using namespace ax::extension;

class LobbyScene:
	public BaseLayer
{
public:
	CREATE_FUNC(LobbyScene);
	LobbyScene();
	~LobbyScene();
	bool init();
public:
	void initGUI();
	void onEnterFinish();

public:
	static const std::string className;

	vector<Sprite*> *dots;
	Sprite *light;
	int curDot = 0;
	Vec2 curPos;
	Node* pRight, *pLeft;
	Button* btnBack;
	TableView* listTop;
	int currentTop;
	ImageView* borderAvatar;
	Text* lbWin, *lbLevel, *lbGold, *lbRank, *lbName, *lbEmpty;
    Button *btnSolo, *btnMulti, *btnLevel, *btnTop;
    Node* bgInfo;
	
	ax::ui::Text* lbVersion;
	ax::ui::Text* lbUpdate;
	void callbackLoading();
	void backKeyPress();
	void onButtonRelease(ax::ui::Button* button, int id);

	static const int BTN_SOLO;
	static const int BTN_MULTI;
	static const int BTN_TOP_WIN;
	static const int BTN_TOP_GOLD;
	static const int BTN_TOP;
	static const int BTN_EDIT;
	static const int BTN_LEVEL;
    static const int BTN_BACK;
};
#endif // LobbyScene_h__
