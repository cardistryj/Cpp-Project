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
	bg->setTag(bgTag);
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
	
	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(bgTag);
		//得到事件对背景的模型坐标
		auto eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
		//存储每个玩家小球的移动参量
		for (auto player : players.playervector)
		{
			player->x = eventpoint.x - player->getPosition().x;
			player->y = eventpoint.y - player->getPosition().y;
		}
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		//存储背景和屏幕中心的移动参量
		x = eventpoint.x - center.x,
		y = eventpoint.y - center.y;

		if (x != 0 || y != 0)
			this->scheduleUpdate();
	};
	
	//单击鼠标进行分裂
	listenerMouse->onMouseDown = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(bgTag);
		gamecontroler.divide(bg, backgroundscale);
	};
	
	//使用鼠标滚轮进行放缩屏幕
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
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto bg = this->getChildByTag(bgTag);
		switch (keycode) {
		case EventKeyboard::KeyCode::KEY_SPACE:
			gamecontroler.divide(bg, backgroundscale);
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
		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		auto eventpoint = center + 40 * Vec2(x, y);
		for (auto player : players.playervector)
		{
			player->x = eventpoint.x - player->getPosition().x;
			player->y = eventpoint.y - player->getPosition().y;
		}
		if (x != 0 || y != 0)
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
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto bg = this->getChildByTag(bgTag);
		auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		auto eventpoint = center + 40 * Vec2(x, y);
		for (auto player : players.playervector)
		{
			player->x = eventpoint.x - player->getPosition().x;
			player->y = eventpoint.y - player->getPosition().y;
		}
	};*/


	//注册监听器
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

void GameScene::update(float dt)	//使用update函数移动背景
{
	auto bg = this->getChildByTag(bgTag);
	gamecontroler.move(bg, x, y, backgroundscale);
	gamecontroler.eat(bg);
	gamecontroler.combine(bg);
}

void GameScene::OnCallFuncN(Node *pSender)
{
	auto bg = this->getChildByTag(bgTag);
	gamecontroler.combine(bg);
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}