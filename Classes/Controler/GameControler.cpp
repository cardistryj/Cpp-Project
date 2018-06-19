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

void GameControler::set_combine(Ref* pSender)
{
	//分裂动画完成后，允许合并
	Player* player = (Player*)pSender;
	player->can_combine = true;
}

bool GameControler::if_attack(PlayerVector* players1, PlayerVector* players2)
{
	for (auto player1 : players1->playervector)
	{
		for (auto player2 : players2->playervector)
		{
			if (player1->spritescale / sqrt(2) > player2->spritescale)
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
	//定义平均小球放缩参数以作为背景移动的一个速度参数
	float averscale = humanplayers->aver_scale;

	//移动玩家的小球
	for (auto player : humanplayers->playervector)
	{
		//玩家的相对坐标
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

		FiniteTimeAction* action1 = //放缩后进行位移补偿
			(FiniteTimeAction *)MoveBy::create(1 / 20, scaleparameter * Vec2(center.x - point.x, center.y - point.y));
		FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(1 / 20, backgroundscale);
		ActionInterval* action = Spawn::create(action1, action2, NULL);
		bg->runAction(action);

		//重新添加刚体
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

	//判断是否进行了分裂操作
	bool ifdivide = false;

	const float& backgroundscale = bg->get_scale();
	//分裂操作需要在容器中增加元素，使用初始容器大小size来进行遍历
	int size = players->playervector.size();
	if (size < MAXPLAYERNUMBER)
	{
		for (int i = 0; i < size; i++)
		{
			Player* player = *(players->playervector.begin() + i);
			//到达一定大小的方可进行分裂
			if (player->spritescale > 2 * STARTPLSCALE) {

				float r = sqrt(player->x*player->x + player->y*player->y);
				//尺寸缩小至一半
				player->spritescale = player->spritescale / sqrt(2);
				player->runAction(ScaleTo::create(0.8, player->spritescale / DEFAULTBGSCALE));
				//克隆小球
				auto _player = player->playerclone();
				bg->addChild(_player, 2);
				//分裂后两小球拉开距离,设置动画
				FiniteTimeAction* action1 = (FiniteTimeAction *)MoveTo::create(0.8,
					_player->getPosition()+30 * Vec2(_player->x / r, _player->y / r)*backgroundscale / 4
				);
				FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.8, _player->spritescale / DEFAULTBGSCALE);
				FiniteTimeAction* action3 = CallFuncN::create(CC_CALLBACK_1(GameControler::set_combine, this));
				ActionInterval* _action = Spawn::create(action1, action2, NULL);
				ActionInterval* action = Sequence::create(_action, action3, NULL);

				player->runAction(MoveTo::create(0.8, player->getPosition() - 6 * Vec2(player->x / r, player->y / r)*backgroundscale / 4));
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
		players->set_scale();
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
				//两小球都尚在背景上时判断能否合并
				if (player1 != player2&&!player1->combined&&!player2->combined
					&&player1->can_combine&&player2->can_combine)
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

						//处理被合并掉的小球
						player2->combined = true;
						//players->toerase.pushBack(player2);
						if (!players->ifAIplayer)
							ifhumancombine = true;
						ifcombine = true;
					}
				}
			}
		}
		if (ifcombine)
			players->set_scale();
	}
	//erase();
	if (ifhumancombine)
		scalebg(-0.1); //放缩屏幕
}

void GameControler::traverse()
{
	auto circles = (Circles*)getChildByTag(circlesTag);
	auto allplayers = (AllPlayersVector*)getChildByTag(allplayersTag);

	///遍历容器
	for (auto players : allplayers->allPlayersVector)
	{
		//判断每个玩家是否进行了吞噬操作的标签
		bool ifeat = false;
		for (auto player : players->playervector)
		{
			//定义与食物的最小距离
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
					eat(player, circle);
					ifeat = true;
				}
			}
		}
		//重新计算平均大小
		if (ifeat)
			players->set_scale();
	}
}

void GameControler::eat(Player* player, Sprite* circle)
{
	auto bg = (BackGround*)getChildByTag(bgTag);
	player->spritescale = lenth(player->spritescale, CIRCLESCALE);
	player->runAction(ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE));
	circle->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
		, CCRANDOM_0_1()*bg->getContentSize().height));
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
	}
}

void GameControler::inter_traverse()
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
}

void GameControler::eat_player(PlayerVector* players1, PlayerVector* players2)
{
	for (auto player1 : players1->playervector)
	{
		for (auto player2 : players2->playervector)
		{
			//两小球都尚在背景上时判断能否吞噬
			if (!player1->eated&&!player2->eated)
			{
				if (isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
					player1->getContentSize().width / 2 * player1->spritescale,
					player2->getContentSize().width / 2 * player2->spritescale) && player1->spritescale > player2->spritescale)
				{
					player1->spritescale = lenth(player1->spritescale, player2->spritescale);
					player1->runAction(ScaleTo::create(0.8, player1->spritescale / DEFAULTBGSCALE));
					//处理被合并掉的小球
					player2->eated = true;
					//players2->toerase.pushBack(player2);
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
	if (lenth(player1->getPosition() - player2->getPosition()) < 30) { //两玩家靠近时
		if (players1->aver_scale > players2->aver_scale) {
			if (if_attack(players1, players2)) {
				for (auto player : players1->playervector) {  //存储分裂方向的坐标
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
	//移动AI玩家的小球
	for (auto player : players->playervector) {
		//AI玩家的相对坐标
		Vec2 point = player->getPosition();
		//存储每个玩家小球的移动参量
		player->x = desitination_x - point.x;
		player->y = sesitination_y - point.y;
		float r = lenth(player->x, player->y);

		//速度参数
		player->speed = SPEEDPARAMETER;

		if (player->x != 0 || player->y != 0) {
			player->setPosition(point + bg->get_scale() / 4 * (player->speed - 2 * player->spritescale)
				*Vec2(player->x / r, player->y / r) / bg->get_scale());  //需除去放缩的比例
		}
	}
}