#include "stdafx.h"
#include "Car.hpp"
#include "0._Game_Engine/Grid.hpp"

namespace G6037599
{
  //___ constructors _____________________________________________
  Car::Car(const std::string& t_name, const std::string& t_shape
    , const int t_id, const int t_max_fuel, const int t_speed)
    : m_name_(t_name), m_shape_(t_shape), m_pos_(Grid::NOT_SPAWN)
      , m_id_(t_id), m_max_fuel_(t_max_fuel), m_fuel_(t_max_fuel), m_speed_(t_speed) {}

  //___ public _____________________________________________
  void Car::spawned(const std::shared_ptr<Grid>& t_grid)
  {
    m_pos_ = t_grid->spawns(m_id_, m_shape_);
  }
}//G6037599