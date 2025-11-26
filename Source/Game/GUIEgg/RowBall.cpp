#include "RowBall.h"
#include "Game/Utility/GameUtility.h"
#include <Game/Logic/Constant.h>


RowBall::RowBall(void)
{
}

RowBall::RowBall( int _idRow )
{
	idRow = _idRow;
	if(_idRow % 2 == 0)
		typeRow = NINE_ROW;
	else
		typeRow = EIGHT_ROW;
	for(int i = 0; i < NINE_ROW; i++)
	{
		Ball* ball = new Ball((int)(GameUtility::getRandom() * NUM_BALL), idRow, i, typeRow);
		arrayBall.push_back(ball);
	}
	if(typeRow == EIGHT_ROW)
		arrayBall[NINE_ROW-1]->setVisible(false);
}

RowBall::RowBall( int _idRow, int typeRow )
{
	idRow = _idRow;
	this->typeRow = typeRow;

	for(int i = 0; i < NINE_ROW; i++)
	{
		Ball* ball = new Ball((int)(GameUtility::getRandom() * NUM_BALL), idRow, i, typeRow);
		arrayBall.push_back(ball);
	}
	if(typeRow == EIGHT_ROW)
		arrayBall[NINE_ROW-1]->setVisible(false);
}


RowBall::~RowBall(void)
{
}

void RowBall::moveDown( float f )
{
	for(int i = 0; i < arrayBall.size(); i++)
	{
		arrayBall[i]->setPosition(arrayBall[i]->getPositionX(), arrayBall[i]->getPositionY() - f);
	}
}

Ball* RowBall::getBall( int idColumn )
{
	if(arrayBall[idColumn]->isVisible())
		return arrayBall[idColumn];
	return NULL;
}

void RowBall::resetCheckConnect()
{
	for(int i = 0; i < arrayBall.size(); i++)
	{
		if(arrayBall[i]->isVisible())
			arrayBall[i]->isCheckConnect = false;
	}
}

void RowBall::copy( RowBall* rowBall )
{
	typeRow = rowBall->typeRow;
	for(int i = 0; i < arrayBall.size(); i++)
	{
		arrayBall[i]->copy(rowBall->arrayBall[i]);
	}	
}

void RowBall::decreaseRow( int num )
{
	for(int i = 0; i < arrayBall.size(); i++)
		arrayBall[i]->setIdRow(arrayBall[i]->idRow - num);
}

void RowBall::renew( int typeRow2 )
{
	typeRow = typeRow2;
	for(int i = 0; i < NINE_ROW; i++)
	{
		//	Ball ball = new Ball((int)(GameUtility::getRandom() * 4), idRow, i, typeRow);
		arrayBall[i]->setIdRow(idRow);
		arrayBall[i]->renew(typeRow);
	}
	if(typeRow == EIGHT_ROW)
		arrayBall[NINE_ROW-1]->setVisible(false);
}

void RowBall::newRow( int typeRow )
{
	this->typeRow = typeRow;

	for(int i = 0; i < NINE_ROW; i++)
	{
		arrayBall[i]->setIdRow(idRow);
		arrayBall[i]->newRow(typeRow);
	}
}

void RowBall::callbackRemove(Node* pSender )
{
	pSender->setVisible(false);
}

void RowBall::moveUp(int countUp)
{
	idRow = idRow + countUp;
	for(int i = 0; i < arrayBall.size(); i++)
	{
		arrayBall.at(i)->moveUp(countUp);
	}
}

void RowBall::setIdRow( int _idRow, int _typeRow )
{
	idRow = _idRow;
	this->typeRow = _typeRow;

	for(int i = 0; i < NINE_ROW; i++)
	{
		arrayBall[i]->setIdRow(idRow);
		arrayBall[i]->newRow(typeRow);
	}

	if(typeRow == EIGHT_ROW)
		arrayBall[EIGHT_ROW]->setVisible(false);
	
}

void RowBall::setVisibleAll()
{
	for(int i = 0; i < NINE_ROW; i++)
	{
		arrayBall[i]->setVisible(true);
	}
	if(typeRow == EIGHT_ROW)
		arrayBall[EIGHT_ROW]->setVisible(false);
}

void RowBall::effectNewGame(float delayTime)
{
	
	for (int i = 0; i < NINE_ROW; i++) {
		if (arrayBall[i]->isVisible()) {
			arrayBall[i]->setPositionY(arrayBall[i]->getPositionY() + 500);
			arrayBall[i]->runAction(Sequence::create(
				DelayTime::create(delayTime + 0.03 * i), 
				MoveBy::create(0.5, Vec2(0, -500)),
				NULL)
			);
		}
	}
}

std::vector<int> RowBall::getArrayId()
{
	vector<int> arrayId;
	for (int i = 0; i < NINE_ROW; i++) {
		if (arrayBall[i]->isVisible()) {
			if (std::count(arrayId.begin(), arrayId.end(), arrayBall[i]->idBall) >= 0) {
				arrayId.push_back(arrayBall[i]->idBall);
			}
			else {
			}
		}
	}
	return arrayId;
}
