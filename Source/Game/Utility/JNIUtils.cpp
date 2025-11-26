#include "JNIUtils.h"
#include "axmol.h"



#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)

#include "PlatformWrapper.h"
#endif
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif


#include "../Data/GlobalData.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
//#include "PlatformInterface/IOS/FacebookController.h


void JNIUtils::showAdsFull()
{
    AXLOGD("SHOW ADS FULL ========== ");
    game->timeNoAds = 0;
    if (game->useAds == 0)
        return;
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "showAdsInterstitial");
 #endif
}

void JNIUtils::showAds(bool visible)
{
    int showAds = visible ? 1 : 0;
    AXLOGD("SHOW ADS BANNER ========== ");
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "showAdsBanner", showAds);
#endif
}

void JNIUtils::showAdsBanner(int showAds)
{
    AXLOGD("SHOW ADS BANNER ========== ");
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "showAdsBanner", showAds);
#endif
}

void JNIUtils::openUrl(const char* url) {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "openUrl", url);
#endif
}

void JNIUtils::initAds(const char* banner, const char* full, const char* reward, int idAdsBanner, int idAdsFull) {
    AXLOGD("BANNER ID NE %s ", banner);
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "initAds", banner, full, reward, idAdsBanner, idAdsFull);
#endif
}


void JNIUtils::initAdsFacebook(const char* app, const char* banner, const char* full, const char* reward) {
    AXLOGD("initAdsFacebook ID NE %s ", app);
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "initAdsFacebook", app, banner, full, reward);
#endif
}

void JNIUtils::openApp(const char* packageApp)
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "openApp", packageApp);
#endif
}

std::string JNIUtils::getPackageApp()
{

    return "";
}

void JNIUtils::sendEvent(const char* name, const char* data)
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "sendEvent", name, data);
#endif
    AXLOGD("Send Event %s === %s ", name ,data);
}

void JNIUtils::showRewardedAds()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "showAdsReward");
#endif
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
    game->onReward(1);
#endif
}

void JNIUtils::reloadAds()
{
    
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "reloadAds", adBannerUnit, adInterUnit, adRewardUnit);
#endif
}

void JNIUtils::setRussia(int isRussia)
{

}

void JNIUtils::submitScore(int type, int score) {
    AXLOGD("SubmitScore ======== ");
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "submitScore", type, score);
#endif
}

void JNIUtils::vibrate(int miliseconds)
{
    if (game->vibrate == false)
        return;
    AXLOGD("VIBRATE %i ", miliseconds);
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "vibrate", miliseconds);
#endif
}

void JNIUtils::setString(const char* name, const char* data)
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "setString", name, data);
#endif
    AXLOGD("Send setString %s === %s ", name, data);
}

std::string JNIUtils::getCountry()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    return JniHelper::callStaticStringMethod(classPath, "getCountry");
#endif
    return "";
}

void JNIUtils::changeToPortrait()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    PlatformWrapper::changeToPortrait();
#endif
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "changeToPortrait");
#endif
}

void JNIUtils::changeToLandscape()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    PlatformWrapper::changeToLandscape();
#endif
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    JniHelper::callStaticVoidMethod(classPath, "changeToLandscape");
#endif
}

int JNIUtils::getSourceApp()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
    return 0;
#endif
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    const char* classPath = "dev.axmol.app.AppActivity";
    return JniHelper::callStaticIntMethod(classPath, "getSourceApp");
#endif
}
