#pragma once
#include "cocos2d.h"
#include"PlayerVector.h"
//�������������������
class AllPlayersVector :public cocos2d::Node
{
	cocos2d::Vector<PlayerVector*> allPlayersVector;
	//�洢Ҫɾ�����������
	cocos2d::Vector<PlayerVector*> toerase;
	void combine(); //���С��֮��ĺϲ�
	bool check_playerdead();  //�����������������ֵ��ʾ��������Ƿ�����
	void action_end(Ref* pSender)
	{     //���ö���������ǩ
		Player* player = (Player*)pSender;
		player->if_action_end = true;
	}

	void erase_combined(); //ɾ�����ϲ��������С��
	void erase_eated(); //ɾ�������ɵ������С��
public:
	friend class GameControler;

	inline bool init();
	static AllPlayersVector* create();
	void init(BackGround*, int, cocos2d::Texture2D*); //��ʼ������
	bool if_survive() {
		auto players = *(allPlayersVector.begin());
		return allPlayersVector.size()==1 && !players->ifAIplayer;
	}
};
