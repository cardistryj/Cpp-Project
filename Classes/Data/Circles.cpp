#include"Circles.h"
#include"color.h"
USING_NS_CC;

bool Circles::init()
{
	//创建纹理缓存对象
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("ball.png");

	//初始化Vector
	spriteVector = Vector<cocos2d::Sprite *>(MAXCIRCLENUMBER);
	for (int i = 0; i < MAXCIRCLENUMBER; i++) {
		//使用纹理生成小球
		auto sprite = CCSprite::createWithTexture(texture);
		spriteVector.pushBack(sprite);
	}

	return true;
}

void Circles::addcirclesto(cocos2d::Sprite* bg,float backgroundscale)
{
	Color color;
	srand((unsigned)time(NULL));

	for (auto sprite : spriteVector)
	{
		unsigned randomnumber = rand() % 12;
		unsigned char *c = color.getColor(randomnumber);
		sprite->setColor(Color3B(*c, *(c + 1), *(c + 2)));
		sprite->setScale(CIRCLESCALE / backgroundscale);
		sprite->setPosition(Vec2(CCRANDOM_0_1()*bg->getContentSize().width
			, CCRANDOM_0_1()*bg->getContentSize().height));
		bg->addChild(sprite, 1);  //添加至背景节点便于整体的放缩
	}
}