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
	//定义人类玩家是否存活标签
	bool if_humanplayer_alive = true;
	//定义游戏是否结束
	bool if_gameover = false;

	//定义分数
	int score = 0;
	int highestscore = 0;
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void cleanup();
	void update(float dt) override;

	// a selector callback
	void menuContinueCallback(cocos2d::Ref *pSender);
	void menuRestartCallback(cocos2d::Ref *pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuHelpCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref *pSender);
	//用于暂停游戏的函数
	void pause();
	//游戏结束的函数
	void gameover();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};