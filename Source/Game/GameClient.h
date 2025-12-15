
#ifndef GameClient1_h__
#define GameClient1_h__

#include "axmol.h"
#include <vector>
#include "Game/Logic/LevelData.h"
#include "extensions/axmol-ext.h"
#include "network/HttpClient.h"
#include "EffekseerForCocos2d-x.h"
#include "Logic/TutorialData.h"
#include "GUIPika/BoardDataPika.h"
using namespace std;

#define NUM_WIDTH      10
#define NUM_HEIGHT     20
#define DELTA_TIME     0.03f
#define NUM_LEVEL_BOMB 4
#define SIZE_BOARD     25

#define GAME_EGG       0
#define GAME_BLOCK     1
#define GAME_PIKA      2
#define GAME_BRICK     3
#define GAME_LINE      4
#define GAME_BOMB      5
#define GAME_DROP      6
#define GAME_POP       7
#define GAME_TWENTY    8
#define GAME_BUBBLE    9
#define GAME_TIENLEN   10
#define GAME_2048      11
#define GAME_SUDOKU      12
#define GAME_SWING    13
#define GAME_AA      14
#define GAME_CHESS     15
#define GAME_CARO    16

#define TOP_NORMAL 0
enum GameState
{
    PLAY,
    NORMAL_GAME,
    GAME_OVER,
    TOUCH,
    MOVE,
    EFFECT,
    NEXT_LEVEL,
    PAUSE,
    WAIT_PLAY,
    END_GAME,
    CHOOSE_REMOVE,
    SCORE
};
enum BallState
{
    JUMP,
    NORMAL,
    DISAPPEAR,
    SMALL,
    BIGGER
};
struct TopData {
	string name;
	string id;
	int typeTop;
	int score;
	int index;
};

enum Direct
{
	LEFT, RIGHT, UP, DOWN, UNDEFINE
};

class GameClient : public ax::Object
{
public:
    GameClient(void);
    ~GameClient(void);

    // Application Events
    bool applicationDidFinishLaunching();
    void applicationDidEnterBackground();
    void applicationWillEnterForeground();

    // Game Events
    void init();
    void initGame();
    void update(float delta);
    void loadingCompleted();
    void takeScreenshot();
    void loadShaders();
    void loadPreferences();
    void onPause();
    void onResume();
    void receivePreference(string data);

    // Gamelogic
    void createCow();
    void listenBackToForeground();

    static void endGame();

    string standartNum(int num);
    float deltaTime;
    bool vibrate;
    bool music;
    bool enableHard;
    bool isRussia;
    bool isInitAds;
    int isNeedIP;
    int extendGame;

    bool isIOS();
    int countPlayAllTime;
    string country;
    float timePlayGame;

    int data[81];
    int saveScore;
    bool showHelp;
    int countHelp;
    float scaleBall;
    float brightBall;
    int highscore;
    bool isPlaying;
    int typeBall;
    int typeBg;
    int typeBackground;
    int typeTheme;
    int showContinue;
    int useAds;
    int numDestroy;
    string message;

    float saveTime;
    bool showLanguage;
    int countFinishAds;
    int countNotFinishAds;

    int numNoBrick;
    int targetSpecial;
    TutorialData* arrayTutorialChallenge[10];

    int level;
    int scoreEndless;
    int scoreStomp[21];
    void readDataLevel(int level);
    void savePreference();
    vector<vector<int>> dataLevel[21];
    int typeRow[21];
    int numBall[21];
    bool isRead[21];
    int scoreTime;

    int arrayBall[9];

    void loadPlayNormal();
    void resetPlayNormal();

    void loadColor();

    void resetColor();
    string getHighscoreData();
    void receiveHighscoreData();

    int saveScoreBubble;
    int highscoreBubble;
    bool isPlayingBubble;
    int dataBubble1[63];
    int dataBubble[45];
    bool showHelpBubble;
    int saveRandBubble[5];
    int saveRandBubble1[7];
    int saveScoreBubble1;
    int highscoreBubble1;
    bool isPlayingBubble1;

    void loadBubble();

     bool showHelpTouch;
    int highscorePop;
    int bestNum;
    int highscorePopHard;
    int bestNumHard;

    void loadPop();

    int dataPika[BOARD_COLUMN_PIKA * BOARD_ROW_PIKA];
    int saveScorePika;
    bool isPlayingPika;
    int levelPika;
    float timePika;
    int numLifePika;
    int highscorePika;
    void loadPika();

    bool showHelpBlock;
    int arrayNextBlock[3];
    int arrayBonus[3];
    int dataBlockPuzzel[8][8];
    int highscoreBlock;
    int saveScoreBlock;
    bool isPlayingBlock;
    int numPlayBlock;
    void loadBlock();

    bool showHelpBomb;
    int arrBestTime[NUM_LEVEL_BOMB];
    int currentTime;
    int arrBomb[SIZE_BOARD][SIZE_BOARD];
    int arrCell[SIZE_BOARD][SIZE_BOARD];
    int currentMode;
    void loadBomb();
    
    
    bool isFirstTime;
    bool isFirstTimeTwenty;
    int highscoreSum;
    void loadTwenty();

    int dataBrick[NUM_HEIGHT][NUM_WIDTH];
    int dataNext[4][4];
    int levelScore[10][10];
    int levelBrick;
    int speedBrick;
    int levelTypeBrick;
    int scoreBrick;
    int highscoreBrick;
    void addScore(int score);
    void setCell(int x, int y);
    GameState state;
    GameState saveState;
    void loadBrick();

    string arrayGame;
    vector<int> arrayIdGame;
    int scoreEnable;
    int targetOldScore;
    int timeShow;
    float timeNoAds;
    int showNewGame;
    int numPlayGame;
    void showAdsForOldUser(bool isUndo = false);
    void changeDesignSolution(bool is3D);

    void getVersion();
    void onVersionCompleted(ax::network::HttpClient* sender, ax::network::HttpResponse* response);
    efk::EffectManager* manager = nullptr;

    void showUpdate();
    void showMessage();
    void onReward(int num);
    time_t timeToGetVersion;
    time_t timeBackground;
    void initAds();
    int useReward;
    int numDivide;
    void showAdsFull();
    int sourceApp; // app duoc cai dat tu dau
    int receiveReward;
    void checkReward();
    bool isLandscape;
    void changeToPortrait();
    void changeToLandscape();
};
#endif // GameClient_h__




