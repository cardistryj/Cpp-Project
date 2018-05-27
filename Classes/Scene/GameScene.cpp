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

	//��������ӱ���
	auto bg = Sprite::create("background.png");
	bg->setScale(backgroundscale);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setTag(111);
	this->addChild(bg, 0);

	////���С��
	//�������������
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("ball.png");

	//ʹ��ʱ���ʼ�����������
	srand((unsigned)time(NULL));

	//��ʼ��Vector
	spriteVector = Vector<Sprite*>(int(MAX_NUMBER_PARAMETER*backgroundscale));
	for (int i = 0; i < int(MAX_NUMBER_PARAMETER*backgroundscale); i++){
		//ʹ����������С��
		auto sprite = CCSprite::createWithTexture(texture);
		//���0~12�������
		unsigned randomnumber = rand() % 12;
		sprite->setColor(Color3B(**(color + randomnumber), *(*(color + randomnumber) + 1), *(*(color + randomnumber) + 2)));
		sprite->setScale(0.03/backgroundscale);
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));
		bg->addChild(sprite, 1);  //����������ڵ��������ķ���
		spriteVector.pushBack(sprite);
	}

	unsigned randomnumber = rand() % 12;
	//�������
	auto playersprite= Sprite::create("ball.png");
	playersprite->setColor(Color3B(**(color+randomnumber),*(*(color+randomnumber)+1), *(*(color + randomnumber) + 2)));
	playersprite->setScale(0.04/ backgroundscale);
	playersprite->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2));
	playersprite->setTag(123);
	bg->addChild(playersprite, 2);  ////����������ڵ��������ķ���

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//ʹ��������
	auto listenerMouse = EventListenerMouse::create();
	//auto listenerKeyboard = EventListenerKeyboard::create();
	auto bg = this->getChildByTag(111);

	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = this->getChildByTag(111);

		//�õ��¼��Ա�����ģ������
		Vec2 eventpoint= bg->convertToNodeSpace(Vec2(e->getCursorX(),e->getCursorY()));

		//�õ��¼�����ҵ����λ��
		x = eventpoint.x - (bg->getChildByTag(123))->getPosition().x;
		y = eventpoint.y - (bg->getChildByTag(123))->getPosition().y;

		//����ģ��r
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

	//ע�������
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

void GameScene::update(float dt)	//ʹ��update�����ƶ�����
{
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = this->getChildByTag(111);
	auto sprite = bg->getChildByTag(123);

	//��ҵ��������
	Vec2 point = sprite->getPosition();

	//move_x,move_y��ʾ��ʵ��Ҫ�ƶ��ľ������
	float move_x = x;
	float move_y = y; 

	//�жϱ߽����
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
			sprite->setPosition(point + Vec2(move_x / r, move_y / r)/ backgroundscale);  //���ȥ�����ı���
			bg->setPosition(bg->getPosition() - Vec2(move_x / r, move_y / r));
	}
}

void GameScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	//
}