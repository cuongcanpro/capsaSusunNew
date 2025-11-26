#include "Utility.h"
#include <sstream>
#include <iosfwd>
#include <fstream>
#include <string>
#include <iostream>
#include "axmol.h"
#include "ScreenUtils.h"
#include "../GlobalVar.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

Utility::Utility(void)
{
}


Utility::~Utility(void)
{
}

string Utility::pointNumber(double num)
{
	string str="";
	string temp;
	//temp=convertIntLongToString(num);
	//
	//if(num<1000)
	//{
	//	return temp;
	//}
	//int n=temp.length();
	//string s;
	//int count=0;
	//for (int i= n-1;i>=0 ;i--)
	//{
	//	s=temp.substr(i,1);
	//	if(count>=3)
	//	{
	//		count=0;
	//		str="."+str;
	//	}

	//	str=s+str;
	//	count++;
	//}

	double num1 = fabs(num);
	int count = 0;

	if(num == 0)
		return "0";

	while(num1 > 0)
	{
		double save = num1;
		num1 = floor(num1 / 1000);
		int result = save - num1 * 1000;

		string next = "";
		if(num1 > 0)
		{
			if(result >= 100)
			{
				next = convertIntLongToString(result);
			}
			else if(result >= 10)
			{
				next = "0" + convertIntLongToString(result);
			}
			else if(result > 0)
			{

				next = "00" + convertIntLongToString(result);
			}
			else
			{
				next = "000";
			}
		}
		else
		{
			next = convertIntLongToString(result);
		}
		
		if(str.length() == 0)
			str = next + str;
		else
			str = next + "." + str;

		count++;
	}

	if(num < 0)
		str = "-" + str;

	return str;


}

string Utility::convertIntLongToString(double num)
{
	stringstream strstream;
	strstream<<num;
	return strstream.str();
}

string Utility::getNameImageByTypeItem(string type)
{
	return type+".png";

}


int Utility::randomBetween(int a,int b)
{
	return rand()%b+a;
}

std::string Utility::convertToStringTime( long t )
{

	int second = t % 60;
	int minute = t / 60;
	int hour= minute / 60;
	minute = minute % 60;
	int day = hour / 24;
	hour = hour % 24;

	string minuteStr =convertIntLongToString(minute);
	string secondStr =convertIntLongToString(second);
	string hourStr=convertIntLongToString(hour);
	if (minute < 10) minuteStr = "0" + minuteStr;
	if (second < 10) secondStr = "0" + secondStr;

	if (day > 0)
	{
		//var n:int = (t * 10) / (60 * 60 * 24);
		//var f:Number = n / 10;
		//return f.toString() + " ngày";
		hour += day * 24;
	}
	if (hour > 0)
	{
		return hourStr + ":" + minuteStr + ":" + secondStr;
	}
	if (minute > 0)
	{
		return minuteStr + ":" + secondStr;
	}
	if (second > 0)
	{
		return minuteStr + ":" + secondStr;
	}

	return "0";
}

std::string Utility::convertToStringTime2( int t )
{
	return "";
}

void Utility::xOrData( unsigned char *data, int len )
{
	string key = "gsnfarmeryhehe";
	int keySize = key.size();
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		data[i] ^= key[j];
		j++;
		if (j==keySize)
		{
			j = 0;
		}
	}
}	

std::string Utility::replaceString( string rootStr,string strReplace,string strTo )
{
	string s="";
	std::size_t f=rootStr.find(strReplace);
	if(f!=std::string::npos)
	{
		s=rootStr.replace(f,strReplace.size(),strTo);
	}
	return s;
}
size_t curl_write(void *ptr, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)ptr,size*nmemb);
	return size*nmemb;
} 
bool Utility::checkMaintain()
{
	//string link = "http://farmery.vn/gate.php";
	//if(RELEASE_GAME)
	//{
	//	link = "http://farmery.vn/gate.php";
	//}else
	//{
	//	link = "http://120.138.76.40/gate.php";
	//}
	//char buf[200];
	//sprintf(buf,"%s?ver=%d&store=%d",link.c_str(),GameConfig::shared()->getCurrentVersion(),GameConfig::shared()->getStoreType());
	//CURL *curl = curl_easy_init();
	//string readBuffer;

	//int32_t code;

	//code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
	//if (code != CURLE_OK) {
	//	return false;
	//}
	//code = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);
	//if (code != CURLE_OK) {
	//	return false;
	//}

	//if(curl) {

	//	// Open up writable temp graphic.
	//	curl_easy_setopt(curl, CURLOPT_URL, buf);
	//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
	//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); 

	//	// Write the image to the file.
	//	int result = curl_easy_perform(curl);
	//	if(result){
	//		return false;
	//	}
	//	else
	//	{
	//		return parseMaintain(readBuffer);
	//	}
	//}
	return false;
}

bool Utility::parseMaintain(string data)
{
	//rapidjson::Document document;
	//document.Parse<0>(data.c_str());
	//if(document.HasParseError())
	//{
	//	CCLog("Parse maintain Error: %s",data.c_str());
	//	return false;
	//}
	//string content = "";
	//int result = 0;
	//result = document["ver"].GetInt();
	//content = document["txt"].GetString();
	//if (result > 0)
	//{
	//	CDialog::shared()->showDialogMaintain(content.c_str());
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	return false;
}

vector<string> Utility::split(const string& s, const string& delim, const bool keep_empty) {
		vector<string> result;
		if (delim.empty()) {
			result.push_back(s);
			return result;
		}
		string::const_iterator substart = s.begin(), subend;
		while (true) {
			subend = search(substart, s.end(), delim.begin(), delim.end());
			string temp(substart, subend);
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
