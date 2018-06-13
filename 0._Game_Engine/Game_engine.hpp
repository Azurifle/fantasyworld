#ifndef G6037599_GAME_ENGINE_HPP
#define G6037599_GAME_ENGINE_HPP
#pragma once

namespace G6037599
{
  class Grid;

  class Game_engine final
  {
  public:
    enum Wait_key
    {
      KEY_NO_PRESS
      , KEY_ARROW = 224
      , KEY_ARROW_UP = 72, KEY_ARROW_DOWN = 80
      , KEY_ARROW_LEFT = 75, KEY_ARROW_RIGHT = 77
      , KEY_ESC = 27
    };

    static void start();
    static bool is_running();
    static int get_key();
    static int wait_key();
    static int wait_key(int t_miliseconds);
    static void limit_interval(int& t_number, int t_min, int t_max);

    Game_engine() = default;
    ~Game_engine() = default;
  private:
    static bool m_is_running_;

    static void disable_mouse_editing();
    static void show_header();
    static void back_to_main_menu();

    std::shared_ptr<Grid> m_grid_;

    Game_engine(const Game_engine& t_to_copy) = default;
    Game_engine(Game_engine&& t_to_move) noexcept = default;
    Game_engine& operator=(const Game_engine& t_to_copy) = default;
    Game_engine& operator=(Game_engine&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GAME_ENGINE_HPP