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
	_player->spritescale = spritescale;
	_player->setTag(getTag());
	_player->x = x;
	_player->y = y;
	auto r = sqrt(x*x + y*y);
	//添加刚体
	auto body = PhysicsBody::createCircle(_player->getContentSize().width / 2);
	_player->setPhysicsBody(body);

	//设置克隆小球的坐标稍微偏离原始小球坐标
	_player->setPosition(getPosition()+ Vec2(x/r, y/r)*getContentSize().width/2*spritescale);
	_player->onbg = onbg;

	return _player;
}