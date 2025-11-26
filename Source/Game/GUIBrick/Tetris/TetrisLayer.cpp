#include "TetrisLayer.h"
#include "../../Utility/GameSound.h"
#include "../../GUIManager.h"
#include "TetrisLRightBrick.h"
#include "TetrisZLeftBrick.h"
#include "TetrisZRightBrick.h"
#include "TetrisSquare.h"
#include "TetrisColumnBrick.h"
#include "TetrisLLeftBrick.h"
#include "TetrisTBrick.h"
#include <stdlib.h> 
#include <time.h>
#include <stdio.h> 
#include "Game/Utility/GameUtility.h"

TetrisLayer::TetrisLayer(void):BaseGame()
{
	data = new TetrisBrickData();
    currentEntity        = new TetrisBaseEntity();
	currentEntity->state = 0;
	currentEntity->type = 0;
    nextEntity           = new TetrisBaseEntity();
	
}


TetrisLayer::~TetrisLayer(void)
{
}

void TetrisLayer::update()
{
	if(game->state == GameState::PAUSE)
		return;
    
	if (game->state == GameState::PLAY) {
		if (currentEntity != NULL)
		{
			currentEntity->update();
		}
 		data->checkScore();
 		data->checkEnd();
		changeData();
	}
	else if (game->state == GameState::SCORE) {
		data->update();
		changeData();
	} else {
		actEnd();
		changeData();
	}
}

void TetrisLayer::show()
{
	BaseGame::show();
	
}
void TetrisLayer::onButtonLeft()
{
	if(game->state == GAME_OVER)
	{
		//GUIManager::getInstance().guiBrick->showLevelLayer(true);
		return;
	}
	currentEntity->moveLeft();
        GameSound::playOpenCell();
	
}

void TetrisLayer::onButtonRight()
{
	if(game->state == GAME_OVER)
	{
	//	if( countTop >= 2)
			//GUIManager::getInstance().guiBrick->showLevelLayer(true);
		return;
	}
        GameSound::playOpenCell();
	currentEntity->moveRight();
	
}
void TetrisLayer::onButtonUp()
{
	if(game->state == GAME_OVER)
	{
		//if( countTop >= 2)
		//GUIManager::getInstance().guiBrick->showLevelLayer(true);
		return;
	}
}
void TetrisLayer::onButtonDown()
{
    if (game->state == GAME_OVER)
	{
		//if( countTop >= 2)
		//GUIManager::getInstance().guiBrick->showLevelLayer(true);
		return;
	}
	currentEntity->moveDown();
        GameSound::playMoveDown();
}
void TetrisLayer::onButtonRotate()
{
	if(game->state == GAME_OVER)
	{
		//if( countTop >= 2)
		//GUIManager::getInstance().guiBrick->showLevelLayer(true);
		return;
	}
    GameSound::playOpenCell();
	currentEntity->changeState();
	
}

void TetrisLayer::changeData()
{
	
	if (currentEntity != NULL)
		currentEntity->changeMap();
	data->changeMap();

	if(nextEntity != NULL)
	{
		for(int i = 0; i < nextEntity->data.size(); i++)
		{
			game->dataNext[nextEntity->data.at(i)->y][nextEntity->data.at(i)->x] = 1;
		}
	}
	changeEnd();	
}



void TetrisLayer::endGame()
{
	BaseGame::endGame();
	
}

void TetrisLayer::newGame()
{
	BaseGame::newGame();
	game->state = GameState::PLAY;
	data->newGame();
	nextData = -1;
	genNew();
}

void TetrisLayer::genNew()
{
	
	
// 	if(nextEntity != NULL)
// 	{
// 		currentEntity->setData(data);
// 		currentEntity = nextEntity;
// 	}
// 	else
// 	{
// 	if(currentEntity != NULL)
// 		currentEntity->setData(data);
// 	else
// 	{
// 		currentEntity = genEntity();
// 		currentEntity->makeState();
// 	}
		
// 	}
// 	nextEntity = genEntity();
	//nextEntity->makeState();

	


	if(nextData >= 0)
	{
		currentEntity->setData(data);
		currentEntity->type = nextData;
	}
	else
	{
		currentEntity->type = (int)(GameUtility::getRandom() * 7);
	}
	currentEntity->state = 0;
	currentEntity->makeState();
	currentEntity->setPos(NUM_WIDTH / 2, NUM_HEIGHT );

	nextData = (int)(GameUtility::getRandom() * 7);
	nextEntity->type = nextData;
	nextEntity->state = 0;
	nextEntity->makeState();
}

TetrisBaseEntity* TetrisLayer::genEntity()
{
    TetrisBaseEntity* currentEntity;
	
	float r = GameUtility::getRandom();
	float pad = 1.0f / 7.0f;
	//r = 0.1f;
	if (r < pad * 1) {
            currentEntity = new TetrisColumnBrick();
	} else if (r < pad * 2) {
            currentEntity = new TetrisLLeftBrick();
	} else if (r < pad * 3) {
            currentEntity = new TetrisLRightBrick();
	} else if (r < pad * 4) {
            currentEntity = new TetrisSquare();
	} else if (r < pad * 5) {
            currentEntity = new TetrisTBrick();
	} else if (r < pad * 6) {
            currentEntity = new TetrisZLeftBrick();
	} else {
            currentEntity = new TetrisZRightBrick();
	}
	return currentEntity;
}
