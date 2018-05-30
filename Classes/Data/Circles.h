#pragma once
#include"cocos2d.h"
//��������Ļ������С��
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