#pragma once
#ifndef ConfigDataBlock_h__
#define ConfigDataBlock_h__

class ConfigDataBlock
{
public:
	ConfigDataBlock();
	~ConfigDataBlock();
	static const int NUM_ROW = 9;
	static const int NUM_COLUMN = 9;
	static float VELOCITY;
	static float TIME_GEN;
	static float TIME_GEN_BREAK;
	static float FREEZE_RATE;
	static float TIME_BONUS;
	static const int MAX_CIRCLE = 5;
	static const int MAX_BIG_CIRCLE = 5;
	static float RATE_NEXT_CELL;
	static float RATE_CURRENT_NEXT_CELL;
	static float RATE_NORMAL_CELL;
};
#endif // ConfigDataBlock_h__

