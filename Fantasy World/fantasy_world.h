#ifndef FANTASY_WORLD
#define FANTASY_WORLD
#pragma once
#include "monster.h"
#include "player.h"

class fantasy_world
{
public:
	fantasy_world() = default;
	explicit fantasy_world(int monster_number);
	virtual ~fantasy_world() = default;
	void create_player(const char* name, int hp);
	void update();

private:
	vector<monster>* monsters_ = nullptr;
	player* a_player_ = nullptr;
};

#endif //FANTASY_WORLD