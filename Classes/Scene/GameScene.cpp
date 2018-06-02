#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include<cmath>
USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	//////////////////////////////
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������ӱ���
	auto bg = Sprite::create("background.png");
	bg->setScale(backgroundscale);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setTag(bgTag);
	this->addChild(bg, 0);

	circles.init();
	//����Ļ�����С��
	circles.addcirclesto(bg, backgroundscale);
	//������ʼ�������
	players.init_on(bg, backgroundscale);

	//��ʼ��������
	gamecontroler.init(&circles, &players);
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//ʹ��������
	auto listenerMouse = EventListenerMouse::create();
	
	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(bgTag);
		//�õ��¼��Ա�����ģ������
		auto eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
		//�洢ÿ�����С����ƶ�����
		for (auto player : players.playervector)
		{
			player->x = eventpoint.x - player->getPosition().x;
			player->y = eventpoint.y - player->getPosition().y;
		}
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		//�洢��������Ļ���ĵ��ƶ�����
		x = eventpoint.x - center.x,
		y = eventpoint.y - center.y;

		if (x != 0 || y != 0)
			this->scheduleUpdate();
	};
	
	//���������з���
	listenerMouse->onMouseDown = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(bgTag);
		
		gamecontroler.divide(bg, backgroundscale);

	};
	
	//ʹ�������ֽ��з�����Ļ
	listenerMouse->onMouseScroll = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(bgTag);
		if (e->getScrollY()<0)
			gamecontroler.scalebg(bg, backgroundscale, -0.2);
		else
			gamecontroler.scalebg(bg, backgroundscale, 0.2);
	};

    /*
	auto listenerKeyboard = EventListenerKeyboard::create();
	
	listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event *event) {
		EventKeyboard* e = (EventKeyboard*)event;
		if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		{
			auto bg = this->getChildByTag(bgTag);
			gamecontroler.divide(bg, backgroundscale);
		}
	};*/
	

	//ע�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this->getChildByTag(bgTag));
    //eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this->getChildByTag(bgTag));
	
}

void GameScene::onExit()
{
	Scene::onExit();
	log("GameScene onExit");
	//unscheduleUpdate();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void GameScene::update(float dt)	//ʹ��update�����ƶ�����
{
	auto bg = this->getChildByTag(bgTag);
	gamecontroler.move(bg, x, y, backgroundscale);

	gamecontroler.eat(bg);
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}