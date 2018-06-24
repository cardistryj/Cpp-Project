#pragma once
#include"cocos2d.h"
#include"BackGround.h"
#include"Virus.h"

class VirusVector :public cocos2d::Node
{
	cocos2d::Vector<Virus*> virusvector;
	cocos2d::Vector<Virus*> to_erase;
	void erase_virus();  //É¾³ý±»ÍÌÊÉµôµÄ²¡¶¾
public:
	friend class GameControler;

	inline bool init(cocos2d::Texture2D*);
	static VirusVector* create(cocos2d::Texture2D*);
	void addvirusto(BackGround*);
};

