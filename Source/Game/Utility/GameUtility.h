#ifndef GAME_UTILITY_H
#define GAME_UTILITY_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "axmol.h"
#include "extensions/axmol-ext.h"
#include "Game/NetworkGame/HttpRequestHandler.h"
#include "network/HttpClient.h"

using namespace ax;
using namespace ax::extension;
using namespace ax::network;
class GameUtility
{
public:
    static std::vector<std::string> split(const std::string& s, const std::string& delim, const bool keep_empty = true);
	static std::string standartTime(int num);
        static std::string toString(int value);
        static std::string standardizeString(std::string value, int numCharacter = 10);
        static std::string standardizeNumber(int value);

	static std::string urlEncode(const std::string& value);
	static float getRandom();
        static std::string standartNum(int num, int max);
   // static void callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler);
	static ax::Color3B getColorLine(int id);
	static const char* getTexture(int id);
        static std::string getTextureCell(int id);
        static std::string getTextureCellImage(int id);
        static std::string getResourceBall(int id);
        static std::string getTextureColor(int id);
	static ax::Color3B getColorTwenty(int id);
	static ax::Color3B getColor(int id);
	static ax::Color3B getColorMerge(int id);
	static ax::Color3B getColorPop(int id);
    static ax::Color3B getColorPopOutline(int id);
        static std::string convertToTime(int time);
#ifdef ANDROID
	static std::string imei;
	static std::string getIMEI();
#endif
	static int convertExp2Level(int exp);
//	static void callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler);
	std::string getClockDay( double timeValue );
    static std::string convertTime(int value);
};
#endif
