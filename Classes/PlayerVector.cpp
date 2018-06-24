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

PlayerVector* PlayerVector::create(bool ifAIplayer)
{
	PlayerVector* players = new PlayerVector();
	if (players->init())
	{
		players->ifAIplayer = ifAIplayer;
		players->autorelease();
	}
	else
	{
		delete players;
		players = NULL;
		return NULL;
	}
	return players;
}

void PlayerVector::set_scale()
{
	sum_scale = 0;
	for (auto player : playervector)
	{
		if (!player->eated && !player->combined)
			sum_scale += player->spritescale*player->spritescale;
	}
}

void PlayerVector::divide()
{
	auto bg = (BackGround*)getParent();
	auto spriteTexture = (SpriteBatchNode*)bg->getChildByTag(textureTag);
	auto texture = spriteTexture->getTexture();

	bool ifdivide = false;

	const float& backgroundscale = bg->get_scale();
	//分裂操作需要在容器中增加元素，使用初始容器大小size来进行遍历
	int size = playervector.size();
	if (size < MAXPLAYERNUMBER)
	{
		for (int i = 0; i < size; i++)
		{
			Player* player = *(playervector.begin() + i);

			if (player->spritescale > sqrt(2) * STARTPLSCALE) {

				float r = BackGround::lenth(player->x, player->y);

				player->spritescale = player->spritescale / sqrt(2);

				//克隆小球
				auto _player = player->playerclone(texture);
				bg->addChild(_player, 3);
				_player->if_action_end = false;
				//分裂后两小球拉开距离,设置动画
				FiniteTimeAction* action1 = (FiniteTimeAction *)MoveBy::create(0.8f, 25 * Vec2(_player->x / r, _player->y / r));
				FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.8f, _player->spritescale / DEFAULTBGSCALE);
				FiniteTimeAction* action3 = CallFuncN::create(CC_CALLBACK_1(PlayerVector::action_end, this));
				ActionInterval* _action = Spawn::create(action1, action2, NULL);
				ActionInterval* action = Sequence::create(_action, action3, NULL);

				player->losingscale();
				player->runAction(ScaleTo::create(0.8f, player->spritescale / DEFAULTBGSCALE));
				player->runAction(MoveBy::create(0.8f, -6 * Vec2(player->x / r, player->y / r)));
				_player->runAction(action);

				playervector.pushBack(_player);
				ifdivide = true;
			}
		}
	}
	if (ifdivide)
	{
		if (!ifAIplayer)
			bg->scalebg(0.1f); //放缩屏幕
	}
}

Vector<Sprite*> PlayerVector::spit()
{
	auto bg = (BackGround*)getParent();
	auto spriteTexture = (SpriteBatchNode*)bg->getChildByTag(textureTag);
	auto texture = spriteTexture->getTexture();
	auto gamecontroler = (GameControler*)bg->getParent();

	Vector<Sprite*> scretions;

	for (auto player : playervector)
	{
		if (player->spritescale > BackGround::lenth(STARTPLSCALE, SCRETIONSCALE))
		{
			player->spritescale = sqrt(player->spritescale*player->spritescale - SCRETIONSCALE*SCRETIONSCALE);
			player->losingscale();
			player->runAction(ScaleTo::create(0.8f, player->spritescale / DEFAULTBGSCALE));

			auto sprite = Sprite::createWithTexture(texture);
			sprite->setScale(SCRETIONSCALE / DEFAULTBGSCALE);
			sprite->setColor(player->getColor());

			auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
			body->setCategoryBitmask(0x01);
			body->setCollisionBitmask(0x01);
			sprite->setPhysicsBody(body);
			bg->addChild(sprite, 1);

			auto r = BackGround::lenth(player->x, player->y);
			sprite->setPosition(player->getPosition() +
				player->getContentSize().width / 2 * player->spritescale / DEFAULTBGSCALE*Vec2(player->x, player->y) / r);
			sprite->runAction(MoveBy::create(0.8f, 25 * Vec2(player->x / r, player->y / r)));

			scretions.pushBack(sprite);
		}
	}
	set_scale();
	return scretions;
}

void PlayerVector::eat_virus(Player* player, Virus* virus)
{
	auto bg = (BackGround*)getParent();
	auto virusvector = (VirusVector*)bg->getChildByTag(virusTag);
	auto spriteTexture = (SpriteBatchNode*)bg->getChildByTag(textureTag);
	auto texture = spriteTexture->getTexture();

	player->spritescale = BackGround::lenth(player->spritescale, virus->get_scale()) / 3;
	player->if_action_end = false;
	FiniteTimeAction* action1 = (FiniteTimeAction *)ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE);
	FiniteTimeAction* action2 = CallFuncN::create(CC_CALLBACK_1(PlayerVector::action_end, this));
	ActionInterval* action = Sequence::create(action1, action2, NULL);
	player->runAction(action);

	float r = BackGround::lenth(player->x, player->y);

	for (int i = 1; i < 9; i++)
	{
		//克隆小球
		auto _player = player->playerclone(texture, i);
		bg->addChild(_player, 3);
		_player->if_action_end = false;
		//设置动画
		FiniteTimeAction* action1 = (FiniteTimeAction *)MoveBy::create(0.5, 10 * Vec2(_player->x / r, _player->y / r));
		FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.5, _player->spritescale / DEFAULTBGSCALE);
		FiniteTimeAction* action3 = CallFuncN::create(CC_CALLBACK_1(PlayerVector::action_end, this));
		ActionInterval* _action = Spawn::create(action1, action2, NULL);
		ActionInterval* action = Sequence::create(_action, action3, NULL);
		_player->runAction(action);

		playervector.pushBack(_player);
	}

	bg->scalebg(0.4f);
}

void PlayerVector::eat_player(PlayerVector* players)
{
	for (auto player1 : playervector)
	{
		for (auto player2 : players->playervector)
		{
			if (!player1->eated && !player2->eated)
			{
				if (BackGround::isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
					player1->getContentSize().width / 2 * player1->spritescale,
					player2->getContentSize().width / 2 * player2->spritescale) && player1->spritescale > player2->spritescale)
				{
					player1->spritescale = BackGround::lenth(player1->spritescale, player2->spritescale);
					player1->runAction(ScaleTo::create(0.8f, player1->spritescale / DEFAULTBGSCALE));

					player2->eated = true;
				}
			}
		}
	}
}

bool PlayerVector::if_attack(PlayerVector* players)
{
	for (auto player1 : playervector)
	{
		for (auto player2 : players->playervector)
		{
			if (player1->spritescale / sqrt(3) > player2->spritescale)
			{
				float r = BackGround::lenth(player2->x, player2->y);
				desitination = Vec2(player2->getPosition().x + 3 * player2->x / r
					, player2->getPosition().y + 3 * player2->y / r);
				return true;
			}
		}
	}
	return false;
}

void PlayerVector::aiControl(PlayerVector* players)
{
	//以容器的第一个元素作为代表元判断距离
	auto player1 = *(playervector.begin());
	auto player2 = *(players->playervector.begin());
	if (BackGround::lenth(player1->getPosition() - player2->getPosition()) < 25) {
		if (sum_scale / playervector.size()
	> players->sum_scale / players->playervector.size()) {
			if (if_attack(players)) {
				for (auto player : playervector) {
					player->x = (desitination - player->getPosition()).x;
					player->y = (desitination - player->getPosition()).y;
				}
				divide();
			}
			else
				desitination = closestfood;
		}
		else
			desitination = 2 * player1->getPosition() - player2->getPosition(); //向反方向逃离
	}
	else
		desitination = closestfood;
}