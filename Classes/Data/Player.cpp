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
	_player->setPosition(getPosition());
	_player->spritescale = spritescale;

	return _player;
}