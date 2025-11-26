#ifndef TalaGameRule_h__
#define TalaGameRule_h__

#include <vector>
#include "Card.h"
#include "TalaSuit.h"
#include "TalaGroupCard.h"
#include "axmol.h"
using namespace std;

class TalaGameRule {
private:
	static vector<vector<Card>> makeCardTestTable(TalaGroupCard group);
	static vector<vector<TalaSuit>> getAllSolution(TalaGroupCard group);
	static bool addSolution(vector<vector<TalaSuit>> &allSolution, TalaSuit s1, TalaSuit s2, TalaSuit s3, int nEatCard);
	static void addSuit(vector<TalaSuit> &allSuit, Card card0, Card card1, Card card2);
	static void addCardsToSuit(TalaSuit &suit, TalaGroupCard &group);
	static void copyDifferent(TalaGroupCard &dest, TalaGroupCard src, vector<TalaSuit> sol);
	static TalaGroupCard createCardGroup(vector<char> handOnCards, vector<char> eatenCards);
	static bool kiemtraTrungQuan(TalaSuit s1, TalaSuit s2);

public:
	static vector<TalaSuit> findAllSuit(TalaGroupCard group);
	static bool kiemtraGuiBai(vector<char> suit, char card);
	static bool kiemtraGuiBai(TalaSuit suit, Card card);
	static vector<char> arrangeCard(vector<char> handOnCards, vector<char> eatenCards);

	static bool kiemtraAnQuan(vector<char> handOnCards, vector<char> eatenCards, char cardId);
	static bool kiemtraVutQuan(vector<char> handOnCards, vector<char> eatenCards, char cardId);
	static vector<char> tuDongHaBai(vector<char> handOnCards, vector<char> eatenCards);
	static vector<vector<char>> kiemtraHaBai(vector<char> handOnCards, vector<char> selectedCards, vector<char> eatenCards);
	static vector<TalaSuit> kiemtraHaBai(TalaGroupCard allCard, TalaGroupCard showCard);
	static vector<char> addCardToSuit(vector<char> suit, char cardId);
	static bool kiemtraUKhan(vector<char> cards);
	static char getSuitId(vector<char>suit);
};

#endif //TalaGameRule_h__
