#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"PlayerVector.h"
#include"AllPlayersVector.h"

//�������������
#define MAXPLAYERSNUMBER 4

//ö�ٱ�ǩ����
typedef enum
{
	bgTag = 110
	, controlerTag
	, allplayersTag
	, circlesTag
	, pausemenuTag
}Tag;
//�洢������Ϸ��������
class GameControler:public cocos2d::Node
{
	inline float lenth(cocos2d::Vec2 point) {
		return (sqrt(point.x*point.x + point.y*point.y));
	}
	inline float lenth(float x, float y) {
		return (sqrt(x*x + y*y));
	}
	inline bool isCircleCover(cocos2d::Vec2 position, float r1, float r2){
		//���ù��ɶ����ж���Բ�Ƿ��ں�
		return ((lenth(position)< (r1 - r2))&&r1>r2);
	}
	bool if_attack(PlayerVector* , PlayerVector* ); //�ж��ܷ���з��ѹ���

	void move(float &,float &);   //�ƶ��������С�򼰱���
	void scalebg(const float); //��������

	void divide(PlayerVector*);  //��ҷ��Ѳ���
	void combine();  //���С��֮��ĺϲ�
	void traverse();  //�������������ʳ��
	void eat(Player*, cocos2d::Sprite*);  //�����ʳ��֮�����ɲ���

	void inter_traverse(); //�������������֮�����
	void aiControl(PlayerVector*, PlayerVector*);	//����AI���С����Ϊ
	void move(float, float, PlayerVector*);  //�ƶ�AIС��
	void eat(PlayerVector*, PlayerVector*);  //���֮�������

public:
	friend class GameScene;

	inline bool init();
	static GameControler* create();
};