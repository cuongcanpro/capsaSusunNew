#include "TalaGameSound.h"
#include "axmol.h"
#include <vector>
#include "audio/AudioEngine.h"
#include "app/GameMgr.h"
#include "core/utils/LanguageMgr.h"
#include "app/Constant.h"

using namespace std;


//board sound

TalaGameSound::TalaGameSound()
{
}

TalaGameSound::~TalaGameSound()
{
}


void TalaGameSound::stopMusic()
{
    
    //AudioEngine::stopBackgroundMusic();
}

int TalaGameSound::playEffect(string path, bool loop, float volume)
{
	int soundId = -1;
	if (gameMgr->getSetting().sound) {
	//	soundId = SimpleAudioEngine::getInstance()->playEffect(path.c_str(), loop);
		//SimpleAudioEngine::getInstance()->setEffectsVolume(MAX(0.f, MIN(1.f, volume)));
                AudioEngine::play2d(path);
	}
	return soundId;
}

int TalaGameSound::playRandom(vector<string> paths, bool loop, float volume)
{
	if (paths.size() > 0) {
		auto path = paths[ax::random() % paths.size()];
		return TalaGameSound::playEffect(path, loop, volume);
	}
	else return -1;
}
int TalaGameSound::_playerVoice = 0;
int TalaGameSound::_dealerVoice = 0;
