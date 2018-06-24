#pragma once
#include "cocos2d.h"
#include"GameControler.h"

class GameScene : public cocos2d::LayerColor
{
    //定义鼠标事件坐标
	float event_x = 0;
	float event_y = 0;
	//定义是否暂停标签
	bool ifPause = false;
	//定义是否第一次进入场景
	bool ifFirstEnter = true;
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void update(float dt) override;

	// a selector callback
	void menuContinueCallback(cocos2d::Ref *pSender);
	void menuRestartCallback(cocos2d::Ref *pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuHelpCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref *pSender);

	void pause();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};