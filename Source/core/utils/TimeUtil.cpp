#include "TimeUtil.h"
#include "StringUtility.h"
#include <ctime>

long long TimeUtil::getCurrentTimeMiliseconds() {
	return ax::utils::getTimeInMilliseconds();
}

long long TimeUtil::getCurrentTimeSeconds() {
	return (long long)(ax::utils::getTimeInMilliseconds() / 1000);
}

std::string TimeUtil::getCurrentDate(std::string format) {

	std::string str = "dd/mm/yyyy";
	if (!format.empty()) {
		str = format;
	}
	time_t now = std::time(0);
	tm *lm = std::localtime(&now);

	std::string h = std::to_string(lm->tm_hour);
	std::string hh = lm->tm_hour > 9 ? h : ("0" + h);
	if (str.find("hh") != std::string::npos)
		str = StringUtility::replaceAll(str, "hh", hh);
	else
		str = StringUtility::replaceAll(str, "h", h);

	std::string ms = std::to_string(lm->tm_min);
	std::string mms = lm->tm_min > 9 ? ms : ("0" + ms);
	if (str.find("mms") != std::string::npos)
		str = StringUtility::replaceAll(str, "mms", mms);
	else
		str = StringUtility::replaceAll(str, "ms", ms);

	std::string s = std::to_string(lm->tm_sec);
	std::string ss = lm->tm_sec > 9 ? s : ("0" + s);
	if (str.find("ss") != std::string::npos)
		str = StringUtility::replaceAll(str, "ss", ss);
	else
		str = StringUtility::replaceAll(str, "s", s);

	std::string d = std::to_string(lm->tm_mday);
	std::string dd = lm->tm_mday > 9 ? d : ("0" + d);
	if(str.find("dd") != std::string::npos)
		str = StringUtility::replaceAll(str, "dd", dd);
	else
		str = StringUtility::replaceAll(str, "d", d);

	std::string m = std::to_string(lm->tm_mon + 1);
	std::string mm = (lm->tm_mon + 1) > 9 ? m : ("0" + m);
	if(str.find("mm") != std::string::npos)
		str = StringUtility::replaceAll(str, "mm", mm);
	else 
		str = StringUtility::replaceAll(str, "m", m);

	std::string yyyy = std::to_string(1900 + lm->tm_year); // 1900 + 121 = 2021
	std::string yy = std::to_string(lm->tm_year - 100);	// 121 - 100 = 21

	if (str.find("yyyy") != std::string::npos)
		str = StringUtility::replaceAll(str, "yyyy", yyyy);
	else
		str = StringUtility::replaceAll(str, "yy", yy);

	return str;
}

long long TimeUtil::convertDateToTimestamp(int dd, int mm, int yyyy) {
	struct tm  tm;
	time_t rawtime;
	time(&rawtime);
	tm = *localtime(&rawtime);
	tm.tm_year = yyyy - 1900;
	tm.tm_mon = mm - 1;
	tm.tm_mday = dd;
	mktime(&tm);
	
	return mktime(&tm);
}

long long TimeUtil::convertDateToTimestamp(std::string date,std::string sp) {
	std::vector<std::string> ar = StringUtility::splitString(date, sp);
	return TimeUtil::convertDateToTimestamp(std::stoi(ar[0]), std::stoi(ar[1]), std::stoi(ar[2]));
}