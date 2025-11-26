#include "CStringUtils.h"
#include <stdlib.h>
#include "axmol.h"
#include <math.h>
bool CStringUtils::replace(std::string& str,const std::string& from, const std::string& to){
	if(from.empty())
		return false;
	size_t start_pos = str.find(from);
	if(start_pos == std::string::npos)
		return false;
	str.replace(start_pos,from.length(),to);
	return true;
}
bool CStringUtils::replace(std::string& str,const std::string& from, int to){
	char s_to[12];
	sprintf(s_to, "%d",to);
	return replace(str,from,s_to);
}
bool CStringUtils::replaceAll(std::string& str,const std::string& from, const std::string& to){
	if(from.empty())
		return false;
	size_t start_pos = 0;
	while((start_pos = str.find(from,start_pos))!= std::string::npos){
		str.replace(start_pos,from.length(),to);
		start_pos +=to.length();
	}
	return true;
}
bool CStringUtils::replaceAll(std::string& str,const std::string& from, int to){
	char s_to[12];
    sprintf(s_to, "%d",to);
	return replaceAll(str,from, std::string(s_to));
}
bool CStringUtils::replaceAll(std::string& str,const std::string& from, long long to){
	char s_to[30];
    sprintf(s_to, "%",to);
	return replaceAll(str,from, std::string(s_to));
}

bool CStringUtils::replaceAll(std::string& str,const std::string& from, double to){
	char s_to[30];
    sprintf(s_to, "%",to);
	return replaceAll(str,from, std::string(s_to));
}

bool CStringUtils::StrToWstr(std::wstring &ws, const std::string &s ){
	std::wstring wsTmp(s.begin(),s.end());
	ws = wsTmp;
	return true;
}

bool CStringUtils::split(const std::string& str, char delim, std::vector<std::string>& elems)
{
	if (str.length() <= 1) return false;
	std::stringstream ss(str);
	std::string item;
	while(std::getline(ss, item, delim)){
		elems.push_back(item);
	}
	return true;
}

std::map<std::string,int> CStringUtils::populateMap(const std::string& str)
{
	std::map<std::string,int> returnMap;
	std::vector<std::string> tokens;
	std::string key;
	int value;

	CStringUtils::split(str, ';', tokens);
	for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		std::vector<std::string> innerToks;
		CStringUtils::split(*it, ':', innerToks);
		key = innerToks[0];
		value = atoi(innerToks[1].c_str());
		returnMap.insert(std::pair<std::string,int>(key, value));
	}
	return returnMap;
}

std::string CStringUtils::toString(int i){
	char s_to[12];
	sprintf(s_to, "%d",i);
	return std::string(s_to);
}
std::string CStringUtils::xOrString(std::string str)
{
	int length = strlen(str.c_str());
	if(length ==0)
		return str;
	
	std::string key = "adstrtr";
    std::string buf = "";
	int keySize = 7;
	int j = 0;
	for (int i = 0; i < length; i++)
	{
		buf += str[i]^key[j];
		j++;
		if (j==keySize)
		{
			j = 0;
		}

	}
	return std::string(buf);
}

std::string CStringUtils::getNumberConvert(double number, double div) {
	int a = (int) (number / (div / 100));

	int b = (int) (a / 100);

	a = a - b * 100;
	if (a == 0) {
		return toString(b);
	} else {
		if (a>9) {
			if (a%10 == 0) {
				std::string result = "%num1%.%num2%";
				replaceAll(result, "%num1%", b);
				replaceAll(result, "%num2%", a/10);
				return result;
			}else {
				std::string result = "%num1%.%num2%";
				replaceAll(result, "%num1%", b);
				replaceAll(result, "%num2%", a);
				return result;
			}
		}else {
			std::string result = "%num1%.0%num2%";
			replaceAll(result, "%num1%", b);
			replaceAll(result, "%num2%", a);
			return result;
		}

	}
}

std::string CStringUtils::convertToString(double money) {
	double f;
	std::string shortNum ;

	if(money < 0)
		shortNum = "-";
	money = fabs(money);

	if (money >= 1000000000) {

		return shortNum + getNumberConvert(money, 1000000000) + "B";

	} else if (money >= 1000000) {
		return shortNum + getNumberConvert(money, 1000000) + "M";
	} else if (money >= 1000) {
		return shortNum + getNumberConvert(money, 1000) + "K";
	} else {
		shortNum = shortNum + toString(money);
	}
	return shortNum;
}

const char * CStringUtils::getConstChar( std::string text )
{
	return text.c_str();
}

