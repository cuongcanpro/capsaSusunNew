#ifndef ImageEffect_h
#define ImageEffect_h

#include "axmol.h"
//#include "Gui/Image.h"

#include <map>
#include "../Layers/GameLayer.h"

using namespace ax;

using namespace std;

class ImageEffect :
	public ax::Sprite {
public:
	ImageEffect();
	~ImageEffect();
	static ImageEffect* create();
	void initAnim();

	void initState();

	void initCoin(int type, int amoutLoop, float posX, float posY);

	void start();

	void stop();

	void repeat();

	void updateCoin(float dt);

public:
	int amoutLoop;
	bool isCollided;
	float opacity;
	float speedX;
	float speedY;
	float speedR;
	float valueRan;
	float rotation;

public:

	static const float SCALE_CHIP_RATE;
	static const int NUM_SPRITE_ANIMATION_COIN;
	static const std::string NAME_ANIMATION_COIN;
	static const float TIME_ANIMATION_COIN;
	static const float TYPE_FLOW;
	static const float TYPE_RAIN;

	static const float RATE_SPEED_Y;
	static const float DEFAULT_SPEED_Y;
	static const float RATE_SPEED_X;
	static const float RATE_SPEED_R;
	static const float RATE_Position_X;
	static const float RATE_Position_Y;
	static const float MIN_SCALE;
	static const float MAX_SCALE;
	static const float RATE_JUMP_BACK;
	static const float GRAVITY;
	static const float POSI;
	static const float NUM_COIN_EACH_TIME;
	static const float NUM_COIN_RATE_RAIN;
	static const float TIME_OUT_COIN;
	static const float DELAY_PLAY_SOUND;
};
#endif // BaseGUI_h__
