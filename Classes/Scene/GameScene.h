#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#include"GameControler.h"

class GameScene : public cocos2d::Scene
{

	//背景放缩比例
	float backgroundscale = 4;

	//关于移动背景的三个参数
	float x = 0;
	float y = 0;
	//r表示向量模长
	float r = 0;

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
