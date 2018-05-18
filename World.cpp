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

  void World::update()
	{
    m_console_cursor_ = m_console_start_cursor_;

    if(m_player_)
    {
      switch (m_is_restart_)
      {
      case false: break;
      default: m_is_restart_ = false;
        reset();
        clean_console();
        move_grid_cursor(m_player_->get_x(), m_player_->get_y());
        return;
      }
      m_player_->update();
    }

		for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
		{
			(*it)->update();
		}

    clean_console();
    move_grid_cursor(m_player_->get_x(), m_player_->get_y());
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
    switch (WAS_SPAWNED_BEFORE)
    {
      case true: switch (is_fighting_w_player(m_monsters_[t_id]))
        {
        case false: clear(m_monsters_[t_id]->get_x(), m_monsters_[t_id]->get_y()); break;
        default: m_grid_[m_monsters_[t_id]->get_y()]->at(m_monsters_[t_id]->get_x()) = m_player_;

          move_grid_cursor(m_monsters_[t_id]->get_x(), m_monsters_[t_id]->get_y());
          m_player_->print_character();
          std::cout << ' ';
        } default:;
    }

		int spawn_x, spawn_y;
		do
		{
      spawn_y = rand() % m_grid_.size();
      spawn_x = rand() % m_grid_[FIRST_INDEX]->size();
    } while (has_unit_on(spawn_x, spawn_y));

    m_grid_[spawn_y]->at(spawn_x) = m_monsters_[t_id];
    m_monsters_[t_id]->set_position(spawn_x, spawn_y);
    m_monsters_[t_id]->set_full_hp();

	  switch (is_grid_built())
	  {
    case true: move_grid_cursor(spawn_x, spawn_y);
      m_monsters_[t_id]->print_character(); default:;
	  }
	}

  void World::build_console()
  { 
    m_console_start_cursor_ = Menu_ui::get_cursor();
    m_console_start_cursor_.X += SPACE_BEFORE_CONSOLE;
    m_console_cursor_ = m_console_start_cursor_;
    clean_console();
  }

  void World::build_grid()
  {
    puts("  --------------------------------- THE GRID -----------------------------------------");
    m_grid_start_cursor_ = Menu_ui::get_cursor();
    ++m_grid_start_cursor_.X;
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
          case false: std::cout << ' '; break;
          default: m_player_->print_character();
          }
        }//has_unit_on tile
      }
      puts("");
    }//row
  }

  void World::player_move(int t_x, int t_y)
  {
    t_x = Menu_ui::limit_interval(m_player_->get_x() + t_x, FIRST_INDEX, m_grid_[FIRST_INDEX]->size() - 1);
    t_y = Menu_ui::limit_interval(m_player_->get_y() + t_y, FIRST_INDEX, m_grid_.size() - 1);

    switch (is_player_fighting())
    {
    case false: clear(m_player_->get_x(), m_player_->get_y()); break;
    default: move_grid_cursor(m_player_->get_x(), m_player_->get_y(), true);
      std::cout << ' ';
    }
    m_player_->set_position(t_x, t_y);

    switch (has_unit_on(t_x, t_y))
    {
    case false: m_grid_[t_y]->at(t_x) = m_player_;
      move_grid_cursor(t_x, t_y);
      break;
    default: m_player_->set_target(m_grid_[t_y]->at(t_x));
      move_grid_cursor(t_x, t_y, true);
    }
    m_player_->print_character();
  }

  void World::set_restart()
  {
    m_is_restart_ = true;
  }

  void World::open_console() const
  {
    if (m_console_start_cursor_.X > NOT_ASSIGN)
    {
      REQUIRE(m_console_cursor_.X > NOT_ASSIGN);

      Menu_ui::move_cursor(m_console_cursor_);
    }
  }

  void World::end_console_line()
  {
    if(m_console_start_cursor_.X <= NOT_ASSIGN)
    {
      return;
    }

    m_console_cursor_ = Menu_ui::get_cursor();

    const auto CHARS_TO_REMOVE = 100;
    while(m_console_cursor_.X <= CHARS_TO_REMOVE)
    {
      std::cout << ' ';
      ++m_console_cursor_.X;
    }

    puts("");
    for(int i = FIRST_INDEX; i < SPACE_BEFORE_CONSOLE; ++i)
    {
      std::cout << ' ';
    }

    m_console_cursor_ = Menu_ui::get_cursor();
  }

  //___ private _______________________________________________________
  bool World::has_unit_on(const int t_x, const int t_y) const
  {
    return !m_grid_[t_y]->at(t_x).expired();
  }

  bool World::is_fighting_w_player(const std::shared_ptr<Unit> t_unit) const
  {
    if(m_player_)
    {
      return t_unit->ID != m_player_->ID && t_unit->get_x() == m_player_->get_x()
        && t_unit->get_y() == m_player_->get_y();
    }
    return false;
  }

  bool World::is_player_fighting() const
  {
    REQUIRE(has_unit_on(m_player_->get_x(), m_player_->get_y()));
    return m_grid_[m_player_->get_y()]->at(m_player_->get_x()).lock()->ID != m_player_->ID;
  }

  bool World::is_grid_built() const
  {
    return m_grid_start_cursor_.X > NOT_ASSIGN;
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
    switch (has_unit_on(MIDDLE_X, MIDDLE_Y))
    {
      case false: break;
      default: respawn_monster(m_grid_[MIDDLE_Y]->at(MIDDLE_X).lock()->ID);
    }
    m_grid_[MIDDLE_Y]->at(MIDDLE_X) = m_player_;
    m_player_->set_position(MIDDLE_X, MIDDLE_Y);

    switch (is_grid_built())
    {
      case true: move_grid_cursor(MIDDLE_X, MIDDLE_Y);
        m_player_->print_character(); default:;
    }
  }

  void World::clear(const int t_x, const int t_y)
  {
    REQUIRE(t_y < static_cast<int>(m_grid_.size()) && t_x < static_cast<int>(m_grid_[t_y]->size()));

    m_grid_[t_y]->at(t_x) = std::weak_ptr<Unit>();

    move_grid_cursor(t_x, t_y);
    std::cout << ". ";

    PROMISE(m_grid_[t_y]->at(t_x).expired());
  }

  void World::reset()
  {
    REQUIRE(m_player_);

    open_console();
      std::cout << m_player_->get_name() << " has fallen !.";
      end_console_line();
    end_console_line();

    const auto GRID_ROWS = static_cast<int>(m_grid_.size())
	    , GRID_COLUMNS = static_cast<int>(m_grid_[FIRST_INDEX]->size());
    for (int row = FIRST_INDEX; row < GRID_ROWS; ++row)
    {
      for (int column = FIRST_INDEX; column < GRID_COLUMNS; ++column)
      {
        clear(column, row);
      }
    }

    m_player_->set_full_hp();
    spawn_player();

    const int MONSTERS = m_monsters_.size();
    m_monsters_.clear();

    for (int i = FIRST_INDEX; i < MONSTERS; ++i)
    {
      add_random_monsters(i);
      respawn_monster(i);
      m_monsters_[i]->set_target(m_player_);
    }

    open_console();
      std::cout << "game resetted.";
    end_console_line();
  }

  void World::move_grid_cursor(const int t_x, const int t_y, const bool t_challenger) const
  {
    const auto TO_CHALLENGER_SLOT = 1;

    switch(is_grid_built())
    {
      case true: Menu_ui::move_cursor(m_grid_start_cursor_.Y + t_y
        , m_grid_start_cursor_.X + t_x * SPACE_BETWEEN_GRID 
        + (t_challenger ? TO_CHALLENGER_SLOT : NONE)); default:;
    }
  }

  void World::clean_console()
  {
    open_console();
    const auto LAST_CONSOLE_ROW = m_console_start_cursor_.Y + CONSOLE_ROWS;
    //0 player attack
    //1 monster damaged
    //2
    //3 monster attack
    //4 player damaged
    //5 player dead message
    while(m_console_cursor_.Y < LAST_CONSOLE_ROW)
    {
      end_console_line();
    }
  }

}//namespace G6037599