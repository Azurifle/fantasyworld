#ifndef UNIT
#define UNIT
#pragma once

namespace G6037599
{
  class Fantasy_world_2_d;

  class Unit
  {
  public:
    const int ID;

    Unit(Fantasy_world_2_d & t_world, int t_id);
    virtual ~Unit() = default;

    virtual void print_character() const = 0;

    void set_target(std::weak_ptr<Unit> t_target)
      , set_position(int t_x, int t_y);
    virtual void set_full_hp() = 0
      , update() = 0;
  protected:
    enum Status { NOT_ASSIGN = -1, DEAD };

    bool has_target() const
      , is_near_target() const;
    int get_hp() const, get_x() const, get_y() const;
    virtual const char* get_name() const = 0
      , * get_attack_name() const = 0;
    virtual int get_attack_power() const = 0;

    void set_hp(int t_new_hp);
    virtual void damaged(int t_damage) = 0;

    void attacks() const;
    void respawn() const;    
  private:
    Fantasy_world_2_d & m_world_;
    std::weak_ptr<Unit> m_target_ = std::weak_ptr<Unit>();
    int m_hp_ = NOT_ASSIGN, m_x_ = NOT_ASSIGN, m_y_ = NOT_ASSIGN;
  };
}

#endif //UNIT
