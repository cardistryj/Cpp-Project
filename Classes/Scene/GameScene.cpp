#include "GameScene.h"
#include"SettingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	Vect gravity(0, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	//////////////////////////////
	if (!LayerColor::initWithColor(Color4B(248,248,255,255)))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建并添加背景
	auto bg = BackGround::create();
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setColor(Color3B(245, 245, 245));
	bg->setTag(bgTag);
	bg->setCascadeOpacityEnabled(true);  //便于调整整体透明度
	this->addChild(bg, 1);

	//为背景添加碰撞层
	auto size = bg->getContentSize();
	size.width += DEFAULTWIDTH /2 ;
	size.height += DEFAULTWIDTH /2 ;
	auto body = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, DEFAULTWIDTH);
	bg->setPhysicsBody(body);

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
	Layer::onEnter();
	log("GameScene onEnter");
	//初始化默认事件坐标为屏幕中心以防止未定义情况
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = (BackGround*)getChildByTag(bgTag);
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
		if (!ifPause)
		{
			if (e->getScrollY()<0)
				gamecontroler->scalebg(-0.2);
			else
				gamecontroler->scalebg(0.2);
		}
	};

	auto listenerKeyboard = EventListenerKeyboard::create();

	listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event *event) {
		auto gamecontroler = (GameControler*)getChildByTag(controlerTag);
		auto players = (PlayerVector*)getChildByTag(playersTag);
		auto bg = (BackGround*)getChildByTag(bgTag);
		if (!ifPause) {
			switch (keycode) {
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				pause();
				ifPause = true;
				unscheduleUpdate();
				break;
			case  EventKeyboard::KeyCode::KEY_SPACE:
				gamecontroler->divide(players);
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				gamecontroler->scalebg(-0.2);
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				gamecontroler->scalebg(0.2);
				break;
			default:
				break;
			}
		}
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	//只在第一次进入场景时注册监听器
	//避免popscene后造成的一些未定义情况
	if (ifFirstEnter)
	{
		eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this->getChildByTag(bgTag));
		eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this->getChildByTag(bgTag));
	}
	ifFirstEnter = false;

	//刷新屏幕
	if (!ifPause)
		scheduleUpdate();
}

void GameScene::onExit()
{
	Layer::onExit();
	log("GameScene onExit");
	unscheduleUpdate();
}

void GameScene::update(float dt)	//使用update函数移动背景
{
	auto gamecontroler = (GameControler*)getChildByTag(controlerTag);
	auto circles = (Circles*)getChildByTag(circlesTag);
	auto players = (PlayerVector*)getChildByTag(playersTag);

	gamecontroler->move(players,event_x,event_y);
	gamecontroler->eat(circles,players);
	gamecontroler->combine(players);
}

void GameScene::pause()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = (BackGround*)getChildByTag(bgTag);
	bg->runAction(FadeTo::create(0.5, 80));

	//添加暂停菜单
	auto continuelabel = Label::createWithTTF("Continue", "fonts/Marker Felt.ttf", 24);
	continuelabel->setColor(Color3B::RED);
	auto continueItem = MenuItemLabel::create(continuelabel, CC_CALLBACK_1(GameScene::menuContinueCallback, this));
	continueItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 80));

	auto restartlabel = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 24);
	restartlabel->setColor(Color3B::RED);
	auto restartItem = MenuItemLabel::create(restartlabel, CC_CALLBACK_1(GameScene::menuRestartCallback, this));
	restartItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 130));

	auto settinglabel = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 24);
	settinglabel->setColor(Color3B::RED);
	auto settingItem = MenuItemLabel::create(settinglabel, CC_CALLBACK_1(GameScene::menuSettingCallback, this));
	settingItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 180));

	auto helplabel = Label::createWithTTF("Help", "fonts/Marker Felt.ttf", 24);
	helplabel->setColor(Color3B::RED);
	auto helpItem = MenuItemLabel::create(helplabel, CC_CALLBACK_1(GameScene::menuHelpCallback, this));
	helpItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 230));

	auto exitlabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
	exitlabel->setColor(Color3B::RED);
	auto exitItem = MenuItemLabel::create(exitlabel, CC_CALLBACK_1(GameScene::menuExitCallback, this));
	exitItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 280));

	auto menu = Menu::create(continueItem, restartItem, settingItem, helpItem, exitItem, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setTag(pausemenuTag);
	this->addChild(menu, 2);

}

void GameScene::menuContinueCallback(cocos2d::Ref *pSender)
{
	ifPause = false;
	removeChildByTag(pausemenuTag);  //移除暂停菜单

	auto bg = (BackGround*)this->getChildByTag(bgTag);
	bg->runAction(FadeTo::create(0.5, 255));
	scheduleUpdate();
}

void GameScene::menuRestartCallback(cocos2d::Ref *pSender)
{
	auto sc = GameScene::createScene();
	auto reScene = TransitionCrossFade::create(2.0, sc);
	Director::getInstance()->replaceScene(reScene);
}

void GameScene::menuSettingCallback(cocos2d::Ref* pSender)
{
	removeChildByTag(pausemenuTag);
	auto sc = SettingScene::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void GameScene::menuHelpCallback(cocos2d::Ref* pSender)
{
	//
}

void GameScene::menuExitCallback(cocos2d::Ref *pSender)
{
	auto sc = HelloWorld::createScene();
	auto reScene = TransitionTurnOffTiles::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);
}