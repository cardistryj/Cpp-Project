#pragma once
#include "cocos2d.h"
//�����ʼС���������
#define STARTPLSCALE 0.04
class Player:public cocos2d::Sprite
{
	//��ʾ����ƶ��Ĳ���
	float x = 0;
	float y = 0;
	float spritescale = STARTPLSCALE;

	Player* playerclone(void);
public:
	friend class GameScene;
	friend class GameControler;
	friend class PlayerVector;

	virtual bool init();
	static Player* create();

	//CREATE_FUNC(MySprite);  
};