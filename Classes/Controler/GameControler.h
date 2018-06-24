#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"VirusVector.h"
#include"AllPlayersVector.h"

//�������������
#define MAXPLAYERSNUMBER 2

//�洢������Ϸ��������
class GameControler:public cocos2d::Node
{
	//�洢�����������
	cocos2d::Vector<cocos2d::Sprite*> scretions;
	//������ɾ���ķ����������
	cocos2d::Vector<cocos2d::Sprite*> scretion_toerase;

	inline PlayerVector* get_humanplayers() {  //�õ���һ���������(Ĭ������¼�Ϊ�������)
		auto bg = (BackGround*)getChildByTag(bgTag);
		auto allplayersvector = (AllPlayersVector*)bg->getChildByTag(allplayersTag);
		return *(allplayersvector->allPlayersVector.begin());
	}
	inline void human_divide() {  //���÷��Ѻ���
		get_humanplayers()->divide();
	}
	inline void human_spit() {   //���÷��ں���,�������������������
		cocos2d::Vector<cocos2d::Sprite*> add_scretions;
		add_scretions = get_humanplayers()->spit();
		for (auto scretion : add_scretions)
			scretions.pushBack(scretion);
	}

	bool move(float &,float &);   //�ƶ�������Ҽ�����,����ֵ��ʾ��������Ƿ�Ψһ���
	void move(float, float, PlayerVector*);  //�ƶ�AI���

	bool traverse(int);  //�������������ʳ�������������,������������Ƿ�����
	float inter_traverse(); //�������������֮�����,���ص�һ����ҵ�����������Ĭ������·����������������
	void virus_traverse(bool); //������������������ʵ������֮��Ĳ���

	void erase_scretion();  //ɾ��������
public:
	friend class GameScene;

	inline bool init();
	static GameControler* create();
};