#pragma once
#include"cocos2d.h"
//定义默认背景大小
#define DEFAULTBGSCALE 5.0f
//定义边缘刚体默认宽度
#define DEFAULTWIDTH 125.0f

//定义分泌物默认放缩参数
#define SCRETIONSCALE 0.03f
//枚举标签类型
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

//背景类
class BackGround :public cocos2d::Sprite
{
	float backgroundscale= DEFAULTBGSCALE;
public:

	bool init();
	static BackGround* create();
	void set_body(); //添加刚体
	void scalebg(const float); //缩放背景
	inline float& get_scale() {
		return backgroundscale;
	};
	inline const float& get_scale()const {
		return backgroundscale;
	};
	//计算背景上向量模长
	static float lenth(cocos2d::Vec2 point) {
		return (sqrt(point.x*point.x + point.y*point.y));
	};
	//计算背景上连点距离
	static float lenth(float x, float y) {
		return (sqrt(x*x + y*y));
	};
	static bool isCircleCover(cocos2d::Vec2 position, float r1, float r2) {
		//运用勾股定理判断背景上两圆的位置关系
		return ((lenth(position)< (r1 - r2)) && r1>r2);
	};
};