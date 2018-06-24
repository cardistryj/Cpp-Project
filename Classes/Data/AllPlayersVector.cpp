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

void AllPlayersVector::init(BackGround* bg, int size,Texture2D* texture)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Color color;
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++)
	{
		auto players = PlayerVector::create(i);
		auto player = Player::create(texture);

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
		int bitmask = pow(2, i+2);  //以2的n（n>1）次方设置碰撞掩码
		body->setCategoryBitmask(bitmask);
		body->setCollisionBitmask(bitmask);
		player->setPhysicsBody(body);

		bg->addChild(player, 3);
		bg->addChild(players);

		players->sum_scale = STARTPLSCALE*STARTPLSCALE;
		(players->playervector).pushBack(player);

		allPlayersVector.pushBack(players);
	}
}

void AllPlayersVector::combine()
{
	auto bg = (BackGround*)getParent();

	//判断是否是人类玩家进行了合并
	bool ifhumancombine = false;

	for (auto players : allPlayersVector)
	{
		//判断每个玩家是否进行合并操作
		bool ifcombine = false;
		for (auto player1 : players->playervector)
		{
			for (auto player2 : players->playervector)
			{
				if (player1 != player2 && !player1->combined && !player2->combined
					&&player1->if_action_end&&player2->if_action_end)
				{
					if (BackGround::isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
						player1->getContentSize().width / 2 * player1->spritescale * 2 / 3,
						-player2->getContentSize().width / 2 * player2->spritescale * 2 / 3) && player1->spritescale > player2->spritescale)
					{
						player1->spritescale = BackGround::lenth(player1->spritescale, player2->spritescale);
						player1->losingscale();

						//if (!player1->if_action_end)
						//	player1->stopAllActions();
						//player1->if_action_end = false;
						FiniteTimeAction* _action1 = ScaleTo::create(0.8f, player1->spritescale / DEFAULTBGSCALE);
						//FiniteTimeAction* _action2 = CallFuncN::create(CC_CALLBACK_1(AllPlayersVector::action_end, this));
						//ActionInterval* _action = Sequence::create(_action1, _action2, NULL);
						player1->runAction(_action1);

						//设置动画
						//if (!player2->if_action_end)
						//	player2->stopAllActions();
						//player2->if_action_end = false;
						FiniteTimeAction* action1 = MoveTo::create(1.0f, player1->getPosition());
						FiniteTimeAction* action2 = ScaleTo::create(0.8f, player2->spritescale / DEFAULTBGSCALE / 10);
						ActionInterval* action3 = Spawn::create(action1, action2, NULL);
						FiniteTimeAction* action4 = CCCallFuncN::create(CC_CALLBACK_0(AllPlayersVector::erase_combined, this));
						ActionInterval* action = Sequence::create(action3, action4, NULL);
						player2->runAction(action);
						player2->combined = true;

						if (!players->ifAIplayer)
							ifhumancombine = true;
						ifcombine = true;
					}
				}
			}
		}
	}
	if (ifhumancombine)
		bg->scalebg(-0.1f);
}

bool AllPlayersVector::check_playerdead()
{
	bool if_humanplayer_alive = true;
	auto bg = getParent();
	for (auto players : allPlayersVector)
	{
		if (players->playervector.empty())
		{
			if (!players->ifAIplayer)
				if_humanplayer_alive = false;
			toerase.pushBack(players);
		}
	}
	//移除
	for (auto players_toerase : toerase)
	{
		allPlayersVector.eraseObject(players_toerase);
	}
	toerase.clear();
	return if_humanplayer_alive;
}

void AllPlayersVector::erase_combined()
{
	auto bg = getParent();
	for (auto players : allPlayersVector)
	{
		//检查标签，false加入删除容器中
		for (auto player : players->playervector)
		{
			if (player->combined)
				players->toerase.pushBack(player);
		}
		for (auto player_toerase : players->toerase)
		{
			player_toerase->getPhysicsBody()->removeAllShapes();
			bg->removeChild(player_toerase);
			players->playervector.eraseObject(player_toerase);
		}
		players->toerase.clear();
	}
}

void AllPlayersVector::erase_eated()
{
	auto bg = getParent();
	for (auto players : allPlayersVector)
	{
		//检查标签，false加入删除容器中
		for (auto player : players->playervector)
		{
			if (player->eated)
				players->toerase.pushBack(player);
		}
		for (auto player_toerase : players->toerase)
		{
			player_toerase->getPhysicsBody()->removeAllShapes();
			bg->removeChild(player_toerase);
			players->playervector.eraseObject(player_toerase);
		}
		players->toerase.clear();
	}
}