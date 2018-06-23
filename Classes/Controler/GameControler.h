#pragma once
#include "cocos2d.h"
#include"Circles.h"
#include"VirusVector.h"
#include"AllPlayersVector.h"

//�������������
#define MAXPLAYERSNUMBER 6

//ö�ٱ�ǩ����
typedef enum
{
	bgTag = 110
	, controlerTag
	, allplayersTag
	, circlesTag
	, pausemenuTag
	,scorelabelTag
	,virusTag
}Tag;

//�洢������Ϸ��������
class GameControler:public cocos2d::Node
{
	//�洢�����������
	cocos2d::Vector<cocos2d::Sprite*> scretions;
	//������ɾ���ķ����������
	cocos2d::Vector<cocos2d::Sprite*> scretion_toerase;
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
	void action_end(Ref* pSender); //�����ܷ�ϲ���ǩ

	bool if_attack(PlayerVector* , PlayerVector* ); //�ж��ܷ���з��ѹ���

	void move(float &,float &);   //�ƶ��������С�򼰱���
	void move(float, float, PlayerVector*);  //�ƶ�AIС��
	void aiControl(PlayerVector*, PlayerVector*);	//����AI���С�����Ϊ

	void scalebg(const float); //��������
	bool check_playerdead();  //�������������������������Ƿ�����

	void divide(PlayerVector*);  //��ҷ��Ѳ���
	void combine();  //���С��֮��ĺϲ�
	void spit(PlayerVector*); //��ҷ��ڷ�����

	void traverse();  //�������������ʳ��
	float inter_traverse(); //�������������֮�����,�������λ����ʱ�������䷵�������
	void virus_traverse(); //�������������������

	void eat(Player*, cocos2d::Sprite*);  //�����ʳ��֮�����ɲ���
	void eat_scretion(Player*, cocos2d::Sprite*); //����������֮������ɲ���
	void eat_virus(PlayerVector*, Player*, Virus*);  //����벡��֮�����ɲ���
	void eat_player(PlayerVector*, PlayerVector*);  //���֮�������

	void erase_scretion(); //ɾ��������
	void erase_combined();  //ɾ�����ϲ��������С��
	void erase_eated();  //ɾ�������ɵ������С��
	void erase_virus(); //ɾ�������ɵ��Ĳ���

public:
	friend class GameScene;

	inline bool init();
	static GameControler* create();
};