#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"

class SettingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	// a selector callback
	void menuSoundeffectCallback(cocos2d::Ref* pSender);
	void menuBGMCallback(cocos2d::Ref* pSender);
	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SettingScene);
};
