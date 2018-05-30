#pragma once
#include "cocos2d.h"

class Player:public cocos2d::Sprite
{
	float x = 0;
	float y = 0;
	float spritescale = 0.04;
public:
	friend class PlayerVector;
	friend class GameControler;

	virtual bool init();
	static Player* create();

	//CREATE_FUNC(MySprite);  
};