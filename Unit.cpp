#include "stdafx.h"
#include "Unit.hpp"
#include "Fantasy_world_2_d.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Unit::Unit(Fantasy_world_2_d& t_world, const int t_id)
    : ID(t_id), m_world_(t_world)
  {
    REQUIRE(t_id > NOT_ASSIGN);
  }

  //___ public ________________________________________________
  void Unit::set_target(const std::weak_ptr<Unit> t_target)
  {
    m_target_ = t_target;
  }

  void Unit::set_position(const int t_x, const int t_y)
  {
    REQUIRE(t_x > NOT_ASSIGN && t_y > NOT_ASSIGN);

    if (m_x_ != NOT_ASSIGN)
    {
      m_world_.despawn(m_x_, m_y_);
    }

    m_x_ = t_x;
    m_y_ = t_y;
  }

  //___ protected ________________________________________________
  bool Unit::has_target() const
  {
    return !m_target_.expired();
  }

  bool Unit::is_near_target() const
  {
    REQUIRE(has_target());
    const auto target = m_target_.lock();
    return target->get_x() == m_x_ && target->get_y() == m_y_;
  }

  int Unit::get_hp() const
  {
    return m_hp_;
  }

  int Unit::get_x() const
  {
    return m_x_;
  }

  int Unit::get_y() const
  {
    return m_y_;
  }

  void Unit::set_hp(const int t_new_hp)
  {
    m_hp_ = t_new_hp;
  }

  void Unit::respawn() const
  {
    m_world_.spawn(ID);
  }

  void Unit::attacks() const
  {
    auto target = m_target_.lock();
    std::cout << get_name() << " attacks " << target->get_name()
      << " with " << get_attack_name() << "." << std::endl;
    target->damaged(get_attack_power());
  }
}
