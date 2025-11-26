#include "BaseGame.h"
#include "../Utility/GameSound.h"
#include "../GameClient.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"



BaseGame::BaseGame(void)
{
	Size size =  Director::getInstance()->getRenderView()->getVisibleSize();
	width = size.width;
	height = size.height;
	isSplash = false;
	frameEnd = DELTA_TIME * 0.7;
	countTimeEnd = 0;
	countTime = 0;
	index = 0;
	stateEnd = 0;
	countEnd = 0;
	countLeft = countRight = countBottom = countTop = 0;
	isLevel = false;
}


BaseGame::~BaseGame(void)
{
}

void BaseGame::update()
{
    
}

void BaseGame::actEnd()
{
	if(music && !isSplash)
		GameSound::playGameOver();
	music = false;
	countTimeEnd = countTimeEnd + game->deltaTime;

	if(countTimeEnd >= frameEnd)
	{
		switch (stateEnd) {
		case 0:
			dataEnd[NUM_HEIGHT - 1 - countTop][index + countLeft] = 1;
			index++;

			if(index == NUM_WIDTH - countLeft - countRight)
			{
				index = 0;
				stateEnd = 1;
				countTop++;
			}
			break;
		case 1:
			dataEnd[NUM_HEIGHT - countTop - index][NUM_WIDTH - 1 - countRight] = 1;
			index++;

			if(index == NUM_HEIGHT - countBottom - countTop)
			{
				index = 0;
				stateEnd = 2;
				countRight++;
			}
			break;
		case 2:
			dataEnd[countBottom][NUM_WIDTH - countRight - index] = 1;
			index++;

			if(index == NUM_WIDTH - countLeft - countRight + 1)
			{
				index = 0;
				stateEnd = 3;
				countBottom++;
			}
			break;
		case 3:
			dataEnd[countBottom + index][countLeft] = 1;
			index++;

			if(index == NUM_HEIGHT - countBottom - countTop)
			{
				if(countLeft < 4)
				{
					index = 0;
					stateEnd = 0;
					countLeft++;
				}
				else
				{
					if(isSplash)
					{
						/*for(int i = 0; i < 20; i++)
							for(int j = 0; j < 10; j++)
								dataEnd[i][j] = game->splash[i][j];
						countTop = countBottom = countRight = countLeft = 0;
						stateEnd = 0;
						index = 0;*/
					}
					else
					{
						
						//GUIManager::getInstance().guiBrick->showLevelLayer(true);
						//	MyCaro.game.caroScreen.showLevelLayer();

						// show quang cao
						//UtilityGettor.inst().showPopup();
                        game->showAdsFull();
					}
					
				}
			}
			break;
		default:
			break;
		}

		countTimeEnd = 0;
	}
}

void BaseGame::endGame()
{
	isEnd = true;
	game->state = GameState::GAME_OVER;
	countTime = 0;
	countEnd++;

	if(height <= 480)
	{
		//UtilityGettor.inst().showAds(true);
	}
}

void BaseGame::changeEnd()
{
	if(isEnd)
	{
		for (int i = 0; i < NUM_HEIGHT; i++) {
			for (int j = 0; j < NUM_WIDTH; j++)
				if(dataEnd[i][j] == 1)
					game->dataBrick[i][j] = 1;
		}
	}
}

void BaseGame::newGame()
{
	if(!isSplash && !isLevel)
		GameSound::playStartGame();
	countTime = 0;
	game->state = GameState::PLAY;
	countTimeEnd = 0;
	index = 0;
	countBottom = countLeft = countRight = countTop = 0;
	stateEnd = 0;

	for (int i = 0; i < NUM_HEIGHT; i++) {
		for (int j = 0; j < NUM_WIDTH; j++)
			dataEnd[i][j] = 0;

	}

}

void BaseGame::show()
{
	if(!isSplash)
	{
		isEnd = false;
		countEnd = 0;
		music = true;
		newGame();
		GUIManager::getInstance().guiBrick->updateLabelGame();
	}
	
}

void BaseGame::onButtonLeft()
{

}

void BaseGame::onButtonRight()
{

}
void BaseGame::onButtonUp()
{

}
void BaseGame::onButtonDown()
{

}
void BaseGame::onButtonRotate()
{

}

void BaseGame::changeData()
{

}
