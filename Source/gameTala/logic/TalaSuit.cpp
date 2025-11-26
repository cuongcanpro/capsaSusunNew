#include "TalaSuit.h"

TalaSuit::TalaSuit()
{
}

TalaSuit::TalaSuit(vector<Card> cards)
{
	this->cards = cards;
}


TalaSuit::~TalaSuit()
{
}

bool TalaSuit::pushCard(Card card)
{
	if (cards.size() >= 3 && card.isValid()) {
		//kiem tra bo cung so
		if (cards[0].getType() == cards[1].getType() && cards[0].getType() == card.getType()) {
			cards.push_back(card);
			return true;
		}
		
		//kiem tra bo cung chat
		if (cards[0].getShape() == cards[1].getShape() && cards[0].getShape() == card.getShape()) {
			if (cards[0].getType() - card.getType() == 1) {
				cards.insert(cards.begin(), card);
				return true;
			}
			if (card.getType() - cards[cards.size() - 1].getType() == 1) {
				cards.insert(cards.begin() + cards.size(), card);
				return true;
			}
		}
	}
	return false;
}

bool TalaSuit::checkCard(Card card)
{
	if (cards.size() >= 3 && card.isValid()) {
		if (cards[0].getType() == cards[1].getType()) return cards[0].getType() == card.getType();
		if (cards[0].getShape() == card.getShape())
			return (cards[0].getType() - card.getType()) == 1 || (card.getType() - cards[cards.size() - 1].getType()) == 1;
	}
	return false;
}

bool TalaSuit::isSameType()
{
	return cards[0].getType() == cards[1].getType();
}

vector<char> TalaSuit::convertToArray()
{
	vector<char> res;
	for (int i = 0; i < cards.size(); i++)
		res.push_back(cards[i].getId());
	return res;
}
