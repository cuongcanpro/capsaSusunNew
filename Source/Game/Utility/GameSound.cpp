#include "GameSound.h"
#include "SoundResources.h"
#include "Engine/GlobalVar.h"
//#include "GameUtility.h"
#include "audio/AudioEngine.h"
GameSound::GameSound(void)
{
}


GameSound::~GameSound(void)
{
}


void GameSound::playSound( const char *sound )
{
	if(game->music)
	{
		AudioEngine::play2d(sound);
	}
	
}

void GameSound::loadSound()
{
	AudioEngine::preload(SOUND_CLICK);
	AudioEngine::preload(SOUND_EAT);
	AudioEngine::preload(SOUND_LOSE);
	AudioEngine::preload(SOUND_MOVE);
	AudioEngine::preload(SOUND_WIN);
	AudioEngine::preload(UP_NUMBER);
	AudioEngine::preload(NEW_NUMBER);
	AudioEngine::preload(LEVEL_UP);
    AudioEngine::preload(SOUND_END);
    AudioEngine::preload(SOUND_LOSE_SOUND);
}

void GameSound::playClick()
{
	playSound(SOUND_CLICK);
}

void GameSound::playLose()
{
	playSound(SOUND_LOSE);
}

void GameSound::playWin()
{
	playSound(SOUND_WIN);
}

void GameSound::playCheck()
{
}

void GameSound::playEat()
{
	playSound(SOUND_EAT);
}


void GameSound::playMyTurn()
{}

void GameSound::playEnd() {
    playSound(SOUND_END);
}

void GameSound::playMove()
{
	playSound(SOUND_MOVE);
}

void GameSound::playStartGame()
{
	playSound(SOUND_START);
}

void GameSound::playCountDown()
{
	playSound(SOUND_COUNT_DOWN);
}

void GameSound::playMessage()
{
}

void GameSound::playJump()
{
    playSound(SOUND_JUMP);
}

void GameSound::playScore(int score)
{
	playSound(("sounds/mobile/Score" + to_string(score) + ".mp3").c_str());
}

void GameSound::playScore1()
{
	playSound(SOUND_SCORE1);
}
void GameSound::playScore2()
{
	playSound(SOUND_SCORE2);
}
void GameSound::playScore3()
{
	playSound(SOUND_SCORE3);
}
void GameSound::playScore4()
{
	playSound(SOUND_SCORE4);
}
void GameSound::playScore5()
{
	playSound(SOUND_SCORE5);
}

void GameSound::playHit()
{
	playSound(SOUND_HIT);
}

void GameSound::playError()
{
}

void GameSound::playScore6()
{
	playSound(SOUND_SCORE5);
}

void GameSound::playFail()
{
    playSound(SOUND_FAIL);
}

void GameSound::playChooseBall()
{
    playSound(SOUND_CHOOSE_BALL);
}

void GameSound::playPass()
{
}

void GameSound::playUpNumber()
{
	playSound(UP_NUMBER);
}

void GameSound::playNewNumber()
{
	playSound(NEW_NUMBER);
}

void GameSound::playLevelUp()
{
	playSound(LEVEL_UP);
}

void GameSound::playDrop(int index)
{
	if (index >= 6)
		index = 6;
	//index = 7;
	string s = "GameSound/drop" + to_string(index) + ".mp3";
	playSound(s.c_str());
}

void GameSound::playEat(int index)
{
	if (index >= 7)
		index = 7;
	string s = "GameSound/seed_3_0" + to_string(index) + ".mp3";
	playSound(s.c_str());
}

void GameSound::playMusic()
{
	
}

void GameSound::stopMusic()
{
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
}

void GameSound::playBomb()
{
	playSound(SOUND_BOMB);
}

void GameSound::playFirework()
{
	playSound(SOUND_FIREWORK);
}

void GameSound::playTime() {
    playSound(SOUND_TIME);
}

void GameSound::playThunder() {
    playSound(SOUND_THUNDER);
}

void GameSound::playSoundLose()
{
    playSound(SOUND_LOSE_SOUND);
}

void GameSound::playSoundBreakBlock()
{
    playSound(SOUND_BREAK_BLOCK);
}

void GameSound::playExtra() {
    playSound(SOUND_EXTRA);
}

void GameSound::playScoreExtra()
{
    playSound(SOUND_SCORE_EXTRA);
}

void GameSound::playBreakEgg()
{
    playSound(SOUND_BREAK_EGG);
}

void GameSound::playEggLands()
{
    playSound(SOUND_EGG_LAND);
}

void GameSound::playWarn()
{
    playSound(SOUND_WARN);
}

void GameSound::playMama()
{
    playSound(SOUND_MAMA);
}

void GameSound::playTicktock()
{
    playSound(SOUND_TICK_TOCK);
}
void GameSound::playWhirley()
{
    playSound(SOUND_WHIRLEY_SIREN);
}

void GameSound::playWhirleyHit()
{
    playSound(SOUND_WHIRLEY_HIT);
}

void GameSound::playBombGuess()
{
    playSound(SOUND_BOMB_GUESS);
}

void GameSound::playBombUnGuess()
{
    playSound(SOUND_BOMB_UN_GUESS);
}

void GameSound::playOpenCell()
{
    playSound(SOUND_OPEN_CELL);
}

void GameSound::playStartApp() {
    playSound(SOUND_START);
}
void GameSound::playGameOver() {
    playSound(SOUND_END);
}
void GameSound::playEatFull() {
    playSound(SOUND_EAT);
}

void GameSound::playMoveDown() {
    playSound(SOUND_MOVE_DOWN);
}

void GameSound::playCorrect()
{
    playSound("GameSound/sudoku/correct.mp3");
}

void GameSound::playErase()
{
    playSound("GameSound/sudoku/erase.mp3");
}

void GameSound::playInvalid()
{
    playSound("GameSound/sudoku/invalid.mp3");
}

void GameSound::playMark()
{
    playSound("GameSound/sudoku/mark.mp3");
}

void GameSound::playMistake()
{
    playSound("GameSound/sudoku/mistake.mp3");
}

void GameSound::playMove2048()
{
    playSound("GameSound/2048/move.mp3");
}

void GameSound::playMerge2048()
{
    int rand = AXRANDOM_0_1() * 2.999 + 1;
    playSound(("GameSound/2048/merger_" + to_string(rand) + ".mp3").c_str());
}

void GameSound::playSpawn2048()
{
    int rand = AXRANDOM_0_1() * 2.999 + 1;
    playSound(("GameSound/2048/swoosh_" + to_string(rand) + ".mp3").c_str());
}

void GameSound::playNewNumber2048()
{
    playSound("GameSound/2048/newNumber.mp3");
}

void GameSound::playWin2048()
{
    playSound("GameSound/2048/2048win.mp3");
}

void GameSound::playWalk()
{
    playSound("GameSound/footstep.mp3");
}

void GameSound::playLand()
{
    playSound("GameSound/land.mp3");
}
