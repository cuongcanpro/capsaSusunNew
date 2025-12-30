#ifndef GameMgr_h__
#define GameMgr_h__

#include <string>
#include <vector>
#include "axmol.h"
using namespace std;

#define gameMgr GameMgr::getInstance()

struct SettingConfig {
	bool sound;
	bool vibrate;
	bool music;
	bool acceptInvite;
	bool acceptFriend;
	bool isVietnam;
};

#define TOP_WIN 0
#define TOP_GOLD 1
#define TOP_TALA 2
#define TOP_BINH_WIN 3
#define TOP_BINH_GOLD 4

#define TALA_OLD 1
#define TALA_NEW 2
enum TypeGame
{
	TIEN_LEN = 0,
	TA_LA = 1,
	BINH = 2
};

struct CountryInfo {
	std::string countryID;
};

class BaseMgr;
class GameMgr {

private:
	static GameMgr* _instance;

	vector<BaseMgr *> arListener;
	std::string appVersion;

	int offsetTimeZone;
	int offsetTimeServer;

	
	CountryInfo country;

public:	
	GameMgr();
	~GameMgr();
	
	void startGame();
	void startLoading();
	void initPlugin();
	void preloadGUI();
	void addSearchPath();
	void loadCache();

	void requestGameServices();
	void responseGameServices(bool isSuccess, std::string data);

	void saveTimestampServer(long long time);
	long long getTimestampServer();
	void setOffsetTimeZone();
	int getOffsetTimeZone();
	int getOffsetTimeServer();

	bool isInBoardScene();

	void onGameShow();
	void onGameHide();

	void onEnterScene();
	void onLoginEnter();
	void onLobbyEnter();
	void onUpdateScene(float dt);

	// country id 
	void findCountryID();
	std::string getCountryIdShop();
	std::string getCountryAppName();
	std::string getCountryID(bool isRealCountry = false);
	bool checkIsCountry(std::string id);

	//settings
	SettingConfig getSetting();
	bool changeSound(int state = -1);
	bool changeVibrate(int state = -1);
	bool changeInvite(int state = -1);
	bool changeFriend(int state = -1);
	bool changeMusic(int state = -1);

	std::string getAppVersion();
	std::string getInstallSource();
	std::string getDeviceID();
	std::string getInstallDate();
	std::string getLanguage();
	SettingConfig setting;
	bool checkLanguage(std::string lang);
	int getPlatform();

	bool useMove;

	int winCount;
	int lostCount;
	int gold;
	int idAvatar;

	int winCountTala;
	int lostCountTala;
	int goldTala;
	int idAvatarTala;

	int winCountBinh;
	int lostCountBinh;
	int goldBinh;
	int idAvatarBinh;

	int typeCard;

	string deviceId;
	string namePlayer;
	void pushMyData();
	void insertTop(int type, string name, string score);
	void getTop(int type);
	void getMyTop(int type);
	string getGameId(int type);
	int getGameCode(string gid);
	std::string getAvatarLevel(int level);
	int getLevel(int level);
	bool haveTop();
	bool waitCreateName;
	int arrayOldTop[5];

	int currentPosture;
	bool onReward(int num);
	void getVersion();
	void getCountry();
	bool isIOS();
	int need_update;
	std::string reasonUpdate;
	std::string urlUpdate;
	void endGame();
	string adsInter;
	string adsReward;
    std::string adBannerUnit;
    std::string adInterUnit;
    std::string adRewardUnit;
    int useAds;
	void getIdAds();
	bool checkUpdate();

	bool useGuiAt;
	int countHelpAt;
	int canPlayEffect;
	int fakeApp;
	string countryName;
	string languageDevice;
	void checkCanPlayEffect();
	int versionGame;
        bool isInitAds;
        void initAds();

    bool isIndo;
    void openBinhScene();
    public:
	static GameMgr* getInstance();
        void showReceiveGold();
        int beginner;
        void checkShowBanner();
};
#endif // GameMgr_h__
