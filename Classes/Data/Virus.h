#pragma once
#include"cocos2d.h"
#include"BackGround.h"
//������󲡶�����
#define MAXVIRUSNUMBER 5
//���岡���ߴ�
#define VIRUSSCALE 0.1

class Virus :public cocos2d::Node
{
	cocos2d::Vector<cocos2d::Sprite*> virusvector;
public:
	friend class GameControler;

	inline bool init();
	static Virus* create();
	void addvirusto(BackGround*);
};

