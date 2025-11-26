#include "GameMgr.h"

#include "gameTienlen/InGameMgr.h"
#include <ctime>
#include <chrono>
#include <iomanip>
#include "gameTienlen/ui/LoadingScene.h"
#include "core/utils/HttpUtils.h"
#include "Game/Utility/JNIUtils.h"
#include "gameTienlen/ui/LobbyScene.h"
#include "gameTienlen/ui/BoardScene.h"
#include "gameTala/TalaInGameMgr.h"
#include "gameTala/ui/TalaLobbyScene.h"
#include "gameTienlen/logic/GameLogic.h"
#include "gameTala/logic/TalaGameLogic.h"
#include <string>
#include "gameBinh/BinhInGameMgr.h"
#include "gameBinh/ui/BinhLobbyScene.h"
#include "gameBinh/ui/BinhHelpGUI.h"



GameMgr::GameMgr()
{

}

GameMgr::~GameMgr()
{

}

void GameMgr::onReward(int num)
{
	Node* scene = sceneMgr->getMainLayer();
	if (scene) {
		BoardScene* lobby = dynamic_cast<BoardScene*>(scene);
		if (lobby) {
			GameLogic::getInstance()->onReward(num);
		}
		else {
			TalaScene* lobby = dynamic_cast<TalaScene*>(scene);
			if (lobby)
				TalaGameLogic::getInstance()->onReward(num);
			else
				BinhGameLogic::getInstance()->onReward(num);
		}
	}
}

bool GameMgr::isIOS()
{
#if(AX_TARGET_PLATFORM==AX_PLATFORM_IOS)
	return true;
#else
	return false;
#endif
}

void GameMgr::endGame()
{
#if(AX_TARGET_PLATFORM==AX_PLATFORM_ANDROID)
    Director::getInstance()->end();
#else
	exit(0);
#endif
}

void GameMgr::checkCanPlayEffect()
{
	if (gameMgr->canPlayEffect == 2) {
		gameMgr->canPlayEffect = 1;
		UserDefault::getInstance()->setIntegerForKey("canPlayEffect", 1);
		UserDefault::getInstance()->flush();
	}
}

void GameMgr::initAds() {
    if (isInitAds)
        return;
    isInitAds = true;
    if (gameMgr->useAds)
	    JNIUtils::initAds(gameMgr->adBannerUnit.c_str(), gameMgr->adInterUnit.c_str(), gameMgr->adRewardUnit.c_str(), 1, 1);
}

void GameMgr::openBinhScene() {
    binhInGameMgr->openBoardScene();
}

GameMgr* GameMgr::getInstance()
{
	if (!_instance) {
		_instance = new GameMgr();
	}
	return _instance;
}

void GameMgr::startGame() {
	// need init before loading
//	typeTop = 0;
        isIndo      = false;
        isInitAds   = false;
        useAds      = 1;
	need_update = 0;
	versionGame = TALA_OLD;
	fakeApp = 0;
	countryName = UserDefault::getInstance()->getStringForKey("countryName", "");
	//getCountry();
	//getVersion();
	//getIdAds();
	currentPosture = UserDefault::getInstance()->getIntegerForKey("currentPosture", 0);

	waitCreateName = false;
        deviceId       = "JNIUtils::getDeviceId()";

	AXLOGD("Device Id %s ", deviceId.c_str());
        typeCard            = 0;
	useMove = UserDefault::getInstance()->getBoolForKey("useMove", false);
	namePlayer = UserDefault::getInstance()->getStringForKey("namePlayer", "");
	gold = UserDefault::getInstance()->getIntegerForKey("myGold", 30000);
	winCount = UserDefault::getInstance()->getIntegerForKey("winCount", 0);
	lostCount = UserDefault::getInstance()->getIntegerForKey("lostCount", 0);
	int level = getLevel(winCount);
	int currentIdAvatar = level;
	if (currentIdAvatar > 19)
		currentIdAvatar = 19;
	idAvatar = UserDefault::getInstance()->getIntegerForKey("idAvatar", currentIdAvatar);

	goldTala = UserDefault::getInstance()->getIntegerForKey("myGoldTala", 30000);
	winCountTala = UserDefault::getInstance()->getIntegerForKey("winCountTala", 0);
	lostCountTala = UserDefault::getInstance()->getIntegerForKey("lostCountTala", 0);
	level = getLevel(winCountTala);
	currentIdAvatar = level;
	if (currentIdAvatar > 19)
		currentIdAvatar = 19;
	idAvatarTala = UserDefault::getInstance()->getIntegerForKey("idAvatarTala", currentIdAvatar);

	goldBinh = UserDefault::getInstance()->getIntegerForKey("myGoldBinh", 30000);
	winCountBinh = UserDefault::getInstance()->getIntegerForKey("winCountBinh", 0);
	lostCountBinh = UserDefault::getInstance()->getIntegerForKey("lostCountBinh", 0);
	level = getLevel(winCountBinh);
	currentIdAvatar = level;
	if (currentIdAvatar > 19)
		currentIdAvatar = 19;
	idAvatarTala = UserDefault::getInstance()->getIntegerForKey("idAvatarBinh", currentIdAvatar);
	useGuiAt = UserDefault::getInstance()->getBoolForKey("useGuiAt", false);
	countHelpAt = UserDefault::getInstance()->getIntegerForKey("countHelpAt", 0);
	canPlayEffect = UserDefault::getInstance()->getIntegerForKey("canPlayEffect", 0);


	for (int i = 0; i < 5; i++) {
		arrayOldTop[i] = UserDefault::getInstance()->getIntegerForKey(("top" + to_string(i)).c_str(), -1);
	}
	if (goldTala > 100000) {
		JNIUtils::sendEvent("gold_tala_big", to_string(goldTala).c_str());
	}
	else {
		JNIUtils::sendEvent("gold_tala_small", to_string(goldTala).c_str());
	}
	if (gold > 100000) {
		JNIUtils::sendEvent("gold_tienlen_big", to_string(gold).c_str());
	}
	else {
		JNIUtils::sendEvent("gold_tienlen_small", to_string(gold).c_str());
	}

	//JNIUtils::sendEvent(("level_" + to_string(level)).c_str(), to_string(winCount).c_str());

	getMyTop(TOP_WIN);
	getMyTop(TOP_GOLD);
	//namePlayer = "";
	//gold = 0;
	//winCount = 0;
	//if (namePlayer == "") {
	//	// can kiem tra xem da co trong Top chua
	//	getMyTop(TOP_WIN);
	//}
	addSearchPath();
	initPlugin();
	languageMgr->init();
	if (languageMgr->cLang.compare(LANGUAGE_VN) == 0) {
		JNIUtils::sendEvent("lang_vn", "1");
	}
	else {
		JNIUtils::sendEvent("lang_en", "1");
	}
	requestGameServices();
	// open loading scene
	//loginMgr->openLoading();
	inGameMgr->init();
	//sceneMgr->openScene(LoadingScene::className);

	//getTop(0);
    //inGameMgr->openBoardScene(true);

	//talaInGameMgr->init();
	//talaInGameMgr->openBoardScene(true);

	binhInGameMgr->init();
	//binhInGameMgr->openBoardScene();

}

void GameMgr::startLoading() {
	// init modules
	loadCache();
	preloadGUI();

	// modules

	// read services
	//requestGameServices();
	//responseGameServices(true, "");
	//loginMgr->openLogin();
	//inGameMgr->openBoardScene();
}


void GameMgr::initPlugin()
{

}

void GameMgr::addSearchPath()
{
	FileUtils::getInstance()->addSearchPath("common");
	FileUtils::getInstance()->addSearchPath("Board");
	FileUtils::getInstance()->addSearchPath("Lobby");
	FileUtils::getInstance()->addSearchPath("Armatures");
}

void GameMgr::loadCache()
{

}

void GameMgr::preloadGUI() {

}

void GameMgr::requestGameServices() {


}

void GameMgr::responseGameServices(bool isSuccess, std::string data) {
	AXLOGD("Data %d : %s", isSuccess ? 1 : 0, data.c_str());

	rapidjson::Document doc;
	doc.Parse<0>(data.c_str());
	if (!doc.HasParseError()) {
		int update = 0;
		if (doc.HasMember("update"))
			update = doc["update"].GetInt();

		std::string message = "";
		if (doc.HasMember("update_message"))
			message = doc["update_message"].GetString();

		std::string url = "";
		if (doc.HasMember("url_update"))
			url = doc["url_update"].GetString();


	}
	else {
		findCountryID();
	}
}

void GameMgr::saveTimestampServer(long long time) {
	offsetTimeServer = TimeUtil::getCurrentTimeMiliseconds() - time;
}

long long GameMgr::getTimestampServer() {
	return TimeUtil::getCurrentTimeMiliseconds() - offsetTimeServer;
}

void GameMgr::setOffsetTimeZone() {
	if (Config::ENABLE_CHEAT) {
		offsetTimeZone = -7 * 60;
	}
	else {
		offsetTimeZone = 6 * 60;
	}
}

int GameMgr::getOffsetTimeServer() {
	return offsetTimeServer;
}

int GameMgr::getOffsetTimeZone() {
	return offsetTimeZone;
}

bool GameMgr::isInBoardScene() {
	return false;
}

void GameMgr::onGameShow() {

}

void GameMgr::onGameHide() {

}

void GameMgr::onEnterScene() {

}

void GameMgr::onLobbyEnter() {

}

void GameMgr::onLoginEnter() {

}

void GameMgr::onUpdateScene(float dt) {

}

//country
void GameMgr::findCountryID() {

}

std::string GameMgr::getCountryID(bool isRealCountry) {
// 	if (CheatCenter.isCheatCountry() && (isRealCountry != true)) {
// 		return CheatCenter.COUNTRY_ID;
// 	}
// 	else {
		if (country.countryID.empty()) country.countryID = getCountryAppName();

		if (country.countryID.length() > 2) {
			country.countryID = country.countryID.substr(0, 2);
		}
		return country.countryID;
//	}
}

std::string GameMgr::getCountryIdShop() {
	return getCountryID();
}

std::string GameMgr::getCountryAppName() {
	return "mx";
}

bool GameMgr::checkIsCountry(std::string id) {
	if (country.countryID.compare(id)) return true;
	return false;
}

SettingConfig GameMgr::getSetting() {
	setting.vibrate = StorageUtil::getBool("_game_setting_vibrate_");
	setting.sound = StorageUtil::getBool("_game_setting_sound_", true);
	setting.acceptInvite = StorageUtil::getBool("_game_setting_invite_");
	setting.acceptFriend = StorageUtil::getBool("_game_setting_friend_");
	setting.isVietnam = StorageUtil::getBool("_game_setting_vietnam_", true);
	if (gameMgr->setting.isVietnam) {
		languageMgr->changeLanguage(LANGUAGE_VN);
	}
	else {
		languageMgr->changeLanguage(LANGUAGE_EN);
	}
	return setting;
}

bool GameMgr::changeVibrate(int state) {
	if (state == -1)
		setting.vibrate = !setting.vibrate;
	else
		setting.vibrate = (state == 1);

	StorageUtil::setBool("_game_setting_vibrate_", setting.vibrate);
	return setting.vibrate;
}

bool GameMgr::changeSound(int state) {
	if (state == -1)
		setting.sound = !setting.sound;
	else
		setting.sound = (state == 1);
	AXLOGD("sound setting %d", setting.sound ? 1 : 0);

	StorageUtil::setBool("_game_setting_sound_", setting.sound);
	return setting.sound;
}

bool GameMgr::changeInvite(int state) {
	if (state == -1)
		setting.acceptInvite = !setting.acceptInvite;
	else
		setting.acceptInvite = (state == 1);

	StorageUtil::setBool("_game_setting_invite_", setting.acceptInvite);
	return setting.acceptInvite;
}

bool GameMgr::changeFriend(int state) {
	if (state == -1)
		setting.acceptFriend = !setting.acceptFriend;
	else
		setting.acceptFriend = (state == 1);

	StorageUtil::setBool("_game_setting_friend_", setting.acceptFriend);
	return setting.acceptFriend;
}

bool GameMgr::changeMusic(int state) {
	if (state == -1)
		setting.music = !setting.music;
	else
		setting.music = (state == 1);

	StorageUtil::setBool("_game_setting_music_", setting.music);
	return setting.music;
}

std::string GameMgr::getAppVersion() {
	return "1000";
}

std::string GameMgr::getInstallSource() {
	return "";
}

std::string GameMgr::getDeviceID() {
	std::string ret = "";
	if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
		return to_string(AXRANDOM_0_1() * 100000l);
	if (Config::ENABLE_CHEAT) {
		ret = StorageUtil::getString(Config::CHEAT_SAVE_DEVICE_ID, "");
	}
	if (ret.empty()) {
		//ret = JNI::getDeviceID();
	}
	return ret;
}

std::string GameMgr::getInstallDate() {
	//std::string uId = std::to_string(userMgr->getUserInfo()->getUserID());
	std::string user_key = "user_install_date";
	std::string sData = StorageUtil::getString(user_key, "");
	if (sData.empty()) {
		sData = TimeUtil::getCurrentDate();
		StorageUtil::setString(user_key, sData);
	}
	return sData;
}

std::string GameMgr::getLanguage() {
	std::string lang = StorageUtil::getString("Language");
	return lang;
}

bool GameMgr::checkLanguage(std::string slang) {
	std::string lang = getLanguage();
	if (lang.compare(slang) != 0) return true;
	return false;
}

int GameMgr::getPlatform() {
	return CONSTANT_PLATFORM_IOS;
}


void GameMgr::pushMyData()
{
	Node* node = sceneMgr->getMainLayer();
	LobbyScene* board = dynamic_cast<LobbyScene*>(node);
	if (haveTop() == false) {
		if (board) {
			getTop(TOP_WIN);
			getTop(TOP_GOLD);
		}
		else {
			TalaLobbyScene* board1 = dynamic_cast<TalaLobbyScene*>(node);
			if (board1)
				getTop(TOP_TALA);
			else {
				getTop(TOP_BINH_GOLD);
				getTop(TOP_BINH_WIN);
			}
		}
	}
	else {
		if (board) {
			insertTop(TOP_WIN, namePlayer, to_string(winCount));
			insertTop(TOP_GOLD, namePlayer, to_string(gold));
		}
		else {
			TalaLobbyScene* board1 = dynamic_cast<TalaLobbyScene*>(node);
			if (board1)
				insertTop(TOP_TALA, namePlayer, to_string(winCountTala));
			else {
				insertTop(TOP_BINH_WIN, namePlayer, to_string(winCountBinh));
				insertTop(TOP_BINH_GOLD, namePlayer, to_string(goldBinh));
			}
		}
	}
}

void GameMgr::insertTop(int type, string name, string score)
{
	string urlRequest1 = "https://news.beansofts.com/?a=2000&sa=1";
	urlRequest1 = urlRequest1 + "&id=" + deviceId;
	urlRequest1 = urlRequest1 + "&name=" + name;
	urlRequest1 = urlRequest1 + "&score=" + score;
	urlRequest1 = urlRequest1 + "&gid=" + getGameId(type);
	string data1 = "";
	//AXLOGD("Request insertTop %s ", urlRequest1.c_str());
	HttpUtils::addRequestPost(urlRequest1, data1, [this](bool isSuccess, std::string data) {
		AXLOGD("Data Insert Top %s ", data.c_str());
		rapidjson::Document doc;
		doc.Parse<0>(data.c_str());
		if (!doc.HasParseError() && doc.IsObject()) {
			string status = "";
			if (doc.HasMember("status"))
				status = doc["status"].GetString();
			if (status.compare("OK") == 0) {
				string gid = "";
				if (doc.HasMember("gid"))
					gid = doc["gid"].GetString();
				int topCode = getGameCode(gid);
				gameMgr->getTop(topCode);
				gameMgr->getMyTop(topCode);
				if (gameMgr->waitCreateName) {
					gameMgr->waitCreateName = false;
					sceneMgr->showOkDialogWithAction("You have just created account successfully!", [this](int btnId) {
						/*Node* scene = sceneMgr->getMainLayer();
						BoardScene* board = dynamic_cast<BoardScene*>(scene);
						if (board) {
							GUITop* gui = (GUITop*)sceneMgr->openGUI(GUITop::className, 200, 200);
						}*/
					});
				}
				else {
					/*GUITop* guiTop = (GUITop*)sceneMgr->getGUIByClassName(GUITop::className);
					if (guiTop != nullptr) {
						guiTop->insertDone();
					}*/

				}
			}
		}
	});
}

void GameMgr::getTop(int type)
{

}


void GameMgr::getMyTop(int type)
{

}

string GameMgr::getGameId(int type) {
	string gid = "tienlen_win";
	switch (type)
	{
	case TOP_WIN:
		gid = "tienlen_win";
		break;
	case TOP_GOLD:
		gid = "tienlen_gold";
		break;
	case TOP_TALA:
		gid = "tlk";
		break;
	case TOP_BINH_WIN:
		gid = "capsa_win";
		break;
	case TOP_BINH_GOLD:
		gid = "capsa_gold";
		break;
	default:
		break;
	}
	//gid = "lines98";
	return gid;
}

int GameMgr::getGameCode(string gid)
{
	//return 0;
	if (gid.compare("tienlen_win") == 0)
		return TOP_WIN;
	if (gid.compare("tienlen_gold") == 0)
		return TOP_GOLD;
	if (gid.compare("tlk") == 0)
		return TOP_TALA;
	if (gid.compare("capsa_win") == 0)
		return TOP_BINH_WIN;
	if (gid.compare("capsa_gold") == 0)
		return TOP_BINH_GOLD;
	return 0;
}

int GameMgr::getLevel(int winCount)
{
	/*if (true)
		return WinCount();*/
	int level = winCount / 5;
	level = (int)log2(level);
	if (level < 0)
		level = 0;
	return level;
}

bool GameMgr::haveTop()
{
    return false;
}


void GameMgr::getCountry()
{
	string urlRequest = "https://api.myip.com/";

    string country = JNIUtils::getCountry();
    if (country.find("id") != std::string::npos || country.find("ID") != std::string::npos)
    {
        //isIndo = true;
    }
    if (country.find("ph") != std::string::npos || country.find("PH") != std::string::npos ||
        country.find("fil") != std::string::npos)
    {
      //  isIndo = true;
    }

	string data = "";
	HttpUtils::addRequestPost(urlRequest, data, [this](bool isSuccess, std::string data) {
		AXLOGD("MyInfo %s ", data.c_str());
		rapidjson::Document attribute;
		attribute.Parse<0>(data.c_str());
		if (attribute.HasParseError()) {
			// chua co du lieu trong Top
		}
		else {
			if (attribute.IsObject()) {
				reasonUpdate = "Please update the latest version to continue the game";
				if (attribute.HasMember("cc")) {
					countryName = attribute["cc"].GetString();
					UserDefault::getInstance()->setStringForKey("countryName", countryName);
					UserDefault::getInstance()->flush();
                    if (countryName.compare("id") == 0 || countryName.compare("ID") == 0) {
                     //   isIndo = true;
                    }
                    if (countryName.compare("ph") == 0 || countryName.compare("PH") == 0)
                    {
                       // isIndo = true;
                    }
                    if (isIndo)
                    {
                      //  languageMgr->changeLanguage(LANGUAGE_EN);
                    }
                    else
                    {
                        //languageMgr->changeLanguage(LANGUAGE_VN);
                    }
				}
			}
		}
	});
    if (isIndo)
    {
        languageMgr->changeLanguage(LANGUAGE_EN);
    }
    else
    {
        languageMgr->changeLanguage(LANGUAGE_VN);
    }
}


void GameMgr::getVersion()
{
	string urlRequest = "https://news.beansofts.com/?a=78&v=3";
	if (versionGame == TALA_NEW) {
		urlRequest = "https://news.beansofts.com/?a=75&v=3";
	}
	if (isIOS())
		urlRequest = urlRequest + "&p=1";
	//	AXLOGD("getmy top %s ", urlRequest.c_str());
	string data = "";
	HttpUtils::addRequestPost(urlRequest, data, [this](bool isSuccess, std::string data) {
		AXLOGD("MyInfo %s ", data.c_str());
		rapidjson::Document attribute;
		attribute.Parse<0>(data.c_str());
		if (attribute.HasParseError()) {
			// chua co du lieu trong Top
		}
		else {
			if (attribute.IsObject()) {
				reasonUpdate = "Please update the latest version to continue the game";
				if (attribute.HasMember("need_update"))
					need_update = attribute["need_update"].GetInt();
				if (attribute.HasMember("urlUpdate"))
					urlUpdate = attribute["link_update"].GetString();
				if (attribute.HasMember("message"))
					reasonUpdate = attribute["message"].GetString();
                if (attribute.HasMember("adBannerUnit"))
                {
                    adBannerUnit = attribute["adBannerUnit"].GetString();
                    UserDefault::getInstance()->setStringForKey("adBannerUnit", adBannerUnit);
                }
                if (attribute.HasMember("adInterUnit"))
                {
                    adInterUnit = attribute["adInterUnit"].GetString();
                    UserDefault::getInstance()->setStringForKey("adInterUnit", adInterUnit);
                }
                if (attribute.HasMember("adRewardUnit"))
                {
                    adRewardUnit = attribute["adRewardUnit"].GetString();
                    UserDefault::getInstance()->setStringForKey("adRewardUnit", adRewardUnit);
                }
                if (attribute.HasMember("useAds"))
                {
                    useAds = attribute["useAds"].GetInt();
                }
				//fakeApp = 0;
				//urlUpdate = "com.bcsofts.tienlen";
				//need_update = 2;
				//checkUpdate();
			}
		}
	});
       // useAds = 1;
    UserDefault::getInstance()->flush();
}

void GameMgr::getIdAds()
{
	string urlRequest = "https://cloudfunction-54e7c.web.app/adsTienLen.txt";
	if (versionGame == TALA_NEW) {
		urlRequest = "https://cloudfunction-54e7c.web.app/adsTienLenNew.txt";
	}
	//	AXLOGD("getmy top %s ", urlRequest.c_str());
	string data = "";
	HttpUtils::addRequestPost(urlRequest, data, [this](bool isSuccess, std::string data) {
		AXLOGD("MyInfo %s ", data.c_str());
		rapidjson::Document attribute;
		attribute.Parse<0>(data.c_str());
		if (attribute.HasParseError()) {
			// chua co du lieu trong Top
		}
		else {
			if (attribute.IsObject()) {
				if (attribute.HasMember("adsReward"))
					adsReward = attribute["adsReward"].GetString();
				if (attribute.HasMember("adsInter"))
					adsInter = attribute["adsInter"].GetString();
				UserDefault::getInstance()->getStringForKey("adsInter", adsInter);
				UserDefault::getInstance()->getStringForKey("adsReward", adsReward);
				UserDefault::getInstance()->flush();
			}
		}
	});
}


bool GameMgr::checkUpdate()
{
	if (need_update == 1) {
		// bat buoc phai update
		sceneMgr->showOkDialogWithAction(reasonUpdate, [this](int btnId) {
			JNIUtils::openApp(urlUpdate.c_str());
			endGame();
		});
		return true;
	}
	else if (need_update == 2) {
		sceneMgr->showOkCancelDialog(reasonUpdate, [this](int buttonId) {
			if (buttonId == Dialog::BTN_OK) {
				JNIUtils::openApp(urlUpdate.c_str());
				endGame();
			}
			need_update = false;
		});
		return true;
	}
	return false;
}

GameMgr* GameMgr::_instance = nullptr;

