#pragma once
#include "cocos2d.h"
//定义初始小球放缩参数
#define STARTPLSCALE 0.05

class Player:public cocos2d::Sprite
{
	//表示玩家移动的参量
	float x = 0;
	float y = 0;
	float speed = 0;

	float spritescale = STARTPLSCALE;
	bool eated = false;//判断是否被吞噬
	bool combined = false; //判断是否被合并
	bool if_action_end = true; //判断是否还在动画中

	Player* playerclone(int i=1); //创建同样的玩家小球
	virtual bool init();
public:
	friend class GameControler;
	friend class PlayerVector;

	static Player* create();
	//CREATE_FUNC(Player);  
};