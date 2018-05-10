#include "stdafx.h"
#include "monster.h"

monster::monster(const int id, fantasy_world_2_d* world)
{
	id_ = id;
	world_ = world;
}

void monster::print() const
{
	if(id_ < 10)
		cout << "0" << id_ << ":" << hp_;
	else
		cout << id_ << ":" << hp_;
}

void monster::update()
{
	--hp_;
	if (hp_ <= 0)
	{
		world_->spawn(this);
		world_->despawn(x_, y_);
	}
}

void monster::respawn(const int x, const int y)
{
	x_ = x;
	y_ = y;
	hp_ = 3;
}
