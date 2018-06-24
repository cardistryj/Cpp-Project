#include"GameControler.h"
USING_NS_CC;
//定义小球速度参数默认值
#define SPEEDPARAMETER 1.3f*4/DEFAULTBGSCALE

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

bool GameControler::move(float &event_x, float &event_y)
{
	auto bg = (BackGround*)getChildByTag(bgTag);
	auto allplayers = (AllPlayersVector*)bg->getChildByTag(allplayersTag);
	auto humanplayers = *(allplayers->allPlayersVector.begin());

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	const float& backgroundscale = bg->get_scale();
	//存储背景和屏幕中心的移动参量
	float x = event_x - center.x;
	float y = event_y - center.y;
	float r = BackGround::lenth(x, y);

	//定义背景移动的速度参数
	float speed = SPEEDPARAMETER;

	//鼠标位于靠近屏幕中心位置时，背景移动速度稍作减小
	if (r < 16)
		speed = 0.5 + (SPEEDPARAMETER - 0.5) / 16 * r;
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
			float r = BackGround::lenth(player->x, player->y);

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
				player->speed = 0.5 + (SPEEDPARAMETER - 0.5) / 16 * r;

			if (player->x != 0 || player->y != 0) {
				player->setPosition(point + backgroundscale / 4 * (player->speed - player->spritescale)*
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
		bg->setPosition(bg->getPosition() - backgroundscale / 4 * (speed - averscale)*Vec2(x / r, y / r));
		//当鼠标未移动时，将上一次移动事件得到的鼠标位置与背景同步移动，以模拟鼠标的移动
		event_x = event_x + backgroundscale / 4 * (speed - averscale)*Vec2(x / r, y / r).x / backgroundscale;
		event_y = event_y + backgroundscale / 4 * (speed - averscale)*Vec2(x / r, y / r).y / backgroundscale;
	}

	return allplayers->if_survive();
}

void GameControler::move(float desitination_x, float desitination_y, PlayerVector* players)
{
	auto bg = (BackGround*)getChildByTag(bgTag);

	for (auto player : players->playervector) {
		Vec2 point = player->getPosition();
		player->x = desitination_x - point.x;
		player->y = desitination_y - point.y;
		float r = BackGround::lenth(player->x, player->y);
		player->speed = SPEEDPARAMETER;

		if (player->x != 0 || player->y != 0) {
			player->setPosition(point + bg->get_scale() / 4 * (player->speed - player->spritescale)
				*Vec2(player->x / r, player->y / r) / bg->get_scale());  //需除去放缩的比例
		}
	}
}

bool GameControler::traverse(int score)
{
	auto bg = getChildByTag(bgTag);
	auto circles = (Circles*)bg->getChildByTag(circlesTag);
	auto allplayers = (AllPlayersVector*)bg->getChildByTag(allplayersTag);
	auto virusvector = (VirusVector*)bg->getChildByTag(virusTag);

	bool if_eat_scretion = false;
	bool if_eat_virus = false;
	bool if_reduce_circles = (allplayers->if_survive()) || score > 830;
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
					float distance = BackGround::lenth(distanceVec.x, distanceVec.y);
					if (distance < min_distance)
					{
						min_distance = distance;
						players->closestfood = circle->getPosition();
					}
				}
				if (BackGround::isCircleCover(DEFAULTBGSCALE*(player->getPosition() - circle->getPosition()),
					player->getContentSize().width / 2 * player->spritescale,
					circle->getContentSize().width / 2 * CIRCLESCALE))
				{
					player->eat(circle);
					if (if_reduce_circles)
					{
						bg->removeChild(circle);
						circles->to_erase.pushBack(circle);
					}
					else
						circle->setPosition(cocos2d::Vec2(CCRANDOM_0_1()*bg->getContentSize().width
							, CCRANDOM_0_1()*bg->getContentSize().height));
					ifeat = true;
				}
			}
			if (!scretions.empty())
			{
				for (auto scretion : scretions)
				{
					if (players->ifAIplayer&&player == *(players->playervector.begin()))
					{
						Vec2 distanceVec = player->getPosition() - scretion->getPosition();
						float distance = BackGround::lenth(distanceVec.x, distanceVec.y);
						if (distance < min_distance)
						{
							min_distance = distance;
							players->closestfood = scretion->getPosition();
						}
					}
					if (BackGround::isCircleCover(DEFAULTBGSCALE*(player->getPosition() - scretion->getPosition()),
						player->getContentSize().width / 2 * player->spritescale,
						scretion->getContentSize().width / 2 * SCRETIONSCALE))
					{
						player->eat_scretion();
						scretion_toerase.pushBack(scretion);
						ifeat = true;
						if_eat_scretion = true;
					}
				}
			}
			for (auto virus : virusvector->virusvector)
			{
				if (BackGround::isCircleCover(DEFAULTBGSCALE*(player->getPosition() - virus->getPosition()),
					player->getContentSize().width / 2 * player->spritescale,
					virus->getContentSize().width / 2 * virus->get_scale())
					&& player->spritescale>virus->get_scale()
					)
				{
					players->eat_virus(player, virus);
					virusvector->to_erase.pushBack(virus);
					ifeat = true;
					if_eat_virus = true;
				}
			}
		}
		if (ifeat)
			players->set_scale();
	}
	if (if_eat_scretion)
		erase_scretion();
	if (if_eat_virus)
		virusvector->erase_virus();
	if (if_reduce_circles)
		circles->erase();

	allplayers->combine();
	return allplayers->check_playerdead();
}

float GameControler::inter_traverse()
{
	auto bg = (BackGround*)getChildByTag(bgTag);
	auto allplayers = (AllPlayersVector*)bg->getChildByTag(allplayersTag);
	for (auto players1 : allplayers->allPlayersVector) {
		for (auto players2 : allplayers->allPlayersVector) {
			if (players1 != players2) {
				if (players1->ifAIplayer) {
					//players1->aiControl(players2);
				}
				players1->eat_player(players2);
			}
		}
		if (players1->ifAIplayer)
			move(players1->desitination.x, players1->desitination.y, players1);
	}
	allplayers->erase_eated();
	auto humanplayers = *(allplayers->allPlayersVector.begin());
	return humanplayers->sum_scale;
}

void GameControler::virus_traverse(bool if_free)
{
	auto bg = getChildByTag(bgTag);
	auto virusvector = (VirusVector*)bg->getChildByTag(virusTag);
	auto spriteTexture = (SpriteBatchNode*)bg->getChildByTag(textureTag);
	auto texture = spriteTexture->getTexture();
	
	bool if_eat_scretion = false;
	int size = virusvector->virusvector.size();
	for (int i = 0; i<size; i++)
	{
		auto virus = *(virusvector->virusvector.begin() + i);
		for (auto scretion : scretions)
		{
			if (BackGround::isCircleCover(DEFAULTBGSCALE*(virus->getPosition() - scretion->getPosition()),
				virus->getContentSize().width / 2 * virus->get_scale(),
				scretion->getContentSize().width / 2 * SCRETIONSCALE))
			{
				virus->eat_scretion();
				scretion_toerase.pushBack(scretion);
				if_eat_scretion = true;
			}
		}
		if (virus->get_scale() > 0.12)
		{
			if (!if_free)
				virusvector->divide(virus);
		}
	}
	if (if_eat_scretion)
		erase_scretion();
}

void GameControler::erase_scretion() {  //删除分泌物
	auto bg = getChildByTag(bgTag);
	for (auto scretion : scretion_toerase)
	{
		bg->removeChild(scretion);
		scretions.eraseObject(scretion);
	}
}