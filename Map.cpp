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

  //___ public _______________________________________________________
  void Map::marked(const COORD& t_pos, const int t_id)
  {
    REQUIRE(0 <= t_pos.X && t_pos.X < SIZE);
    REQUIRE(0 <= t_pos.Y && t_pos.Y < SIZE);
    REQUIRE(t_id > NO_UNIT);

    m_grid_[t_pos.Y]->at(t_pos.X).owner_id = t_id;
  }

  bool Map::is_attacker(const COORD& t_pos, const int t_id) const
  {
    REQUIRE(0 <= t_pos.X && t_pos.X < SIZE);
    REQUIRE(0 <= t_pos.Y && t_pos.Y < SIZE);

    return m_grid_[t_pos.Y]->at(t_pos.X).attacker_id == t_id;
  }

  void Map::move(const COORD& t_from, const int t_id, const COORD& t_to)
  {
    REQUIRE(0 <= t_from.X && t_from.X < SIZE);
    REQUIRE(0 <= t_from.Y && t_from.Y < SIZE);
    REQUIRE(t_id > NO_UNIT);
    REQUIRE(0 <= t_to.X && t_to.X < SIZE);
    REQUIRE(0 <= t_to.Y && t_to.Y < SIZE);

    switch (is_attacker(t_from, t_id))
    {
    case false: REQUIRE(m_grid_[t_from.Y]->at(t_from.X).owner_id == t_id);
      m_grid_[t_from.Y]->at(t_from.X).owner_id = NO_UNIT;
    default: m_grid_[t_from.Y]->at(t_from.X).attacker_id = NO_UNIT;;
    }

    switch (m_grid_[t_to.Y]->at(t_to.X).owner_id)
    {
    case NO_UNIT: m_grid_[t_to.Y]->at(t_to.X).owner_id = t_id; break;
    default: m_grid_[t_to.Y]->at(t_to.X).attacker_id = t_id;
    }
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