#include "stdafx.h"
#include "fantasy_world_2_d.h"
#include "zombie.h"
#include "orc.h"
#include "doremon.h"

void fantasy_world_2_d::spawn(monster* a_monster)
{
	REQUIRE(a_monster);

	int x = rand()%grid_.size(), y = rand()%grid_[0]->size();
	while(true)
	{
		if (grid_[x]->at(y))//if not free
		{
			x = rand() % grid_.size();
			y = rand() % grid_[0]->size();
			continue;
		}
		grid_[x]->at(y) = a_monster;
		a_monster->respawn(x ,y);
		return;
	}
}

fantasy_world_2_d::fantasy_world_2_d(const int rows, const int columns, const int monsters)
{
	REQUIRE(rows > 0 && columns > 0 && monsters >= 0);

	for(auto i = 0; i < rows; ++i)
	{
		grid_.push_back(new vector<monster*>);
		for(auto j = 0; j < columns; ++j)
		{
			grid_[i]->push_back(nullptr);
		}
	}

	srand(unsigned int(time(nullptr)));

	for(auto i = 0; i < monsters; ++i)
	{
		switch (rand() % 3)
		{
		case 0: monsters_.push_back(new zombie(i, this));
			++zombie_count_;
			break;
		case 1: monsters_.push_back(new orc(i, this));
			++orc_count_;
			break;
		default: monsters_.push_back(new doremon(i, this));
			++doremon_count_;
			break;
		}
		spawn(monsters_[i]);
	}
}

fantasy_world_2_d::~fantasy_world_2_d()
{
	for (auto monster : monsters_)
	{
		delete monster;
	}

	for (auto row : grid_)
	{
		delete row;
	}
}

void fantasy_world_2_d::print_grid() const
{
	for (auto row : grid_)
	{
		for(auto column : *row)
		{
			cout << '|';
			if (column)
				column->print();
			else
				cout << "____";
		}
		cout << '|' << endl;
	}
}

void fantasy_world_2_d::update()
{
	for (auto monster_ptr : monsters_)
	{
		monster_ptr->update();
	}
}

void fantasy_world_2_d::despawn(const int x, const int y)
{
	REQUIRE(int(grid_.size()) > x && int(grid_[x]->size()) > y);
	grid_[x]->at(y) = nullptr;
}
