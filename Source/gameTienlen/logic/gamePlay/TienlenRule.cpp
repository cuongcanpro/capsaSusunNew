#include "TienlenRule.h"


TienlenRule::TienlenRule(void)
{
}


TienlenRule::~TienlenRule(void)
{
}


int TienlenRule::CheckValidCard(TienlenGroupCard* LastCards,
								  TienlenGroupCard* FollowCards, TienlenPlayerCard* PlayerCards)
{
	if(FollowCards->GetNumOfCards() <= 0 || LastCards->GetNumOfCards() < 0)
		return E_WRONG_GROUP;

	// check xem co bo nay trong quan bai ko:
	for (int CardID=0;CardID<FollowCards->GetNumOfCards();CardID++)
	{
		int CardResult = 0;
		CardResult = PlayerCards->SearchCard(FollowCards->Cards.at(CardID));
		if (CardResult == -1)
		{
			return E_WRONG_NUMBER;
		}
	}
	// Neu danh xuong khong phai mot bo thi thoi luon
	if(FollowCards->GetGroupKind() == EG_NONE)
	{

		return E_WRONG_GROUP;
	}

	// Check khong duoc de 2 cuoi cung
	//PlayerCards->RemoveGroupCard(FollowCards);
	//if(PlayerCards->Leave2Last())
	//return E_2_LAST;

	// Tiennv_BC ShowCard
	// If this is the first card of the round, then whatever
	if (LastCards->GetNumOfCards() == 0)
	{
		return E_NO_ERROR;
	}
	// Check for super group :
	if (FollowCards->GetGroupKind() == EG_SUPER)
	{
		// 1 quan heo, 2 heo
		if ( (LastCards->GetNumOfCards() == 1) || (LastCards->GetNumOfCards() == 2))
		{
			if (LastCards->GetNumber() != 15)
			{
				return E_WRONG_GROUP;
			}
			else 
				return E_NO_ERROR;
		}
		// 3 doi thong
		else if (LastCards->GetGroupKind() == EG_BIGGER)
		{
			return E_NO_ERROR;
		}
		// 4 doi thong nho hon
		else if (LastCards->GetGroupKind() == EG_SUPER)
		{
			if(FollowCards->GetNumber() < LastCards->GetNumber())
			{
				return E_WRONG_NUMBER;
			}
			if (FollowCards->GetNumber() == LastCards->GetNumber())
			{
				if (FollowCards->GetBiggestSuit() < LastCards->GetBiggestSuit())
					return E_WRONG_GROUP;
			}
			return E_NO_ERROR;
		}
		// tuqui
		else if (LastCards->GetNumOfCards() == 4)
		{
			if (LastCards->GetGroupKind() == EG_NORMAL)
			{

				return E_NO_ERROR;
			}
		}
		return E_WRONG_GROUP;
	}

	if (FollowCards->GetGroupKind() == EG_ULTRA) //5 doi thong
	{
		//20110127 truclc
		if (LastCards->GetNumOfCards() == 3)
		{
			if (LastCards->Cards.at(0)->GetNumber() == 15)
				return E_WRONG_GROUP;
		}
		//20110127 truclc
		return E_NO_ERROR;
	}


	// Tiennv_EC ShowCard
	// Neu so quan danh khac voi so quan truoc do return wrong
	if(FollowCards->GetNumOfCards() != LastCards->GetNumOfCards())
	{
		bool tuqui = false;
		bool BiggerGroup = false;
		if (LastCards->GetNumOfCards() == 1)
		{
			if(LastCards->GetNumber() == 15)
			{
				if(FollowCards->GetNumOfCards() == 4)
				{
					if(FollowCards->GetGroupKind() == EG_NORMAL)
						tuqui = true; 
				}
				if(FollowCards->GetNumOfCards() == 6)
				{
					if(FollowCards->GetGroupKind() == EG_BIGGER)
						BiggerGroup = true; 
				} 
			}
		}
		else if (LastCards->GetNumOfCards() == 2)
		{

			if(LastCards->GetNumber() == 15)
			{

				if(FollowCards->GetNumOfCards() == 4)
				{

					if(FollowCards->GetGroupKind() == EG_NORMAL)
					{

						tuqui = true; 
					}
				} 
			}
		}
		else if (LastCards->GetNumOfCards() == 6)
		{
			if(LastCards->GetGroupKind() == EG_BIGGER)
			{
				if(FollowCards->GetNumOfCards() == 4)
				{
					if(FollowCards->GetGroupKind() == EG_NORMAL)
						BiggerGroup = true; 
				}
			}
		}
		if(tuqui)
		{
			return E_NO_ERROR;
			//return E_TU_QUY;
		}
		else if (BiggerGroup)
		{
			return E_NO_ERROR;
		}
		else
			return E_WRONG_GROUP;
	}

	// Check for bigger group :
	if (FollowCards->GetGroupKind() == EG_BIGGER)
	{
		if (LastCards->GetGroupKind() == EG_BIGGER)
		{
			if(FollowCards->GetNumber() < LastCards->GetNumber())
				return E_WRONG_NUMBER;
			if (FollowCards->GetNumber() == LastCards->GetNumber())
			{
				if (FollowCards->GetBiggestSuit() < LastCards->GetBiggestSuit())
					return E_WRONG_GROUP;
			}
			return E_NO_ERROR;
		}
	}
	// Neu quan bai hop le
	switch(FollowCards->GetGroupKind())
	{
	case EG_ONECARD:
	case EG_NORMAL:   
		//if(FollowCards->GetSuit() != LastCards->GetSuit())      
		//  if(FollowCards->GetNumber() != 15) //15 tuc la 2
		//    return E_WRONG_SUIT;
		//  else
		//  {
		//if (LastCards->GetNumber() == 15)
		if (FollowCards->GetNumber() == LastCards->GetNumber())
		{
			if (FollowCards->GetBiggestSuit() < LastCards->GetBiggestSuit())
				return E_WRONG_SUIT;
		}
		//  }
		if(FollowCards->GetNumber() < LastCards->GetNumber())
			return E_WRONG_NUMBER;

		if (LastCards->GetGroupKind() == EG_SEQUENCE)
		{
			return E_WRONG_NUMBER;
		}

		return E_NO_ERROR;  
	case EG_SEQUENCE:
		// Bo sequence khong the chat 3 & 4 doi thong:
		if ( (LastCards->GetGroupKind() == EG_SUPER)
			||
			(LastCards->GetGroupKind() == EG_BIGGER) )
		{
			return E_WRONG_GROUP;
		}
		if(FollowCards->GetNumber() < LastCards->GetNumber())
			return E_WRONG_NUMBER;
		if (FollowCards->GetNumber() == LastCards->GetNumber())
		{
			if (FollowCards->GetBiggestSuit() < LastCards->GetBiggestSuit())
				return E_WRONG_GROUP;
		}
		if (LastCards->GetGroupKind() == EG_NORMAL)
		{
			return E_WRONG_NUMBER;
		}
		return E_NO_ERROR; 
	}
	return E_WRONG_NUMBER;

}


bool TienlenRule::inSanh(int arrayNumber[][5], int number)
{
	int count = 1;
	for (int i = number + 1; i < 15; i++) {
			int j;
			for (j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					break;
				}
			}
			if (j < 5) {
				count++;
			}
			else {
				break;
			}
	}
	for (int i = number - 1; i > 2; i--) {
			int j;
			for (j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					break;
				}
			}
			if (j < 5) {
				count++;
			}
			else {
				break;
			}
	}
	if (count >= 3)
		return true;
	return false;
}

bool TienlenRule::inXam(int arrayNumber[][5], int number)
{
	int count = 0;
	for (int i = 1; i < 5; i++) {
		if (arrayNumber[number][i] == 1)
			count++;
	}
	if (count >= 3)
		return true;
	return false;
}

bool TienlenRule::inTuQuy(int arrayNumber[][5], int number)
{
	int count = 0;
	for (int i = 1; i < 5; i++) {
		if (arrayNumber[number][i] == 1)
			count++;
	}
	if (count == 4)
		return true;
	return false;
}

bool TienlenRule::inPair(int arrayNumber[][5], int number)
{
	int count = 0;
	for (int i = 1; i < 5; i++) {
		if (arrayNumber[number][i] == 1)
			count++;
	}
	if (count >= 2)
		return true;
	return false;
}

bool TienlenRule::inBaDoiThong(int arrayNumber[][5], int number)
{
	int count = 1;
	for (int i = number + 1; i < 15; i++) {
		if (TienlenRule::inPair(arrayNumber, i)) {
			count++;
		}
		else {
			break;
		}
	}
	for (int i = number - 1; i > 2; i--) {
		if (TienlenRule::inPair(arrayNumber, i)) {
			count++;
		}
		else {
			break;
		}
	}
	if (count >= 3)
		return true;
	return false;
}


bool TienlenRule::haveNumber(int arrayNumber[][5], int number)
{
	for (int j = 1; j < 5; j++) {
		if (arrayNumber[number][j] == 1) {
			return true;
		}
	}
	return false;
}

Vec2 TienlenRule::getMauThau(int arrayNumber[][5])
{
	int temp = -1;
	int state = 0;
	while (state < 5) {
		for (int i = 3; i < 15; i++) {
			int count = 0;
			int suit;

			// phai khong nam trong doi, sanh va count = 1
			for (int j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					count++;
					suit = j;
				}
			}
			if (!TienlenRule::inSanh(arrayNumber, i) && !TienlenRule::inPair(arrayNumber, suit)) {
				return Vec2(i, suit);
			}
		}
		state++;
	}
	return Vec2(0, 0);
}

int TienlenRule::getThoi(TienlenGroupCard* groupCard)
{
	int groupkind = groupCard->GetGroupKind();
	switch (groupkind)
	{
	case EG_TU_QUY:
	case EG_BIGGER:
	case EG_SUPER:
	case EG_ULTRA:
		return 4;
		break;
	case EG_NORMAL:
	case EG_ONECARD: {
		int count = 0;
		if (groupCard->GetNumber() == 15) {
			for (int i = 0; i < groupCard->Cards.size(); i++) {
				if (groupCard->Cards.at(i)->ID == 50 || groupCard->Cards.at(i)->ID == 51) {
					count = count + 2;
				}
				else {
					count = count + 1;
				}
			}
		}
		else if (groupCard->GetNumOfCards() == 4) {
			count = 4;
		}
		return count;
		break;
	}
	default:
		break;
	}
	return 0;
}

int TienlenRule::getPair(int arrayNumber[][5])
{
	for (int i = 2; i < 15; i++) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				// phai khong nam trong xam va sanh
				if (!TienlenRule::inXam(arrayNumber, j) && !TienlenRule::inSanh(arrayNumber, i)) {
					count++;
				}
			}
		}
		if (count == 2) {
			return i;
		}
	}
	return -1;
}

int TienlenRule::getThree(int arrayNumber[][5])
{
	for (int i = 2; i < 15; i++) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				// phai khong nam trong xam va sanh
				if (!TienlenRule::inTuQuy(arrayNumber, j) && !TienlenRule::inSanh(arrayNumber, i)) {
					count++;
				}
			}
		}
		if (count == 2) {
			return i;
		}
	}
	return -1;
}
