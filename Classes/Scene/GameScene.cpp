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

	//˫�㱳��
	auto bg0 = Sprite::create("background.png");
	bg0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg0->setScale(1.3);
	bg0->setColor(Color3B(245, 245, 245));
	this->addChild(bg0, 0);

	//����������ϲ㱳��
	auto bg = BackGround::create();
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setTag(bgTag);
	this->addChild(bg, 1);

	//�����������
	auto players = PlayerVector::create();
	players->setTag(playersTag);
	this->addChild(players, 1);
	//��ʼ���������
	players->init_on(bg);

	auto circles = Circles::create();
	circles->setTag(circlesTag);
	this->addChild(circles, 1);
	//����Ļ�����С��
	circles->addcirclesto(bg);

	//��ʼ��������
	auto gamecontroler = GameControler::create(bg);
	gamecontroler->setTag(controlerTag);
	this->addChild(gamecontroler, 1);
	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	log("GameScene onEnter");
	//��ʼ��Ĭ���¼�����Ϊ��Ļ�����Է�ֹδ�������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = (BackGround*)this->getChildByTag(bgTag);
	auto center = bg->convertToNodeSpace(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	event_x = center.x;
	event_y = center.y;
    
	//ʹ��������
	auto listenerMouse = EventListenerMouse::create();
	
	listenerMouse->onMouseMove = [&](Event *event) {
		EventMouse* e = (EventMouse*)event;
		auto bg = (BackGround*)this->getChildByTag(bgTag);
		//�õ��¼��Ա�����ģ������
		auto eventpoint = bg->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
		event_x = eventpoint.x;
		event_y = eventpoint.y;
	};
	
	//ʹ�������ֽ��з�����Ļ
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

	//ע�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this->getChildByTag(bgTag));
    eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this->getChildByTag(bgTag));

	//ˢ����Ļ
	this->scheduleUpdate();
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