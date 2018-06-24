#pragma once
#include "cocos2d.h"
#include"GameControler.h"

class GameScene : public cocos2d::LayerColor
{
	//��������¼�����
	float event_x = 0;
	float event_y = 0;
	//�����Ƿ���ͣ��ǩ
	bool ifPause = false;
	//�����Ƿ��һ�ν��볡��
	bool ifFirstEnter = true;
	//������������Ƿ����ǩ
	bool if_humanplayer_alive = true;
	//������Ϸ�Ƿ����
	bool if_gameover = false;

	//�������
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
	//������ͣ��Ϸ�ĺ���
	void pause();
	//��Ϸ�����ĺ���
	void gameover();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};