#ifndef TetrisLayer_h__
#define TetrisLayer_h__

#include "../BaseGame.h"

#include "../Die.h"
#include "TetrisBaseEntity.h"
#include "TetrisBrickData.h"

class TetrisLayer :
	public BaseGame
{
public:
	TetrisLayer(void);
	~TetrisLayer(void);

	void update();
	void show();
	void onButtonDown();
	void onButtonLeft();
	void onButtonRight();
	void onButtonRotate();
	void onButtonUp();
	void changeData();
	void checkKeyPress();
	void checkEnd();
	void endGame();
	void newGame();
	void genNew();
    TetrisBaseEntity* genEntity();
	TetrisBaseEntity* currentEntity;
    TetrisBrickData* data;
	int nextData;
    TetrisBaseEntity* nextEntity;

};
#endif // TetrisLayer_h__

