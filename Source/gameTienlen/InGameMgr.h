#ifndef InGameMgr_h__
#define InGameMgr_h__

#include "core/BaseMgr.h"

#define inGameMgr InGameMgr::getInstance()

class InGameMgr : public BaseMgr {
private:

public:
	InGameMgr();
	~InGameMgr();

	static InGameMgr* getInstance();
public:
	void init();
	bool isInBoard();
	int getChairFromId(int id);
	void openBoardScene(bool isSolo);
public:
	static InGameMgr* _instance;
public:
	void sendViewInfo();
	void sendStart();
	void sendAuthenConnect();
	void sendQuit();
	void sendCheatCard(vector <int> arrayCard);
};
#endif // InGameMgr_h__
