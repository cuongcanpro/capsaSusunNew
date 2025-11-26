#include "GameUtility.h"
#include "axmol.h"
#include "../GUIManager.h"
#include "Engine/Utility/CStringUtils.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "Engine/GlobalVar.h"
using namespace ax;

std::vector<std::string> GameUtility::split(const std::string& s, const std::string& delim, const bool keep_empty)
{
	vector<std::string> result;
	if (delim.empty()) {
		result.push_back(s);
		return result;
	}
	std::string::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		std::string temp(substart, subend);
		if (keep_empty || !temp.empty()) {
			result.push_back(temp);
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

std::string GameUtility::standartTime(int num)
{
	if(num < 10)
		return "0" + GameUtility::toString(num);
	else
		return GameUtility::toString(num);
}


std::string GameUtility::toString(int value)
{
	ostringstream ss;
	ss << value;
	return ss.str();
}

std::string GameUtility::standardizeString(std::string value, int numCharacter)
{
	if(value.length() > numCharacter)
	{
		std::string result = value.substr(0, numCharacter - 2);
		return result + "...";
	}
	else
	{
		return value;
	}
	
}

std::string GameUtility::standardizeNumber(int value)
{
	std::string num = toString(value);
	std::string result = "";
	for(int i = num.length() -1 ; i >= 0; i--)
	{
		result = num.at(i) + result;
		if((num.length() - i)%3 == 0 && i != 0)
		{
			result = "." + result;
		}
	}
	return result;
}


#ifdef ANDROID

#include "axmol.h"
#include <string.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"


std::string GameUtility::imei = "";

std::string GameUtility::getIMEI(){
	
	return "";
}
#endif

int GameUtility::convertExp2Level(int exp)
{
	int level = 0;
	if (exp <= 1600) {
		level = 0;
	} else if (exp <= 1690) {
		level = 1;
	} else if (exp <= 1780) {
		level = 2;
	} else if (exp <= 1870) {
		level = 3;
	} else if (exp <= 1960) {
		level = 4;
	} else if (exp <= 2050) {
		level = 5;
	} else if (exp <= 2140) {
		level = 6;
	} else if (exp <= 2230) {
		level = 7;
	} else if (exp <= 2320) {
		level = 8;
	} else {
		level = 9;
	}
	return level;
}

// void GameUtility::callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler)
// {
// 	AXLOGD("url = %s", url);
// 	ax::extension::CCHttpRequest* request = new ax::extension::CCHttpRequest();
// 	request->setUrl(url);
// 	request->setRequestType(ax::extension::CCHttpRequest::kHttpGet);
// 
// 	/*request->setRequestType(ax::extension::CCHttpRequest::kHttpPost);
// 	std::string postData = "pid=25&u1=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Fsuccess&fp=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Ffai&apikey=6bfea26364a08c4ad330dceef4e999a7&u=" + std::string(userName) + "&p=" + std::string(password) + "&longtime=1";
// 	int length = strlen(postData.c_str());
// 	request->setRequestData(postData.c_str(), length);*/
// 
// 	request->setResponseCallback(handler, callBack);
// 	ax::extension::CCHttpClient::getInstance()->send(request);
// 	request->release();
// }

float GameUtility::getRandom()
{
	float r = (float)(rand()) / RAND_MAX;
	return r;
}

std::string GameUtility::standartNum( int num, int max )
{
	int maxConvert = pow(10, max);
	maxConvert = maxConvert - 1;
	if(num > maxConvert)
		num = maxConvert;
	std::string result = CStringUtils::toString(num);
	int add = max - 1 - result.length();
	for(int i = 0; i < add; i++)
	{
		result = "0" + result;
	}
	return result;
}
//
//void GameUtility::callHttpRequest(const char* url, SEL_HttpResponse callBack, HttpRequestHandler* handler)
//{
//    AXLOGD("url = %s", url);
//	HttpRequest* request = new (std::nothrow) HttpRequest();
//	request->setUrl(url);
//	request->setRequestType(HttpRequest::Type::GET);
//	request->setResponseCallback(handler, callBack);
//	request->setTag("GET immediate test1");
//	HttpClient::getInstance()->sendImmediate(request);
//	request->release();
//
//    //ax::extension::CCHttpRequest* request = new ax::extension::CCHttpRequest();
//    //request->setUrl(url);
//    //request->setRequestType(ax::extension::CCHttpRequest::kHttpGet);
//    //
//    ///*request->setRequestType(ax::extension::CCHttpRequest::kHttpPost);
//    // std::string postData = "pid=25&u1=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Fsuccess&fp=http%3A%2F%2Flogin.me.zing.vn%2Flogin%2Ffai&apikey=6bfea26364a08c4ad330dceef4e999a7&u=" + std::string(userName) + "&p=" + std::string(password) + "&longtime=1";
//    // int length = strlen(postData.c_str());
//    // request->setRequestData(postData.c_str(), length);*/
//    //
//    //request->setResponseCallback(handler, callBack);
//    //ax::extension::CCHttpClient::getInstance()->send(request);
//    //request->release();
//}


ax::Color3B GameUtility::getColorLine(int id)
{
	switch (id) {
	case 1:
		return Color3B(255, 0, 0);
		break;
	case 2:
		return Color3B(0, 0, 255);
		break;
	case 3:
		return Color3B(0, 255, 0);
		break;
	case 4:
		return Color3B(255, 255, 0);
		break;
	case 5:
		return Color3B(255, 51, 204);
		break;
	case 6:
		return Color3B(153, 102, 51);
		break;
	case 0:
		return Color3B(0, 204, 255);
		break;

	}
}

const char* GameUtility::getTexture(int id)
{
	switch (id % 20) {
	case 0:
		return "Ball/lineBall_2_0.png";
		break;
	case 1:
		return "Ball/lineBall_2_0.png";
		break;
	case 2:
		return "Ball/lineBall_2_1.png";
		break;
	case 3:
		return "Ball/lineBall_2_1.png";
		break;
	case 4:
		return "Ball/lineBall_2_2.png";
		break;
	case 5:
		return "Ball/lineBall_2_2.png";
		break;
	case 6:
		return "Ball/lineBall_2_3.png";
		break;
	case 7:
		return "Ball/lineBall_2_3.png";
		break;
	case 8:
		return "Ball/lineBall_2_4.png";
		break;
	case 9:
		return "Ball/lineBall_2_4.png";
		break;
	case 10:
		return "Ball/lineBall_2_5.png";
		break;
	case 11:
		return "Ball/lineBall_2_5.png";
		break;
	default:
		return "Ball/lineBall_2_0.png";
		break;
	}

	switch (id % 20) {
	case 0:
		return "brick/cell_0.png";
		break;
	case 1:
		return "brick/cell_0.png";
		break;
	case 2:
		return "brick/cell_1.png";
		break;
	case 3:
		return "brick/cell_1.png";
		break;
	case 4:
		return "brick/cell_2.png";
		break;
	case 5:
		return "brick/cell_2.png";
		break;
	case 6:
		return "brick/cell_3.png";
		break;
	case 7:
		return "brick/cell_3.png";
		break;
	case 8:
		return "brick/cell_4.png";
		break;
	case 9:
		return "brick/cell_4.png";
		break;
	case 10:
		return "brick/cell_5.png";
		break;
	case 11:
		return "brick/cell_5.png";
		break;
	default:
		return "brick/cell_0.png";
		break;
	}
}

std::string GameUtility::getTextureCell(int id)
{
    id            = id % 20;
    id            = id % 6;
    std::string s = "GuiGame/gameBlockPuzzel/cell_" + to_string(id) + ".png";
	return s;
}

std::string GameUtility::getTextureCellImage(int id)
{
    id            = id % 20;
    id            = id % 6;
    std::string s = "gameBlockPuzzel/cell_" + to_string(id) + ".png";
    return s;
}

std::string GameUtility::getResourceBall(int id)
{
   // game->typeBall = 10;
    game->typeBall = 1;
    if (id <= 0 || id >= 8)
        id = 0;
   std::string s = "balls/lineBall_" + to_string(game->typeBall) + "_" + to_string(id - 1) + ".png";
   //std::string s = "bubble_" + to_string(id) + ".png";
   return s;
}

std::string GameUtility::getTextureColor(int id)
{
	int color = 0;
	int _id = id;
	while (_id / 2 != 0)
	{
		color++;
		_id = _id / 2;

	}
	return "Ball/lineBall_3_" + GameUtility::toString(color % 9) + ".png";
}


ax::Color3B GameUtility::getColor(int id)
{
	int color = 0;
	int _id = id;
	while (_id / 2 != 0)
	{
		color++;
		_id = _id / 2;

	}
	color = color + 1;
	switch (color % 20) {
	case 1:

		return Color3B(0, 153, 255);
		break;
	case 2:
		return Color3B(255, 204, 0);
		break;
	case 3:
		return Color3B(255, 0, 0);
		break;
	case 4:
		return Color3B(204, 0, 153);
		break;
	case 5:
		return Color3B(0, 204, 0);
		break;
	case 6:
		return Color3B(255, 102, 0);
		break;
	case 7:
		return Color3B(0, 0, 255);
		break;
	case 8:
		return Color3B(153, 102, 51);
		break;
	case 9:
		return Color3B(102, 102, 153);
		break;
	case 10:
		return Color3B(0, 102, 0);
		break;
	case 11:
		return Color3B(0.0f * 255, 0.11f * 255, 0.4f * 255);
		break;
	case 12:
		return Color3B(1.0f * 255, 0.6f * 255, 0.78f * 255);
		break;
	case 13:
		return Color3B(0.5f * 255, 0.0f * 255, 0.1f * 255);
		break;
	case 14:
		return Color3B(0.6f * 255, 0.7f * 255, 0.9f * 255);
		break;
	case 15:
		return Color3B(0.9f * 255, 0.84f * 255, 0.76f * 255);
		break;
	case 16:
		return Color3B(0.77f * 255, 0.59f * 255, 0.31f * 255);
		break;
	case 17:
		return Color3B(0.7f * 255, 0.0f * 255, 0.15f * 255);
		break;
	case 18:
		return Color3B(0.44f * 255, 0.34f * 255, 0.99f * 255);
		break;
	case 19:
		return Color3B(0.0f * 255, 0.39f * 255, 0.19f * 255);
		break;
	case 0:
		return Color3B(0.96f * 255, 0.53f * 255, 0.47f * 255);
		break;
	}
}

ax::Color3B GameUtility::getColorTwenty(int id)
{
	switch (id % 25)
	{
	case 0:
		return Color3B(135, 162, 81);
		break;
	case 1:
		return Color3B(255, 51, 52);
		break;
	case 2:
		return Color3B(56, 170, 56);
		break;
	case 3:
		return Color3B(255, 204, 0);
		break;
	case 4:
		return Color3B(50, 204, 254);
		break;
	case 5:
		return Color3B(255, 103, 154);
		break;
	case 6:
		return Color3B(199, 95, 60);
		break;
	case 7:
		return Color3B(191, 67, 191);
		break;
	case 8:
		return Color3B(203, 204, 102);
		break;
	case 9:
		return Color3B(255, 102, 0);
		break;
	case 10:
		return Color3B(102, 154, 204);
		break;
	case 11:
		return Color3B(150, 150, 150);
		break;
	case 12:
		return Color3B(138, 73, 95);
		break;
	case 13:
		return Color3B(153, 204, 51);
		break;
	case 14:
		return Color3B(255, 153, 52);
		break;
	case 15:
		return Color3B(255, 51, 102);
		break;
	case 16:
		return Color3B(75, 120, 205);
		break;
	case 17:
		return Color3B(255, 51, 154);
		break;
	case 18:
		return Color3B(53, 51, 255);
		break;
	case 19:
		return Color3B(255, 51, 87);
		break;
	case 20:
		return Color3B(129, 59, 40);
		break;
	case 21:
		return Color3B(117, 63, 146);
		break;
	case 22:
		return Color3B(56, 121, 40);
		break;
	case 23:
		return Color3B(204, 204, 204);
		break;
	case 24:
		return Color3B(55, 88, 150);
		break;
	default:
		return Color3B(255, 255, 255);
		break;
	}
}

ax::Color3B GameUtility::getColorMerge(int id)
{
	switch (id % 25)
	{
	case 0:
		return Color3B(104, 124, 187);
		break;
	case 1:
		return Color3B(255, 51, 52);
		break;
	case 2:
		return Color3B(56, 170, 56);
		break;
	case 3:
		return Color3B(255, 204, 0);
		break;
	case 4:
		return Color3B(50, 204, 254);
		break;
	case 5:
		return Color3B(255, 103, 154);
		break;
	case 6:
		return Color3B(199, 95, 60);
		break;
	case 7:
		return Color3B(191, 67, 191);
		break;
	case 8:
		return Color3B(203, 204, 102);
		break;
	case 9:
		return Color3B(205, 102, 0);
		break;
	case 10:
		return Color3B(178, 24, 25);
		break;
	case 11:
		return Color3B(45, 18, 176);
		break;
	case 12:
		return Color3B(117, 194, 140);
		break;
	case 13:
		return Color3B(203, 184, 131);
		break;
	case 14:
		return Color3B(139, 119, 196);
		break;
	case 15:
		return Color3B(255, 210, 51);
		break;
	case 16:
		return Color3B(139, 255, 51);
		break;
	case 17:
		return Color3B(48, 255, 255);
		break;
	case 18:
		return Color3B(143, 8, 241);
		break;
	case 19:
		return Color3B(255, 56, 87);
		break;
	case 20:
		return Color3B(79, 216, 255);
		break;
	case 21:
		return Color3B(214, 255, 47);
		break;
	case 22:
		return Color3B(192, 134, 112);
		break;
	case 23:
		return Color3B(12, 173, 94);
		break;
	case 24:
		return Color3B(23, 115, 182);
		break;
	default:
		return Color3B(255, 255, 255);
		break;
	}
}

ax::Color3B GameUtility::getColorPop(int id)
{
	switch (id % 25)
	{
	case 0:
		return Color3B(240, 0, 0);
		break;
	case 1:
		return Color3B(240, 0, 0);
		break;
	case 2:
		return Color3B(0, 240, 0);
		break;
	case 3:
		return Color3B(0, 0, 240);
		break;
	case 4:
		return Color3B(240, 240, 0);
		break;
	case 5:
		return Color3B(255, 157, 0);
		break;
	case 6:
		return Color3B(255, 142, 214);
		break;
	case 7:
		return Color3B(1, 200, 201);
		break;
	case 8:
		return Color3B(21, 180, 2);
		break;
	case 9:
		return Color3B(91, 18, 3);
		break;
	case 10:
		return Color3B(255, 1, 162);
		break;
	case 11:
		return Color3B(212, 186, 6);
		break;
	case 12:
		return Color3B(99, 1, 212);
		break;
	case 13:
		return Color3B(203, 184, 131);
		break;
	case 14:
		return Color3B(139, 119, 196);
		break;
	case 15:
		return Color3B(255, 210, 51);
		break;
	case 16:
		return Color3B(139, 255, 51);
		break;
	case 17:
		return Color3B(48, 255, 255);
		break;
	case 18:
		return Color3B(143, 8, 241);
		break;
	case 19:
		return Color3B(255, 56, 87);
		break;
	case 20:
		return Color3B(79, 216, 255);
		break;
	case 21:
		return Color3B(214, 255, 47);
		break;
	case 22:
		return Color3B(192, 134, 112);
		break;
	case 23:
		return Color3B(12, 173, 94);
		break;
	case 24:
		return Color3B(23, 115, 182);
		break;
	default:
		return Color3B(255, 255, 255);
		break;
	}
}


ax::Color3B GameUtility::getColorPopOutline(int id)
{
    switch (id % 25)
    {
    case 0:
        return Color3B(168, 0, 0);  // darker red
        break;
    case 1:
        return Color3B(168, 0, 0);
        break;
    case 2:
        return Color3B(0, 168, 0);  // darker green
        break;
    case 3:
        return Color3B(0, 0, 168);  // darker blue
        break;
    case 4:
        return Color3B(168, 168, 0);  // darker yellow
        break;
    case 5:
        return Color3B(178, 110, 0);  // darker orange
        break;
    case 6:
        return Color3B(178, 99, 150);  // darker pink
        break;
    case 7:
        return Color3B(1, 140, 141);  // darker cyan
        break;
    case 8:
        return Color3B(15, 126, 1);  // darker green
        break;
    case 9:
        return Color3B(64, 12, 2);  // darker brown
        break;
    case 10:
        return Color3B(178, 1, 113);  // darker magenta
        break;
    case 11:
        return Color3B(149, 130, 4);  // darker gold
        break;
    case 12:
        return Color3B(70, 1, 149);  // darker violet
        break;
    case 13:
        return Color3B(142, 129, 91);  // darker beige
        break;
    case 14:
        return Color3B(97, 83, 137);  // darker purple
        break;
    case 15:
        return Color3B(178, 147, 36);  // darker yellow-orange
        break;
    case 16:
        return Color3B(97, 178, 36);  // darker lime
        break;
    case 17:
        return Color3B(34, 178, 178);  // darker aqua
        break;
    case 18:
        return Color3B(100, 5, 169);  // darker indigo
        break;
    case 19:
        return Color3B(178, 39, 61);  // darker pink-red
        break;
    case 20:
        return Color3B(55, 151, 178);  // darker sky blue
        break;
    case 21:
        return Color3B(150, 178, 33);  // darker lime-yellow
        break;
    case 22:
        return Color3B(134, 94, 78);  // darker brown-pink
        break;
    case 23:
        return Color3B(8, 121, 66);  // darker green
        break;
    case 24:
        return Color3B(16, 81, 129);  // darker blue
        break;
    default:
        return Color3B(200, 200, 200);  // darker white
        break;
    }
}

std::string GameUtility::convertToTime(int timeGame)
{
	if (timeGame == 0)
		return "xx:xx:xx";
	int convertTime = timeGame;
	int hour = convertTime / 3600;
	convertTime = convertTime % 3600;
	int minute = convertTime / 60;
	int second = convertTime % 60;
        std::string s   = hour < 10 ? "0" + to_string(hour) : to_string(hour);
        s               = s + ":" + (minute < 10 ? "0" + to_string(minute) : to_string(minute));
        s               = s + ":" + (second < 10 ? "0" + to_string(second) : to_string(second));
	return s;
}

std::string GameUtility::convertTime(int countTime)
{
    int minute = (int)(countTime / 60);
    int second = (int)(countTime - minute * 60);

    string minuteS, secondS;
    if (minute < 10)
    {
        minuteS = "0" + GameUtility::toString(minute);
    }
    else
    {
        minuteS = "" + GameUtility::toString(minute);
    }

    if (second < 10)
    {
        secondS = "0" + GameUtility::toString(second);
    }
    else
    {
        secondS = "" + GameUtility::toString(second);
    }
    return minuteS + ":" + secondS;
}
