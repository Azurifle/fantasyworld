#ifndef HP_BAR
#define HP_BAR
#pragma once

namespace G6037599
{
  class Hp_bar
  {
  public:
    explicit Hp_bar(const COORD& t_pos);
    ~Hp_bar() = default;
    Hp_bar(const Hp_bar& t_to_copy) = default;//no (smart)pointer
    Hp_bar& operator=(const Hp_bar& t_to_copy) = default;

    COORD get_pos() const;
    void set(int t_hp, int t_max_hp) const;
  private:
    COORD m_start_ = {0, 0};

    static int print_half_bar(int t_bar_left);
  };
}//G6037599

#endif //HP_BAR

