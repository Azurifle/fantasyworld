#ifndef MENU_UI
#define MENU_UI
#pragma once

namespace G6037599
{
  class Menu_ui
  {
  public:
    Menu_ui() = default;
    virtual ~Menu_ui();

    static int main_menu();
    /*static COORD get_cursor();

    static void set_cursor(int t_y, int t_x);*/
    static int limit_interval(int t_number, int t_low, int t_high);
  private:
    static char press_any_key();
    static void main_menu_topic()
      , back_to_main_menu()

      , fantasy_world()
      , fantasy_world_2_d()
      , hero_in_fantasy_world();
  };
}//G6037599

#endif //MENU_UI