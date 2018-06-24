#pragma once
#include "cocos2d.h"
#include"Player.h"
#include"BackGround.h"

#define MAXPLAYERNUMBER 21

class PlayerVector:public cocos2d::Node
{
	cocos2d::Vector<Player*> playervector;
public:
	friend class GameControler;

	inline bool init();
	static PlayerVector* create();
	bool init_on(BackGround*);
};
