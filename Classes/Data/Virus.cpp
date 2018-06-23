#include "Virus.h"
USING_NS_CC;

bool Virus::init()
{
	if (!Sprite::initWithFile("ball.png"))
	{
		return false;
	}
	return true;
}

Virus* Virus::create()
{
	Virus* virus = new Virus();
	if (virus->init())
	{
		virus->autorelease();
	}
	else
	{
		delete virus;
		virus = NULL;
		return NULL;
	}
	return virus;
}

Virus* Virus::virus_clone()
{
	auto virus = Virus::create();
	virus->virusscale = virusscale;
	virus->setColor(getColor());
	virus->setPosition(getPosition());
	virus->setScale(VIRUSSCALE/DEFAULTBGSCALE);
	return virus;
}