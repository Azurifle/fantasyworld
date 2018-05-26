#include "stdafx.h"
#include "Map.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Map::Map()
  {
    const auto CAN_CONTAIN_PLAYER_MONSTER_N_SPAWNPOINT = 2;
    REQUIRE(Map::SIZE >= CAN_CONTAIN_PLAYER_MONSTER_N_SPAWNPOINT);

    for(auto row = 0; row < SIZE; ++row)
    {
      m_grid_.push_back(std::make_unique< std::vector<Tile> >(SIZE, Tile{}));
    }

    PROMISE(m_grid_[0]->at(0).owner_id == NO_UNIT);
  }

  Map::Map(const Map& t_to_copy)
  {
    copy_from(t_to_copy);
  }

  Map& Map::operator=(const Map& t_to_copy)
  {
    copy_from(t_to_copy);
    return *this;
  }

  //___ private _______________________________________________________
  void Map::copy_from(const Map& t_to_copy)
  {
    m_grid_.clear();

    const auto ANY_COLUMN = 0;
    for (unsigned row = 0; row < t_to_copy.m_grid_.size(); ++row)
    {
      m_grid_.push_back( std::make_unique< std::vector<Tile> >(SIZE, Tile{}) );

      for (unsigned col = 0; col < t_to_copy.m_grid_[ANY_COLUMN]->size(); ++col)
      {
        m_grid_[row]->at(col) = t_to_copy.m_grid_[row]->at(col);
      }
    }//row

    PROMISE(m_grid_[0]->at(0).owner_id == NO_UNIT);
  }

}//G6037599