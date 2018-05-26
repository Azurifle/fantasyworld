#include "stdafx.h"
#include "Status_panel.hpp"
#include "Hp_bar.hpp"
#include "Console.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Status_panel::Status_panel(COORD t_pos) : m_start_(t_pos)
  {
    ++t_pos.Y;
    ++t_pos.X;
    m_hp_ = std::make_unique<Hp_bar>(t_pos);
  }

  Status_panel::Status_panel(const Status_panel& t_to_copy)
  {
    m_start_ = t_to_copy.m_start_;
    m_name_ = t_to_copy.m_name_;
    *m_hp_ = *t_to_copy.m_hp_;
    m_atk_ = t_to_copy.m_atk_;
    m_max_atk_ = t_to_copy.m_max_atk_;
  }

  Status_panel& Status_panel::operator=(const Status_panel& t_to_copy)
  {
    m_start_ = t_to_copy.m_start_;
    m_name_ = t_to_copy.m_name_;
    *m_hp_ = *t_to_copy.m_hp_;
    m_atk_ = t_to_copy.m_atk_;
    m_max_atk_ = t_to_copy.m_max_atk_;
    return *this;
  }

  //___ public _______________________________________________________
  void Status_panel::show() const
  {
    auto cursor = m_start_;
    Console::set_cursor(cursor);
    std::cout << "-- " << m_name_ << " ";
    std::cout << std::setw(cursor.X + WIDTH - Console::get_cursor().X) << std::setfill('-');

    m_hp_->show();

    const auto ROW_ATK = 2;
    cursor.Y += ROW_ATK;
    ++cursor.X;
    Console::set_cursor(cursor);
    std::cout << "ATK: " << m_atk_ << " - " << m_max_atk_;

    ++cursor.Y;
    Console::set_cursor(cursor);
    std::cout << std::setw(WIDTH) << std::setfill('-');
  }

  COORD Status_panel::get_pos() const
  {
    return m_start_;
  }
}//G6037599