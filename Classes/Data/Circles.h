#pragma once
#include"cocos2d.h"
//��������Ļ������С��
//�������С������
#define MAXCIRCLENUMBER 400
//����С��ߴ�
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