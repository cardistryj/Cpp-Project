#pragma once
#include "cocos2d.h"
//定义初始小球放缩参数
#define STARTPLSCALE 0.04
class Player:public cocos2d::Sprite
{
	//表示玩家移动的参量
	float x = 0;
	float y = 0;
	float spritescale = STARTPLSCALE;
	bool onbg = false;//判断小球是否还在bg上

	Player* playerclone(void);
public:
	friend class GameScene;
	friend class GameControler;
	friend class PlayerVector;

	virtual bool init();
	static Player* create();

	//CREATE_FUNC(MySprite);  
};