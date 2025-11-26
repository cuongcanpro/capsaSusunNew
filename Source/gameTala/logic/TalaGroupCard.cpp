#include "TalaGroupCard.h"

TalaGroupCard::TalaGroupCard(vector<Card> cards)
{
	this->cards = cards;
}

TalaGroupCard::~TalaGroupCard()
{
}

void TalaGroupCard::putCardIn(Card card)
{
	cards.push_back(card);
}

Card TalaGroupCard::takeCardOut(int index)
{
	if (index >= 0 && index < cards.size()) {
		Card card = cards.at(index);
		cards.erase(cards.begin() + index);
		return card;
	}
	return Card();
}

void TalaGroupCard::insertCard(Card card, int index)
{
	if (index >= 0 && index <= cards.size())
		cards.insert(cards.begin() + index, card);
}

Card TalaGroupCard::getCard(int index)
{
	if (index >= 0 && index < cards.size())
		return cards[index];
	else return Card();
}

void TalaGroupCard::clear()
{
	cards.clear();
}

int TalaGroupCard::size()
{
	return cards.size();
}

int TalaGroupCard::getSum()
{
	int sum = 0;
	for (int i = 0; i < cards.size(); i++)
		sum += cards[i].getType();
	return sum;
}

void TalaGroupCard::swap2Card(int idx1, int idx2)
{
	swap(cards[idx1], cards[idx2]);
}

int TalaGroupCard::findCard(int cardId)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].getId() == cardId) 
			return i;
	return -1;
}

int TalaGroupCard::getNumEatCard()
{
	int count = 0;
	for (int i = 0; i < cards.size(); i++)
		count += (int)cards[i].isEaten();
	return count;
}

vector<char> TalaGroupCard::convertToArray()
{
	vector<char> cardIds;
	for (int i = 0; i < cards.size(); i++)
		cardIds.push_back(cards[i].getId());
	return cardIds;
}

void TalaGroupCard::sortCardTypeDown()
{
	for (int i = 0; i < cards.size(); i++) {
		for (int j = i + 1; j < cards.size(); j++){
			if (cards[i].getId() < cards[j].getId())
				swap2Card(i, j);
		}
	}
}
