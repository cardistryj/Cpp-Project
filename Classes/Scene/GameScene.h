#pragma once
#include "cocos2d.h"
#include"GameControler.h"

//ö�ٱ�ǩ����
typedef enum
{
	bgTag = 110
	, controlerTag
	, playersTag
	, circlesTag
}Tag;

class GameScene : public cocos2d::Scene
{
    //��������¼�����
	float event_x = 0;
	float event_y = 0;

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