#ifndef BaseMgr_h__
#define BaseMgr_h__

//#include "BaseFramework.h"
#include "app/Config.h"
#include "app/Constant.h"
#include "app/GameMgr.h"
#include "core/gui/SceneMgr.h"
#include <string>
#include "axmol.h"
using namespace std;
using namespace ax;
using namespace ui;
using namespace extension;

class BaseMgr : public Object {

protected:
	static BaseMgr* _instance;
	static int AUTO_ID;
	
	std::string id;
public:	
	BaseMgr();
	~BaseMgr();

	std::string getID();
	bool compare(BaseMgr *a);

	virtual void onLoginScene();

	//void sendPacket(fr::OutPacket* pk);

	/*virtual bool onReceivePacket(fr::InPacket* pk);

	void putIntArray(fr::OutPacket* pk, const vector<int> &ints);
	void putLongArray(fr::OutPacket* pk, const vector<long long> &longs);
	void putLongArray(fr::OutPacket* pk, const vector<double> &doubles);
	void putDoubleArray(fr::OutPacket* pk, const vector<double> &doubles);
	void putDoubleArray(fr::OutPacket* pk, const vector<long long> &longs);*/
};
#endif // BaseMgr_h__
