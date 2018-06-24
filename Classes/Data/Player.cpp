#include"Player.h"

USING_NS_CC;

bool Player::init(Texture2D* texture)
{
	if (!Sprite::initWithTexture(texture))
	{
		return false;
	}
	return true;
}

Player* Player::create(Texture2D* texture) {
	Player * sprite = new Player();
	if (sprite->init(texture)) {
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

Player* Player::playerclone(Texture2D* texture, int i)
{
	auto _player = Player::create(texture);
	_player->setScale(getScale());
	_player->setColor(getColor());
	_player->spritescale = spritescale;
	_player->setTag(getTag());
	switch (i) //��Ҫ������ɲ��������switch���
	{
	case 1:
		_player->x = x;
		_player->y = y;
		break;
	case 2:
		_player->x = -x;
		_player->y = -y;
		break;
	case 3:
		_player->x = -y;
		_player->y = x;
		break;
	case 4:
		_player->x = y;
		_player->y = -x;
		break;
	case 5:
		_player->x = (x + y) / sqrt(2);
		_player->y = (y - x) / sqrt(2);
		break;
	case 6:
		_player->x = (x - y) / sqrt(2);
		_player->y = (y + x) / sqrt(2);
		break;
	case 7:
		_player->x = (-x - y) / sqrt(2);
		_player->y = (-y + x) / sqrt(2);
		break;
	case 8:
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

void Player::losingscale()
{
	spritescale = sqrt(spritescale*spritescale - LOSINGSCALE*LOSINGSCALE);
}

void Player::eat(Sprite* sprite)
{
	auto bg = getParent();

	spritescale = BackGround::lenth(spritescale, CIRCLESCALE);
	runAction(ScaleTo::create(0.8, spritescale / DEFAULTBGSCALE));
	sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
		, CCRANDOM_0_1()*bg->getContentSize().height));
}

void Player::eat_scretion(Sprite* sprite)
{
	spritescale = BackGround::lenth(spritescale, SCRETIONSCALE);
	losingscale();
	runAction(ScaleTo::create(0.8f, spritescale / DEFAULTBGSCALE));
}