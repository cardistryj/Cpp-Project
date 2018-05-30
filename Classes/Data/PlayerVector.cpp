#include"PlayerVector.h"
USING_NS_CC;

bool PlayerVector::init_on(cocos2d::Sprite* bg, float backgroundscale)
{

	auto player = Player::create();
	player->setScale(player->spritescale / backgroundscale);
	player->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2));
	bg->addChild(player, 2);

	playervector.pushBack(player);
	return true;
}

//