#ifndef BinhPlayerUI_h__
#define BinhPlayerUI_h__
#include "core/gui/BaseLayer.h"
#include "../logic/BinhPlayerInfo.h"
#include "core/utils/AvatarUI.h"
#include "../data/GameConstant.h"
#include "BinhCardImage.h"
#include "spine/SkeletonAnimation.h"
#include "BinhCardButton.h"
#include <DragonBones/DragonBonesHeaders.h>
#include <DragonBones/CCArmatureDisplay.h>
#include "EffekseerForCocos2d-x.h"
using namespace ax::ui;
using namespace ax::extension;
using namespace ax;
using namespace dragonBones;

#define USER_LEFT 1
#define USER_RIGHT 3
#define USER_TOP 2
class BinhCardButton;
class BinhPlayerUI : public Object
{
public:
	BinhPlayerUI();
	~BinhPlayerUI();
	void initGUI();
	void initCommon();
	virtual void onEnterFinish();
	void setInfo(BinhPlayerInfo* pInfo);
	void setRoomOwner(bool show);
	virtual void initGroupCard();
	void initOneGroupCard(Node* panel, float scale, BinhCardButton* arrayCard []);
	virtual void newGame();
	virtual void setViewing();
	virtual void updateDealCard(int num);
	virtual void endDealCard();
	virtual void updateCard();
	virtual void ready();
	virtual void unReady();
	virtual void endCard();
	void updateCardEnd();
	virtual void chiIndex(char chi);
	void startCompare();
	virtual void compareChi(char chi, double money, int result);
	virtual void sapBai(double money, SapBaiType sapTye);
	void soBaiMauBinh(double money);
	void soBaiBinhLung(double money);
	virtual void sapLang(char chair, double money);
	void binhAt(double money);
	virtual void summary(double money);
	void effectGold(double gold, bool isWin = true);
	void chatEmoticon(char id, char emoId);
	void showEffectVip();
	virtual void updateMoney();
    void updateAvatarFrame();
    void effectRenew();

    public:
	virtual Size getCardSize();
	virtual Vec2 getCardPos(int index);
	virtual Vec2 getCardPos2(int index);
	float getCardRotation(int index);
	virtual Vec2 getCardPosById(int id);
	virtual void setDarkCard(bool isDark);
	int getIndexById(int id);
	void setDarkAll(bool isDark);
	virtual Vec2 getPositionAvatar();
	void showArrayCard1(bool show);
	void showArrayCard2(bool show);
	void setVisible(bool visible);
	bool isVisible();
	void setDarkCard1(bool isDark);
	void setDarkCard2(bool isDark);
	void effectChi(char chi, string resource);
	void updateCardOneChi(char chi);
	virtual void update(float delta);
	void setNormalZOrder();
	void showParticle();
	void loadTheme(int idTheme);
	void showGun(float rotation);
public:
	Node* bgAvatar;
	ImageView* bg;
	Node* layout;
	Node* avatarUI;
	ax::ui::Button* btnAvatar;
	Text *labelName, *labelGold;
	ImageView *arrow;
	ImageView* imgState;
	ImageView* imgSap;
	//MoneyGroup *moneyGroup;
	//TextBMFont * moneyGroup;
	Text* moneyGroup;
	//Viewing *effectViewing;
	Node* pEffect;
	Sprite* uiAvatar;
	Sprite* imgResult;
	Sprite* imgEffectChi;
	BinhCardButton* arrayCard1[NUM_CARD]; // mang card nho trong luc xep bai
	BinhCardButton* arrayCard2[NUM_CARD]; // mang card nho trong luc xep bai
	float countViewing;
	ImageView* borderAvatar;
	void onButtonRelease(Button* button, int id);
    efk::EffectManager* manager;
    efk::EffectEmitter* effBomb;
    spine::SkeletonAnimation* effectSpecialChi;
    
protected:
	int chairIndex;
};
#endif // BinhPlayerUI_h__
