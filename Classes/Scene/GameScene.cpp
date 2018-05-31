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

	//创建并添加背景
	auto bg = Sprite::create("background.png");
	bg->setScale(backgroundscale);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setTag(111);
	this->addChild(bg, 0);

	circles.init();
	//在屏幕中添加小球
	circles.addcirclesto(bg, backgroundscale);
	//创建初始玩家容器
	players.init_on(bg, backgroundscale);
	//初始化控制器
	gamecontroler.init(&circles, &players);
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//使用鼠标操作
	auto listenerMouse = EventListenerMouse::create();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(111);
		//得到事件对背景的模型坐标
		Vec2 eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));

		//得到事件与屏幕中心的相对位移
		auto playersprite = *players.playervector.begin();
		x = eventpoint.x - playersprite->getPosition().x;
		y = eventpoint.y - playersprite->getPosition().y;

		//计算模长r
		r = sqrt(x*x + y*y);
		if (x != 0 || y != 0)
			this->scheduleUpdate();
	};

	listenerMouse->onMouseDown = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(111);
		//得到事件对背景的模型坐标
		Vec2 eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));

		//得到事件与屏幕中心的相对位移
		auto playersprite = *players.playervector.begin();
		x = eventpoint.x - playersprite->getPosition().x;
		y = eventpoint.y - playersprite->getPosition().y;

		//计算模长r
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

	//注册监听器
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

void GameScene::update(float dt)	//使用update函数移动背景
{
	auto bg = this->getChildByTag(111);
	gamecontroler.eat(bg, backgroundscale);
	gamecontroler.move(bg, x, y, backgroundscale,r);
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}