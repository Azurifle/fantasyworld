#include "stdafx.h"
#include "Spawn_point.hpp"
#include "Type_data.hpp"
#include "Tile_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Spawn_point::Spawn_point(const std::shared_ptr<Type_data> t_type
    , const std::shared_ptr<Console> t_m_console, const std::shared_ptr<Map> t_m_map)
  {
    m_type_ = t_type;
    m_console_ = t_m_console;
    m_map_ = t_m_map;
    m_tile_ = std::make_unique<Tile_data>();
    m_symbol_ = "X"+ m_type_->SYMBOL;
  }

  Spawn_point::Spawn_point(const Spawn_point& t_to_copy)
  {
    copy_from(t_to_copy);
  }

  Spawn_point& Spawn_point::operator=(const Spawn_point& t_to_copy)
  {
    copy_from(t_to_copy);
    return *this;
  }

  COORD Spawn_point::get_pos() const
  {
    return m_tile_->get_pos();
  }

  //___ private _____________________________________________
  void Spawn_point::copy_from(const Spawn_point& t_to_copy)
  {
    m_type_ = t_to_copy.m_type_;
    m_console_ = t_to_copy.m_console_;
    m_map_ = t_to_copy.m_map_;
    m_tile_.reset();
    m_tile_ = std::make_unique<Tile_data>(t_to_copy.m_tile_->get_pos());
    m_symbol_ = "X" + m_type_->SYMBOL;
  }

}//G6037599