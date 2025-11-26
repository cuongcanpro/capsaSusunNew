#ifndef CStringUtils_h__
#define CStringUtils_h__
#include <string>
#include <vector>
#include <sstream>
#include <map>

class CStringUtils
{
public:
	//example replace(std::string,"$name","somename")
	static bool replace(std::string& str,const std::string& from, const std::string& to);
	static bool replace(std::string& str,const std::string& from, int to);
	static bool replaceAll(std::string& str,const std::string& from, const std::string& to);
	static bool replaceAll(std::string& str,const std::string& from, int to);
	static bool replaceAll(std::string& str,const std::string& from, long long to);
    static bool replaceAll(std::string& str,const std::string& from, double to);
	static bool split(const std::string& str, char delim, std::vector<std::string> &elems);
	static std::map<std::string,int> populateMap(const std::string& str);
	bool StrToWstr(std::wstring &ws, const std::string &s );
	static std::string toString(int i);
	static std::string xOrString(std::string str);
	static std::string convertToString(double money);
	static std::string getNumberConvert(double number, double div);
	static const char * getConstChar(std::string text);
	static inline void trim(std::string& s, const std::string& delimiters = " " )
	{
		s.erase( s.find_last_not_of( delimiters ) + 1 ).erase( 0, s.erase( s.find_last_not_of( delimiters ) + 1 ).find_first_not_of( delimiters ) );
	}

	static std::string cut(std::string& s,int length)
	{
		if (s.length() > length)
		{
			int count = length;
			for (int i = length;i>=0;i++)
			{
				int tmp = s.at(i);
				if (tmp >= 0 && tmp < 128)
				{
					count = i;
					break;
				}
			}
			std::string str = s.substr(0,count);
			str.append("...");
			return str;
		}
		return s;
	}
	
};

#endif // StringUtils_h__
