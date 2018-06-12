#pragma once
#include"cocos2d.h"
#define DEFAULTBGSCALE 4.0

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