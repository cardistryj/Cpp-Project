#pragma once
#include"cocos2d.h"
#include"BackGround.h"
#include"Virus.h"

class VirusVector :public cocos2d::Node
{
	cocos2d::Vector<Virus*> virusvector;
	cocos2d::Vector<Virus*> to_erase;
public:
	friend class GameControler;

	inline bool init();
	static VirusVector* create();
	void addvirusto(BackGround*);
};

