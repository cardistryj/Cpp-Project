#pragma once
#include "cocos2d.h"
//�����ʼС���������
#define STARTPLSCALE 0.05
//����С��ߴ�������
#define LOSINGSCALE 0.01
//���������Ĭ�Ϸ�������
#define SCRETIONSCALE 0.03

class Player:public cocos2d::Sprite
{
	//��ʾ����ƶ��Ĳ���
	float x = 0;
	float y = 0;
	float speed = 0;

	float spritescale = STARTPLSCALE;
	bool eated = false;//�ж��Ƿ�����
	bool combined = false; //�ж��Ƿ񱻺ϲ�
	bool if_action_end = true; //�ж��Ƿ��ڶ�����

	Player* playerclone(int i=1); //����ͬ�������С��
	void losingscale(); //�ߴ����
	virtual bool init();
public:
	friend class GameControler;
	friend class PlayerVector;

	static Player* create();
	//CREATE_FUNC(Player);  
};