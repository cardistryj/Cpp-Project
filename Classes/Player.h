#pragma once
#include "cocos2d.h"
#include"Circles.h"
//定义初始小球放缩参数
#define STARTPLSCALE 0.05f
//定义小球尺寸亏损参数
#define LOSINGSCALE 0.01f

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

	Player* playerclone(cocos2d::Texture2D* , int i = 1); //创建同样的玩家小球
	void losingscale(); //尺寸亏损，每做过一次动作之后即进行亏损
	virtual bool init(cocos2d::Texture2D*);

	inline void eat(Sprite* sprite)
	{ //玩家与食物之间吞噬
		auto bg = getParent();

		spritescale = BackGround::lenth(spritescale, CIRCLESCALE);
		runAction(cocos2d::ScaleTo::create(0.8f, spritescale / DEFAULTBGSCALE));
	}
	inline void eat_scretion()
	{//玩家与分泌物之间的吞噬
		spritescale = BackGround::lenth(spritescale, SCRETIONSCALE);
		losingscale();
		runAction(cocos2d::ScaleTo::create(0.8f, spritescale / DEFAULTBGSCALE));
	} 
public:
	friend class GameControler;
	friend class PlayerVector;
	friend class AllPlayersVector;

	static Player* create(cocos2d::Texture2D*);
	//CREATE_FUNC(Player);  
};