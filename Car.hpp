#ifndef G6037599_CAR_HPP
#define G6037599_CAR_HPP
#pragma once

namespace G6037599
{
  class Car
  {
  public:
    Car(const std::string& t_name, const std::string& t_shape
      , int t_max_fuel, int t_speed);
    ~Car() = default;
    Car& operator=(const Car& t_to_copy) = default;
    Car& operator=(Car&& t_to_move) noexcept = default;
  private:
    std::string m_name_{}, m_shape_{};
    int m_max_fuel_, m_fuel_, m_speed_;

    Car(const Car& t_to_copy) = default;
    Car(Car&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GAME_ENGINE_HPP