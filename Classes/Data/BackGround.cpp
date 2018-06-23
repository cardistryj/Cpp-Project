#include"BackGround.h"

bool BackGround::init()
{
	if (!Sprite::initWithFile("background.png"))
	{
		return false;
	}
	backgroundscale = DEFAULTBGSCALE;
	setScale(backgroundscale);
	return true;
}
BackGround* BackGround::create()
{
	BackGround* bg = new BackGround();
	if (bg->init())
	{
		bg->autorelease();
	}
	else
	{
		delete bg;
		bg = NULL;
		return NULL;
	}
	return bg;
}