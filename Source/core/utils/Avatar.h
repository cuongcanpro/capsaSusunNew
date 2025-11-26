#ifndef Avatar_h__
#define Avatar_h__
#include "axmol.h"
class Avatar:
	public ax::Node{
public:
	Avatar();
	~Avatar();
	static Avatar* create(std::string defaultImg, std::string url = "");
	bool init(std::string defaultImg, std::string url = "");
public:
	void updateAvatar(std::string url);
	void onFinishLoad(bool result);
	std::string getStorePath(std::string url);
public:
	ax::Sprite* defaultAvatar;
};
#endif // Avatar_h__
