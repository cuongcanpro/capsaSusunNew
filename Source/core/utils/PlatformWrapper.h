//
//  PlatformWrapper.h
//  Farmery
//
//  Created by KienVN on 2/17/14.
//
//

#ifndef __PlatformWrapper__
#define __PlatformWrapper__
#include "string"

class PlatformWrapper
{
public:
    static void showInsertial();
    static void loadAds();
    static void sendEvent(const char* key, const char* data);
    static void crashlyticSetString(const char* key, const char* data);
    static void initAds(int type);
    static void showReward();
    static int networkReachable();
    static void showAds(bool visible);
    static void vibrate();
    static void openURL(std::string url);
    static std::string getIMEI();
};

#endif /* defined(__Farmery__PlatformWrapper__) */
