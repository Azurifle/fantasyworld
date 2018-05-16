#include "stdafx.h"
#include "Fantasy_world_2_d.hpp"
#include "Zombie.hpp"
#include "Orc.hpp"
#include "Doremon.hpp"
#include "Player.hpp"

namespace G6037599
{
	//___ (de)constructors _____________________________________________
	Fantasy_world_2_d::Fantasy_world_2_d(const int t_monsters)
	{
		REQUIRE(t_monsters > NONE);

		srand(unsigned int(time(nullptr)));

		for (int i = FIRST_INDEX; i < t_monsters; ++i)
		{
			add_random_monsters(i);
		}

		PROMISE(m_zombie_count_ + m_orc_count_ + m_doremon_count_ == t_monsters);

		puts("world created.");
	}

	Fantasy_world_2_d::Fantasy_world_2_d(const int t_rows, const int t_columns, const int t_monsters)
	{
		REQUIRE(t_rows > NONE && t_columns > NONE && t_monsters >= NONE);

		for (int i = FIRST_INDEX; i < t_rows; ++i)
		{
			m_grid_.push_back(std::make_unique<std::vector<std::weak_ptr<Unit> >>
				(t_columns, std::weak_ptr<Unit>()));
		}

		srand(unsigned int(time(nullptr)));

		for (int i = FIRST_INDEX; i < t_monsters; ++i)
		{
			add_random_monsters(i);
			spawn(i);
		}

		PROMISE(m_zombie_count_ + m_orc_count_ + m_doremon_count_ == t_monsters);

		std::cout << "World " << t_rows << "x" << t_columns << " grid created with "
			<< t_monsters << " monsters spawn randomly." << std::endl;
	}

	Fantasy_world_2_d::~Fantasy_world_2_d()
	{
		puts("world destroyed.");
	}

	//___ public _______________________________________________________
	void Fantasy_world_2_d::update()
	{
    if(m_player_)
    {
      m_player_->update();
    }

		for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
		{
			(*it)->update();
		}
	}

	void Fantasy_world_2_d::create_player(const char* t_name, const int t_hp)
	{
		m_player_ = std::make_shared<Player>(*this, FIRST_INDEX, t_name, t_hp);

		for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
		{
      (*it)->set_target(m_player_);
		}

    std::cout << t_name << " has logged in with " << t_hp << " health." << std::endl;
	}

  void Fantasy_world_2_d::create_player(const char* t_name, const int t_hp
    , const char* t_weapon, const int t_attack_power)
  {
    m_player_ = std::make_shared<Player>(*this, FIRST_INDEX, t_name, t_hp
      , t_weapon, t_attack_power);
    spawn_player();

    for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
    {
      (*it)->set_target(m_player_);
    }

    std::cout << t_name << " has logged in with " << t_hp << " health and "
      << t_weapon << " attack power: " << t_attack_power << " as weapon." << std::endl;
  }

  void Fantasy_world_2_d::spawn(const int t_id)
	{
		REQUIRE(FIRST_INDEX <= t_id && t_id < static_cast<int>( m_monsters_.size() ) );
    
		int x = rand() % m_grid_.size(), y = rand() % m_grid_[FIRST_INDEX]->size();
		while (true)
		{
			if (m_grid_[x]->at(y).expired())//the tile is free
			{
				m_grid_[x]->at(y) = m_monsters_[t_id];
        m_monsters_[t_id]->set_position(x, y);
        m_monsters_[t_id]->set_full_hp();
				break;
			}
			x = rand() % m_grid_.size();
			y = rand() % m_grid_[FIRST_INDEX]->size();
		}
	}

	void Fantasy_world_2_d::despawn(const int t_x, const int t_y)
	{
		REQUIRE(t_x < static_cast<int>(m_grid_.size()) && t_y < static_cast<int>(m_grid_[t_x]->size()));
		m_grid_[t_x]->at(t_y) = std::weak_ptr<Unit>();
		PROMISE(m_grid_[t_x]->at(t_y).expired());
	}

  void Fantasy_world_2_d::spawn_player()
  {
    REQUIRE(m_player_);

    int x = rand() % m_grid_.size(), y = rand() % m_grid_[FIRST_INDEX]->size();
    while (true)
    {
      if (m_grid_[x]->at(y).expired())//the tile is free
      {
        m_grid_[x]->at(y) = m_player_;
        m_player_->set_position(x, y);
        m_player_->set_full_hp();
        break;
      }
      x = rand() % m_grid_.size();
      y = rand() % m_grid_[FIRST_INDEX]->size();
    }
  }

  //___ public const _________________________________________________
	void Fantasy_world_2_d::print_grid() const
	{
		std::cout << "<id><type>:<HP>. z = Zombie (HP 2-3), o = Orc (HP 5-6), d = Doramon (HP 8-9)." << std::endl;
		puts("");
		for (auto row = m_grid_.begin(); row != m_grid_.end(); ++row)
		{
			for (auto column = (*row)->begin(); column != (*row)->end(); ++column)
			{
				std::cout << ' ';
			  switch ((*column).expired())
			  {
        case true: std::cout << ". "; break;
        default: (*column).lock()->print_character();
          std::cout << ' ';
			  }
			}
      puts("");
		}//row
	}

	void Fantasy_world_2_d::print_monster_list() const
	{
		std::cout << " --- List of all monsters in the fantasy world -----------" << std::endl
			<< "Total " << m_zombie_count_ + m_orc_count_ + m_doremon_count_ << " monsters" << std::endl
			<< m_zombie_count_ << " zombies." << std::endl
			<< m_orc_count_ << " orcs." << std::endl
			<< m_doremon_count_ << " doremons." << std::endl;
	}

	//___ private _______________________________________________________
	void Fantasy_world_2_d::add_random_monsters(const int t_id)
	{
    enum Type
    {
      TYPE_1 = 1, TYPE_2, TYPES
    };
		switch (rand() % TYPES)
		{
		case TYPE_1: m_monsters_.push_back(std::make_shared<Zombie>(*this, t_id) );
			++m_zombie_count_;
			break;
		case TYPE_2: m_monsters_.push_back(std::make_shared<Orc>(*this, t_id));
			++m_orc_count_;
			break;
		default: m_monsters_.push_back(std::make_shared<Doremon>(*this, t_id));
			++m_doremon_count_;
			break;
		}
	}

}//namespace G6037599