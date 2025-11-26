#ifndef _GroupCenter_h__
#define _GroupCenter_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"


#include "ObjectNumber.h"
#include "Game/Data/GlobalData.h"
#include <vector>
#include "Engine/GUI/ImageEffect.h"
#include <Game/Logic/Constant.h>
#include "Game/Logic/PointGame.h"
using namespace std;
using namespace ax;
using namespace ax::ui;
#define RATE_SIZE 1.05
#define MOVE_DOWN_TIME 0.13
#define DELAY_CHECK_DOWN_TIME 0.16
#define MOVE_EAT_TIME 0.13
#define DELAY_CHECK_EAT_TIME 0.16
#define MOVE_NUMBER_SPEED -1.1

enum GroupState {
	GROUP_MOVE, GROUP_GEN, GROUP_END
};
class GroupCenter : public Layout
{
public:
	GroupCenter(void);
	~GroupCenter(void);

	int lastColumn;
	int numEat;
	int maxNum;
	int tutorialIndex;
	bool isTutorial;
	bool isPause;
	float speedDown;

	Sprite* iconHand;
	GroupState state;
	ObjectNumber* arrayNumber[NUM_ROW_MERGE][NUM_COLUMN_MERGE];
	ObjectNumber* moveNumber;
	ObjectNumber* nextNumber;
	float sizeCell;
	vector<PointGame> arrayChange;
	Sprite* arrayBgColumn[NUM_COLUMN_MERGE];
	Sprite* arrayArrow[NUM_COLUMN_MERGE];
	Sprite* spriteColumnEffect;
	vector <ImageEffect*> arrayImageEffect;
	vector <Text*> arrayLabel;
	

	void newGame();
	void saveGame();

	void genBall();
	void callbackGenBall();
	void doDropBall(float posX, float posY);
	bool checkEndGame(int index);
	void callbackEffectEndGame();
	void callbackEffectEndGame1();
	void effectImage(ObjectNumber* ball);
	void dropToIndex(int index, int column, float time);
	void doMoveBall(float posX, float posY);
	bool checkInBoard(float posX, float posY);

	bool checkEat(int row, int column);
	void callbackEat();
	void checkEatAfterFall();
	void pushChange(int row, int column);

	void playParticle(float posX, float posY, int id);
	void update(float delta);
	void doTutorial();
	void resumeGame();
	void effectScore(ObjectNumber* number);

	vector <Sprite*> arraySmoke;
	Sprite* getSmoke();
};
#endif
