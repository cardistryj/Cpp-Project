#pragma once
#include "cocos2d.h"
#include"Player.h"
#include"BackGround.h"

#define MAXPLAYERNUMBER 11
//玩家容器
class PlayerVector:public cocos2d::Node
{
	cocos2d::Vector<Player*> playervector;
	//定义存储将要删除的小球的容器
	cocos2d::Vector<Player*> toerase;
	//定义总面积大小
	float sum_scale = 0;

	//仅与AI玩家有关的两个参数
	//定义是否是AI玩家的标签
	bool ifAIplayer;
	//存储离AI最近的食物坐标
	cocos2d::Vec2 closestfood;
	//存储AI移动或分裂的目的地坐标
	cocos2d::Vec2 desitination;
public:
	friend class GameControler;
	friend class AllPlayersVector;

	inline bool init();
	static PlayerVector* create(bool);
	void set_scale(); //计算平均大小的函数
};
