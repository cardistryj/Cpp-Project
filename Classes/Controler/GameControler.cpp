#include"GameControler.h"

void GameControler::eat(cocos2d::Node* bg,float backgroundscale)
{
	for (auto circle : circles->spriteVector)
	{
		for (auto player : players->playervector)
			if (isCircleCover(backgroundscale*(player->getPosition() - circle->getPosition()),
				player->getContentSize().width / 2 * player->spritescale,
				circle->getContentSize().width / 2* circles->circleScale))
			{
				player->spritescale = sqrt(player->spritescale*player->spritescale + 0.03*0.03);
				player->setScale(player->spritescale / backgroundscale);
				circle->setPosition(cocos2d::Vec2(CCRANDOM_0_1()*bg->getContentSize().width
					, CCRANDOM_0_1()*bg->getContentSize().height));
			}
	}
}

void GameControler::move(cocos2d::Node* bg, float x, float y,const float backgroundscale, float r)
{
	//move_x,move_y��ʾ��ʵ��Ҫ�ƶ��ľ������
	float move_x = x;
	float move_y = y;
	for (auto player : players->playervector)
	{
		//��ҵ��������
		cocos2d::Vec2 point = player->getPosition();
		//�жϱ߽����
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
			player->setPosition(point + cocos2d::Vec2(move_x / r, move_y / r) / backgroundscale);  //���ȥ�����ı���
			bg->setPosition(bg->getPosition() - cocos2d::Vec2(move_x / r, move_y / r));
		}
	}
}
