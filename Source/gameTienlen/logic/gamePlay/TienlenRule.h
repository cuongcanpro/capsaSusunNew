#pragma once
#include "axmol.h"
#ifndef TienlenRule_h__
#define TienlenRule_h__
#include "TienlenGroupCard.h"
#include "TienlenPlayerCard.h"
using namespace ax;
#define E_WRONG_SUIT     1 
#define E_WRONG_NUMBER   2 
#define E_WRONG_GROUP    3 
#define E_2_LAST         4 
#define E_NO_ERROR       5 
#define E_TU_QUY         6

class TienlenRule
{
public:
	TienlenRule(void);
	~TienlenRule(void);

	
	static  int CheckValidCard(TienlenGroupCard* LastCards,
		TienlenGroupCard* FollowCards, TienlenPlayerCard* PlayerCards);
	static bool inSanh(int arrayNumber[][5], int number);
	static bool inXam(int arrayNumber[][5], int number);
	static bool inPair(int arrayNumber[][5], int number);
	static bool inTuQuy(int arrayNumber[][5], int number);
	static bool inBaDoiThong(int arrayNumber[][5], int number);
	static bool haveNumber(int arrayNumber[][5], int number);

	static int getPair(int arrayNumber[][5]);
	static int getThree(int arrayNumber[][5]);
	static Vec2 getMauThau(int arrayNumber[][5]);
	static int getThoi(TienlenGroupCard* groupCard);
};
#endif // TienlenRule_h__

