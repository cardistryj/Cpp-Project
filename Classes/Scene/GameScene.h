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

	//�����ƶ���������Ļ���ĵ���������
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
	void OnCallFuncN(cocos2d::Node *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};
