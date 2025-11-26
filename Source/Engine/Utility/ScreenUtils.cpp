#include "ScreenUtils.h"

//namespace
static bool s_bFirstRun = true;
static ScreenUtils* s_shareScale;
static const char* SCREEN_CONFIG = "screen.csv";
Size defauleSpriteSize = Size(1,1);
ScreenUtils* ScreenUtils::share(){
	if (s_bFirstRun)
	{
		s_shareScale = new ScreenUtils();
		s_shareScale->init();
		s_bFirstRun = false;
	}
	return s_shareScale;
}
bool ScreenUtils::init(){

	return true;
}
void ScreenUtils::findSize(){
	
}
std::string ScreenUtils::fileFull(const char* fileName){
	std::stringstream ss;
// 	if(GameConfig::shared()->isEncryptImage()){
// 		ss<<""<<(int)ScreenUtils::share()->getSpriteSize().width<<"_"<<(int)ScreenUtils::share()->getSpriteSize().height<<"_encrypt"<<"/"<<fileName;
// 	}
// 	else
// 	{
		//ss<<""<<(int)ScreenUtils::share()->getSpriteSize().width<<"_"<<(int)ScreenUtils::share()->getSpriteSize().height<<"/"<<fileName;
	//}
        ss << "GuiGame/" << fileName;
	return ss.str();
}
std::string ScreenUtils::fileCommon(const char* fileName){
	std::stringstream ss;
// 	if(GameConfig::shared()->isEncryptCommon()){
// 		ss<<"common_encrypt"<<"/"<<fileName;
// 	}
// 	else
// 	{
		ss<<"common/"<<fileName;
//	}
	return ss.str();
}
float ScreenUtils::defaultScale(){
	return ScreenUtils::share()->getScale();
}
float ScreenUtils::imageScale(){
	return ScreenUtils::share()->getImageScale();
}


float ScreenUtils::textureRatio()
{
	return ScreenUtils::share()->_texture_Ratio;
}
