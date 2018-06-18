#pragma once
#include "cocos2d.h"
#include"PlayerVector.h"
//�������������������
class AllPlayersVector :public cocos2d::Node
{
	cocos2d::Vector<PlayerVector*> allPlayersVector;
public:
	friend class GameControler;
	friend class GameScene;

	inline bool init();
	static AllPlayersVector* create();
	void init(BackGround*,int);
};
