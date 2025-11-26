#pragma once
#ifndef MaubinhPlayerCard_h__
#define MaubinhPlayerCard_h__
#include "MaubinhGroupCardLogic.h"
#include <vector>

#define EM_SANHRONG 0
#define EM_3THUNG 1
#define EM_3SANH 2
#define EM_LUCPHEBON 3
#define EM_NORMAL 4
#define EM_BINHLUNG 5
#define EM_MUOI_BA 6
#define EM_MUOI_HAI 7
#include "axmol.h"
using namespace ax;

class MaubinhPlayerCard
{
public:
	MaubinhPlayerCard(void);
	~MaubinhPlayerCard(void);


	vector<MaubinhGroupCardLogic*> GroupCards;
	MaubinhGroupCardLogic* ChiDau;
	MaubinhGroupCardLogic* ChiGiua;
	MaubinhGroupCardLogic* ChiCuoi;

	void setArrayCard(vector<int> id);
	void AddGroupCard(MaubinhGroupCardLogic* GCard);

	void RemoveGroupCard(MaubinhGroupCardLogic* GCard);

	/**
	 * Ham nay search card trong bo bai va tra ve vi tri cua card do neu tim
	 * thay hoac tra ve -1 neu khong tim thay
	 * 
	 * @param card
	 * @return
	 */
	int SearchCard(MaubinhCardLogic* card);
	// Chua trien khai ham nay
	MaubinhPlayerCard* Copy();

	int GetNumOfGroupCards();
	void Clear();

	bool SanhRong();
	bool CungMau();

	bool MuoiHai();

	bool SauDoi();

	bool BaSanh();

	bool BaThung();

	bool TuQui();

	bool ThungPhaSanh();

	bool NamDoiThong();

	void ArrangeChi();

	int GetPlayerCardsKind(bool isTinhAt = false);

	int GetPlayerCardsKindBao(bool checkBinhLung, bool isTinhAt = false);

	int* ArrangePlayerCardsBao();

	bool isMauBinh();
	// /////////////////////////////////////////////////////////////
	// ToanNC_BC autoSorting

	void ApplyNewGroupCards(MaubinhGroupCardLogic* gc);

	void ApplyNew3GroupCards(MaubinhGroupCardLogic* chidau, MaubinhGroupCardLogic* chigiua, MaubinhGroupCardLogic* chicuoi);

	void RemoveGroupCards(MaubinhGroupCardLogic* gc, MaubinhGroupCardLogic* sub);

	MaubinhCardLogic* GetCard(int id);

	int getNumSuite(int suite);
	bool isHas3Thung();

	MaubinhGroupCardLogic* getCardSameSuite(int suite, int nCard);

	int getMaxCardIDSuite(int suite);

	void SapXepTruocSoBai();
	bool MuoiBaCay();
	bool MuoiHaiCay();

	bool BaSanh2();
	bool isLung();
	bool getWrongChi0(bool isTinhAt);
	bool getWrongChi1(bool isTinhAt);

	int* getAutoArrangeCard();
	
};
#endif // MaubinhPlayerCard_h__

