#ifndef G6037599_GAME_ENGINE_HPP
#define G6037599_GAME_ENGINE_HPP
#pragma once

namespace G6037599
{
  class Grid;

  class Game_engine final
  {
  public:
    static void start();
    static void limit_interval(int& t_number, int t_min, int t_max);

    Game_engine() = default;
    ~Game_engine() = default;
  private:
    std::shared_ptr<Grid> m_grid_;

    Game_engine(const Game_engine& t_to_copy) = default;
    Game_engine(Game_engine&& t_to_move) noexcept = default;
    Game_engine& operator=(const Game_engine& t_to_copy) = default;
    Game_engine& operator=(Game_engine&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GAME_ENGINE_HPP