#include "SettingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
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
	//音效
	auto soundOnMenuItem = MenuItemImage::create("CloseNormal.png", "CloseNormal.png");
	auto soundOffMenuItem = MenuItemImage::create("CloseSelected.png", "CloseSelected.png");

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingScene::menuSoundToggleCallback, this), soundOnMenuItem, soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	//音乐
	auto musicOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	auto musicOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");

	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingScene::menuMusicToggleCallback, this), musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleMenuItem->setPosition(Vec2(origin.x + 600, origin.y + 550));

	//操作：选择键盘还是鼠标
	

	//ok button
	auto okMenuItem = MenuItemImage::create("menu/ok-down.png", "menu/ok-up.png",
		CC_CALLBACK_1(SettingScene::menuOkCallback,this));
	okMenuItem->setPosition(Vec2(origin.x + visibleSize.width, origin.y + 200));

	auto mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);

	this->addChild(mn, 1);

	return true;
}

void SettingScene::menuSoundToggleCallback(cocos2d::Ref* pSender)
{
	//
}

void SettingScene::menuMusicToggleCallback(cocos2d::Ref* pSender)
{
	//
}

void SettingScene::menuOkCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}