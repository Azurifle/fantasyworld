#ifndef CONSOLE
#define CONSOLE
#pragma once

namespace G6037599
{
  class Status_panel;
  class Hp_bar;
  class Timer;

  class Console
  {
  public:
    const enum Enum { SPACE_BETWEEN_TILE = 3 };

    static COORD get_cursor();
    static void set_cursor(const COORD& t_pos);

    Console();
    ~Console() = default;
    Console(const Console& t_to_copy);
    Console& operator=(const Console& t_to_copy);
    
    void show() const;
    void print_player_status() const;
    void print_map() const;
    void marked(const COORD& t_pos, char t_symbol) const;
  private:
    COORD m_map_start_ = { 0, 0 };
    std::unique_ptr<Status_panel> m_monster_status_ = nullptr;
    std::unique_ptr<Status_panel> m_cursor_status_ = nullptr;
    std::unique_ptr<Hp_bar> m_player_hp_ = nullptr;
    std::unique_ptr<Timer> m_timer_ = nullptr;
  };

}//G6037599

#endif //CONSOLE