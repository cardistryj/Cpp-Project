#include"Circles.h"
#include"color.h"
USING_NS_CC;

bool Circles::init(Texture2D* texture)
{
	if (!Node::create())
	{
		return false;
	}

	spriteVector = Vector<Sprite *>(MAXCIRCLENUMBER);
	for (int i = 0; i < MAXCIRCLENUMBER; i++) {
		auto sprite = Sprite::createWithTexture(texture);
		spriteVector.pushBack(sprite);
	}

	return true;
}

Circles* Circles::create(Texture2D* texture)
{
	Circles* circles = new Circles();
	if (circles->init(texture))
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
		sprite->setScale(CIRCLESCALE / DEFAULTBGSCALE);
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));

		//设置呼吸效果的动画
		FiniteTimeAction* action1 = (FiniteTimeAction *)ScaleTo::create(0.8f, CIRCLESCALE / DEFAULTBGSCALE*1.2f);
		FiniteTimeAction* action2 = (FiniteTimeAction *)ScaleTo::create(0.8f, CIRCLESCALE / DEFAULTBGSCALE*0.8f);
		ActionInterval* action = Sequence::create(action1, action2, NULL);
		RepeatForever * repeatforever = RepeatForever::create(action);
		sprite->runAction(repeatforever);

		bg->addChild(sprite, 0);
	}
}