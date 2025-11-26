#ifndef _BoardPop_h__
#define _BoardPop_h__
#include "axmol.h"
#include "Engine/GUI/GameImage.h"


#include "PopObjectNumber.h"
#include "Game/Data/GlobalData.h"
#include "Game/Logic/PointGame.h"
#include <vector>
#include "Engine/GUI/ImageEffect.h"
#include "BoardDataPop.h"
#include "EffekseerForCocos2d-x.h"
using namespace std;
using namespace ax;
using namespace ax::ui;
#define RATE_SIZE 1.05
#define MOVE_DOWN_TIME 0.13
#define DELAY_CHECK_DOWN_TIME 0.16
#define MOVE_EAT_TIME 0.13
#define DELAY_CHECK_EAT_TIME 0.16
#define MOVE_NUMBER_SPEED -1.1

enum PopState {
	POP_NORMAL, POP_WILL_USE_BOMB, POP_BOMB, POP_EFFECT, POP_END
};
class BoardPop : public Layout
{
public:
	BoardPop(void);
	~BoardPop(void);
	BoardDataPop* data;
	PopState state;
	PopObjectNumber* arrayNumber[BOARD_ROW_POP][BOARD_COLUMN_POP];
	float sizeCell;
	vector<PointGame> arrayChange;
	vector <Text*> arrayLabel;
	int countEat;
	vector <ImageEffect*> arrayImageEffect;
	Text* lbNotMove;
    efk::EffectEmitter* effBomb;
    MotionStreak* _streak;
    float timeNoTouch;
    MotionStreak* arrayStreak[10];
    PointGame pointDestroy;
	void updateBoardSize();
	void newGame();
	void saveGame();

	void doTouchEnd(float posX, float posY);
	void callbackEffectEndGame();
	void callbackEffectEndGame1();
    void effectImage(PopObjectNumber* ball);
	bool checkInBoard(float posX, float posY);

	void playParticle(float posX, float posY, int id);
	void update(float delta);
	void effectScore(int score, Vec2 pos);
	Vec2 convertToPosition(int row, int column);
    void callbackDestroy();
	void callbackAfterMove();
	void genNew();
	void callbackGenNew();
	void callbackNoMove();
    void endGame();
	void useBomb();
	void effectBomb(Vec2 pos);
    Vec2 getPosCell(int row, int column);

	vector <Sprite*> arraySmoke;
	Sprite* getSmoke();
};
#endif
