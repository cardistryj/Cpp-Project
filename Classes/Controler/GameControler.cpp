#include"GameControler.h"
USING_NS_CC;

//�����ٶȲ���Ĭ��ֵ
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
	//����С����������ҵ�С�������ж��������
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
	//�洢��������Ļ���ĵ��ƶ�����
	float x = event_x - center.x;
	float y = event_y - center.y;
	float r = sqrt(x*x + y*y);
	//���屳���ƶ����ٶȲ���
	float speed = SPEEDPARAMETER;

	//���λ�ڿ�����Ļ����λ��ʱ�������ƶ��ٶ�������С
	if (r < 16)
		speed = 0.5 + 0.05*r;
	//move_x,move_y��ʾ��ʵ��Ҫ�ƶ��ľ������
	float move_bgx = x;
	float move_bgy = y;
	//����ƽ��С�������������Ϊ�����ƶ���һ���ٶȲ���
	float averscale = 0;
	//�ƶ���ҵ�С��
	for (auto player : players->playervector)
	{

		//��ҵ��������
		Vec2 point = player->getPosition();
		//�洢ÿ�����С����ƶ�����
		player->x = event_x - point.x;
		player->y = event_y - point.y;
		//����ģ��
		float r = sqrt(player->x*player->x + player->y*player->y);

		//��꿿��С��ʱ���ٶ���΢��С
		player->speed = SPEEDPARAMETER;
		if (r < 16)
			player->speed = 0.5 + 0.05*r;

		float move_x = player->x;
		float move_y = player->y;
		averscale += player->spritescale;

		//�жϱ߽����
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
			player->setPosition(point + backgroundscale / 4 * (player->speed - 2 * player->spritescale)*Vec2(move_x / r, move_y / r) / backgroundscale);  //���ȥ�����ı���
		}
	}
	averscale = averscale / players->playervector.size();

	//�ƶ���������Ļ����
	//��꼸��������Ļ����ʱ�����ƶ�
	if ((move_bgx != 0 || move_bgy != 0) && r > 1)
	{
		bg->setPosition(bg->getPosition() - backgroundscale / 4 * (speed - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r));
		//�����δ�ƶ�ʱ������һ���ƶ��¼��õ������λ���뱳��ͬ���ƶ�����ģ�������ƶ�
		event_x = event_x + backgroundscale / 4 * (speed - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r).x / backgroundscale;
		event_y = event_y + backgroundscale / 4 * (speed - 2 * averscale)*Vec2(move_bgx / r, move_bgy / r).y / backgroundscale;
	}
}

void GameControler::divide(PlayerVector* players)
{
	//�ж��Ƿ�����˷��Ѳ���
	bool ifdivide = false;

	const float& backgroundscale = bg->get_scale();
	//���Ѳ�����Ҫ������������Ԫ�أ�ʹ�ó�ʼ������Сsize�����б���
	int size = players->playervector.size();
	if (size < MAXPLAYERNUMBER)
	{
		for (int i = 0; i < size; i++)
		{
			Player* player = *(players->playervector.begin() + i);
			//����һ����С�ķ��ɽ��з���
			if (player->spritescale > 2 * STARTPLSCALE) {

				float r = sqrt(player->x*player->x + player->y*player->y);
				//�ߴ���С��һ��
				player->spritescale = player->spritescale / sqrt(2);
				player->runAction(ScaleTo::create(0.5, player->spritescale / DEFAULTBGSCALE));
				//��¡С��
				auto _player = player->playerclone();
				bg->addChild(_player, 2);
				//���Ѻ���С����������,���ö���
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
		scalebg(0.1); //������Ļ
}

void GameControler::scalebg(const float scaleparameter)
{
	float& backgroundscale = bg->get_scale();

	//�޶�������Χ
	if (backgroundscale - scaleparameter >= 2.1 && backgroundscale - scaleparameter <= 5.9)
	{
		backgroundscale = backgroundscale - scaleparameter;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		Vec2 point = bg->getContentSize() / 2;

		FiniteTimeAction* action1 = //���������λ�Ʋ���
			(FiniteTimeAction *)MoveBy::create(1 / 30, scaleparameter * Vec2(center.x - point.x, center.y - point.y));
		FiniteTimeAction* action2 = (FiniteTimeAction*)ScaleTo::create(1 / 30, backgroundscale);
		ActionInterval* action = Spawn::create(action1, action2, NULL);
		bg->runAction(action);
	}
}

void GameControler::combine(PlayerVector* players)
{
	//�ж��Ƿ���кϲ�����
	bool ifcombine = false;

	for (auto player1 : players->playervector)
	{
		for (auto player2 : players->playervector)
		{
			//��С�����ڱ�����ʱ�ж��ܷ�ϲ�
			if (player1 != player2&&player1->onbg&&player2->onbg)
			{
				if (isCircleCover(DEFAULTBGSCALE*(player1->getPosition() - player2->getPosition()),
					player1->getContentSize().width / 2 * player1->spritescale, 0))
				{
					player1->spritescale = sqrt(player1->spritescale*player1->spritescale + player2->spritescale*player2->spritescale);
					player1->runAction(ScaleTo::create(0.5, player1->spritescale / DEFAULTBGSCALE));
					//�����ϲ�����С��
					player2->onbg = false;
					toerase.pushBack(player2);
					ifcombine = true;
				}
			}
		}
	}
	//ɾ��С��
	for (auto player_toerase : toerase)
	{
		auto bg1 = (Node*)bg;
		bg1->removeChild(player_toerase);
		players->playervector.eraseObject(player_toerase);
	}
	toerase.clear();
	if (ifcombine)
		scalebg(-0.1); //������Ļ
}