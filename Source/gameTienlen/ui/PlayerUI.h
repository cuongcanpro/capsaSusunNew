#ifndef PlayerUI_h__
#define PlayerUI_h__
#include "core/gui/BaseLayer.h"
#include "MoneyGroup.h"
#include "CancelTurn.h"
#include "Viewing.h"
#include "../logic/PlayerInfo.h"
#include "core/utils/AvatarUI.h"
#include "ResultGroup.h"
#include "ClockCountDown.h"

using namespace ax::ui;
using namespace ax::extension;
using namespace ax;

class PlayerUI : public BaseLayer
{
public:
	PlayerUI();
	~PlayerUI();

	virtual bool init();
	void initGUI();
	void initCommon();

	void setInfo(PlayerInfo* pInfo);
	void setRoomOwner(bool show);
	virtual void newGame();
	virtual void setViewing();
	virtual void updateDealCard(int num);
	virtual void endDealCard();
	virtual void changeTurn(int time);
	void stopTurn();
	virtual void showCancel(bool show);
	virtual void updateCard();
	virtual void getRank(char rank, bool isCong);
	void effectResult(char rank);
	void callbackEffectResult(Node* sender);
	virtual void endCard();
	virtual void showCard();
	void effectGold(double gold);
	void chatEmoticon(char id, char emoId);
	void showEffectVip();
	virtual void updateMoney();
	void updateAvatarFrame(long long uId);
        void effectRenew();

    public:
	virtual Size getCardSize();
	virtual Vec2 getCardPos(int index);
	virtual Vec2 getCardPosById(int id);
	virtual void setDarkCard(bool isDark);
	virtual Vec2 getPositionAvatar();
	
public:
	Node* bg;
	ax::ui::Button* btnAvatar;
	Text *labelName, *labelGold;
	ImageView *arrow;
	MoneyGroup *moneyGroup;
	CancelTurn *effectCancel;
	Node* pEffect;
	ImageView* avatar;
	ImageView* borderAvatar;
	Node* timeCircle;
	ResultGroup* resultGroup;
	ClockGame* turnClock;
	void onButtonRelease(Button* button, int id);
protected:
	int chairIndex;
};
#endif // PlayerUI_h__
