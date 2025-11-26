#include "TienlenPlayerCard.h"
#include "TienlenGameLogic.h"
#include "TienlenRule.h"
#include "TienlenGamePlayer.h"
#include "../GameLogic.h"


TienlenPlayerCard::TienlenPlayerCard(void)
{
}


TienlenPlayerCard::~TienlenPlayerCard(void)
{
}

vector<char> TienlenPlayerCard::getListIdCardByChar() {
	vector<char> arrIdCard;

	int index = 0;
	for (int i = 0; i < GroupCards.size(); i++) {
		vector<TienlenCard*> cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < cards.size(); j++) {
			arrIdCard.push_back(cards.at(j)->ID);
		}
	}
	return arrIdCard;
}


vector<int> TienlenPlayerCard::getListIdCard() {
	vector<int> arrIdCard;

	int index = 0;
	for (int i = 0; i < GroupCards.size(); i++) {
		vector<TienlenCard*> cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < cards.size(); j++) {
			arrIdCard.push_back(cards.at(j)->ID);
		}
	}
	return arrIdCard;
}

int TienlenPlayerCard::GetNumOfGroupCards() {
	return GroupCards.size();
}

bool TienlenPlayerCard::Has3Spade() {
	if (GetNumOfGroupCards() == 0)
		return false;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->ID == 0)
				return true;
		}
	}
	return false;
}

void TienlenPlayerCard::AddGroupCard(TienlenGroupCard* GCard) {
	GroupCards.push_back(GCard);
}

void TienlenPlayerCard::SetCard(vector <int> id) {
	for (int i = 0; i < GroupCards.size(); i++) {
		delete GroupCards.at(i);
	}
	GroupCards.clear();
	
	for (int i = 0; i < id.size(); i++) {
		TienlenGroupCard* groupCard = new TienlenGroupCard();
		vector<int> array1;
		array1.push_back(id.at(i));
		groupCard->setCard(array1);
		GroupCards.push_back(groupCard);
	}
	TienlenGameLogic::ScanGroupCard(this, AM_NORMAL);
}

void TienlenPlayerCard::removeCard(int id)
{

}

void TienlenPlayerCard::RemoveGroupCard(TienlenGroupCard* GCard) {
	int i;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			for (int k = 0; k < GCard->GetNumOfCards(); k++) {
				if (GroupCards.at(i)->Cards.at(j)->ID == GCard->Cards.at(k)->ID) {
					GroupCards.at(i)->Cards.clear();
				}
			}
		}
	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		if (GroupCards.at(i)->GetNumOfCards() == 0) {
			if(i > 0)
				GroupCards.erase(GroupCards.begin() + i);
			else
				GroupCards.erase(GroupCards.begin());
		}
	}
}

// Ham nay search card trong bo bai va tra ve vi tri cua card do neu tim
// thay
// hoac tra ve -1 neu khong tim thay
int TienlenPlayerCard::SearchCard(TienlenCard* Card) {
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->ID == Card->ID) {
				return i;
			}
		}
	}
	return -1;
}

/**
* Lay card theo id
* 
* @param id
* @return
*/
TienlenCard* TienlenPlayerCard::GetCard(int id) {
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

// Chua trien khai ham nay
/*
* public PlayerCard Copy() { PlayerCard c;
* 
* for(int i = 0; i < GetNumOfGroupCards(); i++) { GroupCard gc; for(int j =
* 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
* gc->AddCard(GroupCards.at(i)->Cards.at(j)); } c.AddGroupCard(gc); }
* return c; }
*/

void TienlenPlayerCard::Clear() {
	GroupCards.clear();
}

bool TienlenPlayerCard::Leave2Last() {
	bool alltwo = true;
	if (GetNumOfGroupCards() == 0) {
		alltwo = false;
	}

	int i, j;
	for (i = 0; i < GroupCards.size(); i++)
		for (j = 0; j < GroupCards.at(i)->Cards.size(); j++) {
			int id = GroupCards.at(i)->Cards.at(j)->GetNumber();
			if (GroupCards.at(i)->GetNumber() != 15) {
				return false;
			}
		}

		return alltwo;
}

bool TienlenPlayerCard::HasStraight() {
	int i, j;
	bool check2 = false;
	vector<int> v;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			v.push_back(GroupCards.at(i)->Cards.at(j)->GetNumber());
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() == 15)
				check2 = true;
		}
	}

	vector<int> demCards;
	for (i = 0; i < v.size(); i++) { // Dem so cac quan bai trong bo
		int dem = 1;
		for (j = 0; j < v.size(); j++) {
			if (j != i && (v.at(i) == v.at(j))) {
				++dem;
			}
		}
		demCards.push_back(dem);

	}

	int k = 0;
	for (i = 0; i < demCards.size(); i++) { // s? khï¿½ng lï¿½ s?nh r?ng n?u
		// cï¿½ 2 ?ï¿½i card
		if (check2) { // neu co 2 thi ko duoc co doi
			if (demCards.at(i) >= 2) {
				// Log.println("ko co sanh rong");
				return false;
			}
		} else {
			if (demCards.at(i) > 2) { // neu co 1 card co xa'm co hoac tu
				// quy thi ko the la sanh rong
				return false;
			}
			if (demCards.at(i) == 2)
				k++;
		}
	}
	if (k >= 3) {
		// Log.println("ko co sanh rong");
		return false;
	} else {
		// Log.println("co sanh rong nhe!");
		return true;
	}

}

bool TienlenPlayerCard::HasFour2() {
	int i, j;
	int dem = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() == 15)
				dem++;
		}
	}

	if (dem == 4)
		return true;
	else
		return false;
}

bool TienlenPlayerCard::HasFour3() {
	int i, j;
	int dem = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() == 3)
				dem++;
		}
	}

	if (dem == 4)
		return true;
	else
		return false;
}

// 4 doi thong
bool TienlenPlayerCard::Has4DoiThong() {
	int doi[20];
	int ID[6];
	int countCard = 0;
	int k = 0;
	int v = 0;
	int j = 0;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			countCard++;
		}
	}
	if (countCard < 8)
		return false;

	for (int i = 0; i < 20; i++)
		doi[i] = 0;

	for (int i = 0; i < 6; i++)
		ID[i] = 0;

	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() != 15) {
				int index = GroupCards.at(i)->Cards.at(j)->GetNumber();
				if (index >= 0 && index < 20) {
					doi[index]++;
					if (doi[index] == 2) {
						k++;
						ID[v++] = index;
					}
				}

			}
		}
	}

	if (k >= 4) {
		for (int i = 0; i < 5; i++)
			for (v = i + 1; v < 6; v++)
				if (ID[i] < ID[v]) {
					int temp = ID[i];
					ID[i] = ID[v];
					ID[v] = temp;
				}
				for (int i = 0; i < 3; i++)
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 3] == 3) {

							Value.clear();

							for (j = ID[i]; j >= ID[i + 3]; j--) {

								Value.push_back(j);
							}

							return true;
						}
					}
	}
	return false;
}

// ham tra ve true neu co 3 doi thong
bool TienlenPlayerCard::Has3DoiThong() {
	int doi [20];
	int ID [6]; // t?i ?a cï¿½ 6 ?ï¿½i (13/2)
	int countCard = 0;
	int k = 0;
	int v = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			countCard++;
		}
	}
	if (countCard < 6)
		return false;

	for (i = 0; i < 20; i++)
		doi[i] = 0;

	for (i = 0; i < 6; i++)
		ID[i] = 0;

	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() != 15) {
				int index = GroupCards.at(i)->Cards.at(j)->GetNumber();
				if (index >= 0 && index < 20) {
					doi[index]++;
					if (doi[index] == 2) {
						k++;
						ID[v++] = index;
					}
				}

			}
		}
	}

	if (k >= 3) {
		for (i = 0; i < 5; i++)
			for (v = i + 1; v < 6; v++)
				if (ID[i] < ID[v]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[v];
					ID[v] = temp;
				}

				for (i = 0; i < 4; i++)
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 2] == 2) {
							Value.clear();
							for (j = ID[i]; j >= ID[i + 2]; j--)
								Value.push_back(j);
							return true;
						}
					}
	}
	return false;
}

// 5 doi thong
bool TienlenPlayerCard::HasUltra() {
	int doi[20];
	int ID [6]; // t?i ?a cï¿½ 6 ?ï¿½i (13/2)
	int i, j = 0, k = 0;

	for (i = 0; i < GroupCards.size(); i++) {
		for (j = 0; j < GroupCards.at(i)->Cards.size(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() != 15) // khac
				// quan
					// 2
			{
				int index = GroupCards.at(i)->Cards.at(j)->GetNumber();
				if (index >= 0 && index < 20) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 5) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}
				for (i = 0; i < 2; i++)
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 4] == 4) {

							Value.clear();
							for (j = ID[i]; j >= ID[i + 4]; j--)
								Value.push_back(j);
							return true;
						}
					}
	}
	return false;
}


TienlenGroupCard* TienlenPlayerCard::Has3DoiThong(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	if (LastCards->GetNumOfCards() > 0) {
		if (LastCards->GetNumOfCards() == 1 && LastCards->GetNumber() != 15) // khac
				return NULL;
		if (LastCards->GetNumOfCards() > 1)
			if (LastCards->GetGroupKind() != EG_BIGGER) // khac
				return NULL;
	}
	int doi[20];
	int ID[20]; // t?i ?a có 6 ?ôi (13/2)
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 20; i++)
		doi[i] = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 20) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 3) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}

				vector<TienlenGroupCard*> BaDoiThong;
				int cout = 0;
				for (i = 0; i < 4; i++) // duyet cac doi tu lon den nho
				{
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 2] == 2) // co 3 doi thong
						{
							TienlenGroupCard* DoiThong = new TienlenGroupCard();
							// kiem tra cac quan chon co nam trong bo 3 doi thong
							// nay khong
							bool result = false;
							for (int z = 0; z < ChooseCards->GetNumOfCards(); z++) {
								result = false;
								DoiThong->AddCard(ChooseCards->Cards.at(z)); // them
								
								for (int x = i; x < i + 3; x++) {
									if (ID[x] == ChooseCards->Cards.at(z)->GetNumber()) {
										result = true;
									}
								}
								if (!result) // neu 1 quan chon khong nam trong bo
									// doi thong nay thi dung luon,
										// khong phai bo doi thong nay
								{
									DoiThong->RemoveAllCards(); // xoa tat ca cac doi
									// da them vao
									break;
								}
							}
							if (result) // neu tat ca quan chon nam trong bo doi
								// thong nay
							{
								for (int a = i; a < i + 3; a++) {
									vector<int> group = GetCardNumber(ID[a]); // group
								
									for (int c = 0; c < group.size(); c++) {
										if (DoiThong->CheckDoubleCardID(group.at(c))) // neu
											
																					continue;
										if (LastCards->GetNumOfCards() > 1) // khong
											
										{
											if (LastCards->GetMaxNumber() == ID[a]) // neu
												
											{
												if (LastCards->GetMaxID() > group.at(c) && LastCards->GetMaxID() > DoiThong->GetMaxID()) {
													continue;
												}
											}
										}
										if (DoiThong->GetCountCard(GetCard(group.at(c))->GetNumber()) < 2) {
											DoiThong->AddCard(GetCard(group.at(c)));
										}
									}
								}
								BaDoiThong.push_back(DoiThong); // cac bo doi thong
							}
						}
					}
				}
				if (LastCards->GetNumOfCards() > 0) // neu la danh chan
				{
					int index = -1;
					for (int ii = BaDoiThong.size() - 1; ii >= 0; ii--) {
						int resultInt = TienlenRule::CheckValidCard(LastCards, BaDoiThong.at(ii), PlayerCards);
						if (resultInt == E_NO_ERROR) {
							index = ii;
							break;
						}
					}
					if (index >= 0) {
						for (int ii = BaDoiThong.size() - 1; ii >= 0; ii--) {
							if (ii != index) {
								delete BaDoiThong.at(ii);
							}
						}
						return BaDoiThong.at(index);
					}
				}
				else if (BaDoiThong.size() > 0) {
					for (int ii = BaDoiThong.size() - 2; ii >= 0; ii--) {
						delete BaDoiThong.at(ii);
					}
					return BaDoiThong.at(BaDoiThong.size() - 1); // 3 doi thong nho
				}
				for (int ii = BaDoiThong.size() - 1; ii >= 0; ii--) {
					delete BaDoiThong.at(ii);
				}
				// nhat
	}
	return NULL;
}

// kiem tra tu quy
TienlenGroupCard* TienlenPlayerCard::HasFour(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	if (LastCards->GetNumOfCards() > 0) {
		if ((LastCards->GetNumOfCards() == 1 || LastCards->GetNumOfCards() == 2) && LastCards->GetNumber() != 15)
			return NULL;
		if (LastCards->GetNumOfCards() > 2)
			if (LastCards->GetGroupKind() != EG_BIGGER || LastCards->GetGroupKind() != EG_SUPER)
				return NULL;
	} else if (ChooseCards->GetGroupKind() != EG_NORMAL) // cac
		return NULL;
	vector<int> ID = GetCardNumber(ChooseCards->GetNumber());
	if (ID.size() < 4)
		return NULL;
	else // co tu quy
	{
		TienlenGroupCard* Four = new TienlenGroupCard();
		for (int i = 0; i < ID.size(); i++) {
			Four->AddCard(GetCard(ID.at(i)));
		}
		if (LastCards->GetNumOfCards() > 0) {
			int resultInt = TienlenRule::CheckValidCard(LastCards, Four, PlayerCards);
			if (resultInt == E_NO_ERROR)
				return Four;
			delete Four;
			return NULL;
		} else {
			if (Four->GetNumOfCards() == 4)
				return Four;
			delete Four;
			return NULL;
		}
	}
}

TienlenGroupCard* TienlenPlayerCard::Has4DoiThong(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	if (LastCards->GetNumOfCards() > 0) {
		if ((LastCards->GetNumOfCards() == 1 || LastCards->GetNumOfCards() == 2) && LastCards->GetNumber() != 15) // khac
			// 2,
				// doi
					// 2
						return NULL;
		if (LastCards->GetNumOfCards() > 2) {
			if (LastCards->GetGroupKind() != EG_BIGGER || LastCards->GetGroupKind() != EG_SUPER)
				return NULL;
		}
	}
	int doi[20];
	int ID[20]; // t?i ?a có 6 ?ôi (13/2)
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 20; i++)
		doi[i] = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 20) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 4) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}

				vector<TienlenGroupCard*> BonDoiThong;
				int cout = 0;
				for (i = 0; i < 3; i++) // duyet cac doi tu lon den nho
				{
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 3] == 3) // co 4 doi thong
						{
							TienlenGroupCard* DoiThong = new TienlenGroupCard();
							// kiem tra cac quan chon co nam trong bo 4 doi thong
							// nay khong
							bool result = false;
							for (int z = 0; z < ChooseCards->GetNumOfCards(); z++) {
								result = false;
								DoiThong->AddCard(ChooseCards->Cards.at(z)); // them
								
								for (int x = i; x < i + 4; x++) {
									if (ID[x] == ChooseCards->Cards.at(z)->GetNumber()) {
										result = true;
									}
								}
								if (!result) // neu 1 quan chon khong nam trong bo
									// doi thong nay thi dung luon,
										// khong phai bo doi thong nay
								{
									DoiThong->RemoveAllCards(); // xoa tat ca cac doi
									// da them vao
									break;
								}
							}
							if (result) // neu tat ca quan chon nam trong bo doi
								// thong nay
							{
								for (int a = i; a < i + 4; a++) {
									vector<int> group = GetCardNumber(ID[a]); // group
									
									for (int c = 0; c < group.size(); c++) {
										if (DoiThong->CheckDoubleCardID(group.at(c))) // neu
											continue;
										if (LastCards->GetNumOfCards() > 6) // neu la
										{
											if (LastCards->GetMaxNumber() == ID[a]) // neu
											
											{
												if (LastCards->GetMaxID() > group.at(c) && LastCards->GetMaxID() > DoiThong->GetMaxID())
													continue;
											}
										}
										if (DoiThong->GetCountCard(GetCard(group.at(c))->GetNumber()) < 2) {
											DoiThong->AddCard(GetCard(group.at(c)));
										}
									}
								}
								BonDoiThong.push_back(DoiThong); // cac bo doi thong
							}
						}
					}
				}
				if (LastCards->GetNumOfCards() > 0) // neu la danh chan
				{
					int index = -1;

					for (int ii = BonDoiThong.size() - 1; ii >= 0; ii--) {
						int resultInt = TienlenRule::CheckValidCard(LastCards, BonDoiThong.at(ii), PlayerCards);
						if (resultInt == E_NO_ERROR) {
							index = ii;
							break;
						}
					}
					if (index >= 0) {
						for (int ii = BonDoiThong.size() - 1; ii >= 0; ii--) {
							if (index != ii) {
								delete BonDoiThong.at(ii);
							}
						}
						return BonDoiThong.at(index);
					}
					
				}
				else if (BonDoiThong.size() > 0) {
					for (int ii = BonDoiThong.size() - 2; ii >= 0; ii--) {
						delete BonDoiThong.at(ii);
					}
					return BonDoiThong.at(BonDoiThong.size() - 1); // 4 doi thong
				}
				for (int ii = BonDoiThong.size() - 1; ii >= 0; ii--) {
					delete BonDoiThong.at(ii);
				}
	}
	return NULL;
}

TienlenGroupCard* TienlenPlayerCard::Has5DoiThong(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	if (LastCards->GetNumOfCards() > 0) {
		if ((LastCards->GetNumOfCards() == 1 || LastCards->GetNumOfCards() == 2) && LastCards->GetNumber() != 15) // khac
			return NULL;
		if (LastCards->GetGroupKind() == EG_NORMAL && LastCards->GetNumOfCards() != 4) // khong
			return NULL;
		if (LastCards->GetNumOfCards() >= 6)
			if (LastCards->GetGroupKind() != EG_BIGGER || LastCards->GetGroupKind() != EG_SUPER || LastCards->GetGroupKind() != EG_ULTRA)
				return NULL;
	}
	int doi[20];
	int ID[20]; // t?i ?a có 6 ?ôi (13/2)
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 20; i++)
		doi[i] = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 20) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 5) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}

				vector<TienlenGroupCard*> NamDoiThong;
				int cout = 0;
				for (i = 0; i < 2; i++) // duyet cac doi tu lon den nho
				{
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 4] == 4) // co 5 doi thong
						{
							TienlenGroupCard* DoiThong = new TienlenGroupCard();
							// kiem tra cac quan chon co nam trong bo 5 doi thong
							// nay khong
							bool result = false;
							for (int z = 0; z < ChooseCards->GetNumOfCards(); z++) {
								result = false;
								DoiThong->AddCard(ChooseCards->Cards.at(z)); // them
								
								for (int x = i; x < i + 5; x++) {
									if (ID[x] == ChooseCards->Cards.at(z)->GetNumber()) {
										result = true;
									}
								}
								if (!result) // neu 1 quan chon khong nam trong bo
									// doi thong nay thi dung luon,
										// khong phai bo doi thong nay
								{
									DoiThong->RemoveAllCards(); // xoa tat ca cac doi
									// da them vao
									break;
								}
							}
							if (result) // neu tat ca quan chon nam trong bo doi
								// thong nay
							{
								for (int a = i; a < i + 5; a++) {
									vector<int> group = GetCardNumber(ID[a]); // group
								
									for (int c = 0; c < group.size(); c++) {
										if (DoiThong->CheckDoubleCardID(group.at(c))) // neu
																					continue;
										if (LastCards->GetNumOfCards() > 8) // neu la
											
										{
											if (LastCards->GetMaxNumber() == ID[a]) // neu
												
											{
												if (LastCards->GetMaxID() > group.at(c) && LastCards->GetMaxID() > DoiThong->GetMaxID())
													continue;
											}
										}
										if (DoiThong->GetCountCard(GetCard(group.at(c))->GetNumber()) < 2)
											DoiThong->AddCard(GetCard(group.at(c)));
									}
								}
								NamDoiThong.push_back(DoiThong); // cac bo doi thong
							}
						}
					}
				}
				if (LastCards->GetNumOfCards() > 0) // neu la danh chan
				{
					int index = -1;
					for (int ii = NamDoiThong.size() - 1; ii >= 0; ii--) {
						int resultInt = TienlenRule::CheckValidCard(LastCards, NamDoiThong.at(ii), PlayerCards);
						if (resultInt == E_NO_ERROR) {
							index = ii;
							break;
						}
					}
					if (index >= 0) {
						for (int ii = NamDoiThong.size() - 1; ii >= 0; ii--) {
							if (index != ii) {
								delete NamDoiThong.at(ii);
							}
						}
						return NamDoiThong.at(index);
					}
					
				}
				else if (NamDoiThong.size() > 0) {
					for (int ii = NamDoiThong.size() - 2; ii >= 0; ii--) {
						delete NamDoiThong.at(ii);
					}
					return NamDoiThong.at(NamDoiThong.size() - 1); // 4 doi thong
				}
				for (int ii = NamDoiThong.size() - 1; ii >= 0; ii--) {
					delete NamDoiThong.at(ii);
				}
	}
	return NULL;
}

bool TienlenPlayerCard::CardInFour(int number) {
	vector<int> ID = GetCardNumber(number);
	if (ID.size() == 4)
		return true;
	return false;
}

bool TienlenPlayerCard::CardIn3Pair(int number) {
	int* ID = ArrayPair(); // mang cac doi sap xep giam dan
	
	if (ID == NULL)
		return false;
	if (sizeof(ID) / sizeof(ID[0]) >= 3) {
		for (int i = 0; i < 4; i++) // duyet cac doi tu lon den nho
		{
			if (ID[i] > 0) {
				if (ID[i] - ID[i + 2] == 2) // co 3 doi thong
				{
					if (ID[i] >= number && number >= ID[i + 2])
						return true;
				}
			}
		}
	}
	return false;
}

bool TienlenPlayerCard::CardIn4Pair(int number) {
	int* ID = ArrayPair(); // mang cac doi sap xep giam dan
	if (ID == NULL)
		return false;
	if (sizeof(ID) / sizeof(ID[0]) >= 4) {
		for (int i = 0; i < 3; i++) // duyet cac doi tu lon den nho
		{
			if (ID[i] > 0) {
				if (ID[i + 3] - ID[i] == 3) // co 3 doi thong
				{
					if (ID[i + 3] >= number && number >= ID[i]) // number
						// nam trong
							// 3 doi
								// thong
									return true;
				}
			}
		}
	}
	return false;
}

bool TienlenPlayerCard::CardIn5Pair(int number) {
	int* ID = ArrayPair(); // mang cac doi sap xep giam dan
	if (ID == NULL)
		return false;
	if (sizeof(ID) / sizeof(ID[0]) >= 5) {
		for (int i = 0; i < 2; i++) // duyet cac doi tu lon den nho
		{
			if (ID[i] > 0) {
				if (ID[i] - ID[i + 4] == 4) // co 3 doi thong
				{
					if (ID[i] >= number && number >= ID[i + 4])
						return true;
				}
			}
		}
	}
	return false;
}

int* TienlenPlayerCard::ArrayPair() {
	int doi[16];
	int ID[16]; // t?i ?a có 6 ?ôi (13/2)
	for (int i = 0; i < 16; i++)
		doi[i] = 0;
	int l = 0;
	int k = 0;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 16) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[l++] = index;
					}
				}
			}
		}
	}
	if (k > 0) {
		for (int i = 0; i < 16 - 1; i++)
			for (int j = i + 1; j < 16; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}
				return ID;
	}
	return NULL;
}

// co tu quy?
bool TienlenPlayerCard::HasTuQuy() {
	// if (GroupCards.size() < 4)
	// return false;
	int k = 0;
	int tuquy[20];
	int i, j;
	for (i = 0; i < 20; i++)
		tuquy[i] = 0;
	for (i = 0; i < GroupCards.size(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			int iNum = GroupCards.at(i)->Cards.at(j)->GetNumber();
			if (iNum >= 0 && iNum < 20)
				tuquy[iNum]++;
		}
	}
	for (i = 0; i < 20; i++) {
		if (tuquy[i] == 4) {
			return true;
		}
	}
	return false;
}

// 6 doi (tinh ca doi 2 va tu quy tinh la 2 doi)
bool TienlenPlayerCard::HasSixPair() {
	// if (GroupCards.size() < 8)
	// return false;
	int doi[20];
	int i, k = 0, j;

	for (i = 0; i < GroupCards.size(); i++) {
		for (j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			int index = GroupCards.at(i)->Cards.at(j)->GetNumber();
			if (index >= 0 && index < 20) {
				doi[index]++;
				if (doi[index] % 2 == 0) // doi
				{
					k++;
				}
			}
		}
	}
	if (k >= 6) {
		return true;
	}
	return false;
}

// ham lay ve ket qua thoi 2
double TienlenPlayerCard::GetHas2Fail() {
	if (GroupCards.size() == 0)
		return 0;
	double Sum = 0;
	// 2 bich, tep = 0.5
	// 2 ro, co = 1.0
	for (int i = 0; i < GroupCards.size(); i++) {
		vector<TienlenCard*> Cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < Cards.size(); j++) {
			if (Cards.at(j)->GetNumber() == 15) {
				switch (Cards.at(j)->GetSuit()) {
				case 1:
				case 2:
					Sum += 0.5;
					break;
				case 3:
				case 4:
					Sum += 1.0;
					break;
				}
			}
		}
	}
	return Sum;
}

/*
* ham kiem tra co trung lap quan bai khong
*/
bool TienlenPlayerCard::CheckDoubleCard(int id) {
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->ID == id) {
				return true;
			}
		}
	}
	return false;
}

/*
* lay ve tat ca quan bai co Number = ID
*/
vector<int> TienlenPlayerCard::GetCardNumber(int number) {
	vector<int> GroupSameNumber;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			if (GroupCards.at(i)->Cards.at(j)->GetNumber() == number) {
				GroupSameNumber.push_back(GroupCards.at(i)->Cards.at(j)->ID);
			}
		}
	}
	int size = GroupSameNumber.size() - 1;
	for (int i = 0; i < size; i++) {
		for (int j = i; j < GroupSameNumber.size(); j++)
			if (GroupSameNumber.at(i) > GroupSameNumber.at(j)) // sap xep
				// lon
					// dan
			{
				swap(GroupSameNumber.at(i), GroupSameNumber.at(j));
			}
	}
	return GroupSameNumber;
	// vector chua ID quan bai co cung number
}

TienlenGroupCard* TienlenPlayerCard::HasSequence(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	bool kt = false;
	if (LastCards->GetNumOfCards() > 0) {
		if (LastCards->GetGroupKind() != EG_SEQUENCE)
			return NULL;
	}

	// phai sap xep thanh GroupCard theo thu tu tang dan
	vector<TienlenCard*> TempCards;

	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = i; j < GroupCards.at(i)->Cards.size(); j++) {
			TempCards.push_back(GroupCards.at(i)->Cards.at(j));
		}
	}
	// sap xep tang dan
	TempCards = TienlenGameLogic::sortCards(TempCards, true);
	// sap xep tang dan
	// for(int i = 0; i <TempCards.size();i++){
	// for (int j=i;j<TempCards.size();j++)
	// {
	// if(TempCards.at(j).compare(TempCards.at(i))<0){
	// TienlenCard tmp = TempCards.at(j);
	// TempCards.set(j,TempCards.at(i));
	// TempCards.set(i,tmp);
	// }
	// }
	// }

	if (LastCards->GetNumOfCards() == 0 && ChooseCards->GetNumOfCards() == 2) // la
		// nguoi
			// danh
	{
		TienlenGroupCard* ChooseCardsReturn = new TienlenGroupCard();
		ChooseCardsReturn->AddCard(ChooseCards->Cards.at(0));
		if (ChooseCards->Cards.at(1)->GetNumber() - ChooseCards->Cards.at(0)->GetNumber() == 1) {
			ChooseCardsReturn->AddCard(ChooseCards->Cards.at(1)); // add card
		
			kt = true;
		} else if ((ChooseCards->Cards.at(1)->GetNumber() - ChooseCards->Cards.at(0)->GetNumber()) > 1) {
			for (int i = 0; i < TempCards.size(); i++) {
				if (TempCards.at(i)->GetNumber() != 15) {
					if (TempCards.at(i)->GetNumber() == ChooseCardsReturn->Cards.at(ChooseCardsReturn->Cards.size() - 1)->GetNumber() + 1) {
						ChooseCardsReturn->AddCard(TempCards.at(i));
					}
					if (ChooseCardsReturn->Cards.at(ChooseCardsReturn->Cards.size() - 1)->GetNumber() == ChooseCards->Cards.at(1)->GetNumber()) {
						ChooseCardsReturn->Cards.pop_back();
						ChooseCardsReturn->Cards.push_back(ChooseCards->Cards.at(1));
						kt = true;
						break;
					}
				}
			}
		}

		if (kt) {
			for (int i = 0; i < TempCards.size(); i++) {
				if (TempCards.at(i)->GetNumber() != 15) {
					if (TempCards.at(i)->GetNumber() == ChooseCardsReturn->Cards.at(ChooseCardsReturn->Cards.size() - 1)->GetNumber() + 1) {
						ChooseCardsReturn->AddCard(TempCards.at(i));
					}
				}
			}
			for (int i = TempCards.size() - 1; i >= 0; i--) {
				if (TempCards.at(i)->GetNumber() == ChooseCardsReturn->Cards.at(0)->GetNumber() && TempCards.at(i)->GetNumber() < ChooseCards->Cards.at(0)->GetNumber()) {
					if (TempCards.at(i)->ID < ChooseCardsReturn->Cards.at(0)->ID) {
						ChooseCardsReturn->Cards.erase(ChooseCardsReturn->Cards.begin());
						ChooseCardsReturn->Cards.insert(ChooseCardsReturn->Cards.begin(), TempCards.at(i));
					}
				} else if (TempCards.at(i)->GetNumber() == ChooseCardsReturn->Cards.at(0)->GetNumber() - 1) {
					ChooseCardsReturn->Cards.insert(ChooseCardsReturn->Cards.begin(), TempCards.at(i));
					
				}
			}
			for (int i = TempCards.size() - 1; i >= 0; i--) {
				if (TempCards.at(i)->GetNumber() == ChooseCardsReturn->Cards.at(ChooseCardsReturn->Cards.size() - 1)->GetNumber() && TempCards.at(i)->GetNumber() > ChooseCards->Cards.at(1)->GetNumber()) {
					if (TempCards.at(i)->ID > ChooseCardsReturn->Cards.at(ChooseCardsReturn->Cards.size() - 1)->ID)
					{
						ChooseCardsReturn->Cards.pop_back();
						ChooseCardsReturn->Cards.push_back(TempCards.at(i));
					}
				}
			}

		}
		// int myID =
		// ModuleMgr.getInstance().doFunction(ModuleMgr.USER_GET_MY_CHAIR);
		int resultInt = TienlenRule::CheckValidCard(LastCards, ChooseCardsReturn, PlayerCards);
		if (resultInt == E_NO_ERROR && ChooseCardsReturn->searchCard(ChooseCards->Cards.at(1)))
			return ChooseCardsReturn;
		else {
			//delete ChooseCardsReturn;
			return NULL;
		}
	} else
		return NULL;
}

TienlenGroupCard* TienlenPlayerCard::AutoSequence(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	TienlenGroupCard* group = HasSequence(LastCards, ChooseCards, PlayerCards); // sanh
	// da
	// duoc
	// sap
	// xep
	// tang
	// dan
	TienlenGroupCard* gc = new TienlenGroupCard();
	if (group != NULL) {
		group->Sort(true);
		for (int i = 0; i < group->GetNumOfCards(); i++) {
			int num = group->Cards.at(i)->GetNumber();
			int length = GetCardNumber(num).size();
			bool result = (CardInFour(num) || ((CardIn3Pair(num) || CardIn4Pair(num) || CardIn5Pair(num)) && length == 2)) && (!ChooseCards->CheckDoubleCardNumber(num));
			if (result == false)
				gc->AddCard(group->Cards.at(i));
			else if (gc->GetGroupKind() == EG_SEQUENCE) {
				bool b = false;
				for (int j = 0; j < ChooseCards->GetNumOfCards(); j++)
					if (gc->GetMinNumber() > ChooseCards->Cards.at(j)->GetNumber() || gc->GetMaxNumber() < ChooseCards->Cards.at(j)->GetNumber())
						b = true;
				if (b == false) // neu gc co chua quan bai da chon
					return gc;
				else
					gc->RemoveAllCards();
			}
		}
		if (gc->GetGroupKind() == EG_SEQUENCE)
			return gc;
		// kiem tra neu 2 quan chon nam trong 3,4,5 doi thong, thi tra ve
		// group
		bool bSanh = true;
		for (int i = 0; i < ChooseCards->GetNumOfCards(); i++) {
			int n = ChooseCards->Cards.at(i)->GetNumber();
			if ((CardIn3Pair(n) || CardIn4Pair(n) || CardIn5Pair(n)) == false)
				bSanh = false;
		}
		if (bSanh)
			return group;
	}
	return group;
}

TienlenGroupCard* TienlenPlayerCard::Auto4Pair(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	// trace ("vao ham Auto4Pair");
	TienlenGroupCard* group = Has4DoiThong(LastCards, ChooseCards, PlayerCards);
	if (group != NULL) {
		group->Sort(true); // 4 doi thong da duoc sap xep tang dan
		TienlenGroupCard* gc = new TienlenGroupCard();
		for (int i = 0; i < group->GetNumOfCards(); i++) {
			int num = group->Cards.at(i)->GetNumber();
			int length = GetCardNumber(num).size();
			bool result = ChooseCards->CheckDoubleCardNumber(num);
			if (result == true) {
				// trace ("Auto4Pair ---- them quan bai", num);
				gc->AddCard(group->Cards.at(i));
			} else if (CardInFour(num)) {
				if (num > group->GetMinNumber() && num < group->GetMaxNumber()) // truong
				
				{
					if (num - group->GetMinNumber() == 2 || num - group->GetMinNumber() == 1) // truong
				
																gc->AddCard(group->Cards.at(i));
					else
						return group;
				}
				if (num == group->GetMinNumber() || num == group->GetMaxNumber()) {
					if (gc->GetGroupKind() == EG_BIGGER || gc->GetGroupKind() == EG_SUPER || gc->GetGroupKind() == EG_ULTRA) {
						// trace("Auto4Pair --- den day roi");
						if (gc->GetMinNumber() <= ChooseCards->GetMinNumber() && gc->GetMaxNumber() >= ChooseCards->GetMaxNumber())
							return gc;
						else {
							// trace ("Xoa quan bai o day");
							gc->RemoveAllCards();
						}
					} else if (gc->GetNumOfCards() >= 4) // gc co 2 doi ->
						// lay them 1 doi
						// trong bo tu quy
					{
						// trace ("Auto4Pair +++++ them quan bai", num);
						gc->AddCard(group->Cards.at(i));
					}
				}
			} else {
				// trace ("Auto4Pair ---- them quan bai", num);
				gc->AddCard(group->Cards.at(i));
			}
		}
		if (gc->GetGroupKind() == EG_SUPER || gc->GetGroupKind() == EG_BIGGER || gc->GetGroupKind() == EG_ULTRA)
			if (gc->GetMinNumber() <= ChooseCards->GetMinNumber() && gc->GetMaxNumber() >= ChooseCards->GetMaxNumber())
				return gc;
		// trace ("KIND", gc->GetGroupKind());
		// for (i = 0; i < gc->GetNumOfCards(); i++)
		// trace (gc->GetNumber());
	}
	// trace ("Auto4Pair ---- tra ve NULL");
	return group;
}

TienlenGroupCard* TienlenPlayerCard::Auto5Pair(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	// trace ("vao ham Auto5Pair");
	TienlenGroupCard* group = Has5DoiThong(LastCards, ChooseCards, PlayerCards);
	if (group != NULL) {
		group->Sort(true); // 5 doi thong da duoc sap xep tang dan
		TienlenGroupCard* gc = new TienlenGroupCard();
		int i;
		int j;
		for (i = 0; i < group->GetNumOfCards(); i++) {
			int num = group->Cards.at(i)->GetNumber();
			int length = GetCardNumber(num).size();
			bool result = ChooseCards->CheckDoubleCardNumber(num);
			if (result == true) {
				gc->AddCard(group->Cards.at(i));
			} else if (CardInFour(num)) {
				if (num > group->GetMinNumber() && num < group->GetMaxNumber()) // truong
					
				{
					if (gc->GetGroupKind() == EG_BIGGER || gc->GetGroupKind() == EG_SUPER || gc->GetGroupKind() == EG_ULTRA) {
						if (gc->GetMinNumber() <= ChooseCards->GetMinNumber() && gc->GetMaxNumber() >= ChooseCards->GetMaxNumber()) {
							return gc;
						} else {
							// trace("xoa bai roi");
							gc->RemoveAllCards();
						}
					} else {
						if (num - group->GetMinNumber() == 2) // truong hop
							// tu quy
								// nam giua
									// -> tach
										// thanh 2
											// bo 3 doi
												// thong
						{
							if (num > ChooseCards->GetMaxNumber()) {
								// trace ("Auto5Pair ---- them quan bai",
								// num);
								gc->AddCard(group->Cards.at(i));
								if (gc->GetGroupKind() == EG_BIGGER || gc->GetGroupKind() == EG_SUPER || gc->GetGroupKind() == EG_ULTRA)
									if (gc->GetMinNumber() <= ChooseCards->GetMinNumber() && gc->GetMaxNumber() >= ChooseCards->GetMaxNumber())
										return gc;
							} else {
								if (gc->GetNumOfCards() > 2) // nhieu hon 1
									// doi
										gc->RemoveAllCards(); // xoa het
								gc->AddCard(group->Cards.at(i)); // them quan
								// bai vao
								// gc
							}
						} else {
							// trace("xoa bai");
							gc->RemoveAllCards();
						}
					}
				} else if (num == group->GetMinNumber() || num == group->GetMaxNumber()) {
					if (gc->GetGroupKind() == EG_BIGGER || gc->GetGroupKind() == EG_SUPER || gc->GetGroupKind() == EG_ULTRA) {
						// trace("Auto5Pair --- den day roi");
						if (gc->GetMinNumber() <= ChooseCards->GetMinNumber() && gc->GetMaxNumber() >= ChooseCards->GetMaxNumber())
							return gc;
						else
							gc->RemoveAllCards();
					}
				}
			} else {
				// trace ("Auto5Pair ---- them quan bai", num);
				gc->AddCard(group->Cards.at(i));
			}
		}
		if (gc->GetGroupKind() == EG_SUPER || gc->GetGroupKind() == EG_BIGGER || gc->GetGroupKind() == EG_ULTRA)
			if (gc->GetMinNumber() <= ChooseCards->GetMinNumber() && gc->GetMaxNumber() >= ChooseCards->GetMaxNumber())
				return gc;
	}
	return group;
}

TienlenGroupCard* TienlenPlayerCard::CheckGroup(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	if (LastCards->GetNumOfCards() == 0) {
		if (ChooseCards->GetNumOfCards() < 2)
			return NULL;
	} else if (ChooseCards->GetNumOfCards() < 1)
		return NULL;
	int i;
	TienlenGroupCard* group = new TienlenGroupCard();
	TienlenCard* card;
	// copy ChooseCard
	for (i = 0; i < ChooseCards->GetNumOfCards(); i++) {
		card = new TienlenCard();
		card->ID = ChooseCards->Cards.at(i)->ID;
		group->AddCard(card);
	}
	TienlenGroupCard* groupCard = NULL;
	if (LastCards->GetNumOfCards() == 0) {
		if (group->GetNumOfCards() == 3) // chon 3 quan
		{
			if (group->GetGroupKind() == EG_NORMAL) {
				// trace("kiem tra tu quy");
				groupCard = HasFour(LastCards, group, PlayerCards);
			} else {
				bool result = true;
				if (group->Cards.at(0)->GetNumber() != group->Cards.at(1)->GetNumber() && group->Cards.at(1)->GetNumber() != group->Cards.at(2)->GetNumber() && group->Cards.at(0)->GetNumber() != group->Cards.at(2)->GetNumber())
					result = false;
				if (result) {
					// trace("kiem tra 5 doi thong");
					// groupCard = Has5DoiThong(LastCards, group);
					groupCard = Auto5Pair(LastCards, group, PlayerCards);
					if (groupCard == NULL) {
						// trace("Auto 4 doi thong");
						// groupCard = Has4DoiThong(LastCards, group);
						groupCard = Auto4Pair(LastCards, group, PlayerCards);
					}
					/*
					* if (groupCard == NULL) { //trace("kiem tra tu quy");
					* groupCard = HasFour(LastCards, group); }
					*/
					if (groupCard == NULL) {
						// trace("kiem tra 3 doi thong");
						groupCard = Has3DoiThong(LastCards, group, PlayerCards);
					}
				}
			}
		} else if (group->GetNumOfCards() == 2) {
			if (groupCard == NULL) {
				// trace("CheckGroup --- Kiem tra danh sanh");
				if (ChooseCards->GetGroupKind() != EG_NORMAL)
					// groupCard = HasSequence(LastCards, group);
						groupCard = AutoSequence(LastCards, group, PlayerCards);
			}
		}
	}
//	delete group;
	if (groupCard != NULL) {
		// //var pGP:GraphicProcessing = GameModule.graphicProcessing;
		// int MyID =
		// ModuleMgr.getInstance().doFunction(ModuleMgr.USER_GET_MY_CHAIR);
		// var MyCards:CardGroupDraw =
		// GameModule.graphicProcessing.CardsHold[MyID];
		// for (int i = 0; i < MyCards.iNumCard; i++)
		// {
		// for (int j = 0; j < groupCard.GetNumOfCards(); j++)
		// {
		// //trace ("---CardID ", groupCard.Cards[j]->ID);
		// if (MyCards.GetCard(i).ImageID == groupCard.Cards.at(j)->ID)
		// MyCards.GetCard(i).isNoticed = true;
		// }
		// }

		return groupCard;
	}
	return NULL;
}


TienlenGroupCard* TienlenPlayerCard::FirstTurnPlay(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	return CheckGroup(LastCards, ChooseCards, PlayerCards);
}

// minh khong phai la nguoi danh dau tien cua vong choi
TienlenGroupCard* TienlenPlayerCard::OnTurnPlay(TienlenGroupCard* LastCards, TienlenGroupCard* ChooseCards, TienlenPlayerCard* PlayerCards) {
	TienlenGroupCard* ChooseCardsTemp = new TienlenGroupCard(); // bien tam
	vector<TienlenCard*> chooseCardOrigin;
	ChooseCardsTemp->Cards.push_back(ChooseCards->Cards.at(0));
	TienlenCard* cardChoose = ChooseCards->Cards.at(0);
	vector<TienlenCard*> TempCards;
	for (int i = 0; i < PlayerCards->GetNumOfGroupCards(); i++) {
		for (int j = 0; j < PlayerCards->GroupCards.at(i)->Cards.size(); j++) {
			TempCards.push_back(PlayerCards->GroupCards.at(i)->Cards.at(j));
		}
	}

	for (int i = 0; i < ChooseCards->GetNumOfCards(); i++) {
		chooseCardOrigin.push_back(ChooseCards->Cards.at(i));
	}
	// phai loai bo card nam trong bo tu qui, doi thong.
	TempCards = TienlenGameLogic::sortCards(TempCards, true);
	// tim tu quy
	vector<TienlenGroupCard*> vectorTuQuy;
	TienlenGroupCard* groupTuQuy;
	int size = TempCards.size() - 1;
	for (int i = 0; i < size; i++) {
		int countTQ = 0;
		groupTuQuy = new TienlenGroupCard();
		groupTuQuy->AddCard(TempCards.at(i));
		for (int j = i + 1; j < TempCards.size(); j++) {
			if (TempCards.at(i)->GetNumber() == TempCards.at(j)->GetNumber()) {
				countTQ++;
				groupTuQuy->AddCard(TempCards.at(j));
			}
		}
		if (countTQ == 4) {
			vectorTuQuy.push_back(groupTuQuy);
		}
	} // Kiem tra sanh

	// kiem tra doi thong, neu co cho vao cac group
	vector<TienlenGroupCard*> vectoDoiThong;
	TienlenGroupCard* groupDoiThong;
	for (int i = 0; i < TempCards.size(); i++) {
		int num = TempCards.size() - 2;
		if(i <= num)
		{
		}
		
		if (i <= num) {
			if (TempCards.at(i)->GetNumber() == TempCards.at(i + 1)->GetNumber()) {
				groupDoiThong = new TienlenGroupCard();
				groupDoiThong->AddCard(TempCards.at(i));
				int k = 1;
				for (int j = i + 1; j < TempCards.size(); j++) {
					if (k == 1) // 1 card
					{
						if (TempCards.at(j)->GetNumber() == groupDoiThong->Cards.at(groupDoiThong->Cards.size() - 1)->GetNumber()) {
							groupDoiThong->AddCard(TempCards.at(j));
							k++;
							continue;
						} else {
							groupDoiThong->Cards.pop_back();
							break;
						}
					}

					if (k == 2) // 2 card
					{
						// if (TempCards[j]->GetNumber() ==
						// groupDoiThong->Cards[groupDoiThong->Cards.length -
						// 1]->GetNumber())
						// groupDoiThong->Cards[groupDoiThong->Cards.length -
						// 1] = TempCards[j];
						if (TempCards.at(j)->GetNumber() != 15) {
							if (TempCards.at(j)->GetNumber() == groupDoiThong->Cards.at(groupDoiThong->Cards.size() - 1)->GetNumber() + 1) {
								groupDoiThong->AddCard(TempCards.at(j));
								k--;
							}
						}
					}
				}
				if (groupDoiThong->GetNumOfCards() >= 6) {
					if (groupDoiThong->GetNumOfCards() % 2 == 1)
						groupDoiThong->Cards.pop_back();

					vectoDoiThong.push_back(groupDoiThong);
				}
			}
		}
	}

	switch (LastCards->GetGroupKind()) {
	case EG_ONECARD: {
		if (LastCards->GetNumber() == 15) // danh 2 -->dung tu qui hoac 3,4,5
			// doi thong de do
		{
			bool isDoiThong = false;
			// ko co thi kiem tra doi thong,//trýõng 3,4,5 doi thong
			for (int i = 0; i < vectoDoiThong.size(); i++) {
				if (vectoDoiThong.at(i)->searchCard(ChooseCardsTemp->Cards.at(0))) {
					ChooseCards = vectoDoiThong.at(i);
					isDoiThong = true;
					break;
				}
			}
			if (isDoiThong)
				break;
			else {
				int kt = 0;
				for (int i = 0; i < TempCards.size(); i++) {
					if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) {
						ChooseCardsTemp->AddCard(TempCards.at(i));
						kt++;
					}
				}

				if (kt == 4) // co tu quy thi hien het tu quy len
				{
					ChooseCards->Cards = ChooseCardsTemp->Cards;
					break;
				}
			}
		}
		// neu ko phai 2 thi ko lam gi ca
		break;
									  }
	case EG_NORMAL: {
		if (LastCards->GetNumOfCards() == 2) // danh doi
		{
			if (LastCards->GetNumber() != 15) // khong phai doi 2
			{
				// var maxID :int = (LastCards->GetNumber() - 3) * 4 +
				// LastCards->GetBiggestSuit(); //Id cua thang lon nhat
				int maxID = LastCards->Cards.at(1)->ID;
				if (ChooseCardsTemp->Cards.at(0)->GetNumber() >= LastCards->Cards.at(0)->GetNumber()) //
				{
					if (ChooseCardsTemp->Cards.at(0)->ID > maxID) {
						for (int i = 0; i < TempCards.size(); i++) {
							if ((TempCards.at(i)->ID != ChooseCardsTemp->Cards.at(0)->ID) && (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber())) {
								ChooseCardsTemp->AddCard(TempCards.at(i));
								break;
							}
						}
					} else {
						for (int i = 0; i < TempCards.size(); i++) {
							if (TempCards.at(i)->ID > ChooseCardsTemp->Cards.at(0)->ID && TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) {
								ChooseCardsTemp->AddCard(TempCards.at(i));
								break;
							}
						}
					}

				}
				if (ChooseCardsTemp->Cards.size() == 2) {
					ChooseCards->Cards = ChooseCardsTemp->Cards;
				}
			} else // neu la doi 2 : dung tu quy, 4,5 doi thong de chat
			{
				// dung 4, 5 doi thong ne:
				if (ChooseCardsTemp->Cards.at(0)->GetNumber() == 15) // neu
					// co y
						// dinh
							// chon
								// doi 2
									// to
										// hon
				{
					for (int i = 0; i < TempCards.size(); i++) {
						if (TempCards.at(i)->GetNumber() == 15 && TempCards.at(i)->ID != ChooseCardsTemp->Cards.at(0)->ID) {
							ChooseCardsTemp->AddCard(TempCards.at(i));
							break;
						}
					}
					if (ChooseCardsTemp->Cards.size() == 2 && ChooseCardsTemp->GetMaxID() > LastCards->GetMaxID()) {
						ChooseCards = ChooseCardsTemp;
						break; // thoat khoi case GroupCard.EG_NORMAL.
					}

				}

				// dinh chon doi thong
				bool isDoithong1 = false;
				for (int i = 0; i < vectoDoiThong.size(); i++) {
					if (vectoDoiThong.at(i)->Cards.size() >= 8) {
						ChooseCards = vectoDoiThong.at(i);
						isDoithong1 = true;
						break;
					}
				}
				if (isDoithong1) {
					break; // neu co doi thong thi thoi ko chon tu quy nua
				} else {
					int kt1 = 0;
					for (int i = 0; i < TempCards.size(); i++) {
						if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) {
							ChooseCardsTemp->AddCard(TempCards.at(i));
							kt1++;
						}
					}

					if (kt1 == 4) // co tu quy thi hien het tu quy len
					{
						ChooseCards->Cards = ChooseCardsTemp->Cards;
						break;
					}
				}
			}

		} else if (LastCards->GetNumOfCards() == 3) // xam' co
		{
			if (ChooseCardsTemp->Cards.at(0)->GetNumber() > LastCards->Cards.at(0)->GetNumber()) {
				for (int i = 0; i < TempCards.size(); i++) {
					if (ChooseCardsTemp->Cards.size() < 3) {
						if (TempCards.at(i)->ID != ChooseCardsTemp->Cards.at(0)->ID && TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) {
							ChooseCardsTemp->AddCard(TempCards.at(i));
						}
					} else
						break;

				}
				if (ChooseCardsTemp->Cards.size() == 3) {
					ChooseCards->Cards = ChooseCardsTemp->Cards;
				}
			}
		} else // tu qui
		{
			if (ChooseCardsTemp->Cards.at(0)->ID > LastCards->Cards.at(0)->ID) // kiem
			{
				for (int i = 0; i < TempCards.size(); i++) {
					if (ChooseCardsTemp->Cards.size() < 4) {
						if (TempCards.at(i)->ID != ChooseCardsTemp->Cards.at(0)->ID && TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) {
							ChooseCardsTemp->AddCard(TempCards.at(i));
						}
					} else {
						break;
					}
				}
				if (ChooseCardsTemp->Cards.size() == 4) {
					ChooseCards->Cards = ChooseCardsTemp->Cards;
					break;
				}
			}

			// kiem tra xem co 4,5 doi thong ko.
			for (int i = 0; i < vectoDoiThong.size(); i++) {
				if (vectoDoiThong.at(i)->Cards.size() >= 8) {
					ChooseCards = vectoDoiThong.at(i);
					break;
				}
			}
		}
		break;
					}
	case EG_SEQUENCE: {

		if (ChooseCardsTemp->Cards.at(0)->ID < LastCards->Cards.at(LastCards->Cards.size() - 1)->ID) // card
		
		{
			for (int i = 0; i < TempCards.size(); i++) {
				if (ChooseCardsTemp->Cards.size() < LastCards->Cards.size()) // neu
					
				{
					if (TempCards.at(i)->GetNumber() != 15) {
						if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->GetNumber() + 1) {
							ChooseCardsTemp->AddCard(TempCards.at(i));
						}
						if (ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->ID >= LastCards->Cards.at(LastCards->Cards.size() - 1)->ID)
							break;
					}
				} else {
					break;
				}
			}

			// neu nhu cung du so la bai de do rui thi phai chon
			if (ChooseCardsTemp->Cards.size() == LastCards->Cards.size() && ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->GetNumber() == LastCards->Cards.at(LastCards->Cards.size() - 1)->GetNumber() && ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->ID < LastCards->Cards.at(LastCards->Cards.size() - 1)->ID) {
				for (int i = 0; i < TempCards.size(); i++) {
					if (ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->ID < LastCards->Cards.at(LastCards->Cards.size() - 1)->ID)
						if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->GetNumber())
							if (TempCards.at(i)->ID > ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->ID)
							{
								ChooseCardsTemp->Cards.pop_back();
								ChooseCardsTemp->Cards.push_back(TempCards.at(i));
							}
				}

			}

			if (ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->ID < LastCards->Cards.at(LastCards->Cards.size() - 1)->ID) {
				return NULL; // khong co la bai nao co ID lon hon cua
				// LastCard
			}

		}

		if (ChooseCardsTemp->Cards.size() < LastCards->Cards.size()) // add
			
		{
			for (int i = TempCards.size() - 1; i >= 0; i--) {
				// neu ma cung getNumber thi lay la bai co ID nho hon
				if (TempCards.at(i)->GetNumber() < cardChoose->GetNumber()) // khong
					
				{
					if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) // neu
					{
						if (TempCards.at(i)->ID < ChooseCardsTemp->Cards.at(0)->ID) {
							ChooseCardsTemp->Cards.erase(ChooseCardsTemp->Cards.begin());
							ChooseCardsTemp->Cards.insert(ChooseCardsTemp->Cards.begin(), TempCards.at(i));
						}
					}
				}

				if (ChooseCardsTemp->Cards.size() < LastCards->Cards.size()) {
					if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber() - 1) {
						ChooseCardsTemp->Cards.insert(ChooseCardsTemp->Cards.begin(), TempCards.at(i)); // add
						
					}
				}
			}
		}

		if (ChooseCardsTemp->Cards.size() < LastCards->Cards.size()) {
			for (int i = 0; i < TempCards.size(); i++) {
				if (ChooseCardsTemp->Cards.size() < LastCards->Cards.size()) {
					if (TempCards.at(i)->GetNumber() != 15) {
						if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(ChooseCardsTemp->Cards.size() - 1)->GetNumber() + 1) {
							ChooseCardsTemp->AddCard(TempCards.at(i));
						}
					}
				} else {
					break;
				}
			}
		}

		/*
		* var gc:GroupCard = MyCards.HasSequence(LastCards, ChooseCards);
		* if (gc != NULL) ChooseCardsTemp = gc;
		*/

		if (ChooseCardsTemp->Cards.size() == LastCards->Cards.size()) {
			// trace("ok sanh nay do duoc");
			// int myID =
			// ModuleMgr.getInstance().doFunction(ModuleMgr.USER_GET_MY_CHAIR);
			int resultInt = TienlenRule::CheckValidCard(LastCards, ChooseCardsTemp, PlayerCards);
			if (resultInt == E_NO_ERROR)
				ChooseCards->Cards = ChooseCardsTemp->Cards;
		} else {
			// trace("không do dc");
		}
		break;
									   }
	case EG_BIGGER: // ba doi thong
		{
			// chat bang cach dung ba doi thong to hon,tu quy hoac 4, doi thong
			int kt1 = 0;
			// tu quy ne
			for (int i = 0; i < TempCards.size(); i++) {
				if (TempCards.at(i)->GetNumber() == ChooseCardsTemp->Cards.at(0)->GetNumber()) {
					ChooseCardsTemp->AddCard(TempCards.at(i));
					kt1++;
				}
			}
			if (kt1 == 4) // co tu quy thi hien het tu quy len
			{
				ChooseCards->Cards = ChooseCardsTemp->Cards;
				break;
			}

			// ko co tu quy thi dung doi thong
			for (int i = 0; i < vectoDoiThong.size(); i++) {
				if (vectoDoiThong.at(i)->searchCard(ChooseCardsTemp->Cards.at(0))) {
					if (vectoDoiThong.at(i)->Cards.size() == 6) {
						if (vectoDoiThong.at(i)->Cards.at(vectoDoiThong.at(i)->Cards.size() - 1)->ID > LastCards->Cards.at(LastCards->Cards.size() - 1)->ID) {
							ChooseCards = vectoDoiThong.at(i);
							break;
						}
					}
					if (vectoDoiThong.at(i)->Cards.size() > 6) {
						ChooseCards = vectoDoiThong.at(i);
						break;
					}
				}

			}
			break;
		}
	case EG_SUPER: // don doi thong
		{
			// chat bang cach bon doi thong to hon hoac 5 doi thong
			for (int i = 0; i < vectoDoiThong.size(); i++) {
				if (vectoDoiThong.at(i)->searchCard(ChooseCardsTemp->Cards.at(0))) {
					if (vectoDoiThong.at(i)->Cards.size() == 8) {
						if (vectoDoiThong.at(i)->Cards.at(vectoDoiThong.at(i)->Cards.size() - 1)->ID > LastCards->Cards.at(LastCards->Cards.size() - 1)->ID) {
							ChooseCards = vectoDoiThong.at(i);
							break;
						}
					} else if (vectoDoiThong.at(i)->Cards.size() == 10) {
						ChooseCards = vectoDoiThong.at(i);
						break;
					}
				}
			}
			break;
		}
	case EG_ULTRA: // 5 doi thong
		{
			// chat bang cach 5 doi thong to hon
			for (int i = 0; i < vectoDoiThong.size(); i++) {
				if (vectoDoiThong.at(i)->searchCard(ChooseCardsTemp->Cards.at(0))) {
					if (vectoDoiThong.at(i)->Cards.size() == 10) {
						if (vectoDoiThong.at(i)->Cards.at(vectoDoiThong.at(i)->Cards.size() - 1)->ID > LastCards->Cards.at(LastCards->Cards.size() - 1)->ID) {
							ChooseCards = vectoDoiThong.at(i);
							break;
						}
					}
				}
			}
			break;
		}
		// Cac truong hop khac
	}
	// cho card len
	int i, j;
	if (ChooseCards->Cards.size() > 1) {

		for (i = 0; i < chooseCardOrigin.size(); i++)
			if (checkIn(chooseCardOrigin[i]->ID, ChooseCards))
				continue;
			else {
				for (j = 0; j < ChooseCards->Cards.size(); j++)
					if (ChooseCards->Cards.at(j)->GetNumber() == chooseCardOrigin[i]->GetNumber() && !checkIn(ChooseCards->Cards.at(j)->ID, chooseCardOrigin)) {
						// trao doi ID
						ChooseCards->Cards.at(j)->ID = chooseCardOrigin[i]->ID;
						break;
					}

			}
			return ChooseCards;
	}
	return NULL;
}

bool TienlenPlayerCard::checkIn(int number, vector<TienlenCard*> group) {
	int i;
	for (i = 0; i < group.size(); i++) {
		if (number == group[i]->ID)
			return true;
	}
	return false;
}

bool TienlenPlayerCard::checkIn(int number, TienlenGroupCard* group) {
	int i;
	for (i = 0; i < group->Cards.size(); i++) {
		if (number == group->Cards.at(i)->ID)
			return true;
	}
	return false;
}

bool TienlenPlayerCard::CanPlay(TienlenGroupCard* group) {
	switch (group->GetGroupKind()) {
	case EG_NONE:
		return true;
	case EG_ONECARD:// khong phai bo
		{
			// trace("ONE_CARD");
			return CanPlayOneCard(group);
		}
	case EG_NORMAL: // doi, ba, tu quy
		{
			// trace("NORMAL");
			return CanPlayNormal(group);
		}
	case EG_SEQUENCE: // sanh
		{
			// trace("SEQUENCE");
			return CanPlaySequence(group);
		}
	case EG_ULTRA: // 5 doi thong
		{
			// trace("ULTRA");
			return CanPlayULTRA(group);
		}
	case EG_SUPER: // 4 doi thong
		{
			// trace("SUPER");
			return CanPlaySUPER(group);
		}
	case EG_BIGGER: // 3 doi thong
		{
			// trace("BIGGER");
			return CanPlayBIGGER(group);
		}
	}
	return false;
}

bool TienlenPlayerCard::CanPlayOneCard(TienlenGroupCard* group) {
	if (group->GetNumber() == 15) {
		// trace("Quan 2");
		if (CanPlayULTRA(NULL) || CanPlaySUPER(NULL) || CanPlayBIGGER(NULL) || GetMaxFour() > -1)
			return true;
	}
	int maxID = -1;
	int maxNum = -1;
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			if (maxNum < GroupCards.at(i)->Cards.at(s)->GetNumber()) {
				maxNum = GroupCards.at(i)->Cards.at(s)->GetNumber();
				vector<int> groupID = GetCardNumber(maxNum); // group da
			
				if (groupID.size() > 0) {
					for (int m = 0; m < groupID.size(); m++) {
						if (maxID < groupID.at(m))
							maxID = groupID.at(m);
					}
					// maxID = groupID.at(groupID.size() - 1);
				}
			}
		}
	}
	if (maxNum > group->GetMaxNumber())
		return true;
	else if (maxNum == group->GetMaxNumber()) {
		if (maxID > group->GetMaxID())
			return true;
	}
	return false;
}

bool TienlenPlayerCard::CanPlayBIGGER(TienlenGroupCard* group) {
	if (CanPlayULTRA(NULL) // 5 doi thong
		|| CanPlaySUPER(NULL)) // 4 doi thong
		return true;
	// kiem tra tu quy
	int tuquy [16];
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 16; i++) {
		tuquy[i] = 0;
	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int ss = 0; ss < GroupCards.at(i)->GetNumOfCards(); ss++) {
			int ind = GroupCards.at(i)->Cards.at(ss)->GetNumber();
			if (ind >= 0 && ind < 16) {
				tuquy[ind]++;
				if (tuquy[ind] == 4) // 3
				{
					return true;
				}
			}
		}
	}
	// kiem tra 3 doi thong lon hon
	int doi [16];
	int ID [16]; // toi da có 6 dôi (13/2)
	j = 0;
	k = 0;
	for (i = 0; i < 16; i++)
		doi[i] = 0;
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 16) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 3) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}

				for (i = 0; i < 4; i++) // duyet cac doi tu lon den nho
				{
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 2] == 2) // co 3 doi thong
						{
							if (group == NULL) // kiem tra co 3 doi thong hay khong,
								// thi ko can truyen group vao
									return true; // co 3 doi thong
							else {
								if (ID[i] > group->GetMaxNumber())
									return true;
								else if (ID[i] == group->GetMaxNumber()) {
									vector<int> groupID = GetCardNumber(ID[i]); // group
								
									if (groupID.size() > 0) {
										for (int m = 0; m < groupID.size(); m++) {
											if (group->GetMaxID() < groupID.at(m))
												return true;
										}
										// if (groupID.at(groupID.size() - 1) >
										// group->GetMaxID())
										// return true;
									}
								}
							}
						}
					}
				}
	}
	return false;
}

bool TienlenPlayerCard::CanPlaySUPER(TienlenGroupCard* group) {
	if (CanPlayULTRA(NULL))
		return true;
	int doi[16];
	int ID[16]; // toi da có 6 dôi (13/2)
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 16; i++)
		doi[i] = 0;
	// trace("Has5DoiThong->GetNumOfGroupCards ", GetNumOfGroupCards());
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 16) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 4) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}

				for (i = 0; i < 3; i++) // duyet cac doi tu lon den nho
				{
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 3] == 3) // co 4 doi thong
						{
							if (group == NULL)
								return true;
							else {
								if (ID[i] > group->GetMaxNumber())
									return true;
								else if (ID[i] == group->GetMaxNumber()) {
									vector<int> groupID = GetCardNumber(ID[i]); // group
								
									if (groupID.size() > 0) {
										for (int m = 0; m < groupID.size(); m++) {
											if (group->GetMaxID() < groupID.at(m))
												return true;
										}
										// if (groupID.at(groupID.size() - 1) >
										// group->GetMaxID())
										// return true;
									}
								}
							}
						}
					}
				}
	}
	return false;
}

bool TienlenPlayerCard::CanPlayULTRA(TienlenGroupCard* group) {
	int doi[16];
	int ID[16]; // toi da có 6 dôi (13/2)
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 16; i++)
		doi[i] = 0;
	// trace("Has5DoiThong->GetNumOfGroupCards ", GetNumOfGroupCards());
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index != 15) // khac quan 2
			{
				if (index >= 0 && index < 16) {
					doi[index]++;
					if (doi[index] == 2) // doi
					{
						k++;
						ID[j++] = index;
					}
				}
			}
		}
	}
	if (k >= 5) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}

				for (i = 0; i < 2; i++) // duyet cac doi tu lon den nho
				{
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 4] == 4) // co 5 doi thong
						{
							if (group == NULL)
								return true;
							else {
								if (ID[i] > group->GetMaxNumber())
									return true;
								else if (ID[i] == group->GetMaxNumber()) {
									vector<int> groupID = GetCardNumber(ID[i]); // group
								
									if (groupID.size() > 0) {
										for (int m = 0; m < groupID.size(); m++) {
											if (group->GetMaxID() < groupID.at(m))
												return true;
										}
										// if (groupID.at(groupID.size() - 1) >
										// group->GetMaxID())
										// return true;
									}
								}
							}
						}
					}
				}
	}
	return false;
}

bool TienlenPlayerCard::CanPlaySequence(TienlenGroupCard* group) {
	if (group->GetGroupKind() != EG_SEQUENCE)
		return false;
	int number[13];
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < 13; i++) // 13 quan bai
	{
		number[i] = 0;
	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			number[k++] = index;
		}
	}
	// sap xep 13 quan bai giam dan
	for (i = 0; i < 12; i++) {
		for (j = i + 1; j < 13; j++)
			if (number[i] < number[j]) {
				int tmp = number[i];
				number[i] = number[j];
				number[j] = tmp;
			}
			// trace (number[i]);
	}
	
	int n;
	for (i = 0; i < 12; i++) {
		vector<int> S ;
		n = number[i];
		if (n == 0 || n == 15 || n < group->GetMinNumber())
			continue;
		// trace("number[i] ", n);
		S.push_back(n);
		for (j = i + 1; j < 13; j++) {
			if (number[j] != 15) {
				if (number[j] == n - 1) {
					S.push_back(number[j]);
					n = number[j];
					if (S.size() == group->GetNumOfCards())
						break;
				}
			}
		}
		if (S.size() >= group->GetNumOfCards()) {
			// kiem tra cac quan chon co trong sanh nay khong
			int maxNum = -1;
			for (int x = 0; x < S.size(); x++) {
				if (maxNum < S.at(x)) {
					maxNum = S.at(x);
				}
			}
			if (maxNum > group->GetMaxNumber())
				return true;
			else if (maxNum == group->GetMaxNumber()) {
				vector<int> IDCard = GetCardNumber(maxNum);
				if (IDCard.size() > 0) {
					for (int m = 0; m < IDCard.size(); m++) {
						if (group->GetMaxID() < IDCard.at(m))
							return true;
					}
					// if (group->GetMaxID() < IDCard.at(IDCard.size() - 1))
					// return true;
				}
			}
		}
	}
	return false;
}

bool TienlenPlayerCard::CanPlayNormal(TienlenGroupCard* group) // danh chan tu quy ,
	// 3, doi
{
	if (group->GetNumOfCards() == 4) // tu quy
	{
		if (CanPlayULTRA(NULL) // 5 doi thong
			|| CanPlaySUPER(NULL)) // 4 doi thong
			return true;
		if (GetMaxFour() > group->GetMaxNumber())
			return true;
	} else if (group->GetNumOfCards() == 3) // bo 3
	{
		if (GetMaxThree() > group->GetMaxNumber())
			return true;
	} else if (group->GetNumOfCards() == 2) // doi
	{
		// trace("MAX PAIR", GetMaxPair(), "MAXID", group->GetMaxID());
		if (group->GetNumber() == 15) // doi 2
		{
			if (CanPlayULTRA(NULL) // 5 doi thong
				|| CanPlaySUPER(NULL) // 4 doi thong
				|| GetMaxFour() > -1) // tu quy
				return true;
			if (GetMaxPair() > group->GetMaxID())
				return true;
		} else if (GetMaxPair() > group->GetMaxID())
			return true;
	}
	return false;
}

int TienlenPlayerCard::GetMaxPair() // tra ve Max ID cua quan bai cua doi lon nhat
{
	int Pair[16];
	int number[16]; // toi da 6 doi
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 16; i++) {
		Pair[i] = 0;
	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index >= 0 && index < 16) {
				Pair[index]++;
				if (Pair[index] == 2) // doi
				{
					k++; // so doi
					number[j++] = index;
					// trace ("doi thu ", j, " la ", index);
				}
			}
		}
	}
	if (k >= 1) {
		int max = -1;
		for (i = 0; i < k; i++) {
			if (max < number[i])
				max = number[i];
		}
		vector<int> groupID = GetCardNumber(max); // group da duoc sap
		// xep tang dan
		// (mang chua ID
		// quan bai)
		if (groupID.size() > 0)
			return groupID.at(groupID.size() - 1);
	}
	// trace ("Khong co doi");
	return -1;
}

int TienlenPlayerCard::GetMaxThree() {
	int boba[16];
	int number[16]; // toi da 4 bo ba
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 16; i++) {
		boba[i] = 0;
	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index >= 0 && index < 16) {
				boba[index]++;
				if (boba[index] == 3) // 3
				{
					k++; // so bo tu quy
					number[j++] = index;
					// trace ("Co tu quy thu ", j, " la ", index);
				}
			}
		}
	}
	if (k >= 1) {
		for (i = 0; i < k - 1; i++)
			for (j = i + 1; j < k; j++)
				if (number[i] < number[j]) {
					int tmp = number[i];
					number[i] = number[j];
					number[j] = tmp;
				}
				return number[0];
	}
	return -1;
}

int TienlenPlayerCard::GetMaxFour() // lay ve tu quy lon nhat
{
	int tuquy[20];
	int number[20]; // toi da 3 bo tu quy
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i < 20; i++) {
		tuquy[i] = 0;
	}
	for (i = 0; i < GetNumOfGroupCards(); i++) {
		for (int s = 0; s < GroupCards.at(i)->GetNumOfCards(); s++) {
			int index = GroupCards.at(i)->Cards.at(s)->GetNumber();
			if (index >= 0 && index < 16) {
				tuquy[index]++;
				if (tuquy[index] == 4) // 3
				{
					k++; // so bo tu quy
					number[j++] = index;
					// trace ("Co tu quy thu ", j, " la ", index);
				}
			}
		}
	}
	if (k >= 1) {
		for (i = 0; i < k - 1; i++)
			for (j = i + 1; j < k; j++)
				if (number[i] < number[j]) {
					int tmp = number[i];
					number[i] = number[j];
					number[j] = tmp;
				}
				return number[0];
	}
	return -1;
}

int TienlenPlayerCard::getHas2FailAdvance() {
	if (GetNumOfGroupCards() == 0)
		return 0;
	int result = 0;
	for (int i = 0; i < GroupCards.size(); i++) {

		vector<TienlenCard*> Cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < Cards.size(); j++) {
			if (Cards.at(j)->GetNumber() == 15) {
				switch (Cards.at(j)->GetSuit()) {
				case 1:
				case 2:
					result += 3.0;
					break;
				case 3:
				case 4:
					result += 6.0;
					break;
				}
			}
		}
	}
	return result;
}

int TienlenPlayerCard::getNumOf2() {
	int result = 0;
	for (int i = 0; i < GroupCards.size(); i++) {

		vector<TienlenCard*> Cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < Cards.size(); j++) {
			if (Cards.at(j)->GetNumber() == 15) {
				result++;
			}
		}
	}
	return result;
}

bool TienlenPlayerCard::has3DoiThongTuQuy() {
	if (has4DoiThongTuQuy()) {
		if (Value.size() > 0) {
			if (hasTuQuy(Value.at(0)) || hasTuQuy(Value.at(Value.size() - 1)))
				return false;
		}
	} else if (Has3DoiThong()) {
		for (int i = 0; i < Value.size(); i++) {
			if (hasTuQuy(Value.at(i)))
				return true;
		}
	}
	return false;
}

bool TienlenPlayerCard::has4DoiThongTuQuy() {
	if (Has4DoiThong()) {

		for (int i = 0; i < Value.size(); i++) {
			if (hasTuQuy(Value.at(i)))
				return true;
		}
	}
	return false;
}

bool TienlenPlayerCard::has5DoiThongTuQuy() {
	if (HasUltra()) {
		for (int i = 0; i < Value.size(); i++) {
			// tu quy o giua thi return true;
			// de tinh thoi 3 doi thong + tu quy
			if (hasTuQuy(Value.at(i)) && i == Value.size() / 2)
				return true;
		}
	}
	return false;
}

bool TienlenPlayerCard::hasTuQuy(int num) {
	if (num < 0 || num >= 16)
		return false;
	// if (GroupCards.size() < 4)
	// return false;
	int tuquy[16];
	int i;
	for (i = 0; i < 16; i++)
		tuquy[i] = 0;
	int count = 0;
	for (i = 0; i < GroupCards.size(); i++) {
		for (int j = 0; j < GroupCards.at(i)->Cards.size(); j++) {

			int iNum = GroupCards.at(i)->Cards.at(j)->GetNumber();
			if (iNum == num)
				count++;
		}
	}
	if (count == 4)
		return true;
	return false;
}

int TienlenPlayerCard::getNumTuQuy() {
	int result = 0;
	int tuquy[16];
	int i;
	for (i = 0; i < 16; i++)
		tuquy[i] = 0;
	for (i = 0; i < GroupCards.size(); i++) {

		for (int j = 0; j < GroupCards.at(i)->Cards.size(); j++) {
			int iNum = GroupCards.at(i)->Cards.at(j)->GetNumber();
			if (tuquy[iNum] == 0) {
				if (iNum < 15 && hasTuQuy(iNum)) {

					result++;
					tuquy[iNum] = 4;
				}
			}
		}

	}
	return result;
}

bool TienlenPlayerCard::Has6DoiThong() {
	// if (GroupCards.size() < 10)
	// return false;
	int doi[20];
	int ID[6]; // t?i ?a cï¿½ 6 ?ï¿½i (13/2)
	int i, j = 0, k = 0;
	for (i = 0; i < GroupCards.size(); i++)
		doi[i] = 0;
	for (i = 0; i < GroupCards.size(); i++) {
		if (GroupCards.at(i)->GetNumber() != 15) // khac quan 2
		{
			int index = GroupCards.at(i)->GetNumber();
			if (index >= 0 && index < 20) {
				doi[index]++;
				if (doi[index] == 2) // doi
				{
					k++;
					ID[j++] = index;
				}
			}
		}
	}
	if (k >= 6) {
		for (i = 0; i < 5; i++)
			for (j = i + 1; j < 6; j++)
				if (ID[i] < ID[j]) // sap xep mang cac doi nho dan
				{
					int temp = ID[i];
					ID[i] = ID[j];
					ID[j] = temp;
				}
				for (i = 0; i < 2; i++)
					if (ID[i] > 0) {
						if (ID[i] - ID[i + 5] == 5) {
							Value.clear();
							for (j = ID[i]; j >= ID[i + 5]; j--)
								Value.push_back(j);
							return true;
						}
					}
	}
	return false;
}

int TienlenPlayerCard::getHas2FailEatAll() {
	if (GetNumOfGroupCards() == 0)
		return 0;
	int result = 0;
	for (int i = 0; i < GroupCards.size(); i++) {
		vector<TienlenCard*> Cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < Cards.size(); j++) {
			if (Cards.at(j)->GetNumber() == 15) {
				switch (Cards.at(j)->GetSuit()) {
				case 1:
				case 2:
					result += 1.0;
					break;
				case 3:
				case 4:
					result += 2.0;
					break;
				}
			}
		}
	}
	return result;
}

void TienlenPlayerCard::autoArrange()
{
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 16; j++) {
			arraySuit[i][j] = -1;
		}
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 5; j++) {
			arrayNumber[i][j] = -1;
		}
	for (int i = 0; i < GetNumOfGroupCards(); i++) {
		for (int j = 0; j < GroupCards.at(i)->GetNumOfCards(); j++) {
			TienlenCard* card = GroupCards.at(i)->Cards.at(j);
			if (card->GetNumber() >= 0 && card->GetNumber() < 16 && card->GetSuit() >= 0 && card->GetSuit() < 5) {
				if (card->GetNumber() == 14) {
					arraySuit[card->GetSuit()][1] = 1;
					arrayNumber[1][card->GetSuit()] = 1;
				}
				arraySuit[card->GetSuit()][card->GetNumber()] = 1;
				arrayNumber[card->GetNumber()][card->GetSuit()] = 1;
			}
		}
	}
	// xep bo bai tu lon den be
	for (int i = 0; i < autoGroupCard.size(); i++) {
		//delete autoGroupCard.at(i);
	}
	autoGroupCard.clear();
	// lay ra bo tu quy
	autoArrange1();

	// lay ra bo ba doi thong
	autoArrange2();

	// lay ra sanh
	autoArrange3();

	// lay ra xam
	autoArrange4();

	// lay ra doi
	autoArrange5();

	// lay ra mau thau
	autoArrange6();
}

void TienlenPlayerCard::autoArrange1()
{
	for (int i = 15; i >= 3; i--) {
		if (TienlenRule::inTuQuy(arrayNumber, i)) {
			TienlenGroupCard* groupTuquy = new TienlenGroupCard();
			for (int k = 1; k < 5; k++) {
				arraySuit[k][i] = -1;
				arrayNumber[i][k] = -1;
				TienlenCard* card = new TienlenCard();
				card->setCard(i, k);
				groupTuquy->AddCard(card);
			}
			autoGroupCard.push_back(groupTuquy);
		}
	}
}

void TienlenPlayerCard::autoArrange2()
{
	for (int i = 15; i >= 3; i--) {
		if (TienlenRule::inPair(arrayNumber, i)) {
			if (TienlenRule::inBaDoiThong(arrayNumber, i)) {
				TienlenGroupCard* groupBaDoiThong = new TienlenGroupCard();
				for (int j = i; j < 15; j++) {
					if (TienlenRule::inPair(arrayNumber, j)) {
						int count = 0;
						for (int k = 1; k < 5; k++) {
							if (arrayNumber[j][k] > 0) {
								count++;
								arraySuit[k][j] = -1;
								arrayNumber[j][k] = -1;
								TienlenCard* card = new TienlenCard();
								card->setCard(j, k);
								groupBaDoiThong->AddCard(card);
								if (count == 2)
									break;
							}
						}
					}
					else {
						break;
					}
				}
				for (int j = i - 1; j > 2; j--) {
					int count = 0;
					if (TienlenRule::inPair(arrayNumber, j)) {
						for (int k = 1; k < 5; k++) {
							if (arrayNumber[j][k] > 0) {
								count++;
								arraySuit[k][j] = -1;
								arrayNumber[j][k] = -1;
								TienlenCard* card = new TienlenCard();
								card->setCard(j, k);
								groupBaDoiThong->AddCard(card);
								if (count == 2)
									break;
							}
						}
					}
					else {
						break;
					}
				}
				autoGroupCard.push_back(groupBaDoiThong);
			}
		}
	}
}

void TienlenPlayerCard::autoArrange3()
{
	for (int i = 14; i >= 3; i--) {
		if (TienlenRule::haveNumber(arrayNumber, i)) {
			if (TienlenRule::inSanh(arrayNumber, i)) {
				TienlenGroupCard* groupSanh = new TienlenGroupCard();
				for (int j = i; j < 15; j++) {
					bool inSanh = false;
					for (int k = 1; k < 5; k++) {
						if (arrayNumber[j][k] > 0) {
							arraySuit[k][j] = -1;
							arrayNumber[j][k] = -1;
							TienlenCard* card = new TienlenCard();
							card->setCard(j, k);
							groupSanh->AddCard(card);
							inSanh = true;
							break;
						}
					}
					if (inSanh == false) {
						break;
					}
				}
				for (int j = i - 1; j > 2; j--) {
					bool inSanh = false;
					for (int k = 1; k < 5; k++) {
						if (arrayNumber[j][k] > 0) {
							arraySuit[k][j] = -1;
							arrayNumber[j][k] = -1;
							TienlenCard* card = new TienlenCard();
							card->setCard(j, k);
							groupSanh->AddCard(card);
							inSanh = true;
							break;
						}
					}
					if (inSanh == false) {
						break;
					}
				}
				autoGroupCard.push_back(groupSanh);
			}
		}
	}
}

void TienlenPlayerCard::autoArrange4()
{
	for (int i = 15; i >= 3; i--) {
		if (TienlenRule::inXam(arrayNumber, i)) {
			TienlenGroupCard* groupXam = new TienlenGroupCard();
			for (int k = 1; k < 5; k++) {
				if (arrayNumber[i][k] > 0) {
					arraySuit[k][i] = -1;
					arrayNumber[i][k] = -1;
					TienlenCard* card = new TienlenCard();
					card->setCard(i, k);
					groupXam->AddCard(card);
				}
			}
			autoGroupCard.push_back(groupXam);
		}
	}
}

void TienlenPlayerCard::autoArrange5()
{
	for (int i = 15; i >= 3; i--) {
		if (TienlenRule::inPair(arrayNumber, i)) {
			TienlenGroupCard* groupPair = new TienlenGroupCard();
			for (int k = 1; k < 5; k++) {
				if (arrayNumber[i][k] > 0) {
					arraySuit[k][i] = -1;
					arrayNumber[i][k] = -1;
					TienlenCard* card = new TienlenCard();
					card->setCard(i, k);
					groupPair->AddCard(card);
				}
			}
			autoGroupCard.push_back(groupPair);
		}
	}
}

void TienlenPlayerCard::autoArrange6()
{
	for (int i = 15; i >= 3; i--) {
		if (TienlenRule::haveNumber(arrayNumber, i)) {
			TienlenGroupCard* groupMauThau = new TienlenGroupCard();
			for (int k = 1; k < 5; k++) {
				if (arrayNumber[i][k] > 0) {
					arraySuit[k][i] = -1;
					arrayNumber[i][k] = -1;
					TienlenCard* card = new TienlenCard();
					card->setCard(i, k);
					groupMauThau->AddCard(card);
				}
			}
			autoGroupCard.push_back(groupMauThau);
		}
	}
}

vector<int> TienlenPlayerCard::getAutoPlayCard(int minNumCard, int maxCard, int nextCard)
{
	/*if (true)
		{
		vector<int> arr;
		arr.push_back(this->getListIdCard().at(0));
		return arr;
	}*/
	autoArrange();
	TienlenGroupCard* group;
	TienlenGroupCard* group1;
	if (autoGroupCard.size() == 2) {
		// uu tien danh bo co so quan lon hon min Num Card
		/*for (int i = 0; i < autoGroupCard.size(); i++) {
			if (autoGroupCard.at(i)->GetNumOfCards() > minNumCard) {}
		}*/

		// uu tien danh bo to
		
		group = autoGroupCard.at(0);
		group1 = autoGroupCard.at(1);
		int groupKind = group->GetGroupKind();
		
		if (groupKind == EG_ONECARD) {
			if (nextCard >= 2) {
				group = autoGroupCard.at(1);
			}
		}
		else {
			if (nextCard > 1) {
				if (group->GetNumOfCards() > maxCard) {
					// chac chan danh bo nay
				}
				else {
					// danh bo co kha nang ve
					switch (groupKind)
					{
					case EG_TU_QUY:
					case EG_BIGGER:
					case EG_SUPER:
					case EG_ULTRA:
						break;
					case EG_SEQUENCE:
						if (group->GetNumOfCards() >= maxCard - 2) {
							// luon danh
						}
						else {
							if (group->GetNumber() >= 12) {
								// la mot bo to se luon danh
							}
							else {
								// danh bo nho hon
								if (group1->GetNumber() < group->GetNumber() + 4) {
									group = group1;
								}
							}
						}
						break;
					case EG_NORMAL:
						if (group->GetNumOfCards() >= 3) {
							// chac chan danh
						}
                        else if (group1->GetNumOfCards() >= 3)
                        {
                            group = group1;
                        }
						else {
							// danh khi day la mot doi to co kha nang ve, dung ra la se xet ca hien trang xem co bao nhieu ti le bi chan
							if (group->GetNumber() >= 12) {
								// chac chan danh
							}
							else {
								// danh bo nho hon
								if (group1->GetNumOfCards() == 2) {
									group = group1;
								}
								else {
									if (group1->GetNumber() < group->GetNumber() + 2) {
										group = group1;
									}
								}
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else {
		if (minNumCard < 2) {
			group = autoGroupCard.at(0);
		}
		else {
			int i;
			vector<TienlenGroupCard*> groupSanh;
			vector<TienlenGroupCard*> groupNormal;
			vector<TienlenGroupCard*> groupOne;
			for (i = 0; i < autoGroupCard.size(); i++) {
				int groupKind = autoGroupCard.at(i)->GetGroupKind();

				if (groupKind == EG_TU_QUY || groupKind == EG_ULTRA || groupKind == EG_BIGGER || groupKind == EG_SUPER) {

				}
				else {
					if (groupKind == EG_SEQUENCE) {
						groupSanh.push_back(autoGroupCard.at(i));
					}
					else if (groupKind == EG_NORMAL ) {
						if (autoGroupCard.at(i)->GetNumber() != 15 && autoGroupCard.at(i)->GetNumOfCards() < 4)
							groupNormal.push_back(autoGroupCard.at(i));
					}
					else if (groupKind == EG_ONECARD) {
						if (autoGroupCard.at(i)->GetNumber() != 15) {
							groupOne.push_back(autoGroupCard.at(i));
						}
					}
					else {
						if (autoGroupCard.at(i)->GetNumber() != 15)
							groupOne.push_back(autoGroupCard.at(i));
					}
				}
			}
			int sum = groupSanh.size() + groupOne.size() * 2 + groupNormal.size();
			float percentSanh = groupSanh.size() * 1.0f / sum;
			float percentNormal = groupNormal.size() * 1.0f / sum + percentSanh;
			float percentOne = groupOne.size() * 1.0f / sum * 2 + percentNormal;
			float arrayType[] = { percentSanh, percentNormal, percentOne };

			if (sum == 0) {
				group = autoGroupCard.back();
			}
			else {
				float randomType = AXRANDOM_0_1();
				int indexType = 0;
				for (int i = 0; i < 3; i++) {
					if (randomType < arrayType[i]) {
						indexType = i;
						break;
					}
				}
				switch (indexType)
				{
				case 0:
					group = groupSanh.back();
					break;
				case 1:
					group = groupNormal.back();
					break;
				default:
					group = groupOne.back();
					break;
				}
			}
		}
	}
	
	return group->getListId();
	//for (int i = 0; i < group->Cards.size(); i++)
}

std::vector<int> TienlenPlayerCard::getAutoResponseCard(TienlenGroupCard* groupCard, int minNumCard, int nextCard)
{
	
	AXLOGD("getAutoResponseCard 1");
	autoArrange();
	AXLOGD("getAutoResponseCard 2");
	vector<int> result;
	/*if (true)
		return result;*/
	int groupKind = groupCard->GetGroupKind();
	switch (groupKind)
	{
	case EG_ULTRA:
		for (int i = 0; i < autoGroupCard.size(); i++) {
			TienlenGroupCard* group = autoGroupCard.at(i);
			groupKind = group->GetGroupKind();
			if (groupKind == EG_ULTRA) {
				if (group->GetMaxID() > groupCard->GetMaxID())
					return group->getListId();
			}
			else {
				return result;
			}
		}
		break;
	case EG_SUPER:
		for (int i = 0; i < autoGroupCard.size(); i++) {
			TienlenGroupCard* group = autoGroupCard.at(i);
			groupKind = group->GetGroupKind();
			if (groupKind == EG_SUPER) {
				if (group->GetMaxID() > groupCard->GetMaxID())
					return group->getListId();
			}
			else {
				return result;
			}
		}
		break;
	//case EG_TU_QUY:
	//	// xem co tu quy hoac bon doi thong
	//	for (int i = 0; i < autoGroupCard.size(); i++) {
	//		TienlenGroupCard* group = autoGroupCard.at(i);
	//		groupKind = group->GetGroupKind();
	//		if (groupKind == EG_TU_QUY) {
	//			// xem co phai tu quy lon hon khong
	//			if (group->GetMaxNumber() > groupCard->GetMaxNumber()) {
	//				return group->getListId();
	//			}
	//		}
	//	}
	//	for (int i = 0; i < autoGroupCard.size(); i++) {
	//		TienlenGroupCard* group = autoGroupCard.at(i);
	//		groupKind = group->GetGroupKind();
	//		if (groupKind == EG_SUPER || groupKind == EG_ULTRA) {
	//			return group->getListId();
	//		}
	//		else {
	//			return result;
	//		}
	//	}
	//	return result;
	//	break;
	case EG_BIGGER:
		// xem co ba doi thong
		for (int i = 0; i < autoGroupCard.size(); i++) {
			TienlenGroupCard* group = autoGroupCard.at(i);
			groupKind = group->GetGroupKind();
			if (groupKind == EG_BIGGER) {
				if (group->GetMaxID() > groupCard->GetMaxID()) {
					return group->getListId();
				}
			}
		}
		// xem co tu quy hoac bon doi thong
		for (int i = 0; i < autoGroupCard.size(); i++) {
			TienlenGroupCard* group = autoGroupCard.at(i);
			groupKind = group->getTypeGroupCard();
			if (groupKind == EG_TU_QUY) {
				return group->getListId();
			}
		}
		for (int i = 0; i < autoGroupCard.size(); i++) {
			TienlenGroupCard* group = autoGroupCard.at(i);
			groupKind = group->GetGroupKind();
			if (groupKind == EG_SUPER || groupKind == EG_ULTRA) {
				return group->getListId();
			}
			else {
				return result;
			}
		}
		return result;
		break;
	case EG_SEQUENCE:
		for (int i = 0; i < autoGroupCard.size(); i++) {
			TienlenGroupCard* group = autoGroupCard.at(i);
			groupKind = group->GetGroupKind();
			if (groupKind == EG_SEQUENCE) {
				if (group->GetMaxID() > groupCard->GetMaxID()) {
					if (group->GetNumOfCards() <= groupCard->GetNumOfCards() + 1 && group->GetNumOfCards() >= groupCard->GetNumOfCards())
						return group->getMinSequenceGreater(groupCard);
					else if (minNumCard <= 3 && group->GetNumOfCards() >= groupCard->GetNumOfCards())
						return group->getMinSequenceGreater(groupCard);
				}
			}
		}
		if (minNumCard == 1) {
			for (int i = 0; i < GroupCards.size(); i++) {
				TienlenGroupCard *group = GroupCards.at(i);
				if (group->GetGroupKind() == EG_SEQUENCE && group->GetMaxID() > groupCard->GetMaxID() && group->GetNumOfCards() >= groupCard->GetNumOfCards()) {
					return group->getMinSequenceGreater(groupCard);
				}
			}
		}
		return result;
		break;
	case EG_NORMAL: {
		int d = -1;
		int start = autoGroupCard.size() - 1;
		int target = 0;
		if (groupCard->GetNumOfCards() >= nextCard) {
			d = 1;
			start = 0;
			target = autoGroupCard.size() - 1;
		}
		if (groupCard->GetNumOfCards() == 4) {
			// xem co tu quy hoac bon doi thong
			//for (int i = 0; i < autoGroupCard.size(); i++) {
			//	TienlenGroupCard* group = autoGroupCard.at(i);
			//	groupKind = group->getTypeGroupCard();
			//	if (groupKind == EG_TU_QUY) {
			//		// xem co phai tu quy lon hon khong
			//		if (group->GetMaxNumber() > groupCard->GetMaxNumber()) {
			//			return group->getListId();
			//		}
			//	}
			//}
			for (int i = 0; i < autoGroupCard.size(); i++) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->GetGroupKind();
				if (groupKind == EG_NORMAL && group->GetNumOfCards() == 4) {
					// xem co phai tu quy lon hon khong
					if (group->GetMaxNumber() > groupCard->GetMaxNumber()) {
						return group->getListId();
					}
				}
			}
			for (int i = 0; i < autoGroupCard.size(); i++) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->GetGroupKind();
				if (groupKind == EG_SUPER || groupKind == EG_ULTRA) {
					return group->getListId();
				}
				else {
					return result;
				}
			}
			return result;
		}
		else if (groupCard->GetNumOfCards() == 3) {
			for (int i = start; (i - target) * d <= 0; i = i + d) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->GetGroupKind();
				if (groupKind == EG_NORMAL && group->GetNumOfCards() == 3) {
					if (group->GetMaxNumber() > groupCard->GetMaxNumber()) {
						if (group->GetNumber() == 15) {
							// neu bang 2 thi can xet la o dau van thi khong can danh 2 luon hoac phai quan to thi moi danh 2
							if (minNumCard <= 2) {
								return group->getListId();
							}
						}
						else {
							return group->getListId();
						}
					}
				}
			}
		}
		else if (groupCard->GetNumOfCards() == 2) {
			if (groupCard->GetNumber() == 15) {
				// xem co tu quy hoac bon doi thong
				for (int i = start; (i - target) * d <= 0; i = i + d) {
					TienlenGroupCard* group = autoGroupCard.at(i);
					groupKind = group->getTypeGroupCard();
					if (groupKind == EG_TU_QUY) {
						return group->getListId();
					}
				}
				for (int i = start; (i - target) * d <= 0; i = i + d) {
					TienlenGroupCard* group = autoGroupCard.at(i);
					groupKind = group->GetGroupKind();
					if (groupKind == EG_SUPER || groupKind == EG_ULTRA) {
						return group->getListId();
					}
					else {
					}
				}
			}
			else {
				for (int i = start; (i - target) * d <= 0; i = i + d) {
					TienlenGroupCard* group = autoGroupCard.at(i);
					groupKind = group->GetGroupKind();
					if (groupKind == EG_NORMAL) {
						if (group->GetNumOfCards() == 2) {
							if (group->GetMaxID() > groupCard->GetMaxID()) {
								if (group->GetNumber() == 15) {
									if (GameLogic::getInstance()->isPosture) {
										return group->getListId();
									}
									else {
										// neu bang 2 thi can xet la o dau van thi khong can danh 2 luon hoac phai quan to thi moi danh 2
										if (minNumCard <= 2) {
											return group->getListId();
										}
									}
								}
								else {
									return group->getListId();
								}
							}
						}
						else {
							// tach ra tu bo 3 xem xet sau
							if (group->GetNumOfCards() == 3 && group->GetMaxID() > groupCard->GetMaxID()) {
								if (minNumCard <= 3 || GameLogic::getInstance()->isPosture) {
									return group->getMinPair();
								}
								else {

								}
							}
						}
					}
				}
			}
		}
		if (minNumCard == 1) {
			for (int i = 0; i < GroupCards.size(); i++) {
				TienlenGroupCard *group = GroupCards.at(i);
				if (group->GetGroupKind() == EG_NORMAL && group->GetMaxID() > groupCard->GetMaxID() && group->GetNumOfCards() >= groupCard->GetNumOfCards()) {
					if (groupCard->GetNumOfCards() == 3)
						return group->getListId();
					else
						return group->getMinPair();
				}
			}
		}
		return result;
		break;
	}
	case EG_ONECARD:
		if (groupCard->GetNumber() == 15) {
			// xem co ba doi thong
			for (int i = 0; i < autoGroupCard.size(); i++) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->GetGroupKind();
				if (groupKind == EG_BIGGER) {
					return group->getListId();
				}
			}
			// xem co tu quy hoac bon doi thong
			for (int i = 0; i < autoGroupCard.size(); i++) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->getTypeGroupCard();
				if (groupKind == EG_TU_QUY) {
					return group->getListId();
				}
			}
			for (int i = 0; i < autoGroupCard.size(); i++) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->GetGroupKind();
				if (groupKind == EG_SUPER || groupKind == EG_ULTRA) {
					return group->getListId();
				}
			}
			for (int i = autoGroupCard.size() - 1; i >= 0; i--) {
				TienlenGroupCard* group = autoGroupCard.at(i);
				groupKind = group->GetGroupKind();
				if (groupKind == EG_NORMAL) {
					if (group->GetNumOfCards() == 4) {
						return group->getListId();
					}
					else {
						if (group->GetMaxID() > groupCard->GetMaxID()) {
							// lay cay nho nhat
							result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
							return result;
						}
					}
				}
				else if (groupKind == EG_ONECARD) {
					if (group->GetMaxID() > groupCard->GetMaxID()) {
						return group->getListId();
					}
				}
			}
			return result;
		}
		else {
			if (minNumCard > 1) {
				for (int i = autoGroupCard.size() - 1; i >= 0; i--) {
					TienlenGroupCard* group = autoGroupCard.at(i);
					groupKind = group->GetGroupKind();
					if (groupKind == EG_ONECARD) {
						if (group->GetMaxID() > groupCard->GetMaxID()) {
							if (group->GetNumber() == 15) {
								// neu bang 2 thi can xet la o dau van thi khong can danh 2 luon hoac phai quan to thi moi danh 2
								if (minNumCard < 3) {
									// luon danh 2
									return group->getListId();
								}
								else if (minNumCard < 7) {
									// co ti le danh 2
									float rate = 0.3 * (groupCard->GetNumber() - 3) / 12;
									if (AXRANDOM_0_1() < 0.7 + rate) {
										return group->getListId();
									}
								}
								else {
									float rate = 0.4 * (groupCard->GetNumber() - 3) / 12;
									if (AXRANDOM_0_1() < 0.5 + rate) {
										return group->getListId();
									}
								}
							}
							else {
								return group->getListId();
							}
						}
					}
				}
				// cac truong hop pha ra tu doi, sanh, xam xet sau
				for (int i = autoGroupCard.size() - 1; i >= 0; i--) {
					TienlenGroupCard* group = autoGroupCard.at(i);
					groupKind = group->GetGroupKind();
					if (groupKind == EG_NORMAL) {
						if (group->GetNumOfCards() != 4 && group->GetMaxID() > groupCard->GetMaxID()) {
							if (group->GetNumber() == 15) {
								if (GameLogic::getInstance()->isPosture) {
									if (nextCard <= 3 || minNumCard == nextCard) {
										result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
									}
									return result;
								}
								else {
									// neu bang 2 thi can xet la o dau van thi khong can danh 2 luon hoac phai quan to thi moi danh 2
									if (minNumCard < 3 || group->GetNumOfCards() == 3) {
										// luon danh 2
										result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
										return result;
									}
									else if (minNumCard < 7) {
										// co ti le danh 2
										float rate = 0.2 * (groupCard->GetNumber() - 3) / 12;
										if (AXRANDOM_0_1() < 0.7 + rate) {
											result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
											return result;
										}
									}
									else {
										float rate = 0.3 * (groupCard->GetNumber() - 3) / 12;
										if (AXRANDOM_0_1() < 0.5 + rate) {
											result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
											return result;
										}
									}
								}
							}
							else {
								if (GameLogic::getInstance()->isPosture) {
									if (nextCard <= 3 || minNumCard == nextCard) {
										result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
									}
									return result;
								}
								else {
									float percentGet = (group->GetNumber() - 3) * 1.0f / 12;
									if (AXRANDOM_0_1() < percentGet) {
										result.push_back(group->getMinIdGreater(groupCard->GetMaxID()));
										return result;
									}
								}
							}
						}
					}
					else if (groupKind == EG_SEQUENCE) {
						if (group->GetMaxID() > groupCard->GetMaxID() && group->GetNumOfCards() > 3) {
							if (groupCard->GetNumber() >= 12) {
								if (AXRANDOM_0_1() < 0.5) {
									result.push_back(group->GetMaxID());
									return result;
								}
							}
							else {
								if (AXRANDOM_0_1() < 0.2) {
									result.push_back(group->GetMaxID());
									return result;
								}
							}
						}
					}
				}
			}
			else {
				int maxId = 0;
				for (int i = 0; i < autoGroupCard.size(); i++) {
					if (maxId < autoGroupCard.at(i)->GetMaxID()) {
						maxId = autoGroupCard.at(i)->GetMaxID();
					}
				}
				if (maxId > groupCard->GetMaxID()) {
					result.push_back(maxId);
					return result;
				}
			}
			return result;
		}
		break;
	default:
		break;
	}
	return result;
}

int TienlenPlayerCard::getSuddenWin()
{
	bool arrayNumber[16][5];
	int arrayNumber1[16];
	for (int i = 0; i < 16; i++) {
		arrayNumber1[i] = 0;
		for (int j = 0; j < 5; j++) {
			arrayNumber[i][j] = false;
		}
	}
	for (int i = 0; i < GroupCards.size(); i++) {
		vector<TienlenCard*> cards = GroupCards.at(i)->Cards;
		for (int j = 0; j < cards.size(); j++) {
			//arrayNumber[cards.at(j)->GetNumber()] = true;
			arrayNumber[cards.at(j)->GetNumber()][cards.at(j)->GetSuit()] == true;
			arrayNumber1[cards.at(j)->GetNumber()] = arrayNumber1[cards.at(j)->GetNumber()] + 1;
		}
	}

	// check sanh rong
	bool isSanhRong = true;
	for (int i = 3; i < 16; i++) {
		if (arrayNumber1[i] == false) {
			isSanhRong = false;
			break;
		}
	}
	if (isSanhRong)
		return ST_STRAIGHT;

	// check sau doi
	int count = 0;
	for (int i = 3; i < 16; i++) {
		count = count + arrayNumber1[i] / 2;
	}
	if (count == 6)
		return ST_SIXPAIR;

	// check tu quy 2
	if (arrayNumber1[15] == 4)
		return ST_FOUR_2;

	// check 5 doi thong
	autoArrange();
	for (int i = 0; i < autoGroupCard.size(); i++) {
		if (autoGroupCard.at(i)->GetGroupKind() == EG_ULTRA)
			return ST_ULTRA;
	}

	return ST_NONE;
}

int TienlenPlayerCard::getThoi()
{
	int count = 0;
	this->autoArrange();
	for (int i = 0; i < autoGroupCard.size(); i++) {
		TienlenGroupCard* group = autoGroupCard.at(i);
		count = count + TienlenRule::getThoi(group);
	}
	AXLOGD("COunt thoi %i ", count);
	return count;
}
