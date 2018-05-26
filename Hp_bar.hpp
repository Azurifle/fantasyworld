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
    Hp_bar(const Hp_bar& t_to_copy);
    Hp_bar& operator=(const Hp_bar& t_to_copy);

    void show() const;
    void increase_max(int t_increase);
    COORD get_pos() const;
  private:
    COORD m_start_ = {0, 0};
    int m_hp_ = 0, m_max_hp_ = 0;

    static int print_half_bar(int t_bar_left);
  };
}//G6037599

#endif //HP_BAR

