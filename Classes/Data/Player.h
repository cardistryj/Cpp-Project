#pragma once
#include "cocos2d.h"
#include"Circles.h"
//�����ʼС���������
#define STARTPLSCALE 0.05f
//����С��ߴ�������
#define LOSINGSCALE 0.01f

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

	Player* playerclone(cocos2d::Texture2D* , int i = 1); //����ͬ�������С��
	void losingscale(); //�ߴ����ÿ����һ�ζ���֮�󼴽��п���
	virtual bool init(cocos2d::Texture2D*);

	inline void eat(Sprite* sprite)
	{ //�����ʳ��֮������
		auto bg = getParent();

		spritescale = BackGround::lenth(spritescale, CIRCLESCALE);
		runAction(cocos2d::ScaleTo::create(0.8f, spritescale / DEFAULTBGSCALE));
	}
	inline void eat_scretion()
	{//����������֮�������
		spritescale = BackGround::lenth(spritescale, SCRETIONSCALE);
		losingscale();
		runAction(cocos2d::ScaleTo::create(0.8f, spritescale / DEFAULTBGSCALE));
	} 
public:
	friend class GameControler;
	friend class PlayerVector;
	friend class AllPlayersVector;

	static Player* create(cocos2d::Texture2D*);
	//CREATE_FUNC(Player);  
};