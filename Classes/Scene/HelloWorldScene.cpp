#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"SettingScene.h"
#include"GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create and add background
	auto bg = Sprite::create("startbackground.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg,0);

    /////////////////////////////
	auto startlabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 36);
	startlabel->setColor(Color3B::RED);
	auto startItem = MenuItemLabel::create(startlabel, CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
    if (startItem == nullptr)
    {
        problemLoading("startItem");
    }
    else
    {
        float x = origin.x + visibleSize.width/2;
		float y = origin.y + visibleSize.height - 130;
		startItem->setPosition(Vec2(x,y));
    }

	auto settinglabel = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 36);
	settinglabel->setColor(Color3B::RED);
	auto settingItem = MenuItemLabel::create(settinglabel, CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
	if (settingItem == nullptr)
	{
		problemLoading("settingItem");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height - 180;
		settingItem->setPosition(Vec2(x, y));
	}

	auto helplabel = Label::createWithTTF("Help", "fonts/Marker Felt.ttf", 36);
	helplabel->setColor(Color3B::RED);
	auto helpItem = MenuItemLabel::create(helplabel, CC_CALLBACK_1(HelloWorld::menuHelpCallback, this));
	if (helpItem == nullptr)
	{
		problemLoading("helpItem");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height - 230;
		helpItem->setPosition(Vec2(x, y));
	}

	auto exitlabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 36);
	exitlabel->setColor(Color3B::RED);
	auto exitItem = MenuItemLabel::create(exitlabel, CC_CALLBACK_1(HelloWorld::menuExitCallback, this));
	if (exitItem == nullptr)
	{
		problemLoading("exitItem");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height - 280;
		exitItem->setPosition(Vec2(x, y));
	}
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem,settingItem, helpItem,exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////

	auto title = Label::createWithTTF("Agar.io", "fonts/Marker Felt.ttf", 48);
    if (title == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
		title->enableShadow();
		title->setColor(Color3B::RED);
        // position the label on the center of the screen
		title->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - title->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(title, 1);
    }

    return true;
}

void HelloWorld::menuStartCallback(Ref* pSender)
{
	auto sc = GameScene::createScene();
	auto reScene = TransitionCrossFade::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::menuSettingCallback(Ref* pSender)
{
	auto sc = SettingScene::createScene();
	auto reScene = TransitionCrossFade::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::menuHelpCallback(Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Help Menu Item %p", item);
}

void HelloWorld::menuExitCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}


