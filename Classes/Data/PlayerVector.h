#pragma once
#include "cocos2d.h"
#include"Player.h"

class PlayerVector
{
	cocos2d::Vector<Player*> playervector;
public:
	friend class GameScene;
	friend class GameControler;

	bool init_on(cocos2d::Sprite*, float);
	//��������С�����Ӻ���
};
