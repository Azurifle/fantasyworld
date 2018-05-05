#include "stdafx.h"
#include "fantasy_world.h"
#include "zombie.h"
#include "orc.h"

fantasy_world::fantasy_world(const int monster_number)
{
	for(auto i = 0; i < monster_number; ++i)
	{
		switch (rand()%2)
		{
		case 0: monsters_.push_back(zombie());
			break;
		default: monsters_.push_back(orc());
			break;
		}
	}
}

void fantasy_world::create_player(const char* name, int hp)
{
	a_player_ = new a_player_(name, hp);
}

void fantasy_world::update()
{
	for (monster a_monster : monsters_)
	{
		
	}
}
