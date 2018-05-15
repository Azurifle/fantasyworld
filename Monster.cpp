#include "stdafx.h"
#include "Monster.hpp"
#include "Fantasy_world_2_d.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
	Monster::Monster(Fantasy_world_2_d& t_world, const int t_id)
    : m_world_(t_world), m_id_(t_id)
	{
    REQUIRE(t_id >= 0);
	}

  //___ public _______________________________________________________
  void Monster::damaged(const int t_damage)
  {
    hp_ -= t_damage;
    if(hp_ <= 0)
    {
      m_world_.spawn(m_id_);
    }
  }

  void Monster::update()
  {
    if (m_target_.expired())
    {
      damaged(1);
    }
    else
    {
      attacks();
    }
  }

  void Monster::set_target(const std::weak_ptr<Unit>& t_target)
	{
    m_target_ = t_target;
	}

	void Monster::respawns(const int t_x, const int t_y)
	{
    REQUIRE(t_x >= 0 && t_y >= 0);

		if (m_x_ != NOT_ASSIGN)
		{
      m_world_.despawn(m_x_, m_y_);
		}

		m_x_ = t_x;
		m_y_ = t_y;

		const auto RANDOM_0_1 = 2;
		hp_ = get_max_hp() + rand() % RANDOM_0_1;

    PROMISE(hp_ > 0);
	}

  //___ public const _________________________________________________
  void Monster::print() const
  {
    std::cout << m_id_ << get_type() << ':' << hp_;
  }

  //___ private _______________________________________________________
  void Monster::attacks() const
  {
    auto target = m_target_.lock();
    std::cout << get_name() << m_id_ << " attacks " << target->get_name()
      << " with " << get_attack_name() << "." << std::endl;
    target->damaged(get_attack_damage());
  }
}