#ifndef ZOMBIE
#define ZOMBIE
#pragma once
#include "monster.h"

class zombie : public monster
{
public:
	zombie(int id, fantasy_world_2_d* world);

	int get_max_hp() const override;
	char get_type() const override;

	//use monster deconstructor
	//void update() override;
};

#endif //ZOMBIE