#include "stdafx.h"
#include "fantasy_world_2_d.h"

void fantasy_world_2_d::spawn(monster* a_monster)
{
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
		monsters_.push_back(new monster(i, this));
		spawn(monsters_[0]);
	}
}

void fantasy_world_2_d::print_grid() const
{
	for (auto row : grid_)
	{
		cout << " ";
		for(auto column : *row)
		{
			if (column)
				column->print();
			else
				cout << "--:-";
		}
		cout << endl;
	}
}

void fantasy_world_2_d::update()
{
	for (auto monster_ptr : monsters_)
	{
		monster_ptr->update();
	}
}

void fantasy_world_2_d::despawn(const int row, const int column)
{
	grid_[row]->at(column) = nullptr;
}
