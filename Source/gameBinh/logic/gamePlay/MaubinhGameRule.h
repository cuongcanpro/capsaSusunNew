#pragma once
#ifndef MaubinhGameRule_h__
#define MaubinhGameRule_h__
#include "MaubinhGroupCardLogic.h"
#include "MaubinhSoSanhBai.h"
#include "MaubinhPlayerCard.h"

class MaubinhGameRule
{
public:
	MaubinhGameRule(void);
	~MaubinhGameRule(void);
	static int SoSanhChi(MaubinhGroupCardLogic* gc1, MaubinhGroupCardLogic* gc2, bool isTinhAt = false);
	static int getId(int number, int suit);
	static int getPair(int arrayNumber[][5], int except);
	static int getThree(int arrayNumber[][5], int except);
	static Vec2 getMauThau(int arrayNumber[][5]);
	static int getNumber(int cardId);
	static bool inSanh(int arrayNumber[][5], int number, int except = -1);
	static bool inXam(int arrayNumber[][5], int number);
	static bool inPair(int arrayNumber[][5], int number);
	static bool inThung(int arrayNumber[][5], int suit, int except = -1);
	static void checkAt(int arrayNumber[][5], int arraySuit[][15], int number, int suit);
	
	MaubinhSoSanhBai* soSanhBai(MaubinhPlayerCard* pc1, MaubinhPlayerCard* pc2);

};
#endif // MaubinhGameRule_h__

