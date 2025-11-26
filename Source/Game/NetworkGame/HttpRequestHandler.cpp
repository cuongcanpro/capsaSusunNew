
#include "HttpRequestHandler.h"
#include <stdlib.h>

#include "../GUIManager.h"
#include "Engine/GlobalVar.h"
#include "../GameClient.h"
#include "Game/Data/GlobalData.h"
#include "../Utility/JNIUtils.h"

#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
#include "PlatformWrapper.h"
#endif
#include <Engine/Utility/CStringUtils.h>
HttpRequestHandler::HttpRequestHandler(void)
{
}


HttpRequestHandler::~HttpRequestHandler(void)
{
}


void httpUpdateGame()
{

#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
	// update Game IOS
   // PlatformWrapper::openURL(urlUpdate.c_str());
	//IOSConnection::openURL(urlUpdate.c_str());
	// PlatformWrapper::openUpdate("http:\/\/itunes.apple.com\/vn\/app\/clash-of-clans\/id529479190?mt=8");
	exit(1);
#endif

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID|| AX_TARGET_PLATFORM == AX_PLATFORM_WIN32|| AX_TARGET_PLATFORM == AX_PLATFORM_WP8)
	// update Game Android
	string url = urlUpdate + "&referrer=" + game->getHighscoreData();
	JNIUtils::openApp(urlUpdate.c_str());
	game->endGame();
#endif
}

void httpConnectGame()
{

#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS || AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)



#endif

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)

	/*if(GUIManager::getInstance().guiLoading.isEndLoading())
	{
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiLogin);
	}
	else{
		updateGame = 0;
	}*/

#endif
}

void HttpRequestHandler::onCompleteGetVersion(ax::network::HttpClient *client, ax::network::HttpResponse *response)
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != response->getHttpRequest()->getTag().length())
	{
		AXLOGD("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	AXLOGD("response code: %ld", statusCode);
	if (response->getResponseCode() == -1)
	{
		//httpConnectGame();
		return;
	}

	if (!response->isSucceed())
	{
		AXLOGD("response failed");
		return;
	}

	// dump data
	//std::vector<char> *buffer = response->getResponseData()->data;
    auto buffer               = response->getResponseData();
    buffer->push_back('\0');  // to c_str
	AXLOGD("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		//AXLOGD("%c", (*buffer)[i]);
	}
	string result(buffer->begin(), buffer->end());
	//AXLOGD("Content %s ", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;

	string data = "";
	string updateMessage = "";
	string maintainMessage = "";
	updateMessage = "Please update new version app!";
	if (d.GetParseError() == NULL)
	{
		AXLOGD("PARSE DATA");
		if (d.HasMember("need_update")) {
			if (d.HasMember("need_update")) {
				updateGame = d["need_update"].GetInt();
			}
			if (d.HasMember("link_update")) {
				urlUpdate = d["link_update"].GetString();
			}
			if (d.HasMember("support")) {
				fakeApp = d["support"].GetInt();
			}
			if (d.HasMember("idAdsFull"))
			{
				idAdsFull = d["idAdsFull"].GetInt();
			}
			if (d.HasMember("idAdsBanner"))
			{
				idAdsBanner = d["idAdsBanner"].GetInt();
			}
			if (d.HasMember("updateMessage"))
			{
				updateMessage = d["updateMessage"].GetString();
			}
		}

	}
	//	game->countUpdate = 10;
		//updateGame = 1;

	//	ip = "118.102.3.8";
		//port = 443;
		//fakeApp = 1;
		// updateGame = 1;
		//updateGame = 2;
	CStringUtils::replaceAll(updateMessage, "#", "\n");

	//int updateGame = 0;
	if (updateGame != 0) {
		//if (game->countUpdate != 0) {
		//	if (updateGame == 1)
		//	{
		//		GUIManager::getInstance().guiDialog->showGUI(updateMessage.c_str(), httpUpdateGame, true);
		//		return;
		//	}
		//	else if (updateGame == 2)
		//	{
		//		GUIManager::getInstance().guiDialog->showGUI(updateMessage.c_str(), httpUpdateGame, false, httpConnectGame);
		//		return;
		//	}
		//}
		//else {
		//	UserDefault::getInstance()->setIntegerForKey("countUpdate", 1);
		//	UserDefault::getInstance()->flush();
		//	GUIManager::getInstance().removeAllGui();
		////	GUIManager::getInstance().showGui(&GUIManager::getInstance().guiLobby);
		//}

	}
	else {

	}

}

void HttpRequestHandler::onCompleteGetFake(ax::network::HttpClient *client, ax::network::HttpResponse *response)
{
	if (!response)
		return;

	if (0 != response->getHttpRequest()->getTag().length())
	{
	}

	if (response->getResponseCode() == -1)
	{
		return;
	}


	auto buffer = response->getResponseData();
    buffer->push_back('\0');  // to c_str
	string result(buffer->begin(), buffer->end());
	// LOG("receive = %s", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;

	string data = "";

	string updateMessage = "";

	string maintainMessage = "";


	if (d.GetParseError() == NULL)
	{
		//if (d.HasMember("support"))
	//    fakeApp = d["support"].GetInt();
	}
	// fakeApp = 1;
}

void HttpRequestHandler::onCompleteGetPackage(ax::network::HttpClient *client, ax::network::HttpResponse *response)
{
	if (!response)
		return;

	if (0 != response->getHttpRequest()->getTag().length())
	{
	}

	if (response->getResponseCode() == -1)
	{
		AXLOGD("FAIL NE ");
		return;
	}



}


void HttpRequestHandler::onCompleteGetIP(ax::network::HttpClient *client, ax::network::HttpResponse *response)
{
	if (!response)
		return;

	if (0 != response->getHttpRequest()->getTag().length())
	{
	}

	if (response->getResponseCode() == -1)
	{
		AXLOGD("GET IP FAIL *** ");
		return;
	}


	auto buffer = response->getResponseData();
    buffer->push_back('\0');  // to c_str
	string result(buffer->begin(), buffer->end());
	AXLOGD("receive = %s", result.c_str());
	rapidjson::Document d;
	d.Parse<0>(result.c_str());
	int error = -1;

	string data = "";

	string updateMessage = "";

	string maintainMessage = "";


	if (d.GetParseError() == NULL)
	{
		if (d.HasMember("country_code")) {
			string country = d["country_code"].GetString();

			if (country.compare("RU") == 0 || country.compare("RUS") == 0) {
				game->isRussia = true;
				UserDefault::getInstance()->setBoolForKey("isRussia", true);
				UserDefault::getInstance()->flush();
				JNIUtils::setRussia(1);
			}
			else {
				game->isRussia = false;
				UserDefault::getInstance()->setBoolForKey("isRussia", false);
				UserDefault::getInstance()->flush();
				JNIUtils::setRussia(0);
			}
		}
	}
	// fakeApp = 1;
}

