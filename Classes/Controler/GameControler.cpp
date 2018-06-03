#include"GameControler.h"
USING_NS_CC;
//定义速度参数
#define SPEEDPARAMETER 1.3
void GameControler::eat(Node* bg)
{
	//遍历小球容器和玩家的小球容器判断吞噬情况
	for (auto circle : circles->spriteVector)
	{
		for (auto player : players->playervector)
			if (isCircleCover(DEFAULTBGSCALE*(player->getPosition() - circle->getPosition()),
				player->getContentSize().width / 2 * player->spritescale,
				circle->getContentSize().width / 2* CIRCLESCALE))
			{
				player->spritescale = sqrt(player->spritescale*player->spritescale + CIRCLESCALE*CIRCLESCALE);
				player->runAction(ScaleTo::create(0.5,player->spritescale / DEFAULTBGSCALE));
				circle->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
					, CCRANDOM_0_1()*bg->getContentSize().height));
			}
	}
}

void GameControler::move(Node* bg,  float x, float y,const float backgroundscale)
{
	//move_x,move_y表示事实上要移动的距离参量
	float move_bgx = x;
	float move_bgy = y;
	//定义平均小球放缩参数以作为背景移动的参数
	float averscale = 0;
	//移动玩家的小球
	for (auto player : players->playervector)
	{
		float r = sqrt(player->x*player->x + player->y*player->y);
		float move_x = player->x;
		float move_y = player->y;
		averscale += player->spritescale;
		//玩家的相对坐标
		Vec2 point = player->getPosition();
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
			player->setPosition(point + backgroundscale / 4 *(SPEEDPARAMETER - 2 * player->spritescale)*Vec2(move_x / r, move_y / r) / backgroundscale);  //需除去放缩的比例
		}
	}
	averscale = averscale / players->playervector.size();

	//移动背景和屏幕中心
	float r = sqrt(x*x + y*y);
	if (move_bgx != 0 || move_bgy != 0)
		bg->setPosition(bg->getPosition() - backgroundscale / 4* (SPEEDPARAMETER - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r));
}

bool GameControler::divide(Node* bg,float& backgroundscale)
{
	bool ifdivide = false;
	int size = players->playervector.size();
	if (size < 21)
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
				auto _player = player->playerclone();
				bg->addChild(_player, 2);
				//分裂后两小球拉开距离,设置动画
				FiniteTimeAction* action1 = (FiniteTimeAction *)MoveBy::create(0.5, 16 * Vec2(_player->x / r, _player->y / r));
				FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(0.5, _player->spritescale / DEFAULTBGSCALE);
				ActionInterval* action = Spawn::create(action1, action2, NULL);

				player->runAction(MoveBy::create(0.5, -6 * Vec2(player->x / r, player->y / r)));
				_player->runAction(EaseOut::create(action, 2));

				players->playervector.pushBack(_player);
				ifdivide = true;
			}
		}
	}
	if (ifdivide)
	{
		scalebg(bg, backgroundscale, 0.2); //放缩屏幕
	}
	return ifdivide;
}

void GameControler::scalebg(Node* bg, float& backgroundscale, float scaleparameter)
{
	float _backgroundscale = backgroundscale - scaleparameter;;
	//限定放缩范围
	if (_backgroundscale >= 2.1 && _backgroundscale <= 5.9)
	{
		backgroundscale = backgroundscale - scaleparameter;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		Vec2 point = bg->getContentSize() / 2;

		FiniteTimeAction* action1 = //放缩后进行位移补偿
			(FiniteTimeAction *)MoveBy::create(1/30, scaleparameter * Vec2(center.x - point.x, center.y - point.y));
		FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(1/30, backgroundscale);
		ActionInterval* action = Spawn::create(action1, action2, NULL);
		bg->runAction(action);
	}
}

void GameControler::combine(Node*bg)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Vector<Player*> toerase;
	for (auto player1 : players->playervector)
	{
		for (auto player2:players->playervector)
		{
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
				}
			}
		}
	}
	for (auto player_toerase : toerase)
	{
		bg->removeChild(player_toerase);
		players->playervector.eraseObject(player_toerase);
	}
}