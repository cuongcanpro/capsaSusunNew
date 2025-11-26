#pragma once
#include <string>

class TutorialData
{
public:
	TutorialData(int row, int column, float timeDelay, std::string content);
	~TutorialData(void);
	int row, column;
	float timeDelay;
	std::string content;
};

