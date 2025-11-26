#ifndef TalaGroupCard_h__
#define TalaGroupCard_h__

#include "Card.h"
#include <vector>
#include "axmol.h"
using namespace std;

class TalaGroupCard {
public:
	TalaGroupCard(vector<Card> cards);
	~TalaGroupCard();

private:
	vector<Card> cards;

public:
	void putCardIn(Card card);
	Card takeCardOut(int index);
	void insertCard(Card card, int index);
	Card getCard(int index);
	void clear();
	int size();
	
	int findCard(int cardId);
	int getSum();
	int getNumEatCard();
	vector<char> convertToArray();
	
	void swap2Card(int idx1, int idx2);
	void sortCardTypeDown();
};

#endif
