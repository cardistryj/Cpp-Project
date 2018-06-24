#pragma once
#include "cocos2d.h"
#include"Player.h"
#include"VirusVector.h"

#define MAXPLAYERNUMBER 11

//�������
class PlayerVector:public cocos2d::Node
{
	cocos2d::Vector<Player*> playervector;
	//����洢��Ҫɾ����С�������
	cocos2d::Vector<Player*> toerase;
	//�����������С
	float sum_scale = 0;

	void divide();  //��ҷ��Ѳ���
	cocos2d::Vector<cocos2d::Sprite*> spit(); //��ҷ��ڷ�����,�������ӵķ���������
	void eat_virus(Player*, Virus*);  //����벡��֮�����ɣ���Ҫ��player vector�����Ԫ�أ�
	void eat_player(PlayerVector*);  //���֮�������
    void action_end(Ref* pSender)
	{     //���ö���������ǩ
		Player* player = (Player*)pSender;
		player->if_action_end = true;
	}

	//AI������
	//�����Ƿ���AI��ҵı�ǩ
	bool ifAIplayer;
	//�洢��AI�����ʳ������
	cocos2d::Vec2 closestfood;
	//�洢Ŀ�ĵ�����
	cocos2d::Vec2 desitination;

	bool if_attack(PlayerVector*); 	//�ж�AI�ܷ���з��ѹ���
    bool aiControl(PlayerVector*);  //����AI���С�����Ϊ,����ֵ�������Ƿ��и�������
public:
	friend class GameControler;
	friend class AllPlayersVector;

	inline bool init();
	static PlayerVector* create(bool);
	void set_scale(); //����ƽ����С�ĺ���
};