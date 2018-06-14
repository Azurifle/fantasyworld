#include "stdafx.h"
#include "Car.hpp"

namespace G6037599
{
  //___ constructors _____________________________________________
  Car::Car(const std::string& t_name, const std::string& t_shape, const int t_max_fuel, const int t_speed)
    : m_name_(t_name), m_shape_(t_shape)
      , m_max_fuel_(t_max_fuel), m_fuel_(t_max_fuel), m_speed_(t_speed) {}
}//G6037599