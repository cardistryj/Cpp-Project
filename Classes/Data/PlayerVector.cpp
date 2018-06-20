#include"PlayerVector.h"
USING_NS_CC;

bool PlayerVector::init()
{
	if (!Node::create())
	{
		return false;
	}
	return true;
}

PlayerVector* PlayerVector::create(bool ifAIplayer)
{
	PlayerVector* players = new PlayerVector();
	if (players->init())
	{
		players->ifAIplayer = ifAIplayer;
		players->autorelease();
	}
	else
	{
		delete players;
		players = NULL;
		return NULL;
	}
	return players;
}

void PlayerVector::set_scale()
{
	sum_scale = 0;
	for (auto player : playervector)
	{
		if (!player->eated && !player->combined)
			sum_scale += player->spritescale*player->spritescale;
	}
}