#include "Smoke.h"
#include "../Utility/GameUtility.h"
#include "../../Engine/GlobalVar.h"
#include "Game/GUIManager.h"


Smoke::Smoke(void) : GameImage()
{
	//setState(NORMAL);
    GameImage::setImage("swing/smoke0.png");
	frameTime = 0.015f;
	countTime = 0;
	frameTime = 0.2f;
	currentFrame = 0;
}

Smoke::Smoke(const char* nameImg, bool frame) : GameImage(nameImg, frame)
{
	string s(nameImg);
	nameImage = s;

	countTime = 0;
	frameTime = 0.2f;
	currentFrame = 0;

	
}


Smoke::~Smoke(void)
{
}

void Smoke::update()
{
	if(!getVisible())
		return;
	
	countTime = countTime + game->deltaTime;
	if(countTime > frameTime)
	{
		string s = "";
		countTime = 0;
		currentFrame = currentFrame + 1;

		if(currentFrame >= 9)
		{
			// remove
			setVisible(false);
			return;
		}
		else
		{
			s = "swing/smoke"  + GameUtility::toString(currentFrame) +".png";
                    GameImage::setImage(s.c_str());
		}
		
	}
		
		

}

void Smoke::start()
{
	setVisible(true);
	countTime = 0;
	currentFrame = 0;
        GameImage::setImage("swing/smoke0.png");
}

