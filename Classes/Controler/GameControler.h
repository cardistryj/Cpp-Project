#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#define DEFAULTBGSCALE 4.0

class GameControler
{
	Circles*  circles;
	PlayerVector* players;
	inline bool isCircleCover(cocos2d::Vec2 position, float r1, float r2)
	{
		//运用勾股定理判断两圆是否内含
		return (((position.x*position.x + position.y*position.y )< (r1 - r2)*(r1 - r2))&&r1>r2);
	}
	void eat(cocos2d::Node*);  //吞噬操作
	void move(cocos2d::Node*, float,float, const float);   //移动小球及背景（待完善）
	void divide(cocos2d::Node*,float&);  //分裂操作
	void scalebg(cocos2d::Node*, float&, float); //放缩背景
public:
	friend class GameScene;

	inline bool init(Circles* _circles, PlayerVector* _players) {
		circles = _circles;
		players = _players;
		return true;
	}
};