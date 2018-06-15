#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#define DEFAULTBGSCALE 4.0

//定义速度参数默认值
#define SPEEDPARAMETER 1.3
//定义边缘刚体默认宽度
#define DEFAULTWIDTH 100.0f
//枚举标签类型
typedef enum
{
	bgTag = 110
	, controlerTag
	, playersTag
	, circlesTag
	, pausemenuTag
}Tag;

class GameControler:public cocos2d::Node
{
	BackGround *bg;
	//定义存储将要删除的小球的容器
	cocos2d::Vector<Player*> toerase;

	inline bool isCircleCover(cocos2d::Vec2 position, float r1, float r2)
	{
		//运用勾股定理判断两圆是否内含
		return (((position.x*position.x + position.y*position.y )< (r1 - r2)*(r1 - r2))&&r1>r2);
	}
	void eat(Circles*, PlayerVector*);  //吞噬操作
	void move(PlayerVector*,float &,float &);   //移动小球及背景
	void divide(PlayerVector*);  //分裂操作
	void scalebg(const float); //放缩背景
	void combine(PlayerVector*);  //玩家小球之间的合并
public:
	friend class GameScene;

	inline bool init();
	static GameControler* create(BackGround *);
};