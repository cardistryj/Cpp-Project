#pragma once
#include "cocos2d.h"
#include"Player.h"
#include"VirusVector.h"

#define MAXPLAYERNUMBER 11

//玩家容器
class PlayerVector:public cocos2d::Node
{
	cocos2d::Vector<Player*> playervector;
	//定义存储将要删除的小球的容器
	cocos2d::Vector<Player*> toerase;
	//定义总面积大小
	float sum_scale = 0;

	void divide();  //玩家分裂操作
	cocos2d::Vector<cocos2d::Sprite*> spit(); //玩家分泌分泌物,返回增加的分泌物容器
	void eat_virus(Player*, Virus*);  //玩家与病毒之间吞噬（需要在player vector中添加元素）
	void eat_player(PlayerVector*);  //玩家之间的吞噬
    void action_end(Ref* pSender)
	{     //设置动作结束标签
		Player* player = (Player*)pSender;
		player->if_action_end = true;
	}

	//AI玩家相关
	//定义是否是AI玩家的标签
	bool ifAIplayer;
	//存储离AI最近的食物坐标
	cocos2d::Vec2 closestfood;
	//存储目的地坐标
	cocos2d::Vec2 desitination;

	bool if_attack(PlayerVector*); 	//判断AI能否进行分裂攻击
    bool aiControl(PlayerVector*);  //控制AI玩家小球的行为,返回值代表附近是否有更大的玩家
public:
	friend class GameControler;
	friend class AllPlayersVector;

	inline bool init();
	static PlayerVector* create(bool);
	void set_scale(); //计算平均大小的函数
};