#include "stdafx.h"
#include "monster.h"

monster::monster()
{
	name_ = "Monster";
	damage_ = 0;
}

monster::~monster()
{
	target_ = nullptr;
	name_ = nullptr;
}

void monster::set_target(player* target)
{
	target_ = target;
}

void monster::on_update() const
{
	cout << name_ << " attacks " << target_->get_name() << " with Normal Attack." << endl;
	target_->attacked(damage_);
}