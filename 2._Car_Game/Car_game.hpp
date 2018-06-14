#ifndef G6037599_CAR_GAME_HPP
#define G6037599_CAR_GAME_HPP
#pragma once
#include "Car.hpp"

namespace G6037599
{
  class Grid;

  class Car_game final
  {
  public:
    static void run();

    ~Car_game() = default;
  private:
    static bool m_is_running_;

    std::vector<std::unique_ptr<Car>> m_cars_;
    std::shared_ptr<Grid> m_track_{};

    Car_game();
    Car_game(const Car_game& t_to_copy) = default;
    Car_game(Car_game&& t_to_move) noexcept = default;
    Car_game& operator=(const Car_game& t_to_copy) = default;
    Car_game& operator=(Car_game&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_CAR_GAME_HPP