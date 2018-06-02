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
		//���ù��ɶ����ж���Բ�Ƿ��ں�
		return (((position.x*position.x + position.y*position.y )< (r1 - r2)*(r1 - r2))&&r1>r2);
	}
	void eat(cocos2d::Node*);  //���ɲ���
	void move(cocos2d::Node*, float,float, const float);   //�ƶ�С�򼰱����������ƣ�
	void divide(cocos2d::Node*,float&);  //���Ѳ���
	void scalebg(cocos2d::Node*, float&, float); //��������
public:
	friend class GameScene;

	inline bool init(Circles* _circles, PlayerVector* _players) {
		circles = _circles;
		players = _players;
		return true;
	}
};