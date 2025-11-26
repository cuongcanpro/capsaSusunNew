#pragma once
#ifndef TienlenPlayerCard_h__
#define TienlenPlayerCard_h__
#include "TienlenGroupCard.h"
#include "axmol.h"
class TienlenPlayerCard
{
public:
	TienlenPlayerCard(void);
	~TienlenPlayerCard(void);


	vector<TienlenGroupCard*> GroupCards;
	vector<int> Value;
	vector<int> getListIdCard();
	vector<char> getListIdCardByChar();

	int GetNumOfGroupCards();

	bool Has3Spade();

	void AddGroupCard(TienlenGroupCard* GCard);

	void SetCard(vector<int> id);
	void removeCard(int id);
	void RemoveGroupCard(TienlenGroupCard* GCard);

	// Ham nay search card trong bo bai va tra ve vi tri cua card do neu tim
	// thay
	// hoac tra ve -1 neu khong tim thay
	int SearchCard(TienlenCard* Card);
	/**
	 * Lay card theo id
	 * 
	 * @param id
	 * @return
	 */
	TienlenCard* GetCard(int id);

	// Chua trien khai ham nay
	/*
	 * PlayerCard Copy() { PlayerCard c;
	 * 
	 * for(int i = 0; i < GetNumOfGroupCards(); i++) { GroupCard gc; for(int j =
	 * 0; j < GroupCards.get(i).GetNumOfCards(); j++) {
	 * gc.AddCard(GroupCards.get(i).Cards.get(j)); } c.AddGroupCard(gc); }
	 * return c; }
	 */

	void Clear();
	bool Leave2Last();

	bool HasStraight();

	bool HasFour2();

	bool HasFour3();
	// 4 doi thong
	bool Has4DoiThong();

	// ham tra ve true neu co 3 doi thong
	bool Has3DoiThong();

	// 5 doi thong
	bool HasUltra();


	TienlenGroupCard* Has3DoiThong(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	// kiem tra tu quy
	TienlenGroupCard* HasFour(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	TienlenGroupCard* Has4DoiThong(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);
	TienlenGroupCard* Has5DoiThong(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	bool CardInFour(int number);

	bool CardIn3Pair(int number);

	bool CardIn4Pair(int number);

	 bool CardIn5Pair(int number);

	 int* ArrayPair();

	// co tu quy?
	bool HasTuQuy();

	// 6 doi (tinh ca doi 2 va tu quy tinh la 2 doi)
	bool HasSixPair();

	// ham lay ve ket qua thoi 2
	double GetHas2Fail();
	/*
	 * ham kiem tra co trung lap quan bai khong
	 */
	bool CheckDoubleCard(int id);

	/*
	 * lay ve tat ca quan bai co Number = ID
	 */
	vector<int> GetCardNumber(int number);

	TienlenGroupCard* HasSequence(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	TienlenGroupCard* AutoSequence(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	TienlenGroupCard* Auto4Pair(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	TienlenGroupCard* Auto5Pair(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	TienlenGroupCard* CheckGroup(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	void addCardToTest();

	TienlenGroupCard* FirstTurnPlay(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	// minh khong phai la nguoi danh dau tien cua vong choi
	TienlenGroupCard* OnTurnPlay(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards);

	bool checkIn(int number, vector <TienlenCard*> group);

	bool checkIn(int number, TienlenGroupCard* group);

	bool CanPlay(TienlenGroupCard* group);

	bool CanPlayOneCard(TienlenGroupCard* group);

	bool CanPlayBIGGER(TienlenGroupCard* group);
	bool CanPlaySUPER(TienlenGroupCard* group);

	bool CanPlayULTRA(TienlenGroupCard* group);

	bool CanPlaySequence(TienlenGroupCard* group);

	bool CanPlayNormal(TienlenGroupCard* group) ;
	int GetMaxPair();

	int GetMaxThree() ;

	int GetMaxFour() ;
	int getHas2FailAdvance() ;

	int getNumOf2();

	bool has3DoiThongTuQuy();

	bool has4DoiThongTuQuy();

	bool has5DoiThongTuQuy();

	bool hasTuQuy(int num);

	int getNumTuQuy();

	bool Has6DoiThong();

	int getHas2FailEatAll();

	vector<TienlenGroupCard*> autoGroupCard;
	void autoArrange();
	void autoArrange1();
	void autoArrange2();
	void autoArrange3();
	void autoArrange4();
	void autoArrange5();
	void autoArrange6();
	vector<int> getAutoPlayCard(int mimNumCard, int maxCard, int nextCard);
	vector<int> getAutoResponseCard(TienlenGroupCard* groupCard, int minNumCard, int nextCard);
	int getSuddenWin();
	int getThoi();
	int arraySuit[5][16];
	int arrayNumber[16][5];
};
#endif // TienlenPlayerCard_h__

