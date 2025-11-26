#ifndef TalaGameSound_h__
#define TalaGameSound_h__

#include <vector>
#include <string>
#include "axmol.h"
using namespace std;

class TalaGameSound
{
public:
	TalaGameSound();
	~TalaGameSound();
	static void stopMusic();
	
	static int playEffect(string path, bool loop = false, float volume = 1.0f);
	static int playRandom(vector<string> paths, bool loop = false, float volume = 1.0);
private:
	static int _playerVoice;
	static int _dealerVoice;
};
#endif // TalaGameSound_h__
