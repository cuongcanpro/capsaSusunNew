#ifndef TalaCard_h__
#define TalaCard_h__

class Card {
public:
	Card(int id=-1);
	~Card();

private:
	char id;
	bool eaten;

public:
	char getId();
	bool isValid();
	char getType();
	char getShape();
	bool isEaten();
	void setEaten(bool eaten);

public:
	enum CardType {
		typeA = 0,
		type2 = 1,
		type3 = 2,
		type4 = 3,
		type5 = 4,
		type6 = 5,
		type7 = 6,
		type8 = 7,
		type9 = 8,
		type10 = 9,
		typeJ = 10,
		typeQ = 11,
		typeK = 12
	};

	enum CardShape {
		shapeBICH = 0,
		shapeCHUON = 1,
		shapeRO = 2,
		shapeCO = 3
	};
};

#endif
