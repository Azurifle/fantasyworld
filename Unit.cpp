#include "stdafx.h"
#include "Unit.hpp"
#include "Type_data.hpp"
#include "Tile_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Unit::Unit(const char* t_name, const char* t_dead_message, const char* t_atk_name
    , const int t_max_hp, const int t_atk, const int t_max_atk
    , const char t_symbol, const COORD& t_pos) : m_hp_(t_max_hp)
  {
    m_type_ = std::make_shared<Type_data>(t_name, t_dead_message, t_atk_name
      , t_max_hp, t_atk, t_max_atk, t_symbol);

    m_tile_ = std::make_unique<Tile_data>(t_pos);
  }

  Unit::Unit(const Unit& t_to_copy)
  {
    m_hp_ = t_to_copy.m_hp_;
    m_type_ = t_to_copy.m_type_;//shared
    m_tile_.reset();
    m_tile_ = std::make_unique<Tile_data>(t_to_copy.m_tile_->get_pos);
  }

  Unit& Unit::operator=(const Unit& t_to_copy)
  {
    m_hp_ = t_to_copy.m_hp_;
    m_type_ = t_to_copy.m_type_;//shared
    m_tile_.reset();
    m_tile_ = std::make_unique<Tile_data>(t_to_copy.m_tile_->get_pos);
    return *this;
  }

  //___ public ________________________________________________
}
