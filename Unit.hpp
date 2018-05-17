#ifndef UNIT
#define UNIT
#pragma once
#include "World.hpp"

namespace G6037599
{
  class Unit
  {
  public:
    const int ID;

    Unit(World & t_world, int t_id);
    virtual ~Unit() = default;

    int get_x() const, get_y() const;
    virtual const char* get_name() const = 0;
    virtual void print_character() const = 0;

    void set_target(std::weak_ptr<Unit> t_target)
      , set_position(int t_x, int t_y);
    virtual void set_full_hp() = 0
      , update() = 0;
  protected:
    static const int DEAD = 0;

    bool has_target() const
      , is_near_target() const;
    int get_hp() const;
    virtual const char* get_attack_name() const = 0;
    virtual int get_attack_power() const = 0;
    
    void set_hp(int t_new_hp);
    void clear_target();

    void attacks() const;
    void damaged(int t_damage);
    virtual void dies() = 0;
    void respawn() const;
    void game_reset() const;
  private:
    World & m_world_;
    std::weak_ptr<Unit> m_target_ = std::weak_ptr<Unit>();
    int m_hp_ = World::NOT_ASSIGN, m_x_ = World::NOT_ASSIGN, m_y_ = World::NOT_ASSIGN;
  };
}

#endif //UNIT
