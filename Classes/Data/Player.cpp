#include"Player.h"

USING_NS_CC;

bool Player::init()
{
	if (!Sprite::initWithFile("ball.png")) 
	{
		return false;
	}
	return true;
}

Player* Player::create() {
	Player * sprite = new Player();
	if (sprite->init()) {
		sprite->autorelease();  
	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return sprite;
}

Player* Player::playerclone(int i)
{
	auto _player = Player::create();
	_player->setScale(getScale());
	_player->setColor(getColor());
	_player->spritescale = spritescale;
	_player->setTag(getTag());
	switch (i) //主要针对吞噬病毒情况的switch语句
	{
	case 1:
		_player->x = x;
		_player->y = y;
		break;
	case 2:
		_player->x = y;
		_player->y = -x;
		break;
	case 3:
		_player->x = -y;
		_player->y = x;
		break;
	case 4:
		_player->x = (x + y) / sqrt(2);
		_player->y = (y - x) / sqrt(2);
		break;
	case 5:
		_player->x = (x - y) / sqrt(2);
		_player->y = (y + x) / sqrt(2);
		break;
	case 6:
		_player->x = (-x - y) / sqrt(2);
		_player->y = (-y + x) / sqrt(2);
		break;
	case 7:
		_player->x = (-x + y) / sqrt(2);
		_player->y = (-y - x) / sqrt(2);
		break;
	default:
		break;
	}

	auto r = sqrt(x*x + y*y);

	auto body = getPhysicsBody();
	auto _body = PhysicsBody::createCircle(_player->getContentSize().width / 2);
	_body->setCategoryBitmask(body->getCategoryBitmask());
	_body->setCollisionBitmask(body->getCollisionBitmask());
	_player->setPhysicsBody(_body);

	_player->setPosition(getPosition() + Vec2(_player->x / r, _player->y / r)*getContentSize().width / 50 * spritescale);
	_player->eated = eated;
	_player->combined = combined;

	return _player;
}