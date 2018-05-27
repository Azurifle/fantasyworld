#include "stdafx.h"
#include "Unit.hpp"
#include "Type_data.hpp"
#include "Tile_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Unit::Unit(const std::shared_ptr<Type_data> t_type) : m_hp_(t_type->get_max_hp())
  {
    m_type_ = t_type;
    m_tile_ = std::make_unique<Tile_data>();
  }

  Unit::Unit(const Unit& t_to_copy)
  {
    copy_from(t_to_copy);
  }

  Unit& Unit::operator=(const Unit& t_to_copy)
  {
    copy_from(t_to_copy);
    return *this;
  }

  //___ public ________________________________________________
  COORD Unit::get_pos() const
  {
    return m_tile_->get_pos();
  }

  int Unit::get_id() const
  {
    return m_tile_->ID;
  }

  char Unit::get_symbol() const
  {
    return m_type_->SYMBOL;
  }

  void Unit::set_pos(const COORD& t_pos) const
  {
    m_tile_->set_pos(t_pos);
  }

  //___ private ________________________________________________
  void Unit::copy_from(const Unit& t_to_copy)
  {
    m_hp_ = t_to_copy.m_hp_;
    m_type_ = t_to_copy.m_type_;//shared
    m_tile_.reset();
    m_tile_ = std::make_unique<Tile_data>(t_to_copy.m_tile_->get_pos());
  }
}//G6037599
