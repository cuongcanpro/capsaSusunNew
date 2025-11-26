#ifndef TalaSuit_h__
#define TalaSuit_h__

#include <vector>
#include "Card.h"
#include "axmol.h"
using namespace std;

class TalaSuit {
public:
	TalaSuit();
	TalaSuit(vector<Card> card);
	~TalaSuit();

	bool pushCard(Card card);	//push a new card in suit if fit
	bool checkCard(Card card);	//check a new card fit in this suit
	bool isSameType();			//check this suit is same type, if false same shape
	vector<char> convertToArray();

public:
	vector<Card> cards;
};

#endif
