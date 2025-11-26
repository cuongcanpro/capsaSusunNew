#include "BaseMgr.h"

int BaseMgr::AUTO_ID = 0;

BaseMgr::BaseMgr()
{
	id = std::to_string(AUTO_ID) + "_";
	id += std::to_string(rand()) + "_";
	id += std::to_string(TimeUtil::getCurrentTimeMiliseconds());

	AUTO_ID++;

	AXLOGD("ID : %d %s",AUTO_ID,id.c_str());
}

BaseMgr::~BaseMgr()
{

}

std::string BaseMgr::getID() {
	return id;
}

bool BaseMgr::compare(BaseMgr *a) {
	if (this->getID().compare(a->getID()) == 0) {
		return true;
	}
	return false;
}

void BaseMgr::onLoginScene() {
	// call when login scene
}


