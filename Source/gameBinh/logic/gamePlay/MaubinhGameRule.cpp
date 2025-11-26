#include "MaubinhGameRule.h"


MaubinhGameRule::MaubinhGameRule(void)
{
}


MaubinhGameRule::~MaubinhGameRule(void)
{
}

int MaubinhGameRule::SoSanhChi(MaubinhGroupCardLogic *gc1, MaubinhGroupCardLogic* gc2, bool isTinhAt) {
		// Convert code Binh
		// Neu chi 1 co loai nho hon thi thang (so 0 la thung pha sanh, tot
		// nhat, so 9 la rac, kem nhat)
		if (gc1->GetGroupKind() < gc2->GetGroupKind()) {
			return 1;
		}
		// Neu chi 1 co loai lon hon thi thua, tra ve -1
		if (gc1->GetGroupKind() > gc2->GetGroupKind()) {
			return -1;
		}
		// Neu 2 chi co cung loai
		if (gc1->GetGroupKind() == gc2->GetGroupKind()) {
			switch (gc1->GetGroupKind()) {
			// Neu la sanh thi chi can so sanh quan bai to nhat cua chi
			case EG_THUNGPHASANHTHUONG:
				return -1;
			case EG_THUNGPHASANH:
			case EG_SANH: {
							  int num1 = gc1->GetMaxNumber();
							  int num2 = gc2->GetMaxNumber();
							  if (isTinhAt == false)
							  {
								  if (num1 > num2)
									  return 1;
								  if (num1 <= num2)
									  return -1;

							  }
							  else
							  {
								  if (num1 > num2)
								  {
									  if (num1 == 14)
										return 1;
									  if (num2 == 5)  // sanh ha
										  return -1;
									  return 1;
								  }

								  if (num1 < num2)
								  {
									  if (num2 == 14)
										return -1;
									  if (num1 == 5)
										  return 1;
									  return -1;
								  }
								  if (num1 == num2)
									  return -1;
									  
							  }
				
				break;
			}
				// Cac loai nay se so sanh cac gia tri bai voi nhau
			case EG_TUQUI:
			case EG_CULU:
			case EG_THUNG:
			case EG_SAMCO:
			case EG_THU:
			case EG_DOI:
			case EG_MAUTHAU: {
				for (int i = 0; i < gc1->Value.size(); i++) {
					if (gc1->Value.at(i) > gc2->Value.at(i))
						return 1;
					if (gc1->Value.at(i) < gc2->Value.at(i))
						return -1;
					if (gc1->Value.at(i) == gc2->Value.at(i))
						continue;
				}
				break;
			}
			}
		}
		return 0;
	}

int MaubinhGameRule::getId(int number, int suit)
{
	if (number == 1) {
		return 12 * 4 + (suit - 1);
	}
	else {
		return (number - 2) * 4 + (suit - 1);
	}
}

int MaubinhGameRule::getPair(int arrayNumber[][5], int except)
{
	int state = 0;
	while (state < 4) {
		for (int i = 2; i < 15; i++) {
			if (i != except) {
				int count = 0;
				for (int j = 1; j < 5; j++) {
					if (arrayNumber[i][j] == 1) {
						if (state == 0) {
							// phai khong nam trong thung va sanh
							if (!MaubinhGameRule::inThung(arrayNumber, j, except) && !MaubinhGameRule::inSanh(arrayNumber, i, except)) {
								count++;
							}
						}
						else if (state == 1) {
							// phai khong nam trong thung
							if (!MaubinhGameRule::inThung(arrayNumber, j, except)) {
								count++;
							}
						}
						else if (state == 2) {
							// phai khong nam trong sanh
							if (!MaubinhGameRule::inSanh(arrayNumber, i, except)) {
								count++;
							}
						}
						else {
							count++;
						}
					}
				}
				if (count == 2) {
					return i;
				}
			}
		}
		state++;
	}
	return getThree(arrayNumber, except);
}

int MaubinhGameRule::getThree(int arrayNumber[][5], int except)
{
	for (int i = 2; i < 15; i++) {
		if (i != except) {
			int count = 0;
			for (int j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					count++;
				}
			}
			if (count == 3) {
				return i;
			}
		}
	}
	return -1;
}

Vec2 MaubinhGameRule::getMauThau(int arrayNumber[][5])
{
	int temp = -1;
	int state = 0;
	while (state < 5) {
		for (int i = 2; i < 15; i++) {
			int count = 0;
			int suit;
			
			if (state == 0) {
				// phai khong nam trong thung, sanh va count = 1
				for (int j = 1; j < 5; j++) {
					if (arrayNumber[i][j] == 1) {
						count++;
						suit = j;
					}
				}
				if (count == 1 && !MaubinhGameRule::inSanh(arrayNumber, i) && !MaubinhGameRule::inThung(arrayNumber, suit)) {
					return Vec2(i, suit);
				}
			}
			else if (state == 1) {
				// phai khong nam trong thung va sanh
				for (int j = 1; j < 5; j++) {
					if (arrayNumber[i][j] == 1) {
						if (!MaubinhGameRule::inSanh(arrayNumber, i) && !MaubinhGameRule::inThung(arrayNumber, j)) {
							return Vec2(i, j);
						}
					}
				}
			}
			else if (state == 2) {
				// phai khong nam trong thung
				for (int j = 1; j < 5; j++) {
					if (arrayNumber[i][j] == 1) {
						if (!MaubinhGameRule::inThung(arrayNumber, j)) {
							return Vec2(i, j);
						}
					}
				}
			}
			else if (state == 3) {
				// phai khong nam trong sanh
				for (int j = 1; j < 5; j++) {
					if (arrayNumber[i][j] == 1) {
						if (!MaubinhGameRule::inSanh(arrayNumber, i)) {
							return Vec2(i, j);
						}
					}
				}
			}
			else {
				// cay bat ki nho nhat
				for (int j = 1; j < 5; j++) {
					if (arrayNumber[i][j] == 1) {
						return Vec2(i, j);
					}
				}
			}
		}
		state++;
	}
	
	return Vec2(0, 0);
}

int MaubinhGameRule::getNumber(int cardId)
{
	return cardId / 4 + 2;
}

bool MaubinhGameRule::inSanh(int arrayNumber[][5], int number, int except)
{
	int count = 1;
	for (int i = number + 1; i < 15; i++) {
		if (i != except) {
			int j;
			for (j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					break;
				}
			}
			if (j < 5) {
				count++;
			}
			else {
				break;
			}
		}
	}
	for (int i = number - 1; i > 0; i--) {
		if (i != except) {
			int j;
			for (j = 1; j < 5; j++) {
				if (arrayNumber[i][j] == 1) {
					break;
				}
			}
			if (j < 5) {
				count++;
			}
			else {
				break;
			}
		}
	}
	if (count >= 5)
		return true;
	return false;
}

bool MaubinhGameRule::inXam(int arrayNumber[][5], int number)
{
	int count = 0;
	for (int i = 1; i < 5; i++) {
		if (arrayNumber[number][i] == 1)
			count++;
	}
	if (count == 3)
		return true;
	return false;
}

bool MaubinhGameRule::inPair(int arrayNumber[][5], int number)
{
	int count = 0;
	for (int i = 1; i < 5; i++) {
		if (arrayNumber[number][i] == 1)
			count++;
	}
	if (count == 2)
		return true;
	return false;
}

bool MaubinhGameRule::inThung(int arrayNumber[][5], int suit, int except)
{
	int count = 0;
	for (int i = 2; i < 15; i++) {
		if (i != except && arrayNumber[i][suit] == 1) {
			count++;
		}
	}
	if (count == 5)
		return true;
	return false;
}

void MaubinhGameRule::checkAt(int arrayNumber[][5], int arraySuit[][15], int number, int suit)
{
	if (number == 14 || number == 1) {
		arraySuit[suit][14] = -1;
		arrayNumber[14][suit] = -1;
		arraySuit[suit][1] = -1;
		arrayNumber[1][suit] = -1;
	}
}

// SO SANH 2 BAI VOI NHAU - TRA VE TIEN VA DIEM CUA 2 BAI TUONG UNG
	// --------------------------------------------------------------------------------
	// Neu 2 bai cung mau binh thi se duoc cong diem tuong ung va khong duoc
	// cong tien
	// SANH RONG: +45 diem
	// 13 Cu`ng Ma`u: +35 diem
	// 12 Cung` Mau`: +35 diem
	// Sau Doi: +25 diem
	// 3 Sanh: +25 diem
	// 3 thung: +19 diem
	// --------------------------------------------------------------------------------
	// Neu mot bai mau binh, mot bai thuong hoac binh lung thi bai mau binh duoc
	// cong
	// gap doi tien cuoc. Diem tinh nhu tren. Bai thua se mat gap doi tien cuoc
	// va mat
	// 3 diem
	// --------------------------------------------------------------------------------
	// Neu 2 bai thuong thi se so sanh tung chi mot voi nhau.
	// - Chi thua se -1 diem
	// - Chi thang se +1 diem
	// - Hoa khong duoc diem
	// Ngoai le:
	// - Thung pha sanh cuoi +5
	// - Tu qui cuoi +4
	// - Thung pha sanh giua +10
	// - Tu qui giua +8
	// - Cu lu giua +2
	// - Xam chi dau +3
	// --------------------------------------------------------------------------------
	// Mot bai thuong mot bai binh lung thi bai thuong thang +3, bai binh lung
	// thua -3

	// SSoSanhBai la struct gom diem1 va diem2 cho 2 nguoi choi
	// Money khong phai tien that ma la rate de * voi tien cuoc
	// Vi du money = 2 tuc la dung con so nay de gap doi tien cuoc
	MaubinhSoSanhBai* MaubinhGameRule::soSanhBai(MaubinhPlayerCard* pc1, MaubinhPlayerCard* pc2) {
		MaubinhSoSanhBai *s = new MaubinhSoSanhBai();
		int diem1 = 0;
		int diem2 = 0;

		int exp1 = 0;
		int exp2 = 0;

		// Tinh diem neu mot trong 2 bai la mau binh
		switch (pc1->GetPlayerCardsKind()) {
		case EM_SANHRONG:
			exp1 = 45;
			break;

		/*
		 * case PlayerCard.EM_12CUNGMAU: case PlayerCard.EM_13CUNGMAU: { exp1 =
		 * 35; break; }
		 */
		case EM_LUCPHEBON:
		case EM_3SANH: {
			exp1 = 25;
			break;
		}
		case EM_3THUNG: {
			exp1 = 19;
			break;
		}
			/*
			 * case PlayerCard.EM_TUQUI: { exp1 = 5; break; } case
			 * PlayerCard.EM_THUNGPHASANH: { exp1 = 10; break; } case
			 * PlayerCard.EM_NAMDOITHONG: { exp1 = 20; break; }
			 */

		}

		switch (pc2->GetPlayerCardsKind()) {
		case EM_SANHRONG: {
			exp1 = 45;
			break;
		}
			/*
			 * case PlayerCard.EM_12CUNGMAU: case PlayerCard.EM_13CUNGMAU: {
			 * exp1 = 35; break; }
			 */
		case EM_LUCPHEBON:
		case EM_3SANH: {
			exp1 = 25;
			break;
		}
		case EM_3THUNG: {
			exp1 = 19;
			break;
		}
			/*
			 * case PlayerCard.EM_TUQUI: { exp1 = 5; break; } case
			 * PlayerCard.EM_THUNGPHASANH: { exp1 = 10; break; } case
			 * PlayerCard.EM_NAMDOITHONG: { exp1 = 20; break; }
			 */

		}

		bool maubinh1 = (pc1->GetPlayerCardsKind() != EM_NORMAL && pc1->GetPlayerCardsKind() != EM_BINHLUNG);
		bool maubinh2 = (pc2->GetPlayerCardsKind() != EM_NORMAL && pc2->GetPlayerCardsKind() != EM_BINHLUNG);

		// CA HAI CUNG MAU BINH thi se hoa, khong ai an tien cua ai ca
		// -----------------------------------------------------------
		if (maubinh1 && maubinh2) {
			s->exp1 = exp1;
			s->exp2 = exp2;
			s->diem1 = 0;
			s->diem2 = 0;
			s->money1 = 0;
			s->money2 = 0;
			return s;
		}

		// NGUOI 1 MAU BINH, nguoi 2 khong
		// -----------------------------------------------------------
		if ((maubinh1 && maubinh2 == false)) {
			s->exp1 = exp1;
			s->exp2 = 0;
			s->diem1 = 3;
			s->diem2 = -3;
			s->money1 = 3;
			s->money2 = -3;
			return s;
		}

		// NGUOI 1 KHONG MAU BINH, nguoi 2 mau binh
		// -----------------------------------------------------------
		if ((maubinh1 == false && maubinh2)) {
			s->exp1 = 0;
			s->exp2 = exp2;
			s->diem1 = -3;
			s->diem2 = 3;
			s->money1 = -3;
			s->money2 = 3;
			return s;
		}

		// 2 NGUOI CO BAI BINH THUONG thi so sanh 3 chi voi nhau
		// -----------------------------------------------------------
		if (pc1->GetPlayerCardsKind() == EM_NORMAL && pc2->GetPlayerCardsKind() == EM_NORMAL) {
			// So sanh chi dau
			int kq = SoSanhChi(pc1->ChiDau, pc2->ChiDau);
			switch (kq) {
			case 1: {
				diem1++;
				break;
			}
			case -1: {
				diem2++;
				break;
			}
			case 0: {
				break;
			}
			}

			// So sanh chi giua
			kq = SoSanhChi(pc1->ChiGiua, pc2->ChiGiua);
			switch (kq) {
			case 1: {
				diem1++;
				break;
			}
			case -1: {
				diem2++;
				break;
			}
			case 0: {
				break;
			}
			}

			// So sanh chi cuoi
			kq = SoSanhChi(pc1->ChiCuoi, pc2->ChiCuoi);
			switch (kq) {
			case 1: {
				diem1++;
				break;
			}
			case -1: {
				diem2++;
				break;
			}
			case 0: {
				break;
			}
			}

			// Tinh tien va diem cho 2 nguoi
			if (diem1 > diem2) {
				s->exp1 = diem1 - diem2;
				s->exp2 = 0;
				s->money1 = diem1 - diem2;
				s->money2 = diem2 - diem1;
			}

			if (diem1 < diem2) {
				s->exp1 = 0;
				s->exp2 = diem2 - diem1;
				s->money1 = diem1 - diem2;
				s->money2 = diem2 - diem1;
			}
			if (diem1 == diem2) {
				s->exp1 = 0;
				s->exp2 = 0;
				s->money1 = 0;
				s->money2 = 0;
			}
			s->diem1 = diem1 - diem2;
			s->diem2 = diem2 - diem1;
			return s;
		}

		// NGUOI 1 BINH THUONG, 2 BINH LUNG
		// -----------------------------------------------------------
		if (pc1->GetPlayerCardsKind() == EM_NORMAL && pc2->GetPlayerCardsKind() == EM_BINHLUNG) {
			s->diem1 = +3;
			s->diem2 = -3;
			s->money1 = 3;
			s->money2 = -3;
			s->exp1 = 3;
			s->exp2 = 0;
			return s;
		}
		// NGUOI 1 BINH LUNG, 2 BINH THUONG
		// -----------------------------------------------------------
		if (pc1->GetPlayerCardsKind() == EM_BINHLUNG && pc2->GetPlayerCardsKind() == EM_NORMAL) {
			s->diem1 = -3;
			s->diem2 = +3;
			s->money1 = -3;
			s->money2 = +3;
			s->exp1 = 0;
			s->exp2 = 3;
			return s;
		}

		// CA HAI CUNG BINH LUNG thi se hoa, khong ai an tien cua ai ca
		// -----------------------------------------------------------
		if (pc1->GetPlayerCardsKind() == EM_BINHLUNG && pc2->GetPlayerCardsKind() == EM_BINHLUNG) {
			s->exp1 = 0;
			s->exp2 = 0;
			s->diem1 = 0;
			s->diem2 = 0;
			s->money1 = 0;
			s->money2 = 0;
			return s;
		}
		return new MaubinhSoSanhBai();
	}