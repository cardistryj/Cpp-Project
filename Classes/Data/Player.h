#pragma once
#include "cocos2d.h"
//�����ʼС���������
#define STARTPLSCALE 0.04

class Player:public cocos2d::Sprite
{
	//��ʾ����ƶ��Ĳ���
	float x = 0;
	float y = 0;
	float speed = 0;

	float spritescale = STARTPLSCALE;
	bool eated = false;//�ж��Ƿ�����
	bool combined = false; //�ж��Ƿ񱻺ϲ�
	bool can_combine = true; //�ж��ܷ񱻺ϲ�

	Player* playerclone(void);
	virtual bool init();
public:
	friend class GameControler;
	friend class PlayerVector;

	static Player* create();
	//CREATE_FUNC(Player);  
};