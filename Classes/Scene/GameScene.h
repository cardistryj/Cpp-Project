#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#include"GameControler.h"

class GameScene : public cocos2d::Scene
{

	//������������
	float backgroundscale = 4;

	//�����ƶ���������������
	float x = 0;
	float y = 0;
	//r��ʾ����ģ��
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
