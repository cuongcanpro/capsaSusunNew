#include "MaubinhCardLogic.h"



MaubinhCardLogic::MaubinhCardLogic(void)
{
	ID = 52;
}


MaubinhCardLogic::~MaubinhCardLogic(void)
{
}

MaubinhCardLogic::MaubinhCardLogic(int id)
{
	ID = id;
}

/**
	 * Lấy số của quân bài
	 * 
	 * @return
	 */
	int MaubinhCardLogic::GetNumber() {
		// Convert code Binh
		return ID / 4 + 2;
	}

	/**
	 * Lấy chất của quân bài
	 * 
	 * @return
	 */
	int MaubinhCardLogic::GetSuit() {
		// Convert code Binh
		return (ID % 4 + 1);
	}

	void MaubinhCardLogic::SetCard(int n, int s) {
		// Convert code Binh
		ID = (n - 2) * 4 + (s - 1);
	}

	int MaubinhCardLogic::GetColor() {
		// Convert code Binh
		if (GetSuit() == ES_CLUB || GetSuit() == ES_SPADE)
			return EC_BLACK;
		if (GetSuit() == ES_DIAMOND || GetSuit() == ES_HEART)
			return EC_RED;
		return EC_UNDEFINED;
	}
