#include "stdafx.h"
#include "monster.h"

monster::monster(const int id, fantasy_world_2_d* world)
{
	REQUIRE(world);

	id_ = id;
	world_ = world;
}

void monster::print() const
{
	if(id_ < 10)
		cout << "0";

	cout << id_ << ":" << hp_;
}

void monster::update()
{
	--hp_;
	if (hp_ <= 0)
	{
		world_->spawn(this);
	}
}

void monster::respawn(const int x, const int y)
{
	if(x_ != -1 && y_ != -1)
		world_->despawn(x_, y_);
	x_ = x;
	y_ = y;
	hp_ = MAX_HP;
}
