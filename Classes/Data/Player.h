#pragma once
#include "cocos2d.h"
//定义初始小球放缩参数
#define STARTPLSCALE 0.05
//定义小球尺寸亏损参数
#define LOSINGSCALE 0.01
//定义分泌物默认放缩参数
#define SCRETIONSCALE 0.03

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
	void losingscale(); //尺寸亏损
	virtual bool init();
public:
	friend class GameControler;
	friend class PlayerVector;

	static Player* create();
	//CREATE_FUNC(Player);  
};