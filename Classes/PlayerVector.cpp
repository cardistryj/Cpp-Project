#include"PlayerVector.h"
USING_NS_CC;

bool PlayerVector::init()
{
	if (!Node::create())
	{
		return false;
	}
	return true;
}

PlayerVector* PlayerVector::create()
{
	PlayerVector* players = new PlayerVector();
	if (players->init())
		players->autorelease();
	else
	{
		delete players;
		players = NULL;
		return NULL;
	}
	return players;
}

bool PlayerVector::init_on(BackGround* bg)
{
	auto player = Player::create();
	player->setScale(player->spritescale / bg->get_scale());
	player->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2));
	//Ìí¼ÓÅö×²
	auto body = PhysicsBody::createCircle(player->getContentSize().width / 2 );
	player->setPhysicsBody(body);

	bg->addChild(player, 2);
	player->onbg = true;
	playervector.pushBack(player);

	return true;
}