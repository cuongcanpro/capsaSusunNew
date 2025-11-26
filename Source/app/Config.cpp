#include "Config.h"

int Config::APP_VERSION_ANDROID = 0;

int Config::APP_VERSION_IOS = 0;

std::string Config::DEVICE_ID_W32 = "win32deviceid_tester01";

bool Config::ENABLE_NOTIFICATION = true;

std::string Config::SERVER_PRIVATE = "118.102.3.18";
int Config::PORT_PRIVATE = 10101;

std::string Config::SERVER_QC = "118.102.3.18";
int Config::PORT_QC = 10213;

std::string Config::SERVER_LOCAL = "127.0.0.1";
int Config::PORT_LOCAL = 468;

std::string Config::SERVER_LIVE = "118.102.3.12";
int Config::PORT_LIVE = 443;

//std::string Config::SERVER_LIVE = "34.94.99.83";
//int Config::PORT_LIVE = 443;

bool Config::DEV_LOCAL = false;
bool Config::ENABLE_CHEAT = false;

bool Config::PRELOAD_LAYER = true;
bool Config::ENABLE_EVENT = false;
bool Config::ENABLE_HOT_DEAL = true;
bool Config::ENABLE_IAP_LIMIT_TIME = true;

int Config::TIMEOUT_CONNECT_SERVER = 20;

bool Config::ENABLE_TOOL_TIP = true;

int Config::CHEAT_MAX_PLAYER = 4;

int Config::CHEAT_MAX_CARD = 14;

float Config::CARD_CHEAT_SCALE_DECK = 0.3f;

float Config::CARD_CHEAT_SCALE_PLAYER = 0.3f;

int Config::CARD_CHEAT_PLAYER_LINE = 2;

int Config::APP_VERSION_ANDROID_DEFAULT = 1;

int Config::APP_VERSION_IOS_DEFAULT = 1;

std::vector<int> Config::EMO_HAPPY = { 6, 7, 8, 9, 10 };        // id emo happy, use for Chiu
std::vector<int> EMO_SAD = { 1, 2, 3, 4, 5 };   // id emo sad
std::vector<int> EMO_WIN = { 6, 7, 8, 9, 10, 12, 11, 16 };

int Config::TOTAL_GAME_RATE_APP = 100;

int Config::TOTAL_GAME_RATE_APP_MIN = 20;

int Config::SESSION_GAME_RATE_APP = 5;

std::string Config::MAX_MEXICO = "334";

std::string Config::MAX_VIETNAM = "452";

std::string Config::COUNTRY_MX = "mx";

std::string Config::COUNTRY_GLOBAL = "us";

std::string Config::CHEAT_SAVE_SERVER_IP = "cheat_server_ip";

std::string Config::CHEAT_SAVE_SERVER_PORT = "cheat_server_port";

std::string Config::CHEAT_SAVE_DEVICE_ID = "cheat_save_device_id";
