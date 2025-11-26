#ifndef BinhLobbyScene_h__
#define BinhLobbyScene_h__
#include "core/gui/BaseLayer.h"
using namespace ax::extension;
class BinhLobbyScene :
	public BaseLayer
{
public:
	CREATE_FUNC(BinhLobbyScene);
	BinhLobbyScene();
	~BinhLobbyScene();
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
	Button* btnTopWin, *btnTopGold, *btnTop, *btnEdit, *btnMulti, *btnBack;
        Node* bgInfo;
	TableView* listTop;
	int currentTop;
	ImageView* borderAvatar;
	Text* lbWin, *lbLevel, *lbGold, *lbRank, *lbName;

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
	static const int BTN_BACK;
};
#endif // BinhLobbyScene_h__
