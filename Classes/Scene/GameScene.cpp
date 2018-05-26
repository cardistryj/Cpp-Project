#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include"color.h"
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

	//create and add background
	auto bg = Sprite::create("startbackground.png");
	bg->setScale(3.0);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setTag(111);
	this->addChild(bg, 0);

	//create a player
	auto player = Sprite::create("ball.png");
	player->setColor(Color3B(Cyan));
	player->setScale(0.05);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	player->setTag(123);
	this->addChild(player, 2);

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//use Mouse to move
	auto listenerMouse = EventListenerMouse::create();
	//use BackSpace to divide into two part
	auto listenerKeyboard = EventListenerKeyboard::create();
	/*
	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto player = this->getChildByTag(123);

		//get relative displacement
		x = e->getCursorX() - player->getPosition().x;
		y = e->getCursorY() - player->getPosition().y;
		r = 0;
		this->scheduleUpdate();
	};*/

	listenerMouse->onMouseDown = [](Event *event) {
		////////////code to divive
	};

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
		r = 0;
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


	//register eventdispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, getChildByTag(123));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, getChildByTag(123));
}

void GameScene::onExit()
{
	Scene::onExit();
	log("GameScene onExit");
	unscheduleUpdate();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void GameScene::update(float dt)	//use update to move background
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = this->getChildByTag(111);
	auto player = this->getChildByTag(123);

	//get relative coordinates
	Vec2 point = bg->convertToNodeSpace(player->getPosition());

	//move by a unit vector
	//judge if moved to the fringe
	float move_x = x;
	float move_y = y; 
	if (
		(point.x <= 0 && x < 0)
		|| (point.x >= bg->getContentSize().width&&x > 0)
		)
		move_x = 0;
	else if (
		(point.y <= 0 && y < 0)
		|| (point.y >= bg->getContentSize().height&&y > 0)
		)
		move_y = 0;
	if (move_x != 0 || move_y != 0) {
		r = sqrt(move_x*move_x + move_y*move_y);
		bg->setPosition(bg->getPosition() - Vec2(move_x / r, move_y / r));
	}
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}