#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"Virus.h"
#include"PlayerVector.h"
#include"AllPlayersVector.h"

//定义玩家总数量
#define MAXPLAYERSNUMBER 6

//枚举标签类型
typedef enum
{
	bgTag = 110
	, controlerTag
	, allplayersTag
	, circlesTag
	, pausemenuTag
	,scorelabelTag
	,virusTag
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
	void action_end(Ref* pSender); //设置能否合并标签

	bool if_attack(PlayerVector* , PlayerVector* ); //判断能否进行分裂攻击

	void move(float &,float &);   //移动人类玩家小球及背景
	void scalebg(const float); //放缩背景
	bool check_playerdead();  //检验玩家死亡，返回人类玩家是否死亡

	void divide(PlayerVector*);  //玩家分裂操作
	void combine();  //玩家小球之间的合并
	void traverse();  //遍历玩家容器与食物
	void eat(PlayerVector*,Player*, cocos2d::Sprite*);  //玩家与食物之间吞噬操作
	void erase_combined();  //删除被合并掉的玩家小球

	void erase_eated();  //删除被吞噬掉的玩家小球
	float inter_traverse(); //在两个玩家容器之间遍历,返回人类玩家的总面积
	void eat_player(PlayerVector*, PlayerVector*);  //玩家之间的吞噬
	void aiControl(PlayerVector*, PlayerVector*);	//控制AI玩家小球的行为
	void move(float, float, PlayerVector*);  //移动AI小球

public:
	friend class GameScene;

	inline bool init();
	static GameControler* create();
};