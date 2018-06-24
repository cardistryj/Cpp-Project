#include"Player.h"
#include"color.h"
USING_NS_CC;

bool Player::init() //��Ӳ���
{
	if (!Sprite::initWithFile("ball.png")) 
	{
		return false;
	}
	//���������ɫ
	Color color;
	srand((unsigned)time(NULL));
	unsigned randomnumber = rand() % 12;
	unsigned char *c = color.getColor(randomnumber);
	setColor(Color3B(*c, *(c + 1), *(c + 2)));

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
	//��Ӹ���
	auto body = PhysicsBody::createCircle(_player->getContentSize().width / 2);
	_player->setPhysicsBody(body);

	//���ÿ�¡С���������΢ƫ��ԭʼС������
	_player->setPosition(getPosition()+ Vec2(x/r, y/r)*getContentSize().width/2*spritescale);
	_player->onbg = onbg;

	return _player;
}