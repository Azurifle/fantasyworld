#include "stdafx.h"
#include "doremon.h"

doremon::doremon(const int id, fantasy_world_2_d* world) : monster(id, world)
{

}

int doremon::get_max_hp() const
{
	return 8;
}

char doremon::get_type() const
{
	return 'd';
}

/*
doremon::doremon()
{
	name_ = "Doremon";
	damage_ = rand() % 5+50;
}

void doremon::on_update() const
{
	cout << name_ << " attacks " << target_->get_name() << " with Magical Device Attack." << endl;
	target_->damaged(damage_);
}
*/
