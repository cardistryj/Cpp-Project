#pragma once
#include"cocos2d.h"
#include"BackGround.h"
//������󲡶�����
#define MAXVIRUSNUMBER 5
//���岡���ߴ�
#define VIRUSSCALE 0.1f

class Virus :public cocos2d::Sprite
{
	float virusscale;
public:

	inline bool init(cocos2d::Texture2D*);
	static Virus* create(cocos2d::Texture2D*);
	Virus* virus_clone(cocos2d::Texture2D*);
	float& get_scale(){
		return virusscale;
	}
};

