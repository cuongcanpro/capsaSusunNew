#ifndef BinhBoardScene_h__
#define BinhBoardScene_h__
#include "core/gui/BaseLayer.h"
#include "BinhPlayerUI.h"
#include "BinhCardImage.h"
#include "../data/GameConstant.h"
#include "gameTienlen/ui/ClockCountDown.h"
#include "EffekseerForCocos2d-x.h"
using namespace efk;

class BinhBoardScene:
public BaseLayer{
public:
	enum AutoState {
		AUTO_START_STATE,
		ARRANGE_CARD_STATE,
		START_COMPARE_STATE,
		MAUBINH_STATE,
		BI_SAP_BAI_STATE,
		BAT_SAP_BAI_STATE,
		BINHLUNG_STATE,
		INDEX_CHI_0_STATE,
		INDEX_CHI_1_STATE,
		COMPARE_CHI_1_STATE,
		INDEX_CHI_2_STATE,
		COMPARE_CHI_2_STATE,
		INDEX_CHI_3_STATE,
		COMPARE_CHI_3_STATE,
		INDEX_CHI_4_STATE,
		SUMMARY_STATE,
		END_GAME_STATE,
		WAIT_NEXT_GAME_STATE,
		REWARD_FAIL_STATE,
		REWARD_SUCCESS_STATE
	};

	CREATE_FUNC(BinhBoardScene);
	BinhBoardScene();
	~BinhBoardScene();
	bool init();
	
public:
	void initGUI();
	void onEnterFinish();
	void onButtonRelease(ax::ui::Button* button, int id);
	void backKeyPress();
	
public:
	// name
	static const std::string className;
	BinhPlayerUI *arrayPlayer[NUM_PLAYER];
private:
	ImageView *bgBoard, *imgChi, *imgFinish;
	Text *labelRoom, *labelBet, *labelRate;
	Button *btnSound, *btnQuit, *btnStart,*btnArrange, *btnHelp;
	ImageView* btnQuitSelect;
	
	//SelfUI *myPlayer;
	Sprite *dotWait[3];

	Node *pJackpot, *pEffectAll;
	ClockGame* clockGame;
	Node* bgDark;
	vector <BinhCardImage*> arrayCardEffect;
	
	vector <char> arrayAutoCard[NUM_PLAYER];
	vector<double> arrayMoneySummary;

private:
	float timeWaitOther;
	char typeGroup;
public:
	void initPlayer();
	AutoState autoState;
	int idTheme;
public:
	void onEnter();
	// function in Game
	void newGame();
	void joinRoomSuccess();
	void setViewInfo(char gameState, int gameTime, vector<bool> isPlayings, vector<bool> playerStates);
	void updateStateReady(vector<char> playerStates);
	void updateRoomOwner();
	void updateWaitOther();
	void newUserJoinRoom(char chair, BinhPlayerInfo* info);
	void userLeave(char chair);
	void autoStart(int time, bool isAutoStart);
	void notifyStart();
	void dealStartGame();
	void callbackDealCard(Node* sender, int num, int indexPlayer);
	void callbackDealCard1(Node* sender, int num, int indexPlayer);
	void callbackDealMyCard(Node* sender, int num, Vec2 pos);
	void callbackEndDealCard(bool effectGUI = true);
	void showGUIArrange(bool effectGUI);
	void ready(char chair);
	void unReady(char chair);
	void endCard(char chair);
	void updateCardEnd(char chair);
	void chiIndex(char chi);
	void callbackChiIndex();
	void compareChi(char chi, vector<double> arrayMoney, vector<int> arrayResult);
	void sapBai(vector<double> arrayMoney);
	void soBai(bool isMauBinh, vector<double> arrayMoney);
	void callbackSoBai(Node* pSender);
	void sapLang(char chair, vector<double> arrayMoney);
	void binhAt(vector<double> arrayMoney);
	void summary(vector<double> arrayMoney);
	void jackpot(double gold);
	
	void callbackJackpot(Node* sender);
	void updateJackpot();
	void regQuit(bool status);
	void kickFromRoom(char chair, char reason);
	void chatEmoticon(char chair, char id, char type);
	void chatMessage(char chair, string message);
	void updateUserMoney(char chair);
	void update(float delta);
	void updateMyCard(vector<int> arrayId, vector<Vec2> arrayPos, vector<float> arraySize);
	void callbackUpdateMyCard(Node* pSender, int index);
public:
	// utils function
	BinhCardImage* getCardEffect();

	// call from other modules 
	Node* getNodeEffect(char chair);
	void setInfoCountDown();
	void onReceiveChatEmotion(int index, int fromUserId);
	void onReceiveChatMessage(std::string msg, char chair);

	void updateMyInfo();
	ui::Text *getMyGoldLabel();
	Node *getMyAvatar();

	Vec2 getPosFromPlayer(int id);
	std::vector<Vec2> getPlayerPosExcepted(int id);
	
	ax::Point getPositionAvatar(char chairInServer);
	void updateAvatarFrame(char chairInServer);
	void loadTheme();
	void loadBtnSound();
	void updateMyAvatar();

	efk::EffectManager* manager;
	efk::EffectEmitter* emitter;
    void loadLanguage();
};


#endif // BinhBoardScene_h__
