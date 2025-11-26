#include "TalaGameRule.h"
#include "../data/TalaGameConstant.h"
#include "axmol.h"

vector<vector<Card>> TalaGameRule::makeCardTestTable(TalaGroupCard group)
{
	vector<vector<Card>> cards(NUM_TYPE, vector<Card>(NUM_SHAPE, Card()));
	for (int i = 0; i < group.size(); i++)
	{
		auto card = group.getCard(i);
		if (!card.isValid())
			continue;
		else cards[card.getType()][card.getShape()] = group.getCard(i);
	}
	return cards;
}

void TalaGameRule::addSuit(vector<TalaSuit>& allSuit, Card card0, Card card1, Card card2)
{
	if ((int)card0.isEaten() + (int)card1.isEaten() + (int)card2.isEaten() < 2)
		allSuit.push_back(TalaSuit({ card0, card1, card2 }));
}

vector<TalaSuit> TalaGameRule::findAllSuit(TalaGroupCard group)
{
	vector<TalaSuit> suits;
	auto table = makeCardTestTable(group);

	//tim bo cung so
	for (int i = 0; i < NUM_TYPE; i++) {
		bool myTry[NUM_SHAPE];
		for (int j = 0; j < NUM_SHAPE; j++)
			myTry[j] = table[i][j].isValid();

		if (myTry[0] && myTry[1] && myTry[2]) {
			addSuit(suits, group.getCard(group.findCard(table[i][0].getId())), group.getCard(group.findCard(table[i][1].getId())), group.getCard(group.findCard(table[i][2].getId())));
		}
		if (myTry[0] && myTry[1] && myTry[3]) {
			addSuit(suits, group.getCard(group.findCard(table[i][0].getId())), group.getCard(group.findCard(table[i][1].getId())), group.getCard(group.findCard(table[i][3].getId())));
		}
		if (myTry[0] && myTry[2] && myTry[3]) {
			addSuit(suits, group.getCard(group.findCard(table[i][0].getId())), group.getCard(group.findCard(table[i][2].getId())), group.getCard(group.findCard(table[i][3].getId())));
		}
		if (myTry[1] && myTry[2] && myTry[3]) {
			addSuit(suits, group.getCard(group.findCard(table[i][1].getId())), group.getCard(group.findCard(table[i][2].getId())), group.getCard(group.findCard(table[i][3].getId())));
		}
	}

	//tim bo cung chat
	for (int i = 0; i < NUM_TYPE - 2; i++) {
		for (int j = 0; j < NUM_SHAPE; j++) {
			if ((table[i][j].isValid()) && (table[i + 1][j].isValid()) && (table[i + 2][j].isValid())) {
				addSuit(suits, group.getCard(group.findCard(table[i][j].getId())), group.getCard(group.findCard(table[i + 1][j].getId())), group.getCard(group.findCard(table[i + 2][j].getId())));
			}
		}
	}

	return suits;
}

bool TalaGameRule::kiemtraTrungQuan(TalaSuit s1, TalaSuit s2)
{
	for (int i = 0; i < s1.cards.size(); i++) {
		for (int j = 0; j < s2.cards.size(); j++) {
			if (s1.cards[i].getId() == s2.cards[j].getId()) {
				return false;
			}
		}
	}
	return true;
}

bool TalaGameRule::addSolution(vector<vector<TalaSuit>>& allSolution, TalaSuit s1, TalaSuit s2, TalaSuit s3, int nEatCard)
{
	vector<TalaSuit> sol;
	if (s1.cards.size() > 0) {
		sol.push_back(s1);
	}
	if (s2.cards.size() > 0) {
		sol.push_back(s2);
	}
	if (s3.cards.size() > 0) {
		sol.push_back(s3);
	}

	//check numEatCard
	int count = 0;
	for (int i = 0; i < sol.size(); i++) {
		for (int j = 0; j < sol[i].cards.size(); j++) {
			if (sol[i].cards[j].isEaten()) {
				count++;
			}
		}
	}
	if (count != nEatCard) return false;

	//add solution
	if (sol.size() > 0) {
		allSolution.push_back(sol);
		return true;
	}
	else return false;
}

void TalaGameRule::addCardsToSuit(TalaSuit &suit, TalaGroupCard &group)
{
	if (suit.cards.size() < 1 || suit.cards.size() >= 20) return;

	for (int i = 0; i < group.size(); i++) {
		Card card = group.getCard(i);
		if (card.isValid())
			if (suit.pushCard(card)) group.takeCardOut(i--);
	}
}

bool TalaGameRule::kiemtraUKhan(vector<char> cards)
{
	auto group = createCardGroup(cards, {});
	auto cardTable = makeCardTestTable(group);

	int count = 0;
	for (int i = 0; i < NUM_TYPE; i++) {
		count = 0;
		for (int j = 0; j < NUM_SHAPE; j++) {
			if (cardTable[i][j].isValid()) {
				count++;
				if (count >= 2) {
					return false;
				}
			}
		}
	}

	for (int i = 0; i < NUM_TYPE - 2; i++) {
		for (int j = 0; j < NUM_SHAPE; j++) {
			if (cardTable[i][j].isValid() && cardTable[i + 1][j].isValid()) {
				return false;
			}
			if (cardTable[i][j].isValid() && cardTable[i + 2][j].isValid()) {
				return false;
			}
			if (cardTable[i + 1][j].isValid() && cardTable[i + 2][j].isValid()) {
				return false;
			}
		}
	}
	return true;
}

TalaGroupCard TalaGameRule::createCardGroup(vector<char> handOnCards, vector<char> eatenCards)
{
	vector<Card> cards;
	for (int i = 0; i < handOnCards.size(); i++)
	{
		Card card = Card(handOnCards[i]);
		card.setEaten(find(eatenCards.begin(), eatenCards.end(), handOnCards[i]) != eatenCards.end());
		cards.push_back(card);
	}
	return TalaGroupCard(cards);
}

bool TalaGameRule::kiemtraAnQuan(vector<char> handOnCards, vector<char> eatenCards, char cardId)
{
	auto group = createCardGroup(handOnCards, eatenCards);
	auto card = Card(cardId);
	card.setEaten(true);
	group.putCardIn(card);
	auto allSolution = getAllSolution(group);
	return allSolution.size() > 0;
}

vector<vector<TalaSuit>> TalaGameRule::getAllSolution(TalaGroupCard group)
{
	vector<vector<TalaSuit>> allSolution;
	vector<TalaSuit> allSuit = findAllSuit(group);

	int nEatCard = 0;
	Card card(-1);
	TalaSuit nullSuit;
	for (int i = 0; i < group.size(); i++) {
		card = group.getCard(i);
		if (card.isValid() && card.isEaten())
			nEatCard++;
	}

	for (int i = 0; i < allSuit.size(); i++) {
		bool check = false;
		for (int j = i + 1; j < allSuit.size(); j++) {
			if (kiemtraTrungQuan(allSuit[i], allSuit[j])) {
				check = true;
				for (int k = j + 1; k < allSuit.size(); k++) {
					if (kiemtraTrungQuan(allSuit[i], allSuit[k]) && kiemtraTrungQuan(allSuit[j], allSuit[k])) {
						if (addSolution(allSolution, allSuit[i], allSuit[j], allSuit[k], nEatCard)) {
							return allSolution;
						}
					}
				}
				addSolution(allSolution, allSuit[i], allSuit[j], nullSuit, nEatCard);
			}
		}
		if (!check) addSolution(allSolution, allSuit[i], nullSuit, nullSuit, nEatCard);
	}
	return allSolution;
}

bool TalaGameRule::kiemtraVutQuan(vector<char> handOnCards, vector<char> eatenCards, char cardId)
{
	auto group = createCardGroup(handOnCards, eatenCards);
	if (eatenCards.size() == 0) return true;
	if (find(eatenCards.begin(), eatenCards.end(), cardId) != eatenCards.end()) return false;
	
	for (int i = 0; i < group.size(); i++)
	{
		if (group.getCard(i).getId() == cardId)
		{
			group.takeCardOut(i);
			break;
		}
	}

	auto allSol = getAllSolution(group);
	return allSol.size() > 0;
}

vector<TalaSuit> TalaGameRule::kiemtraHaBai(TalaGroupCard allCard, TalaGroupCard showCard)
{
	vector<TalaSuit> suits;
	
	if (showCard.getNumEatCard() != allCard.getNumEatCard()) return suits;
	
	auto allSol = getAllSolution(showCard);
	if (allSol.size() <= 0) suits;
	
	TalaGroupCard group({});
	for (int i = 0; i < allSol.size(); i++) {
		if (allSol[i].size() >= 3) {
			copyDifferent(group, showCard, allSol[i]);
			if (group.size() > 0) {
				for (int j = 0; j < allSol[i].size(); j++) {
					addCardsToSuit(allSol[i][j], group);
				}
			}
			return allSol[i];
		}
	}
	
	for (int i = 0; i < allSol.size(); i++) {
		copyDifferent(group, showCard, allSol[i]);
		if (allSol[i].size() == 3) {
			addCardsToSuit(allSol[i][0], group);
			addCardsToSuit(allSol[i][1], group);
			addCardsToSuit(allSol[i][2], group);
		}
		if (allSol[i].size() == 2) {
			if (!allSol[i][0].isSameType()) {
				addCardsToSuit(allSol[i][0], group);
				addCardsToSuit(allSol[i][1], group);
			}
			else {
				addCardsToSuit(allSol[i][1], group);
				addCardsToSuit(allSol[i][0], group);
			}
		}
		if (allSol[i].size() == 1)
			addCardsToSuit(allSol[i][0], group);

		// neu het bai la ok
		if (group.size() <= 0)
			return allSol[i];
	}
	return suits;
}

vector<char> TalaGameRule::addCardToSuit(vector<char> suit, char cardId)
{
	vector<Card> cards;
	for (int i = 0; i < suit.size(); i++)
		cards.push_back(Card(suit[i]));
	TalaSuit talaSuit(cards);
	talaSuit.pushCard(Card(cardId));
	return talaSuit.convertToArray();
}

char TalaGameRule::getSuitId(vector<char> suit)
{
	char maxId = 0;
	for (int i = 0; i < suit.size(); i++) {
		if (suit[i] > maxId) maxId = suit[i];
	}
	return maxId;
}

void TalaGameRule::copyDifferent(TalaGroupCard &dest, TalaGroupCard src, vector<TalaSuit> sol)
{
	dest.clear();

	for (int i = 0; i < src.size(); i++) {
		Card card = src.getCard(i);
		if (!card.isValid()) continue;

		bool canAdd = true;
		for (int j = 0; j < sol.size(); j++) {
			if (canAdd) {
				TalaSuit suit = sol[j];
				for (int k = 0; k < suit.cards.size(); k++) {
					if (card.getId() == suit.cards[k].getId()) {
						canAdd = false;
						break;
					}
				}
			}
		}
		if (canAdd) {
			if (dest.findCard(card.getId()) == -1) {
				dest.putCardIn(card);
			}
		}
	}
}

bool TalaGameRule::kiemtraGuiBai(vector<char> suit, char card)
{
	vector<Card> cards;
	for (int i = 0; i < suit.size(); i++)
		cards.push_back(Card(suit[i]));
	return TalaSuit(cards).checkCard(Card(card));
}

bool TalaGameRule::kiemtraGuiBai(TalaSuit suit, Card card)
{
	return suit.checkCard(card);
}

vector<char> TalaGameRule::tuDongHaBai(vector<char> handOnCards, vector<char> eatenCards)
{
	auto group = createCardGroup(handOnCards, eatenCards);
	auto allSol = getAllSolution(group);

	if (allSol.size() <= 0) return vector<char>();

	for (int i = 0; i < allSol.size(); i++) {
		auto &sol = allSol[i];
		for (int j = 0; j < sol.size(); j++) {
			for (int k = j + 1; k < sol.size(); k++) {
				if (sol[j].isSameType() && !sol[k].isSameType()) {
					swap(sol[j], sol[k]);
				}
			}
		}
	}
	
	int minSum = INT_MAX;
	vector<TalaSuit> sol;
	for (int i = 0; i < allSol.size(); i++) {
		TalaGroupCard otherGroup({});
		copyDifferent(otherGroup, group, allSol[i]);
		for (int j = 0; j < allSol[i].size(); j++)
			addCardsToSuit(allSol[i][j], otherGroup);
		
		if (otherGroup.size() <= 0) {
			sol = allSol[i];
			break;
		}
		else {
			int curSum = otherGroup.getSum();
			if (curSum < minSum) {
				sol = allSol[i];
				minSum = curSum;
			}
		}
	}
	
	vector<char> res;
	if (sol.size() > 0) {
		for (int i = 0; i < sol.size(); i++) {
			auto suit = sol[i];
			for (int j = 0; j < suit.cards.size(); j++) {
				res.push_back(suit.cards[j].getId());
			}
		}
	}
	return res;
}

vector<vector<char>> TalaGameRule::kiemtraHaBai(vector<char> handOnCards, vector<char> selectedCards, vector<char> eatenCards)
{
	auto allSuits = kiemtraHaBai(createCardGroup(handOnCards, eatenCards), createCardGroup(selectedCards, eatenCards));
	vector<vector<char>> res;
	for (int i = 0; i < allSuits.size(); i++) {
		res.push_back(allSuits[i].convertToArray());
	}
	return res;
}

vector<char> TalaGameRule::arrangeCard(vector<char> handOnCards, vector<char> eatenCards)
{
	TalaGroupCard g = createCardGroup(handOnCards, eatenCards);
	TalaGroupCard g1({}), g2({}), g3({});

	g3 = createCardGroup(tuDongHaBai(handOnCards, eatenCards), eatenCards);
	auto tg = kiemtraHaBai(g, g3);
	if (tg.size() > 0) {
		copyDifferent(g1, g, tg);
		for (int i = 0; i < tg.size(); i++) {
			for (int j = 0; j < tg[i].cards.size(); j++) {
				g2.putCardIn(tg[i].cards[j]);
			}
		}
	}
	else g1 = g;
	g3.clear();

	//sap xep lai g1
	if (g1.size() >= 3) {
		g1.sortCardTypeDown();
		for (int i = 0; i < g1.size(); i++) {
			auto card = g1.getCard(i);
			
			if (i > 0) {
				if (card.getType() == g1.getCard(i - 1).getType())
					continue;
				if (card.getShape() == g1.getCard(i - 1).getShape()) {
					int dt = g1.getCard(i - 1).getType() - card.getType();
					if ((dt == 1) || (dt == 2))
						continue;
				}
			}
			if (i < g1.size() - 1) {
				if (card.getType() == g1.getCard(i + 1).getType())
					continue;
				if (card.getShape() == g1.getCard(i + 1).getShape()) {
					int dt = card.getType() - g1.getCard(i + 1).getType();
					if ((dt == 1) || (dt == 2))
						continue;
				}
			}
			g3.putCardIn(g1.takeCardOut(i--));
		}
	}

	// ghep g3 voi g1
	if (g3.size() > 0) {
		g3.sortCardTypeDown();
		for (int i = 0; i < g3.size(); i++) {
			auto card = g3.getCard(i);
			int idx = g1.size();
			for (int j = 0; j < g1.size(); j++) {
				if (g1.getCard(j).getShape() == card.getShape()) {
					int dt = g1.getCard(j).getType() - card.getType();
					if (abs(dt) == 1 || abs(dt) == 2) {
						idx = j + 1;
						// swap 2 quan neu = nhau
						if (idx < g1.size()) {
							if (g1.getCard(idx).getType() == g1.getCard(j).getType()) {
								g1.swap2Card(j, idx);
								idx = j + 2;
							}
						}
						break;
					}
				}
			}
			g1.insertCard(g3.takeCardOut(i--), idx);
		}
	}

	// ghep g2 voi g1
	for (int i = 0; i < g1.size(); i++) {
		g2.putCardIn(g1.getCard(i));
	}

	// ghep g2 voi g3
	for (int i = 0; i < g3.size(); i++) {
		g2.putCardIn(g3.getCard(i));
	}

	// update player hand cards
	return g2.convertToArray();
}
