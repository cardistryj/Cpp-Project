#include "VirusVector.h"
USING_NS_CC;

bool VirusVector::init(Texture2D* texture)
{
	if (!Node::create())
	{
		return false;
	}

	virusvector = Vector<Virus *>(MAXVIRUSNUMBER);
	for (int i = 0; i < MAXVIRUSNUMBER; i++) {
		auto sprite = Virus::create(texture);
		virusvector.pushBack(sprite);
	}

	return true;
}

VirusVector* VirusVector::create(Texture2D* texture)
{
	VirusVector* virus = new VirusVector();
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

void VirusVector::addvirusto(BackGround* bg)
{
	for (auto virus:virusvector)
	{
		virus->setColor(Color3B::BLACK);
		virus->get_scale() = VIRUSSCALE;
		virus->setScale(VIRUSSCALE / DEFAULTBGSCALE);
		virus->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));

		bg->addChild(virus, 2);
	}
}

void VirusVector::erase_virus()
{
	auto bg = getParent();
	for (auto virus : to_erase)
	{
		bg->removeChild(virus);
		virusvector.eraseObject(virus);
	}
}