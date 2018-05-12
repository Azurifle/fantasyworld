#ifndef FANTASY_WORLD_2_D
#define FANTASY_WORLD_2_D
#pragma once
#include "monster.h"

class monster;

class fantasy_world_2_d
{
public:
	fantasy_world_2_d() = default;
	void spawn(monster* a_monster);
	fantasy_world_2_d(int rows, int columns, int monsters);
	~fantasy_world_2_d();

	void print_grid() const;
	void update();
	void despawn(int x, int y);
private:
	vector<vector<monster*>*> grid_;
	vector<monster*> monsters_;
	int zombie_count_ = 0, orc_count_ = 0, doremon_count_ = 0;
};

#endif //FANTASY_WORLD_2_D