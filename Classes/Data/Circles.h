#pragma once
#include"cocos2d.h"
//用于在屏幕上生成小球
class Circles
{
	cocos2d::Vector<cocos2d::Sprite *> spriteVector;
	int maxCircleNumber = 100;
	float circleScale = 0.03;
public:
	friend class GameControler;

	Circles() = default;
	bool init();
	void addcirclesto(cocos2d::Sprite* bg,float backgroundscale);
};