#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"VirusVector.h"
#include"AllPlayersVector.h"

//定义玩家总数量
#define MAXPLAYERSNUMBER 2

//存储控制游戏函数的类
class GameControler:public cocos2d::Node
{
	//存储分泌物的容器
	cocos2d::Vector<cocos2d::Sprite*> scretions;
	//即将被删除的分泌物的容器
	cocos2d::Vector<cocos2d::Sprite*> scretion_toerase;

	inline PlayerVector* get_humanplayers() {  //得到第一个玩家容器(默认情况下即为人类玩家)
		auto bg = (BackGround*)getChildByTag(bgTag);
		auto allplayersvector = (AllPlayersVector*)bg->getChildByTag(allplayersTag);
		return *(allplayersvector->allPlayersVector.begin());
	}
	inline void human_divide() {  //调用分裂函数
		get_humanplayers()->divide();
	}
	inline void human_spit() {   //调用分泌函数,将分泌物添加至容器中
		cocos2d::Vector<cocos2d::Sprite*> add_scretions;
		add_scretions = get_humanplayers()->spit();
		for (auto scretion : add_scretions)
			scretions.pushBack(scretion);
	}

	bool move(float &,float &);   //移动人类玩家及背景,返回值表示人类玩家是否唯一存活
	void move(float, float, PlayerVector*);  //移动AI玩家

	bool traverse(int);  //遍历玩家容器与食物、病毒、分泌物,返回人类玩家是否死亡
	float inter_traverse(); //在两个玩家容器之间遍历,返回第一个玩家的总质量（即默认情况下返回人类玩家质量）
	void virus_traverse(bool); //遍历病毒容器与分泌物，实现它们之间的操作

	void erase_scretion();  //删除分泌物
public:
	friend class GameScene;

	inline bool init();
	static GameControler* create();
};