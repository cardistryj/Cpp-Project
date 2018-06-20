#include "Virus.h"
USING_NS_CC;

bool Virus::init()
{
	if (!Node::create())
	{
		return false;
	}
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("ball.png");

	virusvector = Vector<Sprite *>(MAXVIRUSNUMBER);
	for (int i = 0; i < MAXVIRUSNUMBER; i++) {
		auto sprite = CCSprite::createWithTexture(texture);
		virusvector.pushBack(sprite);
	}
	return true;
}

Virus* Virus::create()
{
	Virus* virus = new Virus();
	if (virus->init())
	{
		virus->autorelease();
	}
	else
	{
		delete virus;
		virus = NULL;
		return NULL;
	}
	return virus;
}

void Virus::addvirusto(BackGround* bg)
{
	for (auto sprite : virusvector)
	{
		sprite->setColor(Color3B::BLACK);
		sprite->setScale(VIRUSSCALE / bg->get_scale());
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));

		bg->addChild(sprite, 1);
	}
}