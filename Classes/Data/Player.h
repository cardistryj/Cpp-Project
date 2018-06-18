#pragma once
#include "cocos2d.h"
//定义初始小球放缩参数
#define STARTPLSCALE 0.04

class Player:public cocos2d::Sprite
{
	//表示玩家移动的参量
	float x = 0;
	float y = 0;
	float speed = 0;

	float spritescale = STARTPLSCALE;
	bool onbg = true;//判断小球是否还在bg上

	Player* playerclone(void);
	virtual bool init();
public:
	friend class GameControler;
	friend class PlayerVector;

	static Player* create();
	//CREATE_FUNC(Player);  
};