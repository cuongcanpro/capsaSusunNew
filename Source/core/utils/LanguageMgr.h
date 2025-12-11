#ifndef LanguageMgr_h__
#define LanguageMgr_h__
#include <string>

#include <map>
#include <string>
#include <vector>

#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
using namespace ax;

class LocalizedFile {
public:
	LocalizedFile();
	~LocalizedFile();
public:
	void loadLocalized(std::string des);
	std::string getString(std::string key);
public:
	std::map<std::string, std::string> localizedStrings;
};

class LocalizedImage {
public:
	LocalizedImage();
	~LocalizedImage();
public:
	std::string getDir(std::string key);
	void setPathLanguage(std::string path);
	void loadLocalized(std::string path);
public:
	std::map<std::string, std::string> localizedStrings;
	std::string patchLanguage;
};

#define languageMgr LanguageMgr::getInstance()

class LanguageMgr {
public:
	struct Lang {
		Lang(std::string path_, std::string lang_) :path(path_), lang(lang_) {

		}
		std::string path;
		std::string lang;
	};
public:
	LanguageMgr();
	~LanguageMgr();
	static LanguageMgr* getInstance();
public:
	void init();
	void addLanguage(std::string lang);
	void addLocalizedText(std::string path, std::string lang = "");
	void changeLanguage(std::string lang);
	bool checkCurrentLanguage(std::string lang);
	bool validateLanguage(std::string lang);
	std::string localizedTextPath(std::string lang);
	std::string localizedImagePath(std::string lang);
	std::string localizedText(std::string key);
	std::string localizeImage(std::string res);
	std::string getLanguageDir(std::string dir);
	std::string getConfig(std::string key);
	void saveCurrentLanguage();
	std::string loadCurrentLanguage();
public:
	static LanguageMgr* _instance;
	std::string cLang;
	bool hasInit;
    bool isVietnam;
	LocalizedFile* mTextConfig;
	std::vector<Lang> queueAddLocalizeds;
	std::vector<std::string> mLanguages;
	std::map<std::string, LocalizedFile*> mTextLocalized;
	std::map<std::string, LocalizedImage*> mImageLocalized;
};

class LocalizedString {
public:
	static std::string to(std::string key);
	static void add(std::string path);
	static void addLang(std::string path, std::string lang);
	static std::string config(std::string key);
};

class LocalizedSprite
{
public:
	static std::string getDir(std::string key);

};
#endif // LanguageMgr_h__
