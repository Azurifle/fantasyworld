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
	virtual ~fantasy_world_2_d() = default;

	void print_grid() const;
	void update();
	void despawn(int row, int column);
private:
	vector<vector<monster*>*> grid_;
	vector<monster*> monsters_;
};

#endif //FANTASY_WORLD_2_D