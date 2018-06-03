#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#include"GameControler.h"

class GameScene : public cocos2d::Scene
{

	//������������
	float backgroundscale = DEFAULTBGSCALE;
	//������ǩ
	int bgTag = 111;
	//�Ƿ���ѱ�ǩ
	bool ifdivide = false;

    //��������¼�����
	float event_x = 0;
	float event_y = 0;

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
