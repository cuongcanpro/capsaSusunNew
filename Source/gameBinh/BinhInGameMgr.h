#ifndef BinhInGameMgr_h__
#define BinhInGameMgr_h__

#include "core/BaseMgr.h"
#include "logic/BinhGameLogic.h"

#define binhInGameMgr BinhInGameMgr::getInstance()

class BinhInGameMgr : public BaseMgr {
private:

public:
	BinhInGameMgr();
	~BinhInGameMgr();

	static BinhInGameMgr* getInstance();
public:
	void init();
	void update(float deltaTime);
	bool isInBoard();
	int getChairFromId(int id);
	void openBoardScene();
public:
	static BinhInGameMgr* _instance;
public:
	void sendViewInfo();
	void sendStart();
	void sendAuthenConnect();
	void sendQuit();
	void sendConfirmInGame();
	void sendCheatCard(vector <int> arrayCard);
	void sendReady(vector<int> arrayId, TypeSend type);
	void sendUnReady();
	void sendBaoBinh();
	void sendAddBot();
};
#endif // BinhInGameMgr_h__
