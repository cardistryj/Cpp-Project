#include"Circles.h"
#include"color.h"
USING_NS_CC;

bool Circles::init()
{
	if (!Node::create())
	{
		return false;
	}
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("ball.png");

	spriteVector = Vector<Sprite *>(MAXCIRCLENUMBER);
	for (int i = 0; i < MAXCIRCLENUMBER; i++) {
		auto sprite = CCSprite::createWithTexture(texture);
		spriteVector.pushBack(sprite);
	}

	return true;
}

Circles* Circles::create()
{
	Circles* circles = new Circles();
	if (circles->init())
		circles->autorelease();
	else
	{
		delete circles;
		circles = NULL;
		return NULL;
	}
	return circles;
}

void Circles::addcirclesto(BackGround* bg)
{
	Color color;

	srand((unsigned)time(NULL));
	for (auto sprite : spriteVector)
	{
		unsigned randomnumber = rand() % 12;
		unsigned char *c = color.getColor(randomnumber);
		sprite->setColor(Color3B(*c, *(c + 1), *(c + 2)));
		sprite->setScale(CIRCLESCALE / bg->get_scale());
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));
		
		bg->addChild(sprite, 1);
	}
}