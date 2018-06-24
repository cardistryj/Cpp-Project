#include"BackGround.h"
USING_NS_CC;

bool BackGround::init()
{
	if (!Sprite::initWithFile("background.png"))
	{
		return false;
	}
	backgroundscale = DEFAULTBGSCALE;
	setScale(backgroundscale);
	return true;
}

BackGround* BackGround::create()
{
	BackGround* bg = new BackGround();
	if (bg->init())
	{
		bg->autorelease();
	}
	else
	{
		delete bg;
		bg = NULL;
		return NULL;
	}
	return bg;
}

void BackGround::set_body()
{
	auto size = getContentSize();
	size.width += DEFAULTWIDTH * 2 / backgroundscale;
	size.height += DEFAULTWIDTH * 2 / backgroundscale;
	auto body = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, DEFAULTWIDTH);
	setPhysicsBody(body);
}

void BackGround::scalebg(const float scaleparameter)
{
	//限定放缩范围
	if (backgroundscale - scaleparameter >= 0.6 && backgroundscale - scaleparameter <= DEFAULTBGSCALE * 3 / 2)
	{
		backgroundscale = backgroundscale - scaleparameter;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto center = convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		Vec2 point = getContentSize() / 2;

		FiniteTimeAction* action1 = //位移补偿
			(FiniteTimeAction *)MoveBy::create(1 / 20, scaleparameter * Vec2(center.x - point.x, center.y - point.y));
		FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(1 / 20, backgroundscale);
		ActionInterval* action = Spawn::create(action1, action2, NULL);
		runAction(action);

		//重新添加碰撞刚体
		getPhysicsBody()->removeAllShapes();
		set_body();
	}
}