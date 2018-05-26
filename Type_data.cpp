#include "stdafx.h"
#include "Type_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Type_data::Type_data(const char* t_name, const char* t_dead_message, const char* t_atk_name
    , const int t_max_hp, const int t_atk, const int t_max_atk, const char t_symbol)
   : NAME(t_name), DEAD_MESSAGE(t_dead_message), ATK_NAME(t_atk_name)
    , ATK(t_atk), MAX_ATK(t_max_atk), SYMBOL(t_symbol), m_max_hp_(t_max_hp) {}

  Type_data& Type_data::operator=(const Type_data& t_to_copy)
  {
    m_max_hp_ = t_to_copy.m_max_hp_;
    return *this;
  }
}//G6037599