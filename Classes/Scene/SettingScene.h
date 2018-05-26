#pragma once
#include "cocos2d.h"

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SettingScene);
};
