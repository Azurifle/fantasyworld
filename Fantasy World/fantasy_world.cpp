#include "stdafx.h"
#include "fantasy_world.h"
#include "zombie.h"
#include "orc.h"
#include "doremon.h"

fantasy_world::fantasy_world(const int monster_number)
{
	srand(unsigned int(time(nullptr)));

	for(auto i = 0; i < monster_number; ++i)
	{
		switch (rand()%3)
		{
		case 0: monsters_.push_back(new zombie());
			++zombie_count_;
			break;
		case 1: monsters_.push_back(new orc());
			++orc_count_;
			break;
		default: monsters_.push_back(new doremon());
			++doremon_count_;
			break;
		}
	}
}

fantasy_world::~fantasy_world()
{
	player_ = nullptr;
}

void fantasy_world::create_player(const char* name, const int hp)
{
	player_ = new player(name, hp);

	for (auto it = monsters_.begin(); it != monsters_.end(); ++it)
	{
		(*it)->set_target(player_);
	}
}

void fantasy_world::print_monster_list() const
{
	cout << " --- List of all monsters in the fantasy world -----------" << endl
		<< "Total " << zombie_count_+orc_count_+doremon_count_ << " monsters" << endl
		<< zombie_count_ << " zombies." << endl
		<< orc_count_ << " orcs." << endl
		<< doremon_count_ << " doremons." << endl 
		<< endl;
}

void fantasy_world::update()
{
	for (auto it = monsters_.begin(); it != monsters_.end(); ++it) 
	{
		(*it)->on_update();
		cout << endl;
	}
}
