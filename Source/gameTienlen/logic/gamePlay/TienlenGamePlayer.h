#pragma once

#ifndef TienlenGamePlayer_h__
#define TienlenGamePlayer_h__

#include <vector>
#include "TienlenGroupCard.h"
#include "axmol.h"
#define ST_ULTRA	 0
#define ST_FOUR_3	 1
#define ST_FOUR_2	 2
/**
	* Sanh rong
	*/
#define ST_STRAIGHT	 3
/**
	* 6 doi khong can thong
	*/
#define ST_SIXPAIR	 4
#define ST_NONE		 5
#define ST_13LA		 6
#define ST_BIGGER	 7
#define ST_SUPER	 8

using namespace std;

class TienlenGamePlayer
{
public:
	TienlenGamePlayer(void);
	~TienlenGamePlayer(void);
	
	/**
	 * Danh sach id cac quan bai trong bo toi trang
	 */
	vector<int> WinCards;
	/**
	 * Mang id cac quan bai khong nam trong bo toi trang
	 */
	vector<int> WinExcess;
	/**
	 * Nhung card nam trong bo thoi
	 */
	vector<int> LostCards;
	int SuddenWin ;
	
	//Check thoi bai
	void KiemTraBaiThoi(TienlenGroupCard* c);
	int getNumCard(int num,TienlenGroupCard* c);
	
	int NumFour(TienlenGroupCard* c);
	
	int Num3DoiThong(TienlenGroupCard* c);
	
	int Check4_3(TienlenGroupCard* c);
	
	bool Thoi5DoiThong(TienlenGroupCard* c);
	
	bool Thoi4DoiThong(TienlenGroupCard* c);
	
	bool Thoi3DoiThong(TienlenGroupCard* c);
	
	
	bool CardInWinCards(int ID);

	bool CardInWinExcess(int ID);

	void CheckFour(TienlenGroupCard* c);

	void CheckThoiHai(TienlenGroupCard* c);

	// SAP XEP BAI KHI TOI TRANG :
	// Neu la sanh rong :

	void CheckStraight(TienlenGroupCard* c);

	void CheckSixPair(TienlenGroupCard* c);

	void CheckFour2(TienlenGroupCard* c);
	void CheckFour3(TienlenGroupCard* c);
	/**
	 * Kiem tra lay ra 5 doi 
	 * @param c
	 */
	void CheckUltra(TienlenGroupCard* c);

	void CheckSuper(TienlenGroupCard* c);
	
	void CheckBigger(TienlenGroupCard* c);
};
#endif // TienlenGamePlayer_h__

