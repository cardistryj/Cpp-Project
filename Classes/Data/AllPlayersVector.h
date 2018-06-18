#pragma once
#include "cocos2d.h"
#include"PlayerVector.h"
//管理所有玩家容器的类
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
