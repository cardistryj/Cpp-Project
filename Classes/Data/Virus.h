#pragma once
#include"cocos2d.h"
#include"BackGround.h"
//������󲡶�����
#define MAXVIRUSNUMBER 5
//���岡���ߴ�
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

