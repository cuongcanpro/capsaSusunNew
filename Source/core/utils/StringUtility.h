#ifndef StringUtility_h__
#define StringUtility_h__

#include "axmol.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "TimeUtil.h"

#include <vector>

class StringUtility {

public:
	static std::string standartNumber(long long number);
	static std::string formatNumberSymbol(long long number);
	static std::string numberConvert(long long number, long long div);
	static std::string pointNumber(long long number);
	static std::string replaceAll(std::string text, const std::string& searchText, const std::string& replaceText);
	static std::string replaceAll(std::string text, const std::string& searchText, int to);
	static std::string replaceAll(std::string text, const std::string& searchText, long long to);
	static std::string subStringText(std::string& text, ax::ui::Text* lb);
	static std::string subStringTextLength(std::string& text, int length);
	static std::string longWordBreaker(std::string& text, int length);
	static int getLabelWidth(ax::ui::Text* label);
	static std::string getDateString(long long time);
	static int getDifferentTimeZoneHour();
	static std::string getRemainTimeString(long long remainTime);
	static std::string md5(std::string input);
	static std::string encodeURIComponent(std::string s);
	static std::vector<std::string> splitString(std::string str, std::string split);
	static int randomRange(int min, int max);
	static std::string toStringFixed(double percent, int fixed = 2);
	static std::string getTimeString(long long time); // tra ve gio::phut::ss 04:30, 03::20
	static double stringToTimeStamp(std::string time);
	static std::vector<std::string> split(std::string text, char sep);
	static std::vector<std::string> split(std::string text, std::string reg);
	static std::string trim(std::string str);
	static void breakLabel(ax::ui::Text* label, float width);
	static std::string customFormatDate(long long millis, std::string format);
	static std::string toUpperCase(std::string str);
	static std::string toLowerCase(std::string str);
	static std::string toCamelCase(std::string str);
	//static ax::Color4B getColor4B(std::string hex);
	//static ax::Color4B getColor4B(std::string hex);

public:
	static const std::vector<std::string> LIST_MONTH_ES;
	static const std::vector<std::string> LIST_MONTH_EN;
	static const std::vector<std::string> LIST_WDAY_EN;
	static const std::string WHITE_SPACE;
};
#endif // StringUtility_h__
