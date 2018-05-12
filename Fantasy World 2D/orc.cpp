#include "stdafx.h"
#include "orc.h"

orc::orc(const int id, fantasy_world_2_d* world) : monster(id, world)
{

}

int orc::get_max_hp() const
{
	return 5;
}

char orc::get_type() const
{
	return 'o';
}

/*
orc::orc()
{
	name_ = "Orc";
	damage_ = rand() % 5 + 25;
}

void orc::on_update() const
{
	cout << name_ << " attacks " << target_->get_name() << " with Orc Slash !" << endl;
	target_->damaged(damage_);
}
*/
