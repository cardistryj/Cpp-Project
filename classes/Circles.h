#pragma once
#include"cocos2d.h"
#include"BackGround.h"
//用于在屏幕上生成小球
//定义最大小球数量
#define MAXCIRCLENUMBER 150
//定义小球尺寸
#define CIRCLESCALE 0.02f

class Circles :public cocos2d::Node
{
	cocos2d::Vector<cocos2d::Sprite *> spriteVector;
public:
	friend class GameControler;

	Circles() = default;
	bool init(cocos2d::Texture2D*);
	static Circles* create(cocos2d::Texture2D*);
	void addcirclesto(BackGround*);
};