#include "Virus.h"
USING_NS_CC;

bool Virus::init(Texture2D* texture)
{
	if (!Sprite::initWithTexture(texture))
	{
		return false;
	}
	return true;
}

Virus* Virus::create(Texture2D* texture)
{
	Virus* virus = new Virus();
	if (virus->init(texture))
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

Virus* Virus::virus_clone(Texture2D* texture)
{
	auto virus = Virus::create(texture);
	virus->virusscale = virusscale;
	virus->setColor(getColor());
	virus->setPosition(getPosition());
	virus->setScale(VIRUSSCALE/DEFAULTBGSCALE);
	return virus;
}