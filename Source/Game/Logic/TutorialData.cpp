#include "TutorialData.h"

TutorialData::TutorialData(int row, int column, float timeDelay, std::string content)
{
	this->row = row;
	this->column = column;
	this->timeDelay = timeDelay;
	this->content = content;
}


TutorialData::~TutorialData(void)
{
}
