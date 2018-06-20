#include"GameControler.h"
USING_NS_CC;
//定义小球速度参数默认值
#define SPEEDPARAMETER 1.3

bool GameControler::init()
{
	if (!Node::create())
	{
		return false;
	}
	return true;
}

GameControler* GameControler::create()
{
	GameControler* gamecontroler = new GameControler();
	if (gamecontroler->init())
	{
		gamecontroler->autorelease();
	}
	else
	{
		delete gamecontroler;
		gamecontroler = NULL;
		return NULL;
	}
	return gamecontroler;
}

void GameControler::action_end(Ref* pSender)
{
	Player* player = (Player*)pSender;
	player->if_action_end = true;
}

bool GameControler::if_attack(PlayerVector* players1, PlayerVector* players2)
{
	for (auto player1 : players1->playervector)
	{
		for (auto player2 : players2->playervector)
		{
			if (player1->spritescale / 2 > player2->spritescale)
			{
				players1->desitination = Vec2(player2->getPosition().x// + player2->x
					, player2->getPosition().y// + player2->y
				);
				return true;
			}
		}
	}
	return false;
}

void GameControler::move(float &event_x, float &event_y)
{
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	auto humanplayers = *(allplayers->allPlayersVector.begin());
	auto bg = (BackGround*)getChildByTag(bgTag);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	const float& backgroundscale = bg->get_scale();
	//存储背景和屏幕中心的移动参量
	float x = event_x - center.x;
	float y = event_y - center.y;
	float r = lenth(x, y);

	//定义背景移动的速度参数
	float speed = SPEEDPARAMETER;

	//鼠标位于靠近屏幕中心位置时，背景移动速度稍作减小
	if (r < 16)
		speed = 0.5 + 0.05*r;
	//以平均小球缩放参数以作为背景移动的一个速度参数
	float sumscale = 0;
	float averscale = 0;

	for (auto player : humanplayers->playervector)
	{
		if (player->if_action_end)
		{
			Vec2 point = player->getPosition();
			//存储每个玩家小球的移动参量
			player->x = event_x - point.x;
			player->y = event_y - point.y;
			float r = lenth(player->x, player->y);

			//处理边界情况
			if ((player->getPosition().x - player->getContentSize().width / 2 * player->getScale()) < 0 ||
				(player->getPosition().x + player->getContentSize().width / 2 * player->getScale()) > bg->getContentSize().width)
				x = 0;
			if ((player->getPosition().y - player->getContentSize().height / 2 * player->getScale()) < 0 ||
				(player->getPosition().y + player->getContentSize().height / 2 * player->getScale()) > bg->getContentSize().height)
				y = 0;

			//鼠标靠近小球时，速度稍微减小
			player->speed = SPEEDPARAMETER;
			if (r < 16)
				player->speed = 0.5 + 0.05*r;

			if (player->x != 0 || player->y != 0) {
				player->setPosition(point + backgroundscale / 4 * (player->speed - 2 * player->spritescale)*
					Vec2(player->x / r, player->y / r) / backgroundscale);  //需除去放缩的比例
			}
		}
		sumscale += player->spritescale;
	}
	averscale = sumscale / humanplayers->playervector.size();

	//移动背景
	//鼠标几乎处于屏幕中心时则不做移动
	if ((x != 0 || y != 0) && r > 1)
	{
		bg->setPosition(bg->getPosition() - backgroundscale / 4 * (speed - 2 * averscale)*Vec2(x / r, y / r));
		//当鼠标未移动时，将上一次移动事件得到的鼠标位置与背景同步移动，以模拟鼠标的移动
		event_x = event_x + backgroundscale / 4 * (speed - 2 * averscale)*Vec2(x / r, y / r).x / backgroundscale;
		event_y = event_y + backgroundscale / 4 * (speed - 2 * averscale)*Vec2(x / r, y / r).y / backgroundscale;
	}
}

void GameControler::scalebg(const float scaleparameter)
{
	auto bg = (BackGround*)getChildByTag(bgTag);

	float& backgroundscale = bg->get_scale();

	//限定放缩范围
	if (backgroundscale - scaleparameter >= DEFAULTBGSCALE / 2 && backgroundscale - scaleparameter <= DEFAULTBGSCALE * 3 / 2)
	{
		backgroundscale = backgroundscale - scaleparameter;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		Vec2 point = bg->getContentSize() / 2;

		FiniteTimeAction* action1 = //位移补偿
			(FiniteTimeAction *)MoveBy::create(1 / 20, scaleparameter * Vec2(center.x - point.x, center.y - point.y));
		FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(1 / 20, backgroundscale);
		ActionInterval* action = Spawn::create(action1, action2, NULL);
		bg->runAction(action);

		//重新添加碰撞刚体
		bg->getPhysicsBody()->removeAllShapes();
		auto size = bg->getContentSize();
		size.width += DEFAULTWIDTH / 2 / bg->get_scale()*DEFAULTBGSCALE;
		size.height += DEFAULTWIDTH / 2 / bg->get_scale()*DEFAULTBGSCALE;
		auto body = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, DEFAULTWIDTH);
		bg->setPhysicsBody(body);
	}
}

bool GameControler::check_playerdead()
{
	bool if_humanplayer_alive = true;
	auto bg = getChildByTag(bgTag);
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	for (auto players : allplayers->allPlayersVector)
	{
		if (players->playervector.empty())
		{
			if (!players->ifAIplayer)
				if_humanplayer_alive = false;
			allplayers->toerase.pushBack(players);
		}
	}
	//移除
	for (auto players_toerase : allplayers->toerase)
	{
		allplayers->allPlayersVector.eraseObject(players_toerase);
	}
	allplayers->toerase.clear();
	return if_humanplayer_alive;
}

void GameControler::divide(PlayerVector* players)
{
	auto bg = (BackGround*)getChildByTag(bgTag);

	bool ifdivide = false;

	const float& backgroundscale = bg->get_scale();
	//分裂操作需要在容器中增加元素，使用初始容器大小size来进行遍历
	int size = players->playervector.size();
	if (size < MAXPLAYERNUMBER)
	{
		for (int i = 0; i < size; i++)
		{
			Player* player = *(players->playervector.begin() + i);

			if (player->spritescale > sqrt(2) * STARTPLSCALE) {

				float r = lenth(player->x, player->y);
				
				player->spritescale = player->spritescale / sqrt(2);
				player->runAction(ScaleTo::create(0.8, player->spritescale / DEFAULTBGSCALE));
				//克隆小球
				auto _player = player->playerclone();
				bg->addChild(_player, 2);
				_player->if_action_end = false;
				//分裂后两小球拉开距离,设置动画
				FiniteTimeAction* action1 = (FiniteTimeAction *)MoveTo::create(0.8,
					_player->getPosition()+30 * Vec2(_player->x / r, _player->y / r));
				FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.8, _player->spritescale / DEFAULTBGSCALE);
				FiniteTimeAction* action3 = CallFuncN::create(CC_CALLBACK_1(GameControler::action_end, this));
				ActionInterval* _action = Spawn::create(action1, action2, NULL);
				ActionInterval* action = Sequence::create(_action, action3, NULL);

				player->runAction(MoveTo::create(0.8, player->getPosition() - 6 * Vec2(player->x / r, player->y / r)));
				_player->runAction(action);

				players->playervector.pushBack(_player);
				ifdivide = true;
			}
		}
	}
	if (ifdivide)
	{
		if (!players->ifAIplayer)
			scalebg(0.1); //放缩屏幕
	}
}

void GameControler::combine()
{
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	auto bg = (BackGround*)getChildByTag(bgTag);

	//判断是否是人类玩家进行了合并
	bool ifhumancombine = false;

	for (auto players : allplayers->allPlayersVector)
	{
		//判断每个玩家是否进行合并操作
		bool ifcombine = false;
		for (auto player1 : players->playervector)
		{
			for (auto player2 : players->playervector)
			{
				if (player1 != player2&&!player1->combined&&!player2->combined
					&&player1->if_action_end&&player2->if_action_end)
				{
					if (isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
						player1->getContentSize().width / 2 * player1->spritescale * 4 / 5,
						-player2->getContentSize().width / 2 * player2->spritescale * 4 / 5) && player1->spritescale > player2->spritescale)
					{
						player1->spritescale = lenth(player1->spritescale, player2->spritescale);
						player1->runAction(ScaleTo::create(0.8, player1->spritescale / DEFAULTBGSCALE));

						//设置动画
						FiniteTimeAction* action1 = MoveTo::create(0.5, player1->getPosition());
						FiniteTimeAction* action2 = ScaleTo::create(0.5, player2->spritescale / DEFAULTBGSCALE / 10);
						ActionInterval* action3 = Spawn::create(action1, action2, NULL);
						FiniteTimeAction* action4 = CallFuncN::create(CC_CALLBACK_0(GameControler::erase_combined, this));
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
		scalebg(-0.1);
}

void GameControler::traverse()
{
	auto circles = (Circles*)getChildByTag(circlesTag);
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	auto virus = (Virus*)getChildByTag(virusTag);

	for (auto players : allplayers->allPlayersVector)
	{
		//判断每个玩家是否进行了吞噬操作的标签
		bool ifeat = false;
		int size = players->playervector.size();
		for (int i = 0; i < size; i++)
		{
			Player* player = *(players->playervector.begin() + i);
			float min_distance = 1000;
			for (auto circle : circles->spriteVector)
			{
				//对AI玩家，找到最近的食物(对于玩家容器中的第一个小球而言)
				if (players->ifAIplayer&&player == *(players->playervector.begin()))
				{
					Vec2 distanceVec = player->getPosition() - circle->getPosition();
					float distance = sqrt(distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y);
					if (distance < min_distance)
					{
						min_distance = distance;
						players->closestfood = circle->getPosition();
					}
				}
				if (isCircleCover(DEFAULTBGSCALE*(player->getPosition() - circle->getPosition()),
					player->getContentSize().width / 2 * player->spritescale,
					circle->getContentSize().width / 2 * CIRCLESCALE))
				{
					eat(players,player, circle);
					ifeat = true;
				}
			}

			for (auto _virus : virus->virusvector)
			{
				if (isCircleCover(DEFAULTBGSCALE*(player->getPosition() - _virus->getPosition()),
					player->getContentSize().width / 2 * player->spritescale,
					_virus->getContentSize().width / 2 * VIRUSSCALE)&&player->spritescale>VIRUSSCALE
					)
				{
					eat(players,player, _virus);
					ifeat = true;
				}
			}
		}

		if (ifeat)
			players->set_scale();
	}
}

void GameControler::eat(PlayerVector* players, Player* player, Sprite* sprite)
{
	auto bg = getChildByTag(bgTag);
	if (sprite->getColor() == Color3B::BLACK) //通过颜色判断是否是病毒
	{
		player->spritescale = lenth(player->spritescale, VIRUSSCALE/sqrt(2)) / sqrt(8);
		player->if_action_end = false;
		float r = lenth(player->x, player->y);

		FiniteTimeAction* action1 = (FiniteTimeAction *)MoveTo::create(0.5,
			player->getPosition() - 16 * Vec2(player->x / r, player->y / r));
		FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE);
		FiniteTimeAction* action3 = CallFuncN::create(CC_CALLBACK_1(GameControler::action_end, this));
		ActionInterval* _action = Spawn::create(action1, action2, NULL);
		ActionInterval* action = Sequence::create(_action, action3, NULL);
		player->runAction(action);

		for (int i = 1; i < 8; i++)
		{
			//克隆小球
			auto _player = player->playerclone(i);
			bg->addChild(_player, 2);
			_player->if_action_end = false;
			//设置动画
			FiniteTimeAction* action1 = (FiniteTimeAction *)MoveTo::create(0.5,
				_player->getPosition() + 10 * Vec2(_player->x / r, _player->y / r));
			FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.5, _player->spritescale / DEFAULTBGSCALE);
			FiniteTimeAction* action3 = CallFuncN::create(CC_CALLBACK_1(GameControler::action_end, this));
			ActionInterval* _action = Spawn::create(action1, action2, NULL);
			ActionInterval* action = Sequence::create(_action, action3, NULL);
			_player->runAction(action);

			players->playervector.pushBack(_player);
		}
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));
	}
	else
	{
		player->spritescale = lenth(player->spritescale, CIRCLESCALE);
		player->runAction(ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE));
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));
	}
}

void GameControler::erase_combined()
{
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	auto bg =getChildByTag(bgTag);
	for (auto players : allplayers->allPlayersVector)
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

void GameControler::erase_eated()
{
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	auto bg = getChildByTag(bgTag);
	for (auto players : allplayers->allPlayersVector)
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
		players->set_scale();
	}
}

float GameControler::inter_traverse()
{

	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);
	for (auto players1 : allplayers->allPlayersVector) {
		for (auto players2 : allplayers->allPlayersVector) {
			if (players1 != players2) {
				if (players1->ifAIplayer) {
					aiControl(players1, players2);
				}
				eat_player(players1, players2);
			}
		}
		if (players1->ifAIplayer)
			move(players1->desitination.x, players1->desitination.y, players1);
	}
	erase_eated();
	auto humanplayers = *(allplayers->allPlayersVector.begin());
	return humanplayers->sum_scale;
}

void GameControler::eat_player(PlayerVector* players1, PlayerVector* players2)
{
	for (auto player1 : players1->playervector)
	{
		for (auto player2 : players2->playervector)
		{
			if (!player1->eated&&!player2->eated)
			{
				if (isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
					player1->getContentSize().width / 2 * player1->spritescale,
					player2->getContentSize().width / 2 * player2->spritescale) && player1->spritescale > player2->spritescale)
				{
					player1->spritescale = lenth(player1->spritescale, player2->spritescale);
					player1->runAction(ScaleTo::create(0.8, player1->spritescale / DEFAULTBGSCALE));

					player2->eated = true;
				}
			}
		}
	}
}

void GameControler::aiControl(PlayerVector* players1, PlayerVector* players2)
{
	//以容器的第一个元素作为代表元判断距离
	auto player1 = *(players1->playervector.begin());
	auto player2 = *(players2->playervector.begin());
	if (lenth(player1->getPosition() - player2->getPosition()) < 35) {
		if (players1->sum_scale > players2->sum_scale) {
			if (if_attack(players1, players2)) {
				for (auto player : players1->playervector) {
					player->x = (players1->desitination - player->getPosition()).x;
					player->y = (players1->desitination - player->getPosition()).y;
				}
				divide(players1);
			}
			else
				players1->desitination = players1->closestfood;
		}
		else
			players1->desitination = 2 * player1->getPosition() - player2->getPosition(); //向反方向逃离
	}
	else
		players1->desitination = players1->closestfood;
}

void GameControler::move(float desitination_x, float sesitination_y, PlayerVector* players)
{
	auto bg = (BackGround*)getChildByTag(bgTag);

	for (auto player : players->playervector) {
		Vec2 point = player->getPosition();
		player->x = desitination_x - point.x;
		player->y = sesitination_y - point.y;
		float r = lenth(player->x, player->y);
		player->speed = SPEEDPARAMETER;

		if (player->x != 0 || player->y != 0) {
			player->setPosition(point + bg->get_scale() / 4 * (player->speed - 2 * player->spritescale)
				*Vec2(player->x / r, player->y / r) / bg->get_scale());  //需除去放缩的比例
		}
	}
}