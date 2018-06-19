#include"Player.h"

USING_NS_CC;

bool Player::init() //��Ӳ���
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
		sprite->autorelease(); //�ɳ������sprite���������ڣ�  
	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return sprite;
}

Player* Player::playerclone(void)
{
	//����һ���ľ���
	auto _player = Player::create();
	_player->setScale(getScale());
	_player->setColor(getColor());
	_player->spritescale = spritescale;
	_player->setTag(getTag());
	_player->x = x;
	_player->y = y;
	auto r = sqrt(x*x + y*y);

	auto body = getPhysicsBody();
	//��Ӹ���
	auto _body = PhysicsBody::createCircle(_player->getContentSize().width / 2);
	_body->setCategoryBitmask(body->getCategoryBitmask());
	_body->setCollisionBitmask(body->getCollisionBitmask());
	_player->setPhysicsBody(_body);

	_player->setPosition(getPosition() + Vec2(x / r, y / r)*getContentSize().width / 10 * spritescale);
	_player->eated = eated;
	_player->combined = combined;
	_player->can_combine = false;

	return _player;
}