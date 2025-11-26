#pragma once
#ifndef MaubinhGroupCardLogic_h__
#define MaubinhGroupCardLogic_h__
#include "MaubinhCardLogic.h"
#include <vector>
#include "axmol.h"

using namespace std;

#define EG_THUNGPHASANHTHUONG 0
#define EG_THUNGPHASANH 1
#define EG_TUQUI 2
#define EG_CULU 3
#define EG_THUNG 4
#define EG_SANH 5
#define EG_SAMCO 6
#define EG_THU 7
#define EG_DOI 8
#define EG_MAUTHAU 9
class MaubinhGroupCardLogic
{
public:
	MaubinhGroupCardLogic(void);
	~MaubinhGroupCardLogic(void);

public:
	std::vector<MaubinhCardLogic*>Cards;
	std::vector<int> Value;
	
	
	bool IsSelected;

	void GroupCard();

	int GetNumOfCards();
	int GetGroupKind(bool isTinhAt = false);

	bool ThungPhaSanhThuong();
	bool ThungPhaSanh();

	bool TuQui();

	bool CuLu();

	bool Thung();
	bool Sanh();
	bool XamChi();
	bool HaiDoiKhacNhau();

	bool MotDoi();

	bool SanhRong();
	bool CungMau();
	bool MuoiHai();

	bool SauDoi();

	bool SauDoi1();

	bool NamDoiThong();

	bool BaSanh();
	bool BaThung();
	bool CungChat();

	int GetNumber();

	int GetSuit();

	void AddCard(MaubinhCardLogic* card) ;

	void RemoveCard(MaubinhCardLogic* card);

	void Reset();

	int GetMaxNumber();

	int GetMaxID();

	void sortPair();
	void sortTrio();

	void SapXepTruocSoBai2();
	void IncreaseSort();

	void DecreaseSort();
	void Sort(bool inc);

	void sortInc(vector<MaubinhCardLogic*> cards);

	void sortDec(vector<MaubinhCardLogic*> cards);


	bool searchCard(MaubinhCardLogic* card);
	void AddCardByID(int id);

	int getNumSuite(int suite);

	MaubinhGroupCardLogic* getCardsSameSuite(int suite);

	bool isHasThung();

	MaubinhGroupCardLogic* getThung();

	bool isHasSequence();
	MaubinhGroupCardLogic* getSequence();

	bool isHasPair();

	MaubinhGroupCardLogic* getPair();

	bool isHasXamChi();
	MaubinhGroupCardLogic* getXamChi();

	// kiem tra xem co culu hay khong
	bool isHasCulu();
	MaubinhGroupCardLogic* getCulu();

	bool is2DoiKhacNhau();
	MaubinhGroupCardLogic* get2DoiKhacNhau();

	MaubinhGroupCardLogic* getFour();

	MaubinhGroupCardLogic* getMaxCard();
	void wrap(int index1, int index2);

};
#endif // MaubinhGroupCardLogic_h__

