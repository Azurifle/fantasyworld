#include "stdafx.h"
#include "zombie.h"

zombie::zombie(const int id, fantasy_world_2_d* world) : monster(id, world) {}

int zombie::get_max_hp() const
{
	return 2;
}

char zombie::get_type() const
{
	return 'z';
}

/*
zombie::zombie()
{
	name_ = "Zombie";
	damage_ = rand() % 30 + 5;
}

void zombie::on_update() const
{
	cout << name_ << " attacks " << target_->get_name() << " with Bitting Attack !" << endl;
	target_->damaged(damage_);
}
*/
