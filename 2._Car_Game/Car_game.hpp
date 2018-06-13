#ifndef G6037599_CAR_GAME_HPP
#define G6037599_CAR_GAME_HPP
#pragma once
#include "0._Game_Engine/Game_engine.hpp"

namespace G6037599
{
  class Car_game final
  {
  public:
    static void run();

    ~Car_game() = default;
  private:
    Game_engine m_engine_;

    Car_game() = default;
    Car_game(const Car_game& t_to_copy) = default;
    Car_game(Car_game&& t_to_move) noexcept = default;
    Car_game& operator=(const Car_game& t_to_copy) = default;
    Car_game& operator=(Car_game&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_CAR_GAME_HPP