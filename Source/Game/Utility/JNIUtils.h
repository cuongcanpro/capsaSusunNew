#ifndef JNIUtils_h
#define JNIUtils_h

#include <string>
class JNIUtils
{
public:
    static void showAdsFull();
    static void showAds(bool visible);
    static void openUrl(const char* url);
    static void openApp(const char* packageApp);
    static void initAdsFacebook(const char* app, const char* banner, const char* full, const char* reward);
    static void initAds(const char* banner, const char* full, const char* reward, int idAdsBanner, int idAdsFull);
    static std::string getPackageApp();
    static void sendEvent(const char* name, const char* data);
    static void showRewardedAds();
    static void reloadAds();
    static void setRussia(int isRussia);
    static void submitScore(int type, int score);
    static void showAdsBanner(int show);
    static void vibrate(int miliseconds);
    static void setString(const char* name, const char* data);
    static std::string getCountry();
    static void changeToLandscape();
    static void changeToPortrait();
    static int getSourceApp();
};
#endif

