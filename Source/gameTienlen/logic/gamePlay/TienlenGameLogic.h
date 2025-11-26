#pragma once
#ifndef TienlenGameLogic_h__
#define TienlenGameLogic_h__
#include "TienlenGroupCard.h"
#include "TienlenPlayerCard.h"
#include "axmol.h"
#define AM_NORMAL  0
#define AM_NUMBER  1

class TienlenGameLogic
{
public:
	TienlenGameLogic(void);
	~TienlenGameLogic(void);

	
	static int CurrentArrangeMode;
	/**
	 * Sap xep list Group card
	 * 
	 * @param listGroup
	 * @param inc
	 *            true: sap xep tang dan 
	 *            false: sap xep giam dan
	 */
	static vector<TienlenGroupCard*> sortGroupCards(vector<TienlenGroupCard*> listGroup, bool inc);
	/**
	 * Sap xep list Group card
	 * 
	 * @param listGroup
	 * @param inc
	 *            true: sap xep tang dan 
	 *            false: sap xep giam dan
	 */
	static vector<TienlenGroupCard*> sortGroupCardsByNumber(vector<TienlenGroupCard*> listGroup, bool inc);

	/**
	 * So sanh 2 nhom bai
	 * 
	 * @param GroupCard1
	 * @param GroupCard2
	 * @return -1 neu GroupCard1 nho hon 
	 * 			1 neu GroupCard2 lon hon hoac bang
	 */
	static int CompareGroupCards(TienlenGroupCard* GroupCard1, TienlenGroupCard* GroupCard2);
	static vector<TienlenCard*> sortCards(vector<TienlenCard*> listCard, bool inc);
	/**
	 * So sanh 2 quan bai voi nhau
	 * 
	 * @param Card1
	 * @param Card2
	 * @return -1 neu Card1 nho hon 1 neu Card1 lon hon hoac bang
	 */
	static int CompareCardsInGroup(TienlenCard* Card1, TienlenCard* Card2);

	// Moi groupcard chi 1 la', dung de sap xep bo bai theo suit.
	int CompareGroupCardsBySuit(TienlenGroupCard* GroupCard1, TienlenGroupCard* GroupCard2);

	// Moi groupcard chi 1 la', dung de sap xep bo bai theo number.
	static int CompareGroupCardsByNumber(TienlenGroupCard* GroupCard1, TienlenGroupCard* GroupCard2);
	static void ScanGroupCardNormal(TienlenPlayerCard* PlayerCards);
	static void ScanGroupCardAuto(TienlenPlayerCard* PlayerCards);
	static void ScanGroupCard(TienlenPlayerCard* PlayerCards, int arrangeMode);
};
#endif // TienlenGameLogic_h__

