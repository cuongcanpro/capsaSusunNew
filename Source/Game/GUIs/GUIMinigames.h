#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
using namespace std;
using namespace ax::extension;
using namespace ax::ui;

class GUIMinigames : public BaseGUI, public ScrollViewDelegate
{
public:
	GUIMinigames(void);
	~GUIMinigames(void);
	void initGUI();
	int countScroll;
    Scale9Sprite* bgGame;
    BaseButton* btnUpdate;
	BaseButton* btnBack, *btnSound, *btnBubble, *btnBlock, *btnBomb, *btnPop, *btnDrop, *btnTwenty, *btnChess, *btnLine;
    vector<Button*> arrayButtonGame;
    ImageView* borderAvatar, *avatar;
    Text *lbWin, *lbLevel, *lbGold, *lbRank, *lbName;
    Scale9Sprite* bgInfo;
    string arrayNameGame[15];
	ax::extension::ScrollView * scrollView;
    void initInfoUser();
    void onEnter();
	void onButtonRelease(int buttonID, Touch* touch);
    void callBackSplash();
	void onBackKey();
	void sendData(int mode);
	void showGUI(Node* parent /* = NULL */, bool hasFog /* = true */);

    void playLine();
	void playBlock();
	void playEgg();
	void playTwenty();
	void playBubble();
	void playBomb();
    void playCard();
	void updateButton();
    void onTouchGame(ax::Object* pSender, ax::ui::Widget::TouchEventType type);
    virtual void scrollViewDidScroll(ax::extension::ScrollView* view) override;
    virtual void scrollViewDidZoom(ax::extension::ScrollView* view) override;
    bool onTouchBegan( Touch *pTouch, Event *pEvent );

public:
    static std::string className;
};

