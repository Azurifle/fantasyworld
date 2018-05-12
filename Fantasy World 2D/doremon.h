#ifndef DOREMON
#define DOREMON
#pragma once
#include "monster.h"

class doremon : public monster
{
public:
	doremon(int id, fantasy_world_2_d* world);

	int get_max_hp() const override;
	char get_type() const override;

	//use monster deconstructor
	//void on_update() const override;
};

#endif //DOREMON