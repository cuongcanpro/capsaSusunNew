//
//  CCLocalizedString.cpp
//  SkeletonX
//
//  Created by mac on 11-12-1.
//  Copyright (c) 2011年 GeekStudio. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "LocalizedString.h"
#include "ScreenUtils.h"
int language = 0;
static std::map<std::string, std::string> localizedStrings;

void changeLanguage(int change) {
	language = change;
	localizedStrings.clear();
}

std::string CCLocalizedString(const char* mKey, const char* mComment)
{

	//ccLanguageType curLanguage = CCApplication::sharedApplication()->getCurrentLanguage();

	const char * fileName;
	//	language = INDO;
        switch (language)
        {
        case VIETNAM:
            fileName = "Localize/Content_vi";
            break;
        case RUSSIA:
            fileName = "Localize/Content_ru";
            break;
        case ENGLISH_FD:
            fileName = "Localize/Content_en";
            break;
        case INDONESIA:
            fileName = "Localize/Content_in";
            break;
        /**
         case for more localize
         */
        default:
            fileName = "Localize/Content_en";
            break;
        }

	std::string resultStr;

	if (localizedStrings.empty())
	{
		// Initialize variables needed
		unsigned long fileSize = 0;
		unsigned char * fileContents = NULL;
		std::string line, fullPath, contents;

		// Get absolute path of file
		fullPath = FileUtils::getInstance()->fullPathForFilename(ScreenUtils::fileCommon(fileName).c_str());

		// Get data of file
		//fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &fileSize );
		//contents.append( ( char * ) fileContents );
                contents = FileUtils::getInstance()->getStringFromFile(fileName);

		//CCLog("CONTENT %s ", contents.c_str());
		// Create a std::string stream so that we can use getline( ) on it
                std::istringstream fileStringStream(contents);

		// Get file contents line by line
		while (std::getline(fileStringStream, line))
		{
			AXLOGD("LINE %s ", line.c_str());
			//            debug_Printf("line :%s",line.c_str());
			if (line.find("/*", 0) == std::string::npos &&
				line.find("//", 0) == std::string::npos &&
				line.find("*/", 0) == std::string::npos) //filter the valid std::string of one line
			{
				//                debug_Printf("find the line not start with \" /* \"");
				std::string::size_type validPos = line.find('=', 0);
				if (validPos != std::string::npos)
				{
					std::string keyStr = line.substr(0, validPos - 1);
					std::string subStr = line.substr(validPos + 1, line.size() - 1); // get valid std::string

					//trim space
					keyStr.erase(0, keyStr.find_first_not_of(" \t")); // 去掉头部空格
					keyStr.erase(keyStr.find_last_not_of(" \t") + 1); // 去掉尾部空格

					subStr.erase(0, subStr.find_first_not_of(" \t")); // 去掉头部空格
					subStr.erase(subStr.find_last_not_of(" \t") + 1); // 去掉尾部空格

					//trim \" 
					keyStr.erase(0, keyStr.find_first_not_of("\""));
					int findPosition = subStr.find('\"', 0);
					//if (findPosition != std::string::npos)
					//	subStr.erase(findPosition);
					keyStr.erase(keyStr.find_last_not_of("\"") + 1);

					//ax::CCLog("string before erase %s", subStr.c_str());
					subStr.erase(0, subStr.find_first_not_of("\""));
					//ax::CCLog("string after erase %s", subStr.c_str());



					//trim ; character and last \" character
					subStr.erase(subStr.find_last_not_of(";") + 1);
					int position = subStr.find_last_not_of("\"") + 1;
					findPosition = subStr.find('\"', 0);
					if (findPosition != std::string::npos)
						subStr.erase(findPosition);
					//ax::CCLog("string final %s %i %i", subStr.c_str(), position, findPosition);


					//replace line feed with \n
                                        std::string::size_type pos(0);
                                        std::string old_value("\\n");
					if ((pos = subStr.find(old_value)) != std::string::npos)
					{
						for (; pos != std::string::npos; pos += 1)
						{
							if ((pos = subStr.find(old_value, pos)) != std::string::npos)
							{
								subStr.erase(pos, 2);
								subStr.insert(pos, 1, '\n');
							}
							else
								break;
						}
					}

					localizedStrings.insert(std::pair<std::string, std::string>(keyStr, subStr));

					const char * keyChars = keyStr.c_str();

					if (strcmp(keyChars, mKey) == 0) {
						resultStr = subStr;
					}
				}
			}
		}
		//must delete fileContents
		if (fileContents != NULL) {
			delete[] fileContents;
			fileContents = NULL;
		}

		//return valid value
		if (resultStr.length() > 0) {
			return (std::string(resultStr)).c_str();
		}
		return mKey;
	}
	else
	{
		std::map<std::string, std::string>::iterator itr = localizedStrings.find(std::string(mKey));
		if (itr != localizedStrings.end()) {
			return (itr->second).c_str();
		}
	}
	return mKey;
}
