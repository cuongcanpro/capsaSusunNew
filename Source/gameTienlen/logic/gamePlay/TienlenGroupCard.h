#pragma once
#include <vector>
#include "TienlenCard.h"
#include <string>
#include "axmol.h"
using namespace std;

#ifndef TienlenGroupCard_h__
#define TienlenGroupCard_h__

#define EG_SEQUENCE 1
#define EG_NORMAL 2
#define EG_NONE 3
#define EG_ONECARD 4
/**
	*  4 cay thong
	*/
#define EG_SUPER 5//
#define EG_ULTRA 6// 5 cay thong
#define EG_BIGGER 7// 3 cay thong
#define EG_BA_CON_HAI 8// 3 cay thong
#define EG_DOI_HAI 9// doi hai
#define EG_TU_QUY 10// tu quy

class TienlenGroupCard
{
public:
	TienlenGroupCard(void);
	~TienlenGroupCard(void);

	vector<TienlenCard*> Cards;

	/**
	 * @return So quan bai
	 */
	int GetNumOfCards();

	/**
	 * check co sau bo doi
	 * 
	 * @return
	 */
	bool IsSixPair();
	/**
	 * 
	 * @return group thuoc loai nao
	 */
	int GetGroupKind();

	// TLMN_EC
	int GetNumber();

	int GetSuit();

	int GetBiggestSuit();

	/**
	 * Them quan bai vao group
	 * 
	 * @param card
	 *            quan bai them vao
	 */
	void AddCard(TienlenCard* card);

	/**
	 * Kiem tra co con bich ko
	 * 
	 * @return
	 */
	bool Has3Spade();

	/**
	 * Kiem tra co 2 ko
	 * 
	 * @return
	 */
	bool Has2();

	bool HasTuQuy();
	bool HasDoiThong();

	vector<int> getListId();

	bool searchCard(TienlenCard* card);
	void RemoveCard(TienlenCard* card);
	
	void addCardInHead(TienlenCard* card);

	/**
	 * 
	 * @param inc
	 *            true: sap xep tang dan
	 */
	void Sort(bool inc);

	int GetCountCard(int number);

	int GetMaxID();

	int GetMinID();

	int GetMaxNumber();

	int GetMinNumber();

	void RemoveAllCards();

	bool CheckDoubleCardID(int ID);

	bool CheckDoubleCardNumber(int num);

	std::string toString();

	void setCard(vector<int> id);

	void addCardToTest();

	void addCardWithIDs(vector<int> arrID);

	int getTypeGroupCard();

	bool canWithoutTurn();

	int getMinIdGreater(int id);

	vector<int> getMinSequenceGreater(TienlenGroupCard* group);
	vector<int> getMinPair();
};
#endif // TienlenGroupCard_h__

