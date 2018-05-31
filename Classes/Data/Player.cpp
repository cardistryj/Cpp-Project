#include"Player.h"
#include"color.h"
USING_NS_CC;

bool Player::init() //添加参数
{
	if (!Sprite::initWithFile("ball.png")) 
	{
		return false;
	}
	//随机生成颜色
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
		sprite->autorelease(); //由程序控制sprite的生命周期，  
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
	//创建一样的精灵
	auto _player = Player::create();
	_player->setScale(getScale());
	_player->setColor(getColor());
	_player->setPosition(getPosition());
	_player->spritescale = spritescale;

	return _player;
}