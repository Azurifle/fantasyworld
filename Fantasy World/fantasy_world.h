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
	virtual ~fantasy_world();

	void print_monster_list() const;
	void create_player(const char* name, int hp);
	void update();

private:
	vector<monster*> monsters_;
	int zombie_count_ = 0, orc_count_ = 0, doremon_count_ = 0;
	player* player_ = nullptr;//need to be shared with monsters
};

#endif //FANTASY_WORLD