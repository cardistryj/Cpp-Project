#pragma once
#include "cocos2d.h"
#include"PlayerVector.h"
//管理所有玩家容器的类
class AllPlayersVector :public cocos2d::Node
{
	cocos2d::Vector<PlayerVector*> allPlayersVector;
	//存储要删除的玩家容器
	cocos2d::Vector<PlayerVector*> toerase;
	void combine(); //玩家小球之间的合并
	bool check_playerdead();  //检验玩家死亡，返回值表示人类玩家是否死亡

	void erase_combined(); //删除被合并掉的玩家小球
	void erase_eated(); //删除被吞噬掉的玩家小球
public:
	friend class GameControler;

	inline bool init();
	static AllPlayersVector* create();
	void init(BackGround*, int, cocos2d::Texture2D*); //初始化函数
};
