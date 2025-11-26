#ifndef TalaInGameMgr_h__
#define TalaInGameMgr_h__

#include "core/BaseMgr.h"

#define talaInGameMgr TalaInGameMgr::getInstance()

class TalaInGameMgr : public BaseMgr {
private:

public:
	TalaInGameMgr();
	~TalaInGameMgr();

	static TalaInGameMgr* getInstance();
public:
	void init();
	bool isInBoard();
	int getChairFromId(int id);
	void openBoardScene(bool isSolo);
public:
	static TalaInGameMgr* _instance;
public:
	void sendViewInfo();
	void sendStart();
	void sendAuthenConnect();
	void sendQuit();
	void sendCheatCard(vector <int> arrayCard);

	void sendStartGame();
	void sendQuitGame();
	void sendThrowCard(char id);
	void sendGetCard(char chair);
	void sendShowPhom(char chair, vector<char> cards);
	void sendSendCard(char senderChair, char senderCard, char targetChair, char targetCard);
	void sendViewGame();
	void sendConnectRoom();
	void sendCheatCard(vector<char> cards);
	void sendAddBot();
	void sendRemoveBot(char chair);
public:
	static string SOUND_ENTER_ROOM;
	static string SOUND_LEAVE_ROOM;
	static string SOUND_REG_QUIT;
	static string SOUND_CANCEL_QUIT;
	static string SOUND_START_MATCH;
	static string SOUND_TIMER;
	static string SOUND_DRAW_CARD;
	static string SOUND_EAT_CARD;
	static string SOUND_THROW_CARD;
	static string SOUND_ARRANGE_CARD;
	static string SOUND_SELECT_CARD;
	static string SOUND_HINT_SUIT;
	static string SOUND_SHOW_SUIT;
	static string SOUND_SEND_CARD;
	static string SOUND_RANK_WIN;
	static string SOUND_RANK_LOSE;
	static string SOUND_RANK_U;
	static string SOUND_RANK_MOM;
	static string SOUND_CHANGE_TURN;

	static vector<string> VOICE_DRAW_CARD;
	static vector<string> VOICE_DRAW_LAST;
	static vector<string> VOICE_EAT_CARD;
	static vector<string> VOICE_EAT_LAST;
	static vector<string> VOICE_THROW_CARD;
	static vector<string> VOICE_THROW_LAST;
	static vector<string> VOICE_ENTER_ROOM;
	static vector<string> VOICE_LEAVE_ROOM;
	static vector<string> VOICE_RANK_WIN;
	static vector<string> VOICE_RANK_LOSE;
	static vector<string> VOICE_TIMER;
	static vector<string> VOICE_U;
	static vector<string> VOICE_UTRON;
};
#endif // TalaInGameMgr_h__
