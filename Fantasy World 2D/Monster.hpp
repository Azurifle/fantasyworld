#ifndef MONSTER
#define MONSTER
#pragma once
#include "Unit.hpp"

namespace G6037599
{
	class Fantasy_world_2_d;

	class Monster: public Unit
	{
	public:
    virtual const char* get_attack_name() const = 0;
    virtual int get_attack_damage() const = 0;
    virtual char get_type() const = 0;

		explicit Monster(Fantasy_world_2_d& t_world, int t_id);

    void damaged(int t_damage) override;
    void print() const override;

		void update();
	  void set_target(const std::weak_ptr<Unit>& t_target);
		void respawns(int t_x, int t_y);
	private:
		Fantasy_world_2_d& m_world_;
		std::weak_ptr<Unit> m_target_ = std::weak_ptr<Unit>();
		int m_id_ = NOT_ASSIGN, m_x_ = NOT_ASSIGN, m_y_ = NOT_ASSIGN;

    void attacks() const;
	};
}

#endif //MONSTER
