#pragma once
#include"cocos2d.h"
#include"BackGround.h"
//��������Ļ������С��
//�������С������
#define MAXCIRCLENUMBER 350
//����С��ߴ�
#define CIRCLESCALE 0.02

class Circles :public cocos2d::Node
{
	cocos2d::Vector<cocos2d::Sprite *> spriteVector;
public:
	friend class GameControler;

	Circles() = default;
	bool init();
	static Circles* create();
	void addcirclesto(BackGround*);
};