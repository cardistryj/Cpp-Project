#include"GameControler.h"
USING_NS_CC;

void GameControler::eat(Node* bg,float backgroundscale)
{
	//遍历小球容器和玩家的小球容器判断吞噬情况
	for (auto circle : circles->spriteVector)
	{
		for (auto player : players->playervector)
			if (isCircleCover(backgroundscale*(player->getPosition() - circle->getPosition()),
				player->getContentSize().width / 2 * player->spritescale,
				circle->getContentSize().width / 2* CIRCLESCALE))
			{
				player->spritescale = sqrt(player->spritescale*player->spritescale + CIRCLESCALE*CIRCLESCALE);
				player->runAction(ScaleTo::create(0.5,player->spritescale / backgroundscale));
				circle->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
					, CCRANDOM_0_1()*bg->getContentSize().height));
			}
	}
}

void GameControler::move(Node* bg, float x, float y,const float backgroundscale, float r)
{
	//move_x,move_y表示事实上要移动的距离参量
	float move_x = x;
	float move_y = y;
	for (auto player : players->playervector)
	{
		//玩家的相对坐标
		Vec2 point = player->getPosition();
		//判断边界情况
		if (
			(point.x <= 0 && x < 0)
			|| (point.x >= bg->getContentSize().width&&x > 0)
			)
			move_x = 0;
		if (
			(point.y <= 0 && y < 0)
			|| (point.y >= bg->getContentSize().height&&y > 0)
			)
			move_y = 0;
		if (move_x != 0 || move_y != 0) {
			player->setPosition(point + Vec2(move_x / r, move_y / r) / backgroundscale);  //需除去放缩的比例
		}
	}
	bg->setPosition(bg->getPosition() - Vec2(move_x / r, move_y / r));
}

void GameControler::divide(Node* bg, float x, float y, const float backgroundscale, float r)
{
	int size = players->playervector.size();
	for (int i = 0; i < size; i++)
	{
		Player* player = *(players->playervector.begin() + i);
		if (player->spritescale > 3 * CIRCLESCALE) {

			//尺寸缩小至一半
			player->spritescale = player->spritescale / 2;
			player->runAction(ScaleTo::create(0.5, player->spritescale / backgroundscale));
			auto _player = player->playerclone();
			bg->addChild(_player, 2);
			FiniteTimeAction* action1 = (FiniteTimeAction *)MoveBy::create(0.5, 15 * Vec2(x / r, y / r));
			FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(0.5, _player->spritescale / backgroundscale);
			ActionInterval* action = Spawn::create(action1, action2, NULL);

			_player->runAction(EaseOut::create(action, 2));
			players->playervector.pushBack(_player);
		}
	}
}
