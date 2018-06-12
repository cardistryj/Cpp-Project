#include"GameControler.h"
USING_NS_CC;

//定义速度参数默认值
#define SPEEDPARAMETER 1.3

bool GameControler::init()
{
	if (!Node::create())
	{
		return false;
	}
	return true;
}

GameControler* GameControler::create(BackGround* _bg)
{
	GameControler* gamecontroler = new GameControler();
	if (gamecontroler->init())
	{
		gamecontroler->bg = _bg;
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

void GameControler::eat(Circles* circles, PlayerVector* players)
{
	//遍历小球容器和玩家的小球容器判断吞噬情况
	for (auto circle : circles->spriteVector)
	{
		for (auto player : players->playervector)
			if (isCircleCover(DEFAULTBGSCALE*(player->getPosition() - circle->getPosition()),
				player->getContentSize().width / 2 * player->spritescale,
				circle->getContentSize().width / 2 * CIRCLESCALE))
			{
				player->spritescale = sqrt(player->spritescale*player->spritescale + CIRCLESCALE*CIRCLESCALE);
				player->runAction(ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE));
				circle->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
					, CCRANDOM_0_1()*bg->getContentSize().height));
			}
	}
}

void GameControler::move(PlayerVector* players,float &event_x, float &event_y)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	const float& backgroundscale = bg->get_scale();
	//存储背景和屏幕中心的移动参量
	float x = event_x - center.x;
	float y = event_y - center.y;
	float r = sqrt(x*x + y*y);
	//定义背景移动的速度参数
	float speed = SPEEDPARAMETER;

	//鼠标位于靠近屏幕中心位置时，背景移动速度稍作减小
	if (r < 16)
		speed = 0.5 + 0.05*r;
	//move_x,move_y表示事实上要移动的距离参量
	float move_bgx = x;
	float move_bgy = y;
	//定义平均小球放缩参数以作为背景移动的一个速度参数
	float averscale = 0;
	//移动玩家的小球
	for (auto player : players->playervector)
	{

		//玩家的相对坐标
		Vec2 point = player->getPosition();
		//存储每个玩家小球的移动参量
		player->x = event_x - point.x;
		player->y = event_y - point.y;
		//计算模长
		float r = sqrt(player->x*player->x + player->y*player->y);

		//鼠标靠近小球时，速度稍微减小
		player->speed = SPEEDPARAMETER;
		if (r < 16)
			player->speed = 0.5 + 0.05*r;

		float move_x = player->x;
		float move_y = player->y;
		averscale += player->spritescale;

		//判断边界情况
		if (
			(point.x <= 0 && player->x < 0)
			|| (point.x >= bg->getContentSize().width&&player->x > 0)
			)
		{
			move_x = 0;
			move_bgx = 0;
		}
		if (
			(point.y <= 0 && player->y < 0)
			|| (point.y >= bg->getContentSize().height&&player->y > 0)
			)
		{
			move_y = 0;
			move_bgy = 0;
		}
		if (move_x != 0 || move_y != 0) {
			player->setPosition(point + backgroundscale / 4 * (player->speed - 2 * player->spritescale)*Vec2(move_x / r, move_y / r) / backgroundscale);  //需除去放缩的比例
		}
	}
	averscale = averscale / players->playervector.size();

	//移动背景和屏幕中心
	//鼠标几乎处于屏幕中心时则不做移动
	if ((move_bgx != 0 || move_bgy != 0) && r > 1)
	{
		bg->setPosition(bg->getPosition() - backgroundscale / 4 * (speed - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r));
		//当鼠标未移动时，将上一次移动事件得到的鼠标位置与背景同步移动，以模拟鼠标的移动
		event_x = event_x + backgroundscale / 4 * (speed - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r).x / backgroundscale;
		event_y = event_y + backgroundscale / 4 * (speed - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r).y / backgroundscale;
	}
}

void GameControler::divide(PlayerVector* players)
{
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
				player->runAction(ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE));
				//克隆小球
				auto _player = player->playerclone();
				bg->addChild(_player, 2);
				//分裂后两小球拉开距离,设置动画
				FiniteTimeAction* action1 = (FiniteTimeAction *)MoveBy::create(0.5,
					14 * Vec2(_player->x / r, _player->y / r)*backgroundscale / 4);
				FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(0.5, _player->spritescale / DEFAULTBGSCALE);
				ActionInterval* action = Spawn::create(action1, action2, NULL);

				player->runAction(MoveBy::create(0.5, -6 * Vec2(player->x / r, player->y / r)*backgroundscale / 4));
				_player->runAction(EaseOut::create(action, 2));

				players->playervector.pushBack(_player);
				ifdivide = true;
			}
		}
	}
	if (ifdivide)
		scalebg(0.1); //放缩屏幕
}

void GameControler::scalebg(const float scaleparameter)
{
	float& backgroundscale = bg->get_scale();

	//限定放缩范围
	if (backgroundscale - scaleparameter >= 2.1 && backgroundscale - scaleparameter <= 5.9)
	{
		backgroundscale = backgroundscale - scaleparameter;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		Vec2 point = bg->getContentSize() / 2;

		FiniteTimeAction* action1 = //放缩后进行位移补偿
			(FiniteTimeAction *)MoveBy::create(1 / 30, scaleparameter * Vec2(center.x - point.x, center.y - point.y));
		FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(1 / 30, backgroundscale);
		ActionInterval* action = Spawn::create(action1, action2, NULL);
		bg->runAction(action);
	}
}

void GameControler::combine(PlayerVector* players)
{
	//判断是否进行合并操作
	bool ifcombine = false;

	for (auto player1 : players->playervector)
	{
		for (auto player2 : players->playervector)
		{
			//两小球都尚在背景上时判断能否合并
			if (player1 != player2&&player1->onbg&&player2->onbg)
			{
				if (isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
					player1->getContentSize().width / 2 * player1->spritescale, 0))
				{
					player1->spritescale = sqrt(player1->spritescale*player1->spritescale + player2->spritescale*player2->spritescale);
					player1->runAction(ScaleTo::create(0.5, player1->spritescale / DEFAULTBGSCALE));
					//处理被合并掉的小球
					player2->onbg = false;
					toerase.pushBack(player2);
					ifcombine = true;
				}
			}
		}
	}
	//删除小球
	for (auto player_toerase : toerase)
	{
		auto bg1 = (Node*)bg;
		bg1->removeChild(player_toerase);
		players->playervector.eraseObject(player_toerase);
	}
	toerase.clear();
	if (ifcombine)
		scalebg(-0.1); //放缩屏幕
}