#include "TienlenGroupCard.h"
#include "stdlib.h"
#include <algorithm>

TienlenGroupCard::TienlenGroupCard(void)
{
	
}


TienlenGroupCard::~TienlenGroupCard(void)
{
	for (int i = 0; i < Cards.size(); i++) {
		delete Cards.at(i);
	}
}



	/**
	 * @return So quan bai
	 */
	int TienlenGroupCard:: GetNumOfCards() {
		return Cards.size();
	}

	/**
	 * check co sau bo doi
	 * 
	 * @return
	 */
	bool TienlenGroupCard:: IsSixPair() {
		if (GetNumOfCards() < 12)
			return false;

		vector<TienlenCard*> tempCards;
		tempCards = Cards;

		// Sap xep lai Group
		for (int t = 0; t < GetNumOfCards() - 1; t++)
			for (int j = t + 1; j < GetNumOfCards(); j++) {
				if (tempCards.at(t)->GetNumber() > tempCards.at(j)->GetNumber()) {
					int temp = tempCards.at(t)->ID;
					tempCards.at(t)->ID = tempCards.at(j)->ID;
					tempCards.at(j)->ID = temp;
				}
			}

		if (GetNumOfCards() == 12) {
			{
				// Check if there are four two-cards groupcards:
				if (tempCards.at(0)->GetNumber() == tempCards.at(1)->GetNumber()) {
					if (tempCards.at(2)->GetNumber() == tempCards.at(3)->GetNumber()) {
						if (tempCards.at(4)->GetNumber() == tempCards.at(5)->GetNumber()) {
							if (tempCards.at(6)->GetNumber() == tempCards.at(7)->GetNumber()) {
								if (tempCards.at(8)->GetNumber() == tempCards.at(9)->GetNumber()) {
									if (tempCards.at(10)->GetNumber() == tempCards.at(11)->GetNumber()) {
										return true;
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

	/**
	 * 
	 * @return group thuoc loai nao
	 */
	int TienlenGroupCard::GetGroupKind() {
		if (GetNumOfCards() == 0)
			return EG_NONE;
		// NEU CHI CO 1 QUAN BAI
		if (GetNumOfCards() == 1)
			return EG_ONECARD;

		vector<TienlenCard*> tempCards;
		tempCards = Cards;
		// Sap xep lai Group
		for (int t = 0; t < GetNumOfCards() - 1; t++)
			for (int j = t + 1; j < GetNumOfCards(); j++) {
				if (tempCards.at(t)->GetNumber() > tempCards.at(j)->GetNumber()) {
					int temp = tempCards.at(t)->ID;
					tempCards.at(t)->ID = tempCards.at(j)->ID;
					tempCards.at(j)->ID = temp;
				}
			}
		// Check for super group card:
		if (GetNumOfCards() == 6) {
			if (tempCards.at(0)->GetNumber() != 15 &&
					tempCards.at(1)->GetNumber() != 15 &&
					tempCards.at(2)->GetNumber() != 15 &&
					tempCards.at(3)->GetNumber() != 15 &&
					tempCards.at(4)->GetNumber() != 15 &&
					tempCards.at(5)->GetNumber() != 15) {
				// Check if there are four two-cards groupcards:
				if (tempCards.at(0)->GetNumber() == tempCards.at(1)->GetNumber()) {
					if (tempCards.at(2)->GetNumber() == tempCards.at(3)->GetNumber()) {
						if (tempCards.at(4)->GetNumber() == tempCards.at(5)->GetNumber()) {

							// Check if they are next to each other:
							if (tempCards.at(0)->GetNumber() + 1 == tempCards.at(2)->GetNumber()) {
								if (tempCards.at(3)->GetNumber() + 1 == tempCards.at(4)->GetNumber()) {
									return EG_BIGGER;
								}
							}
						}

					}
				}
			}
		}
		// Check for super group card:
		if (GetNumOfCards() == 8) {
			if (tempCards.at(0)->GetNumber() != 15 &&
					tempCards.at(1)->GetNumber() != 15 &&
					tempCards.at(2)->GetNumber() != 15 &&
					tempCards.at(3)->GetNumber() != 15 &&
					tempCards.at(4)->GetNumber() != 15 &&
					tempCards.at(5)->GetNumber() != 15 &&
					tempCards.at(6)->GetNumber() != 15 &&
					tempCards.at(7)->GetNumber() != 15) {
				// Check if there are four two-cards groupcards:
				if (tempCards.at(0)->GetNumber() == tempCards.at(1)->GetNumber()) {
					if (tempCards.at(2)->GetNumber() == tempCards.at(3)->GetNumber()) {
						if (tempCards.at(4)->GetNumber() == tempCards.at(5)->GetNumber()) {
							if (tempCards.at(6)->GetNumber() == tempCards.at(7)->GetNumber()) {
								// Check if they are next to each other:
								if (tempCards.at(0)->GetNumber() + 1 == tempCards.at(2)->GetNumber()) {
									if (tempCards.at(3)->GetNumber() + 1 == tempCards.at(4)->GetNumber()) {
										if (tempCards.at(5)->GetNumber() + 1 == tempCards.at(6)->GetNumber()) {
											return EG_SUPER;
										}
									}
								}
							}
						}

					}
				}
			}
		} else if (GetNumOfCards() == 10) {
			if (tempCards.at(0)->GetNumber() != 15 &&
					tempCards.at(1)->GetNumber() != 15 &&
					tempCards.at(2)->GetNumber() != 15 &&
					tempCards.at(3)->GetNumber() != 15 &&
					tempCards.at(4)->GetNumber() != 15 &&
					tempCards.at(5)->GetNumber() != 15 &&
					tempCards.at(6)->GetNumber() != 15 &&
					tempCards.at(7)->GetNumber() != 15 &&
					tempCards.at(8)->GetNumber() != 15 &&
					tempCards.at(9)->GetNumber() != 15) {
				// Check if there are four two-cards groupcards:
				if (tempCards.at(0)->GetNumber() == tempCards.at(1)->GetNumber()) {
					if (tempCards.at(2)->GetNumber() == tempCards.at(3)->GetNumber()) {
						if (tempCards.at(4)->GetNumber() == tempCards.at(5)->GetNumber()) {
							if (tempCards.at(6)->GetNumber() == tempCards.at(7)->GetNumber()) {
								if (tempCards.at(8)->GetNumber() == tempCards.at(9)->GetNumber()) {
									// Check if they are next to each other:
									if (tempCards.at(0)->GetNumber() + 1 == tempCards.at(2)->GetNumber()) {
										if (tempCards.at(3)->GetNumber() + 1 == tempCards.at(4)->GetNumber()) {
											if (tempCards.at(5)->GetNumber() + 1 == tempCards.at(6)->GetNumber()) {
												if (tempCards.at(7)->GetNumber() + 1 == tempCards.at(8)->GetNumber()) {
													return EG_ULTRA;
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
		}

		// NEU NHIEU HON 1 QUAN BAI CHECK BO NORMAL la bo 22, 333, 4444, v.v...
		int Number;
		bool Normal = true;
		Number = Cards.at(0)->GetNumber();
		int i = 0;
		// Neu trong group, chi can mot con khac number voi cac con con` lai thi
		// khong phai bo normal
		for (i = 0; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetNumber() != Number)
				Normal = false;
		}
		// Neu group co 2 con giong nhau thi check xem co phai bo hay khong
		// Chi co 2 con do hoac 2 con den moi thanh mot bo. Con do hoac den se
		// la coc cach
		if (Normal && GetNumOfCards() == 2) {
			// Check don gian, Co = 1, Ro = 2, tep = 3, bich = 4
			// Vi the cong Suit voi nhau: Co + Ro = 2 + 1 = 3 ----- Bich + Tep =
			// 3 + 4 = 7
			// Neu cong Suit ma khac 3 va 7 thi do la bo coc cach
			// if(((int)Cards[0]->GetSuit() + (int)Cards[1]->GetSuit() == 3) ||
			// ((int)Cards[0]->GetSuit() + (int)Cards[1]->GetSuit() == 7))
			return EG_NORMAL;
			// else
			// return EG_NONE;
		}

		// Neu group co 3 hoac 4 con giong nhau thi do chac chan la bo
		if (Normal && GetNumOfCards() <= 4 && GetNumOfCards() >= 3)
			return EG_NORMAL;

		// Neu khong phai bo normal thi duoi 2 quan se chang la cai gi ca
		if (GetNumOfCards() < 3)
			return EG_NONE;

		// BAY GIO CHECK BO SEQUENCE
		// Neu tu 3 quan tro len, check co phai bo sequence hay khong
		int Suit;
		bool Sequence = true;

		// Sap xep lai Group
		for (i = 0; i < GetNumOfCards() - 1; i++)
			for (int j = i + 1; j < GetNumOfCards(); j++) {
				if (Cards.at(i)->GetNumber() > Cards.at(j)->GetNumber()) {
					int temp = Cards.at(i)->ID;
					Cards.at(i)->ID = Cards.at(j)->ID;
					Cards.at(j)->ID = temp;
				}
			}

		Number = Cards.at(0)->GetNumber();
		Suit = Cards.at(0)->GetSuit();

		// So 15 la quan 2. Neu trong group co 1 quan 2 thi no chac chan khong
		// phai bo sequence. Sequence
		// khong bao gio chua 2
		if (Number == 15)
			Sequence = false;

		// Chay tu dau den cuoi group, neu chi can mot con number khong tien len
		// hoac Suit khac di
		// thi khong phai sequence
		for (i = 1; i < GetNumOfCards(); i++) {
			if (Cards.at(i)->GetNumber() != Number + i)
				Sequence = false;
			// Neu trong group co 1 quan 2 thi do khong phai bo sequence
			if (Cards.at(i)->GetNumber() == 15)
				Sequence = false;

		}
		// Tra ve ket qua
		if (Sequence)
			return EG_SEQUENCE;
		else
			return EG_NONE;

	}

	// TLMN_EC
	int TienlenGroupCard:: GetNumber() {
		if (GetNumOfCards() == 0)
			return -1;
		if (GetGroupKind() == EG_ONECARD || GetGroupKind() == EG_NORMAL || GetGroupKind() == EG_SEQUENCE)
			return Cards.at(0)->GetNumber();
		if (GetGroupKind() == EG_BIGGER || GetGroupKind() == EG_SUPER || GetGroupKind() == EG_ULTRA) {
			int BiggestNumber = 0;
			for (int i = 0; i < Cards.size(); i++) {
				if (BiggestNumber < Cards.at(i)->GetNumber()) {
					BiggestNumber = Cards.at(i)->GetNumber();
					return BiggestNumber;
				}
			}
		}
		return -1;

	}

	int TienlenGroupCard:: GetSuit() {
		if (GetNumOfCards() == 0)
			return 0;
		int SuitNumber = 0;
		for (int i = 0; i < Cards.size(); i++) {
			SuitNumber += Cards.at(i)->GetSuit();
		}
		return SuitNumber;
	}

	int TienlenGroupCard:: GetBiggestSuit() {
		if (GetNumOfCards() == 0)
			return 0;
		int SuitNumber = 0;
		if (GetGroupKind() == EG_ONECARD) {
			SuitNumber = Cards.at(0)->GetSuit();
		} else if (GetGroupKind() == EG_NORMAL) {
			vector<TienlenCard*> tempCards;
			tempCards = Cards;
			// Sap xep lai Group
			for (int t = 0; t < GetNumOfCards() - 1; t++)
				for (int j = t + 1; j < GetNumOfCards(); j++) {
					if (tempCards.at(t)->GetSuit() < tempCards.at(j)->GetSuit()) {
						int temp = tempCards.at(t)->ID;
						tempCards.at(t)->ID = tempCards.at(j)->ID;
						tempCards.at(j)->ID = temp;
					}
				}
			return tempCards.at(0)->GetSuit();
		} else if (GetGroupKind() == EG_SEQUENCE || GetGroupKind() == EG_SUPER || GetGroupKind() == EG_BIGGER || GetGroupKind() == EG_ULTRA) {
			vector<TienlenCard*> tempCards;
			tempCards = Cards;
			// Sap xep lai Group
			for (int t = 0; t < GetNumOfCards() - 1; t++)
				for (int j = t + 1; j < GetNumOfCards(); j++) {
					if (tempCards.at(t)->GetNumber() < tempCards.at(j)->GetNumber()) {
						int temp = tempCards.at(t)->ID;
						tempCards.at(t)->ID = tempCards.at(j)->ID;
						tempCards.at(j)->ID = temp;
					}
				}
			return tempCards.at(0)->GetSuit();
		}
		return SuitNumber;
	}

	/**
	 * Them quan bai vao group
	 * 
	 * @param card
	 *            quan bai them vao
	 */
	void TienlenGroupCard::AddCard(TienlenCard* card) {
		Cards.push_back(card);
	}

	/**
	 * Go bo quan bai khoi bo bai
	 * 
	 * @param card
	 */
	void TienlenGroupCard::RemoveCard(TienlenCard* card) {
		if (GetNumOfCards() == 0)
			return;
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

	/**
	 * Kiem tra co con bich ko
	 * 
	 * @return
	 */
	bool TienlenGroupCard:: Has3Spade() {
		// Debug.trace("Check 3 spade: " + GetNumOfCards());
		if (GetNumOfCards() == 0)
			return false;
		for (int i = 0; i < Cards.size(); i++) {
			// Debug.trace("Card "+ Cards.at(i)->ID);
			if (Cards.at(i)->ID == 0)
				return true;
		}
		return false;
	}

	/**
	 * Kiem tra co 2 ko
	 * 
	 * @return
	 */
	bool TienlenGroupCard:: Has2() {
		if (GetNumOfCards() == 0)
			return false;
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->GetNumber() == 15)
				return true;
		}
		return false;
	}

	bool TienlenGroupCard:: HasTuQuy() {
		if (GetNumOfCards() != 4)
			return false;
		for (int i = 0; i < 3; i++) {
			if (Cards.at(i)->GetNumber() != Cards.at(i + 1)->GetNumber())
				return false;
		}
		return true;
	}
	bool TienlenGroupCard:: HasDoiThong() {
		int groupKind = GetGroupKind();
		if (groupKind == EG_BIGGER || groupKind == EG_SUPER || groupKind == EG_ULTRA) {
			return true;
		}
		return false;
	}

	vector<int> TienlenGroupCard::getListId() {
		
		vector<int> arrId;
		for (int i = 0; i < Cards.size(); i++) {
			arrId.push_back(Cards.at(i)->ID);
		}
		std::sort(arrId.begin(), arrId.end());
		return arrId;
	}

	bool TienlenGroupCard:: searchCard(TienlenCard* card) {
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->ID == card->ID) {
				return true;
			}
		}
		return false;
	}

	void TienlenGroupCard::addCardInHead(TienlenCard* card) {
		vector<TienlenCard*> TempCards;
		for (int i = 0; i < Cards.size(); i++) {
			TempCards.push_back(Cards.at(i));
		}
		
		Cards.clear();
		Cards.push_back(card);
		for (int i = 0; i < TempCards.size(); i++) {
			Cards.push_back(TempCards.at(i));
		}
	}

	/**
	 * 
	 * @param inc
	 *            true: sap xep tang dan
	 */
	void TienlenGroupCard::Sort(bool inc) // true sap xep tang dan - false sap xep giam
									// dan
	{
		for (int i = 0; i < Cards.size(); i++) {
			for (int j = i; j < Cards.size(); j++) {
				if ((inc && Cards.at(j)->compare(Cards.at(i)) < 0) || (!inc && (Cards.at(j)->compare(Cards.at(i)) > 0))) {
					swap(Cards.at(i), Cards.at(j));
				}
			}
		}
	}

	int TienlenGroupCard:: GetCountCard(int number) // ham tra ve so card cung number
	{
		if (GetNumOfCards() == 0)
			return -1;
		int count = 0;
		for (int i = 0; i < Cards.size(); i++) {
			if (number == Cards.at(i)->GetNumber()) {
				++count;
			}
		}
		return count;
	}

	int TienlenGroupCard:: GetMaxID() // ham tra ve ID lon nhat
	{
		if (GetNumOfCards() == 0)
			return -1;
		int BiggestID = -1;
		for (int i = 0; i < Cards.size(); i++) {
			if (BiggestID < Cards.at(i)->ID) {
				BiggestID = Cards.at(i)->ID;
			}
		}
		return BiggestID;
	}

	int TienlenGroupCard:: GetMinID() // ham tra ve ID lon nhat
	{
		if (GetNumOfCards() == 0)
			return -1;
		int MinID = 52; // ID quan bai tu 0 den 51
		for (int i = 0; i < Cards.size(); i++) {
			if (MinID > Cards.at(i)->ID) {
				MinID = Cards.at(i)->ID;
			}
		}
		return MinID;
	}

	int TienlenGroupCard:: GetMaxNumber() // ham tra ve Number lon nhat
	{
		if (GetNumOfCards() == 0)
			return -1;
		int BiggestID = -1;
		for (int i = 0; i < Cards.size(); i++) {
			if (BiggestID < Cards.at(i)->GetNumber()) {
				BiggestID = Cards.at(i)->GetNumber();
			}
		}
		return BiggestID;
	}

	int TienlenGroupCard:: GetMinNumber() // ham tra ve Number lon nhat
	{
		if (GetNumOfCards() == 0)
			return -1;
		int MinNumBer = 16; // quan bai co number tu 3-15
		for (int i = 0; i < Cards.size(); i++) {
			if (MinNumBer > Cards.at(i)->GetNumber()) {
				MinNumBer = Cards.at(i)->GetNumber();
			}
		}
		return MinNumBer;
	}

	void TienlenGroupCard::RemoveAllCards() {
		for (int i = 0; i < Cards.size(); i++) {
			delete Cards.at(i);
		}
		while (GetNumOfCards() > 0)
			Cards.clear();
	}

	bool TienlenGroupCard:: CheckDoubleCardID(int ID) {
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->ID == ID) {
				return true;
			}
		}
		return false;
	}

	bool TienlenGroupCard:: CheckDoubleCardNumber(int num) {
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->GetNumber() == num) {
				return true;
			}
		}
		return false;
	}

	std::string TienlenGroupCard::toString() {
		
		return "No cards";
		
	}

	void TienlenGroupCard::setCard(vector<int> id) {
		Cards.clear();
		for (int i = 0; i < id.size(); i++) {
			TienlenCard* card = new TienlenCard();
			card->ID = id[i];
			Cards.push_back(card);
		}
	}

	void TienlenGroupCard::addCardToTest() {
		vector<TienlenCard*> listRandomCards;
		for (int i = 0; i < 52; i++) {
			TienlenCard* card = new TienlenCard();
			card->ID = i;
			listRandomCards.push_back(card);
		}
		int limit = 51;
		for (int i = 0; i < 13; i++) {
			int rand1 = (int) (rand() % limit);
			limit--;
			Cards.push_back(listRandomCards.at(rand1));
			if(rand1 > 0)
				listRandomCards.erase(listRandomCards.begin() + rand1 - 1);
			else
				listRandomCards.erase(listRandomCards.begin());
		}
	}

	void TienlenGroupCard::addCardWithIDs(vector<int> arrID) {
		
		for (int i = 0; i < arrID.size(); i++) {
			TienlenCard* card = new TienlenCard();
			card->ID = arrID.at(i);
			Cards.push_back(card);
		}
	}

	int TienlenGroupCard:: getTypeGroupCard() {
		int result = GetGroupKind();
		if (result == EG_SUPER || result == EG_ULTRA || result == EG_BIGGER)
			return result;

		if (HasTuQuy())
			return EG_TU_QUY;

		int count = 0;
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->ID > 47 && Cards.at(i)->ID < 52)
				count++;
		}
		if (count == 2)
			return EG_DOI_HAI;

		if (count == 3)
			return EG_BA_CON_HAI;

		return EG_NONE;
	}

	bool TienlenGroupCard::canWithoutTurn()
	{
		int groupKind = GetGroupKind();
		if (groupKind == EG_SUPER || groupKind == EG_ULTRA || groupKind == EG_BIGGER || groupKind == EG_TU_QUY ||
			(Cards[0]->GetNumber() == 15 && Cards.size() <= 2)) {
			return true;
		}
		return false;
	}

	int TienlenGroupCard::getMinIdGreater(int id)
	{
		int MinID = 52;
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards.at(i)->ID > id && Cards.at(i)->ID < MinID) {
				MinID = Cards.at(i)->ID;
			}
		}
		return MinID;
	}

	std::vector<int> TienlenGroupCard::getMinSequenceGreater(TienlenGroupCard* group)
	{
		int i;
		vector<int> result;
		for (i = Cards.size() - 1; i >= 0 && i >= group->GetNumOfCards() - 1; i--) {
			if (Cards.at(i)->ID < group->GetMaxID()) {
				break;
			}
		}
		i++;
		for (int j = 0; j < group->GetNumOfCards(); j++) {
			result.push_back(Cards.at(i - j)->ID);
		}
		std::sort(result.begin(), result.end());
		return result;
	}

	std::vector<int> TienlenGroupCard::getMinPair()
	{
		vector<int> result;
		result.push_back(Cards.at(Cards.size() - 1)->ID);
		result.push_back(Cards.at(Cards.size() - 2)->ID);
		return result;
	}
