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
		auto body = PhysicsBody::createCircle(virus->getContentSize().width / 2);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x02);
		virus->setPhysicsBody(body);

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

void VirusVector::divide(Virus* virus)
{
	auto bg = (BackGround*)getParent();
	auto spriteTexture = (SpriteBatchNode*)bg->getChildByTag(textureTag);
	auto texture = spriteTexture->getTexture();

	virus->get_scale() = VIRUSSCALE;
	virus->runAction(ScaleTo::create(0.8f, VIRUSSCALE / DEFAULTBGSCALE));
	auto _virus = virus->virus_clone(texture);
	bg->addChild(_virus, 2);
	_virus->runAction(MoveBy::create(0.8f, 30 * Vec2(CCRANDOM_0_1() - 1, CCRANDOM_0_1() - 1)));
	virusvector.pushBack(_virus);
}