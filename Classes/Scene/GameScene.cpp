#include "GameScene.h"
#include "SimpleAudioEngine.h"
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

	//双层背景
	auto bg0 = Sprite::create("background.png");
	bg0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg0->setScale(1.3);
	bg0->setColor(Color3B(245, 245, 245));
	this->addChild(bg0, 0);

	//创建并添加上层背景
	auto bg = BackGround::create();
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setTag(bgTag);
	this->addChild(bg, 1);

	//创建玩家容器
	auto players = PlayerVector::create();
	players->setTag(playersTag);
	this->addChild(players, 1);
	//初始化玩家容器
	players->init_on(bg);

	auto circles = Circles::create();
	circles->setTag(circlesTag);
	this->addChild(circles, 1);
	//在屏幕中添加小球
	circles->addcirclesto(bg);

	//初始化控制器
	auto gamecontroler = GameControler::create(bg);
	gamecontroler->setTag(controlerTag);
	this->addChild(gamecontroler, 1);
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//初始化默认事件坐标为屏幕中心以防止未定义情况
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = (BackGround*)this->getChildByTag(bgTag);
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	event_x = center.x;
	event_y = center.y;
    
	//使用鼠标操作
	auto listenerMouse = EventListenerMouse::create();
	
	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = (BackGround*)this->getChildByTag(bgTag);
		//得到事件对背景的模型坐标
		auto eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
		event_x = eventpoint.x;
		event_y = eventpoint.y;
	};
	
	//使用鼠标滚轮进行放缩屏幕
	listenerMouse->onMouseScroll = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto gamecontroler = (GameControler*)this->getChildByTag(controlerTag);
		if (e->getScrollY()<0)
			gamecontroler->scalebg(-0.2);
		else
			gamecontroler->scalebg(0.2);
	};

	auto listenerKeyboard = EventListenerKeyboard::create();

	listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event *event) {
		auto gamecontroler = (GameControler*)this->getChildByTag(controlerTag);
		auto players = (PlayerVector*)this->getChildByTag(playersTag);
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
			gamecontroler->divide(players);
	};

	//注册监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this->getChildByTag(bgTag));
    eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this->getChildByTag(bgTag));

	//刷新屏幕
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
	auto gamecontroler = (GameControler*)this->getChildByTag(controlerTag);
	auto circles = (Circles*)this->getChildByTag(circlesTag);
	auto players = (PlayerVector*)this->getChildByTag(playersTag);

	gamecontroler->move(players,event_x,event_y);
	gamecontroler->eat(circles,players);
	gamecontroler->combine(players);
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}