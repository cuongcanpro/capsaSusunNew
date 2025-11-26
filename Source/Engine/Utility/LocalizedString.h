//
//  CCLocalizedString.h
//  SkeletonX
//
//  Created by 小苏 on 11-12-1.
//  Copyright (c) 2011年 GeekStudio. All rights reserved.
//

#ifndef _CCLocalizedString_h
#define _CCLocalizedString_h
#include <string>
/*get the localized string by the key, if can't get the value then return mComment
 */
extern int language;

#define ENGLISH_FD 0
#define VIETNAM 1
#define RUSSIA    2
#define INDONESIA    3
std::string CCLocalizedString(const char* mKey, const char* mComment = "");
void changeLanguage(int change);

#endif
