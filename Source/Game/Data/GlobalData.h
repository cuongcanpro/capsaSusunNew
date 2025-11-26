#pragma once

#ifndef GlobalData_h__
#define GlobalData_h__

#include "string"


#define FB_APP_ID "1429057640692974"			// Facebook APP_ID
#define GG_APP_ID "232635908588"			// Google APP_ID  (Android)

#define PORTAL_SERVICE_URL "http://118.102.3.25/"
//define PORTAL_SERVICE_URL "http://118.102.3.28:455/"

#define ZINGME_SERVICE_URL "http://myplay.apps.zing.vn/sso3/login.php"
#define ZINGME_REGISTER_URL "http://myplay.apps.zing.vn/sso3/register.php"
#define APP_VERSION_URL "http://myplay.apps.zing.vn/mobile/version.php"
#define GAME_NAME "pokerhk"
#define APP_VERSION "1"
#define GAMECODE_STAND_ALONE "standAlone"
#define GAMECODE_PORTAL "portal"

#define SOCIAL_GG_ID 0
#define SOCIAL_ZM_ID 1
#define SOCIAL_FB_ID 2
#define SOCIAL_GUEST_ID 3
#define SOCIAL_ZALO_ID 3


extern std::string versionApp;
extern int port;
extern std::string ip;
extern std::string urlVersion;
extern std::string urlTop;
extern std::string deviceId;
extern std::string gameCode;
extern std::string urlCheck;
extern std::string appName;

extern int enablePayment;
extern int platformId;
extern std::string platformString;
extern std::string source;
extern std::string urlUpdate;
extern std::string urlPromote;
extern int isApp;
extern std::string urlForum;
extern std::string urlHelp;
extern int updateGame;
extern int maintain;
extern bool isZingphone;
extern int enableFacebook;
extern int defaultLogin;
extern bool isNetwork;
extern int xuChange;
extern int fakeApp;
extern int isUpdate;

extern bool gameInit;
extern int giftIndex;
extern int timeSupport;
extern int numSupport;
extern bool isHolding;
extern int channelHold;
extern int roomHold;
extern std::string passHold;
extern bool isSound;
extern bool showSupportTime;
extern std::string typeSocialLogin;
extern int isPromote;

extern int idAdsFull;
extern int idAdsBanner;
extern std::string adBannerUnit;
extern std::string adInterUnit;
extern std::string adRewardUnit;

extern std::string adBannerUnitCampaign;
extern std::string adInterUnitCampaign;
extern std::string adRewardUnitCampaign;

extern std::string adBannerFacebook;
extern std::string adInterFacebook;
extern std::string adRewardFacebook;
extern std::string adAppFacebook;
extern std::string updateMessage;

#endif // GlobalData_h__


