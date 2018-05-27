#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include"GameControler.h"
#include"color.h"
#include<cmath>



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

	////添加小球
	//创建纹理缓存对象
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("ball.png");

	//使用时间初始化随机数种子
	srand((unsigned)time(NULL));

	//初始化Vector
	spriteVector = Vector<Sprite*>(int(MAX_NUMBER_PARAMETER*backgroundscale));
	for (int i = 0; i < int(MAX_NUMBER_PARAMETER*backgroundscale); i++){
		//使用纹理生成小球
		auto sprite = CCSprite::createWithTexture(texture);
		//获得0~12的随机数
		unsigned randomnumber = rand() % 12;
		sprite->setColor(Color3B(**(color + randomnumber), *(*(color + randomnumber) + 1), *(*(color + randomnumber) + 2)));
		sprite->setScale(0.03/backgroundscale);
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));
		bg->addChild(sprite, 1);  //添加至背景节点便于整体的放缩
		spriteVector.pushBack(sprite);
	}

	unsigned randomnumber = rand() % 12;
	//创建玩家
	auto playersprite= Sprite::create("ball.png");
	playersprite->setColor(Color3B(**(color+randomnumber),*(*(color+randomnumber)+1), *(*(color + randomnumber) + 2)));
	playersprite->setScale(0.04/ backgroundscale);
	playersprite->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2));
	playersprite->setTag(123);
	bg->addChild(playersprite, 2);  ////添加至背景节点便于整体的放缩

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//使用鼠标操作
	auto listenerMouse = EventListenerMouse::create();
	//auto listenerKeyboard = EventListenerKeyboard::create();
	auto bg = this->getChildByTag(111);

	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(111);

		//得到事件对背景的模型坐标
		Vec2 eventpoint= bg->convertToNodeSpace(Vec2(e->getCursorX(),e->getCursorY()));

		//得到事件与玩家的相对位移
		x = eventpoint.x - (bg->getChildByTag(123))->getPosition().x;
		y = eventpoint.y - (bg->getChildByTag(123))->getPosition().y;

		//计算模长r
		r = sqrt(x*x + y*y);
		if (x != 0 || y != 0)
			this->scheduleUpdate();
	};

	listenerMouse->onMouseDown = [&](Event *event) {
		//player.divide();
	};
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
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, bg->getChildByTag(123));
	//eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, bg->getChildByTag(123));
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
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = this->getChildByTag(111);
	auto sprite = bg->getChildByTag(123);

	//玩家的相对坐标
	Vec2 point = sprite->getPosition();

	//move_x,move_y表示事实上要移动的距离参量
	float move_x = x;
	float move_y = y; 

	//判断边界情况
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
			sprite->setPosition(point + Vec2(move_x / r, move_y / r)/ backgroundscale);  //需除去放缩的比例
			bg->setPosition(bg->getPosition() - Vec2(move_x / r, move_y / r));
	}
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}