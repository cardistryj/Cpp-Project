#pragma once
#include"cocos2d.h"
//����Ĭ�ϱ�����С
#define DEFAULTBGSCALE 5.0f
//�����Ե����Ĭ�Ͽ��
#define DEFAULTWIDTH 125.0f

//���������Ĭ�Ϸ�������
#define SCRETIONSCALE 0.03f
//ö�ٱ�ǩ����
typedef enum
{
	bgTag = 110
	, controlerTag
	, textureTag
	, allplayersTag
	, circlesTag
	, menuTag
	, labelTag
	, scorelabelTag
	, virusTag
}Tag;

//������
class BackGround :public cocos2d::Sprite
{
	float backgroundscale= DEFAULTBGSCALE;
public:

	bool init();
	static BackGround* create();
	void set_body(); //��Ӹ���
	void scalebg(const float); //���ű���
	inline float& get_scale() {
		return backgroundscale;
	};
	inline const float& get_scale()const {
		return backgroundscale;
	};
	//���㱳��������ģ��
	static float lenth(cocos2d::Vec2 point) {
		return (sqrt(point.x*point.x + point.y*point.y));
	};
	//���㱳�����������
	static float lenth(float x, float y) {
		return (sqrt(x*x + y*y));
	};
	static bool isCircleCover(cocos2d::Vec2 position, float r1, float r2) {
		//���ù��ɶ����жϱ�������Բ��λ�ù�ϵ
		return ((lenth(position)< (r1 - r2)) && r1>r2);
	};
};