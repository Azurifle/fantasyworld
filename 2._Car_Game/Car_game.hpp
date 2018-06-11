#ifndef G6037599_CAR_GAME_HPP
#define G6037599_CAR_GAME_HPP
#pragma once

namespace G6037599
{
  class Car_game final
  {
  public:
    Car_game() = default;
    ~Car_game() = default;

    void run();
  private:
    Car_game(const Car_game& t_to_copy) = default;
    Car_game(Car_game&& t_to_move) noexcept = default;
    Car_game& operator=(const Car_game& t_to_copy) = default;
    Car_game& operator=(Car_game&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_CAR_GAME_HPP