#include "stdafx.h"
#include "World.hpp"
#include "Console.hpp"
#include "Map.hpp"
#include "Unit.hpp"
#include "Type_data.hpp"
#include "Spawn_point.hpp"
#include "Timer.hpp"

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

  int World::wait_key(const int t_miliseconds)
  {
    const auto TIME_UP = clock() + t_miliseconds;
    do
    {
      switch (_kbhit())
      {
      case NO_KEY_PRESS: break;
      default: return _getch();
      }

      const auto HALF_SECOND = 500;
      Sleep(HALF_SECOND);
    } while (clock() < TIME_UP);

    return NO_KEY_PRESS;
  }

  //___ (de)constructors _____________________________________________
  World::World()
  {
    m_console_ = std::shared_ptr<Console>();
    m_console_->show();

    m_map_ = std::make_shared<Map>();

    m_player_ = std::make_unique<Unit>(std::make_shared<Type_data>(
        PLAYER_NAME, "Ahhhhh, sh*t I'm dead.", "Punch!"
        , PLAYER_MAX_HP, PLAYER_ATK, PLAYER_MAX_ATK, '&') );
    m_player_->set_pos(COORD{ Map::MIDDLE, Map::MIDDLE });

    m_map_->marked(m_player_->get_pos(), m_player_->get_id());
    m_console_->move_player_cursor(m_player_->get_pos());
    m_console_->marked(m_player_->get_pos(), std::string(1, m_player_->get_symbol()).c_str() );

    read_monster_types();

    srand(static_cast<unsigned int>(time(nullptr)));

    spawn_spawners();
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

    for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
    {
      if (t_move.X == (*it)->get_pos().X || t_move.Y == (*it)->get_pos().Y)
      {
        update();
        return;
      }
    }

    switch (m_map_->is_attacker(m_player_->get_pos(), m_player_->get_id()))
    {
    case false: m_console_->marked(m_player_->get_pos(), " ");
    default: m_console_->marked(m_player_->get_pos(), " ", true);
    }
    m_map_->move(m_player_->get_pos(), m_player_->get_id(), t_move);
    m_console_->marked(t_move, std::string(1, m_player_->get_symbol()).c_str());

    switch (m_console_->update_hour())
    {
    case Timer::HOUR_REACH: check_battle(); break;
    default: monster_stronger();
    }//switch update_hour
  }

  void World::move_cursor(const COORD& t_move)
  {
    m_player_cursor_pos_.X = limit_interval(m_player_cursor_pos_.X + t_move.X, 0, m_map_->SIZE);
    m_player_cursor_pos_.Y = limit_interval(m_player_cursor_pos_.Y + t_move.Y, 0, m_map_->SIZE);
    m_console_->move_player_cursor(m_player_cursor_pos_);
    
    auto enemy_id = m_map_->get(m_player_cursor_pos_);
    if(enemy_id <= m_map_->NO_UNIT || enemy_id == m_player_->get_id())
    {
      m_console_->hide_cursor_status();
    }
    else
    {
      for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
      {
        if (enemy_id == (*it)->get_id())
        {
          m_console_->hide_cursor_status();//add bool already hide or not
          return;
        }
      }

      for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
      {
        if (enemy_id <= (*it)->get_last_id())
        {
          m_console_->update_cursor_status((*it)->get_type_name(), (*it)->get_hp(enemy_id)
            , (*it)->get_type_max_hp(), (*it)->get_type_atk(), (*it)->get_type_max_atk());
          break;
        }//if this spawner manage this monster
      }
    }//has unit that not player
  }

  void World::update()
  {
    switch (m_console_->update_minute())
    {
    case Timer::NOT_REACH: break;
    case Timer::HOUR_REACH: check_battle(); break;
    default: monster_stronger();
    }//switch update minute
  }

  void World::exit() const
  {
    system("CLS");
    m_console_->thanks_user();
    _getch();
    _getch();
  }

  //___ private _______________________________________________________
  std::shared_ptr<Type_data> World::tokenize(const std::string& t_line) const
  {
    std::istringstream string_cutter(t_line);
    std::string token, name, dead_message, atk_name;
    const auto TAB = '\t';
    std::getline(string_cutter, name, TAB);
    std::getline(string_cutter, dead_message, TAB);
    std::getline(string_cutter, atk_name, TAB);

    std::getline(string_cutter, token, TAB);
    auto max_hp = std::stoi(token);
    std::getline(string_cutter, token, TAB);
    auto atk = std::stoi(token);
    std::getline(string_cutter, token, TAB);
    auto max_atk = std::stoi(token);

    std::getline(string_cutter, token, TAB);
    const auto TO_CHAR = 0;

    return std::make_shared<Type_data>(name.c_str(), dead_message.c_str(), atk_name.c_str()
      , max_hp, atk, max_atk, token[TO_CHAR]);
  }

  void World::read_monster_types()
  {
    std::ifstream file_reader(MONSTER_CONF_PATH);
    REQUIRE(file_reader.is_open());

    std::string line;
    while (std::getline(file_reader, line))
    {
      m_spawners_.push_back(std::make_unique<Spawn_point>( tokenize(line), m_console_, m_map_));
    }
    file_reader.close();
  }

  void World::spawners_spawn_monster()
  {
    const auto HEIGHT_X_WIDTH = 2;
    REQUIRE(0 < MONSTERS && MONSTERS <= m_map_->SIZE * HEIGHT_X_WIDTH);

    std::vector<int> each_type_random;
    auto total_random = 0;
    for (unsigned i = 0; i < m_spawners_.size(); ++i)
    {
      each_type_random.push_back(rand() % MONSTERS);
      total_random += each_type_random[i];
    }
    total_random /= MONSTERS;

    for (unsigned i = 0; i < m_spawners_.size(); ++i)
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
    for (unsigned i = 0; i < t_to_copy.m_spawners_.size(); ++i)
    {
      m_spawners_.push_back( std::make_unique<Spawn_point>(*t_to_copy.m_spawners_[i]) );
    }

    m_console_->move_player_cursor(m_player_->get_pos());
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
    const auto THREE_SECOND = 3000, COUNT_DOWN = 3, ONE_SECOND = 1000;
    wait_key(THREE_SECOND);

    m_console_->show_game_reset();
    for(auto i = COUNT_DOWN; i > 0; --i)
    {
      m_console_->show_game_reset(i);
      switch (wait_key(ONE_SECOND))
      {
        case NO_KEY_PRESS: break;
        default: i = 0;
          system("CLS");
          m_console_->show();
      }
    }

    m_map_->reset();

    m_player_->set_pos(COORD{ Map::MIDDLE , Map::MIDDLE });
    m_player_->set_full_hp();
    m_map_->marked(m_player_->get_pos(), m_player_->get_id());
    m_console_->marked(m_player_->get_pos(), m_player_->get_symbol());
    m_console_->set_player_full_hp();

    spawn_spawners();
    spawners_spawn_monster();
    m_console_->move_player_cursor(m_player_->get_pos());
  }

  void World::check_battle()
  {
    auto enemy_id = m_map_->has_battle(m_player_->get_pos());
    switch (enemy_id)
    {
    case Map::NO_UNIT: break;
    default: for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
      {
        if (enemy_id <= (*it)->get_last_id())
        {
          (*it)->damaged(enemy_id, m_player_->find_atk());

          auto hp_left = m_player_->damaged((*it)->find_atk(enemy_id));
          m_console_->set_player_hp(hp_left);
          switch (hp_left) { case 0: game_reset(); default:; }
        }//if this spawner manage this monster
      }
    }//switch enemy_id
  }

  void World::spawn_spawners()
  {
    for (unsigned i = 0; i < m_spawners_.size(); ++i)
    {
      m_spawners_[i]->set_pos(m_map_->random_unoccupied());
      m_map_->marked(m_spawners_[i]->get_pos(), m_spawners_[i]->get_id());
      m_console_->marked(m_spawners_[i]->get_pos(), m_spawners_[i]->get_symbol());
    }
  }

}//namespace G6037599