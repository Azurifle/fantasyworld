#include "stdafx.h"
#include "World.hpp"
#include "Console.hpp"
#include "Map.hpp"
#include "Type_data.hpp"
#include "Timer.hpp"
#include "Spawn_to.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  const char* World::MONSTER_CONF_PATH = "monster_conf.txt";
  const char* World::PLAYER_NAME = "NoOne The Hero";
  const COORD World::UP = { 0, -1 };
  const COORD World::DOWN = { 0, 1 };
  const COORD World::LEFT = { -1, 0 };
  const COORD World::RIGHT = { 1, 0 };
  const COORD World::ZERO = { 0, 0 };

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

      const auto MILISEC_PER_KEY = 50;
      Sleep(MILISEC_PER_KEY);
    } while (clock() < TIME_UP);

    return NO_KEY_PRESS;
  }

  //___ (de)constructors _____________________________________________
  World::World() : m_map_(std::make_shared<Map>())
  , m_console_(std::make_shared<Console>())
  , m_player_(std::make_unique<Unit>(std::make_shared<Type_data>(
    PLAYER_NAME, "Ahhhhh, sh*t I'm dead.", "Punch!"
    , PLAYER_MAX_HP, PLAYER_ATK, PLAYER_MAX_ATK, '&')))
  {
    m_console_->show();
    
    m_player_->set_pos(COORD{ Map::MIDDLE, Map::MIDDLE });
    m_player_cursor_pos_ = m_player_->get_pos();
    m_map_->marked(m_player_->get_pos(), m_player_->get_id());

    m_console_->move_player_cursor(m_player_->get_pos());
    m_console_->marked(m_player_->get_pos(), std::string(1, m_player_->get_symbol()).c_str() );

    read_monster_types();

    srand(static_cast<unsigned int>(time(nullptr)));

    spawn_spawners();
    spawners_spawn_monster();
  }

  World::World(const World& t_to_copy) 
    : m_player_cursor_pos_(t_to_copy.m_player_cursor_pos_)
  {
    copy_from(t_to_copy);
  }

  World& World::operator=(const World& t_to_copy)
  {
    m_player_cursor_pos_ = t_to_copy.m_player_cursor_pos_;
    copy_from(t_to_copy);
    return *this;
  }

  //___ public _____________________________________________
  void World::player_move()
  {
    switch (m_console_->update_hour())
    {
    case Timer::HOUR_REACH: check_battle(); 
      break;
    default: monsters_stronger();
      update_monster_status_hp();
      update_cursor_status_hp();
    }//switch update_hour
  }

  void World::player_move(COORD t_move)
  {
    t_move.X = limit_interval(m_player_->get_pos().X + t_move.X, 0, m_map_->SIZE -1);
    t_move.Y = limit_interval(m_player_->get_pos().Y + t_move.Y, 0, m_map_->SIZE -1);

    for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
    {
      if (t_move.X == (*it)->get_pos().X && t_move.Y == (*it)->get_pos().Y)
      {
        update();
        return;
      }
    }//way blocked by spawner

    switch (m_console_->update_hour())
    {
    case Timer::HOUR_REACH: break;
    default: monsters_stronger();
      update_cursor_status_hp();
    }//switch update_hour

    switch (m_map_->is_attacker(m_player_->get_pos(), m_player_->get_id()))
    {
    case false: m_console_->marked(m_player_->get_pos(), "."); 
      break;
    default: m_console_->marked(m_player_->get_pos(), " ", true);
    }//move from battle?

    m_map_->move(m_player_->get_pos(), m_player_->get_id(), t_move);
    m_player_->set_pos(t_move);

    switch (m_map_->is_attacker(m_player_->get_pos(), m_player_->get_id()))
    {
    case false: m_console_->marked(t_move, std::string(1, m_player_->get_symbol()).c_str());
      m_console_->hide_monster_status();
      break;
    default: player_move_into_battle();
    }//move into battle?    
  }

  void World::move_cursor(const COORD& t_move)
  {
    m_player_cursor_pos_.X = limit_interval(m_player_cursor_pos_.X + t_move.X, 0, m_map_->SIZE);
    m_player_cursor_pos_.Y = limit_interval(m_player_cursor_pos_.Y + t_move.Y, 0, m_map_->SIZE);
    m_console_->move_player_cursor(m_player_cursor_pos_);
    
    const auto ENEMY_ID = m_map_->get(m_player_cursor_pos_);
    if(ENEMY_ID <= m_map_->NO_UNIT || ENEMY_ID == m_player_->get_id())
    {
      m_console_->hide_cursor_status();
    }
    else
    {
      for(auto it = m_spawners_.begin(); it < m_spawners_.end(); ++it)
      {
        if(ENEMY_ID == (*it)->get_id())
        {
          m_console_->hide_cursor_status();
          return;
        }
      }//check that it's not spawner

      const auto INDEX = find_spawner_index(ENEMY_ID);      
      m_console_->show_cursor_status(m_spawners_[INDEX]->get_type_name()
        , m_spawners_[INDEX]->find_hp(ENEMY_ID)
        , m_spawners_[INDEX]->get_type_max_hp()
        , m_spawners_[INDEX]->get_type_atk()
        , m_spawners_[INDEX]->get_type_max_atk());
    }//has unit that not player
  }

  void World::update()
  {
    switch (m_console_->update_minute())
    {
    case Timer::NOT_REACH: break;
    case Timer::HOUR_REACH: check_battle(); break;
    default: monsters_stronger();
      update_monster_status_hp();
      update_cursor_status_hp();
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
  void World::copy_from(const World& t_to_copy)
  {
    *m_console_ = *t_to_copy.m_console_;
    m_console_->show();

    *m_map_ = *t_to_copy.m_map_;
    *m_player_ = *t_to_copy.m_player_;

    m_spawners_.clear();
    for (unsigned i = 0; i < t_to_copy.m_spawners_.size(); ++i)
    {
      m_spawners_.push_back(std::make_unique<Spawn_to<Unit>>(
        t_to_copy.m_spawners_[i]->share_type(), m_console_, m_map_) );
    }

    m_console_->move_player_cursor(m_player_->get_pos());
  }

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
      m_spawners_.push_back(std::make_unique<Spawn_to<Unit>>( 
        tokenize(line), m_console_, m_map_) );
    }
    file_reader.close();
  }

  void World::spawn_spawners()
  {
    for (unsigned i = 0; i < m_spawners_.size(); ++i)
    {
      m_spawners_[i]->reset_type();
      m_spawners_[i]->set_pos(m_map_->random_unoccupied());
      m_map_->marked(m_spawners_[i]->get_pos(), m_spawners_[i]->get_id());
      m_console_->marked(m_spawners_[i]->get_pos(), m_spawners_[i]->get_symbol().c_str());
    }
  }

  void World::spawners_spawn_monster()
  {
    REQUIRE(0 < MONSTERS);
    REQUIRE(MONSTERS <= m_map_->SIZE * m_map_->SIZE);

    std::vector<int> size_per_types;
    const auto FIRST_MONSTER = 1;
    for (unsigned i = 0; i < m_spawners_.size(); ++i)
    {
      size_per_types.push_back(FIRST_MONSTER);
    }

    const auto AFTER_FIRST_MONSTER = m_spawners_.size() - 1;
    for (auto i = AFTER_FIRST_MONSTER; i < MONSTERS; ++i)
    {
      ++size_per_types[rand() % m_spawners_.size()];
    }

    for (unsigned i = 0; i < m_spawners_.size(); ++i)
    {
      m_spawners_[i]->spawn(size_per_types[i]);
    }
  }

  void World::monsters_stronger()
  {
    for (auto it = m_spawners_.begin(); it != m_spawners_.end(); ++it)
    {
      const auto PERCENT = 1;
      (*it)->monsters_stronger(PERCENT);
    }
  }

  void World::game_reset()
  {
    const auto THREE_SECOND = 3000, COUNT_DOWN = 9, ONE_SECOND = 1000;
    wait_key(THREE_SECOND);

    m_console_->show_game_reset();
    for(auto i = COUNT_DOWN; i > 0; --i)
    {
      m_console_->show_game_reset(i);
      switch (wait_key(ONE_SECOND))
      {
      case NO_KEY_PRESS: break;
      default: _getch();
      }
    }

    m_console_->show();

    m_map_->reset();

    m_player_->set_pos({ Map::MIDDLE , Map::MIDDLE });
    m_player_->set_hp(PLAYER_MAX_HP);
    m_map_->marked(m_player_->get_pos(), m_player_->get_id());
    m_console_->marked(m_player_->get_pos()
      , std::string(1, m_player_->get_symbol()).c_str());
    m_console_->set_player_full_hp();

    spawn_spawners();
    spawners_spawn_monster();
    m_console_->move_player_cursor(m_player_->get_pos());
  }

  void World::check_battle()
  {
    const auto ENEMY_ID = m_map_->get(m_player_->get_pos());
    if(ENEMY_ID == m_player_->get_id())
    {
      return;
    }

    const auto INDEX = find_spawner_index(ENEMY_ID);
    switch ( m_spawners_[INDEX]->damaged_n_dies(ENEMY_ID, m_player_->random_atk() ) )
    {
    case false: update_cursor_status_hp();
      
      m_player_->damaged(m_spawners_[INDEX]->random_type_atk());
      m_console_->set_player_hp(m_player_->get_hp());

      switch (m_player_->get_hp())
      {
        case 0: game_reset(); default:;
      } 
      break;
    default: monster_dies(ENEMY_ID, INDEX);
    }//switch monster dies
    
  }

  int World::find_spawner_index(const int t_monster_id) const
  {
    REQUIRE(t_monster_id > Map::NO_UNIT);

    for (unsigned i = 0; i < m_spawners_.size(); ++i)
    {
      if (t_monster_id <= m_spawners_[i]->get_last_id())
      {
        return i;
      }
    }
    PROMISE(false);//it's not monster id
    const auto NO_SPAWNER = -1;
    return NO_SPAWNER;
  }

  void World::update_monster_status_hp() const
  {
    const auto ENEMY_ID = m_map_->get(m_player_->get_pos());
    if (ENEMY_ID != m_player_->get_id())
    {
      const auto INDEX = find_spawner_index(ENEMY_ID);
      m_console_->set_monster_hp(m_spawners_[INDEX]->find_hp(ENEMY_ID)
        , m_spawners_[INDEX]->get_type_max_hp());
    }//player is attacker
  }

  void World::update_cursor_status_hp() const
  {
    const auto ENEMY_ID = m_map_->get(m_player_cursor_pos_);
    if (ENEMY_ID > m_map_->NO_UNIT && ENEMY_ID != m_player_->get_id())
    {
      for (auto it = m_spawners_.begin(); it < m_spawners_.end(); ++it)
      {
        if (ENEMY_ID == (*it)->get_id())
        {
          return;
        }
      }//check that it's not spawner

      const auto INDEX = find_spawner_index(ENEMY_ID);
      m_console_->set_cursor_hp(m_spawners_[INDEX]->find_hp(ENEMY_ID)
        , m_spawners_[INDEX]->get_type_max_hp());
    }
  }

  void World::player_move_into_battle()
  {
    m_console_->marked(m_player_->get_pos()
      , std::string(1, m_player_->get_symbol()).c_str(), true);

    const auto ENEMY_ID = m_map_->get(m_player_->get_pos())
      , INDEX = find_spawner_index(ENEMY_ID);
    m_console_->show_monster_status(m_spawners_[INDEX]->get_type_name()
      , m_spawners_[INDEX]->find_hp(ENEMY_ID)
      , m_spawners_[INDEX]->get_type_max_hp()
      , m_spawners_[INDEX]->get_type_atk()
      , m_spawners_[INDEX]->get_type_max_atk());
  }

  void World::monster_dies(const int t_enemy_id, const int t_index)
  {
    m_console_->hide_monster_status();

    m_map_->move(m_player_->get_pos(), m_player_->get_id(), m_player_->get_pos());
    m_console_->marked(m_player_->get_pos(), " ", true);
    m_console_->marked(m_player_->get_pos(), std::string(1, m_player_->get_symbol()).c_str());

    const auto RESPAWN_POS = m_spawners_[t_index]->find_pos(t_enemy_id);
    if (m_player_cursor_pos_.X == RESPAWN_POS.X
      && m_player_cursor_pos_.Y == RESPAWN_POS.Y)
    {
      m_console_->show_cursor_status(m_spawners_[t_index]->get_type_name()
        , m_spawners_[t_index]->find_hp(t_enemy_id)
        , m_spawners_[t_index]->get_type_max_hp()
        , m_spawners_[t_index]->get_type_atk()
        , m_spawners_[t_index]->get_type_max_atk());
    }
    else if (m_player_cursor_pos_.X == m_player_->get_pos().X
      && m_player_cursor_pos_.Y == m_player_->get_pos().Y)
    {
      m_console_->hide_cursor_status();
    }
  }

}//namespace G6037599