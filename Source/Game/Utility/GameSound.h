#pragma once
#ifndef GameSound_h__
#define GameSound_h__

class GameSound
{
public:
	GameSound(void);
	~GameSound(void);

	
	static void loadSound();
	static void playSound(const char *sound);
	static void playClick();
	static void playCheck();

	static void playEat();

	static void playMove();

	static void playLose();

	static void playMyTurn();
    static void playEnd();
	static void playWin();
	static void playStartGame();
	static void playCountDown();
	static void playMessage();
	static void playJump();
	static void playScore(int score);
	static void playScore1();
	static void playScore2();
	static void playScore3();
	static void playScore4();
	static void playScore5();
	static void playScore6();
	static void playHit();
	static void playError();
	static void playFail();
	static void playChooseBall();
	static void playPass();
	static void playUpNumber();
	static void playNewNumber();
	static void playLevelUp();
	static void playDrop(int index);
	static void playEat(int index);
	static void playMusic();
	static void stopMusic();
	static void playBomb();
	static void playFirework();
    static void playTime();
    static void playThunder();
    static void playSoundLose();
    static void playSoundBreakBlock();
    static void playExtra();
    static void playScoreExtra();


    static void playBreakEgg();
    static void playEggLands();
    static void playWarn();
    static void playMama();
    static void playTicktock();
    static void playWhirley();
    static void playWhirleyHit();

    static void playBombGuess();
    static void playBombUnGuess();
    static void playOpenCell();

    static void playStartApp();
    static void playGameOver();
    static void playEatFull();
    static void playMoveDown();

    // sudoku
    static void playCorrect();
    static void playErase();
    static void playInvalid();
    static void playMark();
    static void playMistake();

    // 2048
    static void playMerge2048();
    static void playMove2048();
    static void playSpawn2048();
    static void playNewNumber2048();
    static void playWin2048();

    static void playWalk();
    static void playLand();
};
#endif // GameSound_h__

