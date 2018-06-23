#pragma once
#include"cocos2d.h"
//����Ĭ�ϱ�����С
#define DEFAULTBGSCALE 6.0

//�����Ե����Ĭ�Ͽ��
#define DEFAULTWIDTH 125.0f

class BackGround :public cocos2d::Sprite
{
	float backgroundscale= DEFAULTBGSCALE;
public:

	bool init();
	static BackGround* create();
	inline float& get_scale() {
		return backgroundscale;
	}
	inline const float& get_scale()const {
		return backgroundscale;
	}
};