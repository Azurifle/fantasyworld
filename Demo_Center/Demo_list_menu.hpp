#ifndef G6037599_DEMO_LIST_MENU_HPP
#define G6037599_DEMO_LIST_MENU_HPP
#pragma once

namespace G6037599
{
  class Demo_list_menu final
  {
  public:
    enum Enum
    {
      OPTION_1 = '1', OPTION_2, OPTION_3, OPTION_4, OPTION_5, OPTION_6, OPTION_LAST
    };

    static void start();
  private:
    static void show_menu();
    static void show_option(char t_option, const char* t_name);
    static bool choose_option();
    static void do_option(int t_option = OPTION_LAST);
    static void back_to_main_menu();

    Demo_list_menu() = default;
    ~Demo_list_menu() = default;
    Demo_list_menu(const Demo_list_menu& t_to_copy) = default;
    Demo_list_menu(Demo_list_menu&& t_to_move) noexcept = default;
    Demo_list_menu& operator = (const Demo_list_menu& t_to_copy) = default;
    Demo_list_menu& operator = (Demo_list_menu&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_DEMO_LIST_MENU_HPP