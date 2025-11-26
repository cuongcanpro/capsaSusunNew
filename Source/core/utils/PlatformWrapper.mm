//
//  PlatformWrapper.cpp
//  Farmery
//
//  Created by KienVN on 2/17/14.
//
//

#include "PlatformWrapper.h"
#include "RootViewControllerInterface.h"
#import <AudioToolbox/AudioServices.h>
//#import "Reachability.h"

void PlatformWrapper::showInsertial(){
  
   [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] showInsertial];
    
}

void PlatformWrapper::loadAds(){
  
   [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] showInsertial];
    
}

void PlatformWrapper::sendEvent(const char* key, const char *data){
    NSString* nsURL = [NSString stringWithUTF8String:data];
    NSString* nsKey = [NSString stringWithUTF8String:key];
    
   [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] sendEvent: nsKey data:nsURL];
    
}

void PlatformWrapper::crashlyticSetString(const char* key, const char *data){
    NSString* nsURL = [NSString stringWithUTF8String:data];
    NSString* nsKey = [NSString stringWithUTF8String:key];
    
   [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] crashlyticSetString: nsKey data:nsURL];
    
}

void PlatformWrapper::initAds(int type) {
   
    [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] initAds:type];
}

void PlatformWrapper::showReward() {
    [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] showReward];
}


int PlatformWrapper::networkReachable()
{
//    Reachability *networkReachability = [Reachability reachabilityForInternetConnection];
//    NetworkStatus networkStatus = [networkReachability currentReachabilityStatus];
//    if (networkStatus == NotReachable) {
//        NSLog(@"There IS NO internet connection");
//        return 0;
//    } else {
//        NSLog(@"There IS internet connection");
//        return 1;
//    }
}

void PlatformWrapper::showAds(bool visible){
    
    [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] showAds:visible];
    
}

void PlatformWrapper::vibrate() {
    //AudioServicesPlayAlertSound(UInt32(kSystemSoundID_Vibrate));
    AudioServicesPlaySystemSound(1519);
  //  AudioServicesPlaySystemSoundWithVibration();
//
//    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
//    NSMutableArray* arr = [NSMutableArray array ];
//
//    [arr addObject:[NSNumber numberWithBool:YES]]; //vibrate for 2000ms
//    [arr addObject:[NSNumber numberWithInt:2000]];
//
//    [arr addObject:[NSNumber numberWithBool:NO]];  //stop for 1000ms
//    [arr addObject:[NSNumber numberWithInt:1000]];
//
//    [arr addObject:[NSNumber numberWithBool:YES]];  //vibrate for 1000ms
//    [arr addObject:[NSNumber numberWithInt:1000]];
//
//    [arr addObject:[NSNumber numberWithBool:NO]];    //stop for 500ms
//    [arr addObject:[NSNumber numberWithInt:500]];
//
//    [dict setObject:arr forKey:@"VibePattern"];
//    [dict setObject:[NSNumber numberWithInt:1] forKey:@"Intensity"];
//
//    AudioServicesPlaySystemSoundWithVibration(4095, nil, dict);
//    AudioServicesPlaySystemSoundWithVibration(4095,nil,dict);
}
//


void PlatformWrapper::openURL(std::string url)
{
    NSString* nsURL = [NSString stringWithUTF8String:("" + url).c_str()];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:nsURL]];
}

std::string PlatformWrapper::getIMEI()
{
    NSUUID *identify = [[UIDevice currentDevice] identifierForVendor];
    NSString *str = [identify UUIDString];
    return [str UTF8String];
}
