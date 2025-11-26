#include "TienlenGameLogic.h"

int TienlenGameLogic::CurrentArrangeMode = 0;
TienlenGameLogic::TienlenGameLogic(void)
{
	CurrentArrangeMode = 0;
}


TienlenGameLogic::~TienlenGameLogic(void)
{
}

	/**
	 * Sap xep list Group card
	 * 
	 * @param listGroup
	 * @param inc
	 *            true: sap xep tang dan 
	 *            false: sap xep giam dan
	 */
	vector<TienlenGroupCard*> TienlenGameLogic::sortGroupCards(vector<TienlenGroupCard*> listGroup, bool inc) {
		for (int i = 0; i < listGroup.size(); i++) {
			for (int j = i; j < listGroup.size(); j++) {
				int result = CompareGroupCards(listGroup.at(i), listGroup.at(j));
				if ((result > 0 && inc) || (result < 0 && !inc)) {
				
					swap(listGroup.at(i), listGroup.at(j));
				}
			}
		}
		return listGroup;
	}
	/**
	 * Sap xep list Group card
	 * 
	 * @param listGroup
	 * @param inc
	 *            true: sap xep tang dan 
	 *            false: sap xep giam dan
	 */
	vector<TienlenGroupCard*> TienlenGameLogic::sortGroupCardsByNumber(vector<TienlenGroupCard*> listGroup, bool inc) {
		for (int i = 0; i < listGroup.size(); i++) {
			for (int j = i; j < listGroup.size(); j++) {
				
				int result = CompareGroupCardsByNumber(listGroup.at(i), listGroup.at(j));
				if ((result > 0 && inc) || (result < 0 && !inc)) {
					
					swap(listGroup.at(i), listGroup.at(j));
				}
			}
		}
		return listGroup;
	}

	/**
	 * So sanh 2 nhom bai
	 * 
	 * @param GroupCard1
	 * @param GroupCard2
	 * @return -1 neu GroupCard1 nho hon 
	 * 			1 neu GroupCard2 lon hon hoac bang
	 */
	int TienlenGameLogic::CompareGroupCards(TienlenGroupCard* GroupCard1, TienlenGroupCard* GroupCard2) {
		int GroupCardValue[] = { 0, 0 };

		for (int i = 0; i < GroupCard1->Cards.size(); i++) {
			GroupCardValue[0] += GroupCard1->Cards.at(i)->GetNumber();
		}

		for (int i = 0; i < GroupCard2->Cards.size(); i++) {
			GroupCardValue[1] += GroupCard2->Cards.at(i)->GetNumber();
		}

		// Xep doi thong dau tien
		if (GroupCard1->HasDoiThong() && !GroupCard2->HasDoiThong())
			return -1;
		else if (!GroupCard1->HasDoiThong() && GroupCard2->HasDoiThong())
			return 1;
		// Xep tu quy dau tien
		else if (GroupCard1->HasTuQuy() && !GroupCard2->HasTuQuy())
			return -1;
		else if (!GroupCard1->HasTuQuy() && GroupCard2->HasTuQuy())
			return 1;
		else if (GroupCard1->HasTuQuy() && GroupCard2->HasTuQuy()) {
			if (GroupCardValue[0] < GroupCardValue[1]) {
				return -1;
			} else {
				return 1;
			}
		}

		if (GroupCard1->GetNumOfCards() == GroupCard2->GetNumOfCards()) {
			if (GroupCardValue[0] == GroupCardValue[1]) {
				// These groupcards are equal in value, check their suit
				if (GroupCard1->GetSuit() < GroupCard2->GetSuit()) {
					return -1;
				} else {
					return 1;
				}
			} else {
				if (GroupCardValue[0] < GroupCardValue[1]) {
					return -1;
				} else {
					return 1;
				}
			}
		} else {
			if (GroupCard1->GetNumOfCards() > GroupCard2->GetNumOfCards()) {
				return -1;
			} else {
				return 1;
			}
		}
	}
	vector<TienlenCard*> TienlenGameLogic::sortCards(vector<TienlenCard*> listCard, bool inc) {
		for (int i = 0; i < listCard.size(); i++) {
			for (int j = i; j < listCard.size(); j++) {
				int result = CompareCardsInGroup(listCard.at(i), listCard.at(j));
				if ((result > 0 && inc) || (result < 0 && !inc)) {
					swap(listCard.at(i), listCard.at(j));
				}
			}
		}
		return listCard;
	}
	/**
	 * So sanh 2 quan bai voi nhau
	 * 
	 * @param Card1
	 * @param Card2
	 * @return -1 neu Card1 nho hon 1 neu Card1 lon hon hoac bang
	 */
	int TienlenGameLogic::CompareCardsInGroup(TienlenCard* Card1, TienlenCard* Card2) {
		if (Card1->GetNumber() == Card2->GetNumber()) {
			// These cards are equal in value, check their suit
			if (Card1->GetSuit() < Card2->GetSuit()) {
				return -1;
			} else {
				return 1;
			}
		} else {
			if (Card1->GetNumber() < Card2->GetNumber()) {
				return -1;
			} else {
				return 1;
			}
		}
	}

	// Moi groupcard chi 1 la', dung de sap xep bo bai theo suit.
	int TienlenGameLogic::CompareGroupCardsBySuit(TienlenGroupCard* GroupCard1, TienlenGroupCard* GroupCard2) {
		if (GroupCard1->GetSuit() == GroupCard2->GetSuit()) {
			if (GroupCard1->GetNumber() < GroupCard1->GetNumber())
				return -1;
			else
				return 1;
		} else {
			if (GroupCard1->GetSuit() < GroupCard2->GetSuit())
				return -1;
			else
				return 1;
		}
	}

	// Moi groupcard chi 1 la', dung de sap xep bo bai theo number.
	int TienlenGameLogic::CompareGroupCardsByNumber(TienlenGroupCard* GroupCard1, TienlenGroupCard* GroupCard2) {
		if (GroupCard1->GetNumber() == GroupCard2->GetNumber()) {
			if (GroupCard1->GetSuit() < GroupCard2->GetSuit())
				return -1;
			else
				return 1;
		} else {
			if (GroupCard1->GetNumber() < GroupCard2->GetNumber())
				return -1;
			else
				return 1;
		}
	}
	void TienlenGameLogic::ScanGroupCardNormal(TienlenPlayerCard* PlayerCards){
		CurrentArrangeMode = AM_NORMAL;
		ScanGroupCard(PlayerCards,CurrentArrangeMode);
		CurrentArrangeMode++;
		CurrentArrangeMode %= 2;
	}
	void TienlenGameLogic::ScanGroupCardAuto(TienlenPlayerCard* PlayerCards) {
		ScanGroupCard(PlayerCards,CurrentArrangeMode);
		CurrentArrangeMode++;
		CurrentArrangeMode %= 2;
	}
	void TienlenGameLogic::ScanGroupCard(TienlenPlayerCard *PlayerCards, int arrangeMode) {
		// Create a temporary set of cards identical to that of player:
		vector<TienlenCard*> TempCards;
		TienlenPlayerCard* CurrentPlayerCards = PlayerCards;

		for (int i = 0; i < CurrentPlayerCards->GetNumOfGroupCards(); i++) {
			for (int j = 0; j < CurrentPlayerCards->GroupCards.at(i)->Cards.size(); j++) {
				TempCards.push_back(CurrentPlayerCards->GroupCards.at(i)->Cards.at(j));
			}
		}
		// Create a temporary group card and a result group card array:
		vector<TienlenGroupCard*> SortGroupCard;
		vector<TienlenGroupCard*> GroupCardResult;

		switch (arrangeMode) {
		case AM_NORMAL:
		// Duyệt Kiểm tra tứ quý. Ưu tiên xếp tứ quý trước
		{
			TienlenGroupCard* fourGroupCard;
			int cardFound;
			int cardsNumber[4];
			if (TempCards.size() > 3) {
				for (int i = 0; i < TempCards.size(); i++) {
					fourGroupCard = new TienlenGroupCard();
					
					cardFound = 0;
					fourGroupCard->Cards.clear();
					for (int temp = 0; temp < 4; temp++)
						cardsNumber[temp] = 0;
					fourGroupCard->AddCard(TempCards.at(i));
					cardsNumber[cardFound] = i;

					for (int j = i + 1; j < TempCards.size(); j++) {
						if (TempCards.at(i)->GetNumber() == TempCards.at(j)->GetNumber()) {
							fourGroupCard->AddCard(TempCards.at(j));
							cardFound++;
							cardsNumber[cardFound] = j;
						}

						if (fourGroupCard->GetNumOfCards() == 4) {
							GroupCardResult.push_back(fourGroupCard);
							for (int temp = 0; temp < 4; temp++) {
								TempCards.erase(TempCards.begin() + cardsNumber[temp]);

								//TempCards.er
								if (temp < 3) {
									cardsNumber[temp + 1] -= 1 + temp;
								}
							}
							break;
						}
					}
				}
			}

			// Sắp xếp các Sảnh.
			TienlenGroupCard* tempGroupCard;
			TienlenCard* cardNumber;
			TienlenGroupCard* insertGroup;
			TienlenGroupCard* groupDoiThong;
			int t = 0;
			while (TempCards.size() > 2) {
				SortGroupCard.clear();
				TempCards = sortCards(TempCards,true);
				for (int i = 0; i < TempCards.size(); i++) {
					
				}
				for (int i = 0; i < TempCards.size(); i++) {
					tempGroupCard = new TienlenGroupCard();
					cardNumber = new TienlenCard();
					t = 0;
					tempGroupCard->Cards.clear();
					cardNumber = TempCards.at(i);
					tempGroupCard->AddCard(cardNumber);
					for (int j = i + 1; j < TempCards.size(); j++) {
						if (TempCards.at(j)->GetNumber() < 15) // sảnh không
																// chứa 2.
																// (getNumber()
																// = 15)
						{
							if (TempCards.at(j)->GetNumber() == cardNumber->GetNumber() + 1)// tao
							{
								cardNumber = TempCards.at(j);
								tempGroupCard->AddCard(cardNumber);
								t = j;
							}

						}
					}

					if (tempGroupCard->GetNumOfCards() >= 3) {
						int size = TempCards.size() - 1;
						if (t < size) {
							while (TempCards.at(t)->GetNumber() == TempCards.at(t + 1)->GetNumber()) {
								tempGroupCard->Cards.pop_back();
								tempGroupCard->Cards.push_back(TempCards.at(t + 1));
								t++;
								if (t == size)
									break;
							}
						}
						SortGroupCard.push_back(tempGroupCard);
					}
				}

				// tim cac group doi thong.

				for (int i = 0; i < TempCards.size(); i++) {
					int size = TempCards.size() - 2;
					if (i <= size) {
						if (TempCards.at(i)->GetNumber() == TempCards.at(i + 1)->GetNumber()) {
							groupDoiThong = new TienlenGroupCard();
							groupDoiThong->AddCard(TempCards.at(i));
							int k = 1;
							for (int j = i + 1; j < TempCards.size(); j++) {
								if (k == 1) // da co' 1 card
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

								if (k == 2) // da~ co' 2 card
								{
									// if (TempCards[j]->GetNumber() ==
									// groupDoiThong->Cards[groupDoiThong->Cards.length
									// - 1]->GetNumber())
									// groupDoiThong->Cards[groupDoiThong->Cards.length
									// - 1] = TempCards[j];
									if (TempCards.at(j)->GetNumber() == groupDoiThong->Cards.at(groupDoiThong->Cards.size() - 1)->GetNumber() + 1&&
											TempCards.at(j)->GetNumber() <15) {
										groupDoiThong->AddCard(TempCards.at(j));
										k--;
									}
								}
							}

							if (groupDoiThong->GetNumOfCards() >= 6) { // doi
																		
								// trace("conghoaxahoichunghia + " +
								// groupDoiThong->GetNumOfCards());
								if (groupDoiThong->GetNumOfCards() % 2 == 0)
									SortGroupCard.push_back(groupDoiThong);
								else
								// nếu truong hop co le so card thi card cuoi
								// cung bi thua.
								{
									groupDoiThong->Cards.pop_back();
									SortGroupCard.push_back(groupDoiThong);
								}

							}
						}
					}
				}
//				System.out.print("TempCards1: ");
//				for(int i = 0;i<TempCards.size();i++){
//					System.out.print(""+TempCards.at(i)->GetNumber()+"-"+TempCards.at(i).GetSuit()+",");
//				}
//				Log.println("");
				// xam co, doi
				if (SortGroupCard.size() >= 1) {
					SortGroupCard = sortGroupCards(SortGroupCard, true);
					//SortGroupCard.sort(SortGroupCards);
					insertGroup = new TienlenGroupCard();
					insertGroup = SortGroupCard.at(0);
					SortGroupCard.erase(SortGroupCard.begin());
					// insertGroup = SortGroupCard.shift();
					GroupCardResult.push_back(insertGroup);

					for (int i = 0; i < insertGroup->GetNumOfCards(); i++) {
						for (int j = 0; j < TempCards.size(); j++) {
							if (TempCards.at(j)->ID == insertGroup->Cards.at(i)->ID) {
								TempCards.erase(TempCards.begin() + j);
								break;
							}
						}
					}
				} else
					break;

			}
//			System.out.print("TempCards2: ");
//			for(int i = 0;i<TempCards.size();i++){
//				System.out.print(""+TempCards.at(i)->GetNumber()+"-"+TempCards.at(i).GetSuit()+",");
//			}
//			Log.println("");
			// cho card khong thuoc groud nao vao.
			int j;
			if (TempCards.size() > 2) {
//				TempCards.sort(SortCardsInGroup);
				TempCards = sortCards(TempCards, true);
				for (int i = 0; i < TempCards.size();) {
					tempGroupCard = new TienlenGroupCard();
					// tempGroupCard->Cards.length = 0;
					tempGroupCard->Cards.clear();
					tempGroupCard->AddCard(TempCards.at(i));
					for (j = i + 1; j < TempCards.size(); j++) {

						if (TempCards.at(i)->GetNumber() == TempCards.at(j)->GetNumber()) {
							tempGroupCard->AddCard(TempCards.at(j));
						} else {
							break;
						}
					}
					i = j;
					GroupCardResult.push_back(tempGroupCard);
				}
				//GroupCardResult.sort(SortGroupCards);
				SortGroupCard = sortGroupCards(SortGroupCard, true);
			} else if (TempCards.size() > 0) {
				//TempCards.sort(SortCardsInGroup);
				TempCards = sortCards(TempCards, true);
				for (int i = 0; i < TempCards.size(); i++) {
					tempGroupCard = new TienlenGroupCard();
					// tempGroupCard->Cards.size() = 0;
					tempGroupCard->Cards.clear();
					// insertTempCard = new Card();
					// insertTempCard = TempCards[i];
					tempGroupCard->AddCard(TempCards.at(i));
					GroupCardResult.push_back(tempGroupCard);
				}
				GroupCardResult = sortGroupCards(GroupCardResult, true);
//				GroupCardResult.sort(SortGroupCards);
			}
			GroupCardResult = sortGroupCards(GroupCardResult, true);
		}
			break;
		/*
		 * case AM_SUIT: { Sort the cards: CGroupCard TempGroupCard; for (int
		 * i=0;i<TempCards.size();i++) { tempGroupCard->Cards.clear();
		 * tempGroupCard->AddCard(CCard(TempCards[i].ID));
		 * GroupCardResult.push_back(TempGroupCard);
		 * sort(GroupCardResult.begin(), GroupCardResult.end(),
		 * SortGroupCardsBySuit); } } break;
		 */

		case AM_NUMBER: {
			// Sort the cards:
			for (int i = 0; i < TempCards.size(); i++) {
				TienlenGroupCard* TempGroupCard = new TienlenGroupCard();
				// tempGroupCard->Cards.size() = 0;
				TempGroupCard->Cards.clear();
				TienlenCard* insertTempCard = new TienlenCard();
				insertTempCard->ID = TempCards.at(i)->ID;
				TempGroupCard->AddCard(insertTempCard);
				GroupCardResult.push_back(TempGroupCard);
				GroupCardResult = sortGroupCardsByNumber(GroupCardResult,true);
			//	GroupCardResult.sort(SortGroupCardsByNumber);
			}
		}
			break;
		}
		// Replace the cards in player's hand with the one on GroupCardResult
		// Just in case the groupcard is empty, which should not happened, but
		// a vanguard, nothing will change.
		if (GroupCardResult.size() > 0) {
//			sortGroupCards(GroupCardResult, true);
			// sort the GroupCardResult, look better:
			for (int i = 0; i < GroupCardResult.size(); i++) {
				GroupCardResult.at(i)->Cards = sortCards(GroupCardResult.at(i)->Cards, true);
			}
			// clear the player's cards
			// & replace with the GroupCardResult
			CurrentPlayerCards->Clear();
			CurrentPlayerCards->GroupCards = GroupCardResult;
			
		}
	}
