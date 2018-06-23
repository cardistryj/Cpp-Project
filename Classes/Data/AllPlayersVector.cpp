#include"AllPlayersVector.h"
#include"color.h"
USING_NS_CC;

bool AllPlayersVector::init()
{
	if (!Node::create())
	{
		return false;
	}
	return true;
}

AllPlayersVector* AllPlayersVector::create()
{
	AllPlayersVector* allplayersvector = new AllPlayersVector();
	if (allplayersvector->init())
		allplayersvector->autorelease();
	else
	{
		delete allplayersvector;
		allplayersvector = NULL;
		return NULL;
	}
	return allplayersvector;
}

void AllPlayersVector::init(BackGround* bg, int size)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Color color;
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++)
	{
		auto players = PlayerVector::create(i);
		auto player = Player::create();

		unsigned randomnumber = rand() % 12;
		unsigned char *c = color.getColor(randomnumber);
		player->setColor(Color3B(*c, *(c + 1), *(c + 2)));
		if (i)
		{
			Vec2 point;
			while (true)
			{
				point = Vec2(CCRANDOM_0_1()*bg->getContentSize().width, CCRANDOM_0_1()*bg->getContentSize().height);
				if ( //初始化在可视窗口之外
					((point.x < bg->getContentSize().width / 2 - visibleSize.width / 2 / bg->get_scale())
						|| (point.x > bg->getContentSize().width / 2 + visibleSize.width / 2 / bg->get_scale()))
					&& ((point.y > bg->getContentSize().height / 2 + visibleSize.height / bg->get_scale())
						|| (point.y < bg->getContentSize().height / 2 - visibleSize.height / bg->get_scale()))
					)
					break;

			}
			player->setPosition(point);
		}
		else
		{
			player->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2));
		}
		player->setScale(STARTPLSCALE / bg->get_scale());

		auto body = PhysicsBody::createCircle(player->getContentSize().width / 2);
		int bitmask = pow(2, i+1);  //以2的n（n>1）次方设置碰撞掩码
		body->setCategoryBitmask(bitmask);
		body->setCollisionBitmask(bitmask);
		player->setPhysicsBody(body);

		bg->addChild(player, 3);

		players->sum_scale = STARTPLSCALE*STARTPLSCALE;
		(players->playervector).pushBack(player);

		allPlayersVector.pushBack(players);
	}
}