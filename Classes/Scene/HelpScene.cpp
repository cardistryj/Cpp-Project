#include "HelpScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelpScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create and add background
	auto bg = Sprite::create("startbackground.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg, 0);

	//ÎÄ×Ö
	auto titlelabel = Label::createWithTTF("Help", "fonts/Marker Felt.ttf", 36);
	titlelabel->setColor(Color3B::RED);
	float x = origin.x +45;
	float y = origin.y + visibleSize.height-30 ;
	titlelabel->setPosition(Vec2(x, y));
	this->addChild(titlelabel, 1);

	auto linelabel = Label::createWithTTF("----------", "fonts/Marker Felt.ttf", 36);
	linelabel->setColor(Color3B::BLACK);
	float x1 = origin.x +80;
	float y1 = origin.y + visibleSize.height - 65;
	linelabel->setPosition(Vec2(x1, y1));
	this->addChild(linelabel, 1);

	auto label1 = Label::createWithTTF("press", "fonts/Marker Felt.ttf", 17);
	label1->setColor(Color3B::BLACK);
	float x2 = origin.x + 90;
	float y2 = origin.y + visibleSize.height - 110;
	label1->setPosition(Vec2(x2, y2));
	this->addChild(label1, 1);

	auto label2 = Label::createWithTTF("space", "fonts/Marker Felt.ttf", 23);
	label2->setColor(Color3B::RED);
	float x3 = origin.x + 133;
	float y3 = origin.y + visibleSize.height - 110;
	label2->setPosition(Vec2(x3, y3));
	this->addChild(label2, 1);

	auto label3 = Label::createWithTTF("to split only on condition that your", "fonts/Marker Felt.ttf", 17);
	label3->setColor(Color3B::BLACK);
	float x4 = origin.x + 273;
	float y4 = origin.y + visibleSize.height - 110;
	label3->setPosition(Vec2(x4, y4));
	this->addChild(label3, 1);

	auto label4 = Label::createWithTTF("ball is larger than the ball of a specific size", "fonts/Marker Felt.ttf", 17);
	label4->setColor(Color3B::BLACK);
	float x5 = origin.x + 180;
	float y5 = origin.y + visibleSize.height - 140;
	label4->setPosition(Vec2(x5, y5));
	this->addChild(label4, 1);

	auto label5 = Label::createWithTTF("press", "fonts/Marker Felt.ttf", 17);
	label5->setColor(Color3B::BLACK);
	float x6 = origin.x + 90;
	float y6 = origin.y + visibleSize.height - 168;
	label5->setPosition(Vec2(x6, y6));
	this->addChild(label5, 1);

	auto label6 = Label::createWithTTF("w", "fonts/Marker Felt.ttf", 23);
	label6->setColor(Color3B::RED);
	float x7 = origin.x + 120;
	float y7 = origin.y + visibleSize.height - 168;
	label6->setPosition(Vec2(x7, y7));
	this->addChild(label6, 1);

	auto label7 = Label::createWithTTF("to throw little balls with the same limit", "fonts/Marker Felt.ttf", 17);
	label7->setColor(Color3B::BLACK);
	float x8 = origin.x + 258;
	float y8 = origin.y + visibleSize.height - 168;
	label7->setPosition(Vec2(x8, y8));
	this->addChild(label7, 1);
	
	auto label8 = Label::createWithTTF("move your mouse and your ball will follow", "fonts/Marker Felt.ttf", 17);
	label8->setColor(Color3B::BLACK);
	float x9 = origin.x + 208;
	float y9 = origin.y + visibleSize.height - 199;
	label8->setPosition(Vec2(x9, y9));
	this->addChild(label8, 1);

	auto label9 = Label::createWithTTF("back", "fonts/Marker Felt.ttf", 23);
	label9->setColor(Color3B::RED);
	auto backItem = MenuItemLabel::create(label9, CC_CALLBACK_1(HelpScene::menubackCallback, this));
	float x10 = origin.x + visibleSize.width-40;
	float y10 = origin.y + 20;
	backItem->setPosition(Vec2(x10, y10));
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	return true;
}

void HelpScene::menubackCallback(cocos2d::Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/botton.wav");
	}
	Director::getInstance()->popSceneWithTransition<TransitionFadeTR>(1.0);
}

void HelpScene::onEnter()
{
	Layer::onEnter();
	log("Setting onEnter");
}

void HelpScene::onEnterTransitionDidFinish()
{
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		//²¥·Å
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Synth.mp3", true);
	}
	Layer::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");
}

void HelpScene::onExit()
{
	Layer::onExit();
	log("Setting onExit");
}

void HelpScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}

void HelpScene::cleanup()
{
    //Í£Ö¹
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Synth.mp3");
	Layer::cleanup();
	log("Setting cleanup");
}
