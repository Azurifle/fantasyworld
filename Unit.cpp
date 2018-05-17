#include "stdafx.h"
#include "Unit.hpp"
#include "World.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Unit::Unit(World& t_world, const int t_id)
    : ID(t_id), m_world_(t_world) {}

  //___ public ________________________________________________
  int Unit::get_x() const
  {
    return m_x_;
  }

  int Unit::get_y() const
  {
    return m_y_;
  }

  void Unit::set_target(const std::weak_ptr<Unit> t_target)
  {
    m_target_ = t_target;
  }

  void Unit::set_position(const int t_x, const int t_y)
  {
    REQUIRE(t_x > World::NOT_ASSIGN && t_y > World::NOT_ASSIGN);

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

  void Unit::set_hp(const int t_new_hp)
  {
    m_hp_ = t_new_hp;
  }

  void Unit::clear_target()
  {
    m_target_ = std::weak_ptr<Unit>();
  }

  void Unit::attacks() const
  {
    auto target = m_target_.lock();
    std::cout << get_name() << " attacks " << target->get_name()
      << " with " << get_attack_name() << "." << std::endl;
    target->damaged(get_attack_power());
  }

  void Unit::damaged(const int t_damage)
  {
    m_hp_ -= t_damage;
    std::cout << get_name() << " -" << t_damage << " damage. Now has " << m_hp_ << " health."
      << std::endl;
    if (m_hp_ <= DEAD)
    {
      std::cout << get_name() << " dead message: ..."; 
      dies();
      puts("");
    }
    puts("");
  }

  void Unit::respawn() const
  {
    m_world_.respawn_monster(ID);
  }

  void Unit::game_reset() const
  {
    m_world_.set_restart();
  }

}
