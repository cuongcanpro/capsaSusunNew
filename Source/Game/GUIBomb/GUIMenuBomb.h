#ifndef GUIMenuBomb_H
#define GUIMenuBomb_H

#include "../../Engine/GUI/BaseGUI.h"

using namespace ax::ui;
class GUIMenuBomb : public BaseGUI
{
private:
	Scale9Sprite* bg;
	BaseButton* arrayButton[4];
	BaseButton* btnClose, *btnNewGame;
	Text* arrayLabel[4];
public:
	int currentLevel;
public:
	void initGUI();
	void onButtonRelease(int buttonId, Touch* event);
	void hideGUI();
	void showGUI();
	void moveEffect(Node* node, int rate, float delay = 0);
	void loadSound();
	void updateCurrentLevel(int currentLevel);

    public:
        static std::string className;
};
#endif
