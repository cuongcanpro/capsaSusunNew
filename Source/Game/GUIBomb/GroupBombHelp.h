#ifndef GroupBombHelp_H
#define GroupBombHelp_H

#include "../../Engine/GUI/BaseGUI.h"


using namespace ax::ui;
#define HELP_TOUCH_TO_OPEN 0
#define HELP_ONE_BOMB 1
#define HELP_GUESS_ONE_BOMB 2
#define HELP_TWO_BOMB 3
#define HELP_GUESS_TWO_BOMB 4
#define HELP_GUESS_THIRD_BOMB 5
#define HELP_GUESS_FOUR_BOMB 6

enum HelpType {
	HELP_OPEN,
	HELP_GUESS
};
class GroupBombHelp : public Node
{
public:
	GroupBombHelp(void);
	~GroupBombHelp(void);
	int indexHelp;
	void showHelp(Vec2 pos, float delayTime);
	bool checkCanAction(int row, int column, HelpType type);
	void hideHelp();
private:
	Scale9Sprite* bg;
	Sprite* iconHand;
	Sprite* iconRect;
	Sprite* touchEffect[3];
	Text* lbHelp;
	Button* btnNext;
	Vec2 currentPos;
	void showNext(float delayTime);
	void actionNext();

	void showHand();
	void showHandHold(float delayTime);
	void showRect(float delayTime);
	void effectTouch(Node* sender);

};
#endif
