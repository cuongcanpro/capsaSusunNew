#include "MaubinhGroupCardLogic.h"
#include "MaubinhConstant.h"
#include "MaubinhCardLogic.h"

MaubinhGroupCardLogic::MaubinhGroupCardLogic(void)
{
}


MaubinhGroupCardLogic::~MaubinhGroupCardLogic(void)
{
}



	 void MaubinhGroupCardLogic::GroupCard() {
		// COnvert code Binh
		IsSelected = false;
	}

	 int MaubinhGroupCardLogic::GetNumOfCards() {
		// Convert code Binh
		return Cards.size();
	}

	 int MaubinhGroupCardLogic::GetGroupKind(bool isTinhAt) {
		// Convert code Binh
		// ************************************************
		// PHAN LOAI BO 3 QUAN
		// ************************************************
		int j;
		if (GetNumOfCards() == 3) {
			// Check Xam chi
			if (XamChi())
				return EG_SAMCO;
			if (MotDoi())
				return EG_DOI;

			Reset();
			for (j = 2; j >= 0; j--)
				Value.push_back(Cards.at(j)->GetNumber());
			return EG_MAUTHAU;

		}

		// ************************************************
		// PHAN LOAI BO 5 QUAN
		// ************************************************
		if (GetNumOfCards() == 5) {
			if (isTinhAt)
			{
				if (ThungPhaSanhThuong())
					return EG_THUNGPHASANHTHUONG;
			}
			if (ThungPhaSanh())
				return EG_THUNGPHASANH;
			if (TuQui())
				return EG_TUQUI;
			if (CuLu())
				return EG_CULU;
			if (Thung())
				return EG_THUNG;
			if (Sanh())
				return EG_SANH;
			if (XamChi())
				return EG_SAMCO;
			if (HaiDoiKhacNhau())
				return EG_THU;
			if (MotDoi())
				return EG_DOI;
		}
		if (GetNumOfCards() == 1) {
			return EG_MAUTHAU;
		}
		Reset();
		for (j = 4; j >= 0; j--)
			Value.push_back(Cards.at(j)->GetNumber());
		return EG_MAUTHAU;
	}

	 bool MaubinhGroupCardLogic::ThungPhaSanh() {
		// Convert code Binh
		// Check THUNG PHA SANH gom 5 la bai lien tiep cung chat
		// ----------------------------------------------
		bool bai[4][15]; // bai[i][j] trong bai co quan j
											// chat ihay khong?
		int i = 0;
		int j = 0;
		for (i = 0; i < 4; i++) {
		
			for (j = 0; j < 15; j++)
				bai[i][j] = false;
		}
		for (i = 0; i < GetNumOfCards(); ++i) {
			bai[Cards.at(i)->GetSuit() - 1][Cards.at(i)->GetNumber()] = true;
			if (Cards.at(i)->GetNumber() == 14) // 'A'
				bai[Cards.at(i)->GetSuit() - 1][1] = true;
		}

		bool found = false;
		for (i = 0; i < 4 && !found; ++i) {
			j = 1;
			while (!found && j <= 10) {
				if (bai[i][j]) {
					int k = j + 1;
					// while (k <= j+4 && bai[i][(k-1)%13+1]) k++;
					while (k <= j + 4 && bai[i][k])
						k++;
					k--;
					if (k >= j + 4)
						found = true;
					j = k + 1;
				} else
					j++;
			}
		}
		return found;
		// return (Thung() && Sanh());
	}

	 bool MaubinhGroupCardLogic::ThungPhaSanhThuong() {
		 
		 if (!ThungPhaSanh())
			 return false;
		 bool isAt = false;
		 bool isK = false;

		 for (int i = 0; i < GetNumOfCards(); ++i) {
			 
			 if (Cards.at(i)->GetNumber() == 14) // 'A'
				 isAt = true;
			 else if (Cards.at(i)->GetNumber() == 13) // 'A'
				 isK = true;
		 }

		 return isAt && isK;
	 }

	 bool MaubinhGroupCardLogic::TuQui() {
		if (GetNumOfCards() < 5)
			return false;
		// Convert code Binh
		int i;
		int val = 0;
		// Kiem tra tu tung quan bai mot voi so quan bai con lai, dem xem co bao
		// nhieu con
		// trong bo bai giong quan bai do
		int k = 0;
		for (i = 0; i < GetNumOfCards(); i++) {
			k = 0;
			for (int j = 0; j < GetNumOfCards(); j++) {
				if (j != i) {
					if (Cards.at(j)->GetNumber() == Cards.at(i)->GetNumber()) {
						k++;
						val = Cards.at(i)->GetNumber();
					}
				}
			}
			if (k == 3) {
				// Doan code nay dung de so sanh cac group cung loai voi nhau
				// Voi tu qui thi se so sanh gia tri tu qui truoc, quan bai them
				// sau
				// Tat nhien la khong the xay ra truong hop 2 tu qui giong nhau
				// nen khong
				// can quan tam den quan bai them
				Reset();
				Value.push_back(val);
				return true;
			}
		}
		return false;
	}

	 bool MaubinhGroupCardLogic::CuLu() {
		if (GetNumOfCards() < 5)
			return false;
		// Convert code Binh
		// Check Cu lu: Gom 3 la bai giong nhau va mot doi giong nhau
		// -------------------------------------------------------------
		bool BoDoi = false;
		bool BoBa = false;
		int i = 0;

		// Sap xep lai Group
		for (i = 0; i < GetNumOfCards() - 1; i++)
			for (int j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {

					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
					
				}
			}
		int k = 0;
		for (i = 0; i < 3; i++) {
			if (Cards.at(i)->GetNumber() == Cards.at(0)->GetNumber())
				k++;
		}
		switch (k) {
		case 2: {
			BoDoi = true;
			break;
		}
		case 3: {
			BoBa = true;
			break;
		}
		}

		int val1 = 0;
		int val2 = 0;
		if (BoDoi) {
			k = 0;
			for (i = 2; i < 5; i++) {
				if (Cards.at(i)->GetNumber() == Cards.at(3)->GetNumber())
					k++;
			}

			if (k == 3) {
				val1 = Cards.at(3)->GetNumber();
				val2 = Cards.at(0)->GetNumber();
				Reset();
				Value.push_back(val1);
				Value.push_back(val2);
				return true;
			}
		}
		if (BoBa) {
			k = 0;
			for (i = 3; i < 5; i++) {
				if (Cards.at(i)->GetNumber() == Cards.at(4)->GetNumber())
					k++;
			}
			if (k == 2) {
				val1 = Cards.at(0)->GetNumber();
				val2 = Cards.at(3)->GetNumber();
				Reset();
				Value.push_back(val1);
				Value.push_back(val2);
				return true;
			}
		}
		return false;
	}

	 bool MaubinhGroupCardLogic::Thung() {
		// Convert code Binh
		int i = 0;
		// Thung gom nam la bai cung chat
		for (i = 0; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetSuit() != Cards.at(0)->GetSuit())
				return false;
		}

		// Voi 5 la bai dong chat thi ta sap xep lai group roi
		// push 5 gia tri nay theo thu tu giam dan vao mang
		// Khi so sanh 2 chi se dung 5 gia tri nay de so sanh
		Reset();
		for (i = GetNumOfCards() - 1; i >= 0; i--) {
			Value.push_back(Cards.at(i)->GetNumber());
		}
		return true;
	}

	 void MaubinhGroupCardLogic::wrap(int index1, int index2)
	 {
		 MaubinhCardLogic* temp = Cards.at(index1);
		 Cards.erase(Cards.begin() + index1);
		 //Cards.swap(
	 }

	 bool MaubinhGroupCardLogic::Sanh() {
		if (Cards.size() < 3)
			return false;
		// Convert code Binh
		// Sanh la mot day bai lien tiep nhau
		int i = 0;
		// Sap xep lai Group
		for (i = 0; i < GetNumOfCards() - 1; i++)
			for (int j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/


					swap(Cards.at(i), Cards.at(j));


				}
			}

		int number = Cards.at(0)->GetNumber();

		if (Cards.at(0)->GetNumber() == 2) {
			bool SanhA = true;
			for (i = 0; i < GetNumOfCards() - 2; i++) {
				if (Cards.at(i)->GetNumber() + 1 != Cards.at(i + 1)->GetNumber())
					SanhA = false;
			}
			if (Cards.at(GetNumOfCards() - 1)->GetNumber() != 14)
				SanhA = false;
			if (SanhA)
				return true;
		}
		// Chay tu dau den cuoi group, neu chi can mot con number khong tien len
		// hoac
		// Suit khac di
		// thi khong phai sequence
		for (i = 1; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetNumber() != number + i)
				return false;

		}
		return true;
	}

	 bool MaubinhGroupCardLogic::XamChi() {
		// Convert code Binh
		// Xam Chi se gom 3 quan bai giong nhau va 2 con con` lai khac nhau
		int i;
		int val = 0;
		// Kiem tra tung quan bai mot voi so quan bai con lai, dem xem co bao
		// nhieu
		// con
		// trong bo bai giong quan bai do
		for (i = 0; i < GetNumOfCards(); i++) {
			int k = 0;
			for (int j = 0; j < GetNumOfCards(); j++) {
				if (j != i)
					if (Cards.at(j)->GetNumber() == Cards.at(i)->GetNumber()) {
						k++;
						val = Cards.at(j)->GetNumber();
					}
			}
			if (k == 2) {
				// Voi Xam chi thi cung chi can so sanh bo 3 la du
				// Vi khong bao gio co 2 bo ba giong nhau
				// Vi the ta chi can luu lai gia tri cua bo ba
				Reset();
				Value.push_back(val);
				return true;
			}
		}
		return false;
	}

	 bool MaubinhGroupCardLogic::HaiDoiKhacNhau() {
		if (GetNumOfCards() < 5)
			return false;
		// Convert code Binh
		vector<int> Doi;
		int i = 0;
		int j = 0;
		int k = 0;

		// Dem so doi co trong 5 la bai
		for (i = 0; i < GetNumOfCards() - 1; i++) {
			for (j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() == Cards.at(j)->GetNumber()) {
					Doi.push_back(Cards.at(i)->GetNumber());
					k++;
				}
			}
		}

		for (i = 0; i < k - 1; i++) {
			if (Doi.at(i) != Doi.at(i + 1)) {
				// Neu 2 doi khac nhau thi se luu lai 3 gia tri
				// Mot la doi co gia tri lon hon
				// Hai la doi co gia tri nho hon
				// Ba la quan le
				Reset();
				int max = 0;
				int min = 0;
				if (Doi.at(i) > Doi.at(i + 1)) {
					Value.push_back(Doi.at(i));
					Value.push_back(Doi.at(i + 1));
				} else {
					Value.push_back(Doi.at(i + 1));
					Value.push_back(Doi.at(i));
				}
				for (j = 0; j < 5; j++) {
					if (Cards.at(j)->GetNumber() != Doi.at(i) && Cards.at(j)->GetNumber() != Doi.at(i + 1))
						Value.push_back(Cards.at(j)->GetNumber());
				}
				return true;
			}
		}
		return false;
	}

	 bool MaubinhGroupCardLogic::MotDoi() {
		// Convert code Binh
		// int [] Doi = new int [];
		vector<int> Doi;
		int i = 0;
		int j = 0;
		int k = 0;

		// Dem so doi co trong 5 la bai
		for (i = 0; i < GetNumOfCards() - 1; i++) {
			for (j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() == Cards.at(j)->GetNumber()) {
					Doi.push_back(Cards.at(i)->GetNumber());

				}
			}
		}

		if (Doi.size() == 1) {
			Reset();
			Value.push_back(Doi.at(0));
			for (j = GetNumOfCards() - 1; j >= 0; j--) {
				if (Cards.at(j)->GetNumber() != Doi.at(0))
					Value.push_back(Cards.at(j)->GetNumber());
			}
			return true;
		}
		return false;
	}

	 bool MaubinhGroupCardLogic::SanhRong() {
		// Convert code Binh
		// Check Sanh Rong gom 13 la bai lien tiep cung chat
		// ----------------------------------------------
		if (GetNumOfCards() != 13)
			return false;

		return Sanh();

	}

	 bool MaubinhGroupCardLogic::CungMau() {
		// Convert code Binh
		// Check Thung Rong gom 13 la bai cung chat
		// ----------------------------------------------
		if (GetNumOfCards() != 13)
			return false;

		for (int i = 0; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetColor() != Cards.at(0)->GetColor())
				return false;
		}
		return true;
	}

	 bool MaubinhGroupCardLogic::MuoiHai() {
		// Convert code Binh
		// Check 12 la bai cung mau` va 1 la khac mau`
		// ----------------------------------------------
		if (GetNumOfCards() != 13)
			return false;
		int k = 0;
		for (int i = 0; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetColor() != Cards.at(0)->GetColor())
				k++;
		}
		if (k == 1 || k == 12)
			return true;

		return false;
	}

	 bool MaubinhGroupCardLogic::SauDoi() {
		/*
		 * //Convert code Binh // Check 12 la bai cung mau` va 1 la khac mau`
		 * //---------------------------------------------- if(GetNumOfCards()
		 * != 13) return false; var i:int = 0; var j:int = 0; var k:int = 0;
		 * 
		 * // Sap xep lai Group for(i = 0; i < GetNumOfCards() - 1; i++) for(j =
		 * i + 1; j < GetNumOfCards(); j++) { if(Cards[i].GetNumber() >
		 * Cards[j].GetNumber()) { var temp:Card = Cards[i]; Cards[i] =
		 * Cards[j]; Cards[j] = temp; } }
		 * 
		 * var Doi:Array = new Array(); // Dem so doi co trong 5 la bai for (i =
		 * 0; i < GetNumOfCards() - 1 ; i++) { if(Cards[i].GetNumber() ==
		 * Cards[i + 1].GetNumber()) { Doi[k] = Cards[i].GetNumber(); k++; } }
		 * 
		 * var SoDoi:int = 1; for(i = 0; i < k - 1; i++) { if(Doi[i] != Doi[i +
		 * 1]) { SoDoi++; } } if(SoDoi == 6) return true; return false;
		 */

		// ----------------------------------------------
		if (GetNumOfCards() != 13)
			return false;
		int i = 0;
		int j = 0;
		int k = 0;

		// Sap xep lai Group
		for (i = 0; i < GetNumOfCards() - 1; i++)
			for (j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
				}
			}

		int Doi[15];
		for (i = 0; i < 15; i++)
			Doi[i] = 0;
		// Dem so doi co trong 5 la bai
		for (i = 0; i < GetNumOfCards(); i++) {
			Doi[Cards.at(i)->GetNumber()]++;
		}

		int SoDoi = 0;
		for (i = 0; i < 15; i++) {
			if (Doi[i] == 4) {
				SoDoi += 2;
			} else if (Doi[i] >= 2) {
				SoDoi++;
			}
		}
		if (SoDoi == 6)
			return true;
		return false;
	}

	 bool MaubinhGroupCardLogic::SauDoi1() {
		// Convert code Binh
		// Check 12 la bai cung mau` va 1 la khac mau`
		// ----------------------------------------------
		if (GetNumOfCards() != 13)
			return false;
		int i = 0;
		int j = 0;
		int k = 0;

		// Sap xep lai Group
		for (i = 0; i < GetNumOfCards() - 1; i++)
			for (j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					
					/*	int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));

				}
			}

		int Doi[15];
		for (i = 0; i < 15; i++)
			Doi[i] = 0;
		// Dem so doi co trong 5 la bai
		for (i = 0; i < GetNumOfCards(); i++) {
			Doi[Cards.at(i)->GetNumber()]++;
		}

		int SoDoi = 0;
		for (i = 0; i < 15; i++) {
			if (Doi[i] == 4) {
				SoDoi += 2;
			} else if (Doi[i] >= 2) {
				SoDoi++;
			}
		}
		if (SoDoi == 6)
			return true;
		return false;
	}

	 bool MaubinhGroupCardLogic::NamDoiThong() {
		// Convert code Binh
		if (GetNumOfCards() != 13)
			return false;
		

		int doi[20];

		int i = 0;
		for (i = 0; i < 20; i++) {
			doi[i] = 0;
		}
		int ID[6];
		for (i = 0; i < 6; i++)
			ID[i] = 0;
		int k = 0;
		int j;
		for (i = 0; i < 13; i++) {
			j = Cards.at(i)->GetNumber();
			doi[j]++;
			if (doi[j] == 2) {
				ID[k++] = j;
			}
		}
		if (k >= 5) {
			for (i = 0; i < 5; i++) {
				for (j = i + 1; j < 6; j++) {
					if (ID[i] < ID[j]) {
						int temp = ID[i];
						ID[i] = ID[j];
						ID[j] = temp;
					}
				}
			}
			int Index = 5;
			for (i = 0; i < 6; i++) {
				if (ID[i] > 0)
					Index = i;
			}
			int ii = 0;
			if (k == 6)
				ii = 1;
			if (ID[ii] - ID[Index] == 4)
				return true;
		}
		return false;
	}

	 bool MaubinhGroupCardLogic::BaSanh() {
		// Convert code Binh
		return false;
	}

	 bool MaubinhGroupCardLogic::BaThung() {
		// Convert code Binh
		return false;
	}

	 bool MaubinhGroupCardLogic::CungChat() {
		// Convert code Binh
		for (int i = 0; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetSuit() != Cards.at(0)->GetSuit())
				return false;
		}
		return true;
	}

	 int MaubinhGroupCardLogic::GetNumber() {
		// COnvert code Binh
		return 0;
	}

	 int MaubinhGroupCardLogic::GetSuit() {
		// Convert code Binh
		return 0;
	}

	 void MaubinhGroupCardLogic::AddCard(MaubinhCardLogic *card) {
		// Convert code Binh
		Cards.push_back(card);
	}

	 void MaubinhGroupCardLogic::RemoveCard(MaubinhCardLogic *card) {
		// Convert code Binh
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->ID == card->ID) {
				if(i = 0)
					Cards.erase(Cards.begin());
				else
				{
					Cards.erase(Cards.begin() + i -1);
				}
				
			}
		}
	}

	 void MaubinhGroupCardLogic::Reset() {
		// Convert code Binh
		Value.clear();
		 
		// Sap xep lai Group
		for (int i = 0; i < GetNumOfCards() - 1; i++)
			for (int j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));

				}
			}
	}

	 int MaubinhGroupCardLogic::GetMaxNumber() {
		// Convert code Binh
		// Sap xep lai Group
		for (int i = 0; i < GetNumOfCards() - 1; i++)
			for (int j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
				}
			}

		if (GetGroupKind() == EG_SANH || GetGroupKind() == EG_THUNGPHASANH) {
			if (Cards.at(0)->GetNumber() == 2)
				if (Cards.at(GetNumOfCards() - 1)->GetNumber() == 14) {
					return Cards.at(GetNumOfCards() - 2)->GetNumber();
				}

		}

		return Cards.at(GetNumOfCards() - 1)->GetNumber();
	}

	 int MaubinhGroupCardLogic::GetMaxID() {
		// Convert code Binh
		// Sap xep lai Group - tang dan
		for (int i = 0; i < GetNumOfCards() - 1; i++)
			for (int j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
				}
			}

		if (GetGroupKind() == EG_SANH) {
			if (Cards.at(0)->GetNumber() == 2) {
				if (Cards.at(GetNumOfCards() - 1)->GetNumber() == 14) {
					return Cards.at(GetNumOfCards() - 2)->ID;
				}
			}

		}

		return Cards.at(GetNumOfCards() - 1)->ID;
	}

	void MaubinhGroupCardLogic::sortPair() {
		// da chac chan co doi
		int i, j;
		MaubinhCardLogic temp;
		// sap xep giam dan
		for (i = 0; i < GetNumOfCards() - 1; i++) {
			for (j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() < Cards.at(j)->GetNumber()) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));

				} else if (Cards.at(i)->GetNumber() == Cards.at(j)->GetNumber()) {
					if (Cards.at(i)->ID < Cards.at(j)->ID) {
						/*int oldId = Cards.at(i)->ID;
						Cards.at(i)->ID = Cards.at(j)->ID;
						Cards.at(j)->ID = oldId;*/

						swap(Cards.at(i), Cards.at(j));
					}
				}
			}
		}
		
		int Doi[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int k = 0;
		vector<int> arr;
		for (i = 0; i < GetNumOfCards(); i++) {
			Doi[Cards.at(i)->GetNumber()]++;
			if (Doi[Cards.at(i)->GetNumber()] == 2) {
				arr.push_back(Cards.at(i)->GetNumber());
				k++;
			}
		}
		if (k > 0) {
			// swap vi tri cac doi len vi tri dau tien
			for (int x = 0; x < k; x++) {
				for (i = x * 2; i < GetNumOfCards(); i++) {
					if (Cards.at(i)->GetNumber() != arr.at(x)) {
						int index = -1;
						for (j = i + 1; j < GetNumOfCards(); j++) {
							if (arr.at(x) == Cards.at(j)->GetNumber()) {
								index = j;
								break;
							}
						}
						if (index != -1) {

							/*int oldId = Cards.at(i)->ID;
							Cards.at(i)->ID = Cards.at(index)->ID;
							Cards.at(index)->ID = oldId;*/


							swap(Cards.at(i), Cards.at(index));

						}
					}
				}
			}
		}
	}

	void MaubinhGroupCardLogic::sortTrio() {
		// da chac chan co 1 trio
		int i, j;
		MaubinhCardLogic temp;
		// sap xep giam dan
		for (i = 0; i < GetNumOfCards() - 1; i++) {
			for (j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() < Cards.at(j)->GetNumber()) {

					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/
					swap(Cards.at(i), Cards.at(j));

				} else if (Cards.at(i)->GetNumber() == Cards.at(j)->GetNumber()) {
					if (Cards.at(i)->GetSuit() < Cards.at(j)->GetSuit()) {
						/*int oldId = Cards.at(i)->ID;
						Cards.at(i)->ID = Cards.at(j)->ID;
						Cards.at(j)->ID = oldId;*/

						swap(Cards.at(i), Cards.at(j));
					}
				}
			}
		}
		// Dem so bo co trong 5 la bai
		int Trio[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int k = 0;
		vector<int> arr;
		for (i = 0; i < GetNumOfCards(); i++) {
			Trio[Cards.at(i)->GetNumber()]++;
			if (Trio[Cards.at(i)->GetNumber()] == 3) {
				arr.push_back(Cards.at(i)->GetNumber());

			}
		}
		if (arr.size() > 0) {
			// swap vi tri cac doi len vi tri dau tien
			for (int x = 0; x < arr.size(); x++) {
				for (i = x * 3; i < GetNumOfCards(); i++) {
					if (Cards.at(i)->GetNumber() != arr.at(x)) {
						int index = -1;
						for (j = i + 1; j < GetNumOfCards(); j++) {
							if (arr.at(x) == Cards.at(j)->GetNumber()) {
								index = j;
								break;
							}
						}
						if (index != -1) {
							/*
							int oldId = Cards.at(i)->ID;
							Cards.at(i)->ID = Cards.at(index)->ID;
							Cards.at(index)->ID = oldId;*/

							swap(Cards.at(i), Cards.at(index));
						}
					}
				}
			}
		}
	}

	 void MaubinhGroupCardLogic::SapXepTruocSoBai2() {
		if (CuLu() || XamChi()) {
			sortTrio();
		} else if (TuQui() || MotDoi() || HaiDoiKhacNhau()) {
			sortPair();
		} else {
			DecreaseSort();
		}
	}

	 void MaubinhGroupCardLogic::IncreaseSort() {
		int len = Cards.size();
		MaubinhCardLogic tmp;
		for (int i = 0; i < len - 1; ++i) {
			for (int j = i + 1; j < len; ++j) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
				} else if (Cards.at(i)->GetNumber() == Cards.at(j)->GetNumber()) {
					if (Cards.at(i)->ID > Cards.at(j)->ID) {
						/*int oldId = Cards.at(i)->ID;
						Cards.at(i)->ID = Cards.at(j)->ID;
						Cards.at(j)->ID = oldId;*/

						swap(Cards.at(i), Cards.at(j));
					}
				}
			}
		}
	}

	 void MaubinhGroupCardLogic::DecreaseSort() {
		int len = Cards.size();
		MaubinhCardLogic tmp;
		for (int i = 0; i < len - 1; ++i) {
			for (int j = i + 1; j < len; ++j) {
				if (Cards.at(i)->GetNumber() < Cards.at(j)->GetNumber()) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/
					swap(Cards.at(i), Cards.at(j));

				} else if (Cards.at(i)->GetNumber() == Cards.at(j)->GetNumber()) {
					if (Cards.at(i)->ID < Cards.at(j)->ID) {
						/*int oldId = Cards.at(i)->ID;
						Cards.at(i)->ID = Cards.at(j)->ID;
						Cards.at(j)->ID = oldId;*/

						swap(Cards.at(i), Cards.at(j));
					}
				}
			}
		}
	}

	 void MaubinhGroupCardLogic::Sort(bool inc) // true sap xep tang dan - false sap xep giam
	// dan
	{

		if (inc)
			sortInc(Cards);
		else
			sortDec(Cards);

	}

	 void MaubinhGroupCardLogic::sortInc(vector<MaubinhCardLogic*> cards)

	{
		int i, j;
		for (i = 0; i < cards.size() - 1; i++) {
			for (j = i + 1; j < cards.size(); j++) {
				MaubinhCardLogic* a = cards.at(i);
				MaubinhCardLogic* b = cards.at(j);
				
				int x = a->GetNumber();
				int y = b->GetNumber();

				if (x > y) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
				} else {
					if (a->GetSuit() > b->GetSuit()) {
						/*int oldId = Cards.at(i)->ID;
						Cards.at(i)->ID = Cards.at(j)->ID;
						Cards.at(j)->ID = oldId;*/

						swap(Cards.at(i), Cards.at(j));
					}
				}
			}
		}
	}

	 void MaubinhGroupCardLogic::sortDec(vector<MaubinhCardLogic*> cards)

	{
		int i, j;
		for (i = 0; i < cards.size() - 1; i++) {
			for (j = i + 1; j < cards.size(); j++) {
				MaubinhCardLogic* a = cards.at(i);
				MaubinhCardLogic* b = cards.at(j);
				
				int x = a->GetNumber();
				int y = b->GetNumber();

				if (x < y) {
					/*int oldId = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = oldId;*/

					swap(Cards.at(i), Cards.at(j));
				} else {
					if (a->GetSuit() < b->GetSuit()) {
						/*int oldId = Cards.at(i)->ID;
						Cards.at(i)->ID = Cards.at(j)->ID;
						Cards.at(j)->ID = oldId;*/

						swap(Cards.at(i), Cards.at(j));
					}
				}
			}
		}
	}

	 bool MaubinhGroupCardLogic::searchCard(MaubinhCardLogic *card) {
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->ID == card->ID) {
				return true;
			}
		}
		return false;
	}

	 void MaubinhGroupCardLogic::AddCardByID(int id) {
		if (id < 0 || id > MAX_CARD)
			return;
		MaubinhCardLogic* c = new MaubinhCardLogic();
		c->ID = id;
		AddCard(c);
	}

	 int MaubinhGroupCardLogic::getNumSuite(int suite) {
		int nCount = 0;
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->GetSuit() == suite)
				++nCount;
		}
		return nCount;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getCardsSameSuite(int suite) {
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		DecreaseSort();
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->GetSuit() == suite) {
				Result->AddCardByID(Cards.at(i)->ID);
			}
		}
		return Result;
	}

	 bool MaubinhGroupCardLogic::isHasThung() {
		for (int i = ES_HEART; i >= ES_SPADE; i--)
			if (getNumSuite(i) >= 5)
				return true;
		return false;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getThung() {
		vector<MaubinhGroupCardLogic*> Result ;
		for (int z = 0; z < 2; z++) // co toi da 2 thung 5 la
		{
			MaubinhGroupCardLogic* g = new MaubinhGroupCardLogic();
			Result.push_back(g);
		}
		int k = 0;
		int maxID = 0;
		int i;
		for (i = ES_HEART; i >= ES_SPADE; i--) {
			if (getNumSuite(i) >= 5) {
				MaubinhGroupCardLogic* gc = getCardsSameSuite(i);
				gc->DecreaseSort();
				if (maxID < gc->Cards.at(0)->ID)
					maxID = gc->Cards.at(0)->ID;
				for (int j = 0; j < gc->GetNumOfCards() && j < 5; j++) {
					Result.at(k)->AddCardByID(gc->Cards.at(j)->ID);
				}
				k++;
			}
		}

		if (k > 0) {
			int max = 0;
			bool same = true;
			for (i = 0; i < Result.at(0)->GetNumOfCards() && k > 1; i++) {
				if (Result.at(0)->Cards.at(i)->GetNumber() < Result.at(1)->Cards.at(i)->GetNumber()) {
					same = false;
					max = 1;
					break;
				} else if (Result.at(0)->Cards.at(i)->GetNumber() > Result.at(1)->Cards.at(i)->GetNumber()) {
					same = false;
					max = 0;
					break;
				}
			}
			if (same && k > 1) {
				MaubinhCardLogic* c = new MaubinhCardLogic();
				c->ID = maxID;
				if (Result.at(0)->searchCard(c))
					max = 0;
				else
					max = 1;
			}
			return Result.at(max);
		}
		return NULL;
	}

	 bool MaubinhGroupCardLogic::isHasSequence() {
		if (Cards.size() < 5)
			return false;
		DecreaseSort();
		for (int i = 0; i < Cards.size(); i++) {
			int k = 0;
			int n = Cards.at(i)->GetNumber();
			for (int j = i + 1; j < Cards.size(); j++)
				if (n == Cards.at(j)->GetNumber() + 1) {
					n = Cards.at(j)->GetNumber();
					++k;
					if (k == 4)
						return true;
				}
		}
		return false;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getSequence() {
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		DecreaseSort();
		for (int i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			int k = 0;
			vector<int> aID;
			aID.push_back(Cards.at(i)->ID);
			for (int j = i + 1; j < Cards.size(); j++)
				if (n == Cards.at(j)->GetNumber() + 1) {
					n = Cards.at(j)->GetNumber();
					aID.push_back(Cards.at(j)->ID);
					++k;
					if (k == 5) {
						for (int z = 0; z < aID.size(); z++) {
							Result->AddCardByID(aID.at(z));
						}
						break;
					}
				}
			if (k == 5)
				break;
		}
		return Result;
	}

	 bool MaubinhGroupCardLogic::isHasPair() {
		if (Cards.size() < 2)
			return false;
		DecreaseSort();
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
			if (Num[n] == 2)
				return true;
		}
		return false;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getPair() {
		DecreaseSort();
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		bool bDoi = false;
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		for (i = 15 - 1; i >= 0; i--) {
			if (Num[i] == 2) {
				int nCard = 0;
				for (int j = 0; j < Cards.size(); j++) {
					if (Cards.at(j)->GetNumber() == i && nCard < 2) {
						Result->AddCardByID(Cards.at(j)->ID);
						nCard++;
					}
				}
				break;
			}
		}
		return Result;
	}

	 bool MaubinhGroupCardLogic::isHasXamChi() {
		if (Cards.size() < 3)
			return false;
		bool bXamChi = false;
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		for (i = 0; i < 15; i++) {
			if (Num[i] == 3)
				bXamChi = true;
		}
		return bXamChi;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getXamChi() {
		DecreaseSort();
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		for (i = 15 - 1; i >= 0; i--) {
			if (Num[i] == 3) {
				for (int j = 0; j < Cards.size(); j++) {
					if (Cards.at(j)->GetNumber() == i)
						Result->AddCardByID(Cards.at(j)->ID);
				}
				break;
			}
		}
		return Result;
	}

	// kiem tra xem co culu hay khong
	 bool MaubinhGroupCardLogic::isHasCulu() {
		if (Cards.size() < 5)
			return false;
		// kiem tra co cu lu hay khong
		DecreaseSort();
		bool bDoi = false;
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}

		bool bXamChi = false;
		int nXamChi = 0;
		for (i = 0; i < 15; i++) {
			if (Num[i] == 3) {
				bXamChi = true;
				nXamChi++;
			}
			if (Num[i] == 2)
				bDoi = true;
		}
		if (bXamChi) {
			if (bDoi)
				return true;
			if (nXamChi > 1)
				return true;
		}
		return false;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getCulu() {
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		DecreaseSort();

		MaubinhGroupCardLogic* XamChi = new MaubinhGroupCardLogic();
		MaubinhGroupCardLogic* Doi = new MaubinhGroupCardLogic();
		int Num[15];
		int i, j;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		int XamChiID = -1;
		for (i = 15 - 1; i >= 0; i--) {
			if (Num[i] == 3) {
				XamChiID = i;
				for (j = 0; j < Cards.size(); j++) {
					if (Cards.at(j)->GetNumber() == i)
						XamChi->AddCardByID(Cards.at(j)->ID);
				}
				break;
			}
		}

		// for (i = Num.length - 1; i >= 0; i--)
		for (i = 0; i < 15; i++) // tim doi nho nhat
		{
			if (Num[i] == 2 && i != XamChiID) {
				int nCard = 0;
				for (j = 0; j < Cards.size(); j++) {
					if (Cards.at(j)->GetNumber() == i && nCard < 2) {
						Doi->AddCardByID(Cards.at(j)->ID);
						++nCard;
					}
				}
				break;
			}
		}

		if (Doi->GetNumOfCards() == 0) {
			// for (i = Num.length - 1; i >= 0; i--)
			for (i = 0; i < 15; i++) // tim doi nho nhat
			{
				if (Num[i] >= 2 && i != XamChiID) {
					int _nCard = 0;
					for (j = 0; j < Cards.size(); j++) {
						if (Cards.at(j)->GetNumber() == i && _nCard < 2) {
							Doi->AddCardByID(Cards.at(j)->ID);
							++_nCard;
						}
					}
					break;
				}
			}
		}

		for (i = 0; i < Doi->GetNumOfCards(); i++) {
			Result->AddCardByID(Doi->Cards.at(i)->ID);
		}
		for (i = 0; i < XamChi->GetNumOfCards(); i++) {
			Result->AddCardByID(XamChi->Cards.at(i)->ID);
		}
		return Result;
	}

	 bool MaubinhGroupCardLogic::is2DoiKhacNhau() {
		if (Cards.size() < 4)
			return false;
		DecreaseSort();
		bool b2Doi = false;
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		int k = 0;
		for (i = 0; i < 15; i++) {
			if (Num[i] == 2)
				k++;
			if (k >= 2)
				b2Doi = true;
		}
		return b2Doi;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::get2DoiKhacNhau() {
		// da chac chan co 2 doi khac nhau
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		if (Cards.size() < 4)
			return Result;
		DecreaseSort();
		bool b2Doi = false;
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		int k = 0;
		for (i = 15 - 1; i >= 0; i--) {
			if (Num[i] == 2) {
				++k;
				for (int z = 0; z < Cards.size(); z++)
					if (Cards.at(z)->GetNumber() == i)
						Result->AddCardByID(Cards.at(z)->ID);
				if (k == 2)
					break;
			}
		}
		return Result;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getFour() {
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		if (Cards.size() < 4)
			return Result;
		DecreaseSort();
		bool bFour = false;
		int Num[15];
		int i;
		for (i = 0; i < 15; i++)
			Num[i] = 0;
		for (i = 0; i < Cards.size(); i++) {
			int n = Cards.at(i)->GetNumber();
			Num[n]++;
		}
		int k = 0;
		for (i = 15 - 1; i >= 0; i--) {
			if (Num[i] == 4) {
				++k;
				for (int z = 0; z < Cards.size(); z++)
					if (Cards.at(z)->GetNumber() == i)
						Result->AddCardByID(Cards.at(z)->ID);
				break;
			}
		}
		return Result;
	}

	 MaubinhGroupCardLogic* MaubinhGroupCardLogic::getMaxCard() {
		MaubinhGroupCardLogic* Result = new MaubinhGroupCardLogic();
		if (Cards.size() < 1)
			return Result;
		Result->AddCardByID(GetMaxID());
		return Result;
	}
