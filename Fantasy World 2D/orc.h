#ifndef ORC
#define ORC
#pragma once
#include "monster.h"

class orc : public monster
{
public:
	orc(int id, fantasy_world_2_d* world);

	int get_max_hp() const override;
	char get_type() const override;

	//use monster deconstructor
	//void on_update() const override;
};

#endif //ORC
