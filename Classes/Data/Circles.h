#pragma once
#include"cocos2d.h"
//用于在屏幕上生成小球
//定义最大小球数量
#define MAXCIRCLENUMBER 400
//定义小球尺寸
#define CIRCLESCALE 0.02

class Circles
{
	cocos2d::Vector<cocos2d::Sprite *> spriteVector;
public:
	friend class GameControler;

	Circles() = default;
	bool init();
	void addcirclesto(cocos2d::Sprite* bg,float backgroundscale);
};