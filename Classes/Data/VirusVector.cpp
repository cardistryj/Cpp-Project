#include "VirusVector.h"
USING_NS_CC;

bool VirusVector::init()
{
	if (!Node::create())
	{
		return false;
	}
	return true;
}

VirusVector* VirusVector::create()
{
	VirusVector* virus = new VirusVector();
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

void VirusVector::addvirusto(BackGround* bg)
{
	for (int i = 0; i < MAXVIRUSNUMBER; i++)
	{
		auto virus = Virus::create();
		virus->setColor(Color3B::BLACK);
		virus->virusscale = VIRUSSCALE;
		virus->setScale(VIRUSSCALE / DEFAULTBGSCALE);
		virus->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));

		bg->addChild(virus, 2);
		virusvector.pushBack(virus);
	}
}