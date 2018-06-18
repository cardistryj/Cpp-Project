#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#include"AllPlayersVector.h"

//定义玩家总数量
#define MAXPLAYERSNUMBER 4

//枚举标签类型
typedef enum
{
	bgTag = 110
	, controlerTag
	, allplayersTag
	, circlesTag
	, pausemenuTag
}Tag;
//存储控制游戏函数的类
class GameControler:public cocos2d::Node
{
	inline float lenth(cocos2d::Vec2 point) {
		return (sqrt(point.x*point.x + point.y*point.y));
	}
	inline float lenth(float x, float y) {
		return (sqrt(x*x + y*y));
	}
	inline bool isCircleCover(cocos2d::Vec2 position, float r1, float r2){
		//运用勾股定理判断两圆是否内含
		return ((lenth(position)< (r1 - r2))&&r1>r2);
	}
	bool if_attack(PlayerVector* , PlayerVector* ); //判断能否进行分裂攻击

	void move(float &,float &);   //移动人类玩家小球及背景
	void scalebg(const float); //放缩背景

	void divide(PlayerVector*);  //玩家分裂操作
	void combine();  //玩家小球之间的合并
	void traverse();  //遍历玩家容器与食物
	void eat(Player*, cocos2d::Sprite*);  //玩家与食物之间吞噬操作

	void inter_traverse(); //在两个玩家容器之间遍历
	void aiControl(PlayerVector*, PlayerVector*);	//控制AI玩家小球行为
	void move(float, float, PlayerVector*);  //移动AI小球
	void eat(PlayerVector*, PlayerVector*);  //玩家之间的吞噬

public:
	friend class GameScene;

	inline bool init();
	static GameControler* create();
};