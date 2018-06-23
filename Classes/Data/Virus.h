#pragma once
#include"cocos2d.h"
#include"BackGround.h"
//定义最大病毒数量
#define MAXVIRUSNUMBER 5
//定义病毒尺寸
#define VIRUSSCALE 0.1

class Virus :public cocos2d::Sprite
{
	float virusscale;
public:
	friend class GameControler;
	friend class VirusVector;

	inline bool init();
	static Virus* create();
	Virus* virus_clone();
};

