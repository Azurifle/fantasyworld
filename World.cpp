#include "stdafx.h"
#include "World.hpp"
#include "Zombie.hpp"
#include "Orc.hpp"
#include "Doremon.hpp"
#include "Player.hpp"
#include "Menu_ui.hpp"

namespace G6037599
{
	//___ (de)constructors _____________________________________________
	World::World(const int t_monsters)
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

	World::World(const int t_rows, const int t_columns, const int t_monsters)
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
			respawn_monster(i);
		}

		PROMISE(m_zombie_count_ + m_orc_count_ + m_doremon_count_ == t_monsters);

		std::cout << "World " << t_rows << "x" << t_columns << " grid created with "
			<< t_monsters << " monsters spawn randomly." << std::endl;
	}

	World::~World()
	{
		puts("world destroyed.");
	}

	//___ public _______________________________________________________
  void World::print_monster_list() const
  {
    std::cout << " --- List of all monsters in the fantasy world -----------" << std::endl
      << "Total " << m_zombie_count_ + m_orc_count_ + m_doremon_count_ << " monsters" << std::endl
      << m_zombie_count_ << " zombies." << std::endl
      << m_orc_count_ << " orcs." << std::endl
      << m_doremon_count_ << " doremons." << std::endl;
  }

  void World::build_grid()
  {
    std::cout << "Z = Zombie (HP 2-3), O = Orc (HP 5-6), D = Doramon (HP 8-9)." << std::endl;
    puts("");

    /*m_grid_start_cursor_ = Menu_ui::get_cursor();
    m_grid_start_cursor_.X += 1;*/
    for (int row = FIRST_INDEX; row < static_cast<int>(m_grid_.size()); ++row)
    {
      for (int column = FIRST_INDEX; column < static_cast<int>(m_grid_[FIRST_INDEX]->size()); ++column)
      {
        std::cout << ' ';
        switch (has_unit_on(column, row))
        {
        case false: std::cout << ". "; break;
        default: const auto unit = m_grid_[row]->at(column).lock();
          unit->print_character();
          switch (is_fighting_w_player(unit))
          {
          case true: m_player_->print_character(); break;
          default: std::cout << ' ';
          }
        }//has_unit_on tile
      }
      puts("");
    }//row
  }

	void World::update()
	{
    if(m_player_)
    {
      switch (m_is_restart_)
      {
      case false: break;
      default: m_is_restart_ = false;
        reset();
      }
      m_player_->update();
    }

		for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
		{
			(*it)->update();
		}
	}

	void World::create_player(const char* t_name, const int t_hp)
	{
		m_player_ = std::make_shared<Player>(*this, PLAYER_ID, t_name, t_hp);

		for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
		{
      (*it)->set_target(m_player_);
		}

    std::cout << m_player_->get_name() << " has logged in with " << t_hp << " health." << std::endl;
	}

  void World::create_player(const char* t_name, const int t_hp
    , const char* t_weapon, const int t_attack_power)
  {
    m_player_ = std::make_shared<Player>(*this, PLAYER_ID, t_name, t_hp
      , t_weapon, t_attack_power);
    spawn_player();

    for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
    {
      (*it)->set_target(m_player_);
    }

    std::cout << m_player_->get_name() << " has logged in with " << t_hp << " health and "
      << t_weapon << " attack power: " << t_attack_power << " as weapon." << std::endl;
  }

  void World::respawn_monster(const int t_id)
	{
		REQUIRE(FIRST_INDEX <= t_id && t_id < static_cast<int>( m_monsters_.size() ) );

    const auto WAS_SPAWNED_BEFORE = m_monsters_[t_id]->get_x() > NOT_ASSIGN;
    switch(WAS_SPAWNED_BEFORE)
    {
    case true: switch (is_fighting_w_player(m_monsters_[t_id]))
      {
      case false: clear(m_monsters_[t_id]->get_x(), m_monsters_[t_id]->get_y()); break;
      default: m_grid_[m_monsters_[t_id]->get_y()]->at(m_monsters_[t_id]->get_x()) = m_player_;
      } default:;
    }

		int x, y;
		do
		{
      y = rand() % m_grid_.size();
      x = rand() % m_grid_[FIRST_INDEX]->size();
    } while (has_unit_on(x, y));

    m_grid_[y]->at(x) = m_monsters_[t_id];
    m_monsters_[t_id]->set_position(x, y);
    m_monsters_[t_id]->set_full_hp();
	}

  void World::player_move(int t_x, int t_y)
  {
    t_x = Menu_ui::limit_interval(t_x + m_player_->get_x(), FIRST_INDEX, m_grid_[FIRST_INDEX]->size() - 1);
    t_y = Menu_ui::limit_interval(t_y + m_player_->get_y(), FIRST_INDEX, m_grid_.size() - 1);

    switch (is_player_fighting())
    {
    case false: clear(m_player_->get_x(), m_player_->get_y()); default:;
    }
    m_player_->set_position(t_x, t_y);

    switch (has_unit_on(t_x, t_y))
    {
    case false: m_grid_[t_y]->at(t_x) = m_player_;
      /*const auto SPACE_BETWEEN_GRID = 3;
      Menu_ui::set_cursor(m_grid_start_cursor_.Y+m_player_->get_y()
      , m_grid_start_cursor_.X + m_player_->get_x()*SPACE_BETWEEN_GRID);
      m_player_->print_character();*/
      break;
    default: m_player_->set_target(m_grid_[t_y]->at(t_x));
    }
  }

  void World::set_restart()
  {
    m_is_restart_ = true;
  }

  //___ private _______________________________________________________
  bool World::has_unit_on(const int t_x, const int t_y)
  {
    return !m_grid_[t_y]->at(t_x).expired();
  }

  bool World::is_fighting_w_player(const std::shared_ptr<Unit> unit) const
  {
    return unit->ID != m_player_->ID && unit->get_x() == m_player_->get_x()
      && unit->get_y() == m_player_->get_y();
  }

  bool World::is_player_fighting() const
  {
    REQUIRE(!m_grid_[m_player_->get_y()]->at(m_player_->get_x()).expired());
    return m_grid_[m_player_->get_y()]->at(m_player_->get_x()).lock()->ID != m_player_->ID;
  }

	void World::add_random_monsters(const int t_id)
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

  void World::spawn_player()
  {
    REQUIRE(m_player_);

    const int MIDDLE_Y = m_grid_.size() / 2, MIDDLE_X = m_grid_[FIRST_INDEX]->size() / 2;
    while (true)
    {
      switch (has_unit_on(MIDDLE_X, MIDDLE_Y))
      {
      case false: m_grid_[MIDDLE_Y]->at(MIDDLE_X) = m_player_;
        m_player_->set_position(MIDDLE_X, MIDDLE_Y);
        return;
      default: respawn_monster(m_grid_[MIDDLE_Y]->at(MIDDLE_X).lock()->ID);
      }
    }//always loop
  }

  void World::clear(const int t_x, const int t_y)
  {
    REQUIRE(t_y < static_cast<int>(m_grid_.size()) && t_x < static_cast<int>(m_grid_[t_y]->size()));
    m_grid_[t_y]->at(t_x) = std::weak_ptr<Unit>();
    PROMISE(m_grid_[t_y]->at(t_x).expired());
  }

  void World::reset()
  {
    REQUIRE(m_player_);

    std::cout << m_player_->get_name() << "has fallen !." << std::endl;
    /*
    for (int i = FIRST_INDEX; i < m_grid_.size(); ++i)
    {
      m_grid_.push_back(std::make_unique<std::vector<std::weak_ptr<Unit> >>
        (t_columns, std::weak_ptr<Unit>()));
    }

    srand(unsigned int(time(nullptr)));

    for (int i = FIRST_INDEX; i < t_monsters; ++i)
    {
      add_random_monsters(i);
      respawn_monster(i);
    }*/

    puts("game resetted.");
  }

}//namespace G6037599