#include "StickMan.h"
#include "../Utility/GameUtility.h"
#include "../../Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "../Utility/GameSound.h"

StickMan::StickMan(void) : GameImage()
{
	setState(NORMAL);
	countTime = 0;
	frameTime = 0.06f;
	currentFrame = 0;
	distance = 0;
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	speed = size.width * 0.025f;
}

StickMan::StickMan(const char* nameImg, bool frame) : GameImage(nameImg, frame)
{
	string s(nameImg);
	nameImage = s;

	countTime = 0;
	frameTime = 0.2f;
	currentFrame = 0;
	distance = 0;
	Size size = Director::getInstance()->getRenderView()->getVisibleSize();
	speed = size.width * 0.003f;
}


StickMan::~StickMan(void)
{
}

void StickMan::update()
{
	if(!getVisible())
		return;
	if(state == NORMAL)
		return;
	countTime = countTime + game->deltaTime;
	if(countTime > frameTime)
	{
		countTime = 0;
		currentFrame = currentFrame + 1;
	
		string s = "";
		if(state == RUN)
		{
				if(currentFrame > 13)
				{
					currentFrame = 0;
					
				}
				if(currentFrame % 4 == 0)
				{
					GUIManager::getInstance().guiSwing->makeSmoke();
                    
				}

				s = "swing/stick"  + GameUtility::toString(currentFrame) +".png";
				setPositionX(getPositionX() - speed);
				distance = distance + speed;
		}
		else
		{
			if(currentFrame > 5)
			{
				setState(NORMAL);
				return;
			}

			s = "swing/run_"  + GameUtility::toString(currentFrame + 10) +".png";
		}
		
		
		setImage(s.c_str());
	}
		
		

}

void StickMan::setState( StickManState _state, float _frameTime)
{
	state = _state;
	currentFrame = 0;
	countTime = 0;
	distance = 0;
//	frameTime = _frameTime;

	if(_state == NORMAL)
	{
		setImage("swing/stick0.png");
	}
	else if(_state == RUN)
	{
		setImage("swing/stick0.png");
	}
	else
	{
		setImage("swing/stick0.png");
	}
	
	
}

void StickMan::setImage( const char* nameImg )
{

		//string s(nameImg);
		//nameImage = s;
    GameImage::setImage(nameImg);
		setOpacity(150);
}

