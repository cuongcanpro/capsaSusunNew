#include "GameClient.h"
#include "../Engine/GlobalVar.h"
#include "../Engine/Engine.h"
#include "GUIManager.h"

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
//#include "../../Utility/JNIUtils.h"
#endif
#include "../AppDelegate.h"
#include "Utility/JNIUtils.h"
#include "Data/GlobalData.h"
#include <Engine/Utility/LocalizedString.h>
#include <Engine/Utility/CStringUtils.h>
#include "Utility/GameSound.h"
#include <app/GameMgr.h>

#define TEST_GUI 0



GameClient::GameClient(void)
{
    //
    ////connectPortal = false;
    // CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
    //	callfuncO_selector(GameClient::listenBackToForeground),
    //	EVENT_COME_TO_FOREGROUND,
    //	NULL);
}

GameClient::~GameClient(void) {}

bool GameClient::applicationDidFinishLaunching()
{
    return true;
}

void GameClient::listenBackToForeground()
{
    loadShaders();
}

void GameClient::applicationDidEnterBackground() {
    time_t currentTime;
    time(&currentTime);
    timeBackground = currentTime + 1 * 60 * 60;
}

void GameClient::applicationWillEnterForeground()
{
    AXLOGD("ENTER FOREGROUND ");
    time_t currentTime;
    time(&currentTime);

    if (currentTime > timeBackground && showNewGame && idAdsFull != 3)
    {
        if (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())
            GUIManager::getInstance().guiLine->showNewGame();
    }
}

void GameClient::init()
{
    isLandscape       = true;
    extendGame        = 0;
    showHelpBomb      = false;
    vibrate           = true;
    numDivide         = 5;
    useReward         = 1;
    showNewGame = 0;
    scoreEnable       = 300;
   // scoreEnable       = 0;
    enableHard        = false;
    message           = "";
    numDestroy        = 18;
    useAds            = 1; // nho bo cai nay ============================================
    showContinue      = 0;
    targetOldScore    = 1000;
    timeShow          = 4 * 60;
    //targetOldScore    = 0;
    //timeShow          = 20;
    timeNoAds         = 0;
    timePlayGame      = 0;
    isRussia          = false;
    isInitAds         = false;
    isNeedIP          = 0;
    srand(time(NULL));
    Engine::init();
    loadShaders();
    loadPreferences();
    initGame();

    string lastDay = std::string(UserDefault::getInstance()->getStringForKey("lastDay", ""));
    time_t now     = time(0);
    tm* ltm        = localtime(&now);
    string sDay    = to_string(ltm->tm_year) + "m" + to_string(ltm->tm_mon) + "d" +
                  to_string(ltm->tm_mday);
    AXLOGD("LAST DAY NE %s ", sDay.c_str());
    countPlayAllTime = UserDefault::getInstance()->getIntegerForKey("countPlayAllTime", 0);
    if (countPlayAllTime < 3)
    {
        countPlayAllTime = countPlayAllTime + 1;
        UserDefault::getInstance()->setIntegerForKey("countPlayAllTime", countPlayAllTime);
        UserDefault::getInstance()->flush();
    }
}

void GameClient::receivePreference(string data)
{

}

void GameClient::loadPreferences()
{
    int a = -3 % 7;
    arrayGame    = UserDefault::getInstance()->getStringForKey("arrayIdGame", "0,1,2,11,12,3,4,5,13,14,6,7,8,9");
    std::stringstream ss(arrayGame);
    std::string token;

    while (std::getline(ss, token, ','))
    {
        arrayIdGame.push_back(std::stoi(token));
    }
    numPlayGame = UserDefault::getInstance()->getIntegerForKey("numPlayGame", 0);
    numPlayGame = numPlayGame + 1;
    if (numPlayGame > 5)
        extendGame = 1;
    UserDefault::getInstance()->setIntegerForKey("numPlayGame", numPlayGame);
    sourceApp  = UserDefault::getInstance()->getIntegerForKey("sourceApp", -1);
    idAdsBanner = UserDefault::getInstance()->getIntegerForKey("idAdsBanner", 1);
    idAdsFull = UserDefault::getInstance()->getIntegerForKey("idAdsFull", 1);
    adInterUnit = UserDefault::getInstance()->getStringForKey("adInterUnit", "ca-app-pub-3940256099942544/6300978111");
    adBannerUnit = UserDefault::getInstance()->getStringForKey("adBannerUnit", "ca-app-pub-3940256099942544/1033173712");
    adRewardUnit = UserDefault::getInstance()->getStringForKey("adRewardUnit", "ca-app-pub-3940256099942544/5224354917");

    adInterUnitCampaign  = "ca-app-pub-3940256099942544/6300978111";
    adBannerUnitCampaign = "ca-app-pub-3940256099942544/1033173712";
    adRewardUnitCampaign = "ca-app-pub-3940256099942544/5224354917";

    adBannerFacebook = UserDefault::getInstance()->getStringForKey("adBannerFacebook", "");
    adRewardFacebook = UserDefault::getInstance()->getStringForKey("adRewardFacebook", "");
    adInterFacebook = UserDefault::getInstance()->getStringForKey("adInterFacebook", "");
    adAppFacebook = UserDefault::getInstance()->getStringForKey("adAppFacebook", "");

    isPlaying = UserDefault::getInstance()->getBoolForKey("isPlayingNormal", false);
    AXLOGD("Is Playing =========== %s ", isPlaying ? "true" : "false");
    highscore = UserDefault::getInstance()->getIntegerForKey("highscore", 0);
   // highscore      = 10;
    saveScore = UserDefault::getInstance()->getIntegerForKey("saveScore", 0);
    typeBall = UserDefault::getInstance()->getIntegerForKey("typeBall", -1);
    typeBg = UserDefault::getInstance()->getIntegerForKey("typeBg", -1);
    typeTheme = UserDefault::getInstance()->getIntegerForKey("typeTheme", -1);
    typeBackground = UserDefault::getInstance()->getIntegerForKey("typeBackground", 0);
    game->showHelp = false;
    loadPlayNormal();
    //	idAdsBanner = 1;
//    idAdsFull = idAdsBanner;

    game->isRussia = UserDefault::getInstance()->getBoolForKey("isRussia", false);
    game->isNeedIP = UserDefault::getInstance()->getIntegerForKey("isNeedIP", 0);
    if (game->isRussia)
        JNIUtils::setRussia(1);
    // game->myInfo->numTicket = 10;
    music = UserDefault::getInstance()->getBoolForKey("music", true);

    //highscore  = 0;
    scaleBall     = UserDefault::getInstance()->getFloatForKey("scaleBall", 0.8);
    brightBall    = UserDefault::getInstance()->getFloatForKey("brightBall", 1.0);

    saveTime       = UserDefault::getInstance()->getFloatForKey("saveTime", 0);
    showHelp       = UserDefault::getInstance()->getBoolForKey("showHelp", true);
    showHelp       = false;

    numNoBrick         = UserDefault::getInstance()->getIntegerForKey("numNoBrick", 0);
    targetSpecial      = UserDefault::getInstance()->getIntegerForKey("targetSpecial", 20);

    if (game->highscore > 0)
    {
        JNIUtils::sendEvent(("type_ball_" + to_string(typeBall)).c_str(), "1");
        JNIUtils::sendEvent(("type_theme_" + to_string(typeTheme)).c_str(), "1");
        JNIUtils::sendEvent(("type_bg_" + to_string(typeBg)).c_str(), "1");
        JNIUtils::sendEvent(("type_background_" + to_string(typeBackground)).c_str(), "1");
    }

    arrayTutorialChallenge[0] = new TutorialData(7, 4, 0.5, CCLocalizedString("TUTORIAL_CHALLENGE_1"));
    arrayTutorialChallenge[1] = new TutorialData(4, 4, 0.5, CCLocalizedString("TUTORIAL_CHALLENGE_2"));
    loadColor();

    scoreEndless = UserDefault::getInstance()->getIntegerForKey("scoreEndless", 0);
    scoreTime    = UserDefault::getInstance()->getIntegerForKey("scoreTime", 0);
    // scoreTime = 600;
    UserDefault::getInstance()->setIntegerForKey("scoreTime", 0);
    UserDefault::getInstance()->flush();
    music   = UserDefault::getInstance()->getBoolForKey("music", true);
    level   = UserDefault::getInstance()->getIntegerForKey("level", 1);
    for (int i = 0; i < 21; i++)
        scoreStomp[i] = UserDefault::getInstance()->getIntegerForKey(("scoreStomp" + to_string(i)).c_str(), 0);
    deltaTime = 0;
    for (int i = 0; i < 21; i++)
        isRead[i] = false;



    GameMgr::getInstance()->startGame();
    getVersion();
}

void GameClient::initGame()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GuiGame/pop/texture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GuiGame/gamePika/texture.plist");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GuiGame/lineOld.plist");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boardGame.plist");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ball.plist");
    GameSound::loadSound();
    GUIManager::getInstance().showGuiWithName(GUILoading::className);
    //GUIManager::getInstance().removeAllGui();
   // GUIManager::getInstance().guiBubble.showGuiWithMode(0);
    GUILoading* guiLoading = new GUILoading();

    //layerMgr->getLayerByIndex(LAYER_GUI)->addChild(GUIManager::getInstance().guiLoading);
}

void GameClient::loadPlayNormal()
{
    AXLOGD("LOAD XONG %i ", isPlaying);
    if (isPlaying)
    {
        bool loadPlayNormal = UserDefault::getInstance()->getBoolForKey("loadPlayNormal", false);
        if (loadPlayNormal)
        {
            resetPlayNormal();
            return;
        }
        UserDefault::getInstance()->setBoolForKey("loadPlayNormal", true);
        UserDefault::getInstance()->flush();
        string s;
        // if (isIOS())
        //	s = UserDefault::getInstance()->getStringForKey("dataNormal", "");
        // else
        s = UserDefault::getInstance()->getStringForKey("dataNormal", "");
        if (s.size() <= 10)
        {
            resetPlayNormal();
            return;
        }
        else
        {
            char* pch = new char[s.size() + 1];
            std::copy(s.begin(), s.end(), pch);
            pch[s.size()] = '\0';  // don't forget the terminating 0
            char* num;
            num = strtok(pch, ",");
            if (num == NULL)
            {
                resetPlayNormal();
                return;
            }
            try
            {
                data[0] = std::stoi(num);  // don't call c_str()
            }
            catch (std::exception const& e)
            {
                resetPlayNormal();
                return;
            }
            for (int i = 1; i < 81; i++)
            {
                num = strtok(NULL, ",");
                if (num == NULL)
                {
                    resetPlayNormal();
                    return;
                }
                try
                {
                    data[i] = std::stoi(num);  // don't call c_str()
                }
                catch (std::exception const& e)
                {
                    resetPlayNormal();
                    return;
                }
            }
            AXLOGD("DATA %s", s.c_str());
        }
        UserDefault::getInstance()->setBoolForKey("loadPlayNormal", false);
        UserDefault::getInstance()->flush();
    }
}


void GameClient::loadColor()
{
    string s = std::string(UserDefault::getInstance()->getStringForKey("arrayBall", ""));
    if (s.size() <= 10)
    {
        resetColor();
        return;
    }
    else
    {
        char* pch = new char[s.size() + 1];
        std::copy(s.begin(), s.end(), pch);
        pch[s.size()] = '\0';  // don't forget the terminating 0
        char* num;
        num = strtok(pch, ",");
        if (num == NULL)
        {
            resetColor();
            return;
        }
        try
        {
            arrayBall[0] = std::stoi(num);  // don't call c_str()
        }
        catch (std::exception const& e)
        {
            resetColor();
            return;
        }
        for (int j = 1; j < 9; j++)
        {
            num = strtok(NULL, ",");
            if (num != NULL)
            {
                // arrayBall[j] = atoi(num);
                try
                {
                    arrayBall[j] = std::stoi(num);  // don't call c_str()
                }
                catch (std::exception const& e)
                {
                    resetColor();
                    return;
                }
            }
            else
            {
                resetColor();
                return;
            }
        }
        for (int i = 0; i < 6; i++)
            for (int j = i + 1; j < 7; j++)
            {
                if (arrayBall[i] > arrayBall[j])
                {
                    int temp = arrayBall[i];
                    arrayBall[i] = arrayBall[j];
                    arrayBall[j] = temp;
                }
            }
    }
}

void GameClient::resetColor()
{
    string s = "";
    for (int i = 0; i < 9; i++)
    {
        arrayBall[i] = i;
        if (i == 0)
        {
            s = s + to_string(i);
        }
        else
        {
            s = s + "," + to_string(i);
        }
    }
    UserDefault::getInstance()->setStringForKey("arrayBall", s.c_str());
    UserDefault::getInstance()->flush();
}


void GameClient::resetPlayNormal()
{
    isPlaying = false;
    if (isIOS())
        UserDefault::getInstance()->setBoolForKey("isPlayingNormal", false);
    else
        UserDefault::getInstance()->setBoolForKey("isPlaying", false);
    UserDefault::getInstance()->setBoolForKey("loadPlayNormal", false);
    UserDefault::getInstance()->flush();
}


void GameClient::takeScreenshot()
{

}

void GameClient::loadShaders()
{
#if AX_TARGET_PLATFORM != AX_PLATFORM_WP8


#endif
}

void GameClient::readDataLevel(int levelIndex)
{
    if (isRead[levelIndex])
        return;
    isRead[levelIndex] = true;
    string line;
    // ifstream myfile ("common/level" + CStringUtils::toString(levelType) + ".txt");
    string s             = "Common/" + to_string(levelIndex) + ".txt";
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(s.c_str());
    // CCLog("FULLPATH %s	", fullPath.c_str());
    // ifstream myfile ("common/splash.txt");

    ssize_t fileSize;
    string contents;
    contents = FileUtils::getInstance()->getStringFromFile(fullPath.c_str());
    // contents.append((char*)fileContents);
    AXLOGD("Level %s ", contents.c_str());
    istringstream myfile(contents);

    int count      = 0;
    int countLevel = 1;
    int numRow = 0, numCol = 0;

    vector<vector<int>> arrayRow;
    while (getline(myfile, line))
    {
        int i = 0;

        if (count == 0)
        {
            // doc so hang
            numRow = stoi(line);
        }
        else if (count == 1)
        {
            numCol = stoi(line);
        }
        else if (count == 2)
        {
            typeRow[levelIndex] = stoi(line);
        }
        else if (count == 3)
        {
            numBall[levelIndex] = stoi(line);
        }
        else
        {
            vector<int> arrayBall;
            for (int i = 0; i < line.length(); i++)
            {
                if (line.at(i) == '-')
                    arrayBall.push_back(-1);
                else if (line.at(i) <= '9' && line.at(i) >= '0')
                {
                    arrayBall.push_back(line.at(i) - '0' - 1);
                    // CCLog("array ball %i ", arrayBall.at(arrayBall.size() - 1));
                }
            }
            if (arrayRow.size() < numRow)
                arrayRow.push_back(arrayBall);
        }
        dataLevel[levelIndex] = arrayRow;
        count++;
    }
}

void GameClient::update(float delta)
{
    GUIManager::getInstance().isCallBackPress = false;
    game->deltaTime                           = delta;
    timeNoAds                                 = timeNoAds + delta;
    if (GUIManager::getInstance().guiGame != NULL && GUIManager::getInstance().guiGame->isVisible())
    {
        GUIManager::getInstance().guiGame->act(delta);
    }
    else if (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())
    {
        GUIManager::getInstance().guiLine->update(delta);
    }
    else if (GUIManager::getInstance().guiMerge != NULL && GUIManager::getInstance().guiMerge->isVisible())
    {
        GUIManager::getInstance().guiMerge->update();
    }
    else if (GUIManager::getInstance().guiTwenty != NULL && GUIManager::getInstance().guiTwenty->isVisible())
    {
        GUIManager::getInstance().guiTwenty->update();
    }
    else if (GUIManager::getInstance().guiBomb != NULL && GUIManager::getInstance().guiBomb->isVisible())
    {
        GUIManager::getInstance().guiBomb->update(delta);
    }
    else if (GUIManager::getInstance().guiPop != NULL && GUIManager::getInstance().guiPop->isVisible())
    {
        GUIManager::getInstance().guiPop->update();
    }
    else if (GUIManager::getInstance().guiBubble != NULL && GUIManager::getInstance().guiBubble->isVisible())
    {
        GUIManager::getInstance().guiBubble->update();
    }
    else if (GUIManager::getInstance().guiBrick != NULL && GUIManager::getInstance().guiBrick->isVisible())
    {
        GUIManager::getInstance().guiBrick->update();
    }
    else if (GUIManager::getInstance().guiBlock != NULL && GUIManager::getInstance().guiBlock->isVisible())
    {
        GUIManager::getInstance().guiBlock->update(delta);
    }
    else if (GUIManager::getInstance().guiPika != NULL && GUIManager::getInstance().guiPika->isVisible())
    {
        GUIManager::getInstance().guiPika->act();
    }
    else if (GUIManager::getInstance().guiSwing != NULL && GUIManager::getInstance().guiSwing->isVisible())
    {
        GUIManager::getInstance().guiSwing->update();
    }
    else if (GUIManager::getInstance().guiAa != NULL && GUIManager::getInstance().guiAa->isVisible())
    {
        GUIManager::getInstance().guiAa->act(delta);
    }

    time_t currentTime;
    time(&currentTime);
    if (currentTime > timeToGetVersion)
    {
        JNIUtils::sendEvent("reload_ads", "1");
        getVersion();
    }
}

void GameClient::onPause() {}

void GameClient::onResume() {}

void GameClient::endGame()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)

    exit(1);
#endif

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    // JNIUtils::openPortal();
    Director::getInstance()->end();

#endif

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
    exit(1);
#endif
}

string GameClient::standartNum(int num)
{
    if (num > 999999)
        num = 999999;
    string result = CStringUtils::toString(num);
    int add       = 6 - result.length();
    for (int i = 0; i < add; i++)
    {
        result = "0" + result;
    }
    return result;
}

bool GameClient::isIOS()
{
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    return true;
#endif
    return false;
}

std::string GameClient::getHighscoreData()
{
    string data = "";
    data        = "highscore_" + to_string(highscore) + "";
    return data;
}

void GameClient::receiveHighscoreData()
{
    loadPreferences();
    UserDefault::getInstance()->setBoolForKey("restoreData", true);
    UserDefault::getInstance()->flush();
    /*std::regex regexz("_");
    std::vector<std::string> arrData = { std::sregex_token_iterator(data.begin(), data.end(), regexz, -1),
    std::sregex_token_iterator() }; for (int i = 0; i < arrData.size(); i++) { if (arrData[i].compare("highscore") == 0
    && i + 1 < arrData.size()) { game->highscore = stoi(arrData[i + 1]);
                    UserDefault::getInstance()->setIntegerForKey("highscore", game->highscore);
            }
            else if (arrData[i].compare("highscoreTime") == 0 && i + 1 < arrData.size()) {
                    game->highscoreTime = stoi(arrData[i + 1]);
                    UserDefault::getInstance()->setIntegerForKey("highscoreTime", game->highscore);
            }
            else if (arrData[i].compare("highscoreExtra") == 0 && i + 1 < arrData.size()) {
                    game->highscoreExtra = stoi(arrData[i + 1]);
                    UserDefault::getInstance()->setIntegerForKey("highscoreExtra", game->highscore);
            }
            else if (arrData[i].compare("highscoreLevel") == 0 && i + 1 < arrData.size()) {
                    game->highscoreLevel = stoi(arrData[i + 1]);
                    UserDefault::getInstance()->setIntegerForKey("highscoreLevel", game->highscore);
            }
            else if (arrData[i].compare("highscoreChallenge") == 0 && i + 1 < arrData.size()) {
                    game->highscoreChallenge = stoi(arrData[i + 1]);
                    UserDefault::getInstance()->setIntegerForKey("highscoreChallenge", game->highscore);
            }
            i++;
    }
    UserDefault::getInstance()->flush();*/
}

void GameClient::showAdsForOldUser(bool isUndo)
{
    float timeCheck = 120;
    if (isUndo)
    {
        timeCheck = timeShow;
    }
    if (idAdsBanner == 3)
    {
        timeCheck = timeCheck * 2.5;
    }

    if (game->highscore > targetOldScore && timeNoAds > timeCheck)
    {
        // if (game->highscore > 500 && timeNoAds > 4 * 60 && idAdsBanner != 3) {
        JNIUtils::showAdsFull();
        //GUIManager::getInstance().guiWaiting.showAds(false);
    }
}

void GameClient::getVersion() {
    ax::network::HttpRequest* request = new ax::network::HttpRequest();
    // required fields
    request->setUrl("https://news.beansofts.com/?a=736&v=1");
    request->setRequestType(ax::network::HttpRequest::Type::GET);
  //  request->setHeaders(std::vector<std::string>{CHROME_UA});
    request->setResponseCallback(AX_CALLBACK_2(GameClient::onVersionCompleted, this));
    request->setTag("GET test3");
    //ax::network::HttpClient::getInstance()->send(request);
    // don't forget to release it, pair to new
    request->release();
    time_t currentTime;
    time(&currentTime);
    timeToGetVersion = currentTime + 1 * 60 * 60;
}

void GameClient::onVersionCompleted(ax::network::HttpClient* sender, ax::network::HttpResponse* response)
{
    if (!response)
    {
        return;
    }

    // You can get original request type from: response->request->reqType
    auto tag = response->getHttpRequest()->getTag();
    if (!tag.empty())
    {
        AXLOGD("%s completed", tag.data());
    }

    int32_t statusCode    = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, tag.data());
    AXLOGD("response code: %d", statusCode);

    if (response->getResponseCode() != 200)
    {
        AXLOGD("response failed");
        // ax::print("error buffer: %s", response->getErrorBuffer());
        return;
    }

    // dump data
    auto buffer = response->getResponseData();
    buffer->push_back('\0');  // to c_str
    //ax::print("response %s ", buffer->data());

    string result(buffer->begin(), buffer->end());
    // AXLOGD("Content %s ", result.c_str());
    rapidjson::Document d;
    d.Parse<0>(result.c_str());
    int error = -1;

    string data            = "";

    string maintainMessage = "";

    if (d.GetParseError() == NULL)
    {
        AXLOGD("PARSE DATA");
        if (d.HasMember("need_update"))
        {
            updateGame = d["need_update"].GetInt();
        }
        if (d.HasMember("isUpdate"))
        {
            isUpdate = d["isUpdate"].GetInt();
        }
        if (d.HasMember("link_update"))
        {
            urlUpdate = d["link_update"].GetString();
        }
        if (d.HasMember("support"))
        {
            fakeApp = d["support"].GetInt();
        }
        if (d.HasMember("idAdsFull"))
        {
            idAdsFull = d["idAdsFull"].GetInt();
            UserDefault::getInstance()->setIntegerForKey("idAdsFull", idAdsFull);
        }
        if (d.HasMember("idAdsBanner"))
        {
            idAdsBanner = d["idAdsBanner"].GetInt();
            UserDefault::getInstance()->setIntegerForKey("idAdsBanner", idAdsBanner);
        }
        if (d.HasMember("adBannerUnit"))
        {
            adBannerUnit = d["adBannerUnit"].GetString();
            UserDefault::getInstance()->setStringForKey("adBannerUnit", adBannerUnit);
        }
        if (d.HasMember("adInterUnit"))
        {
            adInterUnit = d["adInterUnit"].GetString();
            UserDefault::getInstance()->setStringForKey("adInterUnit", adInterUnit);
        }
        if (d.HasMember("adRewardUnit"))
        {
            adRewardUnit = d["adRewardUnit"].GetString();
            UserDefault::getInstance()->setStringForKey("adRewardUnit", adRewardUnit);
        }
        if (d.HasMember("adBannerFacebook"))
        {
            adBannerFacebook = d["adBannerFacebook"].GetString();
            UserDefault::getInstance()->setStringForKey("adBannerFacebook", adBannerFacebook);
        }
        if (d.HasMember("adInterFacebook"))
        {
            adInterFacebook = d["adInterFacebook"].GetString();
            UserDefault::getInstance()->setStringForKey("adInterFacebook", adInterFacebook);
        }
        if (d.HasMember("adRewardFacebook"))
        {
            adRewardFacebook = d["adRewardFacebook"].GetString();
            UserDefault::getInstance()->setStringForKey("adRewardFacebook", adRewardFacebook);
        }
        if (d.HasMember("adAppFacebook"))
        {
            adAppFacebook = d["adAppFacebook"].GetString();
            UserDefault::getInstance()->setStringForKey("adAppFacebook", adAppFacebook);
        }
        if (d.HasMember("updateMessage"))
        {
            updateMessage = d["updateMessage"].GetString();
        }
        if (d.HasMember("targetOldScore"))
        {
            game->targetOldScore = d["targetOldScore"].GetInt();
        }
        if (d.HasMember("timeShow"))
        {
            game->timeShow = d["timeShow"].GetInt();
        }
        if (d.HasMember("showContinue"))
        {
            game->showContinue = d["showContinue"].GetInt();
        }
        if (d.HasMember("useAds"))
        {
            game->useAds = d["useAds"].GetInt();
        }
        if (d.HasMember("numDestroy"))
        {
            game->numDestroy = d["numDestroy"].GetInt();
        }
        if (d.HasMember("typeBackground"))
        {
            // do background themn vao sau nen phai phu thuoc vao typeBall, type ball chua duoc chon thi dua tren Service
            if (game->typeBall < 0)
                game->typeBackground = d["typeBackground"].GetInt();
        }
        if (d.HasMember("typeBall"))
        {
            if (game->typeBall < 0)
                game->typeBall = d["typeBall"].GetInt();
        }
        if (d.HasMember("typeBg"))
        {
            if (game->typeBg < 0)
                game->typeBg = d["typeBg"].GetInt();
        }
        if (d.HasMember("message"))
        {
            message = d["message"].GetString();
        }

        if (d.HasMember("showNewGame"))
        {
            showNewGame = d["showNewGame"].GetInt();
        }

        if (d.HasMember("useReward"))
        {
            useReward = d["useReward"].GetInt();
        }
        if (d.HasMember("numDivide"))
        {
            numDivide = d["numDivide"].GetInt();
        }
        if (d.HasMember("extendGame"))
        {
            if (extendGame == 0)
                extendGame = d["extendGame"].GetInt();
        }
        adInterUnitCampaign  = adInterUnit;
        adBannerUnitCampaign = adBannerUnit;
        adRewardUnitCampaign = adRewardUnit;
        if (d.HasMember("adBannerUnitCampaign"))
        {
            adBannerUnit = d["adBannerUnitCampaign"].GetString();
        }
        if (d.HasMember("adInterUnitCampaign"))
        {
            adInterUnit = d["adInterUnitCampaign"].GetString();
        }
        if (d.HasMember("adRewardUnitCampaign"))
        {
            adRewardUnit = d["adRewardUnitCampaign"].GetString();
        }
        UserDefault::getInstance()->flush();
    }
    //urlUpdate  = "org.simpleGame.colorLineChallenge";
    //updateGame = 2;
    if (updateGame != 0) {
        showUpdate();
    }
    else if (message != "") {
        showMessage();
    }
    if (game->isInitAds && idAdsBanner == 1)
    {
        JNIUtils::reloadAds();
    }
}

void onUpdateGame()
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

void onContinueGame() {
    if (GUIManager::getInstance().guiLoading->isVisible())
    {
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().guiLine->showGui();
    }
}

void GameClient::showUpdate() {
    if (updateGame == 1) {
        GUIManager::getInstance().guiDialog->showGUI(updateMessage.c_str(), onUpdateGame, true);
        return;
    }
    else if (updateGame == 2) {
        GUIManager::getInstance().guiDialog->showGUI(updateMessage.c_str(), onUpdateGame, false, onContinueGame);
        return;
    }
}

void GameClient::showMessage()
{
    GUIManager::getInstance().guiDialog->showGUI(message.c_str(), onContinueGame, true);
}

void GameClient::changeDesignSolution(bool is3D)
{
    auto glview               = Director::getInstance()->getRenderView();
    auto frameSize            = glview->getFrameSize();
    Size designResolutionSize = Size(480, 800);
    if (is3D)
    {
        glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
                                        ResolutionPolicy::SHOW_ALL);
    }
    else
    {
        if ((frameSize.width / frameSize.height) < (2.0f / 3.0f))
        {

            glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
                                            ResolutionPolicy::FIXED_WIDTH);
            // pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
            // kResolutionShowAll);
        }
        else
        {
            glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
                                            ResolutionPolicy::FIXED_HEIGHT);
            // pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
            // kResolutionShowAll);
        }
    }
}

void okRewardContinue() {
    if (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())
        GUIManager::getInstance().guiLine->changeToRemoveBall();

}

void GameClient::onReward(int num)
{
    if (num > 0)
    {
        auto director  = Director::getInstance();
        auto glview    = director->getRenderView();
        Size frameSize = glview->getFrameSize();
        if ((frameSize.height / frameSize.width) <= (1.0f))
        {
            gameMgr->onReward(num);
            return;
        }
        if (GUIManager::getInstance().guiLine != NULL && GUIManager::getInstance().guiLine->isVisible())
        {
            GUIManager::getInstance().removeFromListGui();
            JNIUtils::sendEvent("finish_show_ads_continue", "1");
            string s = CCLocalizedString("CONTINUE_GAME_REWARD");
            CStringUtils::replaceAll(s, "@num", utility->pointNumber(game->numDestroy));
            int subScore    = floor(game->saveScore / game->numDivide);
            game->saveScore = game->saveScore - subScore;
            CStringUtils::replaceAll(s, "@score", utility->pointNumber(subScore));
            GUIManager::getInstance().guiDialog->showGUI(s.c_str(), &okRewardContinue, true);

            JNIUtils::sendEvent("finish_reward_success", "1");
        }
        else if (GUIManager::getInstance().guiSudoku != NULL && GUIManager::getInstance().guiSudoku->isVisible())
        {
            GUIManager::getInstance().guiSudoku->onHint();
        }
    }
    else
    {
     //   game->countNotFinishAds++;
        GUIManager::getInstance().guiDialog->showGUI(CCLocalizedString("NOT_FINISH_REWARD_CONTINUE").c_str(), NULL, true);
       // JNIUtils::sendEvent("not_finish_show_ads", GameUtility::toString(game->countNotFinishAds).c_str());
        JNIUtils::sendEvent("finish_reward_fail", "1");
    }
}

void GameClient::initAds() {
    //return;
    if (isInitAds)
        return;
    isInitAds = true;
    if (useAds == 1)
    {
        if (sourceApp < 0)
        {
            sourceApp = JNIUtils::getSourceApp();
            UserDefault::getInstance()->setIntegerForKey("sourceApp", sourceApp);
            UserDefault::getInstance()->flush();
        }
        if (sourceApp == 0)
        {
            // nguon Organic
            AXLOGD("INIT ORGANIC == ");
            JNIUtils::initAds(adBannerUnit.c_str(), adInterUnit.c_str(), adRewardUnit.c_str(), idAdsBanner, idAdsFull);
        }
        else
        {
            // nguon Campaign
            AXLOGD("INIT CAMPAIGN == ");
            JNIUtils::initAds(adBannerUnitCampaign.c_str(), adInterUnitCampaign.c_str(), adRewardUnitCampaign.c_str(),
                              idAdsBanner, idAdsFull);
        }
        JNIUtils::initAdsFacebook(adAppFacebook.c_str(), adBannerFacebook.c_str(), adInterFacebook.c_str(), adRewardFacebook.c_str());

    }

}


void GameClient::showAdsFull()
{
    float timeCheck = 120;
    if (idAdsBanner == 3)
    {
        timeCheck = timeCheck * 1.7;
    }
    if (game->timeNoAds < timeCheck)
    {
        // if (game->timeNoAds < 20) {
        return;
    }
    JNIUtils::showAdsFull();
    //GUIManager::getInstance().guiWaiting.showAds(false);
}



void GameClient::loadBubble()
{
    showHelpBubble = UserDefault::getInstance()->getBoolForKey("showHelpBubble", true);
    //	showHelpBubble = true;
    saveScoreBubble      = UserDefault::getInstance()->getIntegerForKey("scoreBubble", 0);
    isPlayingBubble      = UserDefault::getInstance()->getBoolForKey("isPlayingBubble", false);
    highscoreBubble      = UserDefault::getInstance()->getIntegerForKey("highscore", 0);
    int highscoreBubble3 = UserDefault::getInstance()->getIntegerForKey("highscoreNormal", 0);
    AXLOGD("HighscoreNormal %i ", highscoreBubble3);
    highscoreBubble3 = UserDefault::getInstance()->getIntegerForKey("highscoreBubble", 0);
    AXLOGD("highscoreBubble %i ", highscoreBubble3);
    highscoreBubble3 = UserDefault::getInstance()->getIntegerForKey("highscore1", 0);
    AXLOGD("highscore1 %i ", highscoreBubble3);
    AXLOGD("Du ma 1");
    string s = std::string(UserDefault::getInstance()->getStringForKey("saveRandBubble", "00000"));
    for (int i = 0; i < 5; i++)
    {
        if (i >= s.length())
            saveRandBubble[i] = 0;
        else
            saveRandBubble[i] = s.at(i) - '0';
    }
    AXLOGD("Du ma 2");

    if (isPlayingBubble)
    {
        string s  = std::string(UserDefault::getInstance()->getStringForKey("dataBubble", ""));
        char* pch = new char[s.size() + 1];
        std::copy(s.begin(), s.end(), pch);
        pch[s.size()] = '\0';  // don't forget the terminating 0
        char* num;
        num           = strtok(pch, ",");
        dataBubble[0] = atoi(num);
        for (int i = 1; i < 45; i++)
        {
            num           = strtok(NULL, ",");
            dataBubble[i] = atoi(num);
        }
    }
    AXLOGD("Du ma 3");
    saveScoreBubble1 = UserDefault::getInstance()->getIntegerForKey("scoreTime", 0);
    isPlayingBubble1 = UserDefault::getInstance()->getBoolForKey("isPlayingBubble1", false);
    highscoreBubble1 = UserDefault::getInstance()->getIntegerForKey("highscoreTime", 0);
    // isPlayingBubble1 = false;
    s = UserDefault::getInstance()->getStringForKey("saveRandTime", "000000");
    AXLOGD("Du ma fd3 %s ", s.c_str());
    for (int i = 0; i < 6; i++)
    {
        if (i >= s.length())
            saveRandBubble1[i] = 0;
        else
            saveRandBubble1[i] = s.at(i) - '0';
    }
    AXLOGD("Du ma 4");

    if (isPlayingBubble1)
    {
        string s  = std::string(UserDefault::getInstance()->getStringForKey("dataTime", ""));
        char* pch = new char[s.size() + 1];
        std::copy(s.begin(), s.end(), pch);
        pch[s.size()] = '\0';  // don't forget the terminating 0
        char* num;
        num            = strtok(pch, ",");
        dataBubble1[0] = atoi(num);
        for (int i = 1; i < 63; i++)
        {
            num            = strtok(NULL, ",");
            dataBubble1[i] = atoi(num);
        }
    }
    AXLOGD("Du ma 5");
}

void GameClient::loadPop()
{
    highscorePop     = UserDefault::getInstance()->getIntegerForKey("highscorePop", 0);
    bestNum          = UserDefault::getInstance()->getIntegerForKey("bestNum", 4);
    highscorePopHard = UserDefault::getInstance()->getIntegerForKey("highscorePopHard", 0);
    bestNumHard      = UserDefault::getInstance()->getIntegerForKey("bestNumHard", 4);
    showHelpTouch    = UserDefault::getInstance()->getBoolForKey("showHelpTouch", true);
    int maxNum       = UserDefault::getInstance()->getIntegerForKey("maxNum", 4);
    if (bestNum < maxNum)
    {
        bestNum = maxNum;
        UserDefault::getInstance()->getIntegerForKey("bestNum", bestNum);
        UserDefault::getInstance()->flush();
    }
}


void GameClient::loadPika()
{
    isPlayingPika = UserDefault::getInstance()->getBoolForKey("isPlayingPika1", false);
    highscorePika   = UserDefault::getInstance()->getIntegerForKey("highscorePika", 0);
    if (isPlayingPika)
    {
        numLifePika = UserDefault::getInstance()->getIntegerForKey("numLifePika", 10);
        levelPika   = UserDefault::getInstance()->getIntegerForKey("levelPika", 0);
        timePika    = UserDefault::getInstance()->getFloatForKey("timePika", 0);
        // timePika = 300;
        saveScorePika = UserDefault::getInstance()->getIntegerForKey("saveScorePika", 0);
        string s      = std::string(UserDefault::getInstance()->getStringForKey("dataPika", ""));
        if (s.size() <= 10)
        {
            UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
            game->isPlayingPika = false;
            return;
        }
        else
        {
            char* pch = new char[s.size() + 1];
            std::copy(s.begin(), s.end(), pch);
            pch[s.size()] = '\0';  // don't forget the terminating 0
            char* num;
            num = strtok(pch, ",");
            if (num == NULL)
            {
                UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
                game->isPlayingPika = false;
                return;
            }
            try
            {
                dataPika[0] = std::stoi(num);  // don't call c_str()
            }
            catch (std::exception const& e)
            {
                UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
                game->isPlayingPika = false;
                return;
            }
            for (int i = 1; i < BOARD_ROW_PIKA * BOARD_COLUMN_PIKA; i++)
            {
                num = strtok(NULL, ",");
                if (num == NULL)
                {
                    UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
                    game->isPlayingPika = false;
                    return;
                }
                try
                {
                    dataPika[i] = std::stoi(num);  // don't call c_str()
                }
                catch (std::exception const& e)
                {
                    UserDefault::getInstance()->setBoolForKey("isPlayingPika1", false);
                    game->isPlayingPika = false;
                    return;
                }
            }
            AXLOGD("DATA %s", s.c_str());
        }
    }
}

void GameClient::loadBlock()
{
    game->showHelpBlock = UserDefault::getInstance()->getBoolForKey("showHelpBlock", true);
    game->highscoreBlock = UserDefault::getInstance()->getIntegerForKey("highscoreBlock", 0);
    game->isPlayingBlock = UserDefault::getInstance()->getBoolForKey("isPlayingBlock", false);
    if (game->isPlayingBlock)
    {
        string s  = (string)(UserDefault::getInstance()->getStringForKey("dataBlock", ""));
        char* pch = new char[s.size() + 1];
        std::copy(s.begin(), s.end(), pch);
        pch[s.size()] = '\0';  // don't forget the terminating 0
        char* num;
        num        = strtok(pch, ",");
        dataBlockPuzzel[0][0] = atoi(num);
        for (int i = 1; i < 64; i++)
        {
            num               = strtok(NULL, ",");
            int row           = i / 8;
            int column        = i % 8;
            dataBlockPuzzel[row][column] = atoi(num);
        }

        for (int i = 0; i < 3; i++)
        {
            arrayNextBlock[i] =
                UserDefault::getInstance()->getIntegerForKey(
                ("dataNextBlock" + to_string(i)).c_str(), 0);
            if (arrayNextBlock[i] < 0 || arrayNextBlock[i] > 11)
                arrayNextBlock[i] = 0;
        }

        for (int i = 0; i < 3; i++) {
            arrayBonus[i] =
                UserDefault::getInstance()->getIntegerForKey(("dataBonusBlock" +
            to_string(i)).c_str(), 0);
        }
    }
}


void GameClient::loadBomb()
{
    showHelpBomb = UserDefault::getInstance()->getBoolForKey("showHelpBomb", true);
    for (int i = 0; i < NUM_LEVEL_BOMB; i++)
    {
        arrBestTime[i] = UserDefault::getInstance()->getIntegerForKey(("bestTime" + to_string(i)).c_str(), 0);
    }
    currentTime = UserDefault::getInstance()->getIntegerForKey("currentTime", 0);
    currentMode = UserDefault::getInstance()->getIntegerForKey("currentMode", 0);

    if (currentTime > 0)
    {
        bool loadPlayTime = UserDefault::getInstance()->getBoolForKey("loadPlayTime", false);
        if (loadPlayTime)
        {
            return;
        }
        UserDefault::getInstance()->setBoolForKey("loadPlayTime", true);
        UserDefault::getInstance()->flush();

        string s = (string)(UserDefault::getInstance()->getStringForKey("arrBomb", ""));
        if (s.size() <= 10)
        {
            return;
        }
        else
        {
            char* pch = new char[s.size() + 1];
            std::copy(s.begin(), s.end(), pch);
            pch[s.size()] = '\0';  // don't forget the terminating 0
            char* num;
            num = strtok(pch, ",");
            if (num == NULL)
            {
                return;
            }
            try
            {
                arrBomb[0][0] = std::stoi(num);  // don't call c_str()
            }
            catch (std::exception const& e)
            {
                return;
            }
            for (int i = 1; i < SIZE_BOARD * SIZE_BOARD; i++)
            {
                num = strtok(NULL, ",");
                if (num == NULL)
                {
                    return;
                }
                try
                {
                    int row              = i / SIZE_BOARD;
                    int column           = i % SIZE_BOARD;
                    arrBomb[row][column] = std::stoi(num);  // don't call c_str()
                }
                catch (std::exception const& e)
                {
                    return;
                }
            }
        }

        s = UserDefault::getInstance()->getStringForKey("arrCell", "");
        if (s.size() <= 10)
        {
            return;
        }
        else
        {
            char* pch = new char[s.size() + 1];
            std::copy(s.begin(), s.end(), pch);
            pch[s.size()] = '\0';  // don't forget the terminating 0
            char* num;
            num = strtok(pch, ",");
            if (num == NULL)
            {
                return;
            }
            try
            {
                arrCell[0][0] = std::stoi(num);  // don't call c_str()
            }
            catch (std::exception const& e)
            {
                return;
            }
            for (int i = 1; i < SIZE_BOARD * SIZE_BOARD; i++)
            {
                num = strtok(NULL, ",");
                if (num == NULL)
                {
                    return;
                }
                try
                {
                    int row              = i / SIZE_BOARD;
                    int column           = i % SIZE_BOARD;
                    arrCell[row][column] = std::stoi(num);  // don't call c_str()
                }
                catch (std::exception const& e)
                {
                    return;
                }
            }
        }

        UserDefault::getInstance()->setBoolForKey("loadPlayTime", false);
        UserDefault::getInstance()->flush();
    }
}

void GameClient::loadTwenty()
{
    isFirstTimeTwenty = UserDefault::getInstance()->getBoolForKey("isFirstTimeTwenty", false);
   // isFirstTimeTwenty = true;
    highscoreSum      = UserDefault::getInstance()->getIntegerForKey("highscoreSum", 0);
}

void GameClient::loadBrick()
{
    highscoreBrick = UserDefault::getInstance()->getIntegerForKey("highscoreBrick", 0);
    // isFirstTimeTwenty = true;
    levelTypeBrick = 3;
    game->scoreBrick = 0;
    levelScore[3][1] = 0;
    levelScore[3][2] = 200;
    levelScore[3][3] = 500;
    levelScore[3][4] = 1000;
    levelScore[3][5] = 2000;
    levelScore[3][6] = 5000;
    levelScore[3][7] = 10000;
    levelScore[3][8] = 20000;
    levelScore[3][9] = 50000;
}

void GameClient::addScore(int score)
{
    game->scoreBrick = game->scoreBrick + score;
    GUIManager::getInstance().guiBrick->updateScore();

    if (speedBrick == 9)
        return;
    else
    {
        if (game->scoreBrick >= levelScore[levelTypeBrick][speedBrick + 1])
        {
            speedBrick++;
        }
        GUIManager::getInstance().guiBrick->updateSpeed();
    }
}

void GameClient::setCell(int x, int y)
{
    if (x < 0 || x > NUM_WIDTH - 1)
        return;
    if (y < 0 || y > NUM_HEIGHT - 1)
        return;
    dataBrick[y][x] = 1;
}

void GameClient::changeToPortrait() {
    if (!isLandscape)
        return;
    isLandscape = false;
    JNIUtils::changeToPortrait();
    auto director  = Director::getInstance();
    auto glview    = director->getRenderView();
    Size frameSize = glview->getFrameSize();
    glview->setFrameSize(frameSize.height, frameSize.width);
    if ((frameSize.width / frameSize.height) < (3.0f / 2.0f))
    {
        glview->setDesignResolutionSize(480, 800, ResolutionPolicy::FIXED_HEIGHT);
    }
    else
    {
        glview->setDesignResolutionSize(480, 800, ResolutionPolicy::FIXED_WIDTH);
    }
}

void GameClient::changeToLandscape() {
    if (isLandscape)
        return;
    isLandscape = true;
    JNIUtils::changeToLandscape();

    auto director = Director::getInstance();
    auto glview   = director->getRenderView();

    Size frameSize = glview->getFrameSize();
    glview->setFrameSize(frameSize.height, frameSize.width);
    if ((frameSize.height / frameSize.width) < (3.0f / 2.0f))
    {
        glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_WIDTH);
    }
    else
    {
        glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_HEIGHT);
    }
}

/*****************************  Native Callback method  *****************************/
extern "C" {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)

void Java_org_cocos2dx_cpp_AppActivity_nativeDataPreference(JNIEnv* env, jobject thiz, jstring accessToken)
{
    std::string resultData = env->GetStringUTFChars(accessToken, 0);
    game->receivePreference(resultData);
}

void Java_org_cocos2dx_cpp_AppActivity_highscoreDataPreference(JNIEnv* env, jobject thiz, jstring accessToken)
{
    std::string resultData = env->GetStringUTFChars(accessToken, 0);
    game->receiveHighscoreData();
}
void Java_dev_axmol_app_BaseActivity_nativeOnReward(JNIEnv* env, jobject thiz, jint num)
    {
        int n = (int)num;
        AXLOGD("vo day ne *** ");
        game->onReward(num);
    }
#endif
}
