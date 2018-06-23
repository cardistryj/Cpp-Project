#pragma once
#include"cocos2d.h"
//定义默认背景大小
#define DEFAULTBGSCALE 6.0

//定义边缘刚体默认宽度
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