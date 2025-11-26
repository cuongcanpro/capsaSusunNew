#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <string>
#include <vector>
#include "axmol.h"
using namespace std;
class Utility
{
public:
	Utility(void);
	~Utility(void);
	string pointNumber(double);
	string convertIntLongToString(double num);
	string getNameImageByTypeItem(string type);
	int randomBetween(int,int);
	string convertToStringTime(long t);
	string convertToStringTime2(int t);
	static void xOrData(unsigned char *data, int len);
	string replaceString(string rootStr,string strReplace,string strTo);
	bool checkMaintain();
	bool parseMaintain(string data);
	static vector<string> split(const string& s, const string& delim, const bool keep_empty = true);
};

#endif
