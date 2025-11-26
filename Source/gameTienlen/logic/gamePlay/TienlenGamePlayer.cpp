#include "TienlenGamePlayer.h"


TienlenGamePlayer::TienlenGamePlayer(void)
{
	SuddenWin = ST_NONE;
}


TienlenGamePlayer::~TienlenGamePlayer(void)
{
}


	void TienlenGamePlayer::KiemTraBaiThoi(TienlenGroupCard* c)
	{
		int nFour = NumFour(c);
		int n3Pair = Num3DoiThong(c);
		if (nFour >= 2)
		{
			CheckFour(c);
			CheckThoiHai(c);
		}
		else if (n3Pair >= 2)
		{
			Thoi3DoiThong(c);
			CheckThoiHai(c);
		}
		else
		{
			int result = Check4_3(c);
			if (result == 0)
			{
				Thoi5DoiThong(c);
				Thoi4DoiThong(c);
				Thoi3DoiThong(c);
				CheckFour(c);
				CheckThoiHai(c);
			}
			else if (result == 1)
			{
				CheckFour(c);
				Thoi4DoiThong(c);
				CheckThoiHai(c);
			}
			else if (result == 2)
			{
				CheckFour(c);
				Thoi3DoiThong(c);
				CheckThoiHai(c);
			}
		}
	}
	int TienlenGamePlayer::getNumCard(int num,TienlenGroupCard* c)
	{
		int count = 0;
		for (int i = 0; i < c->GetNumOfCards(); i++)
		{
			if (c->Cards.at(i)->GetNumber() == num)
				count++;
		}
		return count;
	}
	
	int TienlenGamePlayer::NumFour(TienlenGroupCard* c)
	{
		if (c->GetNumOfCards() <= 3)
			return 0;
		int i,j;
		int num[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1};
		for (i = 0; i < c->GetNumOfCards(); i++)
		{
			if (c->Cards.at(i)->GetNumber() != 15)
				num[c->Cards.at(i)->GetNumber()]++;
		}
		int result = 0;
		for (i = 0; i < 13; i++)
		{
			if (num[i] >= 3)
			{
				result++;
			}
		}
		return result;
	}
	
	int TienlenGamePlayer::Num3DoiThong(TienlenGroupCard* c)
	{
		if (c->GetNumOfCards() < 6)
			return 0;
		int i, j, z;
		int n;
		int num[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0};
		int doi[16];
		int k = 0;
		int result = 0;
		for (i = 0; i < c->GetNumOfCards(); i++)
		{

			n = c->Cards.at(i)->GetNumber();
			num[n] = num[n] + 1;
			if (num[n] == 2)
				doi[k++] = n;
		}
		if (k >= 3)
		{
			for (i = 0; i < k - 1; i++)
			{
				for (j = i + 1; j < k; j++)
				{
					if (doi[i] < doi[j])
					{
						int tmp = doi[i];
						doi[i] = doi[j];
						doi[j] = tmp;
					}
				}
			}
			vector<int> Id;
			for (i = 0; i < k - 2; i++)
			{
				int add[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (doi[i] - doi[i + 2] == 2)
				{
					vector<int> gc;
					for (int x = doi[i]; x >= doi[i + 2]; x--)
					{
						for (j = 0; j < c->GetNumOfCards(); j++)
						{
							if (c->Cards.at(j)->GetNumber() == x && add[x] < 2)
							{
								bool b = false;
								for (z = 0; z < Id.size(); z++)
									if (Id.at(z) == c->Cards.at(j)->ID)
										b = true;
								if (!b)
								{
									gc.push_back(c->Cards.at(j)->ID);
									//WinCards.push(c->Cards[j]->ID);
									add[x]++;
								}
							}
						}
					}
					if (gc.size() == 6)
					{
						result++;
						for (j = 0; j < gc.size(); j++)
						{
							Id.push_back(gc.at(j));
						}
					}
				}
			}
		}
		return result;
	}
	int TienlenGamePlayer::Check4_3(TienlenGroupCard* c)
	{
		if (c->GetNumOfCards() < 10)
			return 0;
		int i, j;
		int n;
		int num[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0};
		int doi [16];
		int k = 0;
		int result = 0;
		for (i = 0; i < c->GetNumOfCards(); i++)
		{
			n = c->Cards.at(i)->GetNumber();
			num[n] = num[n] + 1;
			if (num[n] == 2)
				doi[k++] = n;
		}
		
		if (k >= 5)
		{
			for (i = 0; i < k - 1; i++)
			{
				for (j = i + 1; j < k; j++)
				{
					if (doi[i] < doi[j])
					{
						int tmp = doi[i];
						doi[i] = doi[j];
						doi[j] = tmp;
					}
				}
			}
			for (i = 0; i < k - 4; i++)
			{
				int add[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (doi[i] - doi[i + 4] == 4)
				{
					vector<int> gc;
					for (int x = doi[i]; x >= doi[i + 4]; x--)
					{
						for (j = 0; j < c->GetNumOfCards(); j++)
						{
							if (c->Cards.at(j)->GetNumber() == x && add[x] < 2)
							{
								if (!CardInWinCards(c->Cards.at(j)->ID))
								{
									//WinCards.push(c->Cards[j]->ID);
									gc.push_back(c->Cards.at(j)->ID);
									add[x]++;
								}
							}
						}
					}
					if (gc.size() == 10)
					{
						for (j = doi[i]; j >= doi[i+4]; j--)
						{
							int nc = getNumCard(j,c);
							if (nc != 4) 
								continue;
							if (j == doi[i] || j == doi[i+4])
							{
								result = 1;
								break;
							}
							else if (j == doi[i + 1] || j == doi[i + 3])
							{
								result = 2;
								break;
							}
						}
					}
				}
			}
		}
		return result;
	}
	bool TienlenGamePlayer::Thoi5DoiThong(TienlenGroupCard* c)
	{
		if (c->GetNumOfCards() <= 9)
			return false;
		int i, j;
		int n;
		int num[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0};
		int doi[16];
		int k=0;
		for (i = 0; i < c->GetNumOfCards(); i++)
		{
			n = c->Cards.at(i)->GetNumber();
			num[n] = num[n] + 1;
			if (num[n] == 2)
				doi[k++] = n;
		}
		if (k >= 5)
		{
			for (i = 0; i < k - 1; i++)
			{
				for (j = i + 1; j < k; j++)
				{
					if (doi[i] < doi[j])
					{
						int tmp = doi[i];
						doi[i] = doi[j];
						doi[j] = tmp;
					}
				}
			}
			for (i = 0; i < k - 4; i++)
			{
				int add[]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (doi[i] - doi[i + 4] == 4)
				{
					vector<int>gc;
					for (int x= doi[i]; x >= doi[i + 4]; x--)
					{
						for (j = 0; j < c->GetNumOfCards(); j++)
						{
							if (c->Cards.at(j)->GetNumber() == x && add[x] < 2)
							{
								if (!CardInWinCards(c->Cards.at(j)->ID))
								{
									//WinCards.push(c->Cards[j]->ID);
									gc.push_back(c->Cards.at(j)->ID);
									add[x]++;
								}
							}
						}
					}
					if (gc.size() == 10)
					{
						for (j = 0; j < gc.size(); j++)
						{
							WinCards.push_back(gc.at(j));
						}
					}
				}
			}
			if (WinCards.size() >= 10)
			{
				WinExcess.clear();
				for (j = 0; j < c->GetNumOfCards(); j++)
				{
					if (!CardInWinCards(c->Cards.at(j)->ID))
						WinExcess.push_back(c->Cards.at(j)->ID);
				}
				int t = 0;
				for (i = 0; i < c->Cards.size(); i++)
				{
					if(i<WinCards.size())
						c->Cards.at(i)->ID = WinCards.at(i);
					else if (t < WinExcess.size())
						c->Cards.at(i)->ID = WinExcess.at(t++);
				}
				return true;
			}
		}
		return false;
	}
	
	bool TienlenGamePlayer::Thoi4DoiThong(TienlenGroupCard* c)
	{
		if (c->GetNumOfCards() <= 7)
			return false;
		int i, j;
		int n;
		int num[]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0};
		int doi[16];
		int k=0;
		for (i = 0; i < c->GetNumOfCards(); i++)
		{
			n = c->Cards.at(i)->GetNumber();
			num[n] = num[n] + 1;
			if (num[n] == 2)
				doi[k++] = n;
		}
		if (k >= 4)
		{
			for (i = 0; i < k - 1; i++)
			{
				for (j = i + 1; j < k; j++)
				{
					if (doi[i] < doi[j])
					{
						int tmp= doi[i];
						doi[i] = doi[j];
						doi[j] = tmp;
					}
				}
			}
			for (i = 0; i < k - 3; i++)
			{
				int add[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (doi[i] - doi[i + 3] == 3)
				{
					vector<int> gc;
					for (int x= doi[i]; x >= doi[i + 3]; x--)
					{
						for (j = 0; j < c->GetNumOfCards(); j++)
						{
							if (c->Cards.at(j)->GetNumber() == x && add[x] < 2)
							{
								if (!CardInWinCards(c->Cards.at(j)->ID))
								{
									//WinCards.push(c->Cards[j]->ID);
									gc.push_back(c->Cards.at(j)->ID);
									add[x]++;
								}
							}
						}
					}
					if (gc.size() == 8)
					{
						for (j = 0; j < gc.size(); j++)
						{
							WinCards.push_back(gc.at(j));
						}
					}
				}
			}
			if (WinCards.size() >= 8)
			{
				WinExcess.clear();
				for (j = 0; j < c->GetNumOfCards(); j++)
				{
					if (!CardInWinCards(c->Cards.at(j)->ID))
						WinExcess.push_back(c->Cards.at(j)->ID);
				}
				int t = 0;
				
				for (i = 0; i < c->Cards.size(); i++)
				{
					if(i<WinCards.size())
					{
						c->Cards.at(i)->ID = WinCards.at(i);
						
					}
					else if (t < WinExcess.size())
					{
						c->Cards.at(i)->ID = WinExcess.at(t);
						
						t++;
					}
				}
				return true;
			}
		}
		return false;
	}
	
	bool TienlenGamePlayer::Thoi3DoiThong(TienlenGroupCard* c)
	{
		if (c->GetNumOfCards() <= 5)
			return false;
		int i, j;
		int n;
		int num[]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0};
		int doi[16];
		int k=0;
		for (i = 0; i < c->GetNumOfCards(); i++)
		{
			n = c->Cards.at(i)->GetNumber();
			num[n] = num[n] + 1;
			if (num[n] == 2)
				doi[k++] = n;
		}
		if (k >= 3)
		{
			for (i = 0; i < k - 1; i++)
			{
				for (j = i + 1; j < k; j++)
				{
					if (doi[i] < doi[j])
					{
						int tmp= doi[i];
						doi[i] = doi[j];
						doi[j] = tmp;
					}
				}
			}
			for (i = 0; i < k - 2; i++)
			{
				int add[]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (doi[i] - doi[i + 2] == 2)
				{
					vector<int> gc;
					for (int x = doi[i]; x >= doi[i + 2]; x--)
					{
						for (j = 0; j < c->GetNumOfCards(); j++)
						{
							if (c->Cards.at(j)->GetNumber() == x && add[x] < 2)
							{
								if (!CardInWinCards(c->Cards.at(j)->ID))
								{
									gc.push_back(c->Cards.at(j)->ID);
									add[x]++;
								}
							}
						}
					}
					if (gc.size()== 6)
					{
						for (j = 0; j < gc.size(); j++)
						{
							WinCards.push_back(gc.at(j));
						}
					}
				}
			}
			if (WinCards.size() >= 6)
			{
				WinExcess.clear();
				for (j = 0; j < c->GetNumOfCards(); j++)
				{
					if (!CardInWinCards(c->Cards.at(j)->ID))
						WinExcess.push_back(c->Cards.at(j)->ID);
				}
				int t = 0;
				
				for (i = 0; i < c->Cards.size(); i++)
				{
					if(i<WinCards.size())
					{
						c->Cards.at(i)->ID = WinCards.at(i);
						
					}
					else if (t < WinExcess.size())
					{
						c->Cards.at(i)->ID = WinExcess.at(t);
						
						t++;
					}
				}
				return true;
			}
		}
		return false;
	}

	bool TienlenGamePlayer::CardInWinCards(int ID) {
		for (int i = 0; i < WinCards.size(); i++) {
			if (WinCards.at(i) == ID)
				return true;
		}
		return false;
	}

	bool TienlenGamePlayer::CardInWinExcess(int ID) {
		for (int i = 0; i < WinExcess.size(); i++) {
			if (WinExcess.at(i) == ID)
				return true;
		}
		return false;
	}

	void TienlenGamePlayer::CheckFour(TienlenGroupCard* c) {

		if (c->GetNumOfCards() <= 3)
			return;
		int i, j;
		int num[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 , -1};
		for (i = 0; i < c->GetNumOfCards(); i++) {
			if (c->Cards.at(i)->GetNumber() != 15)
				num[c->Cards.at(i)->GetNumber()]++;
		}
		for (i = 0; i < 13; i++) {
			if (num[i] >= 3) {
				vector<int> gc;
				for (j = 0; j < c->GetNumOfCards(); j++) {
					if (c->Cards.at(j)->GetNumber() == i) {
						if (!CardInWinCards(c->Cards.at(j)->ID))
							// WinCards.push(c->Cards[j]->ID);
							gc.push_back(c->Cards.at(j)->ID);
					}
				}
				if (gc.size() == 4) {
					for (j = 0; j < gc.size(); j++)
						WinCards.push_back(gc.at(j));
				}
			}
		}
		int t = 0;
		if (WinCards.size() >= 4) {
			WinExcess.clear();
			for (j = 0; j < c->GetNumOfCards(); j++) {
				if (!CardInWinCards(c->Cards.at(j)->ID))
					WinExcess.push_back(c->Cards.at(j)->ID);
			}
			for (i = 0; i < c->Cards.size(); i++) {
				if (i < WinCards.size())
					c->Cards.at(i)->ID = WinCards.at(i);
				else if (t < WinExcess.size())
					c->Cards.at(i)->ID = WinExcess.at(t++);
			}
		}
	}

	void TienlenGamePlayer::CheckThoiHai(TienlenGroupCard* c) {
		// LostCards = new Vector.<int>();
		vector<int> gc;
		int i;
		for (i = 0; i < c->GetNumOfCards(); i++) {
			if (c->Cards.at(i)->GetNumber() == 15) {
				gc.push_back(c->Cards.at(i)->ID);
			}
		}

		int t = 0;
		if (gc.size() > 0) {
			WinExcess.clear();
			for (i = 0; i < gc.size(); i++) {
				WinCards.push_back(gc.at(i));
			}
			for (i = 0; i < c->GetNumOfCards(); i++) {
				if (!CardInWinCards(c->Cards.at(i)->ID)) {
					WinExcess.push_back(c->Cards.at(i)->ID);
				}
			}
			
			for (i = 0; i < c->Cards.size(); i++) {
				if (i < WinCards.size()) {
					c->Cards.at(i)->ID = WinCards.at(i);
				} else if (t < WinExcess.size()) {
					c->Cards.at(i)->ID = WinExcess.at(t);
					t++;
				}
			}
		}
	}

	// SAP XEP BAI KHI TOI TRANG :
	// Neu la sanh rong :

	void TienlenGamePlayer::CheckStraight(TienlenGroupCard* c) {
		for (int i = 0; i < c->GetNumOfCards(); i++) {
			WinCards.push_back(c->Cards.at(i)->ID);
		}
		WinExcess.clear();
		/*WinCards.push_back(c->Cards.at(0)->ID);
		int n = 0;
		for (int i = 1; i < c->GetNumOfCards(); i++) {
			if (c->Cards.at(i)->GetNumber() != 15) {
				n = WinCards.at(WinCards.size() - 1) / 4;
				if (c->Cards.at(i)->GetNumber() == n + 3 + 1) {
					WinCards.push_back(c->Cards.at(i)->ID);
				} else
					WinExcess.push_back(c->Cards.at(i)->ID);
			} else
				WinExcess.push_back(c->Cards.at(i)->ID);

		}

		for (int i = 0; i < c->Cards.size(); i++) {
			if (i <= 11)
				c->Cards.at(i)->ID = WinCards.at(i);
			else
				c->Cards.at(i)->ID = WinExcess.at(0);
		}
*/
	}

	void TienlenGamePlayer::CheckSixPair(TienlenGroupCard* c) {
		for (int i = 0; i < c->GetNumOfCards() - 1; i++) {
			if (c->Cards.at(i)->GetNumber() == c->Cards.at(i + 1)->GetNumber()) {
				WinCards.push_back(c->Cards.at(i)->ID);
				WinCards.push_back(c->Cards.at(i + 1)->ID);
				i++;
			}
		}

		bool kt = false;
		for (int i = 0; i < c->GetNumOfCards(); i++) {
			for (int j = 0; j < WinCards.size(); j++) {
				if (c->Cards.at(i)->ID == WinCards.at(j)) {
					kt = true;
					break;
				}
			}
			if (!kt)
				WinExcess.push_back(c->Cards.at(i)->ID);
			kt = false;
		}

		for (int i = 0; i < c->Cards.size(); i++) {
			if (i <= 11)
				c->Cards.at(i)->ID = WinCards.at(i);
			else
				c->Cards.at(i)->ID = WinExcess.at(0);
		}

	}

	void TienlenGamePlayer::CheckFour2(TienlenGroupCard* c) {
		WinCards.push_back(48);
		WinCards.push_back(49);
		WinCards.push_back(50);
		WinCards.push_back(51);

		for (int i = 0; i < c->Cards.size(); i++)
			if (c->Cards.at(i)->GetNumber() != 15)
				WinExcess.push_back(c->Cards.at(i)->ID);
		int k = 0;
		for (int i = 0; i < c->Cards.size(); i++) {
			if (i <= 3)
				c->Cards.at(i)->ID = WinCards.at(i);
			else
				c->Cards.at(i)->ID = WinExcess.at(k++);
		}
	}

	void TienlenGamePlayer::CheckFour3(TienlenGroupCard* c) {
		WinCards.push_back(0);
		WinCards.push_back(1);
		WinCards.push_back(2);
		WinCards.push_back(3);

		for (int i = 0; i < c->Cards.size(); i++)
			if (c->Cards.at(i)->GetNumber() != 3)
				WinExcess.push_back(c->Cards.at(i)->ID);
		int k = 0;
		for (int i = 0; i < c->Cards.size(); i++) {
			if (i <= 3)
				c->Cards.at(i)->ID = WinCards.at(i);
			else
				c->Cards.at(i)->ID = WinExcess.at(k++);
		}
	}
	/**
	 * Kiem tra lay ra 5 doi 
	 * @param c
	 */
	void TienlenGamePlayer::CheckUltra(TienlenGroupCard* c) {
		/*
		 * WinCards = new Vector.<int>(); WinExcess = new Vector.<int>();
		 * c->Cards.sort(GameLogic.SortCardsInGroup);
		 */
		for (int i = 0; i < c->Cards.size(); i++) {
			int size = c->Cards.size() - 2;
			if (i <= size) {
				if (c->Cards.at(i)->GetNumber() == c->Cards.at(i + 1)->GetNumber()) {
					WinCards.clear();
					WinCards.push_back(c->Cards.at(i)->ID);
					int k = 1;
					for (int j = i + 1; j < c->Cards.size(); j++) {
						int number = WinCards.at(WinCards.size() - 1) / 4 + 3;
						if (k == 1) // 1 card
						{
							if (c->Cards.at(j)->GetNumber() == number) {
								WinCards.push_back(c->Cards.at(j)->ID);
								k++;
								continue;
							} else {
								WinCards.pop_back();
								break;
							}
						}

						if (k == 2) // 2 card
						{
							if (c->Cards.at(j)->GetNumber() == number + 1) {
								WinCards.push_back(c->Cards.at(j)->ID);
								k--;
							}
						}
					}

					if (WinCards.size() == 10)
						break;
				}
			}
		}

		bool kt = false; // day nhung cay bai ko thuoc 5 doi thong vao
							// WinExcess
		for (int i = 0; i < c->GetNumOfCards(); i++) {
			for (int j = 0; j < WinCards.size(); j++) {
				if (c->Cards.at(i)->ID == WinCards.at(j)) {
					kt = true;
				}
			}

			if (!kt) {
				WinExcess.push_back(c->Cards.at(i)->ID);
			} else {
				kt = false;
			}

		}

		int t = 0;
		if (WinCards.size() == 10) // sap xep lai GourpCard C --> De sap xep
									// hien thi
			for (int i = 0; i < c->Cards.size(); i++)
				if (i <= 9)
					c->Cards.at(i)->ID = WinCards.at(i);
				else
					c->Cards.at(i)->ID = WinExcess.at(t++);
	}
	void TienlenGamePlayer::CheckSuper(TienlenGroupCard* c) {
		/*
		 * WinCards = new Vector.<int>(); WinExcess = new Vector.<int>();
		 * c->Cards.sort(GameLogic.SortCardsInGroup);
		 */
		for (int i = 0; i < c->Cards.size(); i++) {
			int size = c->Cards.size() - 2;
			if (i <= size) {
				if (c->Cards.at(i)->GetNumber() == c->Cards.at(i + 1)->GetNumber()) {
					WinCards.clear();
					WinCards.push_back(c->Cards.at(i)->ID);
					int k = 1;
					for (int j = i + 1; j < c->Cards.size(); j++) {
						int number = WinCards.at(WinCards.size() - 1) / 4 + 3;
						if (k == 1) // 1 card
						{
							if (c->Cards.at(j)->GetNumber() == number) {
								WinCards.push_back(c->Cards.at(j)->ID);
								k++;
								continue;
							} else {
								WinCards.pop_back();
								break;
							}
						}

						if (k == 2) // 2 card
						{
							if (c->Cards.at(j)->GetNumber() == number + 1) {
								WinCards.push_back(c->Cards.at(j)->ID);
								k--;
							}
						}
					}

					if (WinCards.size() == 8)
						break;
				}
			}
		}

		bool kt = false; // day nhung cay bai ko thuoc 5 doi thong vao
							// WinExcess
		for (int i = 0; i < c->GetNumOfCards(); i++) {
			for (int j = 0; j < WinCards.size(); j++) {
				if (c->Cards.at(i)->ID == WinCards.at(j)) {
					kt = true;
				}
			}

			if (!kt) {
				WinExcess.push_back(c->Cards.at(i)->ID);
			} else {
				kt = false;
			}

		}

		int t = 0;
		if (WinCards.size() == 8) // sap xep lai GourpCard C --> De sap xep
									// hien thi
			for (int i = 0; i < c->Cards.size(); i++)
				if (i <= 7)
					c->Cards.at(i)->ID = WinCards.at(i);
				else
					c->Cards.at(i)->ID = WinExcess.at(t++);
	}
	
	void TienlenGamePlayer::CheckBigger(TienlenGroupCard* c) {
		for (int i = 0; i < c->Cards.size(); i++) {
			int size = c->Cards.size() - 2;
			if (i <= size) {
				if (c->Cards.at(i)->GetNumber() == c->Cards.at(i + 1)->GetNumber()) {
					WinCards.clear();
					WinCards.push_back(c->Cards.at(i)->ID);
					int k = 1;
					for (int j = i + 1; j < c->Cards.size(); j++) {
						int number = WinCards.at(WinCards.size() - 1) / 4 + 3;
						if (k == 1) // 1 card
						{
							if (c->Cards.at(j)->GetNumber() == number) {
								WinCards.push_back(c->Cards.at(j)->ID);
								k++;
								continue;
							} else {
								WinCards.pop_back();
								break;
							}
						}

						if (k == 2) // 2 card
						{
							// if (c->Cards[j]->GetNumber() == number)
							// WinCards[WinCards.length - 1] = c->Cards[j]->ID;
							if (c->Cards.at(j)->GetNumber() == number + 1) {
								WinCards.push_back(c->Cards.at(j)->ID);
								k--;
							}
						}
					}

					if (WinCards.size() == 6)
						break;
				}
			}
		}

		bool kt = false; // day nhung cay bai ko thuoc 5 doi thong vao
							// WinExcess
		for (int i = 0; i < c->GetNumOfCards(); i++) {
			for (int j = 0; j < WinCards.size(); j++) {
				if (c->Cards.at(i)->ID == WinCards.at(j)) {
					kt = true;
				}
			}

			if (!kt) {
				WinExcess.push_back(c->Cards.at(i)->ID);
			} else {
				kt = false;
			}

		}

		int t = 0;
		if (WinCards.size() == 6) // sap xep lai GourpCard C --> De sap xep hien
									// thi
			for (int i = 0; i < c->Cards.size(); i++)
				if (i <= 5)
					c->Cards.at(i)->ID = WinCards.at(i);
				else
					c->Cards.at(i)->ID = WinExcess.at(t++);
	}
	