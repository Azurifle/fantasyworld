#include "stdafx.h"
#include "Spawn_point.hpp"
#include "Type_data.hpp"
#include "Tile_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Spawn_point::Spawn_point(const char* t_name, const char* t_dead_message
    , const char* t_atk_name, int t_max_hp, int t_atk, int t_max_atk, char t_symbol
    , const std::shared_ptr<Console> t_m_console, const std::shared_ptr<Map> t_m_map)
  {
    m_type_ = std::make_shared<Type_data>(t_name, t_dead_message, t_atk_name
      , t_max_hp, t_atk, t_max_atk, t_symbol);
    m_tile_ = std::make_unique<Tile_data>({0, 0});
    m_console_ = t_m_console;
    m_map_ = t_m_map;
  }

  Spawn_point::Spawn_point(const Spawn_point& t_to_copy)
  {
    m_type_ = t_to_copy.m_type_;
    m_tile_.reset();
    m_tile_ = std::make_unique<Tile_data>(t_to_copy.get_pos());
    m_console_ = t_to_copy.m_console_;
    m_map_ = t_to_copy.m_map_;
  }

  Spawn_point& Spawn_point::operator=(const Spawn_point& t_to_copy)
  {
    m_type_ = t_to_copy.m_type_;
    m_tile_.reset();
    m_tile_ = std::make_unique<Tile_data>(t_to_copy.get_pos());
    m_console_ = t_to_copy.m_console_;
    m_map_ = t_to_copy.m_map_;
    return *this;
  }
}//G6037599