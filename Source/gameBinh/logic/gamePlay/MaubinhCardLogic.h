#pragma once
#ifndef MaubinhCardLogic_h__
#define MaubinhCardLogic_h__

#include "axmol.h"

#define CS_ON_HAND 0
#define CS_ON_CHOOSE 1
#define CS_ON_FLYING 2
#define CS_ON_DRAG 3
#define CS_ON_DROP 4
#define CS_ON_ENEMY_HAND 5
#define CS_UP 6
#define CS_DOWN 7

// Card Suit:
#define ES_HEART 4
#define ES_DIAMOND 3
#define ES_CLUB 2
#define ES_SPADE 1

// Card color:
#define EC_RED 0
#define EC_BLACK 1
#define EC_UNDEFINED 2

using namespace ax;
class MaubinhCardLogic
{
public:
	MaubinhCardLogic(void);
	~MaubinhCardLogic(void);

	MaubinhCardLogic(int id);
	int ID;

	/**
	 * Lấy số của quân bài
	 * 
	 * @return
	 */
	int GetNumber();
	/**
	 * Lấy chất của quân bài
	 * 
	 * @return
	 */
	int GetSuit();

	void SetCard(int n, int s);

	int GetColor();

};
#endif // MaubinhCardLogic_h__

