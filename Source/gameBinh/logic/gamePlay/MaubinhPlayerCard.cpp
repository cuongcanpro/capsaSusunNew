#include "MaubinhPlayerCard.h"
#include "MaubinhGameRule.h"
#include "stdlib.h"


MaubinhPlayerCard::MaubinhPlayerCard(void)
{
	ChiDau = new MaubinhGroupCardLogic();
	ChiGiua = new MaubinhGroupCardLogic();
	ChiCuoi = new MaubinhGroupCardLogic();
}


MaubinhPlayerCard::~MaubinhPlayerCard(void)
{
}


void MaubinhPlayerCard::setArrayCard(vector<int> idCard)
{
	for (int i = 0; i < idCard.size(); i++) {
		MaubinhGroupCardLogic* group = new MaubinhGroupCardLogic();
		group->AddCardByID(idCard[i]);
		AddGroupCard(group);
	}
}

void MaubinhPlayerCard::AddGroupCard(MaubinhGroupCardLogic* GCard) {
		// Convert code Binh
		GroupCards.push_back(GCard);
	}

	void MaubinhPlayerCard::RemoveGroupCard(MaubinhGroupCardLogic* GCard) {
	// Convert code Binh
	int i;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			for (int k = 0; k < GCard->GetNumOfCards(); k++) {
				if (GroupCards.at(i)->Cards.at(j)->ID == GCard->Cards.at(k)->ID) {
					GroupCards.at(i)->Cards.erase(GroupCards.at(i)->Cards.begin() + j);
				}
			}

		}

	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		if (GroupCards.at(i)->GetNumOfCards() == 0) {
			GroupCards.erase(GroupCards.begin() + i);
		}
	}
}

/**
	* Ham nay search card trong bo bai va tra ve vi tri cua card do neu tim
	* thay hoac tra ve -1 neu khong tim thay
	* 
	* @param card
	* @return
	*/
	int MaubinhPlayerCard::SearchCard(MaubinhCardLogic* card) {
	// Convert code Binh
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->ID == card->ID) {
				return i;
			}
		}
	}
	return -1;
}

// Chua trien khai ham nay
	MaubinhPlayerCard* MaubinhPlayerCard::Copy() {
	// Convert code Binh
	MaubinhPlayerCard* c = NULL;

	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		MaubinhGroupCardLogic* gc = new MaubinhGroupCardLogic();
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
		c->AddGroupCard(gc);
	}
	return c;
}

	int MaubinhPlayerCard::GetNumOfGroupCards() {
	// Convert code Binh
	return GroupCards.size();
}

	void MaubinhPlayerCard::Clear() {
	// Convert code Binh
	GroupCards.clear();
}

	bool MaubinhPlayerCard::SanhRong() {
	// Convert code Binh
	MaubinhGroupCardLogic* gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}
	if (gc->SanhRong())
		return true;
	return false;
}

	bool MaubinhPlayerCard::CungMau() {
	// Convert code Binh
	MaubinhGroupCardLogic* gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}
	if (gc->CungMau())
		return true;
	return false;
}

	bool MaubinhPlayerCard::MuoiHai() {
	// Convert code Binh
	MaubinhGroupCardLogic* gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}
	if (gc->MuoiHai())
		return true;
	return false;
}

	bool MaubinhPlayerCard::SauDoi() {
	// Convert code Binh
	MaubinhGroupCardLogic *gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}
	if (gc->SauDoi()) {
		ArrangeChi();
		if (ChiCuoi->GetGroupKind() == EG_THU) {
			if (ChiGiua->GetGroupKind() == EG_THU) {
				if (ChiDau->GetGroupKind() == EG_DOI) {
					return true;
				}
			}
		}
			
	}
	return false;
}

	bool MaubinhPlayerCard::BaSanh() {
	// Convert code Binh
	ArrangeChi();
	if (ChiGiua->Sanh()) {
		if (ChiCuoi->Sanh()) {
			if (ChiDau->Sanh())
				return true;
		}
	}
	return false;
}

	bool MaubinhPlayerCard::BaThung() {
	// Convert code Binh
	ArrangeChi();
	if (ChiGiua->Thung() && ChiCuoi->Thung()) {
		if (ChiDau->Thung()) {
			return true;
		}
	}
	return false;
}

	bool MaubinhPlayerCard::TuQui() {
	// Convert code Binh
	ArrangeChi();
	MaubinhGroupCardLogic* gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}
	if (gc->TuQui()) {
		return true;
	}
	return false;
}

	bool MaubinhPlayerCard::ThungPhaSanh() {
	// Convert code Binh
	ArrangeChi();
	MaubinhGroupCardLogic *gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}

	if (gc->ThungPhaSanh()) {
		return true;
	}
	return false;
}

	bool MaubinhPlayerCard::NamDoiThong() {
	// Convert code Binh
	ArrangeChi();
	MaubinhGroupCardLogic* gc = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			gc->AddCard(GroupCards.at(i)->Cards.at(j));
		}
	}
	if (gc->NamDoiThong())
		return true;
	return false;
}

	void MaubinhPlayerCard::ArrangeChi() {
	// Convert code Binh
	ChiDau->Cards.clear();
	ChiGiua->Cards.clear();
	ChiCuoi->Cards.clear();

	int i = 0;

	for (i = 0; i < 3; i++) {
		ChiDau->AddCard(GroupCards.at(i)->Cards.at(0));
	}
	for (i = 3; i < 3 + 5; i++) {
		ChiGiua->AddCard(GroupCards.at(i)->Cards.at(0));
	}
	for (i = 8; i < 13; i++) {
		ChiCuoi->AddCard(GroupCards.at(i)->Cards.at(0));
	}
}

	int MaubinhPlayerCard::GetPlayerCardsKind(bool isTinhAt) {
	// Convert code Binh
	if (GroupCards.size() <= 0) {
		return EM_BINHLUNG;
	}
	ArrangeChi();

	// CHECK MAU BINH
	// ---------------------------------------------------
	// 20100614 truclc
	/*
		* if (CungMau()) return EM_13CUNGMAU; if (MuoiHai()) return
		* EM_12CUNGMAU;
		*/
	// 20100614 truclc
	if (SanhRong())
		return EM_SANHRONG;
	if (isTinhAt)
	{
		if (MuoiBaCay())
			return EM_MUOI_BA;
		if (MuoiHaiCay())
			return EM_MUOI_HAI;
	}
		
	if (BaThung())
		return EM_3THUNG;
	if (BaSanh())
		return EM_3SANH;
	if (SauDoi())
		return EM_LUCPHEBON;
		
	/*
		* if(TuQui()) return EM_TUQUI; if(ThungPhaSanh()) return
		* EM_THUNGPHASANH;
		*/
	/*
		* if(NamDoiThong()) return EM_NAMDOITHONG;
		*/

	// Check BINH LUNG
	// ----------------------------------------------------
	bool binhlung = true;
	if (MaubinhGameRule::SoSanhChi(ChiDau, ChiGiua, isTinhAt) == -1)
		if (MaubinhGameRule::SoSanhChi(ChiGiua, ChiCuoi, isTinhAt) == -1) {
			binhlung = false;
		}
	if (binhlung)
		return EM_BINHLUNG;

	return EM_NORMAL;
}

	bool MaubinhPlayerCard::isMauBinh() {
	if (GetPlayerCardsKind() != EM_BINHLUNG && GetPlayerCardsKind() != EM_NORMAL)
		return true;
	return false;
}

// /////////////////////////////////////////////////////////////
// ToanNC_BC autoSorting

	void MaubinhPlayerCard::ApplyNewGroupCards(MaubinhGroupCardLogic* gc) {
	// Convert code Binh
	// tao moi GroupCards
	GroupCards.clear();

	for (int i = 0; i < gc->GetNumOfCards(); ++i) {
		MaubinhGroupCardLogic* _gc = new MaubinhGroupCardLogic();
		_gc->AddCard(gc->Cards.at(i));
		AddGroupCard(_gc);
	}

	ArrangeChi();
}

	void MaubinhPlayerCard::ApplyNew3GroupCards(MaubinhGroupCardLogic *chidau, MaubinhGroupCardLogic* chigiua, MaubinhGroupCardLogic *chicuoi) {
	int i;
	GroupCards.clear();
	for (i = 0; i < chidau->GetNumOfCards(); ++i) {
		MaubinhGroupCardLogic* _gc = new MaubinhGroupCardLogic();
		_gc->AddCard(chidau->Cards.at(i));
		AddGroupCard(_gc);
	}
	for (i = 0; i < chigiua->GetNumOfCards(); ++i) {
		MaubinhGroupCardLogic* _gc1 = new MaubinhGroupCardLogic();
		_gc1->AddCard(chigiua->Cards.at(i));
		AddGroupCard(_gc1);
	}
	for (i = 0; i < chicuoi->GetNumOfCards(); ++i) {
		MaubinhGroupCardLogic* _gc2 = new MaubinhGroupCardLogic();
		_gc2->AddCard(chicuoi->Cards.at(i));
		AddGroupCard(_gc2);
	}

	ArrangeChi();
}

	void MaubinhPlayerCard::RemoveGroupCards(MaubinhGroupCardLogic* gc, MaubinhGroupCardLogic* sub) {
	int i;
	for (i = 0; i < sub->GetNumOfCards(); i++) {
		if (gc->searchCard(sub->Cards.at(i)) == true) {
			gc->RemoveCard(sub->Cards.at(i));
		}
	}
}

	MaubinhCardLogic* MaubinhPlayerCard::GetCard(int id) {
	if (GetNumOfGroupCards() == 0)
		return NULL;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->ID == id) {
				return GroupCards.at(i)->Cards.at(j);
			}
		}
	}
	return NULL;
}

	int MaubinhPlayerCard::getNumSuite(int suite) {
	int nCount = 0;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetSuit() == suite)
				++nCount;
		}
	}
	return nCount;
}

	bool MaubinhPlayerCard::isHas3Thung() {
	int num[4];
	int i;
	for (i = ES_SPADE; i <= ES_HEART; i++)
		num[i - 1] = getNumSuite(i);
	int n10 = 0;
	int n8 = 0;
	int n5 = 0;
	int n3 = 0;
	for (i = 0; i < 4; i++) {
		if (num[i] > 0) {
			switch (num[i]) {
			case 13:
				return true;
			case 10:
				n10++;
				break;
			case 8:
				n8++;
				break;
			case 5:
				n5++;
				break;
			case 3:
				n3++;
				break;
			}
		}
	}
	if (n10 > 0 && n3 > 0)
		return true;
	else if (n8 > 0 && n5 > 0)
		return true;
	else if (n5 >= 2 && n3 > 0)
		return true;
	return false;
}

	MaubinhGroupCardLogic* MaubinhPlayerCard::getCardSameSuite(int suite, int nCard) {
	MaubinhGroupCardLogic* result = new MaubinhGroupCardLogic();
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetSuit() == suite) {
				MaubinhCardLogic* temp = new MaubinhCardLogic();
				temp->ID = GroupCards.at(i)->Cards.at(j)->ID;
				result->AddCard(temp);
				if (result->GetNumOfCards() == nCard)
					return result;
			}
		}
	}
	return result;
}

	int MaubinhPlayerCard::getMaxCardIDSuite(int suite) {
	int maxID = 0;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetSuit() == suite) {
				if (maxID < GroupCards.at(i)->Cards.at(j)->ID)
					maxID = GroupCards.at(i)->Cards.at(j)->ID;
			}
		}
	}
	return maxID;
}

	void MaubinhPlayerCard::SapXepTruocSoBai() {
	ArrangeChi();
	ChiDau->SapXepTruocSoBai2();
	ChiGiua->SapXepTruocSoBai2();
	ChiCuoi->SapXepTruocSoBai2();
	ApplyNew3GroupCards(ChiDau, ChiGiua, ChiCuoi);
}

	bool MaubinhPlayerCard::MuoiBaCay()
	{
		int countBlack = 0;
		int countRed = 0;
		for (int i = 0; i < GetNumOfGroupCards(); i++) {
			for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
				if (GroupCards.at(i)->Cards.at(j)->GetSuit() == 3 || GroupCards.at(i)->Cards.at(j)->GetSuit() == 4)
				{
					countRed++;
				}
				else
				{
					countBlack++;
				}
			}
		}
		if (countBlack >= 13 || countRed >= 13)
			return true;
		return false;
	}

	bool MaubinhPlayerCard::MuoiHaiCay()
	{
		int countBlack = 0;
		int countRed = 0;
		for (int i = 0; i < GetNumOfGroupCards(); i++) {
			for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
				if (GroupCards.at(i)->Cards.at(j)->GetSuit() == 3 || GroupCards.at(i)->Cards.at(j)->GetSuit() == 4)
				{
					countRed++;
				}
				else
				{
					countBlack++;
				}
			}
		}
		if (countBlack >= 12 || countRed >= 12)
			return true;
		return false;
	}

	int MaubinhPlayerCard::GetPlayerCardsKindBao(bool checkBinhLung, bool isTinhAt)
	{
		if (SanhRong())
			return EM_SANHRONG;
		 
		if (isTinhAt) {
			if (MuoiBaCay())
				return EM_MUOI_BA;
			if (MuoiHaiCay())
				return EM_MUOI_HAI;
		}
		
		// Check 3 cai thung
		int arrayKind[5] = { 0, 0, 0, 0 , 0};
		int arrayCount[15];
		for (int i = 0; i < 15; i++)
			arrayCount[i] = 0;
		 
		for (int i = 0; i < GetNumOfGroupCards(); i++) {
			for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
				//gc->AddCard(GroupCards.at(i)->Cards.at(j));
				arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] = arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] + 1;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			arrayCount[arrayKind[i]] = arrayCount[arrayKind[i]] + 1;
		}

		if (arrayCount[5] == 2 && arrayCount[3] == 1 || arrayCount[10] == 1 && arrayCount[3] == 1 || arrayCount[8] == 1 && arrayCount[5] == 1)
		{
			return EM_3THUNG;
		}

		 
		if (BaSanh2())
			return EM_3SANH;


		for (int i = 0; i < 15; i++)
		{
			arrayCount[i] = 0;
		}
		for (int i = 0; i < GetNumOfGroupCards(); i++) {
			for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
				//gc->AddCard(GroupCards.at(i)->Cards.at(j));
				arrayCount[GroupCards.at(i)->Cards.at(j)->GetNumber()] = arrayCount[GroupCards.at(i)->Cards.at(j)->GetNumber()] + 1;
			}
		}

		int countPair = 0;
		for (int i = 0; i < 15; i++)
		{
			countPair = countPair + arrayCount[i] / 2;
		}
		 
		if (countPair == 6)
		{
			return EM_LUCPHEBON;
		}

		if (checkBinhLung)
		{
			bool binhlung = true;
			if (MaubinhGameRule::SoSanhChi(ChiDau, ChiGiua, isTinhAt) == -1)
			if (MaubinhGameRule::SoSanhChi(ChiGiua, ChiCuoi, isTinhAt) == -1) {
				binhlung = false;
			}
			if (binhlung)
				return EM_BINHLUNG;
		}

		return EM_NORMAL;
	}
	bool MaubinhPlayerCard::BaSanh2()
	{
		 
		int i, j, ii, z;
		int iNum;
		vector<int> number;
		int n, x;
		int index, index2;
		 
		for (i = 0; i < GetNumOfGroupCards(); i++)
		{
			for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++)
			{
				n = GroupCards.at(i)->Cards[j]->GetNumber();
				number.push_back(n);
			}
		}
		//sap xep theo number tang dan
		for (i = 0; i < number.size(); i++)
		{
			for (j = i + 1; j < number.size(); j++)
			{
				if (number[i] > number[j])
				{
					iNum = number[i];
					number[i] = number[j];
					number[j] = iNum;
				}
			}
		}
		for (i = 0; i < number.size() - 3; i++)
		{
			vector<int>arr;
			vector<int>arr1;
			arr.push_back(number[i]);
			for (j = 0; j < number.size(); j++)
			{
				if (arr[arr.size() - 1] + 1 == number[j] && arr.size() < 4)
				{
					arr.push_back(number[j]);
				}
				else if (arr[arr.size() - 1] == 5 && number[j] == 14 && arr.size() < 4 && arr[0] == 2)
					arr.push_back(number[j]);
				else if (i != j)
					arr1.push_back(number[j]);
			}
			if (arr.size() == 4 && arr1.size() == 9)
			{
				index = -1;
				for (z = 0; z < arr1.size(); z++)
				{
					if (arr[arr.size() - 1] + 1 != arr1[z] && arr1[z] != 14)
						continue;
					vector<int> mang1;
					vector<int> mang2;
					for (j = 0; j < arr.size(); j++)
						mang1.push_back(arr[j]);
					for (j = 0; j < arr1.size(); j++)
					{
						if (mang1[mang1.size() - 1] + 1 == arr1[j] && mang1.size() < 5 && j != index)
						{
							mang1.push_back(arr1[j]);
							index = j;
							//break;
						}
						else if (mang1[arr.size() - 1] == 5 && arr1[j] == 14 && mang1.size() < 5 && mang1[0] == 2 && j != index)
						{
							mang1.push_back(arr1[j]);
							index = j;
							//break;
						}
						else
							mang2.push_back(arr1[j]);
					}
					if (mang1.size() == 5 && mang2.size() == 8)
					{
						for (j = 0; j < mang2.size() - 3; j++)
						{
							vector<int>s1;
							vector<int>s2;
							s1.push_back(mang2[j]);
							for (x = 0; x < mang2.size(); x++)
							{
								if (s1[s1.size() - 1] + 1 == mang2[x] && s1.size() < 4)
									s1.push_back(mang2[x]);
								else if (s1[s1.size() - 1] == 5 && mang2[x] == 14 && s1.size() < 4 && s1[0] == 2)
									s1.push_back(mang2[x]);
								else if (j != x)
								{
									s2.push_back(mang2[x]);
								}
							}
							if (s1.size() == 4 && s2.size() == 4)
							{
								index2 = -1;
								for (x = 0; x < s2.size(); x++)
								{
									if (s1[s1.size() - 1] + 1 != s2[x] && s2[x] != 14)
										continue;
									 
									vector<int> mang3;
									vector<int> mang4;
									int xx;
									for (xx = 0; xx < s1.size(); xx++)
										mang3.push_back(s1[xx]);
									for (n = 0; n < s2.size(); n++)
									{
										if (mang3[mang3.size() - 1] + 1 == s2[n] && mang3.size() < 5 && n != index2)
										{
											mang3.push_back(s2[n]);
											index2 = n;
										}
										else if (mang3[mang3.size() - 1] == 5 && s2[n] == 14 && mang3.size() < 5 && mang3[0] == 2 && n != index2)
										{
											mang3.push_back(s2[n]);
											index2 = n;
										}
										else
											mang4.push_back(s2[n]);
									}
									if (mang3.size() == 5 && mang4.size() == 3)
									{
										 
										bool isSequence = true;
										n = mang4[0];
										bool at = false;
										 
										for (xx = 1; xx < mang4.size(); xx++)
										{
											if (n == 3 && mang4[xx] == 14 && !at)
											{
												at = true;
												continue;
											}
											if (n + 1 != mang4[xx])
											{
												isSequence = false;
												break;
											}
											n = mang4[xx];
										}
										if (isSequence)
										{
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	int* MaubinhPlayerCard::ArrangePlayerCardsBao()
	{
		int* arrayId = new int [13];
		int kind = GetPlayerCardsKindBao(false);
		//if (kind == EM_SANHRONG || kind == EM_MUOI_HAI || kind == EM_MUOI_BA)
		if (kind == EM_SANHRONG)
		{
			int count = 0;
			for (int i = 0; i < GetNumOfGroupCards(); i++) {
				for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
					arrayId[count] = GroupCards.at(i)->Cards.at(j)->ID;
					count++;
				}
			}
			 
			return arrayId;
		}
		else
		{
			if (kind == EM_3THUNG)
			{
				int arrayKind[5] = { 0, 0, 0, 0, 0 };
				vector<vector<int>> arrayNumKind;
				for (int i = 0; i < 5; i++)
				{
					vector<int> arrayNum;
					arrayNumKind.push_back(arrayNum);
				}

				for (int i = 0; i < GetNumOfGroupCards(); i++) {
					for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
						//gc->AddCard(GroupCards.at(i)->Cards.at(j));
						//arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] = arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] + 1;
						arrayNumKind.at(GroupCards.at(i)->Cards.at(j)->GetSuit()).push_back(GroupCards.at(i)->Cards.at(j)->ID);
					}
				}

				int count = 0;
				bool next = true;
				int idThung1 = -1, idThung2 = -1;
				for (int i = 0; i < 5; i++)
				{
					if (arrayNumKind.at(i).size() == 5 || arrayNumKind.at(i).size() == 10 || arrayNumKind.at(i).size() == 8)
					{
						if (idThung1 == -1)
						{
							idThung1 = i;
						}
						else
						{
							idThung2 = i;
						}
					}
				}

				for (int i = 0; i < 5; i++)
				{
					if (arrayNumKind.at(i).size() == 5 || arrayNumKind.at(i).size() == 10)
					{
						for (int j = 0; j < arrayNumKind.at(i).size(); j++)
						{
							arrayId[count] = arrayNumKind.at(i).at(j);
							count++;
						}
					}
					else if (arrayNumKind.at(i).size() == 8)
					{
						int j;
						for (j = 0; j < 5; j++)
						{
							arrayId[count] = arrayNumKind.at(i).at(j);
							count++;
						}
						for (; j < 8; j++)
						{
							arrayId[10 + j - 5] = arrayNumKind.at(i).at(j);
						}
						next = false;
					}

				}
				if (next)
				{
					for (int i = 0; i < 5; i++)
					{
						if (arrayNumKind.at(i).size() == 3)
						{
							for (int j = 0; j < arrayNumKind.at(i).size(); j++)
							{
								arrayId[count] = arrayNumKind.at(i).at(j);
								count++;
							}
						}
					}
				}
				return arrayId;
			}
			else if (kind == EM_3SANH)
			{
				int i, j, ii, z;
				int iNum;
				int number[13];
				int n, x;
				int index = 0;
				int index2 = 0;
				int iNumCard = 13;
				for (i = 0; i < iNumCard; i++)
				{
					iNum = arrayId[i] / 4 + 2;
					number[i] = iNum;
				}

				int count = 0;
				for (int i = 0; i < GetNumOfGroupCards(); i++) {
					for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
						//gc->AddCard(GroupCards.at(i)->Cards.at(j));
						//arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] = arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] + 1;
						//arrayNumKind.at(GroupCards.at(i)->Cards.at(j)->GetSuit()).push_back(GroupCards.at(i)->Cards.at(j)->ID);
						iNum = GroupCards.at(i)->Cards.at(j)->GetNumber();
						number[count] = iNum;
						count++;
					}
				}

				//sap xep theo number tang dan
				for (i = 0; i < 13; i++)
				{
					for (j = i + 1; j < 13; j++)
					{
						if (number[i] > number[j])
						{
							iNum = number[i];
							number[i] = number[j];
							number[j] = iNum;
						}
					}
				}
				for (i = 0; i < 13 - 3; i++)
				{

					vector<int> arr;
					vector<int> arr1;
					arr.push_back(number[i]);
					for (j = 0; j < 13; j++)
					{
						if (arr[arr.size() - 1] + 1 == number[j] && arr.size() < 4)
						{
							arr.push_back(number[j]);
						}
						else if (arr[arr.size() - 1] == 5 && number[j] == 14 && arr.size() < 4 && arr[0] == 2)
							arr.push_back(number[j]);
						else if (i != j)
							arr1.push_back(number[j]);
					}
					if (arr.size() == 4 && arr1.size() == 9)
					{
						index = -1;
						for (z = 0; z < arr1.size(); z++)
						{
							if (arr[arr.size() - 1] + 1 != arr1[z] && arr1[z] != 14)
								continue;
							vector<int> mang1;
							vector<int> mang2;
							for (j = 0; j < arr.size(); j++)
								mang1.push_back(arr[j]);
							for (j = 0; j < arr1.size(); j++)
							{
								if (mang1[mang1.size() - 1] + 1 == arr1[j] && mang1.size() < 5 && index != j)
								{
									mang1.push_back(arr1[j]);
									index = j;
									//break;
								}
								else if (mang1[arr.size() - 1] == 5 && arr1[j] == 14 && mang1.size() < 5 && mang1[0] == 2 && index != j)
								{
									mang1.push_back(arr1[j]);
									index = j;
									//break;
								}
								else
									mang2.push_back(arr1[j]);
							}
							if (mang1.size() == 5 && mang2.size() == 8)
							{
								for (j = 0; j < mang2.size() - 3; j++)
								{

									vector <int> s1;
									vector <int> s2;
									s1.push_back(mang2[j]);
									for (x = 0; x < mang2.size(); x++)
									{
										if (s1[s1.size() - 1] + 1 == mang2[x] && s1.size() < 4)
											s1.push_back(mang2[x]);
										else if (s1[s1.size() - 1] == 5 && mang2[x] == 14 && s1.size() < 4 && s1[0] == 2)
											s1.push_back(mang2[x]);
										else if (j != x)
										{
											s2.push_back(mang2[x]);
										}
									}
									if (s1.size() == 4 && s2.size() == 4)
									{
										index2 = -1;
										for (x = 0; x < s2.size(); x++)
										{
											if (s1[s1.size() - 1] + 1 != s2[x] && s2[x] != 14)
												continue;
											vector <int> mang3;
											vector <int> mang4;
											int xx;
											for (xx = 0; xx < s1.size(); xx++)
												mang3.push_back(s1[xx]);
											for (n = 0; n < s2.size(); n++)
											{
												if (mang3[mang3.size() - 1] + 1 == s2[n] && mang3.size() < 5 && index2 != n)
												{
													mang3.push_back(s2[n]);
													index2 = n;
												}
												else if (mang3[mang3.size() - 1] == 5 && s2[n] == 14 && mang3.size() < 5 && mang3[0] == 2 && index2 != n)
												{
													mang3.push_back(s2[n]);
													index2 = n;
												}
												else
													mang4.push_back(s2[n]);
											}
											if (mang3.size() == 5 && mang4.size() == 3)
											{

												bool isSequence = true;
												n = mang4[0];
												bool at = false;
												for (xx = 1; xx < mang4.size(); xx++)
												{
													if (n == 3 && mang4[xx] == 14 && !at)
													{
														at = true;
														continue;
													}
													if (n + 1 != mang4[xx])
													{
														isSequence = false;
														break;
													}
													n = mang4[xx];
												}
												if (isSequence)
												{

													vector<int> result;
													for (x = 0; x < 3; x++)
													{
														result.push_back(mang4[x]);
													}
													for (x = 0; x < 5; x++)
													{
														result.push_back(mang1[x]);
													}
													for (x = 0; x < 5; x++)
													{
														result.push_back(mang3[x]);
													}
													for (x = 0; x < iNumCard; x++)
													{

														 
														for (int i1 = 0; i1 < GetNumOfGroupCards(); i1++) {
															for (int j1= 0; j1 < GroupCards.at(i1)->GetNumOfCards(); j1++) {
																if (GroupCards.at(i1)->Cards.at(j1)->GetNumber() == result.at(12-x))
																{
																	int k;
																	for (k = 0; k < x; k++)
																	{
																		if (arrayId[k] == GroupCards.at(i1)->Cards.at(j1)->ID)
																			break;
																	}
																	if (k == x)
																	{
																		arrayId[x] = GroupCards.at(i1)->Cards.at(j1)->ID;
																	}
																}
															}
														}
														 
													}
													return arrayId;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else if (kind == EM_LUCPHEBON)
			{
				int arrayKind[5] = { 0, 0, 0, 0, 0 };
				vector<vector<int>> arrayNumKind;
				for (int i = 0; i < 15; i++)
				{
					vector<int> arrayNum;
					arrayNumKind.push_back(arrayNum);
				}

				for (int i = 0; i < GetNumOfGroupCards(); i++) {
					for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
						//gc->AddCard(GroupCards.at(i)->Cards.at(j));
						//arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] = arrayKind[GroupCards.at(i)->Cards.at(j)->GetSuit()] + 1;
						arrayNumKind.at(GroupCards.at(i)->Cards.at(j)->GetNumber()).push_back(GroupCards.at(i)->Cards.at(j)->ID);
					}
				}

				int count = 0;
				int numPair = 0;
				for (int i = 14; i >= 0; i--)
				{
					if (arrayNumKind.at(i).size() >= 2)
					{
						arrayId[count] = arrayNumKind.at(i).at(arrayNumKind.at(i).size() - 1);
						arrayNumKind.at(i).pop_back();
						count++;

						arrayId[count] = arrayNumKind.at(i).at(arrayNumKind.at(i).size() - 1);
						arrayNumKind.at(i).pop_back();
						count++;
						numPair++;
						if (numPair == 2)
							break;
					}
				}

				for (int i = 0; i < 15; i++)
				{
					if (arrayNumKind.at(i).size() > 0)
					{
						int j;
						for (j = 0; j < 4; j++)
						if (arrayId[j] / 4 == arrayNumKind.at(i).at(0) / 4)
							break;
						if (j == 4)
						{
							arrayId[count] = arrayNumKind.at(i).at(arrayNumKind.at(i).size() - 1);
							arrayNumKind.at(i).pop_back();
							count++;
							break;
						}
						 
					}
				}

				for (int i = 14; i >= 0; i--)
				{
					if (arrayNumKind.at(i).size() >= 2)
					{
						arrayId[count] = arrayNumKind.at(i).at(arrayNumKind.at(i).size() - 1);
						arrayNumKind.at(i).pop_back();
						count++;

						arrayId[count] = arrayNumKind.at(i).at(arrayNumKind.at(i).size() - 1);
						arrayNumKind.at(i).pop_back();
						count++;
						numPair++;
						if (numPair == 4)
							break;
					}
				}

				for (int i = 0; i < 15; i++)
				{
					if (arrayNumKind.at(i).size() > 0)
					{
						int j;
						for (j = 5; j < 10; j++)
							if (arrayId[j] / 4 == arrayNumKind.at(i).at(0) / 4)
								break;
						if (j == 10)
						{
							arrayId[count] = arrayNumKind.at(i).at(arrayNumKind.at(i).size() - 1);
							arrayNumKind.at(i).pop_back();
							count++;
							break;
						}

					}
				}

				for (int i = 0; i < 15; i++)
				{
					if (arrayNumKind.at(i).size() >= 1)
					{
						for (int j = 0; j < arrayNumKind.at(i).size(); j++)
						{
							arrayId[count] = arrayNumKind.at(i).at(j);
							count++;
						}
					}
						 
				}

				return arrayId;
			}
		}
	}

	bool MaubinhPlayerCard::isLung()
	{
		// chi dung rieng cho binh at
		bool binhlung = true;
		if (MaubinhGameRule::SoSanhChi(ChiDau, ChiGiua, true) == -1)
		if (MaubinhGameRule::SoSanhChi(ChiGiua, ChiCuoi, true) == -1) {
			binhlung = false;
		}
		return binhlung;
	}

	bool MaubinhPlayerCard::getWrongChi0(bool isTinhAt)
	{
		if (MaubinhGameRule::SoSanhChi(ChiDau, ChiGiua, isTinhAt) != -1)
			return true;
		return false;
	}

	bool MaubinhPlayerCard::getWrongChi1(bool isTinhAt)
	{
		if (MaubinhGameRule::SoSanhChi(ChiGiua, ChiCuoi, isTinhAt) != -1) {
			return true;
		}
		return false;
	}

int* MaubinhPlayerCard::getAutoArrangeCard()
{

	int kindBao = GetPlayerCardsKindBao(false, false);
	if (kindBao == EM_SANHRONG || kindBao == EM_LUCPHEBON || kindBao == EM_3SANH || kindBao == EM_3THUNG) {
		return ArrangePlayerCardsBao();
	}
	
	string s = "";
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			s = s + " " + to_string(GroupCards.at(i)->Cards.at(j)->ID);
		}
	}
	AXLOGD("ARRAY CARD %s ", s.c_str());
	int arraySuit[5][15];
	int arrayNumber[15][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 15; j++) {
            arraySuit[i][j] = -1;
        }
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 5; j++) {
            arrayNumber[i][j] = -1;
        }
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			MaubinhCardLogic* card = GroupCards.at(i)->Cards.at(j);
			if (card->GetNumber() == 14) {
				arraySuit[card->GetSuit()][1] = 1;
				arrayNumber[1][card->GetSuit()] = 1;
			}
			arraySuit[card->GetSuit()][card->GetNumber()] = 1;
			arrayNumber[card->GetNumber()][card->GetSuit()] = 1;
		}
	}
	// check thung pha sanh
	int* arrayId = new int [13];
	int countId = 0;
	int arrayThungPhaSanh[2][5];
	int countThungPhaSanh = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            arrayThungPhaSanh[i][j] = -1;
        }
    }
	for (int i = 1; i < 5; i++) {
		int count = 0;
		for (int j = 14; j >= 1; j--) {
			if (arraySuit[i][j] == 1) {
				count++;
				if (count == 5) {
					for (int k = 0; k < 5; k++) {
						arrayThungPhaSanh[countThungPhaSanh][k] = MaubinhGameRule::getId(j + 4 - k, i);
						arraySuit[i][j + 4 - k] = -1;
						arrayNumber[j + 4 - k][i] = -1;
						MaubinhGameRule::checkAt(arrayNumber, arraySuit, j + 4 - k, i);
					}
					countThungPhaSanh++;
					count = 0;
				}
			}
			else {
				count = 0;
			}
		}
	}
	if (arrayThungPhaSanh[1][0] >= 0 && arrayThungPhaSanh[1][0] > arrayThungPhaSanh[0][0]) {
		for (int i = 1; i >= 0; i--) {
			if (arrayThungPhaSanh[i][0] >= 0) {
				for (int j = 0; j < 5; j++) {
					arrayId[countId] = arrayThungPhaSanh[i][j];
					countId++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			if (arrayThungPhaSanh[i][0] >= 0) {
				for (int j = 0; j < 5; j++) {
					arrayId[countId] = arrayThungPhaSanh[i][j];
					countId++;
				}
			}
		}
	}

	// check Tu Quy
	int arrayTuQuy[3][4];
	int countTuQuy = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++) {
            arrayTuQuy[i][j] = -1;
        }
	for (int i = 14; i >= 2; i--) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				count++;
				if (count == 4) {
					for (int k = 0; k < 4; k++) {
						arrayTuQuy[countTuQuy][k] = MaubinhGameRule::getId(i, k + 1);
						arraySuit[k + 1][i] = -1;
						arrayNumber[i][k + 1] = -1;
						MaubinhGameRule::checkAt(arrayNumber, arraySuit, i, k + 1);
					}
					count = 0;
					countTuQuy++;
				}
			}
			else {
				count = 0;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (arrayTuQuy[i][0] >= 0) {
			for (int j = 0; j < 4; j++) {
				arrayId[countId] = arrayTuQuy[i][j];
				countId++;
			}
			// chon ra 1 cay mau thau nho nhat
			Vec2 idMauThau = MaubinhGameRule::getMauThau(arrayNumber);
			arrayId[countId] = MaubinhGameRule::getId(idMauThau.x, idMauThau.y);
			arrayNumber[(int)idMauThau.x][(int)idMauThau.y] = -1;
			arraySuit[(int)idMauThau.y][(int)idMauThau.x] = -1;
			countId++;
		}
	}

	// check Cu Lu
	for (int i = 14; i >= 2; i--) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				count++;
			}
		}
		if (count == 3) {
			int idPair = MaubinhGameRule::getPair(arrayNumber, i);
			if (idPair >= 0) {
				for (int k = 0; k < 4; k++) {
					if (arrayNumber[i][k + 1] == 1) {
						arrayId[countId] = MaubinhGameRule::getId(i, k + 1);
						arraySuit[k + 1][i] = -1;
						arrayNumber[i][k + 1] = -1;
						MaubinhGameRule::checkAt(arrayNumber, arraySuit, i, k + 1);
						countId++;
					}
				}
				count = 0;
				for (int k = 0; k < 4; k++) {
					if (arrayNumber[idPair][k + 1] == 1) {
						arrayId[countId] = MaubinhGameRule::getId(idPair, k + 1);
						arraySuit[k + 1][idPair] = -1;
						arrayNumber[idPair][k + 1] = -1;
						MaubinhGameRule::checkAt(arrayNumber, arraySuit, idPair, k + 1);
						countId++;
						count++;
						if (count == 2)
							break;
					}
				}
			}
		}
	}

	// check thung
	int arrayThung[2][5];
	int countThung = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5; j++) {
            arrayThung[i][j] = -1;
        }
	vector <int> arrayIdThung;
	vector <int> arrayIdThung2;
	for (int i = 1; i < 5; i++) {
		arrayIdThung.clear();
		arrayIdThung2.clear();
		int state = 0;
		for (int j = 14; j >= 2; j--) {
			if (arraySuit[i][j] == 1) {
				arrayIdThung.push_back(j);
			}
		}
		while (arrayIdThung.size() + arrayIdThung2.size() >= 5)
		{
			// uu tien lay nhung quan thung khong tham gia vao sanh hoac thu hoac sam
			int k;
			for (k = 0; k < arrayIdThung.size(); k++) {
				bool isSuitable = false;
				if (state == 0) {
					if (!MaubinhGameRule::inSanh(arrayNumber, arrayIdThung[k]) && !MaubinhGameRule::inXam(arrayNumber, arrayIdThung[k]) && !MaubinhGameRule::inPair(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else if (state == 1) {
					if (!MaubinhGameRule::inSanh(arrayNumber, arrayIdThung[k]) && !MaubinhGameRule::inXam(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else if (state == 2) {
					if (!MaubinhGameRule::inSanh(arrayNumber, arrayIdThung[k]) && !MaubinhGameRule::inPair(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else if (state == 3) {
					if (!MaubinhGameRule::inXam(arrayNumber, arrayIdThung[k]) && !MaubinhGameRule::inPair(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else if (state == 4) {
					if (!MaubinhGameRule::inSanh(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else if (state == 5) {
					if (!MaubinhGameRule::inXam(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else if (state == 6) {
					if (!MaubinhGameRule::inPair(arrayNumber, arrayIdThung[k])) {
						isSuitable = true;
					}
				}
				else {
					isSuitable = true;
				}
				if (isSuitable) {
					arrayIdThung2.push_back(arrayIdThung[k]);
					arrayIdThung.erase(arrayIdThung.begin() + k);
					k--;
					if (arrayIdThung2.size() == 5) {
						sort(arrayIdThung2.begin(), arrayIdThung2.end(), greater<int>());
						for (int k = 0; k < 5; k++) {
							arrayThung[countThung][k] = MaubinhGameRule::getId(arrayIdThung2[k], i);
							arraySuit[i][arrayIdThung2[k]] = -1;
							arrayNumber[arrayIdThung2[k]][i] = -1;
							MaubinhGameRule::checkAt(arrayNumber, arraySuit, arrayIdThung2[k], i);
						}
						countThung++;
						arrayIdThung2.clear();
						state = 0;
						break;
					}
				}
			}
			if (k == arrayIdThung.size()) {
				state++;
			}
		}
	}

	bool isRevert = false;
	for (int i = 0; i < 5; i++) {
		if (MaubinhGameRule::getNumber(arrayThung[1][i]) > MaubinhGameRule::getNumber(arrayThung[0][i])) {
			isRevert = true;
			break;
		}
		else if (MaubinhGameRule::getNumber(arrayThung[1][i]) < MaubinhGameRule::getNumber(arrayThung[0][i])) {
			break;
		}
	}
	if (isRevert) {
		for (int i = 1; i >= 0; i--) {
			if (arrayThung[i][0] >= 0) {
				for (int j = 0; j < 5; j++) {
					arrayId[countId] = arrayThung[i][j];
					countId++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			if (arrayThung[i][0] >= 0) {
				for (int j = 0; j < 5; j++) {
					arrayId[countId] = arrayThung[i][j];
					countId++;
				}
			}
		}
	}

	// Check Sanh
	int arraySanh[2][5];
	int countSanh = 0;
	int count = 0;
	int arrayIdSanh[15];
	bool haveSanh = true;
	while (haveSanh)
	{
		count = 0;
		int i;
		for (i = 14; i > 0; i--) {
			int j;
			for (j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					arrayIdSanh[count] = j;
					count++;
					break;
				}
			}
			
			if (j == 5 ) {
				AXLOGD("INDEX JLJ NEW %i ", i);
				if (count >= 5) {
					int start = 0;
					if (count > 5 && count < 10) {
						// tim Card Id lam cho sanh chua it doi nhat (hoac la chua doi co gia tri thap nhat)
						int minPriorityValue = 10000;
						for (int k = 0; k <= count - 5; k++) {
							bool inGroup = false;
							int priorityValue = 0;
							int countPair = 0;
							for (int l = 0; l < 5; l++) {
								int index = i + count - k - l;
								if (MaubinhGameRule::inXam(arrayNumber, index) || MaubinhGameRule::inPair(arrayNumber, index)) {
									priorityValue = priorityValue + index + countPair * 20;
									countPair++;
								}
							}
							if (priorityValue < minPriorityValue) {
								minPriorityValue = priorityValue;
								start = k;
							}
						}
					}
					int startNumber = i + count - start;
					for (int j = 0; j < 5; j++) {
						arrayNumber[startNumber - j][arrayIdSanh[start + j]] = -1;
						arraySuit[arrayIdSanh[start + j]][startNumber - j] = -1;
						MaubinhGameRule::checkAt(arrayNumber, arraySuit, startNumber - j, arrayIdSanh[start + j]);
						arrayId[countId] = MaubinhGameRule::getId(startNumber - j, arrayIdSanh[start + j]);
						countId++;
					}
					break;
				}
				else {
					if (i == 0)
						haveSanh = false;
				}
				count = 0;
				AXLOGD("INDEX I %i ", i);
			}
			
		}
		if (i < 1) {
			if (count >= 5) {
				int start = 0;
				if (count > 5 && count < 10) {
					// tim Card Id khong nam trong doi hoac xam
					for (int k = 0; k < count - 5; k++) {
						if (!MaubinhGameRule::inXam(arrayNumber, i + count) && MaubinhGameRule::inPair(arrayNumber, i + count)) {
							start = k;
							break;
						}
					}
				}
				int startNumber = i + count - start;
				for (int j = 0; j < 5; j++) {
					arrayNumber[startNumber - j][arrayIdSanh[start + j]] = -1;
					arraySuit[arrayIdSanh[start + j]][startNumber - j] = -1;
					MaubinhGameRule::checkAt(arrayNumber, arraySuit, startNumber - j, arrayIdSanh[start + j]);
					arrayId[countId] = MaubinhGameRule::getId(startNumber - j, arrayIdSanh[start + j]);
					countId++;
				}
				break;
			}
			haveSanh = false;
			break;
		}
	}

	// Check xam
	for (int i = 14; i > 1; i--) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				count++;
			}
		}
		if (count == 3) {
			for (int k = 0; k < 4; k++) {
				if (arrayNumber[i][k + 1] == 1) {
					arrayId[countId] = MaubinhGameRule::getId(i, k + 1);
					arraySuit[k + 1][i] = -1;
					arrayNumber[i][k + 1] = -1;
					countId++;
				}
			}
			int num = countId < 10 ? 2 : 0;
			
			// chon ra 2 cay mau thau nho nhat
			for (int j = 0; j < num; j++) {
				Vec2 idMauThau = MaubinhGameRule::getMauThau(arrayNumber);
				arrayId[countId] = MaubinhGameRule::getId(idMauThau.x, idMauThau.y);
				arrayNumber[(int)idMauThau.x][(int)idMauThau.y] = -1;
				arraySuit[(int)idMauThau.y][(int)idMauThau.x] = -1;
				countId++;
			}
		}
	}
	s = "";
	for (int i = 0; i < countId; i++) {
		s = s + to_string(arrayId[i]) + ", ";
	}
	AXLOGD("ARRAY AUTO xam %s ", s.c_str());

	// Check thu
	int start = 14;
	int d = -1;
	int limit = 2;
	if (countId >= 5) {
		start = 2;
		d = 1;
		limit = 14;
	}
	for (int i = start; (i - limit) * d <= 0; i = i + d) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				count++;
			}
		}
		if (count == 2) {
			int idPair = MaubinhGameRule::getPair(arrayNumber, i);
			if (idPair >= 0) {
				for (int k = 0; k < 4; k++) {
					if (arrayNumber[i][k + 1] == 1) {
						arrayId[countId] = MaubinhGameRule::getId(i, k + 1);
						arraySuit[k + 1][i] = -1;
						arrayNumber[i][k + 1] = -1;
						countId++;
					}
				}
				count = 0;
				for (int k = 0; k < 4; k++) {
					if (arrayNumber[idPair][k + 1] == 1) {
						arrayId[countId] = MaubinhGameRule::getId(idPair, k + 1);
						arraySuit[k + 1][idPair] = -1;
						arrayNumber[idPair][k + 1] = -1;
						countId++;
						count++;
						if (count == 2)
							break;
					}
				}
				// chon ra 1 cay mau thau nho nhat
				Vec2 idMauThau = MaubinhGameRule::getMauThau(arrayNumber);
				arrayId[countId] = MaubinhGameRule::getId(idMauThau.x, idMauThau.y);
				arrayNumber[(int)idMauThau.x][(int)idMauThau.y] = -1;
				arraySuit[(int)idMauThau.y][(int)idMauThau.x] = -1;
				countId++;
			}
		}
	}

	s = "";
	for (int i = 0; i < countId; i++) {
		s = s + to_string(arrayId[i]) + ", ";
	}
	AXLOGD("ARRAY AUTO THU %s ", s.c_str());

	// check doi
	for (int i = 14; i > 1; i--) {
		int count = 0;
		for (int j = 1; j < 5; j++) {
			if (arrayNumber[i][j] == 1) {
				count++;
			}
		}
		if (count == 2) {
			for (int k = 0; k < 4; k++) {
				if (arrayNumber[i][k + 1] == 1) {
					arrayId[countId] = MaubinhGameRule::getId(i, k + 1);
					arraySuit[k + 1][i] = -1;
					arrayNumber[i][k + 1] = -1;
					countId++;
				}
			}
			int num = countId < 10 ? 3 : 1;
			// chon ra 3 cay mau thau nho nhat
			for (int j = 0; j < num; j++) {
				Vec2 idMauThau = MaubinhGameRule::getMauThau(arrayNumber);
				arrayId[countId] = MaubinhGameRule::getId(idMauThau.x, idMauThau.y);
				arrayNumber[(int)idMauThau.x][(int)idMauThau.y] = -1;
				arraySuit[(int)idMauThau.y][(int)idMauThau.x] = -1;
				countId++;
			}
		}
	}

	s = "";
	for (int i = 0; i < countId; i++) {
		s = s + to_string(arrayId[i]) + ", ";
	}
	AXLOGD("ARRAY AUTO DOI %s ", s.c_str());

	// check Mau Thau
	if (countId == 5) {
		// co 2 chi mau thau
		for (int i = 14; i > 1; i--) {
			for (int j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					arrayId[countId] = MaubinhGameRule::getId(i, j);
					countId++;
					arrayNumber[i][j] = -1;
					break;
				}
			}
			if (countId > 5)
				break;
		}
		for (int i = 2; i <= 14; i++) {
			for (int j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					arrayId[countId] = MaubinhGameRule::getId(i, j);
					countId++;
				}
			}
		}
	}
	else {
		for (int i = 14; i > 1; i--) {
			for (int j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					arrayId[countId] = MaubinhGameRule::getId(i, j);
					countId++;
				}
			}
		}
	}
	
	s = "";
	for (int i = 0; i < countId; i++) {
		s = s + to_string(arrayId[i]) + ", ";
	}
	AXLOGD("ARRAY AUTO %s ", s.c_str());
	return arrayId;
}
