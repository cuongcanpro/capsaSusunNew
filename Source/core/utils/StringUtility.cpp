#include "StringUtility.h"
#include "LanguageMgr.h"
#include "axmol.h"
#include <regex>
#include <ctime>
#include <iomanip>
#include <fmt/format.h>
std::string StringUtility::standartNumber(long long number)
{
	std::string tmp = std::to_string(number);
	
	return tmp;
}

std::string StringUtility::formatNumberSymbol(long long number)
{
	std::string retVal = "";
	if (number < 0)
		retVal = "-";
	number = abs(number);

    if (number >= 1000000000)
    {
        AXLOGD("CONVERT MONEY %s ", numberConvert(number, 1000000000).c_str());
        return fmt::format("{}{}B", retVal, numberConvert(number, 1000000000));
    }
    else if (number >= 1000000)
    {
        return fmt::format("{}{}M", retVal, numberConvert(number, 1000000));
    }
    else if (number >= 1000)
    {
        return fmt::format("{}{}K", retVal, numberConvert(number, 1000));
    }
    else
    {
        return fmt::format("{}{}", retVal, number);
    }
}

std::string StringUtility::numberConvert(long long number, long long div)
{
    long long a = number / (div / 100);
    long long b = a / 100;

    a = a - b * 100;
    if (a == 0)
    {
        return ax::StringUtils::format("%ld", b);
    }
    else
    {
        if (a > 9)
        {
            if (a % 10 == 0)
            {
                return std::to_string(b) + "." + std::to_string(a / 10);
            }
            else
            {
                return std::to_string(b) + "." + std::to_string(a);
            }
        }
        else
        {
            return std::to_string(b) + "." + std::to_string(a);
        }
    }
}

std::string StringUtility::pointNumber(long long number)
{
	return standartNumber(number);
}

std::string StringUtility::replaceAll(std::string text, const std::string& searchText, const std::string& replaceText)
{
	std::string txt = text;
	if (searchText.empty())
		return text;
	size_t start_pos = 0;
	while ((start_pos = txt.find(searchText, start_pos)) != std::string::npos) {
		txt.replace(start_pos, searchText.length(), replaceText);
	}
	return txt;
}

std::string StringUtility::replaceAll(std::string text, const std::string& searchText, int to) {
	char s_to[12];
	sprintf(s_to, "%d", to);
	return replaceAll(text, searchText, std::string(s_to));
}
std::string StringUtility::replaceAll(std::string text, const std::string& searchText, long long to)
{
	char s_to[30];
	sprintf(s_to, "%lld", to);
	return replaceAll(text, searchText, std::string(s_to));
}
std::string StringUtility::subStringText(std::string& text, ax::ui::Text* lb)
{
	std::string str = std::string(lb->getString());
	if (text.size() <= str.size()) return text;
        return str;
	//return ax::StringUtils::format("%s...",text.substr(0, str.size() - 3).c_str());
}

std::string StringUtility::subStringTextLength(std::string& text, int length)
{
	if (text.size() <= length) 
		return text;

	return text.substr(0, length - 2) + "...";
}

std::string StringUtility::longWordBreaker(std::string& text, int length)
{
	int count = 0;
	std::string resultText = "";
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == ' ') count = 0; else count++;
		if (count > length) {
			resultText += " -" + text[i];
			count = 1;
		}
		else
			resultText += text[i];
	}
	return resultText;
}

int StringUtility::getLabelWidth(ax::ui::Text* label)
{
	ax::ui::Text* tempStr = ax::ui::Text::create();
	tempStr->setFontName(label->getFontName());
	tempStr->setFontSize(label->getFontSize());
	tempStr->setString(label->getString());
	return tempStr->getContentSize().width;
}

std::string StringUtility::getDateString(long long time)
{
    return "";
	//return ax::StringUtils::format("%lld", time);
}

int StringUtility::getDifferentTimeZoneHour() {
	return 0;
}

std::string StringUtility::getRemainTimeString(long long remainTime)
{
	int totalSeconds = floor(remainTime / 1000);
	int numSeconds = totalSeconds % 60;
	int totalMinutes = floor(totalSeconds / 60);
	int numMinutes = totalMinutes % 60;
	int totalHour = floor(totalMinutes / 60);
	int numHours = totalHour % 24;
	int totalDay = floor(totalHour / 24);

	std::string keyDay = "DAY_TEXT";
	std::string keyHour = "HOUR_TEXT";
	std::string keyMinute = "MINUTE_TEXT";
	std::string keySecond = "SECOND_TEXT";
	std::string strDays = StringUtility::replaceAll(LanguageMgr::getInstance()->localizedText(keyDay), "@day", totalDay);
	std::string strHours = StringUtility::replaceAll(LocalizedString::to(keyHour), "@hour", numHours);
	std::string strMinutes = StringUtility::replaceAll(LocalizedString::to(keyMinute), "@minute", numMinutes);
	std::string strSeconds = StringUtility::replaceAll(LocalizedString::to(keySecond), "@second", numSeconds);

	std::string remainTimeStr = "";
	bool enoughInfoTime = false;
	if (totalDay > 0) {
		remainTimeStr += strDays;
		enoughInfoTime = true;
	}

	if (numHours > 0) {
		remainTimeStr += strHours;
		enoughInfoTime = true;
	}

	if (numMinutes > 0) {
		remainTimeStr += strMinutes;
		enoughInfoTime = true;
	}

	if (numSeconds > 0) {
		remainTimeStr += strSeconds;
	}
	
	if (remainTimeStr.compare("") == 0) {
		remainTimeStr = LocalizedString::to("TIME_UP");
	}

	return remainTimeStr;
}


std::string StringUtility::md5(std::string input)
{
    return "";
}
std::string char2hex(char dec)
{
	char dig1 = (dec & 0xF0) >> 4;
	char dig2 = (dec & 0x0F);
	if (0 <= dig1 && dig1 <= 9) dig1 += 48;    //0,48inascii
	if (10 <= dig1 && dig1 <= 15) dig1 += 97 - 10; //a,97inascii
	if (0 <= dig2 && dig2 <= 9) dig2 += 48;
	if (10 <= dig2 && dig2 <= 15) dig2 += 97 - 10;

	std::string r;
	r.append(&dig1, 1);
	r.append(&dig2, 1);
	return r;
}

std::string StringUtility::encodeURIComponent(std::string decoded)
{
    std::ostringstream oss;
        std::regex r("[!'\\(\\)*-.0-9A-Za-z_~]");

        for (char &c : decoded)
        {
            if (std::regex_match(std::string(1, c), r))
            {
                oss << c;
            }
            else
            {
                oss << "%" << std::uppercase << std::hex << (0xff & c);
            }
        }
        return oss.str();
}

std::vector<std::string> StringUtility::splitString(std::string s, std::string delimiter) {
	size_t pos = 0;
	std::string token;
	std::vector<std::string> ret;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		ret.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	ret.push_back(s);

	return ret;
}

int StringUtility::randomRange(int min, int max) {
	return std::rand() % (max - min + 1) + min;
}

std::string StringUtility::toStringFixed(double percent, int fixed /* = 2 */) {
	std::string str = std::to_string(percent);
	std::vector<std::string> ar = StringUtility::splitString(str, ".");
	if (ar.size() == 2) {
		std::string ret = "";
		ret += ar[0];

		std::string sss = ".";
		std::string szero = ".";
		for (int i = 0; i < ar[1].length(); i++) {
			if (i >= fixed) break;
			sss += ar[1].at(i);
			szero += "0";
		}
		if (sss.compare(szero) != 0) ret += sss;
		return ret;
	}
	
	return str;
}

std::string StringUtility::getTimeString(long long time)
{
	int timeLeft = floor(time);
	if (timeLeft <= 0) return "0";

	//var day = parseInt(timeLeft / 86400);
	//timeLeft -= day * 86400;
	int hour = (int)(timeLeft / 3600);
	timeLeft -= hour * 3600;
	int minute = (int)(timeLeft / 60);
	timeLeft -= minute * 60;

	std::string str = "";
	str = str + ((hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour)) + ":";
	str = str + ((minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute)) + ":";
	str = str + ((timeLeft < 10) ? "0" + std::to_string(timeLeft) : std::to_string(timeLeft));
	return str;
}

double StringUtility::stringToTimeStamp(std::string time)
{
	std::tm t{};
	std::istringstream ss(time);

	ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");
	if (ss.fail()) {
		throw std::runtime_error{ "failed to parse time string" };
	}
	std::time_t time_stamp = mktime(&t);
	return time_stamp;
}

std::vector<std::string> StringUtility::split(std::string text, std::string sep)
{
	std::vector<std::string> words;
	while (text != "") {
		size_t start = text.find_first_not_of(sep);
		size_t end = text.find_first_of(sep, start);
		words.push_back(text.substr(start, end - start));
		if (end != std::string::npos)
			text = text.substr(end);
		else text = "";
	}
	return words;
}

std::string StringUtility::trim(std::string str)
{
	size_t start = str.find_first_not_of(WHITE_SPACE);
	str = (start == std::string::npos) ? "" : str.substr(start);
	size_t end = str.find_last_not_of(WHITE_SPACE);
	str = (end == std::string::npos) ? "" : str.substr(0, end + 1);
	return str;
}

void StringUtility::breakLabel(ax::ui::Text * label, float width)
{
	label->ignoreContentAdaptWithSize(true);
	std::string str = trim(std::string(label->getString()));
	auto words = split(str, WHITE_SPACE);
	if (words.size() == 0) {
		label->setString("");
		return;
	}
	int curIdx = 0;
	std::string resStr = "";
	std::string curStr = "";
	bool newLine = true;
	while (curIdx < words.size()) {
		if (newLine) {
			curStr = words[curIdx++];
			newLine = false;
		}
		else {
			label->setString(curStr + " " + words[curIdx]);
			if (label->getContentSize().width <= width)
				curStr += " " + words[curIdx++];
			else {
				resStr += curStr + "\n";
				newLine = true;
				curStr = "";
			}
		}
		label->setString(resStr + curStr);
	}
}

std::string StringUtility::customFormatDate(long long millis, std::string format)
{
	/* Description: Describe all tokens can be used.
	 * token:       description:            example:
	 * #YYYY#       4-digit year            1999
	 * #YY#         2-digit year            99
	 * #MMMM#       full month name         February
	 * #MMM#        3-letter month name     Feb
	 * #MM#         2-digit month number    02
	 * #M#          month number            2
	 * #DDDD#       full weekday name       Wednesday
	 * #DDD#        3-letter weekday name   Wed
	 * #DD#         2-digit day number      09
	 * #D#          day number              9
	 * #th#         day ordinal suffix      st
	 * #hhhh#       2-digit 24-based hour   17, 09
	 * #hhh#        24-based hour           17, 9
	 * #hh#         2-digit 12-based hour   12, 01
	 * #h#          12-based hour           12, 1
	 * #mm#         2-digit minute          09, 59
	 * #m#          minute                  9, 59
	 * #ss#         2-digit second          09, 59
	 * #s#          second                  9, 59
	 * #msmsms#     3-digit millis          001, 999
	 * #msms#       2-digit millis          01, 99
	 * #ms#         1-digit millis          1, 9
	 * #ampm#       "am" or "pm"            am, pm
	 * #AMPM#       "AM" or "PM"            AM, PM
	 */

	time_t now = millis / 1000L;
	tm *date = localtime(&now);
	int year = 1900 + date->tm_year;
	int month = 1 + date->tm_mon;
	int day = date->tm_mday;
	int wday = date->tm_wday;
	int hour = date->tm_hour;
	int hour12 = hour > 12 ? hour - 12 : (hour == 0 ? 12 : hour);
	int minute = date->tm_min;
	int second = date->tm_sec;
	int milli = millis % 1000;
	std::string YYYY = std::to_string(year);
	std::string YY = std::to_string(year % 100);
	std::string M = std::to_string(month);
	std::string MM = month < 10 ? "0" : "" + M;
	std::string MMMM = LIST_MONTH_EN[month - 1];
	std::string MMM = MMMM.substr(0, 3);
	std::string D = std::to_string(day);
	std::string DD = day < 10 ? "0" : "" + D;
	std::string DDDD = LIST_WDAY_EN[wday];
	std::string DDD = DDDD.substr(0, 3);
	int dMod = day % 10;
	std::string th = (day >= 10 && day <= 20) ? "th" : (dMod == 1 ? "st" : (dMod == 2 ? "nd" : (dMod == 3 ? "rd" : "th")));
	std::string hhh = std::to_string(hour);
	std::string hhhh = hour < 0 ? "0" : "" + hhh;
	std::string h = std::to_string(hour12);
	std::string hh = hour12 < 10 ? "0" : "" + h;
	std::string ampm = hour < 12 ? "am" : "pm";
	std::string AMPM = toUpperCase(ampm);
	std::string m = std::to_string(minute);
	std::string mm = minute < 10 ? "0" : "" + m;
	std::string s = std::to_string(second);
	std::string ss = second < 10 ? "0" : "" + s;
	std::string msmsms = std::to_string(milli);
	std::string msms = std::to_string(milli / 10);
	std::string ms = std::to_string(milli / 100);

	format = replaceAll(format, "#YYYY#", YYYY);
	format = replaceAll(format, "#YY#", YY);
	format = replaceAll(format, "#MMMM#", MMMM);
	format = replaceAll(format, "#MMM#", MMM);
	format = replaceAll(format, "#MM#", MM);
	format = replaceAll(format, "#M#", M);
	format = replaceAll(format, "#DDDD#", DDDD);
	format = replaceAll(format, "#DDD#", DDD);
	format = replaceAll(format, "#DD#", DD);
	format = replaceAll(format, "#D#", D);
	format = replaceAll(format, "#th#", th);
	format = replaceAll(format, "#hhhh#", hhhh);
	format = replaceAll(format, "#hhh#", hhh);
	format = replaceAll(format, "#hh#", hh);
	format = replaceAll(format, "#h#", h);
	format = replaceAll(format, "#mm#", mm);
	format = replaceAll(format, "#m#", m);
	format = replaceAll(format, "#ss#", ss);
	format = replaceAll(format, "#s#", s);
	format = replaceAll(format, "#msmsms#", msmsms);
	format = replaceAll(format, "#msms#", msms);
	format = replaceAll(format, "#ms#", ms);
	format = replaceAll(format, "#AMPM#", AMPM);
	format = replaceAll(format, "#ampm#", ampm);

	return format;
}

std::string StringUtility::toUpperCase(std::string str)
{
	for (auto& c : str) {
		c = toupper(c);
	}
	return str;
}

std::string StringUtility::toLowerCase(std::string str)
{
	for (auto& c : str) {
		c = tolower(c);
	}
	return str;
}

std::string StringUtility::toCamelCase(std::string str)
{
	bool newword = true;
	for (auto& c : str) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' || c <= 'Z')) {
			if (newword) {
				newword = false;
				c = toupper(c);
			}
			else c = tolower(c);
		}
		else newword = true;
	}
	return str;
}
//
//ax::Color4B StringUtility::getColor4B(std::string hex)
//{
//	if (std::regex_match(hex, std::regex("#?[0-9a-fA-F]{6}"))) {
//		if (hex[0] == '#') hex = hex.substr(1);
//		unsigned char r = std::stoi(hex.substr(0, 2), nullptr, 16);
//		unsigned char g = std::stoi(hex.substr(2, 2), nullptr, 16);
//		unsigned char b = std::stoi(hex.substr(4, 2), nullptr, 16);
//		return ax::Color4B(r, g, b);
//	}
//	return ax::Color4B::BLACK;
//}
//
//ax::Color4B StringUtility::getColor4B(std::string hex)
//{
//	return ax::Color4B(getColor4B(hex));
//}

const std::vector<std::string> StringUtility::LIST_MONTH_ES = {
	"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

const std::vector<std::string> StringUtility::LIST_MONTH_EN = {
	"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

const std::vector<std::string> StringUtility::LIST_WDAY_EN = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

const std::string StringUtility::WHITE_SPACE = " \n\r\t\f\v";
