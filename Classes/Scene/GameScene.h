#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#include"GameControler.h"

class GameScene : public cocos2d::Scene
{

	//背景放缩比例
	float backgroundscale = DEFAULTBGSCALE;
	//背景标签
	int bgTag = 111;

	//关于移动背景和屏幕中心的三个参数
	float x = 0;
	float y = 0;

	Circles  circles;
	PlayerVector players;
	GameControler gamecontroler;
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void update(float dt) override;

	// a selector callback
	void menuReturnCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};
