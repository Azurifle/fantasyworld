#include "stdafx.h"
#include "Tile_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Tile_data::Tile_data() : ID(m_id_count_)
  {
    ++m_id_count_;
  }

  Tile_data::Tile_data(const COORD& t_pos) : ID(m_id_count_), m_pos_(t_pos)
  {
    ++m_id_count_;
  }

  //___ public ________________________________________________
  COORD Tile_data::get_pos() const
  {
    return m_pos_;
  }

  void Tile_data::set_pos(const COORD& t_pos)
  {
    m_pos_ = t_pos;
  }
}//G6037599