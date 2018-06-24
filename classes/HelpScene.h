#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"

USING_NS_CC;

class HelpScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menubackCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(HelpScene);
};