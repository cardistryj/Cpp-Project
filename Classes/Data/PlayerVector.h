#pragma once
#include "cocos2d.h"
#include"Player.h"
#include"BackGround.h"

#define MAXPLAYERNUMBER 11
//�������
class PlayerVector:public cocos2d::Node
{
	cocos2d::Vector<Player*> playervector;
	//����洢��Ҫɾ����С�������
	cocos2d::Vector<Player*> toerase;
	//�����������С
	float sum_scale = 0;

	//����AI����йص���������
	//�����Ƿ���AI��ҵı�ǩ
	bool ifAIplayer;
	//�洢��AI�����ʳ������
	cocos2d::Vec2 closestfood;
	//�洢AI�ƶ�����ѵ�Ŀ�ĵ�����
	cocos2d::Vec2 desitination;
public:
	friend class GameControler;
	friend class AllPlayersVector;

	inline bool init();
	static PlayerVector* create(bool);
	void set_scale(); //����ƽ����С�ĺ���
};
