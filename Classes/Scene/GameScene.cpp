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
	//初始化默认鼠标事件坐标为屏幕中心以防止未定义情况
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = this->getChildByTag(bgTag);
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	event_x = center.x;
	event_y = center.y;
	
	//使用鼠标操作
	auto listenerMouse = EventListenerMouse::create();
	
	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(bgTag);
		//得到事件对背景的模型坐标
		auto eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
		event_x = eventpoint.x;
		event_y = eventpoint.y;


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
	
   
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event *event) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto bg = this->getChildByTag(bgTag);
		switch (keycode) {
		case EventKeyboard::KeyCode::KEY_SPACE:
			gamecontroler.divide(bg, backgroundscale);
			break;
		}
	};


	//注册监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this->getChildByTag(bgTag));
    eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this->getChildByTag(bgTag));
	this->scheduleUpdate();
}

void GameScene::onExit()
{
	Scene::onExit();
	log("GameScene onExit");
	unscheduleUpdate();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void GameScene::update(float dt)	//使用update函数移动背景
{
	auto bg = this->getChildByTag(bgTag);
	gamecontroler.move(bg,backgroundscale,event_x,event_y);
	gamecontroler.eat(bg);
	gamecontroler.combine(bg,backgroundscale);
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}