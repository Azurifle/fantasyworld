#include "stdafx.h"
#include "World.hpp"
#include "Console.hpp"
#include "Map.hpp"
#include "Unit.hpp"
#include "Spawn_point.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  short World::limit_interval(int t_number, const int t_min, const int t_max)
  {
    if (t_number < t_min)
      t_number = t_min;
    else if (t_number > t_max)
      t_number = t_max;
    return static_cast<short>(t_number);
  }

  //___ (de)constructors _____________________________________________
  World::World()
  {
    m_console_ = std::make_unique<Console>();
    m_console_->show();

    m_map_ = std::make_shared<Map>();

    const short MIDDLE_MAP = static_cast<short>(m_map_->SIZE) / 2;
    m_player_ = std::make_unique<Unit>(PLAYER_NAME, "Ahhhhh, sh*t I'm dead.", "Punch!"
      , PLAYER_MAX_HP, PLAYER_ATK, PLAYER_MAX_ATK, '&', { MIDDLE_MAP, MIDDLE_MAP });
    m_map_->marked(m_player_->get_pos(), m_player_->get_id());
    m_console_->marked(m_player_->get_pos(), m_player_->get_symbol());

    read_monster_types();

    for(auto i = 0; i < m_spawners_.size(); ++i)
    {
      m_map_->marked(m_spawners_[i]->get_pos(), m_spawners_[i]->get_id());
      m_console_->marked(m_spawners_[i]->get_pos(), m_spawners_[i]->get_symbol());
    }

    spawners_spawn_monster();
  }

  World::World(const World& t_to_copy)
  {
    copy_from(t_to_copy);
  }

  World& World::operator=(const World& t_to_copy)
  {
    copy_from(t_to_copy);
    return *this;
  }

  //___ public _____________________________________________
  void World::player_move(COORD t_move)
  {
    t_move.X = limit_interval(m_player_->get_pos().X + t_move.X, 0, m_map_->SIZE);
    t_move.Y = limit_interval(m_player_->get_pos().Y + t_move.Y, 0, m_map_->SIZE);
    //*******************
    switch (m_map_->explore(m_player_->get_pos(), m_player_->get_id(), t_move))
    {
    case NO_UNIT: clear(m_player_->get_x(), m_player_->get_y()); break;
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

  void World::move_cursor(COORD t_move)
  {
    
  }

  void World::update()
  {
    switch (m_console_->update_minute())
    {
    case m_console_->NOTHING: break;
    case m_console_->HOUR_REACH: auto enemy_id = m_map_->has_battle(m_player_->get_pos());
      switch (enemy_id)
      {
      case NO_UNIT: break;
      default: for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
        {
          if (enemy_id <= (*it)->get_last_id())
          {
            (*it)->damaged(enemy_id, m_player_->find_atk());

            auto hp_left = m_player_->damaged((*it)->find_atk(enemy_id));
            if (hp_left <= 0)
            {
              game_reset();
            }
            else
            {
              m_console_->set_player_hp(hp_left);
            }
          }//if monster in this spawner
        }//for who in chart of the monster
      }
    default: monster_stronger();
    }//switch update minute
  }

  void World::exit() const
  {

  }

  //___ private _______________________________________________________
  char World::tokenize(const std::string& t_line, std::string& t_name
    , std::string& t_dead_message, std::string& t_atk_name
    , int& t_max_hp, int& t_atk, int& t_max_atk) const
  {
    std::istringstream string_cutter(t_line);
    std::string token;
    const auto TAB = '\t';
    std::getline(string_cutter, t_name, TAB);
    std::getline(string_cutter, t_dead_message, TAB);
    std::getline(string_cutter, t_atk_name, TAB);

    std::getline(string_cutter, token, TAB);
    t_max_hp = std::stoi(token);
    std::getline(string_cutter, token, TAB);
    t_atk = std::stoi(token);
    std::getline(string_cutter, token, TAB);
    t_max_atk = std::stoi(token);

    std::getline(string_cutter, token, TAB);
    const auto TO_CHAR = 0;
    return token[TO_CHAR];
  }

  void World::read_monster_types()
  {
    std::ifstream file_reader(MONSTER_CONF_PATH);
    REQUIRE(file_reader.is_open());

    std::string line;
    while (std::getline(file_reader, line))
    {
      std::string name, dead_message, atk_name;
      auto max_hp = 1, atk = 1, max_atk = 1;
      auto symbol = tokenize(line, name, dead_message, atk_name, max_hp, atk, max_atk);

      m_spawners_.push_back(std::make_unique<Spawn_point>(name, dead_message, atk_name
        , max_hp, atk, max_atk, symbol, m_console_, m_map_, m_map_->random_unoccupied()));
    }
    file_reader.close();
  }

  void World::spawners_spawn_monster()
  {
    const auto HEIGHT_X_WIDTH = 2;
    REQUIRE(0 < MONSTERS && MONSTERS <= m_map_->SIZE * HEIGHT_X_WIDTH);

    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<int> each_type_random;
    auto total_random = 0;
    for (auto i = 0; i < m_spawners_.size(); ++i)
    {
      each_type_random.push_back(rand() % MONSTERS);
      total_random += each_type_random[i];
    }
    total_random /= MONSTERS;

    for (auto i = 0; i < m_spawners_.size(); ++i)
    {
      m_spawners_[i]->spawn(each_type_random[i] / total_random);
    }
  }

  void World::copy_from(const World& t_to_copy)
  {
    *m_console_ = *t_to_copy.m_console_;
    m_console_->show();

    *m_map_ = *t_to_copy.m_map_;
    *m_player_ = *t_to_copy.m_player_;

    m_spawners_.clear();
    for (auto i = 0; i < t_to_copy.m_spawners_.size(); ++i)
    {
      m_spawners_.push_back( std::make_unique<Spawn_point>(*t_to_copy.m_spawners_[i]) );
    }
  }

  void World::monster_stronger()
  {
    for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
    {
      const auto PERCENT = 1;
      (*it)->monster_stronger(PERCENT);
    }
  }

  void World::game_reset()
  {

  }
}//namespace G6037599