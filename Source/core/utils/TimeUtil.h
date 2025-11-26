#ifndef TimeUtil_h__
#define TimeUtil_h__

#include "axmol.h"

static const std::string DATE_SEPERATE = "-";

class TimeUtil {

public:
	static long long getCurrentTimeMiliseconds();
	static long long getCurrentTimeSeconds();
	static std::string getCurrentDate(std::string format = "");

	static long long convertDateToTimestamp(std::string date, std::string sp = DATE_SEPERATE);
	static long long convertDateToTimestamp(int dd, int mm, int yyyy);
};
#endif // TimeUtil_h__
