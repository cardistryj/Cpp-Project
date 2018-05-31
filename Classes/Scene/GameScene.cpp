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
	bg->setTag(111);
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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(111);
		//�õ��¼��Ա�����ģ������
		Vec2 eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));

		//�õ��¼�����Ļ���ĵ����λ��
		auto playersprite = *players.playervector.begin();
		x = eventpoint.x - playersprite->getPosition().x;
		y = eventpoint.y - playersprite->getPosition().y;

		//����ģ��r
		r = sqrt(x*x + y*y);
		if (x != 0 || y != 0)
			this->scheduleUpdate();
	};

	listenerMouse->onMouseDown = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(111);
		//�õ��¼��Ա�����ģ������
		Vec2 eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));

		//�õ��¼�����Ļ���ĵ����λ��
		auto playersprite = *players.playervector.begin();
		x = eventpoint.x - playersprite->getPosition().x;
		y = eventpoint.y - playersprite->getPosition().y;

		//����ģ��r
		r = sqrt(x*x + y*y);
		gamecontroler.divide(bg, x, y, backgroundscale, r);

	};

	//auto listenerKeyboard = EventListenerKeyboard::create();


	/*
	listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event *event) {
		switch (keycode) {
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
			//////////////////code to divide
			break;
		case EventKeyboard::KeyCode::KEY_W:
			y++;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			y--;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			x--;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			x++;
			break;
		default:
			break;
		}
		x = (x > 1) ? 1 : x;
		x = (x < -1) ? -1 : x;
		y = (y > 1) ? 1 : y;
		y = (y < -1) ? -1 : y;
		r = sqrt(x*x + y*y);
		if (x!= 0||y!=0)
			this->scheduleUpdate();
	};

	listenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode keycode, Event *event) {
		if (keycode == EventKeyboard::KeyCode::KEY_W)
			y--;
		if (keycode == EventKeyboard::KeyCode::KEY_S)
			y++;
		if (keycode == EventKeyboard::KeyCode::KEY_A)
			x++;
		if (keycode == EventKeyboard::KeyCode::KEY_D)
			x--;
	};
	*/

	//ע�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	for(auto player:players.playervector)
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, player);
		//eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, player);
	
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
	auto bg = this->getChildByTag(111);
	gamecontroler.eat(bg, backgroundscale);
	gamecontroler.move(bg, x, y, backgroundscale,r);
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}