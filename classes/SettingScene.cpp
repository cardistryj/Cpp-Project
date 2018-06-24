#include "SettingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
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

	/////////////////////////////
	//ÒôÐ§
	auto soundOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto soundOffMenuItem = MenuItemImage::create("off.png", "off.png");

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingScene::menuSoundToggleCallback, this), soundOnMenuItem, soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(Vec2(origin.x+visibleSize.width/1.5,origin.y+visibleSize.height/1.5));

	auto soundeffectlabel = Label::createWithTTF("Soundeffect", "fonts/Marker Felt.ttf", 36);
	soundeffectlabel->setColor(Color3B::RED);
	auto soundeffectItem = MenuItemLabel::create(soundeffectlabel, CC_CALLBACK_1(SettingScene::menuSoundeffectCallback, this));
	float x = origin.x + visibleSize.width / 2-50;
	float y = origin.y + visibleSize.height - 105;
	soundeffectItem->setPosition(Vec2(x, y));


	//ÒôÀÖ
	auto musicOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto musicOffMenuItem = MenuItemImage::create("off.png", "off.png");

	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingScene::menuMusicToggleCallback, this), musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleMenuItem->setPosition(Vec2(origin.x+visibleSize.width/1.5,origin.y+visibleSize.height/3));

	auto BGMlabel = Label::createWithTTF("BGM", "fonts/Marker Felt.ttf", 36);
	BGMlabel->setColor(Color3B::RED);
	auto BGMItem = MenuItemLabel::create(BGMlabel, CC_CALLBACK_1(SettingScene::menuBGMCallback, this));
	float x1 = origin.x + visibleSize.width / 2-90;
	float y1 = origin.y + visibleSize.height - 210;
	BGMItem->setPosition(Vec2(x1, y1));
	
	auto menu = Menu::create(soundeffectItem, BGMItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//ok button
	auto okMenuItem = MenuItemImage::create("ok-down.png", "ok-up.png",
		CC_CALLBACK_1(SettingScene::menuOkCallback,this));
	okMenuItem->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/7));

	auto mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);

	this->addChild(mn, 1);

	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		musicToggleMenuItem->setSelectedIndex(0);//off
	}
	else {
		musicToggleMenuItem->setSelectedIndex(1);//on
	}

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		soundToggleMenuItem->setSelectedIndex(0);//off
	}
	else {
		soundToggleMenuItem->setSelectedIndex(1);//on
	}

	return true;
}

void SettingScene::menuSoundeffectCallback(cocos2d::Ref* pSender)
{
	
}

void SettingScene::menuBGMCallback(cocos2d::Ref* pSender)
{
	
}

void SettingScene::menuSoundToggleCallback(cocos2d::Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/botton.wav");
		UserDefault::getInstance()->setBoolForKey(SOUND_KEY, false);
	}
	else {
		UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
	}
}

void SettingScene::menuMusicToggleCallback(cocos2d::Ref* pSender)
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());

	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Synth.mp3");
	}
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/botton.wav");
	}
}

void SettingScene::menuOkCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();

	SimpleAudioEngine::getInstance()->playEffect("sound/botton.wav");
}

void SettingScene::onEnter()
{
	Layer::onEnter();
	log("Setting onEnter");
}

void SettingScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");

	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		//²¥·Å
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Synth.mp3", true);
	}

}

void SettingScene::onExit()
{
	Layer::onExit();
	log("Setting onExit");
}

void SettingScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}

void SettingScene::cleanup()
{
	Layer::cleanup();
	log("Setting cleanup");
	//Í£Ö¹
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Synth.mp3");
}