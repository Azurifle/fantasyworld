#include "stdafx.h"
#include "Type_data.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Type_data::Type_data(const std::string& t_name
    , const std::string& t_dead_message, const std::string& t_atk_name
    , const int t_max_hp, const int t_atk, const int t_max_atk, const char t_symbol)
   : NAME(t_name), DEAD_MESSAGE(t_dead_message), ATK_NAME(t_atk_name)
    , ATK(t_atk), MAX_ATK(t_max_atk), SYMBOL(t_symbol), m_max_hp_(t_max_hp) {}

  Type_data& Type_data::operator=(const Type_data& t_to_copy)
  {
    m_max_hp_ = t_to_copy.m_max_hp_;
    return *this;
  }

  //___ public ________________________________________________
  int Type_data::get_max_hp() const
  {
    return m_max_hp_;
  }

  void Type_data::increase_max_hp(const int t_amount)
  {
    m_max_hp_ += t_amount;
  }

  int Type_data::random_atk() const
  {
    const auto RANDOM_SIZE = MAX_ATK + 1 - ATK;
    return ATK + rand() % RANDOM_SIZE;
  }
}//G6037599