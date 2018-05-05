#include "stdafx.h"
#include "monster.h"

monster::monster(player player_to_attack)
{
	player_to_attack_ = player_to_attack;
	name_ = "Monster";
	damage_ = 0;
}

void monster::update() const
{
	cout << name_.c_str() << " attack " << player_to_attack_.get_name() << " " << damage_ << " points." << endl;
	player_to_attack_.attacked(damage_);
}
