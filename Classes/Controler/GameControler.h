#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#define DEFAULTBGSCALE 4.0

//�����ٶȲ���Ĭ��ֵ
#define SPEEDPARAMETER 1.3
//�����Ե����Ĭ�Ͽ��
#define DEFAULTWIDTH 100.0f
//ö�ٱ�ǩ����
typedef enum
{
	bgTag = 110
	, controlerTag
	, playersTag
	, circlesTag
	, pausemenuTag
}Tag;

class GameControler:public cocos2d::Node
{
	BackGround *bg;
	//����洢��Ҫɾ����С�������
	cocos2d::Vector<Player*> toerase;

	inline bool isCircleCover(cocos2d::Vec2 position, float r1, float r2)
	{
		//���ù��ɶ����ж���Բ�Ƿ��ں�
		return (((position.x*position.x + position.y*position.y )< (r1 - r2)*(r1 - r2))&&r1>r2);
	}
	void eat(Circles*, PlayerVector*);  //���ɲ���
	void move(PlayerVector*,float &,float &);   //�ƶ�С�򼰱���
	void divide(PlayerVector*);  //���Ѳ���
	void scalebg(const float); //��������
	void combine(PlayerVector*);  //���С��֮��ĺϲ�
public:
	friend class GameScene;

	inline bool init();
	static GameControler* create(BackGround *);
};