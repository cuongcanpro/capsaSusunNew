#include "TetrisBrickData.h"
#include "Game/GameClient.h"
#include "Engine/GlobalVar.h"
#include "Game/Utility/GameSound.h"
#include "Game/GUIManager.h"
#include "Game/Utility/JNIUtils.h"

TetrisBrickData::TetrisBrickData(void)
{
	for(int i = 0; i < NUM_HEIGHT; i++)
		for(int j = 0; j < NUM_WIDTH; j++)
		{
			data[i][j] = 0;
		}

		countTime = 0;
		frame = DELTA_TIME;
}


TetrisBrickData::~TetrisBrickData(void)
{
}

void TetrisBrickData::update()
{
	if(arrayScore.size() > 0)
	{
		countTime = countTime + game->deltaTime;
		if(countTime > DELTA_TIME)
		{
			countTime = 0;
			for(int i = 0; i < arrayScore.size(); i++)
			{
				for(int j = 0; j < NUM_WIDTH; j++)
				{
					if(data[arrayScore.at(i)][j] == 1)
					{
						data[arrayScore.at(i)][j] = 0;
						break;
					}
				}
			}
			int i;
			for(i = 0; i < NUM_WIDTH; i++)
			{
				if(data[arrayScore.at(0)][i] == 1)
					return;
			}
			int count = 0;
			int countRow = 0;
			if( i == NUM_WIDTH)
			{
				for(i = 0; i < NUM_HEIGHT; i++)
				{
					if(arrayScore.size() == 0 ||i != arrayScore.at(0))
					{
						for(int j = 0; j < NUM_WIDTH; j++)
						{
							data[countRow][j] = data[i][j];

						}
						countRow++;


					}
					else
					{
						if(arrayScore.size() > 0)
						{
							if(i == arrayScore.at(0))
							{
								arrayScore.erase(arrayScore.begin());
							}
						}
					}
				}

				arrayScore.clear();
				game->state = GameState::PLAY;
			}
		}
	}
}

void TetrisBrickData::setCell( int x, int y )
{
	data[y][x] = 1;
}

void TetrisBrickData::changeMap()
{
	for(int i = 0; i < NUM_HEIGHT; i++)
		for(int j = 0; j < NUM_WIDTH; j++)
		{
			if(data[i][j] == 1)
				game->setCell(j, i);
		}
}

bool TetrisBrickData::inData( PointGame* point )
{
	for(int i = 0; i < NUM_HEIGHT; i++)
		for(int j = 0; j < NUM_WIDTH; j++)
		{
			if(data[i][j] == 1)
			{
				if(point->x == j && point->y == i)
					return true;
			}
		}

		return false;
}

void TetrisBrickData::checkScore()
{
	arrayScore.clear();
	for(int i = 0; i < NUM_HEIGHT; i++)
	{
		int j;
		for(j = 0; j < NUM_WIDTH; j++)
		{
			if(data[i][j] != 1)
				break;
		}
		if(j == NUM_WIDTH)
		{
			arrayScore.push_back(i);
			AXLOGD("GHI SCORE ");
		}
	}

	if(arrayScore.size() > 0)
	{
		
		GameSound::playEatFull();
		game->state = GameState::SCORE;
		switch (arrayScore.size()) {
		case 1:
			game->addScore(10);
			break;
		case 2:
			game->addScore(20);
			break;
		case 3:
			game->addScore(40);
			break;
		case 4:
			game->addScore(160);
			break;
		default:
			break;
		}
        JNIUtils::vibrate(10 * arrayScore.size());
	}
}

void TetrisBrickData::newGame()
{
	for(int i = 0; i < NUM_HEIGHT; i++)
		for(int j = 0; j < NUM_WIDTH; j++)
		{
			if(i < game->levelBrick - 1)
			{
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				data[i][j] = r > 0.5f ? 1 : 0;
			}
			else
			{
				data[i][j] = 0;
			}
		}
}

void TetrisBrickData::checkEnd()
{
	for(int i = 0; i < NUM_WIDTH; i++)
	{
		if(data[19][i] == 1)
		{
			
			GUIManager::getInstance().guiBrick->tetrisLayer->endGame();
			return;
		}
	}
}
